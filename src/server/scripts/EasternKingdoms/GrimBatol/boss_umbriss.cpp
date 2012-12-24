/*
 * Copyright (C) 2011 True Blood <http://www.trueblood-servers.com/>
 * By Asardial
 *
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "ScriptPCH.h"
#include "grimbatol.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

#define SAY_AGGRO "Millions more await my orders. What chance do you have?"
#define SAY_DIED "Finally, this nightmare is over ..."

enum Texts
{
    SAY_BOMBING_1,
    SAY_BOMBING_2,
    SAY_SUMMON,
    SAY_KILL_1,
    SAY_KILL_2,
    EMOTE_BLITZ,
    EMOTE_GROUND_SIEGE,
    EMOTE_FRENZY
};

enum Creatures
{
    NPC_UMBRISS         = 39625,
    NPC_MALIGNANT_TROGG = 39984,
    NPC_TROGG_DWELLER   = 45467
};

enum Spells
{
    BLEEDING_WOUND          = 74846,
    BLEEDING_WOUND_H        = 91937,
    GROUND_SIEGE            = 74634,
    GROUND_SIEGE_H          = 90249,
    BLITZ                   = 74670,
    BLITZ_H                 = 90250,
    FRENZY                  = 74853,
    //Adds
    CLAW_PUNCTURE           = 76507,
    CLAW_PUNCTURE_H         = 90212,
    MODGUD_MALICE           = 74699,
    MODGUD_MALICE_H         = 90169,
};

struct Locations
{
    float x, y, z, o;
};

static Locations SpawnPosition[]=
{
    {-722.15f, -442.53f, 268.77f, 0.54f},
    {-702.22f, -450.9f, 268.77f, 1.34f}
};

class boss_general_umbriss : public CreatureScript
{
    public:

        boss_general_umbriss() : CreatureScript("boss_general_umbriss")
        {
        }

        struct boss_general_umbrissAI : public ScriptedAI
        {
            boss_general_umbrissAI(Creature *c) : ScriptedAI(c)
            {
                pInstance = c->GetInstanceScript();
            }

            uint32 blitzTimer;
            uint32 groundTimer;
            uint32 woundTimer;
            uint32 addTimer;
            bool isMalignantSpawn;
            bool enrage;

            InstanceScript* pInstance;

            void Reset()
            {
                woundTimer = 15000;
                groundTimer = 30000;
                blitzTimer = 25000;
                addTimer = 18000;
                isMalignantSpawn = false;
                enrage = false;
                me->RemoveAurasDueToSpell(DUNGEON_MODE(MODGUD_MALICE,MODGUD_MALICE_H));
                me->RemoveAurasDueToSpell(FRENZY);
            }

            void EnterCombat(Unit* pWho)
            {
                me->MonsterYell(SAY_AGGRO, 0, 0);
            }

            void JustDied(Unit* pKiller)
            {
				me->MonsterYell(SAY_DIED, 0, 0);
                if (pInstance)
                {
                    pInstance->SetData(DATA_GENERAL_UMBRISS_EVENT, DONE);
                    if (IsHeroic() && me->HasAura(MODGUD_MALICE_H))
                        pInstance->DoCompleteAchievement(ACHIEV_UMBRAGE_FOR_UMBRISS);
                }
            }

            void KilledUnit(Unit* /*victim*/)
            {
                switch(urand(0,1))
                {
                    case 0: Talk(SAY_KILL_1); break;
                    case 1: Talk(SAY_KILL_2); break;
                }
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if(woundTimer <= uiDiff)
                {
                    DoCastVictim(DUNGEON_MODE(BLEEDING_WOUND,BLEEDING_WOUND_H));
                    woundTimer = 25000;
                }else woundTimer -= uiDiff;

                if(groundTimer <= uiDiff)
                {
                    if(Unit* unit = SelectTarget(SELECT_TARGET_RANDOM, 1))
                    {
                        Talk(EMOTE_GROUND_SIEGE);
                        DoCast(unit, DUNGEON_MODE(GROUND_SIEGE,GROUND_SIEGE_H));
                    }

                    groundTimer = 30000;
                }else groundTimer -= uiDiff;

                if(blitzTimer <= uiDiff)
                {
                    if(Unit* unit = SelectTarget(SELECT_TARGET_RANDOM, 1))
                    {
                        Talk(EMOTE_BLITZ, unit->GetGUID());
                        DoCast(unit, DUNGEON_MODE(BLITZ,BLITZ_H));
                    }
                    blitzTimer = 25000;
                }else blitzTimer -= uiDiff;

                if(!enrage)
                {
                    if(addTimer <= uiDiff)
                    {
                        Talk(SAY_SUMMON);
                        SpawnMalignant();
                        SpawnAdd();
                        addTimer = 60000;

                    }else addTimer -= uiDiff;

                    if (HealthBelowPct(30))
                    {
                        enrage = true;
                        Talk(EMOTE_FRENZY);
                        DoCast(FRENZY);
                    }
                }

                DoMeleeAttackIfReady();
            }

            void SpawnAdd()
            {
                for(int i = 0; i < 3; i ++)
                    SummonCreatureWithRandomTarget(NPC_TROGG_DWELLER, SpawnPosition[0].x,SpawnPosition[0].y,SpawnPosition[0].z,SpawnPosition[0].o);
            }

            void SpawnMalignant()
            {
                if(!isMalignantSpawn && !enrage)
                {
                    SummonCreatureWithRandomTarget(NPC_MALIGNANT_TROGG, SpawnPosition[1].x,SpawnPosition[1].y,SpawnPosition[1].z,SpawnPosition[1].o);
                    isMalignantSpawn = true;
                }
            }

            void SummonCreatureWithRandomTarget(uint32 creatureId, float x, float y, float z, float o)
            {
                Creature* Summoned = me->SummonCreature(creatureId, x, y, z, 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 5000);
                if (Summoned)
                {
                    Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    if (pTarget)
                    {
                        Summoned->AddThreat(pTarget, 1.0f);
                        Summoned->AI()->AttackStart(pTarget);
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_general_umbrissAI(pCreature);
        }
};

class npc_malignant : public CreatureScript
{
    public:

        npc_malignant() : CreatureScript("npc_malignant")
        {
        }

        struct npc_malignantAI : public ScriptedAI
        {
            npc_malignantAI(Creature *c) : ScriptedAI(c)
            {
                me->AddAura(DUNGEON_MODE(MODGUD_MALICE,MODGUD_MALICE_H), me);
                die = false;
            }

            bool die;

            void DamageTaken(Unit* /*done_by*/, uint32& damage)
            {
                if(die)
                {
                    damage = 0;
                    return;
                }

                if(damage >= me->GetHealth())
                {
                    die = true;
                    damage = 0;
                    if(Creature* umbriss = me->FindNearestCreature(NPC_UMBRISS,100.0f))
                    {
                        std::list<Creature*> troggList;
                        GetCreatureListWithEntryInGrid(troggList, me, NPC_TROGG_DWELLER, 8.0f);

                        if (!troggList.empty())
                        {
                            for (std::list<Creature*>::const_iterator itr = troggList.begin(); itr != troggList.end(); ++itr)
                            {
                                if (Creature* trog = *itr)
                                {
                                    CAST_AI(boss_general_umbriss::boss_general_umbrissAI, umbriss->AI())->SummonCreatureWithRandomTarget(NPC_MALIGNANT_TROGG, trog->GetPositionX(), trog->GetPositionY(), trog->GetPositionZ(), 0);
                                    trog->DespawnOrUnsummon();
                                }
                            }
                        }

                        if (me->GetDistance2d(umbriss->GetPositionX(), umbriss->GetPositionY()) < 8.0f)
                            me->AddAura(DUNGEON_MODE(MODGUD_MALICE,MODGUD_MALICE_H), umbriss);

                        CAST_AI(boss_general_umbriss::boss_general_umbrissAI, umbriss->AI())->isMalignantSpawn = false;
                        CAST_AI(boss_general_umbriss::boss_general_umbrissAI, umbriss->AI())->SpawnMalignant();
                    }

                    me->DespawnOrUnsummon();
                }
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                DoSpellAttackIfReady(DUNGEON_MODE(CLAW_PUNCTURE,CLAW_PUNCTURE_H));
            }
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_malignantAI(pCreature);
        }
};

class npc_trogg_dweller : public CreatureScript
{
    public:

        npc_trogg_dweller() : CreatureScript("npc_trogg_dweller")
        {
        }

        struct npc_trogg_dwellerAI : public ScriptedAI
        {
            npc_trogg_dwellerAI(Creature *c) : ScriptedAI(c) {}

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                DoSpellAttackIfReady(DUNGEON_MODE(CLAW_PUNCTURE,CLAW_PUNCTURE_H));
            }
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_trogg_dwellerAI(pCreature);
        }
};

void AddSC_boss_general_umbriss()
{
    new boss_general_umbriss();
    new npc_malignant();
    new npc_trogg_dweller();
}
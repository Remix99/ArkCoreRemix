/*Reset CDs/HP/Mana on duel END
 By Hrr_95*/
#include "ScriptPCH.h"
#include "config.h"

class Reset_OnDuelEnd : public PlayerScript
{
    public:
        Reset_OnDuelEnd() : PlayerScript("Reset_OnDuelEnd") {}

    void OnDuelEnd(Player *Pw, Player *Pl, DuelCompleteType type)
    {
	uint32 zone1 = ConfigMgr::GetIntDefault("Duel.Zone1", NULL);
	uint32 zone2 = ConfigMgr::GetIntDefault("Duel.Zone2", NULL);
	uint32 zone3 = ConfigMgr::GetIntDefault("Duel.Zone3", NULL);
	uint32 zone4 = ConfigMgr::GetIntDefault("Duel.Zone4", NULL);
                if (Pw->GetZoneId() == zone1 || Pw->GetZoneId() == zone2 || Pw->GetZoneId() == zone3 || Pw->GetZoneId() == zone4)
                {
						
                        Pw->RemoveArenaSpellCooldowns();
                        Pl->RemoveArenaSpellCooldowns();
                        Pw->SetHealth(Pw->GetMaxHealth());
                        Pw->SetPower(POWER_MANA, Pw->GetMaxPower(POWER_MANA));
                        Pl->SetHealth(Pl->GetMaxHealth());
                        Pl->SetPower(POWER_MANA, Pl->GetMaxPower(POWER_MANA));
                }
    }
};

void AddSC_Reset_OnDuelEnd()
{
    new Reset_OnDuelEnd;
}
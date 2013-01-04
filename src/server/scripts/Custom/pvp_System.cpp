// Original Author: Kjanko and Trinity Forum for Ideas:
// Updated and expanded by Pryd, tested and works great.

#include "ScriptPCH.h"

///////////////////////////////////////////////////////////////////////
/////////////////////// CONFIG /////////////////////////////
/////////////////////////////////////////////////////////////////////

float Version = 2.50f; //Don't touch this.
bool PvPSystemEnabled = true; //Set to false if you want to disable the PvP System
bool OnlyInBattlegrounds = false; //Set to true if you want to enable this only in battlegrounds.
bool LooseTokenOnPvPDeath = false; //Set to true if you want the victim to loose tokens when the victim dies.
int32 AmountOfItemsYouWantTheVictimToLoose = 0; //Amount of items you want the victim to loose when victim dies.
bool AddTokenOnPvPKill = false; //Set to false if you don't want the killer to be rewarded.
int32 ItemReward = 0; //The ItemID of the reward.
int32 AmountOfRewardsOnKillStreak[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //With how many items you want to reward the killer when he slays the victim.
int32 HowManyTimesYouWantTheKillerToGetAwardedForKillingTheSameVictim = 25; //Name speaks for It self.
const int32 KillerStreak15 = 5;
const int32 KillerStreak20 = 10;
const int32 KillerStreak30 = 15;
const int32 KillerStreak40 = 20;
const int32 KillerStreak50 = 25;
const int32 KillerStreak60 = 30;
const int32 KillerStreak70 = 35;
const int32 KillerStreak80 = 40;
const int32 KillerStreak90 = 45;
const int32 KillerStreak100 = 50;
const int32 KillerStreak110 = 55;
const int32 KillerStreak120 = 60;
const int32 KillerStreak130 = 65;
const int32 KillerStreak140 = 70;
const int32 KillerStreak150 = 75;
uint32 KillStreaks[16] = { KillerStreak15, KillerStreak20, KillerStreak30, KillerStreak40, KillerStreak50, KillerStreak60, KillerStreak70, KillerStreak80, KillerStreak90, KillerStreak100, KillerStreak110, KillerStreak120, KillerStreak130, KillerStreak140, KillerStreak150 };
///////////////////////////////////////////////////////////////////
/////////////////////// END ////////////////////////////
/////////////////////////////////////////////////////////////////


struct SystemInfo
{
    uint32 KillStreak;
    uint32 LastGUIDKill;
    uint8 KillCount;
};

static std::map<uint32, SystemInfo> KillingStreak;

class System_OnPVPKill : public PlayerScript
{
        public:
                System_OnPVPKill() : PlayerScript("System_OnPVPKill") {}

        
void OnPVPKill(Player *pKiller, Player *pVictim)
{
    if(PvPSystemEnabled == false)
    {
             return;
    }
    else if(PvPSystemEnabled == true)
    {
        uint32 kGUID;
        uint32 vGUID;
        char msg[500];
        kGUID = pKiller->GetGUID();
        vGUID = pVictim->GetGUID();
        if(kGUID == vGUID)
        {
          return;
        }
                
      if(KillingStreak[kGUID].LastGUIDKill == vGUID)
        {
        KillingStreak[kGUID].KillCount++;
        KillingStreak[vGUID].KillCount = 1;
          pKiller->AddItem(ItemReward, 1);
        if(LooseTokenOnPvPDeath == true)
          pVictim->DestroyItemCount(ItemReward, AmountOfItemsYouWantTheVictimToLoose, true, false);
        }
      if(KillingStreak[kGUID].LastGUIDKill != vGUID)
      {
        KillingStreak[kGUID].KillCount = 1;
        KillingStreak[vGUID].KillCount = 1;
      }

      if(KillingStreak[kGUID].KillCount == HowManyTimesYouWantTheKillerToGetAwardedForKillingTheSameVictim)
      {
        return;
      }

      if(OnlyInBattlegrounds == true)
        {
        if(!pKiller->GetMap()->IsBattleground())
           return;
      }

        KillingStreak[kGUID].KillStreak++;
        KillingStreak[vGUID].KillStreak = 0;
        KillingStreak[kGUID].LastGUIDKill = vGUID;
        KillingStreak[vGUID].LastGUIDKill = 0;
      if(AddTokenOnPvPKill == true)
          pKiller->AddItem(ItemReward, 1);
      if(LooseTokenOnPvPDeath == true)
        pVictim->DestroyItemCount(ItemReward, AmountOfItemsYouWantTheVictimToLoose, true, false);
                
        switch(KillingStreak[kGUID].KillStreak)
        {



        case KillerStreak15:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(1) - Beware of |cFFa2cc0f%s|r the Criminal who destroyed |cFFff0000%s|r and is warming up with a 2 person killing spree. Rising to the top!", pKiller->GetName(), pVictim->GetName(), KillStreaks[1]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,65858,true);
        break;

        case KillerStreak20:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(2) - Avoid |cFFa2cc0f%s|r the Insane who dismembered |cFFff0000%s|r and is on fire with a 3 person killing spree. Inspired by death..", pKiller->GetName(), pVictim->GetName(), KillStreaks[2]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
       // pKiller->CastSpell(pKiller,65874,true);
        break;

        case KillerStreak30:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(3) - Watch out! |cFFa2cc0f%s|r the Maniac has slain |cFFff0000%s|r and is on a crazed 4 person killing spree. Full of comtempt!", pKiller->GetName(), pVictim->GetName(), KillStreaks[3]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        //pKiller->CastSpell(pKiller,67260,true);
        break;
        
        case KillerStreak40:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(4) - Caution! |cFFa2cc0f%s|r the Serial Killer has massacred |cFFff0000%s|r and is on a 5 person killing spree. Focused on the path.", pKiller->GetName(), pVictim->GetName(), KillStreaks[4]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        //pKiller->CastSpell(pKiller,67257,true);
        break;

        case KillerStreak50:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(5) - Fate steps aside as |cFFa2cc0f%s|r the Unmerciful has relinquished |cFFff0000%s|r to the heavens and is on a 6 person killing spree. Demonic intentions", pKiller->GetName(), pVictim->GetName(), KillStreaks[5]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,67259,true);
        break;
        
        case KillerStreak60:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(6) - Attention! |cFFa2cc0f%s|r the Ender has absolved |cFFff0000%s|r and is on a 7 person killing spree. Halfway to the highest of Ken", pKiller->GetName(), pVictim->GetName(), KillStreaks[6]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        //pKiller->CastSpell(pKiller,67256,true);
        break;
        
        case KillerStreak70:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(7) - Be wary! |cFFa2cc0f%s|r the Gravedigger has buried |cFFff0000%s|r and is raging with a 8 person killing spree. Working the late night shift!", pKiller->GetName(), pVictim->GetName(), KillStreaks[7]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        //pKiller->CastSpell(pKiller,67261,true);
        break;

        case KillerStreak80:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(8) - Like clockwork, |cFFa2cc0f%s|r the Mastermind has tactfully removed |cFFff0000%s|r from battle and is on fire with a 9 person killing spree. Motivated by the one.", pKiller->GetName(), pVictim->GetName(), KillStreaks[8]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        //pKiller->CastSpell(pKiller,67258,true);
        break;

        case KillerStreak90:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(9) - Concealed in the Shadows, |cFFa2cc0f%s|r the Assassin has slain |cFFff0000%s|r and is on a 10 person killing spree. Seeking revenge for the past.", pKiller->GetName(), pVictim->GetName(), KillStreaks[9]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,80747,true);
        break;

        case KillerStreak100:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(10) - Tossing the carcass aside, |cFFa2cc0f%s|r the Bloodletter has devoured |cFFff0000%s|r and is on a 11 person killing spree. Hell walks among the living.", pKiller->GetName(), pVictim->GetName(), KillStreaks[10]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        pKiller->CastSpell(pKiller,95537,true);
        break;

        case KillerStreak110:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(11) - Cower before |cFFa2cc0f%s|r the Unstoppable who has slain |cFFff0000%s|r and is on a rampaging 12 person killing spree. Second in command to only one!", pKiller->GetName(), pVictim->GetName(), KillStreaks[11]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        //pKiller->CastSpell(pKiller,24378,true);
        break;
        
        case KillerStreak120:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(12) - Fear |cFFa2cc0f%s|r the Conqueror; who has annihilated yet another victim, |cFFff0000%s|r, and is on a 13 person killing spree. UnMatched by all, can no one stop them?", pKiller->GetName(), pVictim->GetName(), KillStreaks[12]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        //pKiller->CastSpell(pKiller,24378,true);
        break;
        
        case KillerStreak130:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(13) - Fear |cFFa2cc0f%s|r the Conqueror; who has annihilated yet another victim, |cFFff0000%s|r, and is on a 14 person killing spree. UnMatched by all, can no one stop them?", pKiller->GetName(), pVictim->GetName(), KillStreaks[12]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[1]);
        //pKiller->CastSpell(pKiller,24378,true);
        break;
        
        case KillerStreak140:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(14) - Fear |cFFa2cc0f%s|r the Conqueror; who has annihilated yet another victim, |cFFff0000%s|r, and is on a 15 person killing spree. UnMatched by all, can no one stop them?", pKiller->GetName(), pVictim->GetName(), KillStreaks[12]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[2]);
        //pKiller->CastSpell(pKiller,24378,true);
        break;

        case KillerStreak150:
        sprintf(msg, "|cFFff8400[Kill Streak]:|r -RANK-(15) - The Reaper |cFFa2cc0f%s|r ; Has claimed another soul for the harvest, |cFFff0000%s|r, and is on a 20 person killing spree. Who will be their next victim?!", pKiller->GetName(), pVictim->GetName(), KillStreaks[12]);
        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
        pKiller->AddItem(ItemReward, AmountOfRewardsOnKillStreak[2]);
        pKiller->CastSpell(pKiller,24378,true);
        break;
        
        

                                               
                                                        
                                                       }
     }

                
        }
};

void AddSC_System_OnPVPKill()
{
    new System_OnPVPKill();
}
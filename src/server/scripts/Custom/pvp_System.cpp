/*
Originally by Kjanko
Edited by Tommy
Edited by Rochet2 ~ Made dynamic
*/

#include "ScriptPCH.h"

class System_OnKill : public PlayerScript
{
	public:
		System_OnKill() : PlayerScript("System_OnKill") {}

	void OnPVPKill(Player * Killer, Player * Victim)
	{
		uint64 KillerGUID = Killer->GetGUID();
		uint64 VictimGUID = Victim->GetGUID();

		struct KillStreak_Info
		{
			uint32 killstreak;
			uint64 lastkill;
		};

		static std::map<uint32, KillStreak_Info> KillStreakData;

		if( KillerGUID == VictimGUID || KillStreakData[KillerGUID].lastkill == VictimGUID )
			return;

		if( KillStreakData[VictimGUID].killstreak >= 3 )
		{
			char msg[250];
			snprintf(msg, 250, "|cFF81CF42%s|r has ended |cFFFFFFFF%s|r's killing spree!", Killer->GetName(), Victim->GetName());
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
		}

		KillStreakData[KillerGUID].killstreak++;
		KillStreakData[KillerGUID].lastkill = VictimGUID;
		KillStreakData[VictimGUID].killstreak = 0;
		KillStreakData[VictimGUID].lastkill = 0;

		if( KillStreakData[KillerGUID].killstreak % 10 == 0 ) // send killstreak message every 10 kills
		{
			char msg[250];
			snprintf(msg, 250, "|cFF81CF42%s|r has a killstreak of |cFF42A0CF%u|r!", Killer->GetName(), KillStreakData[KillerGUID].killstreak);
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
		}
		else if( KillStreakData[KillerGUID].killstreak == 3 )
		{
			char msg[250];
			snprintf(msg, 250, "|cFF81CF42%s|r is on a killingspree!", Killer->GetName());
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
		}

	}
};

void AddSC_PvP_System()
{
    new System_OnKill;
}
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//######################################################################||
//                                                                     #||
//  Scripted By -Oreo-                                                 #||
//           ~~                                                        #||
//         [Title_NPC Script]                                          #||
//         (Please don't remove credits!)                              #||
//                                                                     #||
//######################################################################||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

#include "ScriptPCH.h"


enum enums
{
	//Token ID!
	TITLE_TOKEN = 37829, //Change me pl0x
	//Cost for title!
	TITLE_1 = 50, //Change me pl0x
	TITLE_2 = 100, //Change me pl0x
	TITLE_3 = 150, //Change me pl0x
	TITLE_4 = 200, //Change me pl0x
	TITLE_5 = 250, //Change me pl0x
	TITLE_6 = 300, //Change me pl0x
	TITLE_7 = 350, //Change me pl0x
	TITLE_8 = 400, //Change me pl0x
	TITLE_9 = 450, //Change me pl0x
	TITLE_10 = 500, //Change me pl0x
	TITLE_11 = 550, //Change me pl0x
	TITLE_12 = 600, //Change me pl0x
	TITLE_13 = 650, //Change me pl0x
	TITLE_14 = 700, //Change me pl0x
};
	
//---------------------------------------//
    class Title_NPC : public CreatureScript
    {
            public:
            Title_NPC() : CreatureScript("Title_NPC") { }

			bool OnGossipHello(Player * pPlayer, Creature * pCreature)
	{
		if (pPlayer->GetTeam() == ALLIANCE)
		{
		pPlayer->ADD_GOSSIP_ITEM(4, "Alliance Titles", GOSSIP_SENDER_MAIN, 0); //Alliance Titles Main Gossip
		}
		else
		{
		pPlayer->ADD_GOSSIP_ITEM(4, "Horde Titles", GOSSIP_SENDER_MAIN, 1); //Horde Titles Main Gossip
		}
		pPlayer->PlayerTalkClass->SendGossipMenu(9452, pCreature->GetGUID());
		return true;
	}

		bool OnGossipSelect(Player * pPlayer, Creature * pCreature, uint32 sender, uint32 uiAction)
	{
		if (sender == GOSSIP_SENDER_MAIN)
		{
			pPlayer->PlayerTalkClass->ClearMenus();
			switch(uiAction)
			{

	{
		case 0:
		pPlayer->ADD_GOSSIP_ITEM(4, "Private (50 Title Tokens)", GOSSIP_SENDER_MAIN, 2);
		pPlayer->ADD_GOSSIP_ITEM(4, "Corporal(100 Title Tokens)", GOSSIP_SENDER_MAIN, 3);
		pPlayer->ADD_GOSSIP_ITEM(4, "Sergeant(150 Title Tokens)", GOSSIP_SENDER_MAIN, 4);
		pPlayer->ADD_GOSSIP_ITEM(4, "Master Sergeant(200 Title Tokens)", GOSSIP_SENDER_MAIN, 5);
		pPlayer->ADD_GOSSIP_ITEM(4, "Sergeant Major (250 Title Tokens)", GOSSIP_SENDER_MAIN, 6);
		pPlayer->ADD_GOSSIP_ITEM(4, "Knight (300 Title Tokens)", GOSSIP_SENDER_MAIN, 7);
		pPlayer->ADD_GOSSIP_ITEM(4, "Knight-Lieutenant(350 Title Tokens)", GOSSIP_SENDER_MAIN, 8);
		pPlayer->ADD_GOSSIP_ITEM(4, "Knight-Captain (400 Title Tokens)", GOSSIP_SENDER_MAIN, 9);
		pPlayer->ADD_GOSSIP_ITEM(4, "Knight-Champion (450 Title Tokens)", GOSSIP_SENDER_MAIN, 10);
		pPlayer->ADD_GOSSIP_ITEM(4, "Lieutenant Commander (500 Title Tokens)", GOSSIP_SENDER_MAIN, 11);
		pPlayer->ADD_GOSSIP_ITEM(4, "Commander (550 Title Tokens)", GOSSIP_SENDER_MAIN, 12);
		pPlayer->ADD_GOSSIP_ITEM(4, "Marshal(600 Title Tokens)", GOSSIP_SENDER_MAIN, 13);
		pPlayer->ADD_GOSSIP_ITEM(4, "Field Marshal(650 Title Tokens)", GOSSIP_SENDER_MAIN, 14);
		pPlayer->ADD_GOSSIP_ITEM(4, "Grand Marshal(700 Title Tokens)", GOSSIP_SENDER_MAIN, 15);
		pPlayer->PlayerTalkClass->SendGossipMenu(9452, pCreature->GetGUID());
		break;

		case 1:
		pPlayer->ADD_GOSSIP_ITEM(4, "Scout(50 Title Tokens)", GOSSIP_SENDER_MAIN, 14);
		pPlayer->ADD_GOSSIP_ITEM(4, "Grunt(100 Title Tokens)", GOSSIP_SENDER_MAIN, 15);
		pPlayer->ADD_GOSSIP_ITEM(4, "Sergeant(150 Title Tokens)", GOSSIP_SENDER_MAIN, 16);
		pPlayer->ADD_GOSSIP_ITEM(4, "Senior Sergeant(200 Title Tokens)", GOSSIP_SENDER_MAIN, 17);
		pPlayer->ADD_GOSSIP_ITEM(4, "First Major(250 Title Tokens)", GOSSIP_SENDER_MAIN, 18);
		pPlayer->ADD_GOSSIP_ITEM(4, "Stone Guard(300 Title Tokens)", GOSSIP_SENDER_MAIN, 19);
		pPlayer->ADD_GOSSIP_ITEM(4, "Blood Guard(350 Title Tokens)", GOSSIP_SENDER_MAIN, 20);
		pPlayer->ADD_GOSSIP_ITEM(4, "Legionnaire(400 Title Tokens)", GOSSIP_SENDER_MAIN, 21);
		pPlayer->ADD_GOSSIP_ITEM(4, "Centurion(450 Title Tokens)", GOSSIP_SENDER_MAIN, 22);
		pPlayer->ADD_GOSSIP_ITEM(4, "Champion(500 Title Tokens)", GOSSIP_SENDER_MAIN, 23);
		pPlayer->ADD_GOSSIP_ITEM(4, "Lieutenant General(550 Title Tokens)", GOSSIP_SENDER_MAIN, 24);
		pPlayer->ADD_GOSSIP_ITEM(4, "General(600 Title Tokens)", GOSSIP_SENDER_MAIN, 25);
		pPlayer->ADD_GOSSIP_ITEM(4, "Warlord(650 Title Tokens)", GOSSIP_SENDER_MAIN, 26);
		pPlayer->ADD_GOSSIP_ITEM(4, "High Warlord(700 Title Tokens)", GOSSIP_SENDER_MAIN, 27);
		pPlayer->PlayerTalkClass->SendGossipMenu(9452, pCreature->GetGUID());
		break;
	
				//Alliance
				case 2: 
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_1, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_1, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(1);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 3:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_2, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_2, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(2);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 4:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_3, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_3, true);
						 CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(3);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 5:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_4, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_4, true);
						 CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(4);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 6:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_5, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_5, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(5);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 7:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_6, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_6, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(6);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 8:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_7, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_7, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(7);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 9:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_8, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_8, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(8);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 10:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_9, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_9, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(9);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 11:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_10, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_10, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(10);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 12:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_11, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_11, true);
						 CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(11);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 13:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_12, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_12, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(12);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 14:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_13, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_13, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(13);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 15:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_14, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_14, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(14);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				//Horde
				
				case 16:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_1, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_1, true);
						 CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(15);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 17:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_2, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_2, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(16);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 18:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_3, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_3, true);
				CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(17);
				pPlayer->SetTitle(titleInfo, false);
				pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
				pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 19:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_4, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_4, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(18);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 20:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_5, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_5, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(19);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 21:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_6, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_6, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(20);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 22:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_7, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_7, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(21);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 23:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_8, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_8, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(22);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 24:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_9, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_9, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(23);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 25:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_10, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_10, true);
						 CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(24);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 26:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_11, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_11, true);
						 CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(25);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 27:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_12, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_12, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(26);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 28:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_13, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_13, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(27);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
				}
				break;
				
				case 29:
				if (pPlayer->HasItemCount(TITLE_TOKEN, TITLE_14, true))
				{
				pPlayer->DestroyItemCount(TITLE_TOKEN, TITLE_14, true);
						CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(28);
						pPlayer->SetTitle(titleInfo, false);
						pCreature->MonsterWhisper("Title for you!", pPlayer->GetGUID());
						pPlayer->CLOSE_GOSSIP_MENU();
				}
				else
				{
				 pCreature->MonsterWhisper("You don't deserve a new title!", pPlayer->GetGUID());
				 pPlayer->CLOSE_GOSSIP_MENU();
}


                                    }
                            }
                    }
                    return true;
            }
    };
     
    void AddSC_Title_NPC()
    {
    new Title_NPC();
    }
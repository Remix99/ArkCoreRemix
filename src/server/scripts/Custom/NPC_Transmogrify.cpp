/*
Transmogrification
By Rochet2
*/

#include "ScriptPCH.h"

class NPC_Transmogrify : public CreatureScript
{
public:
	NPC_Transmogrify() : CreatureScript("NPC_Transmogrify") { }

	bool OnGossipHello(Player* pPlayer, Creature* pUnit)
	{
		pPlayer->PlayerTalkClass->ClearMenus();
		for (uint8 Slot = EQUIPMENT_SLOT_START; Slot < EQUIPMENT_SLOT_END; Slot++)
			if (Item* pItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, Slot))
			{
				uint32 Quality = pItem->GetTemplate()->Quality;
				if(Quality == ITEM_QUALITY_UNCOMMON || Quality == ITEM_QUALITY_RARE || Quality == ITEM_QUALITY_EPIC)
					if(char* SlotName = GetSlotName(Slot))
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, SlotName, EQUIPMENT_SLOT_END, Slot);
			}
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Nevermind..", EQUIPMENT_SLOT_END+2, 0);
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pUnit->GetGUID());         
			return true;
	}

	bool OnGossipSelect(Player* pPlayer, Creature* pUnit, uint32 sender, uint32 uiAction)
	{
		pPlayer->PlayerTalkClass->ClearMenus();
		if(sender == EQUIPMENT_SLOT_END)
		{
			if (Item* OLD = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, uiAction))
			{
				uint64 GUID = pPlayer->GetGUID();
				Items[GUID].clear();
				for (uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; i++)
					if (Item* pItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
						if(IsSuitable(pItem, OLD, pPlayer))
							if(Items[GUID].find(pItem->GetTemplate()->DisplayInfoID) == Items[GUID].end())
								Items[GUID][pItem->GetTemplate()->DisplayInfoID] = pItem, pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, pItem->GetTemplate()->Name1, uiAction, pItem->GetTemplate()->DisplayInfoID, AreYouSure(uiAction, pItem), 0, false);

				for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; i++)
					if (Bag* pBag = pPlayer->GetBagByPos(i))
						for (uint32 j = 0; j < pBag->GetBagSize(); j++)
							if (Item* pItem = pPlayer->GetItemByPos(i, j))
								if(IsSuitable(pItem, OLD, pPlayer))
									if(Items[GUID].find(pItem->GetTemplate()->DisplayInfoID) == Items[GUID].end())
										Items[GUID][pItem->GetTemplate()->DisplayInfoID] = pItem, pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, pItem->GetTemplate()->Name1, uiAction, pItem->GetTemplate()->DisplayInfoID, AreYouSure(uiAction, pItem), 0, false);

				if(Items[GUID].empty())
				{
					pPlayer->GetSession()->SendNotification("You have no suitable items in your inventory");
					OnGossipHello(pPlayer, pUnit);
					return true;
				}
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back..", EQUIPMENT_SLOT_END+1, 0);
				pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pUnit->GetGUID());
			}
			else
				OnGossipHello(pPlayer, pUnit);
		}
		else if(sender == EQUIPMENT_SLOT_END+1)
			OnGossipHello(pPlayer, pUnit);
		else if(sender == EQUIPMENT_SLOT_END+2)
			pPlayer->PlayerTalkClass->SendCloseGossip();
		else
		{
			uint64 GUID = pPlayer->GetGUID();
			Item* OLD = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, sender);
			if(!OLD || Items[GUID].find(uiAction) == Items[GUID].end() || !IsSuitable(Items[GUID][uiAction], OLD, pPlayer))
			{
				pPlayer->GetSession()->SendNotification("There is no suitable item in the slot");
				return true;
			}
			else
			{
				pPlayer->UpdateUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (sender * 2), Items[GUID][uiAction]->GetEntry());
				pPlayer->GetSession()->SendAreaTriggerMessage("%s transmogrified", GetSlotName(sender));
			}
			Items[GUID].clear();
			OnGossipHello(pPlayer, pUnit);
		}
		return true;
	}
private:
	std::map<uint64, std::map<uint32, Item*> > Items; // Items[GUID][DISPLAY] = item

	char * GetSlotName(uint8 slot)
	{
		switch(slot)
		{
		case EQUIPMENT_SLOT_HEAD      : return "Head";
		case EQUIPMENT_SLOT_SHOULDERS : return "Shoulders";
		case EQUIPMENT_SLOT_BODY      : return "Shirt";
		case EQUIPMENT_SLOT_CHEST     : return "Chest";
		case EQUIPMENT_SLOT_WAIST     : return "Waist";
		case EQUIPMENT_SLOT_LEGS      : return "Legs";
		case EQUIPMENT_SLOT_FEET      : return "Feet";
		case EQUIPMENT_SLOT_WRISTS    : return "Wrists";
		case EQUIPMENT_SLOT_HANDS     : return "Hands";
		case EQUIPMENT_SLOT_BACK      : return "Back";
		case EQUIPMENT_SLOT_MAINHAND  : return "Main hand";
		case EQUIPMENT_SLOT_OFFHAND   : return "Off hand";
		case EQUIPMENT_SLOT_RANGED    : return "Ranged";
		case EQUIPMENT_SLOT_TABARD    : return "Tabard";
		default: return NULL;
		}
	}

	bool IsSuitable(Item* pItem, Item* OLD, Player* pPlayer)
	{
		if(pPlayer->CanUseItem(pItem, false) == EQUIP_ERR_OK)
		{
			uint32 Quality = pItem->GetTemplate()->Quality;
			if(Quality == ITEM_QUALITY_UNCOMMON || Quality == ITEM_QUALITY_RARE || Quality == ITEM_QUALITY_EPIC)
			{
				uint32 NClass = pItem->GetTemplate()->Class;
				uint32 OClass = OLD->GetTemplate()->Class;
				uint32 NSubClass = pItem->GetTemplate()->SubClass;
				uint32 OSubClass = OLD->GetTemplate()->SubClass;
				if(NClass == OClass) // not possibly the best structure here, but atleast I got my head around this
					if(NClass == ITEM_CLASS_WEAPON)
					{
						if(NSubClass == OSubClass || ((NSubClass == ITEM_SUBCLASS_WEAPON_BOW || NSubClass == ITEM_SUBCLASS_WEAPON_GUN || NSubClass == ITEM_SUBCLASS_WEAPON_CROSSBOW) && (OSubClass == ITEM_SUBCLASS_WEAPON_BOW || OSubClass == ITEM_SUBCLASS_WEAPON_GUN || OSubClass == ITEM_SUBCLASS_WEAPON_CROSSBOW)))
						{
							return true;
						}
					}
					else if(NClass == ITEM_CLASS_ARMOR)
						if(NSubClass == OSubClass && pItem->GetTemplate()->InventoryType == OLD->GetTemplate()->InventoryType)
						{
							return true;
						}
			}
		}
		return false;
	}
	std::string AreYouSure(uint8 slot, Item* pItem)
	{
		std::string msg = "Transmogrify ";
		msg += GetSlotName(slot);
		msg += "\nTo ";
		msg += pItem->GetTemplate()->Name1;
		return msg;
	}
};

void AddSC_NPC_Transmogrify()
{
	new NPC_Transmogrify();
}
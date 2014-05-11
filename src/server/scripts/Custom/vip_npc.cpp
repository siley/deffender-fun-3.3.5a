#include "ScriptPCH.h"

//VIP NPC, coded by minig
//OH $#!T - Repaired by Wolf Officious :D
//Predelano pouze na migraci - Siley

#define VIP_NPC_TEXT_MONEYERR       "Nedostatek penez!"

#define VIP_NPC_TEXT_FACTIONCHANGE  "Novou rasu u druhe frakce si zvolis pri relogu"

#define GOSSIP 65002

class vip_npc : public CreatureScript
{
private:

    enum vipPayPrices
    {
        PRICE_FACTIONCHANGE = 500000000,    // Factionchange price
    };

    bool vip_pay(vipPayPrices price, Player * player)
    {
        if(player->GetMoney() < uint32(price))
            return false;

        player->ModifyMoney( - int32(price) );
        return true;
    }

public:
    vip_npc() : CreatureScript("vip_npc") {}

    bool OnGossipHello(Player *player, Creature *npc)
    {
        if(player->IsInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            npc->MonsterWhisper("Jsi v combatu!", player, true);
            return true;
        }
        player->ADD_GOSSIP_ITEM_EXTENDED( 6, "Zmena frakce (cena 50 000G)", GOSSIP_SENDER_MAIN, 1, "!! UPOZORNENI: Migrace vam smaze veskere questy, ktere mate v questlogu !!", 0, false);
        player->ADD_GOSSIP_ITEM( 0, "Close",    GOSSIP_SENDER_MAIN, 2);
        player->SEND_GOSSIP_MENU(GOSSIP, npc->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player *player, Creature *npc, uint32 sender, uint32 uiAction)
    {
        if(player->IsInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            npc->MonsterWhisper("Jsi v combatu!", player, true);
            return true;
        }

        if(sender != GOSSIP_SENDER_MAIN)
        {
            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        //player->PlayerTalkClass->ClearMenus(); // pøi potížích povolit

        switch(uiAction)
        {
        case 1: //Faction Change
            if(vip_pay(PRICE_FACTIONCHANGE, player))
            {
                player->CLOSE_GOSSIP_MENU();
                player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                npc->MonsterWhisper(VIP_NPC_TEXT_FACTIONCHANGE, player, true);
                return true;
            }
            break;

        case 2: //Close
            {
                player->CLOSE_GOSSIP_MENU();
                return true;
            }

        default:
            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        player->CLOSE_GOSSIP_MENU();
        npc->MonsterWhisper(VIP_NPC_TEXT_MONEYERR, player, true);

        return true;
    }
};

void AddSC_NPC_vip()
{
new vip_npc();
}
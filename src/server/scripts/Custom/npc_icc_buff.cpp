#include "ScriptPCH.h"

#define GOSSIP 11203

class npc_icc_buff : public CreatureScript
{
public:
    npc_icc_buff() : CreatureScript("npc_icc_buff") {}

    bool OnGossipHello(Player *player, Creature *npc)
    {
        if(player->IsInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            npc->MonsterWhisper("You are in combat!", player, true);
            return true;
        }
        player->ADD_GOSSIP_ITEM( 0, "Zrusit buff", GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM( 0, "5% buff", GOSSIP_SENDER_MAIN, 2);
        player->ADD_GOSSIP_ITEM( 0, "10% buff", GOSSIP_SENDER_MAIN, 3);
        player->ADD_GOSSIP_ITEM( 0, "15% buff", GOSSIP_SENDER_MAIN, 4);
        player->ADD_GOSSIP_ITEM( 0, "30% buff", GOSSIP_SENDER_MAIN, 5);          
        player->ADD_GOSSIP_ITEM(0, "Close", GOSSIP_SENDER_MAIN, 6);
        player->SEND_GOSSIP_MENU(GOSSIP, npc->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *npc, uint32 sender, uint32 uiAction)
    {
        if(sender != GOSSIP_SENDER_MAIN)
        {
            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        switch(uiAction)
        {
        case 1:
        {
            player->RemoveAura(73828);
            player->RemoveAura(73762);
            player->RemoveAura(73824);
            player->RemoveAura(73825);
            player->CLOSE_GOSSIP_MENU();
        }
            break;
        case 2:
            player->AddAura(73762, player);
            player->CLOSE_GOSSIP_MENU();
            break;
        case 3:
            player->AddAura(73824, player);
            player->CLOSE_GOSSIP_MENU();
            break;
        case 4:
            player->AddAura(73825, player);
            player->CLOSE_GOSSIP_MENU();
            break;
        case 5:
            player->AddAura(73828, player);
            player->CLOSE_GOSSIP_MENU();
            break;
        case 6: //Close
            {
                player->CLOSE_GOSSIP_MENU();
                return true;
            }
            
        default:
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        return true;
    }
};

void AddSC_npc_icc_buff()
{
new npc_icc_buff();
}
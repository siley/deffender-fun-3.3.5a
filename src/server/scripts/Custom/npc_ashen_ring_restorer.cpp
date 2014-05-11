/*##################
# npc_icc_rep_rings
###################*/

#include "ScriptPCH.h"

#define GMSG  537006
#define GMSNG 537008

void printHasItem(Player *player, Creature *creature)
{
    player->SEND_GOSSIP_MENU( GMSNG, creature->GetGUID());
}



class npc_argent_ring_restorer : public CreatureScript
{
public:
    npc_argent_ring_restorer() : CreatureScript("npc_argent_ring_restorer") { }

    enum AshenRings
    {
        ASHEN_VERDICT = 1156,
        C_F = 50377,
        H_F = 50378,
        MS_F = 52569,
        MA_F = 50376,
        T_F = 50375,
        C_H = 50384,
        H_H = 50386,
        MS_H = 52570,
        MA_H = 50387,
        T_H = 50388,
        C_R = 50397,
        H_R = 50399,
        MS_R = 52571,
        MA_R = 50401,
        T_R = 50403,
        C_E = 50398,
        H_E = 50400,
        MS_E = 52572,
        MA_E = 50402,
        T_E = 50404,
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        uint32 friendly = 3000;
        uint32 honored = 9000;
        uint32 revered = 21000;
        uint32 exalted = 42000;
        uint32 value = player->GetReputation(ASHEN_VERDICT);


        if (value >= friendly && value < honored && player)
        {
            if (!player->HasItemCount(C_F,1,true) && !player->HasItemCount(H_F,1,true) && !player->HasItemCount(MS_F,1,true) && !player->HasItemCount(MA_F,1,true) &&
                !player->HasItemCount(T_F,1,true))
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci caster DPS (frieldy)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci Healer (friendy)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci DPS - str (friendy)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci DPS - agy (friendy)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci tanker (friendy)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+5);
                player->SEND_GOSSIP_MENU(GMSG, creature->GetGUID());
                return true;
            }
            else
                printHasItem(player, creature);

        }

        else if (value >= honored && value < revered && player)
        {
            if (!player->HasItemCount(C_F,1,true) && !player->HasItemCount(H_F,1,true) && !player->HasItemCount(MS_F,1,true) && !player->HasItemCount(MA_F,1,true) &&
                !player->HasItemCount(T_F,1,true) && !player->HasItemCount(C_H,1,true) && !player->HasItemCount(H_H,1,true) && !player->HasItemCount(MS_H,1,true) &&
                !player->HasItemCount(MA_H,1,true) && !player->HasItemCount(T_H,1,true))
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci caster DPS (honored)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci Healer (honored)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci DPS - str (honored)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci DPS  - agy (honored)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci tanker (honored)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+10);
                player->SEND_GOSSIP_MENU(GMSG, creature->GetGUID());
                return true;
            }

            else
                printHasItem(player, creature);

        }

        else if (value >= revered && value < exalted && player)
        {
            if (!player->HasItemCount(C_F,1,true) && !player->HasItemCount(H_F,1,true) && !player->HasItemCount(MS_F,1,true) && !player->HasItemCount(MA_F,1,true) &&
                !player->HasItemCount(T_F,1,true) && !player->HasItemCount(C_H,1,true) && !player->HasItemCount(H_H,1,true) && !player->HasItemCount(MS_H,1,true) &&
                !player->HasItemCount(MA_H,1,true) && !player->HasItemCount(T_H,1,true) && !player->HasItemCount(C_R,1,true) && !player->HasItemCount(H_R,1,true) &&
                !player->HasItemCount(MS_R,1,true) && !player->HasItemCount(MA_R,1,true) && !player->HasItemCount(T_R,1,true))
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci caster DPS (revered)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci Healer (revered)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+12);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci DPS - str (revered)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+13);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci DPS - agy (revered)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+14);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci tanker (revered)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+15);
                player->SEND_GOSSIP_MENU(GMSG, creature->GetGUID());
                return true;
            }

            else
                printHasItem(player, creature);

        }

        else if (value >= exalted && player)
        {
            if (!player->HasItemCount(C_F,1,true) && !player->HasItemCount(H_F,1,true) && !player->HasItemCount(MS_F,1,true) && !player->HasItemCount(MA_F,1,true) &&
                !player->HasItemCount(T_F,1,true) && !player->HasItemCount(C_H,1,true) && !player->HasItemCount(H_H,1,true) && !player->HasItemCount(MS_H,1,true) &&
                !player->HasItemCount(MA_H,1,true) && !player->HasItemCount(T_H,1,true) && !player->HasItemCount(C_R,1,true) && !player->HasItemCount(H_R,1,true) &&
                !player->HasItemCount(MS_R,1,true) && !player->HasItemCount(MA_R,1,true) && !player->HasItemCount(T_R,1,true) && !player->HasItemCount(C_E,1,true) &&
                !player->HasItemCount(H_E,1,true) && !player->HasItemCount(MS_E,1,true) && !player->HasItemCount(MA_E,1,true) && !player->HasItemCount(T_E,1,true))
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci DPS caster(exalted)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+16);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci Healer (exalted)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+17);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci DPS - str (exalted)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+18);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci DPS - agy (exalted)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+19);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,"Chci Tanker (exalted)",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+20);
                player->SEND_GOSSIP_MENU(GMSG, creature->GetGUID());
                return true;
            }

            else
                printHasItem(player, creature);
        }

        else
            printHasItem(player, creature);

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*uiSender*/, uint32 uiAction)
    {
        if (player)
            player->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->AddItem(C_F,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            player->AddItem(H_F,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            player->AddItem(MS_F,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            player->AddItem(MA_F,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            player->AddItem(T_F,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            player->AddItem(C_H,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            player->AddItem(H_H,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+8:
            player->AddItem(MS_H,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+9:
            player->AddItem(MA_H,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+10:
            player->AddItem(T_H,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+11:
            player->AddItem(C_R,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+12:
            player->AddItem(H_R,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+13:
            player->AddItem(MS_R,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+14:
            player->AddItem(MA_R,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+15:
            player->AddItem(T_R,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+16:
            player->AddItem(C_E,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+17:
            player->AddItem(H_E,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+18:
            player->AddItem(MS_E,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+19:
            player->AddItem(MA_E,1);
            break;
        case GOSSIP_ACTION_INFO_DEF+20:
            player->AddItem(T_E,1);
            break;
        }
        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

void AddSC_npc_argent_ring_restorer()
{
    new npc_argent_ring_restorer();
}
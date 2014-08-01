#include "ScriptPCH.h"
#include "Guild.h"
#include "Spell.h"

class npc_guild_vendor : public CreatureScript
{
public:
    npc_guild_vendor() : CreatureScript("npc_guild_vendor") { }

    bool OnGossipHello(Player *player, Creature *_creature)
    {
        if (!player || !_creature)
            return true;

        if (Guild* guild = player->GetGuild())
        {
            if (guild->HasLevelForBonus(GUILD_BONUS_VAULT))
                player->ADD_GOSSIP_ITEM(5, "Dostat item Mobile Guild Vault.", GOSSIP_SENDER_MAIN, 1);
            if (guild->HasLevelForBonus(GUILD_BONUS_MOUNT_GRFLY))
            {
                //player->ADD_GOSSIP_ITEM(5, "Naucit se Ground Mounta.", GOSSIP_SENDER_MAIN, 2);
                //player->ADD_GOSSIP_ITEM(5, "Naucit se Fly Mounta.", GOSSIP_SENDER_MAIN, 3);
            }
            if (guild->HasLevelForBonus(GUILD_BONUS_MOUNT_GROUND_FLY))
               //player->ADD_GOSSIP_ITEM(5, "Naucit se Ground/Fly Mounta.", GOSSIP_SENDER_MAIN, 4);
            if (!guild->HasLevelForBonus(GUILD_BONUS_VAULT) && !guild->HasLevelForBonus(GUILD_BONUS_MOUNT_GRFLY) && !guild->HasLevelForBonus(GUILD_BONUS_MOUNT_GROUND_FLY))
            {
                player->ADD_GOSSIP_ITEM(5, "Guilda nema dostatecny level.", GOSSIP_SENDER_MAIN, 5);
            }
            player->ADD_GOSSIP_ITEM(5, "Zavrit.", GOSSIP_SENDER_MAIN, 5);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
            return true;
        } 
        else
            player->ADD_GOSSIP_ITEM(5, "Nejsem v Guilde.", GOSSIP_SENDER_MAIN, 5);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
            return true;
    }

    bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch (uiAction)
            {
            case 1: // Guild Vault
                player->CLOSE_GOSSIP_MENU();
                if (player->HasItemCount(12323, 1, true))
                    _creature->MonsterWhisper("Tento Item jiz mas.", player, true);
                else
                {
                    player->AddItem(12323, 1);
                    _creature->MonsterWhisper("Dostal jsi Guild Vault", player, true);
                }
                break;

            case 2: // Ground Mount
                player->CLOSE_GOSSIP_MENU();
                if (!player->HasSpell(16059))
                {
                    player->learnSpell(16059, false);
                    _creature->MonsterWhisper("Naucil jsi se Ground mounta.", player, true);
                }
                else
                    _creature->MonsterWhisper("Tohoto mounta jiz umis.", player, true);
                break;

            case 3: // Fly Mount
                player->CLOSE_GOSSIP_MENU();
                if (!player->HasSpell(16060))
                {
                    player->learnSpell(16060, false);
                    _creature->MonsterWhisper("Naucil jsi se Fly mounta.", player, true);
                }
                else
                    _creature->MonsterWhisper("Tohoto mounta jiz umis.", player, true);
                break;

            case 4: // Ground/Fly Mount
                player->CLOSE_GOSSIP_MENU();
                if (!player->HasSpell(31700))
                {
                    player->learnSpell(31700, false);
                    _creature->MonsterWhisper("Naucil jsi se Ground/Fly mounta.", player, true);
                }
                else
                    _creature->MonsterWhisper("Tohoto mounta jiz umis.", player, true);
                break;

            case 5: // Zavrit
                player->CLOSE_GOSSIP_MENU();
                return true;

            default:
                break;
            }
        }
        return true;
    }
};

void AddSC_npc_guild_vendor()
{
    new npc_guild_vendor();
}
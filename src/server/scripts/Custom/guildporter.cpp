#include "ScriptPCH.h"

extern WorldDatabaseWorkerPool WorldDatabase;
#define MSG_INCOMBAT             "Mas combat, nelze te teleportovat do GuildHouse."
#define MSG_NOGUILDHOUSE         "Tva guilda uz nevlastni GuildHouse."
#define MSG_GOSSIP_TELE          "Teleportovat do GuildHouse"
#define MSG_NOTINGUILD           "Musis mit guildu, pokud se chces teleportovat do GuildHouse."
#define MSG_GOSSIP_GUILDHOUSE    "Ziskat GuildHouse"
#define MSG_GUILD                "Pokud si chces poridit Guildhouse, kontaktuj GM"
#define ICON_GOSSIP_BALOON 0
#define ACTION_TELE 1001
#define ACTION_HOUSE 1002

class guildporter : public CreatureScript
{
public:
    guildporter() : CreatureScript("guildporter") { } 

    bool isPlayerGuildLeader(Player *player)
    {
        return (player->GetRank() == 0) && (player->GetGuildId() != 0);
    }

    bool getGuildHouseCoords(uint32 guildId, float &x, float &y, float &z, uint32 &map)
    {
        if (guildId == 0)
        {
            //if player has no guild
            return false;
        }

        QueryResult result;
        result = WorldDatabase.PQuery("SELECT `x`, `y`, `z`, `map` FROM `guildhouses` WHERE `guildId` = %u", guildId);
        if (result)
        {
            Field *fields = result->Fetch();
            x = fields[0].GetFloat();
            y = fields[1].GetFloat();
            z = fields[2].GetFloat();
            map = fields[3].GetUInt32();
            return true;
        }

        return false;
    }

    void teleportPlayerToGuildHouse(Player *player, Creature *_creature)
    {
        if (player->GetGuildId() == 0)
        {
            //if player has no guild
            _creature->MonsterWhisper(MSG_NOTINGUILD, player, true);
            return;
        }

        if (!player->getAttackers().empty())
        {
            //if player in combat
            _creature->MonsterWhisper(MSG_INCOMBAT, player, true);
            return;
        }

        float x, y, z;
        uint32 map;

        if (getGuildHouseCoords(player->GetGuildId(), x, y, z, map))
        {
            //teleport player to the specified location
            player->TeleportTo(map, x, y, z, 0.0f);
        }
        else
            _creature->MonsterWhisper(MSG_NOGUILDHOUSE, player, true);
    }

    bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (sender != GOSSIP_SENDER_MAIN)
            return false;

        switch (action)
        {
        case ACTION_TELE:
            //teleport player to GH
            player->CLOSE_GOSSIP_MENU();
            teleportPlayerToGuildHouse(player, _creature);
            break;

        case ACTION_HOUSE:
            player->CLOSE_GOSSIP_MENU();
            _creature->MonsterWhisper(MSG_GUILD, player, true);
            break;
        }
        return true;
    }

    bool OnGossipHello(Player *player, Creature *_creature)
    {
        if (!player)
            return true;

        player->ADD_GOSSIP_ITEM(ICON_GOSSIP_BALOON, MSG_GOSSIP_TELE, GOSSIP_SENDER_MAIN, ACTION_TELE);      
        player->ADD_GOSSIP_ITEM(ICON_GOSSIP_BALOON, MSG_GOSSIP_GUILDHOUSE, GOSSIP_SENDER_MAIN, ACTION_HOUSE);  
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
        return true;
    }
};
void AddSC_guildporter()
{
    new guildporter();
}
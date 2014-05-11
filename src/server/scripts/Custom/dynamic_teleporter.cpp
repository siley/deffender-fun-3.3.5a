/*******************************************************
 * File:'dynamic_teleporter.cpp'
 * ScriptName:'npc_dynamic_teleporter'
 * (c)2011 - Wolf Officious
 *******************************************************/

/* -- NPC SQL EXAMPLE
REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`)
VALUES('700020','0','0','0','0','0','736','0','0','0','Dynamic Teleporter','TEST','','0','80','80','1','35','35','1','1','1.14286','2','0','5000','5000','0','35000','10','1','0','1','512','0','0','0','0','0','0','10000','10000','68','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','20','20','20','0','0','0','0','0','0','0','0','255','0','0','0','npc_dynamic_teleporter','0');
*/

#include "ScriptPCH.h"
#include "DynamicTeleportMgr.h"

class npc_dynamic_teleporter : public CreatureScript
{
private:

    // COMBAT CHECKER
    inline
    bool IsInCombat(Player *player)
    {
        if(player->IsInCombat())
        {
            player->GetSession()->SendNotification("You are in combat!");
            return true;
        }
        return false;
    }

    // SHOW MENU BY ID
    inline
    void ShowMenu(Player *player, Creature *_Creature, uint32 menu_id)
    {
        if(!sDynamicTeleportMgr->isLoaded())
        {
            player->CLOSE_GOSSIP_MENU();
            return;
        }

        uint32 count = 0;
        uint8  send_counter = 0;

        if(player->IsGameMaster() && menu_id == 0)
        {
            ++count;
            player->ADD_GOSSIP_ITEM(5, "~RELOAD TELEPORTER DATA~\n", GOSSIP_SENDER_MAIN, 666);
        }

        for(uint32 itr = 0; itr < sDynamicTeleportMgr->GetCount(); itr++)
        {
            TeleportData const* td;
            td = sDynamicTeleportMgr->GetTeleportData(itr);

            if(td)
            {
                if(td->menu_parent == menu_id)
                {
                    if(td->faction == 0 || player->GetTeam() == td->faction) // HORDE 67, ALLIANCE 469
                    {
                        uint8 icon_id = td->icon;

                        if(icon_id > 9)
                        {
                            icon_id = 0;
                        }

                        player->ADD_GOSSIP_ITEM(icon_id, td->name.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + td->entry);

                        ++count;
                        ++send_counter;

                        if(send_counter >= 10)
                        {
                            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
                            send_counter = 0;
                        }
                    }
                }
            }
            else
            {
                TC_LOG_INFO("LOG_FILTER_GENERAL", "TD_ERROR: UNK1 (!td)");
                return;
            }
        }

        if(send_counter != 0 || count == 0)
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
    }

    // TELEPORT PROCESS
    inline
    void TeleportToTarget(Player *player, uint32 target_id)
    {
        if(!sDynamicTeleportMgr->isLoaded())
        {
            player->CLOSE_GOSSIP_MENU();
            return;
        }

        TeleportLoc const* tl;
        tl = sDynamicTeleportMgr->GetTeleportLoc(target_id);

        if(tl)
        {
            player->TeleportTo(tl->map, tl->position_x, tl->position_y, tl->position_z, tl->position_o);
        }
        else
        {
            TC_LOG_INFO("LOG_FILTER_GENERAL", "TD_ERROR: UNK1 (!tl)");
        }

        return;
    }

    // ACTION TYPE HANDLER
    inline
    bool HandleMenuAction(Player *player, Creature *_Creature, uint32 action)
    {
        if(!sDynamicTeleportMgr->isLoaded())
            return false;

        for(uint32 itr = 0; itr < sDynamicTeleportMgr->GetCount(); itr++)
        {
            TeleportData const* td;
            td = sDynamicTeleportMgr->GetTeleportData(itr);

            if(td)
            {
                if(td->entry == action - GOSSIP_ACTION_INFO_DEF)
                {
                    if(td->menu_sub < 0)
                    {
                        TeleportToTarget(player, action - GOSSIP_ACTION_INFO_DEF);
                        return true;
                    }
                    else
                    {
                        ShowMenu(player, _Creature, td->menu_sub);
                        return true;
                    }
                }
            }
            else
            {
                TC_LOG_INFO("LOG_FILTER_GENERAL", "TD_ERROR: UNK1 (!td)");
                return false;
            }
        }

        return false;
    }

public:
    npc_dynamic_teleporter() : CreatureScript("npc_dynamic_teleporter") { }

    bool OnGossipHello(Player *player, Creature *_Creature)
    {
        if(IsInCombat(player) || !sDynamicTeleportMgr->isLoaded())
            return false;

        ShowMenu(player, _Creature, 0);

        return true;
    }

    bool OnGossipSelect(Player *player, Creature *_Creature, uint32 sender, uint32 action)
    {
        if(sender != GOSSIP_SENDER_MAIN || IsInCombat(player) || !sDynamicTeleportMgr->isLoaded())
        {
            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        player->PlayerTalkClass->ClearMenus();

        if(action == 666 && player->IsGameMaster())
        {
            player->CLOSE_GOSSIP_MENU();
            sDynamicTeleportMgr->Update();
            player->GetSession()->SendNotification("Reloaded..");
            return true;
        }

        if(!HandleMenuAction(player, _Creature, action))
        {
            player->CLOSE_GOSSIP_MENU();
        }

        return true;
    }
};

void AddSC_npc_dynamic_teleporter()
{
    new npc_dynamic_teleporter();
}

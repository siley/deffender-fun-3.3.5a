/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "InstanceScript.h"
#include "Player.h"
#include "ulduar.h"

enum Teleporter
{
    ANTECHAMBER = 200,
};

class xt_teleporter : public GameObjectScript
{
    public:
        xt_teleporter() : GameObjectScript("xt_teleporter") { }

        bool OnGossipSelect(Player* player, GameObject* /*gameObject*/, uint32 sender, uint32 action) override
        {
            player->PlayerTalkClass->ClearMenus();
            if (sender != GOSSIP_SENDER_MAIN)
                return false;
            if (!player->getAttackers().empty())
                return false;

            switch (action)
            {
                case ANTECHAMBER:
                    player->TeleportTo(603, 1498.09f, -24.246f, 420.967f, 0.0f);
                    player->CLOSE_GOSSIP_MENU();
                    break;
            }

            return true;
        }

        bool OnGossipHello(Player* player, GameObject* gameObject) override
        {      
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport to the Antechamber of Ulduar", GOSSIP_SENDER_MAIN, ANTECHAMBER); 

            player->SEND_GOSSIP_MENU(gameObject->GetGOInfo()->GetGossipMenuId(), gameObject->GetGUID());
            return true;
        }
};

void AddSC_xt_teleporter()
{
    new xt_teleporter();
}

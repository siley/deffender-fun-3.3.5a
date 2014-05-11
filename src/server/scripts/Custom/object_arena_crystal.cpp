#include "ScriptPCH.h"
#include "Battleground.h"
#include "BattlegroundMgr.h"
#include "ArenaTeam.h"
#include "Chat.h"
#include "Log.h"

class object_arena_crystal : public GameObjectScript
{
public:
    object_arena_crystal() : GameObjectScript("object_arena_crystal") { }

    bool OnGossipHello(Player* player, GameObject* /*pGO*/)
    {
        

        if (player->HasAura(32727))
        {
            player->m_clicked = true;

            Battleground* bg = player->GetBattleground();
            Battleground* battleground = player->GetBattleground();
            uint8 numOfReadyPlrs = 0;

            for (Battleground::BattlegroundPlayerMap::const_iterator itr = battleground->GetPlayers().begin(); itr != battleground->GetPlayers().end(); ++itr)
            {
                if (Player *plr = sObjectAccessor->FindPlayer(itr->first))
                {
                    if (plr->m_clicked == true)
                        ++numOfReadyPlrs;
                }
            }

            // 0 by se nemela vypsat nikdy, ale co uz...
            if (numOfReadyPlrs == 0 && battleground->GetArenaType() == 2)
                ChatHandler(player->GetSession()).PSendSysMessage("Je pripraveno %u hracu ze %u potrebnych.", numOfReadyPlrs, battleground->GetArenaType()*2);
            // 2v2
            else if (numOfReadyPlrs == 1 && battleground->GetArenaType() == 2)
                ChatHandler(player->GetSession()).PSendSysMessage("Je pripraven %u hrac ze %u potrebnych.", numOfReadyPlrs, battleground->GetArenaType()*2);
            else if ((numOfReadyPlrs == 2 || numOfReadyPlrs == 3) && battleground->GetArenaType() == 2)
                ChatHandler(player->GetSession()).PSendSysMessage("Jsou pripraveni %u hraci ze %u potrebnych.", numOfReadyPlrs, battleground->GetArenaType()*2);
            else if (numOfReadyPlrs == 4 && battleground->GetArenaType() == 2)
                ChatHandler(player->GetSession()).PSendSysMessage("Jsou pripraveni vsichni hraci.", numOfReadyPlrs, battleground->GetArenaType()*2);
            // 3v3
            else if (numOfReadyPlrs == 0 && battleground->GetArenaType() == 3)
                ChatHandler(player->GetSession()).PSendSysMessage("Je pripraveno %u hracu z %u potrebnych.", numOfReadyPlrs, battleground->GetArenaType()*2);
            else if (numOfReadyPlrs == 1 && battleground->GetArenaType() == 3)
                ChatHandler(player->GetSession()).PSendSysMessage("Je pripraven %u hrac z %u potrebnych.", numOfReadyPlrs, battleground->GetArenaType()*2);
            else if ((numOfReadyPlrs == 2 || numOfReadyPlrs == 3 || numOfReadyPlrs == 4) && battleground->GetArenaType() == 3)
                ChatHandler(player->GetSession()).PSendSysMessage("Jsou pripraveni %u hraci z %u potrebnych.", numOfReadyPlrs, battleground->GetArenaType()*2);
            else if (numOfReadyPlrs == 5 && battleground->GetArenaType() == 3)
                ChatHandler(player->GetSession()).PSendSysMessage("Je pripraveno %u hracu z %u potrebnych.", numOfReadyPlrs, battleground->GetArenaType()*2);
            else if (numOfReadyPlrs == 6 && battleground->GetArenaType() == 3)
                ChatHandler(player->GetSession()).PSendSysMessage("Jsou pripraveni vsichni hraci.", numOfReadyPlrs, battleground->GetArenaType()*2);
            // Todle je pro 5v5 a a ja jsem linej vypisovat vsechny mozny kombinace. Pokud se nekomu chce, muze to doplnit, ale me to prijde zbytecny.
            else
                ChatHandler(player->GetSession()).PSendSysMessage("Je pripraveno %u hracu z %u potrebnych.", numOfReadyPlrs, battleground->GetArenaType()*2);

            if ((bg->GetStartDelayTime() - player->timeDiff) <= 15000)
            {
                player->GetSession()->SendAreaTriggerMessage("Arena za chvili zacina");
            }
            else
            {
                player->GetSession()->SendAreaTriggerMessage("Jste oznacen jako pripaven");
            }
        }
        return true;
    }
};

void AddSC_object_arena_crystal()
{
    new object_arena_crystal();
}
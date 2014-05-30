#include "ScriptPCH.h"
#include "../../scripts/Northrend/IcecrownCitadel/icecrown_citadel.h"
#include "Group.h"
#define GOSSIP 11203

class npc_icc_buff : public CreatureScript
{
public:
    npc_icc_buff() : CreatureScript("npc_icc_buff") {}

    struct npc_icc_buffAI : public ScriptedAI
    {
        npc_icc_buffAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

    private:
        InstanceScript* instance;
    };
        bool OnGossipHello(Player *player, Creature *npc)
        {
            InstanceScript* instance = npc->GetInstanceScript();

            if (player->IsInCombat())
            {
                player->CLOSE_GOSSIP_MENU();
                npc->MonsterWhisper("You are in combat!", player, true);
                return true;
            }

            if (instance->GetBossState(DATA_LORD_MARROWGAR) == DONE)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Lord Marrowgar is dead.", GOSSIP_SENDER_MAIN, 6);
                player->SEND_GOSSIP_MENU(GOSSIP, npc->GetGUID());
                return true;
            }

            if ((!player->GetGroup() || !player->GetGroup()->IsLeader(player->GetGUID())) && !player->IsGameMaster())
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'm not the raid leader...", GOSSIP_SENDER_MAIN, 6);
                player->SEND_GOSSIP_MENU(GOSSIP, npc->GetGUID());
                return true;
            }

            player->ADD_GOSSIP_ITEM(0, "Zrusit buff", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(0, "5% buff", GOSSIP_SENDER_MAIN, 2);
            player->ADD_GOSSIP_ITEM(0, "10% buff", GOSSIP_SENDER_MAIN, 3);
            player->ADD_GOSSIP_ITEM(0, "15% buff", GOSSIP_SENDER_MAIN, 4);
            player->ADD_GOSSIP_ITEM(0, "30% buff", GOSSIP_SENDER_MAIN, 5);
            player->ADD_GOSSIP_ITEM(0, "Close", GOSSIP_SENDER_MAIN, 6);
            player->SEND_GOSSIP_MENU(GOSSIP, npc->GetGUID());
            return true;
        }
        bool OnGossipSelect(Player *player, Creature *npc, uint32 sender, uint32 uiAction)
        {
            InstanceScript* instance = npc->GetInstanceScript();

            if (sender != GOSSIP_SENDER_MAIN)
            {
                player->CLOSE_GOSSIP_MENU();
                return true;
            }

            switch (uiAction)
            {
            case 1:
                {
                    instance->SetData(DATA_BUFF, 4);
                    instance->DoRemoveAurasDueToSpellOnPlayers(73828);
                    instance->DoRemoveAurasDueToSpellOnPlayers(73762);
                    instance->DoRemoveAurasDueToSpellOnPlayers(73824);
                    instance->DoRemoveAurasDueToSpellOnPlayers(73825);
                    player->CLOSE_GOSSIP_MENU();
                }
                break;
            case 2:
                instance->SetData(DATA_BUFF, 3);
                instance->DoCastSpellOnPlayers(73762);
                player->CLOSE_GOSSIP_MENU();
                break;
            case 3:
                instance->SetData(DATA_BUFF, 2);
                instance->DoCastSpellOnPlayers(73824);
                player->CLOSE_GOSSIP_MENU();
                break;
            case 4:
                instance->SetData(DATA_BUFF, 1);
                instance->DoCastSpellOnPlayers(73825);
                player->CLOSE_GOSSIP_MENU();
                break;
            case 5:
                instance->SetData(DATA_BUFF, 0);
                instance->DoCastSpellOnPlayers(73828);
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

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_icc_buffAI(creature);
    }
};

void AddSC_npc_icc_buff()
{
    new npc_icc_buff();
}
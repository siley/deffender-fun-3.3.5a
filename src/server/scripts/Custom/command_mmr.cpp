
#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "WorldPacket.h"
#include "Chat.h"
#include "Group.h"
#include <ArenaTeam.h>
#include <ArenaTeamMgr.h>

class command_mmr : public CommandScript
{
public:
    command_mmr() : CommandScript("command_mmr") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand commandTable[] =
        {
            { "mmr",            rbac::RBAC_PERM_COMMAND_U_MMR, false, &HandleMMRCommand, "", NULL },
            { NULL,             0,                  false, NULL,                              "", NULL }
        };
        return commandTable;
    }

    static bool HandleMMRCommand(ChatHandler* handler, const char* args)
        {
     
            Player* player = handler->GetSession()->GetPlayer();
                    uint64 playerGuid = player->GetGUID();
     
                    uint16 *MMR = new uint16[2];
                   
                    // I'm not really sure why, but I have to create 2 db statements (ugly code, I know..)
                    PreparedStatement* stmt_twos = CharacterDatabase.GetPreparedStatement(CHAR_SEL_MATCH_MAKER_RATING);
                    PreparedStatement* stmt_threes = CharacterDatabase.GetPreparedStatement(CHAR_SEL_MATCH_MAKER_RATING);
     
                    stmt_twos->setUInt32(0, GUID_LOPART(playerGuid));
                    stmt_twos->setUInt8(1, 0);
                    PreparedQueryResult result_twos = CharacterDatabase.Query(stmt_twos);
     
                    if (result_twos)
                            MMR[0] = (*result_twos)[0].GetUInt16();
                    else
                            MMR[0] = sWorld->getIntConfig(CONFIG_ARENA_START_MATCHMAKER_RATING);
     
                    stmt_threes->setUInt32(0, GUID_LOPART(playerGuid));
                    stmt_threes->setUInt8(1, 1);
                    PreparedQueryResult result_threes = CharacterDatabase.Query(stmt_threes);
     
                    if (result_threes)
                            MMR[1] = (*result_threes)[0].GetUInt16();
                    else
                            MMR[1] = sWorld->getIntConfig(CONFIG_ARENA_START_MATCHMAKER_RATING);
     
                    if (MMR[0] != 0)
                            handler->PSendSysMessage("Vase MMR v 2v2 je %u.", MMR[0]);
                    else
                            handler->PSendSysMessage("Neznama chyba.");
     
                    if (MMR[1] != 0)
                            handler->PSendSysMessage("Vase MMR v 3v3 je %u.", MMR[1]);
                    else
                            handler->PSendSysMessage("Neznama chyba.");
     
                    delete MMR;
     
            return true;
        }


};

void AddSC_command_mmr()
{
    new command_mmr();
}

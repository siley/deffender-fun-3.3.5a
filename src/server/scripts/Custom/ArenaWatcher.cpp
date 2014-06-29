/*######
## Arena Watcher
######*/

#include "Player.h"
#include "BattlegroundMgr.h"
#include "Battleground.h"
#include "ArenaTeamMgr.h"
#include "ArenaTeam.h"
#include "GroupMgr.h"
#include "WorldPacket.h"
#include "Chat.h"

enum WatcherData
{
    OPTION_2V2 = 800,
	OPTION_3V3 = 900,
	OPTION_CODE = 1000,
	OPTION_OFFSET = 1100
};

// Chtelo by to prepsat prototypy funkci do nejakeho headeru - vetsina z nich je znovupouzitelna
std::vector<Battleground*> ratedArenas;

bool IsArenaInProgress(Battleground* arena);

uint32 NejvetsiRating(Battleground* arena)
{
	if (!arena)
		return 0;

    uint32 firstTeamId = 0;
    uint32 secondTeamId = 0;

    for (Battleground::BattlegroundPlayerMap::const_iterator itr = arena->GetPlayers().begin(); itr != arena->GetPlayers().end(); ++itr)
    {
		if (Player* player = ObjectAccessor::FindPlayer(itr->first))
		{
			if (player->isSpectator())
				continue;
			if (player->IsGameMaster())
				continue;

			if (firstTeamId == 0)
			{
				firstTeamId = itr->second.Team;
			}
			if (firstTeamId != 0 && itr->second.Team != firstTeamId)
			{
				secondTeamId = itr->second.Team;
				break;
			}                               
		}
    }

    if (firstTeamId == 0 || secondTeamId == 0)
            return 0;

    uint32 nejvetsiRating = 0;

    nejvetsiRating = arena->GetArenaMatchmakerRating(firstTeamId);
    if (nejvetsiRating < arena->GetArenaMatchmakerRating(secondTeamId))
            nejvetsiRating = arena->GetArenaMatchmakerRating(secondTeamId);

    return nejvetsiRating;
}

void LoadRatedArenas()
{
	ratedArenas.clear();

	BattlegroundDataContainer bgs = sBattlegroundMgr->GetAllBattlegrounds();
	
	BattlegroundDataContainer::const_iterator bgdata_citer = bgs.begin();
	for (; bgdata_citer != bgs.end(); ++bgdata_citer)
	{
		// I need only RL || NA || BE arenas
		if (bgdata_citer->first != BATTLEGROUND_RL && bgdata_citer->first != BATTLEGROUND_NA &&
			bgdata_citer->first != BATTLEGROUND_BE && bgdata_citer->first != BATTLEGROUND_AA)
			continue;

		BattlegroundContainer::const_iterator citr = ++bgdata_citer->second.m_Battlegrounds.begin();
		for (; citr != bgdata_citer->second.m_Battlegrounds.end(); ++citr)
			if (Battleground* arena = citr->second)
				if (arena->isArena() && arena->isRated() && IsArenaInProgress(arena))
					ratedArenas.push_back(arena);
	}

	// If there are no arenas, there is no reason to sort it
	// Also if there is only 1 arena, it's pointless to calculate highest rated team
	if (ratedArenas.size() < 2)
		return;

	std::vector<Battleground*>::iterator itr = ratedArenas.begin();
	int count = 0;
	for (; itr != ratedArenas.end(); ++itr)
	{
		if (!(*itr))
		{
			count++;
			continue;
		}

		// I have no idea if this event could ever happen, but if it did, it would most likely
		// cause crash
		if (count >= ratedArenas.size())
			return;

		int size = ratedArenas.size();
		// Bubble sort, oh yeah, that's the stuff..	
		for (int i = count; i < size; i++)
		{
			if (Battleground* tmpBg = ratedArenas[i])
			{
				if (NejvetsiRating((*itr)) < NejvetsiRating(tmpBg))
				{
					Battleground* tmp = (*itr);
					(*itr) = ratedArenas[i];
					ratedArenas[i] = tmp;
				}
			}
		}
		count++;
	}
}

bool IsArenaInProgress(Battleground* arena)
{
	if ((arena->GetEvent() & BG_STARTING_EVENT_4) && (arena->GetStatus() != STATUS_WAIT_LEAVE))
		return true;
	return false;
}

uint16 GetSpecificArenasCount(ArenaType type)
{
	if (ratedArenas.empty())
		return 0;

	uint16 count = 0;

	for (std::vector<Battleground*>::const_iterator citr = ratedArenas.begin();
		 citr != ratedArenas.end(); ++citr)
		if (Battleground* arena = (*citr))
			if (IsArenaInProgress(arena) && arena->GetArenaType() == type)
				count++;

	return count;
}

Battleground* GetArenaByArenaTeamId(uint32 arenaTeamId)
{
	ArenaTeam* arenaTeam = sArenaTeamMgr->GetArenaTeamById(arenaTeamId);

	if (!arenaTeam)
		return NULL;

	std::list<ArenaTeamMember>::const_iterator citr = arenaTeam->m_membersBegin();
	for (; citr != arenaTeam->m_membersEnd(); ++citr)
		if (Player* plr = sObjectAccessor->FindPlayer(citr->Guid))
			if (Battleground* bg = plr->GetBattleground())
				if (bg->isArena())
					if (bg->isRated())
						return bg;

	return NULL;
}

uint32 GetMatchmakingRatingByPlrIGuid(uint64 playerGuid, uint8 slot)
{
	if (slot > 1)
		return 0;

	PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_MATCH_MAKER_RATING);
    stmt->setUInt32(0, GUID_LOPART(playerGuid));
    stmt->setUInt8(1, slot);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    uint32 matchMakerRating;
    if (result)
        matchMakerRating = (*result)[0].GetUInt32();
    else
        matchMakerRating = sWorld->getIntConfig(CONFIG_ARENA_START_MATCHMAKER_RATING);

	return matchMakerRating;
}

Player* GetSuitablePlayer(Battleground* arena)
{
	Player* player = NULL;

	std::map<uint64, BattlegroundPlayer>::const_iterator citr = arena->GetPlayers().begin();
	for (; citr != arena->GetPlayers().end(); ++citr)
	{
		if (Player* plr = sObjectAccessor->FindPlayer(citr->first))
		{
			/*if (plr->isSpectator())
				continue;*/
			if (plr->IsGameMaster())
				continue;

			player = plr;
			break;
		}
	}

	return player;
}

bool CanEnter(Player* player)
{
	if (!player)
		return false;

	if (player->GetPet())
    {
		ChatHandler(player->GetSession()).PSendSysMessage("Musite si schovat (dissmissnout) peta.");
			return false;
    }
    if (player->GetGuardianPet())
    {
		ChatHandler(player->GetSession()).PSendSysMessage("Musite si schovat (dissmissnout) peta.");
			return false;
    }
    if (player->IsMounted())
    {
		ChatHandler(player->GetSession()).PSendSysMessage("Musite sesednout z mounta.");
			return false;
    }
	
	if (player->InBattlegroundQueue())
	{
		ChatHandler(player->GetSession()).PSendSysMessage("Musite leavnout Battleground/Arena Queue");
			return false;
	}

	return true;
}

bool CanPortToTargetArena(Player* target, Player* player)
{
	if (!target || !player)
		return false;

	Battleground* arena = NULL;
	if (!(arena = target->GetBattleground()))
		return false;

	if (!IsArenaInProgress(arena))
	{
		ChatHandler(player->GetSession()).PSendSysMessage("Arena jeste nezacala nebo uz skoncila.");
		return false;
	}

	if (!target->IsInWorld())
    {
		ChatHandler(player->GetSession()).PSendSysMessage("Hrac se momentalne portuje. Zkuste to za chvili.");
        return false;
    }

    if (!target->InArena())
    {
		ChatHandler(player->GetSession()).PSendSysMessage("Hrac neni v arene.");
        return false;
    }

    if (target->IsGameMaster())
    {
		ChatHandler(player->GetSession()).PSendSysMessage("Hrac je Game Master (GM).");
        return false;
    }

	return true;
}

std::string GetClassNameById(uint8 id)
{
    std::string sClass = "";
    switch (id)
    {
        case CLASS_WARRIOR:         sClass = "Warr ";        break;
        case CLASS_PALADIN:         sClass = "Pala ";           break;
        case CLASS_HUNTER:          sClass = "Hunt ";           break;
        case CLASS_ROGUE:           sClass = "Rogue ";          break;
        case CLASS_PRIEST:          sClass = "Priest ";         break;
        case CLASS_DEATH_KNIGHT:    sClass = "DK ";             break;
        case CLASS_SHAMAN:          sClass = "Shama ";          break;
        case CLASS_MAGE:            sClass = "Mage ";           break;
        case CLASS_WARLOCK:         sClass = "Warlock ";        break;
        case CLASS_DRUID:           sClass = "Druid ";          break;
		default:					sClass = "";				break;
    }
    return sClass;
}

std::string GetGossipString(Battleground* arena)
{
	if (!arena)
		return " ";

	ArenaTeam* aTeamOne = NULL;
	ArenaTeam* aTeamTwo = NULL;

	uint32 firstTeamId = 0;
	uint32 secondTeamId = 0;

	uint32 bgTeamIdOne = 0;
	uint32 bgTeamIdTwo = 0;
	
	Battleground::BattlegroundPlayerMap::const_iterator citr = arena->GetPlayers().begin();
	for (; citr != arena->GetPlayers().end(); ++citr)
	{
		if (Player* plr = sObjectAccessor->FindPlayer(citr->first))
		{
			if (plr->isSpectator())
				continue;
			if (plr->IsGameMaster())
				continue;

			if (firstTeamId == 0)
			{
				firstTeamId = plr->GetArenaTeamId(0);
				bgTeamIdOne = citr->second.Team;
			}
			else if (plr->GetArenaTeamId(0) != firstTeamId)
			{
				secondTeamId = plr->GetArenaTeamId(0);
				bgTeamIdTwo = citr->second.Team;
				break;
			}
		}
	}

	aTeamOne = sArenaTeamMgr->GetArenaTeamById(firstTeamId);
	aTeamTwo = sArenaTeamMgr->GetArenaTeamById(secondTeamId);

	if (!(aTeamOne && aTeamTwo))
		return " ";

	if (arena->GetArenaType() == ARENA_TYPE_2v2)
	{
		std::string teamsMember[4];
		uint8 index1 = 0;
		uint8 index2 = 0;
		ArenaTeam::MemberList::const_iterator citr1 = aTeamOne->m_membersBegin();
		for (; citr1 != aTeamOne->m_membersEnd(); ++citr1)
		{
			if (Player* plr = sObjectAccessor->FindPlayer(citr1->Guid))
			{
				if (plr->isSpectator())
					continue;
				if (!plr->InArena())
					continue;

				if (index1 == 0)
				{
					teamsMember[0] += GetClassNameById(plr->getClass());
					index1++;
				}
				else
				{
					teamsMember[1] += GetClassNameById(plr->getClass());
					break;
				}
			}
		}

		ArenaTeam::MemberList::const_iterator citr2 = aTeamTwo->m_membersBegin();
		for (; citr2 != aTeamTwo->m_membersEnd(); ++citr2)
		{
			if (Player* plr = sObjectAccessor->FindPlayer(citr2->Guid))
			{
				if (plr->isSpectator())
					continue;
				if (!plr->InArena())
					continue;

				if (index2 == 0)
				{
					teamsMember[2] += GetClassNameById(plr->getClass());
					index2++;
				}
				else
				{
					teamsMember[3] += GetClassNameById(plr->getClass());
					break;
				}
			}
		}
		std::string data = teamsMember[0] + teamsMember[1] + " (";
        std::stringstream ss;
        ss << arena->GetArenaMatchmakerRating(bgTeamIdOne) << ") VS ";
        data += ss.str();
        data += teamsMember[2] + teamsMember[3];
                std::stringstream strstr;
                strstr << "(" << arena->GetArenaMatchmakerRating(bgTeamIdTwo) << ")";
                data += strstr.str();
        return data;
	}
	else if (arena->GetArenaType() == ARENA_TYPE_3v3)
	{
		std::string teamsMember[6];
		uint8 index1 = 0;
		uint8 index2 = 0;

		ArenaTeam::MemberList::const_iterator citr1 = aTeamOne->m_membersBegin();
		for (; citr1 != aTeamOne->m_membersEnd(); ++citr1)
		{
			if (Player* plr = sObjectAccessor->FindPlayer(citr1->Guid))
			{
				if (plr->isSpectator())
					continue;
				if (!plr->InArena())
					continue;

				if (index1 == 0)
				{
					teamsMember[0] += GetClassNameById(plr->getClass());
					index1++;
				}
				else if (index1 == 1)
				{
					teamsMember[1] += GetClassNameById(plr->getClass());
					index1++;
				}
				else
				{
					teamsMember[2] += GetClassNameById(plr->getClass());
					break;
				}
			}
		}

		ArenaTeam::MemberList::const_iterator citr2 = aTeamTwo->m_membersBegin();
		for (; citr2 != aTeamTwo->m_membersEnd(); ++citr2)
		{
			if (Player* plr = sObjectAccessor->FindPlayer(citr2->Guid))
			{
				if (plr->isSpectator())
					continue;
				if (!plr->InArena())
					continue;

				if (index2 == 0)
				{
					teamsMember[3] += GetClassNameById(plr->getClass());
					index2++;
				}
				else if (index2 == 1)
				{
					teamsMember[4] += GetClassNameById(plr->getClass());
					index2++;
				}
				else
				{
					teamsMember[5] += GetClassNameById(plr->getClass());
					break;
				}
			}
		}

		std::string data = teamsMember[0] + teamsMember[1] + teamsMember[2] + " (";
        std::stringstream ss;
        ss << arena->GetArenaMatchmakerRating(bgTeamIdOne) << ") VS ";
        data += ss.str();
        data += teamsMember[3] + teamsMember[4] + teamsMember[5];
                std::stringstream strstr;
                strstr << "(" << arena->GetArenaMatchmakerRating(bgTeamIdTwo) << ")";
                data += strstr.str();
        return data;
	}
	else
		return " ";
}

class npc_arena_watcher : public CreatureScript
{
public:
    npc_arena_watcher() : CreatureScript("npc_arena_watcher") {}
    
    bool OnGossipHello(Player* player, Creature* creature)
    {
		if(!player)
			return true;

		// Load and save all rated matches
		LoadRatedArenas();

		uint32 arenasQty[2] = {0, 0};
		arenasQty[0] = GetSpecificArenasCount(ARENA_TYPE_2v2);
		arenasQty[1] = GetSpecificArenasCount(ARENA_TYPE_3v3);

        std::stringstream gossip2;
        std::stringstream gossip3;
        gossip2 << "Sleduj 2v2 arenu. (" << arenasQty[0] << " aren v prubehu)";
        gossip3 << "Sleduj 3v3 arenu. (" << arenasQty[1] << " aren v prubehu)";

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, gossip2.str(), GOSSIP_SENDER_MAIN, OPTION_2V2);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, gossip3.str(), GOSSIP_SENDER_MAIN, OPTION_3V3);
        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Sleduj urciteho hrace.", GOSSIP_SENDER_MAIN, OPTION_CODE, "", 0, true);
        
        player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        if (action < GOSSIP_ACTION_INFO_DEF)
        {
			// 2v2
            if (action == OPTION_2V2)
			{
				if (GetSpecificArenasCount(ARENA_TYPE_2v2) == 0)
				{
					ChatHandler(player->GetSession()).PSendSysMessage("Zadne 2v2 areny prave neprobihaji.");
					player->PlayerTalkClass->ClearMenus();
					player->CLOSE_GOSSIP_MENU();
					return false;
				}
				else
				{
					std::vector<Battleground*>::const_iterator citr = ratedArenas.begin();
					for (; citr != ratedArenas.end(); ++citr)
					{
						if (Battleground* arena = (*citr))
						{
							// Better be safe than sorry
							if (!arena)
								continue;
							if (arena->GetArenaType() != ARENA_TYPE_2v2)
								continue;
							if (!IsArenaInProgress(arena))
								continue;

							uint32 suitableTeamId = 0;

							std::map<uint64, BattlegroundPlayer>::const_iterator citr1 = arena->GetPlayers().begin();
							for (; citr1 != arena->GetPlayers().end(); ++citr1)
							{
								if (Player* plr = sObjectAccessor->FindPlayer(citr1->first))
								{
									if (plr->isSpectator())
										continue;
									if (plr->IsGameMaster())
										continue;

									suitableTeamId = plr->GetArenaTeamId(0);
									break;
								}
							}

							if (!suitableTeamId)
								continue;

							std::string gossipItem = GetGossipString(arena);

							if (gossipItem.length() < 20)
								continue;

							player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, gossipItem, GOSSIP_SENDER_MAIN + 1, OPTION_OFFSET + suitableTeamId);
						}
					}
					player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetGUID());
				}
			}
			// 3v3
			else if (action == OPTION_3V3)
			{
				if (GetSpecificArenasCount(ARENA_TYPE_3v3) < 1)
				{
					ChatHandler(player->GetSession()).PSendSysMessage("Zadne 3v3 areny prave neprobihaji.");
					player->PlayerTalkClass->ClearMenus();
					player->CLOSE_GOSSIP_MENU();
					return false;
				}
				else
				{
					std::vector<Battleground*>::const_iterator citr = ratedArenas.begin();
					for (; citr != ratedArenas.end(); ++citr)
					{
						if (Battleground* arena = (*citr))
						{
							// Better be safe than sorry
							if (!arena)
								continue;
							if (arena->GetArenaType() != ARENA_TYPE_3v3)
								continue;
							if (!IsArenaInProgress(arena))
								continue;
							
							uint32 suitableTeamId = 0;

							std::map<uint64, BattlegroundPlayer>::const_iterator citr1 = arena->GetPlayers().begin();
							for (; citr1 != arena->GetPlayers().end(); ++citr1)
							{
								if (Player* plr = sObjectAccessor->FindPlayer(citr1->first))
								{
									if (plr->isSpectator())
										continue;
									if (plr->IsGameMaster())
										continue;

									suitableTeamId = plr->GetArenaTeamId(0);
									break;
								}
							}

							if (!suitableTeamId)
								continue;

							std::string gossipItem = GetGossipString(arena);

							if (gossipItem.length() < 25)
								continue;

							player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, gossipItem, GOSSIP_SENDER_MAIN + 1, OPTION_OFFSET + suitableTeamId);
						}
					}
					player->PlayerTalkClass->SendGossipMenu(player->GetGossipTextId(creature), creature->GetGUID());
				}
			}
			// Unknown error
			else
			{
				player->CLOSE_GOSSIP_MENU();
				return true;
			}
        }
        else
        {
            uint32 arenaTeamId = action - OPTION_OFFSET;

			Battleground* arenaChosen;
			// Unknown error
			if (!(arenaChosen = GetArenaByArenaTeamId(arenaTeamId)))
			{
				player->CLOSE_GOSSIP_MENU();
				return true;
			}

            if (!IsArenaInProgress(arenaChosen))
            {
				ChatHandler(player->GetSession()).PSendSysMessage("Arena prave skoncila.");
                player->PlayerTalkClass->ClearMenus();
                player->CLOSE_GOSSIP_MENU();
                return false;
            }

			if (!CanEnter(player))
			{
				player->CLOSE_GOSSIP_MENU();
				return true;
			}

			Player* suitablePlr = NULL;
			if (!(suitablePlr = GetSuitablePlayer(arenaChosen)))
			// Unknown error
			{
				player->CLOSE_GOSSIP_MENU();
				return true;
			}

            // OK. In the case of a selected arena, we teleport in the center of the arena.
            player->SetBattlegroundId(arenaChosen->GetInstanceID(), arenaChosen->GetTypeID());
            player->SetBattlegroundEntryPoint();
            float x, y, z;
            switch (arenaChosen->GetMapId())
            {
                case 617: x = 1299.046f;    y = 784.825f;     z = 9.338f;     break; // Dalaran Sewers
                case 618: x = 763.5f;       y = -284;         z = 28.276f;    break; // Ring of Valor
                case 572: x = 1285.810547f; y = 1667.896851f; z = 39.957642f; break; // Ruins of Lordearon
                case 562: x = 6238.930176f; y = 262.963470f;  z = 0.889519f;  break; // Blade's Edge Arena
                case 559: x = 4055.504395f; y = 2919.660645f; z = 13.611241f; break; // Nagrand Arena
            }

			//arenaChosen->AddSpectator(player->GetGUID());

            player->SetPhaseMask(suitablePlr->GetPhaseMask(), true);
            player->SetSpectate(true);
			arenaChosen->AddSpectator(player->GetGUID());
			// used to build that shit of a button under minimap
			WorldPacket data;
			BattlegroundQueueTypeId bgQueueTypeId = sBattlegroundMgr->BGQueueTypeId(arenaChosen->GetTypeID(), arenaChosen->GetArenaType());
			uint32 queueslot = suitablePlr->GetBattlegroundQueueIndex(bgQueueTypeId);
			sBattlegroundMgr->BuildBattlegroundStatusPacket(&data, arenaChosen, queueslot, STATUS_IN_PROGRESS, 0, arenaChosen->GetStartTime(), arenaChosen->GetArenaType(), player->GetTeam());
			player->GetSession()->SendPacket(&data);
            player->TeleportTo(arenaChosen->GetMapId(), x, y, z, player->GetOrientation(), TELE_TO_GM_MODE);
        }
        return true;
    }

    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction, const char* code)
    {
		if (!player || !code)
		{
			return true;
		}

        // Prevent future crash caused by too long code msg
        if (strlen(code) > 13)
        {
			ChatHandler(player->GetSession()).PSendSysMessage("Vami zadany hrac je offline nebo neexistuje.");
            return true;
        }

        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();
        if (uiSender == GOSSIP_SENDER_MAIN)
        {
            switch (uiAction)
            {
                case OPTION_CODE: // choosing a player
                    
					const char* plrName = code;
                                        
                    char playerName[50];
                    strcpy(playerName, plrName);
                                        
                    for (int i = 0; i < 13; i++)
                    {
                        if (playerName[i] == NULL)
							break;
                        if (i == 0 && playerName[i] > 96)
							playerName[0] -= 32;
						else if (playerName[i] < 97)
							playerName[i] += 32;
                    }

                    if (Player* target = sObjectAccessor->FindPlayerByName(playerName))
                    {
                        if (!CanPortToTargetArena(target, player))
							return true;
						if (!CanEnter(player))
							return true;

						Battleground* arenaChosen = NULL;
						if (!(arenaChosen = target->GetBattleground()))
						{
							ChatHandler(player->GetSession()).PSendSysMessage("Doslo k nezname chybe (target->GetBattleground() == NULL)");
							return true;
						}

                        player->SetBattlegroundId(arenaChosen->GetInstanceID(), arenaChosen->GetTypeID());
						player->SetBattlegroundEntryPoint();
						float x, y, z;
						switch (arenaChosen->GetMapId())
						{
							case 617: x = 1299.046f;    y = 784.825f;     z = 9.338f;     break; // Dalaran Sewers
							case 618: x = 763.5f;       y = -284;         z = 28.276f;    break; // Ring of Valor
							case 572: x = 1285.810547f; y = 1667.896851f; z = 39.957642f; break; // Ruins of Lordearon
							case 562: x = 6238.930176f; y = 262.963470f;  z = 0.889519f;  break; // Blade's Edge Arena
							case 559: x = 4055.504395f; y = 2919.660645f; z = 13.611241f; break; // Nagrand Arena
						}

						player->SetPhaseMask(target->GetPhaseMask(), true);
					    player->SetSpectate(true);
						arenaChosen->AddSpectator(player->GetGUID());
						player->TeleportTo(arenaChosen->GetMapId(), x, y, z, player->GetOrientation(), TELE_TO_GM_MODE);

                    }
					else
						ChatHandler(player->GetSession()).PSendSysMessage("Vami zadany hrac neni online nebo neexistuje");
                    return true;
            }
        }

        return false;
    }
};

class command_leave : public CommandScript
{
public:
    command_leave() : CommandScript("command_leave") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand commandTable[] =
        {
            { "leave",            rbac::RBAC_PERM_COMMAND_SPEC_LEAVE, false, &HandleLeaveCommand, "", NULL },
            { NULL,             0,                  false, NULL,                              "", NULL }
        };
        return commandTable;
    }

    static bool HandleLeaveCommand(ChatHandler* handler, const char* args)
    {
        if (Player* player = handler->GetSession()->GetPlayer())
        {
            if (!player->isSpectator())
            {
                handler->PSendSysMessage("Nejste spectator.");
                return true;
            }

            if (Battleground* arena = player->GetBattleground())
            {
				arena->RemoveSpectator(player->GetGUID());
                player->CancelSpectate();
                player->TeleportToBGEntryPoint();

                return true;
            }
            else
				return false;
        }
        else
			return false;
    }
};

void AddSC_ArenaWatcher()
{
    new npc_arena_watcher();
	new command_leave();
}

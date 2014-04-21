#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include "Group.h"
//#include "CustomFunctionsMgr.h"
#include "World.h"
#include "InstanceSaveMgr.h"

class command_chartrade : public CommandScript
{
public:
	command_chartrade() : CommandScript("command_chartrade") { } // chartrade  

	ChatCommand* GetCommands() const
	{
		static ChatCommand charCommandTable[] =
		{
			{ "start", SEC_PLAYER, false, &HandleStartCommand, "", NULL },
			{ "accept", SEC_PLAYER, false, &HandleAcceptCommand, "", NULL },
			{ "finish", SEC_PLAYER, false, &HandleFinishCommand, "", NULL },
			{ "close", SEC_PLAYER, false, &HandleCloseCommand, "", NULL },
			{ NULL, 0, false, NULL, "", NULL }
		};
		static ChatCommand commandTable[] =
		{
			{ "chartrade", SEC_PLAYER, true, NULL, "", charCommandTable },
			{ NULL, 0, false, NULL, "", NULL }
		};
		return commandTable;
	}


	static bool HandleStartCommand(ChatHandler* handler, const char* args)
	{

		Player* player = handler->GetSession()->GetPlayer();
		uint64 playerGuid = player->GetGUID();

		if (!player || !player->GetGroup())
		{
			handler->PSendSysMessage("Chartrade: ERR: NEMAS PARTU!");
			return true;
		}

		if ((player && player->getChartradePreAccept()) || (player && player->getChartradeStatus()) || (player && player->getChartradeID() != 0))
		{
			handler->PSendSysMessage("Chartrade: ERR: JIZ MAS AKTIVNI CHARTRADE. PRO UKONCENI STAVAJICIHO TRADE POUZIJ COMMAND .chartrade close");
			return true;
		}

		if (!player || !player->GetGroup() || player->GetGroup()->GetMembersCount() != 2)
		{
			handler->PSendSysMessage("Chartrade: ERR: SPATNY POCET CLENU V PARTE!");
			return true;
		}

		if (player && player->GetGroup() && player->GetGroup()->GetMembersCount() == 2)
		{
			for (GroupReference *itr = player->GetGroup()->GetFirstMember(); itr != NULL; itr = itr->next())
			{
				Player *member = itr->GetSource();
				if (!member || !member->GetSession())
					continue;

				if (member->GetGUID() == playerGuid)
					continue;

				player->setChartradeStatus(true);
				member->setChartradeStatus(true);
				player->setChartradeID(member->GetGUID());
				member->setChartradeID(playerGuid);
				player->setChartradePreAccept(true);
				ChatHandler(player->GetSession()).PSendSysMessage("Chartrade: Prave si zazadal hrace %s o vymenu postav a zaroven si oznacil sebe, ze s vymenou souhlasis. (Prozatim nedojde k vymene, ale pouze se spusti zacatek procesu)", member->GetName().c_str());
				ChatHandler(member->GetSession()).PSendSysMessage("Chartrade: Hrac %s te zada o vymenu postav. Pokud mas o vymenu zajem, tak pouzij prikaz .chartrade accept (Prozatim nedojde k vymene, ale pouze se spusti zacatek procesu)", player->GetName().c_str());
			}
		}
		else
		{
			handler->PSendSysMessage("Chartrade: ERR: CHYBA PARTY!");
			return true;
		}

		return true;
	}

	static bool HandleAcceptCommand(ChatHandler* handler, const char* args)
	{

		Player* player = handler->GetSession()->GetPlayer();
		uint64 playerGuid = player->GetGUID();

		if (!player || player->getChartradeID() == 0 || !player->getChartradeStatus())
		{
			handler->PSendSysMessage("Chartrade: ERR: NEMAS AKTIVNI CHARTRADE!");
			return true;
		}

		Player* _player = ObjectAccessor::FindPlayer(player->getChartradeID());

		if (!_player)
		{
			handler->PSendSysMessage("Chartrade: ERR: CHYBA CHAR NENALEZEN!");
			return true;
		}

		if (!_player || !_player->getChartradeStatus())
		{
			handler->PSendSysMessage("Chartrade: ERR: CHAR O KTERY MAS ZAJEM ZRUSIL TRADE, TAKZE JIZ NEMUZES VYMENOVAT!");

			player->setChartradeID(0);
			player->setChartradePreAccept(false);
			player->setChartradeStatus(false);
			player->setChartradePotvrzeni(false);
			handler->PSendSysMessage("Chartrade: Chartrade ukonceno.");
			return true;
		}

		if (!player || player->getChartradePreAccept())
		{
			handler->PSendSysMessage("Chartrade: ERR: JIZ SI CHARTRADE PRIJAL! POKUD HO PRIJALA I DRUHA STRANA, TAK SI NYNI MUZES PROHLEDNOUT INFORMACE O POSTAVE, O KTEROU MAS ZAJEM A TO COMMANDEM .chartrade info");
			return true;
		}

		player->setChartradePreAccept(true);

		if (player && player->getChartradePreAccept() && _player && _player->getChartradePreAccept())
		{
			handler->PSendSysMessage("Chartrade: Obe strany potvrdily trade. Nyni si muzete prohlednou informace o dane postave pomoci commandu .chartrade info nebo chartrade dokoncit pomoci commandu .chartrade finish");
			ChatHandler(_player->GetSession()).PSendSysMessage("Chartrade: Obe strany potvrdily trade. Nyni si muzete prohlednou informace o dane postave pomoci commandu .chartrade info nebo chartrade dokoncit pomoci commandu .chartrade finish");
			player->UnbindInstance(35, DUNGEON_DIFFICULTY_NORMAL);
			_player->UnbindInstance(35, DUNGEON_DIFFICULTY_NORMAL);
			player->AddAura(9454, player);
			_player->AddAura(9454, _player);
			player->TeleportTo(35, -96.780197f, 147.017014f, -40.375076f, 1.604990f);
			_player->TeleportTo(35, -94.966705f, 149.8600001f, -40.382870f, 2.965499f);
			player->SaveToDB();
			_player->SaveToDB();
			return true;
		}

		return true;
	}

	static bool HandleFinishCommand(ChatHandler* handler, const char* args)
	{
		Player* player = handler->GetSession()->GetPlayer();

		if (!player || player->getChartradeID() == 0 || !player->getChartradeStatus())
		{
			handler->PSendSysMessage("Chartrade: ERR: NEMAS AKTIVNI CHARTRADE!");
			return true;
		}

		Player* _player = ObjectAccessor::FindPlayer(player->getChartradeID());

		if (!_player)
		{
			handler->PSendSysMessage("Chartrade: ERR: CHYBA CHAR NENALEZEN!");
			return true;
		}

		if (!_player || !_player->getChartradeStatus())
		{
			handler->PSendSysMessage("Chartrade: ERR: CHAR O KTERY MAS ZAJEM ZRUSIL TRADE, TAKZE JIZ NEMUZES VYMENOVAT!");

			player->setChartradeID(0);
			player->setChartradePreAccept(false);
			player->setChartradeStatus(false);
			player->setChartradePotvrzeni(false);
			handler->PSendSysMessage("Chartrade: Chartrade ukonceno.");
			return true;
		}

		if (!player || player->getChartradePotvrzeni())
		{
			handler->PSendSysMessage("Chartrade: ERR: JIZ SI CHARTRADE DOKONCIL! NYNI POCKEJ, AZ JEJ DOKONCI DRUHA STRANA.");
			return true;
		}

		if (!player || !player->getChartradePreAccept() || !_player || !_player->getChartradePreAccept())
		{
			handler->PSendSysMessage("Chartrade: ERR: CHARTRADE NEBYLO SPUSTENO OBJEMI STRANAMI!");
			return true;
		}

		player->setChartradePotvrzeni(true);

		if (!player || !player->getChartradePotvrzeni() || !_player || !_player->getChartradePotvrzeni())
			handler->PSendSysMessage("Chartrade: Dokoncil si trade. Vymena bude provedena po ukonceni druhou stranou.");

		ChatHandler(_player->GetSession()).PSendSysMessage("Druha strana dokoncila trade. Po tvem commandu .chartrade finish bude vymena provedena.");

		if (player && player->getChartradePotvrzeni() && _player && _player->getChartradePotvrzeni())
		{
			uint32 acc = player->GetSession()->GetAccountId();
			uint64 guid = player->GetGUID();

			uint32 _acc = _player->GetSession()->GetAccountId();
			uint64 _guid = _player->GetGUID();

			CharacterDatabase.PExecute("UPDATE characters SET account = %u WHERE guid = %u", acc, _guid);
			CharacterDatabase.PExecute("UPDATE characters SET account = %u WHERE guid = %u", _acc, guid);

			player->GetSession()->KickPlayer();
			_player->GetSession()->KickPlayer();
			return true;
		}

		return true;
	}

	static bool HandleCloseCommand(ChatHandler* handler, const char* args)
	{

		Player* player = handler->GetSession()->GetPlayer();
		uint64 playerGuid = player->GetGUID();

		if (!player || player->getChartradeID() == 0 || !player->getChartradeStatus())
		{
			handler->PSendSysMessage("Chartrade: ERR: NEMAS AKTIVNI CHARTRADE!");
			return true;
		}

		if (player && player->HasAura(9454) && player->GetMapId() == 43)
		{
			player->TeleportTo(530, -1870.091675f, 5437.583984f, -7.768305f, 5.452976f); //shattrath
			player->RemoveAura(9454);
		}

		player->setChartradeID(0);
		player->setChartradePreAccept(false);
		player->setChartradeStatus(false);
		player->setChartradePotvrzeni(false);
		handler->PSendSysMessage("Chartrade: Chartrade ukonceno.");

		return true;
	}
};

void OnChartradeLogin(Player* player)
{
	if (player && player->GetMapId() == 43)
	{
		player->TeleportTo(530, -1870.091675f, 5437.583984f, -7.768305f, 5.452976f); //shattrath
		player->RemoveAura(9454);
	}
	return;
}

class chartrade_login : public PlayerScript
{
public:
	chartrade_login() : PlayerScript("chartrade_login") { }

	void OnLogin(Player* player)
	{
		if (player)
			OnChartradeLogin(player);
	}
};

void AddSC_command_chartrade()
{
	new command_chartrade();
	new chartrade_login();
}
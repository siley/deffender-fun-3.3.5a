/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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

/* ScriptData
Name: guild_commandscript
%Complete: 100
Comment: All guild related commands
Category: commandscripts
EndScriptData */

#include "Chat.h"
#include "Language.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "ObjectAccessor.h"
#include "ScriptMgr.h"

class guild_commandscript : public CommandScript
{
public:
    guild_commandscript() : CommandScript("guild_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand guildCommandTable[] =
        {
            { "create",   rbac::RBAC_PERM_COMMAND_GUILD_CREATE,    true, &HandleGuildCreateCommand,           "", NULL },
            { "delete",   rbac::RBAC_PERM_COMMAND_GUILD_DELETE,    true, &HandleGuildDeleteCommand,           "", NULL },
            { "invite",   rbac::RBAC_PERM_COMMAND_GUILD_INVITE,    true, &HandleGuildInviteCommand,           "", NULL },
            { "uninvite", rbac::RBAC_PERM_COMMAND_GUILD_UNINVITE,  true, &HandleGuildUninviteCommand,         "", NULL },
            { "rank",     rbac::RBAC_PERM_COMMAND_GUILD_RANK,      true, &HandleGuildRankCommand,             "", NULL },
            { "rename",   rbac::RBAC_PERM_COMMAND_GUILD_RENAME,    true, &HandleGuildRenameCommand,           "", NULL },
            { "info",     rbac::RBAC_PERM_COMMAND_GUILD_INFO,      true, &HandleGuildInfoCommand,             "", NULL },
            { "setlevel", rbac::RBAC_PERM_COMMAND_GUILD_SET_LEVEL, true, &HandleGuildSetLevelCommand,         "", NULL },
            { "givexp",   rbac::RBAC_PERM_COMMAND_GUILD_GIVE_XP,   true, &HandleGuildGiveXpCommand,           "", NULL },
            { NULL,       0,                               false, NULL,                                "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "guild", rbac::RBAC_PERM_COMMAND_GUILD,  true, NULL, "", guildCommandTable },
            { NULL,    0,                       false, NULL, "", NULL }
        };
        return commandTable;
    }

    /** \brief GM command level 3 - Create a guild.
     *
     * This command allows a GM (level 3) to create a guild.
     *
     * The "args" parameter contains the name of the guild leader
     * and then the name of the guild.
     *
     */
    static bool HandleGuildCreateCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        // if not guild name only (in "") then player name
        Player* target;
        if (!handler->extractPlayerTarget(*args != '"' ? (char*)args : NULL, &target))
            return false;

        char* tailStr = *args != '"' ? strtok(NULL, "") : (char*)args;
        if (!tailStr)
            return false;

        char* guildStr = handler->extractQuotedArg(tailStr);
        if (!guildStr)
            return false;

        std::string guildName = guildStr;

        if (target->GetGuildId())
        {
            handler->SendSysMessage(LANG_PLAYER_IN_GUILD);
            return true;
        }

        Guild* guild = new Guild;
        if (!guild->Create(target, guildName))
        {
            delete guild;
            handler->SendSysMessage(LANG_GUILD_NOT_CREATED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        sGuildMgr->AddGuild(guild);

        return true;
    }

    static bool HandleGuildDeleteCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char* guildStr = handler->extractQuotedArg((char*)args);
        if (!guildStr)
            return false;

        std::string guildName = guildStr;

        Guild* targetGuild = sGuildMgr->GetGuildByName(guildName);
        if (!targetGuild)
            return false;

        targetGuild->Disband();
        delete targetGuild;

        return true;
    }

    static bool HandleGuildInviteCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        // if not guild name only (in "") then player name
        uint64 targetGuid;
        if (!handler->extractPlayerTarget(*args != '"' ? (char*)args : NULL, NULL, &targetGuid))
            return false;

        char* tailStr = *args != '"' ? strtok(NULL, "") : (char*)args;
        if (!tailStr)
            return false;

        char* guildStr = handler->extractQuotedArg(tailStr);
        if (!guildStr)
            return false;

        std::string guildName = guildStr;
        Guild* targetGuild = sGuildMgr->GetGuildByName(guildName);
        if (!targetGuild)
            return false;

        // player's guild membership checked in AddMember before add
        return targetGuild->AddMember(targetGuid);
    }

    static bool HandleGuildUninviteCommand(ChatHandler* handler, char const* args)
    {
        Player* target;
        uint64 targetGuid;
        if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid))
            return false;

        uint32 guildId = target ? target->GetGuildId() : Player::GetGuildIdFromDB(targetGuid);
        if (!guildId)
            return false;

        Guild* targetGuild = sGuildMgr->GetGuildById(guildId);
        if (!targetGuild)
            return false;

        targetGuild->DeleteMember(targetGuid, false, true, true);
        return true;
    }

    static bool HandleGuildRankCommand(ChatHandler* handler, char const* args)
    {
        char* nameStr;
        char* rankStr;
        handler->extractOptFirstArg((char*)args, &nameStr, &rankStr);
        if (!rankStr)
            return false;

        Player* target;
        uint64 targetGuid;
        std::string target_name;
        if (!handler->extractPlayerTarget(nameStr, &target, &targetGuid, &target_name))
            return false;

        uint32 guildId = target ? target->GetGuildId() : Player::GetGuildIdFromDB(targetGuid);
        if (!guildId)
            return false;

        Guild* targetGuild = sGuildMgr->GetGuildById(guildId);
        if (!targetGuild)
            return false;

        uint8 newRank = uint8(atoi(rankStr));
        return targetGuild->ChangeMemberRank(targetGuid, newRank);
    }

    static bool HandleGuildRenameCommand(ChatHandler* handler, char const* _args)
    {
        if (!*_args)
            return false;

        char *args = (char *)_args;

        char const* oldGuildStr = handler->extractQuotedArg(args);
        if (!oldGuildStr)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        char const* newGuildStr = handler->extractQuotedArg(strtok(NULL, ""));
        if (!newGuildStr)
        {
            handler->SendSysMessage(LANG_INSERT_GUILD_NAME);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Guild* guild = sGuildMgr->GetGuildByName(oldGuildStr);
        if (!guild)
        {
            handler->PSendSysMessage(LANG_COMMAND_COULDNOTFIND, oldGuildStr);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (sGuildMgr->GetGuildByName(newGuildStr))
        {
            handler->PSendSysMessage(LANG_GUILD_RENAME_ALREADY_EXISTS, newGuildStr);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!guild->SetName(newGuildStr))
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage(LANG_GUILD_RENAME_DONE, oldGuildStr, newGuildStr);
        return true;
    }
    //Guild-Level-System
    static bool HandleGuildInfoCommand(ChatHandler* handler, char const* /*args*/)
    {
        Guild* guild = handler->GetSession()->GetPlayer()->GetGuild();

        if (guild)
        {
            handler->PSendSysMessage(LANG_GUILDINFO_LEVEL, guild->GetLevel());

            if (guild->GetLevel() >= GUILD_MAX_LEVEL)
                handler->PSendSysMessage(LANG_GUILDINFO_XP_INFO, 0, 0);
            else
                handler->PSendSysMessage(LANG_GUILDINFO_XP_INFO, guild->GetCurrentXP(), guild->GetXpForNextLevel());

            handler->PSendSysMessage("Active Bonus:");

            if (guild->GetLevel() > 0)
            {
                if (guild->HasLevelForBonus(GUILD_BONUS_GOLD_1) && !guild->HasLevelForBonus(GUILD_BONUS_GOLD_2))
                    handler->PSendSysMessage("Gold bonus [Rank 1]");
                if (guild->HasLevelForBonus(GUILD_BONUS_XP_1) && !guild->HasLevelForBonus(GUILD_BONUS_XP_2))
                    handler->PSendSysMessage("Bonus Experience [Rank 1]");
                if (guild->HasLevelForBonus(GUILD_BONUS_SCHNELLER_GEIST))
                    handler->PSendSysMessage("Faster Ghost");
                if (guild->HasLevelForBonus(GUILD_BONUS_REPERATUR_1) && !guild->HasLevelForBonus(GUILD_BONUS_REPERATUR_2) && !guild->HasLevelForBonus(GUILD_BONUS_REPERATUR_3))
                    handler->PSendSysMessage("Cheaper Repairs [Rank 1]");
                if (guild->HasLevelForBonus(GUILD_BONUS_GOLD_2))
                    handler->PSendSysMessage("Gold bonus [Rank 2]");
                if (guild->HasLevelForBonus(GUILD_BONUS_REITTEMPO_1) && !guild->HasLevelForBonus(GUILD_BONUS_REITTEMPO_2))
                    handler->PSendSysMessage("Mount Speed [Rank 1]");
                if (guild->HasLevelForBonus(GUILD_BONUS_RUF_1) && !guild->HasLevelForBonus(GUILD_BONUS_RUF_2))
                    handler->PSendSysMessage("Reputation [Rank 1]");
                if (guild->HasLevelForBonus(GUILD_BONUS_XP_2))
                    handler->PSendSysMessage("Bonus Experience [Rank 2]");
                if (guild->HasLevelForBonus(GUILD_BONUS_REPERATUR_2) && !guild->HasLevelForBonus(GUILD_BONUS_REPERATUR_3))
                    handler->PSendSysMessage("Cheaper Repairs [Rank 2]");
                if (guild->HasLevelForBonus(GUILD_BONUS_REPERATUR_3))
                    handler->PSendSysMessage("Cheaper Repairs [Rank 3]");
                if (guild->HasLevelForBonus(GUILD_BONUS_REITTEMPO_2))
                    handler->PSendSysMessage("Mount Speed [Rank 2]");
                if (guild->HasLevelForBonus(GUILD_BONUS_RUF_2))
                    handler->PSendSysMessage("Reputation [Rank 2]");
                if (guild->HasLevelForBonus(GUILD_BONUS_EHRE_1) && !guild->HasLevelForBonus(GUILD_BONUS_EHRE_2))
                    handler->PSendSysMessage("Bonus Honor [Rank 1]");
                if (guild->HasLevelForBonus(GUILD_BONUS_EHRE_2))
                    handler->PSendSysMessage("Bonus Honor [Rank 2]");
                if (guild->HasLevelForBonus(GUILD_BONUS_MAIL_1) && !guild->HasLevelForBonus(GUILD_BONUS_MAIL_2))
                    handler->PSendSysMessage("Bonus Mail [Rank 1]");
                if (guild->HasLevelForBonus(GUILD_BONUS_MAIL_2))
                    handler->PSendSysMessage("Bonus Mail [Rank 2]");
                if (guild->HasLevelForBonus(GUILD_BONUS_DURATION))
                    handler->PSendSysMessage("Flask duration");
                if (guild->HasLevelForBonus(GUILD_BONUS_VAULT))
                    handler->PSendSysMessage("Mobile Guild Vault");
                if (guild->HasLevelForBonus(GUILD_BONUS_MOUNT_GRFLY))
                    handler->PSendSysMessage("Ground and Fly Mount");
                if (guild->HasLevelForBonus(GUILD_BONUS_MOUNT_GROUND_FLY))
                    handler->PSendSysMessage("Ground/Fly mount");
            }
            else
                handler->PSendSysMessage("None");

            return true;
        }
        else
        {
            handler->PSendSysMessage("You are not in a guild");
            return false;
        }
    }

    static bool HandleGuildSetLevelCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char* guildNameStr;
        char* levelStr;
        handler->extractOptFirstArg((char*)args, &guildNameStr, &levelStr);

        if (!levelStr)
            return false;

        uint8 newLevel = uint8(atoi(levelStr));
        Guild* guild = sGuildMgr->GetGuildByName(guildNameStr);

        if (guild)
        {
            if (newLevel > GUILD_MAX_LEVEL)
            {
                handler->PSendSysMessage("Your guild is max level");
                return false;
            }
            else
                guild->SetLevel(newLevel, true);
        }
        else
        {
            handler->PSendSysMessage("There is no guild named [%s] found.", guildNameStr);
            return false;
        }

        return true;
    }

    static bool HandleGuildGiveXpCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char* guildNameStr;
        char* xpStr;
        handler->extractOptFirstArg((char*)args, &guildNameStr, &xpStr);

        if (!xpStr)
            return false;

        uint32 value = uint32(atoi(xpStr));

        Guild* guild = sGuildMgr->GetGuildByName(guildNameStr);

        if (guild)
            guild->GiveXp(value);
        else
        {
            handler->PSendSysMessage("There was no guild with the name [%s] found.", guildNameStr);
            return false;
        }

        return true;
    }
};

void AddSC_guild_commandscript()
{
    new guild_commandscript();
}

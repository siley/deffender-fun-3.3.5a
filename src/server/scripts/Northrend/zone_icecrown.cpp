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
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "SpellAuras.h"
#include "Player.h"
#include "TemporarySummon.h"
#include "CombatAI.h"
#include "CreatureAI.h"
#include "CreatureTextMgr.h"

/*######
## npc_squire_david
######*/

enum SquireDavid
{
    QUEST_THE_ASPIRANT_S_CHALLENGE_H                    = 13680,
    QUEST_THE_ASPIRANT_S_CHALLENGE_A                    = 13679,

    SPELL_SUMMON_ARGENT_VALIANT                         = 63028,

    GOSSIP_TEXTID_SQUIRE                                = 14407,
    GOSSIP_TEXTID_SQUIRE_DAVID_2                        = 14476
};

#define GOSSIP_SQUIRE_ITEM_1 "I am ready to fight!"
#define GOSSIP_SQUIRE_ITEM_2 "How do the Argent Crusader raiders fight?"

class npc_squire_david : public CreatureScript
{
public:
    npc_squire_david() : CreatureScript("npc_squire_david") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (player->GetQuestStatus(QUEST_THE_ASPIRANT_S_CHALLENGE_H) == QUEST_STATUS_INCOMPLETE ||
            player->GetQuestStatus(QUEST_THE_ASPIRANT_S_CHALLENGE_A) == QUEST_STATUS_INCOMPLETE)//We need more info about it.
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUIRE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUIRE_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
        }

        player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SQUIRE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF+1)
        {
            player->CLOSE_GOSSIP_MENU();
            creature->CastSpell(player, SPELL_SUMMON_ARGENT_VALIANT, true);
        }
        else
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUIRE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SQUIRE_DAVID_2, creature->GetGUID());
        }
        return true;
    }
};

/*######
## npc_squire_danny
######*/

enum eSquireDanny
{
    QUEST_THE_VALIANT_S_CHALLENGE_0 = 13699,
    QUEST_THE_VALIANT_S_CHALLENGE_1 = 13713,
    QUEST_THE_VALIANT_S_CHALLENGE_2 = 13723,
    QUEST_THE_VALIANT_S_CHALLENGE_3 = 13724,
    QUEST_THE_VALIANT_S_CHALLENGE_4 = 13725,
    QUEST_THE_VALIANT_S_CHALLENGE_5 = 13726,
    QUEST_THE_VALIANT_S_CHALLENGE_6 = 13727,
    QUEST_THE_VALIANT_S_CHALLENGE_7 = 13728,
    QUEST_THE_VALIANT_S_CHALLENGE_8 = 13729,
    QUEST_THE_VALIANT_S_CHALLENGE_9 = 13731,

    //NPC_ARGENT_CHAMPION = 33707,
    SPELL_SUMMON_ARGENT_CHAMPION    = 63172, // or 63171 ?

    GOSSIP_TEXTID_SQUIRE_DANNY = 14335
};

#define GOSSIP_SQUIRE_ITEM_1 "I am ready to fight!"

class npc_squire_danny : public CreatureScript
{
public:
    npc_squire_danny(): CreatureScript("npc_squire_danny"){}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_THE_VALIANT_S_CHALLENGE_0) == QUEST_STATUS_INCOMPLETE ||
        player->GetQuestStatus(QUEST_THE_VALIANT_S_CHALLENGE_1) == QUEST_STATUS_INCOMPLETE ||
        player->GetQuestStatus(QUEST_THE_VALIANT_S_CHALLENGE_2) == QUEST_STATUS_INCOMPLETE ||
        player->GetQuestStatus(QUEST_THE_VALIANT_S_CHALLENGE_3) == QUEST_STATUS_INCOMPLETE ||
        player->GetQuestStatus(QUEST_THE_VALIANT_S_CHALLENGE_4) == QUEST_STATUS_INCOMPLETE ||
        player->GetQuestStatus(QUEST_THE_VALIANT_S_CHALLENGE_5) == QUEST_STATUS_INCOMPLETE ||
        player->GetQuestStatus(QUEST_THE_VALIANT_S_CHALLENGE_6) == QUEST_STATUS_INCOMPLETE ||
        player->GetQuestStatus(QUEST_THE_VALIANT_S_CHALLENGE_7) == QUEST_STATUS_INCOMPLETE ||
        player->GetQuestStatus(QUEST_THE_VALIANT_S_CHALLENGE_8) == QUEST_STATUS_INCOMPLETE ||
        player->GetQuestStatus(QUEST_THE_VALIANT_S_CHALLENGE_9) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUIRE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        }

        player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SQUIRE_DANNY, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            player->CLOSE_GOSSIP_MENU();
            //creature->SummonCreature(NPC_ARGENT_CHAMPION, 8562.83691f, 1099.15393f, 556.787598f, 5.02655f); // TODO (Récupérer les coordonnées réelles)
            creature->CastSpell(player, SPELL_SUMMON_ARGENT_CHAMPION, true);
        }
        return true;
    }
};

//    Squire Cavin yells: <name> 
//    Squire Cavin says: Good luck, <name>.

/*######
## npc_squire_cavin
######*/

enum eSquireCavin
{
    QUEST_THE_BLACK_KNIGHT_FALL = 13664,

    NPC_BLACK_KNIGHT = 33785,
    SPELL_RIDING_ARGENT_CHARGER = 63663
};

#define GOSSIP_SQUIRE_C_ITEM_1 "Ask Cavian to summon the black knight"
#define SQUIRE_CAVIN_YELL "$N challenges the Black Knight to trial by combat!"
#define SQUIRE_CAVIN_SAY "Good luck, $N"

class npc_squire_cavin : public CreatureScript
{
public:
    npc_squire_cavin() : CreatureScript("npc_squire_cavin"){}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_THE_BLACK_KNIGHT_FALL) == QUEST_STATUS_INCOMPLETE && player->HasAura(SPELL_RIDING_ARGENT_CHARGER))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUIRE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
        {
            player->CLOSE_GOSSIP_MENU();
            if (Creature* knight = creature->SummonCreature(NPC_BLACK_KNIGHT, 8462.94f, 962.13f, 545.5f, 3.13f, TEMPSUMMON_DEAD_DESPAWN)) // TODO fix coordinates
                knight->Attack(player, true);
            creature->MonsterYell(SQUIRE_CAVIN_YELL, LANG_UNIVERSAL, NULL); //not blizzlike
            creature->MonsterSay(SQUIRE_CAVIN_SAY, LANG_UNIVERSAL, NULL); //not blizzlike
        }
        return true;
    }
};

/*######
# npc_argent_valiant
#####*/
enum ArgentValiantChampion
{
    SPELL_CHARGE                = 63010,
    SPELL_SHIELD_BREAKER        = 65147,
    SPELL_DEFEND                = 62719,
    SPELL_THRUST                = 62544,
    YELLOW_ROSE_FIREWORK        = 11544,
    PLAYER_ON_TOURNAMENT_MOUNT  = 63034,
    SHIELD_LEVEL1               = 63130,
    SHIELD_LEVEL2               = 63131,
    SHIELD_LEVEL3               = 63132,
    SPELL_DEFEND_8_S            = 64220, // for valiant
    SPELL_DEFEND_6_S            = 64221, // for champion and commander
 
    NPC_ARGENT_VALIANT_CREDIT   = 24108,
    NPC_ARGENT_VALIANT          = 33448,
    SPELL_VALIANT_CREDIT        = 63049, // Kill Credit (38595)
    NPC_ARGENT_CHAMPION         = 33707,
    SPELL_CHAMPION_CREDIT       = 63516, // Kill Credit (33708)
    BESTED_ARGENT_CRUSADE       = 64892,

    NPC_DARNASSUS_VALIANT       = 33559,
    NPC_DARNASSUS_CHAMPION      = 33738,
    BESTED_DARNASSUS            = 64805,

    NPC_EXODAR_VALIANT          = 33562,
    NPC_EXODAR_CHAMPION         = 33739,
    BESTED_THE_EXODAR           = 64808,

    NPC_GNOMEREGAN_VALIANT      = 33558,
    NPC_GNOMEREGAN_CHAMPION     = 33740,
    BESTED_GNOMEREGAN           = 64809,

    NPC_IRONFORGE_VALIANT       = 33564,
    NPC_IRONFORGE_CHAMPION      = 33743,
    BESTED_IRONFORGE            = 64810,

    NPC_ORGRIMMAR_VALIANT       = 33306,
    NPC_ORGRIMMAR_CHAMPION      = 33744,
    BESTED_ORGRIMMAR            = 64811,

    NPC_SENJIN_VALIANT          = 33285,
    NPC_SENJIN_CHAMPION         = 33745,
    BESTED_SENJIN               = 64812,

    NPC_SILVERMOON_VALIANT      = 33382,
    NPC_SILVERMOON_CHAMPION     = 33746,
    BESTED_SILVERMOON_CITY      = 64813,

    NPC_STORMWIND_VALIANT       = 33561,
    NPC_STORMWIND_CHAMPION      = 33747,
    BESTED_STORMWIND            = 64814,

    NPC_UNDERCITY_VALIANT       = 33384,
    NPC_UNDERCITY_CHAMPION      = 33749,
    BESTED_THE_UNDERCITY        = 64816,

    NPC_THUNDER_BLUFF_VALIANT   = 33383,
    NPC_THUNDER_BLUFF_CHAMPION  = 33748,
    BESTED_THUNDER_BLUFF        = 64815,
};

/*######
## npc_argent_champion
######*/

class npc_argent_champion : public CreatureScript
{
public:
    npc_argent_champion(): CreatureScript("npc_argent_champion"){}

    struct npc_argent_championAI : public ScriptedAI
    {
        npc_argent_championAI(Creature* creature) : ScriptedAI(creature)
        {
            creature->Relocate(8562.83691f, 1099.15393f, 556.787598f, 5.02655f);
            creature->GetMotionMaster()->MovePoint(0, 8552.46973f, 1124.12878f, 556.7876f); // TODO (Trouver les coordonnées exactes)
            //creature->setFaction(35); //wrong faction in db?
        }
 
         void Reset()
         {
            me->CastSpell(me, SPELL_DEFEND, true);
            me->CastSpell(me, SPELL_DEFEND, true);
            me->CastSpell(me, SPELL_DEFEND, true);
            me->CastSpell(me, SPELL_DEFEND_6_S, true);
            Reset();
         }
 
        void KilledUnit(Unit* victim)
         {
         //   me->AI()->Talk(NPC_ARGENT_CHAMPION_TEXT_SAY_LOOSE, me);
            KilledUnit(victim);
         }
 
        void EnterCombat(Unit* /*who*/)
         {
         //   me->AI()->Talk(NPC_ARGENT_CHAMPION_TEXT_SAY_START, me);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_argent_championAI(creature);
    }
};

/*######
## npc_valiant
######*/

#define GOSSIP_VALIANT_1    "I am ready to fight."
//#define GOSSIP_VALIANT_GOSS "Are you sure you ready to fight a champion?"
#define SAY_START_1         "On your guard!"
#define SAY_START_2         "Prepare yourself!"
#define SAY_END             "I have been defeated. Good Fight !"

enum ValiantQuest
{
    QUEST_AMONG_THECHAMPIONS_A      = 13790,
    QUEST_AMONG_THECHAMPIONS_H      = 13811,
    QUEST_AMONG_THECHAMPIONS_A2     = 13793,
    QUEST_AMONG_THECHAMPIONS_H2     = 13814,
    MOUNTED_MELEE_VICTORY           = 63596
};

class npc_faction_champion : public CreatureScript
{
public:
    npc_faction_champion() : CreatureScript("npc_faction_champion") { }

    struct npc_faction_championAI : public ScriptedAI
    {
        npc_faction_championAI(Creature* creature) : ScriptedAI(creature) {}

        void PlayerWon(Unit* target)
        {
            me->MonsterSay(SAY_END, LANG_UNIVERSAL, 0);
            target->CastSpell(target, MOUNTED_MELEE_VICTORY, true);
            //DoScriptText(NPC_ARGENT_CHAMPION_TEXT_SAY_WIN, me);
            PlayerWon(target);
        }

        void KilledUnit(Unit* victim)
        {
            //DoScriptText(NPC_ARGENT_CHAMPION_TEXT_SAY_LOOSE, me);
            KilledUnit(victim);
        }

        void EnterCombat(Unit* /*who*/)
        {
            //DoScriptText(NPC_ARGENT_CHAMPION_TEXT_SAY_START, me);
        }
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (((player->GetQuestStatus(QUEST_AMONG_THECHAMPIONS_H) == QUEST_STATUS_INCOMPLETE)  ||
            (player->GetQuestStatus(QUEST_AMONG_THECHAMPIONS_H2) == QUEST_STATUS_INCOMPLETE) ||
            (player->GetQuestStatus(QUEST_AMONG_THECHAMPIONS_A) == QUEST_STATUS_INCOMPLETE)  ||
            (player->GetQuestStatus(QUEST_AMONG_THECHAMPIONS_A2) == QUEST_STATUS_INCOMPLETE)) &&
            (player->HasAura(PLAYER_ON_TOURNAMENT_MOUNT)) &&
            (!player->IsInCombat()))

        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VALIANT_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            player->CLOSE_GOSSIP_MENU();
            creature->setFaction(14);
            creature->SetReactState(REACT_AGGRESSIVE);
            creature->MonsterSay(urand(0,1) ? SAY_START_1 : SAY_START_2, LANG_UNIVERSAL, 0);
            creature->AI()->AttackStart(player);
            /*creature->AddThreat(player, 0.0f);
            creature->SetInCombatWith(player);
            player->SetInCombatWith(creature);*/
            //creature->GetMotionMaster()->MovePoint(0, 8552.46973f, 1124.12878f, 556.7876f); // TODO should be the middle of the ring

            creature->CastSpell(creature, SPELL_DEFEND, true);
            creature->CastSpell(creature, SPELL_DEFEND, true);
            creature->CastSpell(creature, SPELL_DEFEND, true);
            creature->CastSpell(creature, SPELL_DEFEND_6_S, true);
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_faction_championAI(creature);
    }
};

/*######
## The Grand Melee Quests
## 13665-13745-13750-13756-13761-13767-13772-13777-13782-13787
## http://www.wowhead.com/search?q=The+Grand+Melee SELECT entry,title FROM quest_template WHERE title LIKE 'The Grand Melee%'
######*/

enum FactionValiant
{
    QUEST_GRAND_MELEE_1                     = 13665,
    QUEST_GRAND_MELEE_2                     = 13745,
    QUEST_GRAND_MELEE_3                     = 13750,
    QUEST_GRAND_MELEE_4                     = 13756,
    QUEST_GRAND_MELEE_5                     = 13761,
    QUEST_GRAND_MELEE_6                     = 13767,
    QUEST_GRAND_MELEE_7                     = 13772,
    QUEST_GRAND_MELEE_8                     = 13777,
    QUEST_GRAND_MELEE_9                     = 13782,
    QUEST_GRAND_MELEE_10                    = 13787,
    MOUNTED_MELEE_VICTORY_GRAND             = 62724, // Crea item Credit.
};

#define GOSSIP_VALIANT_1_GRAND    "I am ready to fight."
#define SAY_START_1_GRAND         "On your guard!"
#define SAY_START_2_GRAND         "Prepare yourself!"
#define SAY_END_GRAND             "I have been defeated. Good Fight !"

class npc_faction_valiant : public CreatureScript
{
public:
    npc_faction_valiant() : CreatureScript("npc_faction_valiant") { }

    struct npc_faction_valiantAI : public ScriptedAI
    {
        npc_faction_valiantAI(Creature* creature) : ScriptedAI(creature) {}

        void PlayerWon(Unit* target)
        {
            me->MonsterSay(SAY_END_GRAND, LANG_UNIVERSAL, 0);
           target->CastSpell(target, MOUNTED_MELEE_VICTORY_GRAND, true);
            //DoScriptText(NPC_ARGENT_CHAMPION_TEXT_SAY_WIN, me);
            PlayerWon(target);
        }

        void KilledUnit(Unit* victim)
        {
            //DoScriptText(NPC_ARGENT_CHAMPION_TEXT_SAY_LOOSE, me);
            KilledUnit(victim);
        }

        void EnterCombat(Unit* /*who*/)
        {
            //DoScriptText(NPC_ARGENT_CHAMPION_TEXT_SAY_START, me);
        }
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (((player->GetQuestStatus(QUEST_GRAND_MELEE_1) == QUEST_STATUS_INCOMPLETE) ||
            (player->GetQuestStatus(QUEST_GRAND_MELEE_2) == QUEST_STATUS_INCOMPLETE)   ||
            (player->GetQuestStatus(QUEST_GRAND_MELEE_3) == QUEST_STATUS_INCOMPLETE)   ||
            (player->GetQuestStatus(QUEST_GRAND_MELEE_4) == QUEST_STATUS_INCOMPLETE)   ||
            (player->GetQuestStatus(QUEST_GRAND_MELEE_5) == QUEST_STATUS_INCOMPLETE)   ||
            (player->GetQuestStatus(QUEST_GRAND_MELEE_6) == QUEST_STATUS_INCOMPLETE)   ||
            (player->GetQuestStatus(QUEST_GRAND_MELEE_7) == QUEST_STATUS_INCOMPLETE)   ||
            (player->GetQuestStatus(QUEST_GRAND_MELEE_8) == QUEST_STATUS_INCOMPLETE)   ||
            (player->GetQuestStatus(QUEST_GRAND_MELEE_9) == QUEST_STATUS_INCOMPLETE)   ||
            (player->GetQuestStatus(QUEST_GRAND_MELEE_10) == QUEST_STATUS_INCOMPLETE)) &&
            (player->HasAura(PLAYER_ON_TOURNAMENT_MOUNT)) &&
            (!player->IsInCombat()))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VALIANT_1_GRAND, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }

        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            player->CLOSE_GOSSIP_MENU();
            creature->setFaction(14);
            creature->SetReactState(REACT_AGGRESSIVE);
            creature->MonsterSay(urand(0,1) ? SAY_START_1_GRAND : SAY_START_2_GRAND, LANG_UNIVERSAL, 0);
            creature->AI()->AttackStart(player);
            /*creature->AddThreat(player, 0.0f);
            creature->SetInCombatWith(player);
            player->SetInCombatWith(creature);*/
            //creature->GetMotionMaster()->MovePoint(0, 8552.46973f, 1124.12878f, 556.7876f); // TODO should be the middle of the ring

            creature->CastSpell(creature, SPELL_DEFEND, true);
            creature->CastSpell(creature, SPELL_DEFEND, true);
            creature->CastSpell(creature, SPELL_DEFEND_8_S, true);
        }
        return true;
    }

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_faction_valiantAI(creature);
    }
};

/*######
## npc_boneguard_commander
######*/
enum eBoneguardCommander
{
    SPELL_SCOURGE_BANNER_AURA = 60023
};
class npc_boneguard_commander : public CreatureScript
{
public:
    npc_boneguard_commander(): CreatureScript("npc_boneguard_commander"){}

    struct npc_boneguard_commanderAI : public ScriptedAI
    {
        npc_boneguard_commanderAI(Creature* creature) : ScriptedAI(creature)
        {
            uint32 uiChargeTimer;
            uint32 uiShieldBreakerTimer;

            uiChargeTimer = urand(0,3000);
            uiShieldBreakerTimer = urand(0,1500);
        }

        void Reset()
        {
            me->AddAura(SPELL_DEFEND_6_S, me);
            me->AddAura(SPELL_SCOURGE_BANNER_AURA, me);
            Reset();
        }

        void DamageTaken(Unit* /*pDoneBy*/, uint32& /*uiDamage*/) {}
        void MovementInform(uint32 /*uiType*/, uint32 /*uiId*/) {}
        void KilledUnit(Unit* /*victim*/) {}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_boneguard_commanderAI(creature);
    }
};

/*######
## npc_black_knight_argent 33785
######*/

//http://www.youtube.com/watch?v=Fshwn10mkv4
#define BK_SAY_AGGRO "Enough of this insolence! Prepare to die!"
#define BK_YELL_END_PH1 "Get off that horse and fight me man-to-man!"
#define BK_YELL_START_PH2 "I will not fail you, master!"


enum eBlackKnight
{
    SPELL_CHARGE_BKNIGHT = 63003,
    SPELL_DARK_SHIELD = 64505,
    SPELL_BLACK_KNIGHT_TRANSFORM = 64490,
    SPELL_BLACK_KNIGHT_TRANSFORM2 = 64498,
    MODELID_GRYPHON = 28652,
//[DND] Herald Face Black Knight 67482
};

class npc_black_knight_argent : public CreatureScript
{
public:
    npc_black_knight_argent(): CreatureScript("npc_black_knight_argent"){}

    struct npc_black_knight_argentAI : public ScriptedAI
    {
        npc_black_knight_argentAI(Creature* creature) : ScriptedAI(creature)
        {
            creature->GetMotionMaster()->MovePoint(0, 8426.77f, 961.49f, 544.675f); // TODO (Trouver les coordonnées exactes)
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        uint32 phase;
        uint32 uiRunAwayTimer;
        uint32 uiChargeTimer;
        uint32 uiShieldBreakerTimer;

        void Reset()
        {
            //me->CastSpell(me, SPELL_DEFEND, true);
            //me->CastSpell(me, SPELL_DEFEND, true);
            //me->CastSpell(me, SPELL_DEFEND, true);
            //me->CastSpell(me, SPELL_DEFEND_6_S, true);
            me->Mount(MODELID_GRYPHON);
            Reset();
        }

        /*        void DoMeleeAttackIfReady()
                {
                //Make sure our attack is ready and we aren't currently casting before checking distance
                if (me->isAttackReady())
                {
                //If we are within range melee the target
                if (me->IsWithinMeleeRange(me->getVictim()))
                {
                DoCastVictim(SPELL_THRUST);
                me->resetAttackTimer();
                }

                }
                }*/

        void AttackStart(Unit* victim)
        {
            if (victim && me->Attack(victim, true) && phase)
                me->GetMotionMaster()->MoveChase(victim);
        }

        void MovementInform(uint32 uiType, uint32 uiId)
        {
            if (uiType != POINT_MOTION_TYPE || uiId > 0)
                return;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->MonsterSay(BK_SAY_AGGRO, LANG_UNIVERSAL, 0);
            me->GetMotionMaster()->MoveChase(me->GetVictim());
            phase = 1;
        }

        void EnterEvadeMode()
        {
            me->DespawnOrUnsummon(5000);
            ScriptedAI::EnterEvadeMode();
        }

        void PreparePhaseTwo()
        {
            phase = 2;
            me->RemoveAllAuras();
            me->CastSpell(me, SPELL_DARK_SHIELD, true);
            me->CastSpell(me, SPELL_BLACK_KNIGHT_TRANSFORM, true);
            me->Dismount();
            me->GetMotionMaster()->MoveIdle();
            me->MonsterYell(BK_YELL_END_PH1, LANG_UNIVERSAL, 0);
            me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
        }

        void UpdateAI(uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;
            if (me->HasUnitState(UNIT_STATE_CASTING) || me->HasAura(SPELL_DARK_SHIELD))
                return;

            if (phase == 1)
            {
                if (me->GetHealthPct() <= 25.0f)
                {
                    PreparePhaseTwo();
                    return;
                }

                //me->IsInRange(target,5,40,false)
                if (uiShieldBreakerTimer <= uiDiff)
                {
                    DoCastVictim(SPELL_SHIELD_BREAKER);
                    uiShieldBreakerTimer = 1100;
                    return;
                }
                else uiShieldBreakerTimer -= uiDiff;

                if (uiChargeTimer <= uiDiff)
                {
                    if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == CHASE_MOTION_TYPE) // so he won't cast charge while running away
                    {
                        DoCastVictim(SPELL_CHARGE_BKNIGHT);
                        uiChargeTimer = 2500;
                        return;
                    }
                }
                else uiChargeTimer -= uiDiff;

                if (uiRunAwayTimer <= uiDiff)
                {
                    float x, y, z;
                    me->GetVictim()->GetRandomContactPoint(me, x, y, z, 10, 20);
                    me->GetMotionMaster()->MovePoint(1, x, y, z);
                    uiRunAwayTimer = 10000;
                    return;
                }
                else uiRunAwayTimer -= uiDiff;
            }
            else if (phase == 2)
            {
                phase = 3;
                me->CastSpell(me, SPELL_BLACK_KNIGHT_TRANSFORM2, true);
                me->MonsterYell(BK_YELL_START_PH2, LANG_UNIVERSAL, 0);
                if (Unit* newVictim = me->GetVictim()->GetCharmerOrOwnerOrSelf())
                {
                    if (newVictim->GetVehicle())
                        newVictim->GetVehicleBase()->Dismount();
                    newVictim->Dismount();
                    AttackStart(newVictim);
                }
                return;
            }
            if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE)
                me->GetMotionMaster()->MoveChase(me->GetVictim());

            DoMeleeAttackIfReady();
        }
    };

    protected:
        uint32 uiChargeTimer;
        uint32 uiShieldBreakerTimer;
        uint32 uiRunAwayTimer;
        uint8 phase;
 
     CreatureAI *GetAI(Creature* creature) const
     {
        return new npc_black_knight_argentAI(creature);
     };
};

/*######
## npc_vendor_argent_tournament
######*/
const uint32 ArgentTournamentVendor[10][4] =
{
    {33553, 13726, 2, 14460}, // Orc
    {33554, 13727, 8, 14464}, // Troll
    {33556, 13728, 6, 14458}, // Tauren
    {33555, 13729, 5, 14459}, // Undead
    {33557, 13731, 10, 14465}, // Blood Elf
    {33307, 13699, 1, 14456}, // Human
    {33310, 13713, 3, 14457}, // Dwarf
    {33653, 13725, 4, 14463}, // Night Elf
    {33650, 13723, 7, 14462}, // Gnome
    {33657, 13724, 11, 14461} // Draenei
};

class npc_vendor_argent_tournament : public CreatureScript
{
public:
    npc_vendor_argent_tournament(): CreatureScript("npc_vendor_argent_tournament"){}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        bool npcCheck = false;
        bool questCheck = false;
        bool raceCheck = false;
        uint32 textId = 0;

        for(int i = 0; (i < 10) && !npcCheck; i++)
        {
            if(creature->GetEntry() == ArgentTournamentVendor[i][0])
            {
                npcCheck = true;
                questCheck = player->GetQuestRewardStatus(ArgentTournamentVendor[i][1]);
                raceCheck = player->getRace() == ArgentTournamentVendor[i][2];
               textId = ArgentTournamentVendor[i][3];
            }
        }

        if(questCheck || raceCheck)
            player->GetSession()->SendListInventory(creature->GetGUID());
       else
            player->SEND_GOSSIP_MENU(textId, creature->GetGUID());
        return true;
    }
};

/*######
* npc_training_dummy_argent
######*/
enum SpellsTrainingDummy
{
    SPELL_DEFEND_AURA_1         = 64100,
    SPELL_ARGENT_CHARGE         = 68321,
    SPELL_ARGENT_BREAK_SHIELD   = 62626,
    SPELL_ARGENT_MELEE          = 62544,

    SPELL_SPECIAL_ATTACK_DUMMY_HIT  = 62673,  // Kill Credit (33339)
    SPELL_CHARGE_DUMMY_HIT          = 62658, // Kill Credit (33340)
    SPELL_BLOCK_DUMMY_HIT           = 62672, // Kill Credit (33341)
};

class npc_training_dummy_argent : public CreatureScript
{
public:
    npc_training_dummy_argent(): CreatureScript("npc_training_dummy_argent"){}

    struct npc_training_dummy_argentAI : ScriptedAI
    {
        npc_training_dummy_argentAI(Creature *c) : ScriptedAI(c)
        {
            m_Entry = c->GetEntry();
        }

        uint64 m_Entry;
        uint32 ResetTimer;
        uint32 ShieldTimer;

        void Reset()
        {
            me->SetControlled(true, UNIT_STATE_CONTROLLED);//disable rotate
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);//imune to knock aways like blast wave
            ResetTimer = 10000;
            ShieldTimer = 0;
        }

        void EnterEvadeMode()
        {
            if (!_EnterEvadeMode())
                return;

            Reset();
        }

        void DamageTaken(Unit * /*done_by*/, uint32 &damage)
        {
            ResetTimer = 10000;
            damage = 0;
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if(Player* _player=caster->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                switch (m_Entry)
                {
                case 33272:
                    if(spell->Id==SPELL_ARGENT_CHARGE && !me->GetAura(SPELL_DEFEND_AURA_1))
                        me->CastSpell(_player,SPELL_CHARGE_DUMMY_HIT,true);
                    break;
                case 33229:
                    if(spell->Id==SPELL_ARGENT_MELEE)
                    {
                        me->CastSpell(_player,SPELL_BLOCK_DUMMY_HIT,true);
                        me->CastSpell(caster, 62709, true);
                    }
                    break;
                case 33243:
                    if(spell->Id==SPELL_ARGENT_BREAK_SHIELD && !me->GetAura(SPELL_DEFEND))
                        me->CastSpell(_player,SPELL_SPECIAL_ATTACK_DUMMY_HIT,true);
                    break;
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (ShieldTimer <= diff)
            {
                if(m_Entry==33243)
                    me->CastSpell(me, SPELL_DEFEND, true);

                if(m_Entry==33272 && !me->GetAura(SPELL_DEFEND_AURA_1))
                    me->CastSpell(me, SPELL_DEFEND_AURA_1, true);
                ShieldTimer = 8000;
            }
            else
                ShieldTimer -= diff;

            if (!UpdateVictim())
                return;
            if (!me->HasUnitState(UNIT_STATE_STUNNED))
                me->SetControlled(true, UNIT_STATE_STUNNED);//disable rotate

            if (ResetTimer <= diff)
            {
                EnterEvadeMode();
                ResetTimer = 10000;
            }
            else
                ResetTimer -= diff;
            return;
        }

        void MoveInLineOfSight(Unit* /*who*/){}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_training_dummy_argentAI(creature);
    }
};

/*
* Npc Jeran Lockwood (33973)
*/
#define JERAN_DEFAULT_TEXTID 14453
#define JERAN_QUEST_TEXTID 14431
#define JERAN_RP_TEXTID 14434
#define GOSSIP_HELLO_JERAN_1 "Show me how to train with a Melee Target."
#define GOSSIP_HELLO_JERAN_2 "Tell me more about Defend and Thrust!"
#define SPELL_CREDIT_JERAN 64113

class npc_jeran_lockwood : public CreatureScript
{
public:
    npc_jeran_lockwood(): CreatureScript("npc_jeran_lockwood"){}

    bool OnGossipHello(Player* player, Creature* creature)
    {
//        if((player->GetQuestStatus(13828) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(13829) == QUEST_STATUS_INCOMPLETE))
        if (player->HasAura(PLAYER_ON_TOURNAMENT_MOUNT))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_JERAN_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_JERAN_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->SEND_GOSSIP_MENU(JERAN_QUEST_TEXTID, creature->GetGUID());
        }
        else
        {
            player->SEND_GOSSIP_MENU(JERAN_DEFAULT_TEXTID, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        switch(uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                player->CastSpell(player, SPELL_CREDIT_JERAN, true);
                player->CLOSE_GOSSIP_MENU();
               sCreatureTextMgr->SendChat(creature, 0, NULL);
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_JERAN_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->SEND_GOSSIP_MENU(JERAN_RP_TEXTID, creature->GetGUID());
                break;
        }
        return true;
    }
};

/*
* Npc Rugan Steelbelly (33972)
*/
#define RUGAN_DEFAULT_TEXTID 14453
#define RUGAN_QUEST_TEXTID 14436
#define RUGAN_RP_TEXTID 14437
#define GOSSIP_HELLO_RUGAN_1 "Show me how to train with a Charge Target."
#define GOSSIP_HELLO_RUGAN_2 "Tell me more about the Charge!"
#define SPELL_CREDIT_RUGAN 64114

class npc_rugan_steelbelly : public CreatureScript
{
public:
    npc_rugan_steelbelly(): CreatureScript("npc_rugan_steelbelly"){}

    bool OnGossipHello(Player* player, Creature* creature)
    {
//        if((player->GetQuestStatus(13837) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(13839) == QUEST_STATUS_INCOMPLETE))
        if (player->HasAura(PLAYER_ON_TOURNAMENT_MOUNT))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_RUGAN_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_RUGAN_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->SEND_GOSSIP_MENU(RUGAN_QUEST_TEXTID, creature->GetGUID());
        }
        else
        {
            player->SEND_GOSSIP_MENU(RUGAN_DEFAULT_TEXTID, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        switch(uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                player->CastSpell(player, SPELL_CREDIT_RUGAN, true);
                player->CLOSE_GOSSIP_MENU();
                sCreatureTextMgr->SendChat(creature, 0, NULL);
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_RUGAN_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->SEND_GOSSIP_MENU(RUGAN_RP_TEXTID, creature->GetGUID());
                break;
        }
        return true;
    }
};

/*
* Npc Valis Windchaser
*/
#define VALIS_DEFAULT_TEXTID 14453
#define VALIS_QUEST_TEXTID 14438
#define VALIS_RP_TEXTID 14439
#define GOSSIP_HELLO_VALIS_1 "Show me how to train with a Ranged Target."
#define GOSSIP_HELLO_VALIS_2 "Tell me more about using the Shield-Breaker."
#define SPELL_CREDIT_VALIS 64115
class npc_valis_windchaser : public CreatureScript
{
public:
    npc_valis_windchaser(): CreatureScript("npc_valis_windchaser"){}

    bool OnGossipHello(Player* player, Creature* creature)
    {
//        if((player->GetQuestStatus(13835) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(13838) == QUEST_STATUS_INCOMPLETE))
        if (player->HasAura(PLAYER_ON_TOURNAMENT_MOUNT))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_VALIS_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_VALIS_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->SEND_GOSSIP_MENU(VALIS_QUEST_TEXTID, creature->GetGUID());
        }
        else
            player->SEND_GOSSIP_MENU(VALIS_DEFAULT_TEXTID, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                player->CastSpell(player, SPELL_CREDIT_VALIS, true);
                player->CLOSE_GOSSIP_MENU();
                sCreatureTextMgr->SendChat(creature, 0, NULL);
            break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_VALIS_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                player->SEND_GOSSIP_MENU(VALIS_RP_TEXTID, creature->GetGUID());
            break;
        }
        return true;
    }
};

/*######
## Argent Tournament: Quest There's Something About the Squire "13654"
######*/

enum Maloric
{
    SPELL_INCAPACITATE_MALORIC              = 63124,
    SPELL_SEARCH_MALORIC_CREDIT             = 63126, // instead it should be triggered by dummy effect of 63125
    QUEST_THERES_SOMETHING_ABOUT_THE_SQUIRE = 13654
};

class npc_maloric : public CreatureScript
{
public:
    npc_maloric() : CreatureScript("npc_maloric") {}

    struct npc_maloricAI : public ScriptedAI
    {
        npc_maloricAI(Creature *c) : ScriptedAI(c) {}

        void SpellHit(Unit* pCaster, const SpellInfo* spell)
        {
            if (pCaster->GetTypeId() == TYPEID_PLAYER)
            {
                if (spell->Id == SPELL_INCAPACITATE_MALORIC)
                {
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                }
            }
        }
    };

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_maloricAI(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_THERES_SOMETHING_ABOUT_THE_SQUIRE) == QUEST_STATUS_INCOMPLETE && creature->HasAura(SPELL_INCAPACITATE_MALORIC))
        {
            player->CastSpell(player, SPELL_SEARCH_MALORIC_CREDIT, true);
            creature->AI()->AttackStart(player);
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
        return true;
    }


};

// need correct positions
const Position movePosition[] = 
{
    { 8539.276367f, 624.307678f, 563.883545f, 0.0f },
    { 8607.274414f, 796.302795f, 597.421082f, 0.0f },
    { 8689.521484f, 1071.988525f, 607.254333f, 0.0f },
    { 8759.689453f, 1333.898315f, 514.711304f, 0.0f },
    { 8854.704102f, 1684.304443f, 267.374268f, 0.0f },
    { 8868.194336f, 1900.236206f, 136.044876f, 0.0f },
    { 8893.030273f, 1998.716431f, 88.405754f, 0.0f },
    { 8958.488281f, 2062.763428f, 22.060783f, 0.0f },
    { 8980.103516f, 2068.657227f, 12.500456f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f }
};
class vehicle_knight_gryphon : public CreatureScript
{
public:
    vehicle_knight_gryphon() : CreatureScript("vehicle_knight_gryphon") { }

    struct vehicle_knight_gryphonAI : VehicleAI
    {
        vehicle_knight_gryphonAI(Creature *c) : VehicleAI(c) 
        {
            MovingStarted = false;
            curPoint = 0;
        }

        uint8 curPoint;
        bool MovingStarted;

        void UpdateAI(uint32 /*diff*/) override
        {
            if (!MovingStarted) {
                me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                me->GetMotionMaster()->MovePoint(curPoint,movePosition[curPoint]);
                MovingStarted = true;
            } else
                if (me->GetDistance(movePosition[curPoint]) <= 5.0f)
               {
                    curPoint++;
                    if (movePosition[curPoint].GetPositionX() > 8000)
                        me->GetMotionMaster()->MovePoint(curPoint,movePosition[curPoint]);
                    else  {
                        if (Player* target=me->GetCharmerOrOwnerPlayerOrPlayerItself())
                        {
                            target->KilledMonsterCredit(me->GetEntry(),0);
                           target->ExitVehicle();
                        }
                        me->DespawnOrUnsummon(0);
                    }
                }
        }
    };

    CreatureAI *GetAI(Creature *creature) const
    {
        return new vehicle_knight_gryphonAI(creature);
    }
};

class spell_defend : public SpellScriptLoader
{
    public:
        spell_defend() : SpellScriptLoader("spell_defend") { }

        class spell_defendAuraScript : public AuraScript
        {
            PrepareAuraScript(spell_defendAuraScript);
            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                // check if spellid exists in dbc, we will trigger it later
                if (!sSpellStore.LookupEntry(SHIELD_LEVEL1))
                    return false;
                if (!sSpellStore.LookupEntry(SHIELD_LEVEL2))
                    return false;
                if (!sSpellStore.LookupEntry(SHIELD_LEVEL3))
                    return false;
                return true;
            }

            void HandleEffectApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (aurEff->GetEffIndex()==EFFECT_1)
                    return;

                Unit* target = GetTarget();
                if (target->GetOwner())
                    target=target->GetOwner();

                switch (GetStackAmount())
                {
                case 1:
                    target->AddAura(SHIELD_LEVEL1, target);
                    break;
                case 2:
                    target->AddAura(SHIELD_LEVEL2, target);
                    break;
                case 3:
                    target->AddAura(SHIELD_LEVEL3, target);
                    break;
                }
            }

            void HandleEffectRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
            {
                if (aurEff->GetEffIndex()==EFFECT_1)
                    return;

               Unit* target = GetTarget();
                if (target->GetOwner())
                {
                    target=target->GetOwner();
                    if ((mode & AURA_EFFECT_HANDLE_REAPPLY) == 0)
                        target->RemoveAuraFromStack(GetId());
                }

                target->RemoveAura(SHIELD_LEVEL3);
                target->RemoveAura(SHIELD_LEVEL2);
                target->RemoveAura(SHIELD_LEVEL1);
            }

            // function registering
            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_defendAuraScript::HandleEffectApply, EFFECT_ALL, SPELL_EFFECT_ANY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
                OnEffectRemove += AuraEffectRemoveFn(spell_defendAuraScript::HandleEffectRemove, EFFECT_ALL, SPELL_EFFECT_ANY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
            }
        };

        // function which creates AuraScript
        AuraScript* GetAuraScript() const
        {
            return new spell_defendAuraScript();
        }
};

enum eValiantText
{
    NPC_ARGENT_VAILIANT_TEXT_SAY_START = -1850007, //You think you have the courage?  We shall see.
    NPC_ARGENT_VAILIANT_TEXT_SAY_WIN = -1850008, //Impressive demonstration. I think you\'re able to join the ranks of the valiants.
    NPC_ARGENT_VAILIANT_TEXT_SAY_LOOSE = -1850009, //I\'ve won. You'll probably have more luck next time.

    NPC_FACTION_VAILIANT_TEXT_SAY_START_1 = -1850004, //Stand ready!
    NPC_FACTION_VAILIANT_TEXT_SAY_START_2 = -1850005, //Let the battle begin!
    NPC_FACTION_VAILIANT_TEXT_SAY_START_3 = -1850006, //Prepare your self!
    NPC_FACTION_VAILIANT_TEXT_SAY_WIN_1 = -1850010, //I stand defeated. Nice battle !
    NPC_FACTION_VAILIANT_TEXT_SAY_WIN_2 = -1850011, //It seems that I\'ve underestimated your skills. Well done.'
    NPC_FACTION_VAILIANT_TEXT_SAY_LOOSE = -1850012  //You\'ll probably have more luck next time.
};

enum eChampionText
{
    NPC_ARGENT_CHAMPION_TEXT_SAY_START = -1850013, //    Vous pensez avoir la vaillance en vous ? Nous verrons.
    NPC_ARGENT_CHAMPION_TEXT_SAY_WIN = -1850014, //    Impressionnante démonstration. Je pense que vous êtes tout à fait en mesure de rejoindre les rangs des vaillants.
    NPC_ARGENT_CHAMPION_TEXT_SAY_LOOSE = -1850009, //    J'ai gagné. Vous aurez sans doute plus de chance la prochaine fois.

    NPC_FACTION_CHAMPION_TEXT_SAY_START_1 = -1850004, //    Tenez-vous prêt !
    NPC_FACTION_CHAMPION_TEXT_SAY_START_2 = -1850005, //    Que le combat commence !
    NPC_FACTION_CHAMPION_TEXT_SAY_START_3 = -1850006, //    Préparez-vous !
    NPC_FACTION_CHAMPION_TEXT_SAY_WIN_1 = -1850010, //    Je suis vaincue. Joli combat !
    NPC_FACTION_CHAMPION_TEXT_SAY_WIN_2 = -1850011, //    On dirait que j'ai sous-estimé vos compétences. Bien joué.
    NPC_FACTION_CHAMPION_TEXT_SAY_LOOSE = -1850012, //    J'ai gagné. Vous aurez sans doute plus de chance la prochaine fois.
};

class npc_argent_valiant : public CreatureScript
{
   public:
       npc_argent_valiant() : CreatureScript("npc_argent_valiant") {}

       struct npc_argent_valiantAI : public ScriptedAI
       {
           npc_argent_valiantAI(Creature* creature) : ScriptedAI(creature)
           {
               creature->Relocate(8575.451f, 952.472f, 547.554f, 0.38f);
               creature->GetMotionMaster()->MovePoint(0, 8599.258f, 963.951f, 547.553f);
               creature->setFaction(35); //wrong faction in db?
           }

           void Reset()
           {
               me->CastSpell(me, SPELL_DEFEND, true);
               me->CastSpell(me, SPELL_DEFEND, true);
               me->CastSpell(me, SPELL_DEFEND_8_S, true);
               Reset();
           }

           void KilledUnit(Unit* victim)
           {
               me->AI()->Talk(NPC_ARGENT_VAILIANT_TEXT_SAY_LOOSE, me);
               KilledUnit(victim);
           }

           void EnterCombat(Unit* /*who*/)
           {
               me->AI()->Talk(NPC_ARGENT_VAILIANT_TEXT_SAY_START, me);
           }
       };

       CreatureAI* GetAI(Creature* creature) const override
       {
           return new npc_argent_valiantAI(creature);
       }
};

struct dummy_valiant_championAI : public ScriptedAI
{
    dummy_valiant_championAI(Creature* creature) : ScriptedAI(creature) {}

    void Reset()
    {
        uiChargeTimer = 4500;
        uiShieldBreakerTimer = 1500;
        uiRunAwayTimer=15000;
        me->RestoreFaction();
        ScriptedAI::Reset();
    }

    void MovementInform(uint32 uiType, uint32 /*uiId*/)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        me->setFaction(14);
    }

    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        if (uiDamage > me->GetHealth())
        {
            if (Player* target=pDoneBy->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                PlayerWon(target);
                uiDamage = 0;
                me->DespawnOrUnsummon(5000);
                me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                EnterEvadeMode();
            }
        }
    }

    void KilledUnit(Unit* /*victim*/)
    {
        me->setFaction(35);
        me->DespawnOrUnsummon(5000);
        me->CombatStop(true);
    }

    void DoMeleeAttackIfReady()
    {
        //Make sure our attack is ready and we aren't currently casting before checking distance
        if (me->isAttackReady())
        {
            //If we are within range melee the target
            if (me->IsWithinMeleeRange(me->GetVictim()))
            {
                DoCastVictim(SPELL_THRUST);
                me->resetAttackTimer();
            }

        if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE)
            me->GetMotionMaster()->MoveChase(me->GetVictim());
        }
    }

    void UpdateAI(uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        //me->IsInRange(target,5,40,false)
        if (uiShieldBreakerTimer <= uiDiff)
        {
            DoCastVictim(SPELL_SHIELD_BREAKER);
            uiShieldBreakerTimer = 1100;
            return;
        } else uiShieldBreakerTimer -= uiDiff;

        if (uiChargeTimer <= uiDiff)
        {
            if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == CHASE_MOTION_TYPE) // so he won't cast charge while running away
            {
                DoCastVictim(SPELL_CHARGE);
                uiChargeTimer = 3000;
                return;
            }
        } else uiChargeTimer -= uiDiff;

        if (uiRunAwayTimer <= uiDiff)
        {
            float x, y, z;
            me->GetVictim()->GetRandomContactPoint(me, x, y, z, 10, 20);
            me->GetMotionMaster()->MovePoint(0, x, y, z);
            uiRunAwayTimer = 15000;
            return;
        } else uiRunAwayTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }

protected:
    virtual void PlayerWon(Unit* target)
    {
        switch (me->GetEntry())
        {
        case NPC_ARGENT_VALIANT:
            target->CastSpell(target,SPELL_VALIANT_CREDIT, true);
            target->CastSpell(target,BESTED_ARGENT_CRUSADE, true);
            me->AI()->Talk(NPC_ARGENT_VAILIANT_TEXT_SAY_WIN);
            break;
        case NPC_ARGENT_CHAMPION:
           target->CastSpell(target,SPELL_CHAMPION_CREDIT, true);
            target->CastSpell(target,BESTED_ARGENT_CRUSADE, true);
            me->AI()->Talk(NPC_ARGENT_CHAMPION_TEXT_SAY_WIN);
            break;
        case NPC_DARNASSUS_VALIANT:
        case NPC_DARNASSUS_CHAMPION:
            target->CastSpell(target,BESTED_DARNASSUS, true);
            break;
        case NPC_EXODAR_VALIANT:
        case NPC_EXODAR_CHAMPION:
            target->CastSpell(target,BESTED_THE_EXODAR, true);
            break;
        case NPC_GNOMEREGAN_VALIANT:
        case NPC_GNOMEREGAN_CHAMPION:
            target->CastSpell(target,BESTED_GNOMEREGAN, true);
            break;
        case NPC_IRONFORGE_VALIANT:
        case NPC_IRONFORGE_CHAMPION:
            target->CastSpell(target,BESTED_IRONFORGE, true);
            break;
        case NPC_ORGRIMMAR_VALIANT:
        case NPC_ORGRIMMAR_CHAMPION:
            target->CastSpell(target,BESTED_ORGRIMMAR, true);
            break;
        case NPC_SENJIN_VALIANT:
        case NPC_SENJIN_CHAMPION:
            target->CastSpell(target,BESTED_SENJIN, true);
            break;
        case NPC_SILVERMOON_VALIANT:
        case NPC_SILVERMOON_CHAMPION:
            target->CastSpell(target,BESTED_SILVERMOON_CITY, true);
            break;
        case NPC_STORMWIND_VALIANT:
        case NPC_STORMWIND_CHAMPION:
            target->CastSpell(target,BESTED_STORMWIND, true);
            break;
        case NPC_UNDERCITY_VALIANT:
        case NPC_UNDERCITY_CHAMPION:
            target->CastSpell(target,BESTED_THE_UNDERCITY, true);
            break;
        case NPC_THUNDER_BLUFF_VALIANT:
        case NPC_THUNDER_BLUFF_CHAMPION:
            target->CastSpell(target,BESTED_THUNDER_BLUFF, true);
            break;
        }
    }

    uint32 uiChargeTimer;
    uint32 uiShieldBreakerTimer;
    uint32 uiRunAwayTimer;
};

/*######
## npc_guardian_pavilion
######*/

enum GuardianPavilion
{
    SPELL_TRESPASSER_H                            = 63987,
    AREA_SUNREAVER_PAVILION                       = 4676,

    AREA_SILVER_COVENANT_PAVILION                 = 4677,
    SPELL_TRESPASSER_A                            = 63986,
};

class npc_guardian_pavilion : public CreatureScript
{
public:
    npc_guardian_pavilion() : CreatureScript("npc_guardian_pavilion") { }

    struct npc_guardian_pavilionAI : public ScriptedAI
    {
        npc_guardian_pavilionAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
        }

        void MoveInLineOfSight(Unit* who) override

        {
            if (me->GetAreaId() != AREA_SUNREAVER_PAVILION && me->GetAreaId() != AREA_SILVER_COVENANT_PAVILION)
                return;

            if (!who || who->GetTypeId() != TYPEID_PLAYER || !me->IsHostileTo(who) || !me->isInBackInMap(who, 5.0f))
                return;

            if (who->HasAura(SPELL_TRESPASSER_H) || who->HasAura(SPELL_TRESPASSER_A))
                return;

            if (who->ToPlayer()->GetTeamId() == TEAM_ALLIANCE)
                who->CastSpell(who, SPELL_TRESPASSER_H, true);
            else
                who->CastSpell(who, SPELL_TRESPASSER_A, true);

        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_guardian_pavilionAI(creature);
    }
};

/*######
## npc_vereth_the_cunning
######*/

enum VerethTheCunning
{
    NPC_GEIST_RETURN_BUNNY_KC   = 31049,
    NPC_LITHE_STALKER           = 30894,
    SPELL_SUBDUED_LITHE_STALKER = 58151,
};

class npc_vereth_the_cunning : public CreatureScript
{
public:
    npc_vereth_the_cunning() : CreatureScript("npc_vereth_the_cunning") { }

    struct npc_vereth_the_cunningAI : public ScriptedAI
    {
        npc_vereth_the_cunningAI(Creature* creature) : ScriptedAI(creature) { }

        void MoveInLineOfSight(Unit* who) override

        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetEntry() == NPC_LITHE_STALKER && me->IsWithinDistInMap(who, 10.0f))
            {
                if (Unit* owner = who->GetCharmer())
                {
                    if (who->HasAura(SPELL_SUBDUED_LITHE_STALKER))
                        {
                            owner->ToPlayer()->KilledMonsterCredit(NPC_GEIST_RETURN_BUNNY_KC, 0);
                            who->ToCreature()->DisappearAndDie();

                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vereth_the_cunningAI(creature);
    }
};

/*######
* npc_tournament_training_dummy
######*/
enum TournamentDummy
{
    NPC_CHARGE_TARGET         = 33272,
    NPC_MELEE_TARGET          = 33229,
    NPC_RANGED_TARGET         = 33243,

    SPELL_CHARGE_CREDIT       = 62658,
    SPELL_MELEE_CREDIT        = 62672,
    SPELL_RANGED_CREDIT       = 62673,

    SPELL_PLAYER_THRUST       = 62544,
    SPELL_PLAYER_BREAK_SHIELD = 62626,
    SPELL_PLAYER_CHARGE       = 62874,

    SPELL_RANGED_DEFEND       = 62719,
    SPELL_CHARGE_DEFEND       = 64100,
    SPELL_VULNERABLE          = 62665,

    SPELL_COUNTERATTACK       = 62709,

    EVENT_DUMMY_RECAST_DEFEND = 1,
    EVENT_DUMMY_RESET         = 2,
};

class npc_tournament_training_dummy : public CreatureScript
{
    public:
        npc_tournament_training_dummy(): CreatureScript("npc_tournament_training_dummy"){ }

        struct npc_tournament_training_dummyAI : ScriptedAI
        {
            npc_tournament_training_dummyAI(Creature* creature) : ScriptedAI(creature)
            {
                SetCombatMovement(false);
            }

            EventMap events;
            bool isVulnerable;

            void Reset() override
            {
                me->SetControlled(true, UNIT_STATE_STUNNED);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                isVulnerable = false;

                // Cast Defend spells to max stack size
                switch (me->GetEntry())
                {
                    case NPC_CHARGE_TARGET:
                        DoCast(SPELL_CHARGE_DEFEND);
                        break;
                    case NPC_RANGED_TARGET:
                        me->CastCustomSpell(SPELL_RANGED_DEFEND, SPELLVALUE_AURA_STACK, 3, me);
                        break;
                }

                events.Reset();
                events.ScheduleEvent(EVENT_DUMMY_RECAST_DEFEND, 5000);
            }

            void EnterEvadeMode() override
            {
                if (!_EnterEvadeMode())
                    return;

                Reset();
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage) override
            {
                damage = 0;
                events.RescheduleEvent(EVENT_DUMMY_RESET, 10000);
            }

            void SpellHit(Unit* caster, SpellInfo const* spell) override
            {
                switch (me->GetEntry())
                {
                    case NPC_CHARGE_TARGET:
                        if (spell->Id == SPELL_PLAYER_CHARGE)
                            if (isVulnerable)
                                DoCast(caster, SPELL_CHARGE_CREDIT, true);
                        break;
                    case NPC_MELEE_TARGET:
                        if (spell->Id == SPELL_PLAYER_THRUST)
                        {
                            DoCast(caster, SPELL_MELEE_CREDIT, true);

                            if (Unit* target = caster->GetVehicleBase())
                                DoCast(target, SPELL_COUNTERATTACK, true);
                        }
                        break;
                    case NPC_RANGED_TARGET:
                        if (spell->Id == SPELL_PLAYER_BREAK_SHIELD)
                            if (isVulnerable)
                                DoCast(caster, SPELL_RANGED_CREDIT, true);
                        break;
                }

                if (spell->Id == SPELL_PLAYER_BREAK_SHIELD)
                    if (!me->HasAura(SPELL_CHARGE_DEFEND) && !me->HasAura(SPELL_RANGED_DEFEND))
                        isVulnerable = true;
            }

            void UpdateAI(uint32 diff) override
            {
                events.Update(diff);

                switch (events.ExecuteEvent())
                {
                    case EVENT_DUMMY_RECAST_DEFEND:
                        switch (me->GetEntry())
                        {
                            case NPC_CHARGE_TARGET:
                            {
                                if (!me->HasAura(SPELL_CHARGE_DEFEND))
                                    DoCast(SPELL_CHARGE_DEFEND);
                                break;
                            }
                            case NPC_RANGED_TARGET:
                            {
                                Aura* defend = me->GetAura(SPELL_RANGED_DEFEND);
                                if (!defend || defend->GetStackAmount() < 3 || defend->GetDuration() <= 8000)
                                    DoCast(SPELL_RANGED_DEFEND);
                                break;
                            }
                        }
                        isVulnerable = false;
                        events.ScheduleEvent(EVENT_DUMMY_RECAST_DEFEND, 5000);
                        break;
                    case EVENT_DUMMY_RESET:
                        if (UpdateVictim())
                        {
                            EnterEvadeMode();
                            events.ScheduleEvent(EVENT_DUMMY_RESET, 10000);
                        }
                        break;
                }

                if (!UpdateVictim())
                    return;

                if (!me->HasUnitState(UNIT_STATE_STUNNED))
                    me->SetControlled(true, UNIT_STATE_STUNNED);
            }

            void MoveInLineOfSight(Unit* /*who*/) override { }

        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_tournament_training_dummyAI(creature);
        }

};

// Battle for Crusaders' Pinnacle
enum BlessedBanner
{
    SPELL_BLESSING_OF_THE_CRUSADE       = 58026,
    SPELL_THREAT_PULSE                  = 58113,
    SPELL_CRUSADERS_SPIRE_VICTORY       = 58084,
    SPELL_TORCH                         = 58121,

    NPC_BLESSED_BANNER                  = 30891,
    NPC_CRUSADER_LORD_DALFORS           = 31003,
    NPC_ARGENT_BATTLE_PRIEST            = 30919,
    NPC_ARGENT_MASON                    = 30900,
    NPC_REANIMATED_CAPTAIN              = 30986,
    NPC_SCOURGE_DRUDGE                  = 30984,
    NPC_HIDEOUS_PLAGEBRINGER            = 30987,
    NPC_HALOF_THE_DEATHBRINGER          = 30989,
    NPC_LK                              = 31013,

    BANNER_SAY                          = 0, // "The Blessed Banner of the Crusade has been planted.\n Defend the banner from all attackers!"
    DALFORS_SAY_PRE_1                   = 0, // "BY THE LIGHT! Those damned monsters! Look at what they've done to our people!"
    DALFORS_SAY_PRE_2                   = 1, // "Burn it down, boys. Burn it all down."
    DALFORS_SAY_START                   = 2, // "Let 'em come. They'll pay for what they've done!"
    DALFORS_YELL_FINISHED               = 3, // "We've done it, lads! We've taken the pinnacle from the Scourge! Report to Father Gustav at once and tell him the good news! We're gonna get to buildin' and settin' up! Go!"
    LK_TALK_1                           = 0, // "Leave no survivors!"
    LK_TALK_2                           = 1, // "Cower before my terrible creations!"
    LK_TALK_3                           = 2, // "Feast my children! Feast upon the flesh of the living!"
    LK_TALK_4                           = 3, // "Lay down your arms and surrender your souls!"

    EVENT_SPAWN                         = 1,
    EVENT_INTRO_1                       = 2,
    EVENT_INTRO_2                       = 3,
    EVENT_INTRO_3                       = 4,
    EVENT_MASON_ACTION                  = 5,
    EVENT_START_FIGHT                   = 6,
    EVENT_WAVE_SPAWN                    = 7,
    EVENT_HALOF                         = 8,
    EVENT_ENDED                         = 9,
};

Position const DalforsPos[3] =
{
    {6458.703f, 403.858f, 490.498f, 3.1205f}, // Dalfors spawn point
    {6422.950f, 423.335f, 510.451f, 0.0f}, // Dalfors intro pos
    {6426.343f, 420.515f, 508.650f, 0.0f}, // Dalfors fight pos
};

Position const Priest1Pos[2] =
{
    {6462.025f, 403.681f, 489.721f, 3.1007f}, // priest1 spawn point
    {6421.480f, 423.576f, 510.781f, 5.7421f}, // priest1 intro pos
};

Position const Priest2Pos[2] =
{
    {6463.969f, 407.198f, 489.240f, 2.2689f}, // priest2 spawn point
    {6419.778f, 421.404f, 510.972f, 5.7421f}, // priest2 intro pos
};

Position const Priest3Pos[2] =
{
    {6464.371f, 400.944f, 489.186f, 6.1610f}, // priest3 spawn point
    {6423.516f, 425.782f, 510.774f, 5.7421f}, // priest3 intro pos
};

Position const Mason1Pos[3] =
{
    {6462.929f, 409.826f, 489.392f, 3.0968f}, // mason1 spawn point
    {6428.163f, 421.960f, 508.297f, 0.0f}, // mason1 intro pos
    {6414.335f, 454.904f, 511.395f, 2.8972f}, // mason1 action pos
};

Position const Mason2Pos[3] =
{
    {6462.650f, 405.670f, 489.576f, 2.9414f}, // mason2 spawn point
    {6426.250f, 419.194f, 508.219f, 0.0f}, // mason2 intro pos
    {6415.014f, 446.849f, 511.395f, 3.1241f}, // mason2 action pos
};

Position const Mason3Pos[3] =
{
    {6462.646f, 401.218f, 489.601f, 2.7864f}, // mason3 spawn point
    {6423.855f, 416.598f, 508.305f, 0.0f}, // mason3 intro pos
    {6417.070f, 438.824f, 511.395f, 3.6651f}, // mason3 action pos
};

class npc_blessed_banner : public CreatureScript
{
public:
    npc_blessed_banner() : CreatureScript("npc_blessed_banner") { }

    struct npc_blessed_bannerAI : public ScriptedAI
    {
        npc_blessed_bannerAI(Creature* creature) : ScriptedAI(creature), Summons(me)
        {
            HalofSpawned = false;
            PhaseCount = 0;
            Summons.DespawnAll();

            SetCombatMovement(false);
        }

        EventMap events;

        bool HalofSpawned;

        uint32 PhaseCount;

        SummonList Summons;

        uint64 guidDalfors;
        uint64 guidPriest[3];
        uint64 guidMason[3];
        uint64 guidHalof;

        void Reset() override
        {
            me->setRegeneratingHealth(false);
            DoCast(SPELL_THREAT_PULSE);
            Talk(BANNER_SAY);
            events.ScheduleEvent(EVENT_SPAWN, 3000);
        }

        void EnterCombat(Unit* /*who*/) override { }

        void MoveInLineOfSight(Unit* /*who*/) override { }


        void JustSummoned(Creature* Summoned) override
        {
            Summons.Summon(Summoned);
        }

        void JustDied(Unit* /*killer*/) override
        {
            Summons.DespawnAll();
            me->DespawnOrUnsummon();
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            switch (events.ExecuteEvent())
            {
                case EVENT_SPAWN:
                    {
                        if (Creature* Dalfors = DoSummon(NPC_CRUSADER_LORD_DALFORS, DalforsPos[0]))
                        {
                            guidDalfors = Dalfors->GetGUID();
                            Dalfors->GetMotionMaster()->MovePoint(0, DalforsPos[1]);
                        }
                        if (Creature* Priest1 = DoSummon(NPC_ARGENT_BATTLE_PRIEST, Priest1Pos[0]))
                        {
                            guidPriest[0] = Priest1->GetGUID();
                            Priest1->GetMotionMaster()->MovePoint(0, Priest1Pos[1]);
                        }
                        if (Creature* Priest2 = DoSummon(NPC_ARGENT_BATTLE_PRIEST, Priest2Pos[0]))
                        {
                            guidPriest[1] = Priest2->GetGUID();
                            Priest2->GetMotionMaster()->MovePoint(0, Priest2Pos[1]);
                        }
                        if (Creature* Priest3 = DoSummon(NPC_ARGENT_BATTLE_PRIEST, Priest3Pos[0]))
                        {
                            guidPriest[2] = Priest3->GetGUID();
                            Priest3->GetMotionMaster()->MovePoint(0, Priest3Pos[1]);
                        }
                        if (Creature* Mason1 = DoSummon(NPC_ARGENT_MASON, Mason1Pos[0]))
                        {
                            guidMason[0] = Mason1->GetGUID();
                            Mason1->GetMotionMaster()->MovePoint(0, Mason1Pos[1]);
                        }
                        if (Creature* Mason2 = DoSummon(NPC_ARGENT_MASON, Mason2Pos[0]))
                        {
                            guidMason[1] = Mason2->GetGUID();
                            Mason2->GetMotionMaster()->MovePoint(0, Mason2Pos[1]);
                        }
                        if (Creature* Mason3 = DoSummon(NPC_ARGENT_MASON, Mason3Pos[0]))
                        {
                            guidMason[2] = Mason3->GetGUID();
                            Mason3->GetMotionMaster()->MovePoint(0, Mason3Pos[1]);
                        }
                        events.ScheduleEvent(EVENT_INTRO_1, 15000);
                    }
                    break;
                case EVENT_INTRO_1:
                    {
                        if (Creature* Dalfors = ObjectAccessor::GetCreature(*me, guidDalfors))
                            Dalfors->AI()->Talk(DALFORS_SAY_PRE_1);
                        events.ScheduleEvent(EVENT_INTRO_2, 5000);
                    }
                    break;
                case EVENT_INTRO_2:
                    {
                        if (Creature* Dalfors = ObjectAccessor::GetCreature(*me, guidDalfors))
                        {
                            Dalfors->SetFacingTo(6.215f);
                            Dalfors->AI()->Talk(DALFORS_SAY_PRE_2);
                        }
                    events.ScheduleEvent(EVENT_INTRO_3, 5000);
                    }
                    break;
                case EVENT_INTRO_3:
                    {
                        if (Creature* Dalfors = ObjectAccessor::GetCreature(*me, guidDalfors))
                        {
                            Dalfors->GetMotionMaster()->MovePoint(0, DalforsPos[2]);
                            Dalfors->SetHomePosition(DalforsPos[2]);
                        }
                        if (Creature* Priest1 = ObjectAccessor::GetCreature(*me, guidPriest[0]))
                        {
                            Priest1->SetFacingTo(5.7421f);
                            Priest1->SetHomePosition(Priest1Pos[1]);
                        }
                        if (Creature* Priest2 = ObjectAccessor::GetCreature(*me, guidPriest[1]))
                        {
                            Priest2->SetFacingTo(5.7421f);
                            Priest2->SetHomePosition(Priest2Pos[1]);
                        }
                        if (Creature* Priest3 = ObjectAccessor::GetCreature(*me, guidPriest[2]))
                        {
                            Priest3->SetFacingTo(5.7421f);
                            Priest3->SetHomePosition(Priest3Pos[1]);
                        }
                        if (Creature* Mason1 = ObjectAccessor::GetCreature(*me, guidMason[0]))
                        {
                            Mason1->GetMotionMaster()->MovePoint(0, Mason1Pos[2]);
                            Mason1->SetHomePosition(Mason1Pos[2]);
                        }
                        if (Creature* Mason2 = ObjectAccessor::GetCreature(*me, guidMason[1]))
                        {
                            Mason2->GetMotionMaster()->MovePoint(0, Mason2Pos[2]);
                            Mason2->SetHomePosition(Mason2Pos[2]);
                        }
                        if (Creature* Mason3 = ObjectAccessor::GetCreature(*me, guidMason[2]))
                        {
                            Mason3->GetMotionMaster()->MovePoint(0, Mason3Pos[2]);
                            Mason3->SetHomePosition(Mason3Pos[2]);
                        }
                        events.ScheduleEvent(EVENT_START_FIGHT, 5000);
                        events.ScheduleEvent(EVENT_MASON_ACTION, 15000);
                    }
                    break;
                case EVENT_MASON_ACTION:
                    {
                        if (Creature* Mason1 = ObjectAccessor::GetCreature(*me, guidMason[0]))
                        {
                            Mason1->SetFacingTo(2.8972f);
                            Mason1->AI()->SetData(1, 1); // triggers SAI actions on npc
                        }
                        if (Creature* Mason2 = ObjectAccessor::GetCreature(*me, guidMason[1]))
                        {
                            Mason2->SetFacingTo(3.1241f);
                            Mason2->AI()->SetData(1, 1); // triggers SAI actions on npc
                        }
                        if (Creature* Mason3 = ObjectAccessor::GetCreature(*me, guidMason[2]))
                        {
                            Mason3->SetFacingTo(3.6651f);
                            Mason3->AI()->SetData(1, 1); // triggers SAI actions on npc
                        }
                    }
                    break;
                case EVENT_START_FIGHT:
                    {
                        if (Creature* LK = GetClosestCreatureWithEntry(me, NPC_LK, 100))
                            LK->AI()->Talk(LK_TALK_1);
                        if (Creature* Dalfors = ObjectAccessor::GetCreature(*me, guidDalfors))
                            Dalfors->AI()->Talk(DALFORS_SAY_START);
                        events.ScheduleEvent(EVENT_WAVE_SPAWN, 1000);
                    }
                    break;
                case EVENT_WAVE_SPAWN:
                    {
                        if (PhaseCount == 3)
                        {
                            if (Creature* LK = GetClosestCreatureWithEntry(me, NPC_LK, 100))
                                LK->AI()->Talk(LK_TALK_2);
                        }
                        else if (PhaseCount == 6)
                        {
                            if (Creature* LK = GetClosestCreatureWithEntry(me, NPC_LK, 100))
                                LK->AI()->Talk(LK_TALK_3);
                        }
                        if (Creature* tempsum = DoSummon(NPC_SCOURGE_DRUDGE, Mason3Pos[0]))
                            {
                                tempsum->SetHomePosition(DalforsPos[2]);
                                tempsum->AI()->AttackStart(GetClosestCreatureWithEntry(me, NPC_BLESSED_BANNER, 100));
                            }
                        if (urand(0, 1) == 0)
                        {
                            if (Creature* tempsum = DoSummon(NPC_HIDEOUS_PLAGEBRINGER, Mason1Pos[0]))
                            {
                                tempsum->SetHomePosition(DalforsPos[2]);
                                tempsum->AI()->AttackStart(GetClosestCreatureWithEntry(me, NPC_BLESSED_BANNER, 100));
                            }
                            if (Creature* tempsum = DoSummon(NPC_HIDEOUS_PLAGEBRINGER, Mason2Pos[0]))
                            {
                                tempsum->SetHomePosition(DalforsPos[2]);
                                tempsum->AI()->AttackStart(GetClosestCreatureWithEntry(me, NPC_BLESSED_BANNER, 100));
                            }
                        }
                        else
                        {
                            if (Creature* tempsum = DoSummon(NPC_REANIMATED_CAPTAIN, Mason1Pos[0]))
                            {
                                tempsum->SetHomePosition(DalforsPos[2]);
                                tempsum->AI()->AttackStart(GetClosestCreatureWithEntry(me, NPC_BLESSED_BANNER, 100));
                            }
                            if (Creature* tempsum = DoSummon(NPC_REANIMATED_CAPTAIN, Mason2Pos[0]))
                            {
                                tempsum->SetHomePosition(DalforsPos[2]);
                                tempsum->AI()->AttackStart(GetClosestCreatureWithEntry(me, NPC_BLESSED_BANNER, 100));
                            }
                        }

                        PhaseCount++;

                        if (PhaseCount < 8)
                            events.ScheduleEvent(EVENT_WAVE_SPAWN, urand(10000, 20000));
                        else
                            events.ScheduleEvent(EVENT_HALOF, urand(10000, 20000));
                    }
                    break;
                case EVENT_HALOF:
                    {
                        if (Creature* LK = GetClosestCreatureWithEntry(me, NPC_LK, 100))
                            LK->AI()->Talk(LK_TALK_4);
                        if (Creature* tempsum = DoSummon(NPC_SCOURGE_DRUDGE, Mason1Pos[0]))
                        {
                            tempsum->SetHomePosition(DalforsPos[2]);
                            tempsum->AI()->AttackStart(GetClosestCreatureWithEntry(me, NPC_BLESSED_BANNER, 100));
                        }
                        if (Creature* tempsum = DoSummon(NPC_SCOURGE_DRUDGE, Mason2Pos[0]))
                        {
                            tempsum->SetHomePosition(DalforsPos[2]);
                            tempsum->AI()->AttackStart(GetClosestCreatureWithEntry(me, NPC_BLESSED_BANNER, 100));
                        }
                        if (Creature* tempsum = DoSummon(NPC_HALOF_THE_DEATHBRINGER, DalforsPos[0]))
                        {
                            HalofSpawned = true;
                            guidHalof = tempsum->GetGUID();
                            tempsum->SetHomePosition(DalforsPos[2]);
                            tempsum->AI()->AttackStart(GetClosestCreatureWithEntry(me, NPC_BLESSED_BANNER, 100));
                        }
                    }
                    break;
                case EVENT_ENDED:
                    {
                        Summons.DespawnAll();
                        me->DespawnOrUnsummon();
                    }
                    break;
            }

            if (PhaseCount == 8)
                if (Creature* Halof = ObjectAccessor::GetCreature(*me, guidHalof))
                    if (Halof->isDead())
                    {
                        DoCast(me, SPELL_CRUSADERS_SPIRE_VICTORY, true);
                        Summons.DespawnEntry(NPC_HIDEOUS_PLAGEBRINGER);
                        Summons.DespawnEntry(NPC_REANIMATED_CAPTAIN);
                        Summons.DespawnEntry(NPC_SCOURGE_DRUDGE);
                        Summons.DespawnEntry(NPC_HALOF_THE_DEATHBRINGER);
                        if (Creature* Dalfors = ObjectAccessor::GetCreature(*me, guidDalfors))
                            Dalfors->AI()->Talk(DALFORS_YELL_FINISHED);
                        events.ScheduleEvent(EVENT_ENDED, 10000);
                    }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_blessed_bannerAI(creature);
    }
};

/*######
## Borrowed Technology - Id: 13291, The Solution Solution (daily) - Id: 13292, Volatility - Id: 13239, Volatiliy - Id: 13261 (daily)
######*/

enum BorrowedTechnologyAndVolatility
{
    // Spells
    SPELL_GRAB             = 59318,
    SPELL_PING_BUNNY       = 59375,
    SPELL_IMMOLATION       = 54690,
    SPELL_EXPLOSION        = 59335,
    SPELL_RIDE             = 56687,

    // Points
    POINT_GRAB_DECOY       = 1,
    POINT_FLY_AWAY         = 2,

    // Events
    EVENT_FLY_AWAY         = 1
};

class npc_frostbrood_skytalon : public CreatureScript
{
    public:
        npc_frostbrood_skytalon() : CreatureScript("npc_frostbrood_skytalon") { }

        struct npc_frostbrood_skytalonAI : public VehicleAI
        {
            npc_frostbrood_skytalonAI(Creature* creature) : VehicleAI(creature) { }

            EventMap events;

            void IsSummonedBy(Unit* summoner) override
            {
                me->GetMotionMaster()->MovePoint(POINT_GRAB_DECOY, summoner->GetPositionX(), summoner->GetPositionY(), summoner->GetPositionZ());
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (id == POINT_GRAB_DECOY)
                    if (TempSummon* summon = me->ToTempSummon())
                        if (Unit* summoner = summon->GetSummoner())
                            DoCast(summoner, SPELL_GRAB);
            }

            void UpdateAI(uint32 diff) override
            {
                VehicleAI::UpdateAI(diff);
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    if (eventId == EVENT_FLY_AWAY)
                    {
                        Position randomPosOnRadius;
                        randomPosOnRadius.m_positionZ = (me->GetPositionZ() + 40.0f);
                        me->GetNearPoint2D(randomPosOnRadius.m_positionX, randomPosOnRadius.m_positionY, 40.0f, me->GetAngle(me));
                        me->GetMotionMaster()->MovePoint(POINT_FLY_AWAY, randomPosOnRadius);
                    }
                }
            }

            void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
            {
                switch (spell->Id)
                {
                    case SPELL_EXPLOSION:
                        DoCast(me, SPELL_IMMOLATION);
                        break;
                    case SPELL_RIDE:
                        DoCastAOE(SPELL_PING_BUNNY);
                        events.ScheduleEvent(EVENT_FLY_AWAY, 100);
                        break;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_frostbrood_skytalonAI(creature);
        }
};

/*######
## The Flesh Giant Champion - Id: 13235
######*/
enum FleshGiant
{
    QUEST_FLESH_GIANT_CHAMPION = 13235,

    NPC_MORBIDUS = 30698,
    NPC_LICH_KING = 31301,
    NPC_OLAKIN = 31428,
    NPC_DHAKAR = 31306,

    FACTION_HOSTILE = 14,
    FACTION_BASIC = 2102,

    EVENT_INTRO = 1,
    EVENT_LK_SAY_1 = 2,
    EVENT_LK_SAY_2 = 3,
    EVENT_LK_SAY_3 = 4,
    EVENT_LK_SAY_4 = 5,
    EVENT_LK_SAY_5 = 6,
    EVENT_OUTRO = 7,
    EVENT_START = 8,

    SPELL_SIMPLE_TELEPORT = 64195,

    SAY_DHAKAR_START = 0,
    SAY_LK_1 = 0,
    SAY_LK_2 = 1,
    SAY_LK_3 = 2,
    SAY_LK_4 = 3,
    SAY_LK_5 = 4,
    SAY_OLAKIN_PAY = 0
};

class npc_margrave_dhakar : public CreatureScript
{
    public:
        npc_margrave_dhakar() : CreatureScript("npc_margrave_dhakar") { }

        struct npc_margrave_dhakarAI : public ScriptedAI
        {
            npc_margrave_dhakarAI(Creature* creature) : ScriptedAI(creature) , _summons(me), _lichKingGuid(0) { }

            void Reset() override
            {
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);

                _events.Reset();
                _summons.DespawnAll();
            }

            void sGossipSelect(Player* player, uint32 sender, uint32 action) override
            {
                if (player->GetQuestStatus(QUEST_FLESH_GIANT_CHAMPION) == QUEST_STATUS_INCOMPLETE && !player->IsInCombat())
                {
                    if (me->GetCreatureTemplate()->GossipMenuId == sender && !action)
                    {
                        _events.ScheduleEvent(EVENT_INTRO, 1000);
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    }
                }
            }

            void UpdateAI(uint32 diff) override
            {
                _events.Update(diff);

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_INTRO:
                        {
                            Talk(SAY_DHAKAR_START);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);

                            if (Creature* morbidus = me->FindNearestCreature(NPC_MORBIDUS, 50.0f, true))
                            {
                                if (Creature* lichKing = me->SummonCreature(NPC_LICH_KING, morbidus->GetPositionX() + 10.0f, morbidus->GetPositionY(), morbidus->GetPositionZ()))
                                {
                                    _lichKingGuid = lichKing->GetGUID();
                                    lichKing->SetFacingTo(morbidus->GetOrientation());
                                    lichKing->CastSpell(lichKing, SPELL_SIMPLE_TELEPORT, true);
                                }
                            }

                            _events.ScheduleEvent(EVENT_LK_SAY_1, 5000);
                            break;
                        }
                        case EVENT_LK_SAY_1:
                        {
                            if (Creature* lichKing = ObjectAccessor::GetCreature(*me, _lichKingGuid))
                                lichKing->AI()->Talk(SAY_LK_1);
                            _events.ScheduleEvent(EVENT_LK_SAY_2, 5000);
                            break;
                        }
                        case EVENT_LK_SAY_2:
                        {
                            if (Creature* lichKing = ObjectAccessor::GetCreature(*me, _lichKingGuid))
                                lichKing->AI()->Talk(SAY_LK_2);
                            _events.ScheduleEvent(EVENT_LK_SAY_3, 5000);
                            break;
                        }
                        case EVENT_LK_SAY_3:
                        {
                            if (Creature* lichKing = ObjectAccessor::GetCreature(*me, _lichKingGuid))
                                lichKing->AI()->Talk(SAY_LK_3);
                            _events.ScheduleEvent(EVENT_LK_SAY_4, 5000);
                            break;
                        }
                        case EVENT_LK_SAY_4:
                        {
                            if (Creature* lichKing = ObjectAccessor::GetCreature(*me, _lichKingGuid))
                                lichKing->AI()->Talk(SAY_LK_4);
                            _events.ScheduleEvent(EVENT_OUTRO, 12000);
                            break;
                        }
                        case EVENT_LK_SAY_5:
                        {
                            if (Creature* lichKing = ObjectAccessor::GetCreature(*me, _lichKingGuid))
                                lichKing->AI()->Talk(SAY_LK_5);
                            _events.ScheduleEvent(EVENT_OUTRO, 8000);
                            break;
                        }
                        case EVENT_OUTRO:
                        {
                            if (Creature* olakin = me->FindNearestCreature(NPC_OLAKIN, 50.0f, true))
                                olakin->AI()->Talk(SAY_OLAKIN_PAY);

                            if (Creature* lichKing = ObjectAccessor::GetCreature(*me, _lichKingGuid))
                                lichKing->DespawnOrUnsummon(0);

                            _events.ScheduleEvent(EVENT_START, 5000);
                            break;
                        }
                        case EVENT_START:
                        {
                            if (Creature* morbidus = me->FindNearestCreature(NPC_MORBIDUS, 50.0f, true))
                            {
                                morbidus->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_DISABLE_MOVE);
                                morbidus->setFaction(FACTION_HOSTILE);
                            }

                            break;
                        }
                    }
                }

                DoMeleeAttackIfReady();
            }

        private:
            EventMap _events;
            SummonList _summons;
            uint64 _lichKingGuid;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_margrave_dhakarAI(creature);
    }
};

class npc_morbidus : public CreatureScript
{
    public:
        npc_morbidus() : CreatureScript("npc_morbidus") { }

        struct npc_morbidusAI : public ScriptedAI
        {
            npc_morbidusAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() override
            {
                if (Creature* dhakar = me->FindNearestCreature(NPC_DHAKAR, 50.0f, true))
                    dhakar->AI()->Reset();

                // this will prevent the event to start without morbidus being alive
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                me->setFaction(FACTION_BASIC);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_morbidusAI(creature);
        }
};

void AddSC_icecrown()
{
    new npc_squire_david();
    new npc_argent_valiant();
    new npc_argent_champion();
    new npc_guardian_pavilion();
    new npc_vereth_the_cunning();
    new npc_tournament_training_dummy();
    new npc_blessed_banner();
    new npc_frostbrood_skytalon();
    new npc_margrave_dhakar();
    new npc_morbidus();
    new npc_faction_champion();
    new npc_faction_valiant();
    new npc_boneguard_commander();    
    new npc_vendor_argent_tournament(); //sell only to its race or those who had completed valiant chain for its race
    new npc_training_dummy_argent(); //for mastery of ...
    new npc_valis_windchaser(); //for mastery of ...
    new npc_rugan_steelbelly(); //for mastery of ...
    new npc_jeran_lockwood(); //for mastery of ...
    new npc_squire_danny();  //summons argent champion
    new npc_maloric(); // There's Something About the Squire
    new vehicle_knight_gryphon();
    new npc_black_knight_argent();
    new npc_squire_cavin();
    new spell_defend();
 }


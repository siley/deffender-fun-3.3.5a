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

/*
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "npc_pet_mag_".
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "CombatAI.h"
#include "Pet.h"

enum MageSpells
{
    SPELL_MAGE_CLONE_ME                 = 45204,
    SPELL_MAGE_MASTERS_THREAT_LIST      = 58838
};

class npc_pet_mage_mirror_image : public CreatureScript
{
    public:
        npc_pet_mage_mirror_image() : CreatureScript("npc_pet_mage_mirror_image") { }

        struct npc_pet_mage_mirror_imageAI : CasterAI
        {
            npc_pet_mage_mirror_imageAI(Creature* creature) : CasterAI(creature) { }

            void InitializeAI() override
            {
                CasterAI::InitializeAI();
                Unit* owner = me->GetOwner();
                if (!owner)
                    return;
                // Inherit Master's Threat List (not yet implemented)
                owner->CastSpell((Unit*)NULL, SPELL_MAGE_MASTERS_THREAT_LIST, true);
                // here mirror image casts on summoner spell (not present in client dbc) 49866
                // here should be auras (not present in client dbc): 35657, 35658, 35659, 35660 selfcast by mirror images (stats related?)
                // Clone Me!
                owner->CastSpell(me, SPELL_MAGE_CLONE_ME, false);

                if (owner->ToPlayer() && owner->ToPlayer()->GetSelectedUnit())
                    me->AI()->AttackStart(owner->ToPlayer()->GetSelectedUnit());
            }

            void EnterCombat(Unit* who)
            {
                if (spells.empty())
                    return;

                for (SpellVct::iterator itr = spells.begin(); itr != spells.end(); ++itr)
                {
                    if (AISpellInfo[*itr].condition == AICOND_AGGRO)
                        me->CastSpell(who, *itr, false);
                    else
                    if (AISpellInfo[*itr].condition == AICOND_COMBAT)
                    {
                        uint32 cooldown = GetAISpellInfo(*itr)->realCooldown;
                        events.ScheduleEvent(*itr, cooldown);
                    }
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                bool hasCC = false;
                if (me->GetCharmerOrOwnerGUID() && me->GetVictim())
                    hasCC = me->GetVictim()->HasAuraType(SPELL_AURA_MOD_CONFUSE);

                if (hasCC)
                {
                    if (me->HasUnitState(UNIT_STATE_CASTING))
                        me->CastStop();
                    me->AI()->EnterEvadeMode();
                    return;
                }

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (uint32 spellId = events.ExecuteEvent())
                {
                    if (hasCC)
                    {
                        events.ScheduleEvent(spellId, 500);
                        return;
                    }

                    DoCast(spellId);
                    uint32 casttime = me->GetCurrentSpellCastTime(spellId);
                    events.ScheduleEvent(spellId, (casttime ? casttime : 500) + GetAISpellInfo(spellId)->realCooldown);

                }
            }

            // Do not reload Creature templates on evade mode enter - prevent visual lost
            void EnterEvadeMode() override
            {
                if (me->IsInEvadeMode() || !me->IsAlive())
                    return;

                Unit* owner = me->GetCharmerOrOwner();

                me->CombatStop(true);
                if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
                {
                    me->GetMotionMaster()->Clear(false);
                    me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle(), MOTION_SLOT_ACTIVE);
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_pet_mage_mirror_imageAI(creature);
        }
};

void AddSC_mage_pet_scripts()
{
    new npc_pet_mage_mirror_image();
}

#include "ScriptPCH.h"
#include "ScriptedCreature.h"
#include "GameObjectAI.h"
#include "LFGMgr.h"
#include "Player.h"
#include "Group.h"

class npc_trigger_ribbon : public CreatureScript
{
public:
    npc_trigger_ribbon() : CreatureScript("npc_trigger_ribbon") { }

    struct npc_trigger_ribbonAI : public ScriptedAI
    {
        npc_trigger_ribbonAI(Creature* creature) : ScriptedAI(creature) {}

		uint32 PersonasBailando;
		uint32 TimeOuA;
		uint32 TimeOuB;
		uint32 TimeOuC;

        void Reset()
        {
            PersonasBailando = 0;
			TimeOuA = 30000;
			TimeOuB = 40000;
			TimeOuC = 4000;
           
        }
  
 void ComenzandoBaile(bool modificador, Unit* player)
	 {
		if(modificador)
		{
                ++PersonasBailando;
            if(PersonasBailando == 1)
			    TimeOuA = 30000;
			else if(PersonasBailando == 2){
			    TimeOuA = 2000;
			    TimeOuB = 40000;}
			else if(PersonasBailando > 2 && PersonasBailando < 6){
				TimeOuA = 2000;
				TimeOuB = 25000; }
			else if(PersonasBailando > 5 && PersonasBailando < 11){
			    TimeOuA = 1000;
				TimeOuB = 5000;
			    TimeOuC = 3000;}
			else if(PersonasBailando > 10){
                TimeOuA = 500;
				TimeOuB = 5000;
			    TimeOuC = 3000;
		}


       if(PersonasBailando < 11)
		 {
			    player->CastSpell(me,40071,true);
				player->CastSpell(player,62192,false);
		 }else
		 {
              switch (urand(0, 1))
                    {
                        case 0:
							player->CastSpell(me,40071,true);
							player->CastSpell(player,62192,false);
                          break;
                        case 1:
	                        	player->CastSpell(me,45421,true);
								player->CastSpell(player,62192,false);
	                      break;
		            }
		 }
            
		}
		else
		{
		     if(PersonasBailando > 0)
			    --PersonasBailando;


			if(PersonasBailando == 1)
			    TimeOuA = 30000;
			else if(PersonasBailando == 2){
			    TimeOuA = 2000;
			    TimeOuB = 40000;}
			else if(PersonasBailando > 2 && PersonasBailando < 6){
				TimeOuA = 2000;
				TimeOuB = 25000; }
			else if(PersonasBailando > 5 && PersonasBailando < 11){
			    TimeOuA = 1000;
				TimeOuB = 5000;
			    TimeOuC = 3000;}
			else if(PersonasBailando > 10){
                TimeOuA = 500;
				TimeOuB = 5000;
			    TimeOuC = 3000;
	    }
   }
}


	   void UpdateAI(uint32 diff) override
	   {	

     if (PersonasBailando == 1)
      {
        if (TimeOuA <= diff)
		  {
			  me->CastSpell(me,46847,true);
              TimeOuA = 4000;
          } else TimeOuA-= diff;
       }
    else if (PersonasBailando == 2)
       {
        if (TimeOuA <= diff)
		  {
			  me->CastSpell(me,46847,true);
              TimeOuA = 3000;
          } else TimeOuA-= diff;

        if (TimeOuB <= diff)
		  {
			  me->CastSpell(me,46969,true);
              TimeOuB = 37000;
          } else TimeOuB-= diff;
       }
else if (PersonasBailando > 2 && PersonasBailando < 6)
{
if (TimeOuA <= diff)
		  {
			  me->CastSpell(me,46847,true);
              TimeOuA = 2700;
          } else TimeOuA-= diff;

if (TimeOuB <= diff)
		  {
			  me->CastSpell(me,46969,true);
              TimeOuB = 25000;
          } else TimeOuB-= diff;
}
else if (PersonasBailando > 5 && PersonasBailando < 11)
{
if (TimeOuA <= diff)
		  {
			  me->CastSpell(me,46847,true);
              TimeOuA = 1800;
          } else TimeOuA-= diff;

if (TimeOuB <= diff)
		  {
			  me->CastSpell(me,46969,true);
              TimeOuB = 22000;
          } else TimeOuB-= diff;
	
if (TimeOuC <= diff)
		  {
			  me->CastSpell(me,37099,true);
              TimeOuC = 7000;
          } else TimeOuC-= diff;

}
else if (PersonasBailando > 10)
{
if (TimeOuA <= diff)
		  {
			  me->CastSpell(me,46847,true);
              TimeOuA = 800;
          } else TimeOuA-= diff;

if (TimeOuB <= diff)
		  {
			  me->CastSpell(me,46969,true);
              TimeOuB = 20000;
          } else TimeOuB-= diff;
	
if(PersonasBailando > 10 && PersonasBailando < 15)
{
if (TimeOuC <= diff)
		  {
			  me->CastSpell(me,37099,true);
              TimeOuC = 3000;
          } else TimeOuC-= diff;
}
else{
if (TimeOuC <= diff)
		  {
			  me->CastSpell(me,37099,true);
              TimeOuC = 900;
          } else TimeOuC-= diff;
}
    }
	   }
	};

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_trigger_ribbonAI(creature);
    }
};


enum RibbonPoleData
{
    SPELL_HAS_FULL_MIDSUMMER_SET = 58933,
    SPELL_BURNING_HOT_POLE_DANCE = 58934,
    SPELL_RIBBON_DANCE = 29175,
    GO_RIBBON_POLE = 181605,
};

class spell_gen_ribbon_pole_dancer_check : public SpellScriptLoader
{
    public:
        spell_gen_ribbon_pole_dancer_check() : SpellScriptLoader("spell_gen_ribbon_pole_dancer_check") { }

        class spell_gen_ribbon_pole_dancer_check_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_ribbon_pole_dancer_check_AuraScript);

            bool Validate(SpellInfo const* /*spell*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_HAS_FULL_MIDSUMMER_SET) || !sSpellMgr->GetSpellInfo(SPELL_BURNING_HOT_POLE_DANCE) || !sSpellMgr->GetSpellInfo(SPELL_RIBBON_DANCE))
                    return false;
                return true;
/*
                if (!sSpellStore.LookupEntry(SPELL_HAS_FULL_MIDSUMMER_SET))
                    return false;
                if (!sSpellStore.LookupEntry(SPELL_BURNING_HOT_POLE_DANCE))
                    return false;
                if (!sSpellStore.LookupEntry(SPELL_RIBBON_DANCE))
                    return false;
                return true;
*/
            }

            void PeriodicTick(AuraEffect const* /*aurEff*/)
            {
                Unit* target = GetTarget();

                if (!target)
                    return;


                 if(!target->GetAura(40227) && !target->GetAura(40228) && !target->GetAura(40071) && !target->GetAura(62192))
				 {
				if (Creature* Ribbon_trigger = target->FindNearestCreature(17066, 15.0f))
	              CAST_AI(npc_trigger_ribbon::npc_trigger_ribbonAI, Ribbon_trigger->AI())->ComenzandoBaile(true, target);

 
				 }

                
                if (!target->FindNearestGameObject(GO_RIBBON_POLE, 10.0f) || !target->HasUnitState(UNIT_STATE_CASTING))
                {
                    target->InterruptNonMeleeSpells(false);
                    target->RemoveAurasDueToSpell(GetId());

				if (Creature* Ribbon_trigger = target->FindNearestCreature(17066, 70.0f))
                    CAST_AI(npc_trigger_ribbon::npc_trigger_ribbonAI, Ribbon_trigger->AI())->ComenzandoBaile(false, target);
				 target->RemoveAurasDueToSpell(40227);
				 target->RemoveAurasDueToSpell(40228);
				 target->RemoveAurasDueToSpell(40071);
				 target->RemoveAurasDueToSpell(62192);
				 target->RemoveAurasDueToSpell(45421);
				 


                    return;
                }

           
                if (Aura* aur = target->GetAura(SPELL_RIBBON_DANCE))
                {
                    aur->SetMaxDuration(aur->GetMaxDuration() >= 3600000 ? 3600000 : aur->GetMaxDuration() + 180000);
                    aur->RefreshDuration();

        
                    if (aur->GetMaxDuration() == 3600000 && target->HasAura(SPELL_HAS_FULL_MIDSUMMER_SET))
                        target->CastSpell(target, SPELL_BURNING_HOT_POLE_DANCE, true);
                }
                else
                    target->AddAura(SPELL_RIBBON_DANCE, target);
            }

            void Register() override
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_gen_ribbon_pole_dancer_check_AuraScript::PeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_gen_ribbon_pole_dancer_check_AuraScript();
        }
};

class npc_trigger_torch_mal : public CreatureScript
{
public:
    npc_trigger_torch_mal() : CreatureScript("npc_trigger_torch_mal") { }

    struct npc_trigger_torch_malAI : public ScriptedAI
    {
        npc_trigger_torch_malAI(Creature* creature) : ScriptedAI(creature) {}

		uint32 timercount;
		bool CountAcept;

 void Reset()
        {
 CountAcept = false;
 }

 Creature* GetRandomEntryTarget(uint32 entry, float range = 100.0f)
        {
            std::list<Creature*> TargetList;
            me->GetCreatureListWithEntryInGrid(TargetList,entry, range);
            if(TargetList.empty())
                return NULL;

            std::list<Creature*>::iterator itr = TargetList.begin();
            advance(itr, urand(0, TargetList.size()-1));
			
            return (*itr);
        }



 void Selection(bool type, Unit* plr)
	   {
	if(Creature* trigg = me->FindNearestCreature(90028,1))
        {
			if(plr){
				if(me->GetDistance2d(plr) <= 2){
					if (Aura* aura = plr->GetAura(45693)){
				        if(plr->GetTypeId() == TYPEID_PLAYER){
						  if(aura){
							  if ((aura->GetStackAmount() == 4) && (plr->ToPlayer()->GetQuestStatus(11923) == QUEST_STATUS_INCOMPLETE || plr->ToPlayer()->GetQuestStatus(11657) == QUEST_STATUS_INCOMPLETE)){
					             if(plr->ToPlayer()->GetQuestStatus(11923) == QUEST_STATUS_INCOMPLETE)
									  plr->ToPlayer()->CompleteQuest(11923);
								 if(plr->ToPlayer()->GetQuestStatus(11657) == QUEST_STATUS_INCOMPLETE)
									  plr->ToPlayer()->CompleteQuest(11657);

								 plr->PlayDirectSound(12340);
						         plr->RemoveAurasDueToSpell(45693);
							  }
							  else if ((aura->GetStackAmount() == 10) && (plr->ToPlayer()->GetQuestStatus(11925) == QUEST_STATUS_INCOMPLETE || plr->ToPlayer()->GetQuestStatus(11924) == QUEST_STATUS_INCOMPLETE)){
                                  if(plr->ToPlayer()->GetQuestStatus(11925) == QUEST_STATUS_INCOMPLETE)
									  plr->ToPlayer()->CompleteQuest(11925);
								 if(plr->ToPlayer()->GetQuestStatus(11924) == QUEST_STATUS_INCOMPLETE)
									  plr->ToPlayer()->CompleteQuest(11924);

								 plr->PlayDirectSound(12340);
						         plr->RemoveAurasDueToSpell(45693);
							  }
							  else{

					  if(Unit* target = GetRandomEntryTarget(90028,35.0f))
						  plr->CastSpell(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 45669, true); 

                          plr->CastSpell(plr,45693,true);			
							  }}}}
					             else{
								  if(Unit* target = GetRandomEntryTarget(90028,35.0f))
						  plr->CastSpell(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 45669, true); 

                          plr->CastSpell(plr,45693,true);	
							  }}
}
	}
	else
	{
      if(type)
      {
          if (Unit* target = me->FindNearestPlayer(1.0f, true))
         target->CastSpell(target,45280,true);
         me->DespawnOrUnsummon(500);
}
else
{
	timercount = urand(1500, 2000);
	CountAcept = true;
	me->DespawnOrUnsummon(4000);
}
 }
 }


	   void UpdateAI(uint32 diff) override
	   {	
if(CountAcept)
{
	if (timercount <= diff)
		  {
 if (Unit* target =  me->FindNearestPlayer(1.0f, true))
     target->CastSpell(target,45280,true);
           me->DespawnOrUnsummon(500);
			  
		   CountAcept = false;

       } else timercount-= diff;
}}

	};
	    
	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_trigger_torch_malAI(creature);
    }
};

class spell_gen_antorchas_logr : public SpellScriptLoader
{
    public:
        spell_gen_antorchas_logr() : SpellScriptLoader("spell_gen_antorchas_logr") {}

        class spell_gen_antorchas_logr_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_antorchas_logr_SpellScript);
            
			bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(45638))
                    return false;
				if (!sSpellMgr->GetSpellInfo(45669))
                    return false;
				
 
                return true;
            }

 void HandleOnCast()
            {
	
	const WorldLocation* pos = GetExplTargetDest();
  
	if(GetCaster()->GetDistance2d(pos->GetPositionX(), pos->GetPositionY()) <= 1.5)
	{
    GetCaster()->CastSpell(GetCaster(), 45638, true); //45638
if (Creature* triggerAntor = GetCaster()->SummonCreature(90027, GetCaster()->GetPositionX(), GetCaster()->GetPositionY(), GetCaster()->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000))
	   CAST_AI(npc_trigger_torch_mal::npc_trigger_torch_malAI, triggerAntor->AI())->Selection(false,GetCaster());

	}
	else
 GetCaster()->CastSpell(pos->GetPositionX(), pos->GetPositionY(), pos->GetPositionZ(), 45669, true); //45638

             }
 

            void Register()
            {
				OnCast += SpellCastFn(spell_gen_antorchas_logr_SpellScript::HandleOnCast);
            }

        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_antorchas_logr_SpellScript();
        }
};

class spell_gen_lanz_antor_logro: public SpellScriptLoader
{
    public:
        spell_gen_lanz_antor_logro() : SpellScriptLoader("spell_gen_lanz_antor_logro") {}

        class spell_gen_lanz_antor_logro_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_lanz_antor_logro_SpellScript);

			bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(45638))
                    return false;
 
                return true;
            }

 void HandleOnCast()
   {	
	const WorldLocation* pos = GetExplTargetDest();
  
	if (Creature* triggerAntor = GetCaster()->SummonCreature(90027, pos->GetPositionX(), pos->GetPositionY(), pos->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000))
	   CAST_AI(npc_trigger_torch_mal::npc_trigger_torch_malAI, triggerAntor->AI())->Selection(true,GetCaster());
            }

            void Register()
            {
				OnCast += SpellCastFn(spell_gen_lanz_antor_logro_SpellScript::HandleOnCast);
            }
		};

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_lanz_antor_logro_SpellScript();
        }
};




class spell_blandones_golpeados_qcredit: public SpellScriptLoader
{
    public:
        spell_blandones_golpeados_qcredit() : SpellScriptLoader("spell_blandones_golpeados_qcredit") {}

        class spell_blandones_golpeados_qcredit_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_blandones_golpeados_qcredit_SpellScript);


						bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(45716))
                    return false;
 
                return true;
            }

 void HandleOnHit()
            {

               Unit* target = GetHitUnit();

				if (!target->HasAura(45716) && !target->HasAura(46630))
					 target->RemoveAurasDueToSpell(45724);
				else{

				if (Aura* aura = target->GetAura(45724))
					   {
				  if(target->GetTypeId() == TYPEID_PLAYER)
				   {
                if (aura && aura->GetStackAmount() == 8)
				{
				  
					  if(target->ToPlayer()->GetQuestStatus(11922) == QUEST_STATUS_INCOMPLETE){
                        target->ToPlayer()->CompleteQuest(11922);
						target->PlayDirectSound(12340);
						target->RemoveAurasDueToSpell(45724);}
					  else if (target->ToPlayer()->GetQuestStatus(11731) == QUEST_STATUS_INCOMPLETE){
						target->ToPlayer()->CompleteQuest(11731);
						target->PlayDirectSound(12340);
						target->RemoveAurasDueToSpell(45724);}
				  }
                else if (aura && aura->GetStackAmount() == 20)
				{
				  
					  if(target->ToPlayer()->GetQuestStatus(11926) == QUEST_STATUS_INCOMPLETE){
                        target->ToPlayer()->CompleteQuest(11926);
						target->PlayDirectSound(12340);
						target->RemoveAurasDueToSpell(45724);}
					  else if (target->ToPlayer()->GetQuestStatus(11921) == QUEST_STATUS_INCOMPLETE){
						target->ToPlayer()->CompleteQuest(11921);
						target->PlayDirectSound(12340);
						target->RemoveAurasDueToSpell(45724);}
				  }

  
				}
					   }
				}}
      

            void Register()
            {
               OnHit += SpellHitFn(spell_blandones_golpeados_qcredit_SpellScript::HandleOnHit);
			}

           
		};

        SpellScript* GetSpellScript() const
        {
            return new spell_blandones_golpeados_qcredit_SpellScript();
        }
};



class spell_ev_antorchas_quest : public SpellScriptLoader
{
    public:
        spell_ev_antorchas_quest() : SpellScriptLoader("spell_ev_antorchas_quest") {}

        class spell_ev_antorchas_quest_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ev_antorchas_quest_SpellScript);
            
			bool Validate(SpellInfo const* /*spellEntry*/)
            {
				if (!sSpellMgr->GetSpellInfo(45669))
                    return false;
				if (!sSpellMgr->GetSpellInfo(45693))
                    return false;
				
                return true;
            }

	Creature* GetRandomEntryTarget(uint32 entry, float range = 100.0f)
        {
            std::list<Creature*> TargetList;
            GetCaster()->GetCreatureListWithEntryInGrid(TargetList,entry, range);
            if(TargetList.empty())
                return NULL;

            std::list<Creature*>::iterator itr = TargetList.begin();
            advance(itr, urand(0, TargetList.size()-1));
            return (*itr);
        }


 void HandleOnCast()
            {

				if (GetCaster()->HasAura(45693))
					 GetCaster()->RemoveAurasDueToSpell(45693);

	if(Unit* target = GetRandomEntryTarget(90028,35.0f))
 GetCaster()->CastSpell(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 45669, true); 

             }
 

            void Register()
            {
				OnCast += SpellCastFn(spell_ev_antorchas_quest_SpellScript::HandleOnCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ev_antorchas_quest_SpellScript();
        }
};


#define GOSSIP_LOG "Ya he conseguido las llamas de todas las ciudades."

class npc_achievement_llamas_ciudades : public CreatureScript
{
public:
    npc_achievement_llamas_ciudades() : CreatureScript("npc_achievement_llamas_ciudades") { }


  bool OnGossipHello(Player* player, Creature* creature)
    {
 if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());


  if (player->GetQuestRewardStatus(9325) && player->GetQuestRewardStatus(9326) && player->GetQuestRewardStatus(11935) && player->GetQuestRewardStatus(9324) && !player->HasAchieved(1145))
      player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOG, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

  if (player->GetQuestRewardStatus(9332) && player->GetQuestRewardStatus(11933) && player->GetQuestRewardStatus(9331) && player->GetQuestRewardStatus(9330) && !player->HasAchieved(1145))
      player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOG, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
  return true;
  }

     bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF+1)
        {
			        ItemPosCountVec dest;
                    uint8 canStoreNewItem = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 23323, 1);
                    if(canStoreNewItem == EQUIP_ERR_OK)
                    {
                        Item *newItem = NULL;
                        newItem = player->StoreNewItem(dest,23323,1,true);
                        player->SendNewItem(newItem,1,true,false);

					AchievementEntry const* Logro = sAchievementStore.LookupEntry(1145);
                    player->CompletedAchievement(Logro);  
                    }

			 player->CLOSE_GOSSIP_MENU();
        }
        return true;
    }
};


#include "CreatureTextMgr.h"

class npc_midsummer_music : public CreatureScript
{
public:
    npc_midsummer_music() : CreatureScript("npc_midsummer_music") { }

    struct npc_midsummer_musicAI : public ScriptedAI
    {
        npc_midsummer_musicAI(Creature* creature) : ScriptedAI(creature) {}

		uint32 MusicCounter;

          void Reset()
              {
				  MusicCounter = 3000;
				
		       }



	   void UpdateAI(uint32 diff) override
	   {	

	   if (MusicCounter <= diff)
		  {
			   switch (me->GetEntry())
            {
                case 90029:
                   //SendMusicToPlayers(12325);
				   sCreatureTextMgr->SendSound(me, 12325, CHAT_MSG_MONSTER_YELL, 0, TEXT_RANGE_NORMAL, TEAM_OTHER, false);
                    break;

				 case 90030:
                   //SendMusicToPlayers(12319);
				    sCreatureTextMgr->SendSound(me, 12319, CHAT_MSG_MONSTER_YELL, 0, TEXT_RANGE_NORMAL, TEAM_OTHER, false);
                    break;
			   }
			  
		   MusicCounter = 4000;

       } else MusicCounter -= diff;
	   
	   }


	};
	    
	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_midsummer_musicAI(creature);
    }
};

enum Creatures
{
    NPC_AHUNE = 25740,
    NPC_FROZEN_CORE = 25865,
    NPC_AHUNITE_COLDWEAVE = 25756,
    NPC_AHUNITE_FROSTWIND = 25757,
    NPC_AHUNITE_HAILSTONE = 25755,
    NPC_SLIPPERY_FLOOR = 25952,
    NPC_ICESPEAR_BUNNY = 25985,
    NPC_EARTHEN_RING_TOTEM = 25961,
    NPC_AHUNE_GHOST = 26239,
};

enum GameObjects
{
    GO_ICE_STONE = 187882,
    GO_ICE_SPEAR = 188077,
    GO_ICE_CHEST = 187892,
};

enum Spells
{
    // Ahune
    SPELL_AHUNES_SHIELD = 45954,
    SPELL_COLD_SLAP = 46145,

    SPELL_ICESPEAR_SUMMON_BUNNY = 46359,
    SPELL_ICESPEAR_SUMMON_GO = 46369,
    SPELL_ICESPEAR_KNOCKBACK = 46360, // also triggers dmg

    SPELL_MAKE_BONFIRE = 45930,
    SPELL_SUMMONING_VISUAL1 = 45937, // below Ahune (?)
    SPELL_SUMMONING_VISUAL2 = 45938, // below the Summoning Stone (?)
    SPELL_SUMMON_MINION_VISUAL = 46103, // Midsummer - Ahune - Summon Minion, Lower
    SPELL_GHOST_VISUAL = 46786,
    SPELL_RESURFACE = 46402, // Ahune Resurfaces
    SPELL_SLIPPERY_FLOOR_AMBIENT = 46314,
    SPELL_AHUNE_SUMMON_RHYME = 45926,

    SPELL_LOOT_CHEST = 45939,
    SPELL_LOOT_CHEST_HC = 46622,

    SPELL_AHUNE_ACHIEVEMENT = 62043, // Midsummer - Ahune - DIES, Achievement (Visual, no credit)

    // Totem
    SPELL_BEAM_ATTACK = 46336, // Earthen Ring Totem Attack Visuals
    SPELL_BEAM_ATTACK_BEAM = 46363,

    // Coldweave
    SPELL_BITTER_BLAST = 46406,

    // Frostwind
    SPELL_LIGHTNING_SHIELD = 12550,
    SPELL_WIND_BUFFET = 46568,

    // Hailstone
    SPELL_CHILLING_AURA = 46542, // damage tick
    SPELL_CHILLING_AURA_PERIODIC = 46885, // periodic trigger (yet to be scripted..., we use it as visual for now)
    SPELL_PULVERIZE = 2676,
};

enum Events
{
    // Ahune
    EVENT_SWITCH_PHASE = 1,
    EVENT_SUMMON_HAILSTONE = 2,
    EVENT_SUMMON_COLDWEAVE = 3,
    EVENT_SUMMON_FROSTWIND = 4,
    EVENT_ICE_SPEAR = 5,
    EVENT_ICE_SPEAR_KNOCKBACK = 6,
    EVENT_COLD_SLAP = 7,

    // Frozen Core
    EVENT_GHOST_VISUAL = 8,
    EVENT_RESURFACE_SOON = 9,

    // Coldweave
    EVENT_BITTER_BLAST = 10,

    // Frostwind
    EVENT_WIND_BUFFET = 11,

    // Hailstone
    EVENT_CHILLING_AURA = 12,
    EVENT_PULVERIZE = 13,

    // Visual Stuff
    EVENT_EARTHEN_RING_ATTACK = 14,
};

enum Phases
{
    PHASE_ONE = 1,
    PHASE_TWO = 2,

    //PHASE_MASK_ONE  = 1 << PHASE_ONE,
    //PHASE_MASK_TWO  = 1 << PHASE_TWO,
};

#define GOSSIP_AHUNE_SUMMON "Disturb the Stone and summon Lord Ahune."
#define EMOTE_SUBMERGE "Ahune Retreats. His Defenses Diminish."
#define EMOTE_EMERGE_SOON "Ahune will soon resurface."

// After GOSSIP_SUMMON was clicked
// Player says: The Ice stone has melted.
// Player says: Ahune, your strength grows no more!
// Player says: Your frozen reign will not come to pass!

Position const SummonPositions[4] =
{
    { -88.495071f, -254.462997f, -1.077302f, 1.84f }, // Ahune / Frozen-Core
    { -90.891891f, -243.488068f, -1.116222f, 1.84f }, // Hailstone
    { -97.389175f, -239.780701f, -1.264044f, 1.84f }, // Coldweave #1
    { -85.160637f, -236.127808f, -1.572418f, 1.84f }, // Coldweave #2
};

class boss_ahune : public CreatureScript
{
public:
    boss_ahune() : CreatureScript("boss_ahune") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ahuneAI(creature);
    }

    struct boss_ahuneAI : public ScriptedAI
    {
        boss_ahuneAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            SetCombatMovement(false);
        }

        EventMap events;
        SummonList summons;

        bool intro;

        void Reset()
        {
            me->AddAura(SPELL_AHUNES_SHIELD, me);

            summons.DespawnAll();

            events.Reset();
            events.SetPhase(PHASE_ONE);

            intro = false;

            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK_DEST, true);

            me->CastSpell(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), SPELL_SUMMONING_VISUAL1, true);
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
        }

        void EnterCombat(Unit* /*who*/)
        {
            //DoZoneInCombat();
            me->SetInCombatWithZone();

            events.Reset();
            events.SetPhase(PHASE_ONE);
            events.ScheduleEvent(EVENT_SWITCH_PHASE, 90000); // phase 2 after 90 seconds
            events.ScheduleEvent(EVENT_COLD_SLAP, 500, 0, PHASE_ONE); // every 500ms in melee range in phase 1
            events.ScheduleEvent(EVENT_SUMMON_HAILSTONE, 1000, 0, PHASE_ONE); // once in every phase 1
            events.ScheduleEvent(EVENT_SUMMON_COLDWEAVE, 8000, 0, PHASE_ONE); // every 7 seconds in phase 1
            events.ScheduleEvent(EVENT_ICE_SPEAR, 9500, 0, PHASE_ONE); // every 7 seconds in phase 1, first after 9.5 seconds
            events.ScheduleEvent(EVENT_EARTHEN_RING_ATTACK, 10000, 0, PHASE_ONE); // every 10 seconds in phase 1 totem attack visual
        }

        void JustDied(Unit* /*killer*/)
        {
            Map::PlayerList const& playerList = me->GetMap()->GetPlayers();
            if (!playerList.isEmpty())
            {
                for (Map::PlayerList::const_iterator i = playerList.begin(); i != playerList.end(); ++i)
                if (Player* player = i->GetSource())
                    DoCast(player, SPELL_AHUNE_ACHIEVEMENT);

                if (Group* group = playerList.begin()->GetSource()->GetGroup())
                if (group->isLFGGroup())
                    sLFGMgr->FinishDungeon(group->GetGUID(), 286);

            }

            summons.DespawnAll();
            DoCast(me, SPELL_LOOT_CHEST);
        }

        void JustSummoned(Creature* summoned)
        {
            summons.Summon(summoned);

            switch (summoned->GetEntry())
            {
            case NPC_ICESPEAR_BUNNY:
                summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_DISABLE_MOVE);
                break;
            case NPC_SLIPPERY_FLOOR:
                summoned->SetReactState(REACT_PASSIVE);
                summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_DISABLE_MOVE);
                summoned->SetDisplayId(11686);
                me->AddAura(SPELL_SLIPPERY_FLOOR_AMBIENT, summoned);
                return;
            case NPC_FROZEN_CORE:
                summoned->SetMaxHealth(me->GetMaxHealth());
                summoned->SetInCombatWithZone();
                summoned->SetHealth(me->GetHealth()); // sync health on phase change
                break;
            }

            DoZoneInCombat(summoned);
        }

        void SummonedCreatureDespawn(Creature* summoned)
        {
            summons.Despawn(summoned);
        }

        void UpdateAI(uint32 diff)
        {
            if (!intro)
            {
                me->SummonCreature(NPC_SLIPPERY_FLOOR, SummonPositions[0]); // floor ambient
                me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                me->SetReactState(REACT_AGGRESSIVE);
                intro = true;
            }

            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SWITCH_PHASE:
                    if (events.GetPhaseMask() & PHASE_ONE)
                    {
                        // Emote: Ahune retreats. His defenses diminish.
                        me->MonsterTextEmote(EMOTE_SUBMERGE, 0, true);


                        events.SetPhase(PHASE_TWO);
                        events.ScheduleEvent(EVENT_SWITCH_PHASE, 40000);
                        events.ScheduleEvent(EVENT_GHOST_VISUAL, 10000);
                        events.ScheduleEvent(EVENT_GHOST_VISUAL, 20000);
                        events.ScheduleEvent(EVENT_GHOST_VISUAL, 30000);

                        me->CastSpell(me, SPELL_MAKE_BONFIRE);

                        // Handle Submerge. This is essentially a copy of how Ragnaros submerges... :) minus the threatwipe
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        me->setFaction(35);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->RemoveAurasDueToSpell(SPELL_AHUNES_SHIELD);
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_SUBMERGED);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_SUBMERGE);

                        // spawn core
                        me->SummonCreature(NPC_FROZEN_CORE, SummonPositions[0], TEMPSUMMON_CORPSE_DESPAWN);
                    }
                    else
                    {
                        events.SetPhase(PHASE_ONE);
                        events.ScheduleEvent(EVENT_SWITCH_PHASE, 95000);
                        events.ScheduleEvent(EVENT_COLD_SLAP, 500, 0, PHASE_ONE);
                        events.ScheduleEvent(EVENT_SUMMON_HAILSTONE, 1000, 0, PHASE_ONE);
                        events.ScheduleEvent(EVENT_SUMMON_COLDWEAVE, 8000, 0, PHASE_ONE);
                        events.ScheduleEvent(EVENT_SUMMON_FROSTWIND, 9000, 0, PHASE_ONE);
                        events.ScheduleEvent(EVENT_ICE_SPEAR, 9500, 0, PHASE_ONE);
                        events.ScheduleEvent(EVENT_EARTHEN_RING_ATTACK, 10000, 0, PHASE_ONE);

                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RestoreFaction();
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                        me->AddAura(SPELL_AHUNES_SHIELD, me);

                        me->CastSpell(me, SPELL_RESURFACE, true);

                        // despawn core
                        summons.DespawnEntry(NPC_FROZEN_CORE);
                    }
                    break;
                case EVENT_COLD_SLAP:
                    if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0, 8.0f, true))
                    {
                        DoCast(target, SPELL_COLD_SLAP);
                        Position targetPos = target->GetNearPosition(float(rand_norm()) * 5.0f + 35.0f, me->GetAngle(target));
                        //target->GetNearPosition(targetPos, float(rand_norm()) * 5.0f + 35.0f, me->GetAngle(target));
                        target->GetMotionMaster()->MoveJump(targetPos.GetPositionX(), targetPos.GetPositionY(), targetPos.GetPositionZ(), target->GetExactDist2d(targetPos.GetPositionX(), targetPos.GetPositionY()), 10.0f);
                    }
                    events.ScheduleEvent(EVENT_COLD_SLAP, 500, 0, PHASE_ONE);
                    break;
                case EVENT_ICE_SPEAR: // FIXME: should make use of all the proper spells...
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 120.0f, true))
                    {
                        target->CastSpell(target, SPELL_ICESPEAR_SUMMON_BUNNY);
                        target->CastSpell(target, SPELL_ICESPEAR_SUMMON_GO);
                        events.ScheduleEvent(EVENT_ICE_SPEAR_KNOCKBACK, 2000);
                    }
                    events.ScheduleEvent(EVENT_ICE_SPEAR, 7000, 0, PHASE_ONE);
                    break;
                case EVENT_ICE_SPEAR_KNOCKBACK:
                    if (GameObject* go = me->FindNearestGameObject(GO_ICE_SPEAR, 200.0f))
                    {
                        go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                        go->UseDoorOrButton();
                        Map::PlayerList const& playerList = me->GetMap()->GetPlayers();
                        if (!playerList.isEmpty())
                        for (Map::PlayerList::const_iterator i = playerList.begin(); i != playerList.end(); ++i)
                        if (i->GetSource() && go->GetDistance(i->GetSource()) <= 2.0f)
                            i->GetSource()->CastSpell(i->GetSource(), SPELL_ICESPEAR_KNOCKBACK);
                        go->Delete();
                    }
                    break;
                case EVENT_SUMMON_HAILSTONE:
                    me->SummonCreature(NPC_AHUNITE_HAILSTONE, SummonPositions[1], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                    break;
                case EVENT_SUMMON_COLDWEAVE: // they always come in pairs of two
                    me->SummonCreature(NPC_AHUNITE_COLDWEAVE, SummonPositions[2], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                    me->SummonCreature(NPC_AHUNITE_COLDWEAVE, SummonPositions[3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                    events.ScheduleEvent(EVENT_SUMMON_COLDWEAVE, 5000, 0, PHASE_ONE);
                    break;
                case EVENT_SUMMON_FROSTWIND: // not in first phase 1
                    me->SummonCreature(NPC_AHUNITE_FROSTWIND, SummonPositions[urand(2, 3)], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                    events.ScheduleEvent(EVENT_SUMMON_FROSTWIND, 7000, 0, PHASE_ONE);
                    break;
                case EVENT_EARTHEN_RING_ATTACK:
                    if (Creature* totem = me->FindNearestCreature(NPC_EARTHEN_RING_TOTEM, 200.0f))
                    {
                        totem->CastSpell(me, SPELL_BEAM_ATTACK, false);
                        totem->CastSpell(me, SPELL_BEAM_ATTACK_BEAM, false);
                    }
                    events.ScheduleEvent(EVENT_EARTHEN_RING_ATTACK, 10000, 0, PHASE_ONE);
                    break;
                case EVENT_GHOST_VISUAL:
                    if (Creature* ghost = me->SummonCreature(NPC_AHUNE_GHOST, SummonPositions[0], TEMPSUMMON_TIMED_DESPAWN, 3000))
                        ghost->CastSpell(ghost, SPELL_GHOST_VISUAL);
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

class npc_frozen_core : public CreatureScript
{
public:
    npc_frozen_core() : CreatureScript("npc_frozen_core") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_frozen_coreAI(creature);
    }

    struct npc_frozen_coreAI : public ScriptedAI
    {
        npc_frozen_coreAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
            events.ScheduleEvent(EVENT_RESURFACE_SOON, 25000); // after 25 seconds Emote: Ahune will soon resurface.

            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK_DEST, true);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE + UNIT_FLAG_NON_ATTACKABLE);
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (me->ToTempSummon())
            {
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                {
                    if (me->GetHealth() > damage)
                        summoner->SetHealth((summoner->GetMaxHealth() / 100) * me->GetHealthPct());
                    else
                        who->Kill(summoner);
                }
            }
        }

        void JustDied(Unit* killer)
        {
            if (me->ToTempSummon())
            if (Unit* summoner = me->ToTempSummon()->GetSummoner())
            if (summoner->IsAlive())
                killer->Kill(summoner);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_RESURFACE_SOON:
                    // Emote: Ahune will soon resurface.
                    me->MonsterTextEmote(EMOTE_EMERGE_SOON, 0, true);
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

class go_ice_stone : public GameObjectScript
{
public:
    go_ice_stone() : GameObjectScript("go_ice_stone") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (go->FindNearestCreature(NPC_AHUNE, 200.0f, true))
            return false;

        if (go->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
        {
            player->PrepareQuestMenu(go->GetGUID());
            player->SendPreparedQuest(go->GetGUID());
        }

        if (player->HasAura(SPELL_AHUNE_SUMMON_RHYME))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_AHUNE_SUMMON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(go), go->GetGUID());
        }

        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();

        if (action == GOSSIP_ACTION_INFO_DEF)
        {
            go->SummonCreature(NPC_AHUNE, SummonPositions[0], TEMPSUMMON_DEAD_DESPAWN);
            go->SetPhaseMask(PHASE_TWO, true);
        }

        return true;
    }

    struct go_ice_stoneAI : public GameObjectAI
    {
        go_ice_stoneAI(GameObject* gameObject) : GameObjectAI(gameObject)
        {
            _checkTimer = 10000;
        }

        uint32 _checkTimer;

        void UpdateAI(uint32 diff)
        {
            if (go->GetPhaseMask() & PHASE_TWO)
            {
                if (_checkTimer <= diff)
                {
                    go->SetPhaseMask(PHASE_ONE, true);
                    _checkTimer = 10000;
                }
                else _checkTimer -= diff;
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return new go_ice_stoneAI(go);
    }
};

class npc_ahunite_hailstone : public CreatureScript
{
public:
    npc_ahunite_hailstone() : CreatureScript("npc_ahunite_hailstone") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ahunite_hailstoneAI(creature);
    }

    struct npc_ahunite_hailstoneAI : public ScriptedAI
    {
        npc_ahunite_hailstoneAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset()
        {
            events.Reset();
            events.ScheduleEvent(EVENT_PULVERIZE, urand(6000, 8000));

            DoCast(me, SPELL_CHILLING_AURA);
            DoCast(me, SPELL_CHILLING_AURA_PERIODIC); // use for visual atm
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_PULVERIZE:
                    DoCastVictim(SPELL_PULVERIZE);
                    events.ScheduleEvent(EVENT_PULVERIZE, urand(6000, 8000));
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

class npc_ahunite_coldweave : public CreatureScript
{
public:
    npc_ahunite_coldweave() : CreatureScript("npc_ahunite_coldweave") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ahunite_coldweaveAI(creature);
    }

    struct npc_ahunite_coldweaveAI : public ScriptedAI
    {
        npc_ahunite_coldweaveAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset()
        {
            events.Reset();
            events.ScheduleEvent(EVENT_BITTER_BLAST, 500);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_BITTER_BLAST:
                    DoCastVictim(SPELL_BITTER_BLAST);
                    events.ScheduleEvent(EVENT_BITTER_BLAST, urand(5000, 7000));
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

class npc_ahunite_frostwind : public CreatureScript
{
public:
    npc_ahunite_frostwind() : CreatureScript("npc_ahunite_frostwind") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ahunite_frostwindAI(creature);
    }

    struct npc_ahunite_frostwindAI : public ScriptedAI
    {
        npc_ahunite_frostwindAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset()
        {
            events.Reset();
            events.ScheduleEvent(EVENT_WIND_BUFFET, 2000); // FIXME: get correct timing for wind buffet

            DoCast(me, SPELL_LIGHTNING_SHIELD);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_WIND_BUFFET:
                    if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 120.0f))
                        DoCast(target, SPELL_WIND_BUFFET);
                    events.ScheduleEvent(EVENT_WIND_BUFFET, urand(5000, 7000));
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

	void AddSC_evento_midsummer()
{
	new spell_gen_ribbon_pole_dancer_check();
	new spell_gen_antorchas_logr();
	new spell_gen_lanz_antor_logro();
	new spell_blandones_golpeados_qcredit();
	new spell_ev_antorchas_quest();
	new npc_trigger_torch_mal();
	new npc_trigger_ribbon();
	new npc_achievement_llamas_ciudades();
	new npc_midsummer_music();
    new boss_ahune();
    new npc_frozen_core();
    new go_ice_stone();
    new npc_ahunite_hailstone();
    new npc_ahunite_coldweave();
    new npc_ahunite_frostwind();
}
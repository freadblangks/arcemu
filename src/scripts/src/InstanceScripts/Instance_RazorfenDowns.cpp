/*
 * ArcScript Scripts for Arcemu MMORPG Server
 * Copyright (C) 2008-2009 Arcemu Team
 * Copyright (C) 2007 Moon++ <http://www.moonplusplus.com/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "StdAfx.h"
#include "Setup.h"

/************************************************************************/
/*  Instance_RazorfenDowns.cpp Script									*/
/************************************************************************/

class AmnennarTheColdbringer : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(AmnennarTheColdbringer);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    AmnennarTheColdbringer(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(10179);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(22645);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;


		     spells[2].info = dbcSpell.LookupEntry(13009);
		     spells[2].cooldown = 10;
		     spells[2].targettype = TARGET_ATTACKING;
		     spells[2].instant = true;
		     spells[2].perctrigger = (float)RandomFloat(20.0f);
		     spells[2].attackstoptimer = 3000;
		     m_spellcheck[2] = true;

    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(Unit* mTarget)
    {
    }

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:

	int nrspells;
};


class Glutton : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Glutton);
	SP_AI_Spell spells[1];
 bool m_spellcheck[1];

    Glutton(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(16345);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;

    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(Unit* mTarget)
    {
    }

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:

	int nrspells;
};


class MordreshFireEye : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(MordreshFireEye);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    MordreshFireEye(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(10148);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(12470);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(Unit* mTarget)
    {
    }

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:

	int nrspells;
};


class PlaguemawTheRotting : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PlaguemawTheRotting);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    PlaguemawTheRotting(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(12947);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(12946);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(Unit* mTarget)
    {
    }

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:

	int nrspells;
};

class Ragglesnout : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Ragglesnout);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    Ragglesnout(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(10892);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(11659);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(Unit* mTarget)
    {
    }

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:

	int nrspells;
};


class TutenKash : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(TutenKash);
	SP_AI_Spell spells[2];
 bool m_spellcheck[2];

    TutenKash(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		     spells[0].info = dbcSpell.LookupEntry(12255);
		     spells[0].cooldown = 10;
		     spells[0].targettype = TARGET_ATTACKING;
		     spells[0].instant = true;
		     spells[0].perctrigger = (float)RandomFloat(20.0f);
		     spells[0].attackstoptimer = 3000;
		     m_spellcheck[0] = true;


		     spells[1].info = dbcSpell.LookupEntry(12252);
		     spells[1].cooldown = 10;
		     spells[1].targettype = TARGET_ATTACKING;
		     spells[1].instant = true;
		     spells[1].perctrigger = (float)RandomFloat(20.0f);
		     spells[1].attackstoptimer = 3000;
		     m_spellcheck[1] = true;

    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i=0;i<nrspells;i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(Unit* mTarget)
    {
    }

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i=0;i<nrspells;i++)
			{
				spells[i].casttime--;
				
				if (m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant); break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant); break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant); break;
					}

					if (spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if ((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:

	int nrspells;
};


void SetupRazorfenDowns(ScriptMgr * mgr)
{
mgr->register_creature_script(7358, &AmnennarTheColdbringer::Create);
mgr->register_creature_script(8567, &Glutton::Create);
mgr->register_creature_script(7357, &MordreshFireEye::Create);
mgr->register_creature_script(7356, &PlaguemawTheRotting::Create);
mgr->register_creature_script(7354, &Ragglesnout::Create);
mgr->register_creature_script(7355, &TutenKash::Create);
}
 --[[
   ******************************************************************
   *	 _____              ___                           _         *
   *	(  _  )            (  _`\               _        ( )_       *
   *	| (_) | _ __   ___ | (_(_)   ___  _ __ (_) _ _   | ,_)      *
   *	|  _  |( '__)/'___)`\__ \  /'___)( '__)| |( '_`\ | |        *
   *	| | | || |  ( (___ ( )_) |( (___ | |   | || (_) )| |_       *
   *	(_) (_)(_)  `\____)`\____)`\____)(_)   (_)| ,__/'`\__)      *
   *	                                          | |               *
   *	                                          (_)               *
   *	                                                            *
   *	               OpenSource Scripting Team                    *
   *	                <http://www.arcemu.org>                     *
   *	                                                            *
   ******************************************************************
  
   This software is provided as free and open source by the
staff of The ArcScript Project, in accordance with 
the GPL license. This means we provide the software we have 
created freely and it has been thoroughly tested to work for 
the developers, but NO GUARANTEE is made it will work for you 
as well. Please give credit where credit is due, if modifying,
redistributing and/or using this software. Thank you.

Staff of ArcScript Project, Feb 2008
~~End of License Agreement

#############################################################

-- ]]
-- Scripted By:  n4xD

function Dragonflayer_Overseer_OnCombat(pUnit, Event)
pUnit:RegisterEvent("Dragonflayer_Overseer_Battle_Shout", math.random(22000, 25000), 0)
pUnit:RegisterEvent("Dragonflayer_Overseer_Charge", 10000, 0)
pUnit:RegisterEvent("Dragonflayer_Overseer_Demoralizing_Shout", 30000, 0)
end

function Dragonflayer_Overseer_OnLeaveCombat(pUnit, Event)
pUnit:RemoveEvents()
end

function Dragonflayer_Overseer_OnDeath(pUnit, Event)
pUnit:RemoveEvents()
end

RegisterUnitEvent(24085, 1, "Dragonflayer_Overseer_OnCombat")
RegisterUnitEvent(24085, 2, "Dragonflayer_Overseer_OnLeaveCombat")
RegisterUnitEvent(24085, 4, "Dragonflayer_Overseer_OnDeath")

function Dragonflayer_Overseer_Battle_Shout(pUnit, Event)
pUnit:FullCastSpell(38232)
end

function Dragonflayer_Overseer_Charge(pUnit, Event)
pUnit:FullCastSpellOnTarget(35570, pUnit:GetRandomPlayer(0))
end

function Dragonflayer_Overseer_Demoralizing_Shout(pUnit, Event)
pUnit:FullCastSpell(16244)
end

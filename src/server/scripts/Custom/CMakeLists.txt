# Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Custom/dynamic_teleporter.cpp
  Custom/vip_npc.cpp
  Custom/guildporter.cpp
  Custom/BountyHunter.cpp
  Custom/npc_ashen_ring_restorer.cpp
  Custom/object_arena_crystal.cpp
  Custom/command_mmr.cpp
  Custom/Transmogrification.h
	Custom/Transmogrification.cpp
	Custom/Transmogrifier.cpp
  Custom/TrialOfTheChampion/TW_instance_trial_of_the_champion.cpp
  Custom/TrialOfTheChampion/TW_trial_of_the_champion.h
  Custom/TrialOfTheChampion/TW_boss_argent_challenge.cpp
  Custom/TrialOfTheChampion/TW_boss_grand_champions.cpp
  Custom/TrialOfTheChampion/TW_boss_black_knight.cpp
  Custom/TrialOfTheChampion/TW_trial_of_the_champion.cpp
  Custom/Ulduar/TW_boss_thorim.cpp
  Custom/Ulduar/TW_boss_mimiron.cpp
  Custom/npc_icc_buff.cpp
)

message("  -> Prepared: Custom")

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
  Custom/npc_arena_spectator.cpp
  Custom/npc_arena_teams.cpp
  Custom/BountyHunter.cpp
  Custom/npc_ashen_ring_restorer.cpp
  Custom/object_arena_crystal.cpp
  Custom/command_mmr.cpp
)

message("  -> Prepared: Custom")

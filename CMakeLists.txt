cmake_minimum_required(VERSION 3.6)
project(RPG)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Settings.h Heroes/Hero.cpp Heroes/Hero.h Team.cpp Team.h Heroes/Defender.cpp Heroes/Defender.h Heroes/Warrior.cpp Heroes/Warrior.h Heroes/Healer.cpp Heroes/Healer.h)
add_executable(RPG ${SOURCE_FILES} Settings.h Heroes/Hero.cpp Heroes/Hero.h Team.cpp Team.h Heroes/Defender.cpp Heroes/Defender.h Heroes/Warrior.cpp Heroes/Warrior.h Heroes/Healer.cpp Heroes/Healer.h)
cmake_minimum_required(VERSION 3.10)

project(RUNTRACK_CPP_Y2 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable from source files
add_executable(hello
    src/day01/main.cpp
    src/day01/day01.cpp)

add_executable(day02
    src/day02/day02.cpp
    src/day02/terrestrial.cpp
    src/day02/aquatic.cpp
    src/day02/penguin.cpp
    )

add_executable(campus_quest
    src/day03/main.cpp
    src/day03/Bow.cpp
    src/day03/Character.cpp
    src/day03/Decor.cpp
    src/day03/Enemy.cpp
    src/day03/Game.cpp
    src/day03/GameManager.cpp
    src/day03/GameObject.cpp
    src/day03/Player.cpp
    src/day03/Projectile.cpp
    src/day03/Spear.cpp
    src/day03/Sword.cpp
    src/day03/UIHelper.cpp
    src/day03/Vector2d.cpp
    src/day03/Weapon.cpp
    )
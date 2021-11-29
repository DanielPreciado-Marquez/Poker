cmake_minimum_required(VERSION 3.16.0)

set(PROJECT_NAME DPMpoker)
set(LIBRARY_NAME DPMpoker)
set(INCLUDE_DIR include)
set(SOURCE_DIR src)
set(EXAMPLES_DIR examples)

option(BUILD_EXAMPLES "Builds all examples")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)


if (BUILD_EXAMPLES)
    add_subdirectory(${EXAMPLES_DIR})
endif ()

add_library(${PROJECT_NAME}
        include/DPMpoker/DPMpoker.hpp
        src/Card.cpp
        src/Card.h
        src/Enums/CardRank.h
        src/Enums/CardSuit.h
        src/Enums/DealerAction.cpp
        src/Enums/DealerAction.h
        src/Enums/GameMode.h
        src/Enums/GameNodeType.hpp
        src/Enums/GameStateType.hpp
        src/Enums/MoveType.h
        src/Enums/PlayerAction.cpp
        src/Enums/PlayerAction.h
        src/DealerMove.cpp
        src/DealerMove.h
        src/Hand.h
        src/History.h
        src/InformationSet.h
        src/PlayerMove.cpp
        src/PlayerMove.h
        src/PlayerSlot.cpp
        src/PlayerSlot.h
        src/Move.cpp
        src/Move.h
        src/Outcome.cpp
        src/Outcome.h
        src/Player.cpp
        src/Player.h
        src/Poker.h
        src/RoundHistory.h
        src/RuleSet/RuleSet.h
        src/RuleSet/RuleSetLeducHoldem.hpp
        src/RuleSet/RuleSetKuhnPoker.h
        src/RuleSet/RuleSets.h
        src/Strategy.h
        src/StrategyBase.cpp
        src/StrategyBase.h
        src/Tree/ChildInfo.hpp
        src/Tree/DecisionNode.h
        src/Tree/GameState.hpp
        src/Tree/InitialGameState.hpp
        src/Tree/InternalNode.h
        src/Tree/LeafNode.h
        src/Tree/NodeBase.h
        src/Tree/RootNode.h
        src/Tree/RoundState.hpp
        src/Tree/State.h
        src/TurnOptions.h
        src/Types/Cash.h
        src/Types/PlayerIndex.cpp
        src/Types/PlayerIndex.h
        src/Types/Turn.h)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/${LIBRARY_NAME}/pch.h)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}/${LIBRARY_NAME}>
        $<INSTALL_INTERFACE:${INCLUDE_DIR}/${LIBRARY_NAME}>)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR}>
        $<INSTALL_INTERFACE:${SOURCE_DIR}>)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}>
        $<INSTALL_INTERFACE:${INCLUDE_DIR}>)

cmake_minimum_required(VERSION 3.0)
project(poker)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(poker
        main.cpp
        src/Card.cpp
        src/Card.h
        src/Enums/CardRank.h
        src/Enums/CardSuit.h
        src/Enums/DealerAction.cpp
        src/Enums/DealerAction.h
        src/Enums/GameMode.h
        src/Enums/GameNodeType.hpp
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

target_precompile_headers(poker PRIVATE pch.h)

cmake_minimum_required(VERSION 3.0)
project(kuhn_poker)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(kuhn_poker
        main.cpp
        src/enums.cpp
        src/enums.h
        src/InformationSet.cpp
        src/InformationSet.h
        src/InternalNode.cpp
        src/InternalNode.h
        src/KuhnPoker.cpp
        src/KuhnPoker.h
        src/LeafNode.cpp
        src/LeafNode.h
        src/NodeBase.cpp
        src/NodeBase.h
        src/Outcome.cpp
        src/Outcome.h
        src/Player.cpp
        src/Player.h
        src/RootNode.cpp
        src/RootNode.h
        src/State.cpp
        src/State.h)

target_precompile_headers(kuhn_poker PRIVATE pch.h)

link_libraries(${PROJECT_NAME})

add_executable(KuhnPoker
        KuhnPoker/main.cpp)
add_executable(LeducHoldem
        LeducHoldem/main.cpp)

target_precompile_headers(KuhnPoker PRIVATE pch.h)
target_precompile_headers(LeducHoldem PRIVATE pch.h)

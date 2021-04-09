set(MAIN_SRC main.cpp)

add_executable(APP ${MAIN_SRC})

target_compile_features(APP PRIVATE cxx_std_17)

target_link_libraries(APP PRIVATE OPERATING_SYSTEM)


set(SIMULATION_INCLUDES_DIR ${PROJECT_SOURCE_DIR}/inc/)
set(SIMULATION_SOURCES Operating_System.cpp)

set(INTERNAL_LIBRARIES MEMORY_STORAGE ORDER_UTIL PAGE_UTIL PAGING_ALGORITHMS)

add_library(SIMULATION ${SIMULATION_SOURCES})

target_include_directories(SIMULATION PUBLIC ${SIMULATION_INCLUDES_DIR}/)
target_link_libraries(SIMULATION PUBLIC ${INTERNAL_LIBRARIES})

add_library(ALL_LIBS INTERFACE)

target_link_libraries(ALL_LIBS INTERFACE SIMULATION)
target_compile_features(ALL_LIBS INTERFACE cxx_std_17)

add_subdirectory(Page_Util)
add_subdirectory(Order_Util)
add_subdirectory(Memory_Storage)
add_subdirectory(Paging_Algorithms)
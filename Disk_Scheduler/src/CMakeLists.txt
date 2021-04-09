add_library(HARD_DRIVE IHard_Drive.cpp Hard_Drive.cpp)
add_library(OPERATING_SYSTEM Operating_System.cpp)


set(INCLUDES_DIR "${PROJECT_SOURCE_DIR}/inc/")

#target_include_directories(HARD_DRIVE PUBLIC "${INCLUDES_DIR}/Hard_Drive_Parts/" ${INCLUDES_DIR}/)
target_include_directories(HARD_DRIVE PUBLIC ${INCLUDES_DIR}/)
target_include_directories(OPERATING_SYSTEM PUBLIC ${INCLUDES_DIR}/)

target_link_libraries(HARD_DRIVE PUBLIC HARD_DRIVE_PARTS ALGORITHMS)
target_link_libraries(OPERATING_SYSTEM PUBLIC HARD_DRIVE ORDERS)
#target_link_libraries(ORDER PUBLIC )

target_compile_features(HARD_DRIVE PRIVATE cxx_std_17)
target_compile_features(OPERATING_SYSTEM PRIVATE cxx_std_17)

add_subdirectory(Hard_Drive_Parts)
add_subdirectory(Orders)
add_subdirectory(Algorithms)

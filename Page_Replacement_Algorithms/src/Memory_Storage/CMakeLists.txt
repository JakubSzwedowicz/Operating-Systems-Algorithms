set(MEMORY_STORAGE_INCLUDES_DIR
        ${PROJECT_SOURCE_DIR}/inc/Memory_Storage
        ${PROJECT_SOURCE_DIR}/inc/Paging_Algorithms/
        ${PROJECT_SOURCE_DIR}/inc/Order_Util/
        ${PROJECT_SOURCE_DIR}/inc/Page_Util/)

set(MEMORY_STORAGE_SOURCES Hard_Drive.cpp Memory_Container.cpp Memory_Handler.cpp RAM.cpp Segment_Table.cpp)

add_library(MEMORY_STORAGE ${MEMORY_STORAGE_SOURCES})

target_include_directories(MEMORY_STORAGE PUBLIC ${MEMORY_STORAGE_INCLUDES_DIR})

target_compile_features(MEMORY_STORAGE PUBLIC cxx_std_17)


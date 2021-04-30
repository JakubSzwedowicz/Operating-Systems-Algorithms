set(PAGING_ALGORITHMS_INCLUDES_DIR
        ${PROJECT_SOURCE_DIR}/inc/Paging_Algorithms/
        ${PROJECT_SOURCE_DIR}/inc/Memory_Storage/
        ${PROJECT_SOURCE_DIR}/inc/Page_Util/
        ${PROJECT_SOURCE_DIR}/inc/Order_Util/)

set(PAGING_ALGORITHMS_SOURCES IAlgorithm.cpp FIFO_Algorithm.cpp LRU_Algorithm.cpp LRU_Est_Algorithm.cpp OPT_Algorithm.cpp RAND_Algorithm.cpp)

add_library(PAGING_ALGORITHMS ${PAGING_ALGORITHMS_SOURCES})

target_include_directories(PAGING_ALGORITHMS PUBLIC ${PAGING_ALGORITHMS_INCLUDES_DIR})

target_compile_features(PAGING_ALGORITHMS PRIVATE cxx_std_17)
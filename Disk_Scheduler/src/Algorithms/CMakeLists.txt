set(ALGORITHMS_SRC IAlgorithm.cpp FIFO_Algorithm.cpp SSTF_Algorithm.cpp SCAN_Algorithm.cpp C_SCAN_Algorithm.cpp)

add_library(ALGORITHMS STATIC ${ALGORITHMS_SRC})

target_include_directories(ALGORITHMS PUBLIC "${INCLUDES_DIR}/" "${INCLUDES_DIR}/Orders/" "${INCLUDES_DIR}/Algorithms/")
target_link_libraries(ALGORITHMS PUBLIC HARD_DRIVE)

target_compile_features(ALGORITHMS PRIVATE cxx_std_17)

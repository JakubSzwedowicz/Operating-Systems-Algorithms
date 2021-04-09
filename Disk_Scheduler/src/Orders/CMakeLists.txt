add_library(ORDERS Order.cpp Reading_Order.cpp Writing_Order.cpp)

target_include_directories(ORDERS PUBLIC "${INCLUDES_DIR}/" "${INCLUDES_DIR}/Orders/")

target_link_libraries(ORDERS PUBLIC HARD_DRIVE_PARTS ALGORITHMS)

target_compile_features(ORDERS PRIVATE cxx_std_17)


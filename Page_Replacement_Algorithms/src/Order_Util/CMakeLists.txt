set(ORDER_UTIL_INCLUDES_DIR ${PROJECT_SOURCE_DIR}/inc/Order_Util/ ${PROJECT_SOURCE_DIR}/inc/Page_Util/)

set(ORDER_UTIL_SOURCES Order.cpp Write_Order.cpp Read_Order.cpp)

add_library(ORDER_UTIL ${ORDER_UTIL_SOURCES})

target_include_directories(ORDER_UTIL PUBLIC ${ORDER_UTIL_INCLUDES_DIR})

target_compile_features(ORDER_UTIL PUBLIC cxx_std_17)

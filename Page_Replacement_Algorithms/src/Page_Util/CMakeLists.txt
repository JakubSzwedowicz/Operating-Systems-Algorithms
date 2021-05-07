set(PAGE_UTIL_INCLUDES_DIR ${PROJECT_SOURCE_DIR}/inc/Page_Util/)
set(PAGE_UTIL_SOURCES Page.cpp Page_Info.cpp)

add_library(PAGE_UTIL ${PAGE_UTIL_SOURCES})

target_include_directories(PAGE_UTIL PUBLIC ${PAGE_UTIL_INCLUDES_DIR})

target_compile_features(PAGE_UTIL PRIVATE cxx_std_17)
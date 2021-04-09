set(HARD_DRIVE_PARTS_SRC Disk_Block.cpp Disk_Track.cpp Disk_Plate.cpp Disk_Plates_Set.cpp)

add_library(HARD_DRIVE_PARTS STATIC ${HARD_DRIVE_PARTS_SRC})

target_include_directories(HARD_DRIVE_PARTS PUBLIC "${INCLUDES_DIR}/Hard_Drive_Parts/")

target_compile_features(HARD_DRIVE_PARTS PRIVATE cxx_std_17)
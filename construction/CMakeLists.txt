include_directories(${PROJECT_SOURCE_DIR}/construction)
include_directories(${PROJECT_SOURCE_DIR}/objects)
add_library(detector 
    DetectorConstruction.cc
    B2DetectorConstruction.cc
    B2MagneticField.cc
    B2TrackerHit.cc
    B2TrackerSD.cc
    MaskDetector.cc
    SensitiveDetector.cc
)
target_link_libraries(detector objects)

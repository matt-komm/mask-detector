include_directories(${PROJECT_SOURCE_DIR}/construction)
add_library(detector 
    DetectorConstruction.cc
    B2DetectorConstruction.cc
    B2MagneticField.cc
    B2TrackerHit.cc
    B2TrackerSD.cc
)

include_directories(${PROJECT_SOURCE_DIR}/analysis)
include_directories(${PROJECT_SOURCE_DIR}/objects)

find_package(ROOT)
include_directories(${ROOT_INCLUDE_DIR})

add_library(analysis 
    AnalysisChain.cc
    Module.cc
    ObjectStore.cc
    demangle.cc
)
target_link_libraries(analysis ${ROOT_LIBRARIES})





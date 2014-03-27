cmake_minimum_required(VERSION 2.6)
project(detector)

find_package(Geant4 REQUIRED)
include_directories(${Geant4_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/construction)
include_directories(${PROJECT_SOURCE_DIR}/action)
include_directories(${PROJECT_SOURCE_DIR}/physics)

add_subdirectory(construction)
add_subdirectory(physics)
add_subdirectory(action)

add_executable(main
    main.cc
)
target_link_libraries(main 
    detector 
    physics 
    action 
    ${Geant4_LIBRARIES}
)



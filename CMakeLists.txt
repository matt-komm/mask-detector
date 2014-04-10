cmake_minimum_required(VERSION 2.6)
project(detector)

add_custom_target(copy)

MACRO(COPY_FILE_IF_CHANGED in_file out_file)  
        ADD_CUSTOM_COMMAND (
            TARGET     copy
            POST_BUILD
            COMMAND    ${CMAKE_COMMAND}
            ARGS       -E copy_if_different ${in_file} ${out_file}
            COMMENT "Copying file: ${in_file} to: ${out_file}"
        )
ENDMACRO(COPY_FILE_IF_CHANGED)



option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE}) #this changes compile commands such that opengl becomes available amongst others

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
COPY_FILE_IF_CHANGED(${CMAKE_CURRENT_SOURCE_DIR}/gui.mac ${CMAKE_CURRENT_BINARY_DIR}/gui.mac)
COPY_FILE_IF_CHANGED(${CMAKE_CURRENT_SOURCE_DIR}/init_vis.mac ${CMAKE_CURRENT_BINARY_DIR}/init_vis.mac)
target_link_libraries(main 
    detector 
    physics 
    action 
    ${Geant4_LIBRARIES}
)
add_dependencies(main copy)



cmake_minimum_required(VERSION 2.6)
project(detector)

MACRO(COPY_FILE_IF_CHANGED in_file out_file target)
    IF(${in_file} IS_NEWER_THAN ${out_file})    
    	ADD_CUSTOM_COMMAND (
    		TARGET     ${target}
    		POST_BUILD
    		COMMAND    ${CMAKE_COMMAND}
    		ARGS       -E copy ${in_file} ${out_file}
    	)
	ENDIF(${in_file} IS_NEWER_THAN ${out_file})
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
COPY_FILE_IF_CHANGED(${CMAKE_CURRENT_SOURCE_DIR}/gui.mac ${CMAKE_CURRENT_BINARY_DIR}/gui.mac main)
COPY_FILE_IF_CHANGED(${CMAKE_CURRENT_SOURCE_DIR}/init_vis.mac ${CMAKE_CURRENT_BINARY_DIR}/init_vis.mac main)
target_link_libraries(main 
    detector 
    physics 
    action 
    ${Geant4_LIBRARIES}
)



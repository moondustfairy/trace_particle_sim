cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(trace_particle_sim)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
option(GEANT4_USE_OPENGL_X11 ON)
if (WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else ()
    find_package(Geant4 REQUIRED)
endif ()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(sim sim.cc ${sources} ${headers}
        src/construction.cc
        src/run_action.cc
        include/run_action.hh
        src/histo_manager.cc
        include/histo_manager.hh
        src/tracking_action.cc
        include/tracking_action.hh)

target_link_libraries(sim ${Geant4_LIBRARIES})

set(TRACE_PARTICLE_SIM_SCRIPTS
        init_vis.mac
        vis.mac
        gps_proton_iso.mac)

foreach (_script ${TRACE_PARTICLE_SIM_SCRIPTS})
    configure_file(
            ${PROJECT_SOURCE_DIR}/${_script}
            ${PROJECT_BINARY_DIR}/${_script}
            COPYONLY
    )
endforeach ()

add_custom_target(trace_particle_sim DEPENDS sim)

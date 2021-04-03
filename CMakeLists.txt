cmake_minimum_required (VERSION 3.18)
project ("castles")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE on)

#Architecture detection
if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "Detected x86 architecture which is unsupported one. Exiting...")
endif()

#Mode and system detection
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Detected DEBUG mode.")
    set(DEBUG_BUILD true)
else()
    message("Detected RELEASE mode.")
    set(DEBUG_BUILD false)
endif()

#Additional find_package search paths
set(CMAKE_PREFIX_PATH "${DEPENDENCIES_PATHS}" "${CMAKE_PREFIX_PATH}")
#All libraries output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/")

if (MSVC)
    if (${DEBUG_BUILD})
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    else()
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    endif()
endif()

if (DEFINED CPPCHECK_PATH)
    message("CPPCheck detected in: ${CPPCHECK_PATH}")
    set(CMAKE_CXX_CPPCHECK "${CPPCHECK_PATH}")
endif()


find_package(spdlog CONFIG REQUIRED)
link_libraries(spdlog::spdlog)

set(SRC_FILES 
    #Graphics
    "src/graphics/game_renderer.hpp" 
    "src/graphics/render_layer.hpp" 
    "src/graphics/assets_loader.hpp"
    "src/graphics/render_layer.hpp" 

     #Game
    "src/game/game_map.hpp" "src/game/game_map.cpp"
    "src/game/tile.hpp"  
    "src/game/units.hpp"

    #Application
    "src/application/application.hpp" "src/application/application.cpp"
    "src/input/input_handler.hpp"
)

if (DEFINED SDL_PC_BUILD OR DEFINED SDL_BROWSER_BUILD)
    list(APPEND SRC_FILES
        #SDL Graphics Layer    
        "src/application/sdl/sdl_small_guards.hpp"
        "src/application/sdl/sdl_include.hpp" 
    
        "src/graphics/sdl/sdl_renderer.hpp" "src/graphics/sdl/sdl_renderer.cpp"
        "src/graphics/sdl/sdl_window.hpp" "src/graphics/sdl/sdl_window.cpp" 
        "src/graphics/sdl/sdl_texture.hpp" "src/graphics/sdl/sdl_texture.cpp" 
        "src/graphics/sdl/sdl_surface.hpp" "src/graphics/sdl/sdl_surface.cpp"
     
        "src/graphics/sdl/sdl_game_renderer.hpp" "src/graphics/sdl/sdl_game_renderer.cpp"
        "src/graphics/sdl/layers/sdl_render_layer.hpp"
        "src/graphics/sdl/layers/sdl_game_layer.hpp" "src/graphics/sdl/layers/sdl_game_layer.cpp"

        #SDL Application
        "src/application/sdl/sdl_pc_application.hpp" "src/application/sdl/sdl_pc_application.cpp" 
        "src/input/sdl/sdl_input_handler.hpp" "src/input/sdl/sdl_input_handler.cpp" 
    )
endif()

if (DEFINED SDL_PC_BUILD)
    list(APPEND SRC_FILES
        "src/sdl_pc_main.cpp" 
        "src/graphics/fs_assets_loader.hpp" "src/graphics/fs_assets_loader.cpp"
    )
endif()

add_executable(${PROJECT_NAME} ${SRC_FILES})

#SYSTEM PUBLIC to disable clang warnings
target_include_directories("${PROJECT_NAME}" SYSTEM PUBLIC "${SDL_PATH}/include/")
target_include_directories("${PROJECT_NAME}" PUBLIC "src/")
target_link_directories("${PROJECT_NAME}" PUBLIC "${SDL_PATH}/lib/x64/")
target_link_libraries("${PROJECT_NAME}" PUBLIC "SDL2")
target_link_libraries("${PROJECT_NAME}" PUBLIC "SDL2_ttf")
target_link_libraries("${PROJECT_NAME}" PUBLIC "SDL2_image")

#Debug mode features enable macro
if (${DEBUG_BUILD})
    add_compile_definitions(DEBUG_MODE_ENABLED)
endif()


#Warnings setup
add_compile_options(
    -Wall -Wextra -Weverything -Wpedantic #Warnings
    -Wno-c++98-compat #No annoying warnings about c++98 from Wall
)

if (MSVC)
    add_compile_options(/EHsc) #Enable exceptions
endif()  

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake_dev_utils.cmake")
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake_dev_utils.cmake")
endif()

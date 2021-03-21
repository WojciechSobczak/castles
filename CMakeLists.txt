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

find_package(spdlog CONFIG REQUIRED)
link_libraries(spdlog::spdlog)

if (${DEBUG_BUILD})
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

add_executable(${PROJECT_NAME} 
    "src/main.cpp"  

    #SDL Wrapper    
    "src/sdlwrap/sdlwrap.hpp" 
    "src/sdlwrap/sdlsmallguards.hpp"
    "src/sdlwrap/sdl_include.hpp" 
    "src/sdlwrap/sdlrenderer.hpp" "src/sdlwrap/sdlrenderer.cpp"
    "src/sdlwrap/sdlwindow.hpp" "src/sdlwrap/sdlwindow.cpp" 
    "src/sdlwrap/sdltexture.hpp" "src/sdlwrap/sdltexture.cpp" 
    "src/sdlwrap/sdlsurface.hpp" "src/sdlwrap/sdlsurface.cpp"
    
    #Game
    "src/assets_loader.hpp" "src/assets_loader.cpp"
    "src/game/game_map.hpp" "src/game/game_map.cpp"
    "src/game/tile.hpp"  
    "src/game/units.hpp"
)

#SYSTEM PUBLIC to disable clang warnings
target_include_directories("${PROJECT_NAME}" SYSTEM PUBLIC "${SDL_PATH}/include/")
target_link_directories("${PROJECT_NAME}" PUBLIC "${SDL_PATH}/lib/x64/")
target_link_libraries("${PROJECT_NAME}" PUBLIC "SDL2")
target_link_libraries("${PROJECT_NAME}" PUBLIC "SDL2_ttf")
target_link_libraries("${PROJECT_NAME}" PUBLIC "SDL2_image")

#Warnings setup
add_compile_options(
    -Wall -Wextra -Weverything -Wpedantic #Warnings
    -Wno-c++98-compat #No annoying warnings about c++98 from Wall
    /EHsc #Enable exceptions
)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake_dev_utils.cmake")
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake_dev_utils.cmake")
endif()

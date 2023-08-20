cmake_minimum_required(VERSION 3.22)  # CMake version check
project(BC_GAME_PROJECT_ENGINE)       # Create project "BC_GAME_PROJECT_ENGINE"
set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

FIND_PACKAGE(PkgConfig REQUIRED)

set(CORE
Memory/Memory.cpp
Object/Object.cpp
Render/Render.cpp
UI/Widget/Widget.cpp
Input/InputManager.cpp
EngineDebugger/EngineDebugger.cpp
SceneManager/SceneManager.cpp
ShaderManager/ShaderManager.cpp
Transforms/Transform.cpp
Camera/Camera.cpp
Algo/QuadTree.cpp
WorldGeneration/Chunk/Chunk.cpp
WorldGeneration/WorldLoader/WorldLoader.cpp
BitmapManager/BitmapManager.cpp
Game/Game.cpp)



set(UI
#
#write new UI widget .cpp files here
UI/Canvas/CanvasWidget.cpp 
UI/TextWidget/TextWidget.cpp
UI/HorizontalBox/HorizontalBox.cpp
#
)



add_executable(BC_GAME_PROJECT_ENGINE ${CORE} ${UI} main.cpp)

pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5)

target_link_libraries(BC_GAME_PROJECT_ENGINE ${ALLEGRO5_LIBRARIES})

target_include_directories(BC_GAME_PROJECT_ENGINE PUBLIC ${ALLEGRO5_INCLUDE_DIRS} ".")

# configure_file("Resources" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_custom_command(
        TARGET BC_GAME_PROJECT_ENGINE PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/Resources
                ${CMAKE_CURRENT_BINARY_DIR}/Resources)
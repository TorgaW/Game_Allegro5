cmake_minimum_required(VERSION 3.22)  # CMake version check
project(BC_GAME_PROJECT)               # Create project "BC_GAME_PROJECT"
set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

FIND_PACKAGE(PkgConfig REQUIRED)
FIND_PACKAGE(Boost 1.81 REQUIRED thread system)

set(CORE_SOURCE Core/Object/AObject.cpp
                Core/ObjectManager/ObjectManager.cpp
                Core/Statics/Statics.cpp
                Core/Main/Game.cpp
                Core/Input/InputManager.cpp
                Core/Defines/Defines.cpp
                Core/World.cpp
                Core/Render/Render.cpp
                Core/Animations/Animation/AAnimation.cpp
                Core/BitmapLoader/BitmapLoader.cpp
                Core/ShaderManager/ShaderManager.cpp)

set(CORE_MATH   Core/Math/Noise/Perlin.cpp
                Core/Math/Vector/VectorMath.cpp
                Core/Math/Noise/Noise.cpp)

set(CORE_UI     Core/UI/Fonts/StaticFonts.cpp
                Core/UI/Viewport.cpp
                Core/UI/Profiler/Profiler.cpp
                Core/UI/Widget/Widget.cpp)

set(COMPONENTS_SOURCE   Components/InputComponent/InputComponent.cpp
                        Components/BitmapComponent/BitmapComponent.cpp
                        Components/SpriteSheetComponent/SpriteSheetComponent.cpp
                        Components/AnimationComponent/AnimationComponent.cpp)

set(SCENE_SOURCE    SceneObjects/SceneObject/SceneObject.cpp
                    SceneObjects/Scene/AScene.cpp
                    SceneObjects/Player/APlayer.cpp
                    SceneObjects/Camera/Camera.cpp
                    SceneObjects/StaticObject/StaticObject.cpp)

set(WORLD_GENERATION WorldGeneration/ChunkManager/AChunkManager.cpp)


# set(EngineEntity    Engine/Entity/Base/EntityBase.cpp)

# set(EngineComponent)
# set(EngineSystems   Engine/System/EngineLog/EngineLog.cpp
#                     Engine/System/Game/GameSystem.cpp
#                     Engine/System/Input/InputSystem.cpp)

set(SOURCE_FILES ${CORE_SOURCE} ${COMPONENTS_SOURCE} ${SCENE_SOURCE} ${CORE_MATH} ${CORE_UI} ${WORLD_GENERATION} main.cpp)

# set(Engine  Engine/Object/Object.cpp
#             Engine/GarbageCollector/GarbageCollector.cpp
#             Engine/Memory/Memory.cpp
#             Engine/Scene/Scene.cpp)

# set(SOURCE_FILES ${Engine} main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(BC_GAME_PROJECT ${SOURCE_FILES})

# Find Allegro modules
pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5)

# Link libraries
target_link_libraries(BC_GAME_PROJECT ${ALLEGRO5_LIBRARIES})

target_link_libraries( BC_GAME_PROJECT Boost::thread Boost::system)

# Print all linked libraries
message("ALLEGRO5_LIBRARIES = ${ALLEGRO5_LIBRARIES}")

target_include_directories(BC_GAME_PROJECT PUBLIC ${ALLEGRO5_INCLUDE_DIRS} ".")

file(COPY "Resources" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "Shaders" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
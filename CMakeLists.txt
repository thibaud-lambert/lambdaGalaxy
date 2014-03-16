project(lambdaGalaxy)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


find_package(PkgConfig REQUIRED)

#GLEW
INCLUDE(FindGLEW REQUIRED)
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})

#GLFW
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

#Eigen
pkg_search_module(EIGEN3 REQUIRED eigen3)
include_directories(${EIGEN3_INCLUDE_DIRS})

include_directories(src/)
include_directories(src/camera)
include_directories(src/object)
include_directories(src/object/mesh)
include_directories(src/object/shader)

set(SOURCES 
  src/main.cpp
  src/GameLoop.cpp
  src/StarField.cpp
  src/Star.cpp
  src/Chunk.cpp
  src/PlanetarySystem.cpp
  src/camera/Camera.cpp
  src/object/Object.cpp
  src/object/mesh/Mesh.cpp
  src/object/mesh/Vertex.cpp
  src/object/mesh/MeshLoader.cpp
  src/object/shader/Shader.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GLFW_STATIC_LIBRARIES} ${GLEW_LIBRARIES})


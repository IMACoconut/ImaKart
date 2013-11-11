cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

include_directories(third-party/SFML-2.1/include)
add_subdirectory(third-party/SFML-2.1)

include_directories(third-party/glew-1.10.0/include)
add_definitions(-DGLEW_STATIC=1)
add_subdirectory(third-party/glew-1.10.0)

include_directories(third-party/tinyxml2/include)
add_subdirectory(third-party/tinyxml2)

include_directories(third-party/glm)
include_directories(lib/include)
add_subdirectory(lib)

set(ALL_LIBRARIES glew ${OPENGL_LIBRARIES} imacoconut sfml-graphics sfml-window sfml-system tinyxml2)

add_subdirectory(template)

cmake_minimum_required(VERSION 3.24)
project(Clip_your_arbitrary_polygons)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_OSX_ARCHITECTURES  "arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)

set(LOCAL_H /opt/homebrew/include)
include_directories(${LOCAL_H})

set(GLEW_H /opt/homebrew/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /opt/homebrew/Cellar/glfw/3.3.8/include/GLFW)
link_directories(${GLEW_H} ${GLFW_H})

set(GLEW_LINK /opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /opt/homebrew/Cellar/glfw/3.3.8/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

add_executable(output src/glad.c src/main.cpp src/PolygonUtils.h src/Polygon.h src/Polygon.cpp src/PolygonClipping.h src/PolygonClipping.cpp)


if (APPLE)
    target_link_libraries(output  "-framework OpenGL")
    target_link_libraries(output  "-framework GLUT")
endif ()
cmake_minimum_required(VERSION 2.8)

project(OpenCL_3D_Engine)

include("cmake/FindCXXFeatures.cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_COMPILER_FLAGS}")

if(APPLE)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD c++11)
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY libc++)
    set(CMAKE_OSX_ARCHITECTURES x86_64)
    set(CMAKE_LIBRARY_PREFIX /opt/local /usr/local)

    include_directories(
        /opt/local/include
        /usr/local/include
        ${PROJECT_SOURCE_DIR}/thirdparty
    )

    find_library(COCOA_LIBRARY Cocoa)
    find_library(OPENGL_LIBRARY OpenGL)
    find_library(OPENAL_LIBRARY OpenAL)
    find_library(OPENCL_LIBRARY OpenCL)
    find_library(IOKIT_LIBRARY IOKit)

endif(APPLE)

find_library(
	GLUT_LIB
	glut
)

add_executable(
    OpenCL_3D_Engine_Test
    ${PROJECT_SOURCE_DIR}/sources/test.cpp
	${PROJECT_SOURCE_DIR}/sources/glut_win.cpp
	${PROJECT_SOURCE_DIR}/sources/glut_win.hpp
	${PROJECT_SOURCE_DIR}/sources/win_3d_engine.cpp
	${PROJECT_SOURCE_DIR}/sources/win_3d_engine.hpp
)

target_link_libraries(
    OpenCL_3D_Engine_Test
    ${Boost_LIBRARIES}
    ${OPENGL_LIBRARY}
    ${GLUT_LIB}
    ${OPENCL_LIBRARY}
)

# Created by Yun Yeomin <min050820@gmail.com>
# Licensed under GPLv3

# CMake 3.1 이상이 되어야 이 프로젝트를 빌드할 수 있음을 표기
cmake_minimum_required(VERSION 3.1)

# tetris 라는 이름의 C++(CXX) 프로젝트를 만듦
project(tetris CXX)


# TETRIS_SOURCES 변수를 설정함
set(TETRIS_SOURCES main.cpp)


# 만약 Emscripten 환경이라면...
if(EMSCRIPTEN)
    # 실행 파일 확장자를 .html 로 만듦 (기본은 .js)
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()


# TETRIS_SOURCES 변수에 있는 파일들을 컴파일해서 tetris.exe (혹은 tetris.html) 라는 이름의 실행 파일을 만듦
add_executable(tetris ${TETRIS_SOURCES})


# 만약 Emscripten 환경이라면...
if(EMSCRIPTEN)
    # 환경 변수를 설정함
    set_property(TARGET tetris APPEND_STRING PROPERTY COMPILE_FLAGS "-s WASM=0")
    set_property(TARGET tetris APPEND_STRING PROPERTY LINK_FLAGS "-s WASM=0")
endif()
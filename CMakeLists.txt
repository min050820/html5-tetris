# Created by Yun Yeomin <min050820@gmail.com>
# Licensed under GPLv3

# CMake 3.1 이상이 되어야 이 프로젝트를 빌드할 수 있음을 표기
cmake_minimum_required(VERSION 3.1)

# tetris 라는 이름의 C++(CXX) 프로젝트를 만듦
project(tetris CXX)


# 만약 win32 환경이라면...
if(WIN32)
    # SDL2 라는 이름의 "가져온=imported" "공유=shared" 라이브러리 타겟을 만듦
    add_library(SDL2 SHARED IMPORTED)
    # DLL 파일과 헤더파일 경로 지정
    set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2-2.0.10/lib/x86/SDL2.dll)
    set_target_properties(SDL2 PROPERTIES IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2-2.0.10/lib/x86/SDL2.lib)
    set_target_properties(SDL2 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2-2.0.10/include)

    # SDL2main 라이브러리도 똑같이 해줌
    add_library(SDL2main STATIC IMPORTED)
    set_target_properties(SDL2main PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2-2.0.10/lib/x86/SDL2main.lib)
endif()


# TETRIS_SOURCES 변수를 설정함
set(TETRIS_SOURCES main.cpp)


# 만약 Emscripten 환경이라면...
if(EMSCRIPTEN)
    # 실행 파일 확장자를 .html 로 만듦 (기본은 .js)
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()


# TETRIS_SOURCES 변수에 있는 파일들을 컴파일해서 tetris.exe (혹은 tetris.html) 라는 이름의 실행 파일을 만듦
add_executable(tetris ${TETRIS_SOURCES})

# tetris 라는 타겟은 C++11을 사용함
set_property(TARGET tetris PROPERTY CXX_STANDARD 11)


# 만약 Emscripten 환경이라면...
if(EMSCRIPTEN)
    # 환경 변수를 설정함
    set_property(TARGET tetris APPEND_STRING PROPERTY COMPILE_FLAGS "-s WASM=0 -s USE_SDL=2")
    set_property(TARGET tetris APPEND_STRING PROPERTY LINK_FLAGS "-s WASM=0 -s USE_SDL=2")
elseif(WIN32)
    target_link_libraries(tetris SDL2main SDL2)
endif()
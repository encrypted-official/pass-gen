cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PNAME pass_gen)

project(${PNAME})

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(${PNAME} ${SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/raylib/include)

target_link_libraries(${PNAME}
    ${CMAKE_SOURCE_DIR}/third_party/raylib/lib/libraylib.a
    opengl32 gdi32 winmm
)

# target_sources(${PNAME} PRIVATE resource.rc)

add_custom_command(TARGET ${PNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PNAME}>/assets)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set_target_properties(${PNAME} PROPERTIES LINK_FLAGS "-mwindows")

set(CMAKE_BUILD_TYPE Release)
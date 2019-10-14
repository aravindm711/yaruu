cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_C_COMPILER "gcc")

project(yaruu VERSION 0.1.0 DESCRIPTION "yet another rsync wrapper" HOMEPAGE_URL "https://github.com/aravindm711/yaruu" LANGUAGES C)

if(NOT DEFINED CMAKE_C_STANDARD AND NOT CMake_NO_C_STANDARD)
    set(CMAKE_C_STANDARD 11)
endif()

# guard against in-source builds and bad build-type strings
include(cmake/safeguards.cmake)

# detect operating system and host processor
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")
message(STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")

# c compiler flags for both linux and darwin systems
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unknown-pragmas -Wno-sign-compare -Wwrite-strings -Wno-unused")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -lpthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib/")
set(CMAKE_C_FLAGS_DEBUG   "-O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "-O3")

# c compiler and linker flags for darwin systems
if(CMAKE_C_COMPILER_ID MATCHES GNU AND CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -largp")
    #    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/local/include/")
    #    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib/ -largp")
endif()

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/include)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/include)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/main.c
    ${LIBRARY_OUTPUT_PATH}/daemon.h
    ${LIBRARY_OUTPUT_PATH}/yaruu.h
    ${LIBRARY_OUTPUT_PATH}/argp_config.h
    ${LIBRARY_OUTPUT_PATH}/argh.h
)

enable_testing()

add_executable(yaruu ${SOURCES})
target_include_directories(yaruu PRIVATE "include")

# # this must have worked
# if(CMAKE_C_COMPILER_ID MATCHES GNU AND CMAKE_SYSTEM_NAME MATCHES "Darwin")
#     #    target_link_libraries(yaruu -L/usr/local/lib)
#     #    target_link_libraries(yaruu -largp)
# endif()

install(TARGETS yaruu DESTINATION bin)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#*******************************************************************************
#
# CMake template for firmware static library generation BY mz4
#
#*******************************************************************************
cmake_minimum_required(VERSION 3.16)
project(queue VERSION 0.1.0 LANGUAGES C)

set(LIBRARY_OUTPUT_DIRECTORY "./build")
set(ARCHIVE_OUTPUT_DIRECTORY "./build")

option(QUEUE_STATIC_MODE "Do you want generate static mode" OFF)

#cmake -D QUEUE_STATIC_MODE=ON
if(QUEUE_STATIC_MODE)
	set(MAX_QUEUES_IN_POOL 1 CACHE STRING "MAX queues in pool")
	set(QUEUE_SIZE_IN_BYTES 1 CACHE STRING "Queue size in Bytes")
else()
	message("No")
endif()
	

# General settings {{{
set(TOOLCHAIN_NAME "arm-none-eabi-")

set(PROJECT_PATH ${CMAKE_CURRENT_LIST_DIR})
set(BUILD_PATH ${CMAKE_CURRENT_LIST_DIR}/build)

# Prepend the cross-compiler prefix to the used tools.
set(CMAKE_C_COMPILER "${TOOLCHAIN_NAME}gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_NAME}g++")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_NAME}as")
#}}}

#Add compile options
add_compile_options(
	-Wall
	-Wextra
	-Wpedantic	
	)

# Compiler settings {{{
# Be verbose when compiling.
set(WARNING_FLAGS "-Wall -Wextra -Wpedantic")

# Flags which are required for gcc, g++ and as.
#set(COMMON_COMPILE_FLAGS "-mcpu=${TARGET} -mthumb -std=gnu11 -O0 -g")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_COMPILE_FLAGS} ${WARNING_FLAGS} ${DEFINITIONS}")

# The following is required to get rid of the (not supported) -rdynamic flag
# when linking the final binary.
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "" )
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "" )
#}}}


# Source files  {{{
# Fill in your source files here (duh).
file(GLOB_RECURSE SOURCES ${PROJECT_PATH}/src/*.c)
#}}}

# Header files  {{{
# Fill in your header files here.
file(GLOB_RECURSE HEADERS ${PROJECT_PATH}/inc/*.h)
#}}}

# Include dirs  {{{
# Fill in the directories of your header files here.
include_directories(
    "${PROJECT_PATH}/inc"
)
#}}}

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})


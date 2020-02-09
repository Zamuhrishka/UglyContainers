#*******************************************************************************
#
#       CMake template for firmware static library generation
#													BY mz4
#
#*******************************************************************************
cmake_minimum_required(VERSION 3.5)
project(vector VERSION 0.1.0 LANGUAGES C CXX)
set(TARGET cortex-m4)

# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)


# General settings {{{
set(TOOLCHAIN_PATH  "/opt/Atollic_TrueSTUDIO_for_STM32_x86_64_9.2.0/ARMTools/bin/")
set(TOOLCHAIN_NAME "arm-atollic-eabi-")

set(PROJECT_PATH ${CMAKE_CURRENT_LIST_DIR})
set(BUILD_PATH ${CMAKE_CURRENT_LIST_DIR}/build)
set(DOXYGEN_PATH ${CMAKE_CURRENT_LIST_DIR}/doc)

# Fill in the linker script to use here
set(LINKER_SCRIPT "${PROJECT_PATH}/scripts/linker.ld")
# Fill in the config for openocd to use.
# E.g. for an STM32F4-Discovery dev-board:
set(OPENOCD_CFG "/usr/share/openocd/scripts/board/stm32f4discovery.cfg")

# Prepend the cross-compiler prefix to the used tools.
set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}${TOOLCHAIN_NAME}gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}${TOOLCHAIN_NAME}g++")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}${TOOLCHAIN_NAME}as")

set(DOXYGEN_CONFIG ${PROJECT_PATH}/Doxygen.conf)

set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_PATH}/build)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_PATH}/build)
set(ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_PATH}/build)
#}}}


# Compiler settings {{{
# Be verbose when compiling.
set(WARNING_FLAGS "-Wall -Wextra -Wpedantic")

# Flags which are required for gcc, g++ and as.
set(COMMON_COMPILE_FLAGS "-mcpu=${TARGET} -mthumb -std=gnu11 -O0 -g")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_COMPILE_FLAGS} ${WARNING_FLAGS} ${DEFINITIONS}")

# The following is required to get rid of the (not supported) -rdynamic flag
# when linking the final binary.
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "" )
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "" )
#}}}


# Source files  {{{
# Fill in your source files here (duh).
file(GLOB_RECURSE SOURCES src/*.c)
#}}}

# Header files  {{{
# Fill in your header files here.
file(GLOB_RECURSE HEADERS inc/*.h)
#}}}

# Include dirs  {{{
# Fill in the directories of your header files here.
include_directories(
    "${PROJECT_PATH}/inc"
)
#}}}

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Добавляем синоним, содержащий имя выпускающей библиотеку организации
add_library(mz4::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

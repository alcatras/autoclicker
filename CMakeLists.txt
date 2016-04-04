cmake_minimum_required(VERSION 3.3)
project(autoclicker)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(
        CORE src/core/commands
        src/core/utils
        src/core/CommandExecutor
        src/core/dev/VirtualDevice
        src/core/dev/VirtualMouse
)
set(CLI src/cli/ArgParser)

set(SOURCE src/main ${CORE} ${DEV})
add_executable(autoclicker-cli ${SOURCE} ${CLI})
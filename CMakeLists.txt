cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 17)
project(DeviceLog)

# Add the folders for header files
include_directories(${CMAKE_SOURCE_DIR}/)

add_executable(DeviceLog_gcc 
               ${CMAKE_SOURCE_DIR}/main.c
               ${CMAKE_SOURCE_DIR}/devicelog/devicelog.c
               ${CMAKE_SOURCE_DIR}/fileOperation/fileOperation.c
               ${CMAKE_SOURCE_DIR}/memmoryHandle/memmoryHandle.c)
              

# List executable files in release folder

target_compile_options(DeviceLog_gcc PRIVATE 
                       -Wall -Wextra -Werror -fanalyzer)

set_target_properties(DeviceLog_gcc PROPERTIES 
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/release)

# List debug files in debug folder
add_executable(DeviceLog_Debug 
               ${CMAKE_SOURCE_DIR}/main.c
               ${CMAKE_SOURCE_DIR}/devicelog/devicelog.c
               ${CMAKE_SOURCE_DIR}/fileOperation/fileOperation.c
               ${CMAKE_SOURCE_DIR}/memmoryHandle/memmoryHandle.c)

target_compile_options(DeviceLog_Debug PRIVATE -g -O0 -c -fanalyzer)

set_target_properties(DeviceLog_Debug PROPERTIES 
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/debug)

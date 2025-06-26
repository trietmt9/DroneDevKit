
cmake_minimum_required(VERSION 3.19)
project(DroneDevKit C)

# Set variable for each path
set(SOURCE_FILE Core/Src/main.c Core/Src/syscalls.c)

# Add cross-compiler 
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)


# Execute file and link libraries
add_executable(DroneDevKit.elf ${SOURCE_FILE})
target_include_directories(DroneDevKit.elf PRIVATE Core/Inc)

# Add custom commands to generate .bin and .hex
add_custom_command(TARGET DroneDevKit.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:DroneDevKit.elf> ${CMAKE_BINARY_DIR}/DroneDevKit.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:DroneDevKit.elf> ${CMAKE_BINARY_DIR}/DroneDevKit.hex
    COMMENT "Generating BIN and HEX files"
)
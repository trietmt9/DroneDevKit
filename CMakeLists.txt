 cmake_minimum_required(VERSION 3.19)
 set(PROJECT_NAME DroneDevKit)
 project(${PROJECT_NAME} C)

 # Add cross-compiler settings for STM32
 set(CMAKE_SYSTEM_NAME Generic)
 set(CMAKE_C_COMPILER arm-none-eabi-gcc)
 set(CMAKE_OBJCOPY arm-none-eabi-objcopy)

 # Set source files and directories
 set(SOURCE_FILE Core/Src/main.c 
                 Core/Src/syscalls.c
)

#Set CPU and instruction set for STM32F4 (Cortex-M4)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g")

 # Include directories for STM32CubeF4 and toolchain
 include_directories(
     Drivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Inc
     Drivers/STM32CubeF4/Drivers/CMSIS/Include
     Drivers/STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include
     Core/Inc
     ${CMAKE_C_COMPILER_SYSROOT}/include  # Add toolchain include path
 )

 # Manually specify STM32CubeF4 HAL source files (adjust paths as needed)
 set(HAL_SRC
     Drivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
     Drivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
     Drivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
     Drivers/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
 )

 # Manually specify CMSIS source files (adjust paths as needed)
 set(CMSIS_SRC
     Drivers/STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
     # Add other CMSIS source files here if present
 )

 # Create a library from STM32CubeF4 sources
 add_library(stm32f4xx_hal ${HAL_SRC})
 add_library(arm_cmsis ${CMSIS_SRC})

 # Ensure HAL and CMSIS include their own headers
 target_include_directories(stm32f4xx_hal PRIVATE Drivers/STM32F4xx_HAL_Driver/Inc)
 target_include_directories(arm_cmsis PRIVATE Drivers/CMSIS/Include Drivers/CMSIS/Device/ST/STM32F4xx/Include)

 # Execute file and link libraries
 add_executable(${PROJECT_NAME}.elf ${SOURCE_FILE})

 target_include_directories(${PROJECT_NAME}.elf PRIVATE Core/Inc)

 # Link the executable with the built libraries
 target_link_libraries(${PROJECT_NAME}.elf
     stm32f4xx_hal
     arm_cmsis
 )

 # Add custom commands to generate .bin and .hex
 add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
     COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin
     COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex
     COMMENT "Generating BIN and HEX files"
 )
cmake_minimum_required(VERSION 3.22)

project(STM32F769I_DISCO_STemWin_Demo C ASM)

set(CUBE_FW "C:/Users/hazh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.0" CACHE PATH "STM32CubeF7 firmware package")
set(SW4STM32_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SW4STM32")
set(ECLIPSE_PROJECT_DIR "${SW4STM32_DIR}/STM32F769I-Discovery_Demo")
set(LINKER_SCRIPT "${ECLIPSE_PROJECT_DIR}/STM32F769NIHx_FLASH.ld")

if(NOT EXISTS "${CUBE_FW}/Drivers")
  message(FATAL_ERROR "CUBE_FW does not point to STM32CubeF7: ${CUBE_FW}")
endif()

file(READ "${ECLIPSE_PROJECT_DIR}/.project" PROJECT_XML)
string(REGEX MATCHALL "<location>[^<]+</location>" LINK_LOCATIONS "${PROJECT_XML}")

set(PROJECT_SOURCES)
foreach(LOCATION_TAG IN LISTS LINK_LOCATIONS)
  string(REGEX REPLACE "^<location>|</location>$" "" SOURCE_PATH "${LOCATION_TAG}")
  if(SOURCE_PATH MATCHES "\\.(c|s|S)$")
    string(REPLACE "PARENT-6-PROJECT_LOC/" "${CUBE_FW}/" SOURCE_PATH "${SOURCE_PATH}")
    string(REPLACE "PARENT-2-PROJECT_LOC/" "${CMAKE_CURRENT_SOURCE_DIR}/" SOURCE_PATH "${SOURCE_PATH}")
    string(REPLACE "PARENT-1-PROJECT_LOC/" "${SW4STM32_DIR}/" SOURCE_PATH "${SOURCE_PATH}")
    cmake_path(NORMAL_PATH SOURCE_PATH OUTPUT_VARIABLE SOURCE_PATH)
    if(EXISTS "${SOURCE_PATH}")
      list(APPEND PROJECT_SOURCES "${SOURCE_PATH}")
    else()
      message(WARNING "Linked source does not exist: ${SOURCE_PATH}")
    endif()
  endif()
endforeach()
list(REMOVE_DUPLICATES PROJECT_SOURCES)

add_executable(${PROJECT_NAME}.elf ${PROJECT_SOURCES})

set(CPU_FLAGS
  -mcpu=cortex-m7
  -mthumb
  -mfpu=fpv5-d16
  -mfloat-abi=hard
)

target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
  STM32F769xx
  USE_HAL_DRIVER
  USE_STM32F769I_DISCO
  USE_USB_HS
)

target_include_directories(${PROJECT_NAME}.elf PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/Config"
  "${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc"
  "${CMAKE_CURRENT_SOURCE_DIR}/Gui/STemWin_Addons"
  "${CMAKE_CURRENT_SOURCE_DIR}/Gui/Target"
  "${CMAKE_CURRENT_SOURCE_DIR}/Modules/audio_player"
  "${CMAKE_CURRENT_SOURCE_DIR}/Modules/audio_recorder"
  "${CMAKE_CURRENT_SOURCE_DIR}/Modules/Common"
  "${CMAKE_CURRENT_SOURCE_DIR}/Modules/videoplayer"
  "${CMAKE_CURRENT_SOURCE_DIR}/Modules/vnc_server"
  "${CUBE_FW}/Drivers/BSP/Components"
  "${CUBE_FW}/Drivers/BSP/Components/Common"
  "${CUBE_FW}/Drivers/BSP/STM32F769I-Discovery"
  "${CUBE_FW}/Drivers/CMSIS/Device/ST/STM32F7xx/Include"
  "${CUBE_FW}/Drivers/CMSIS/Include"
  "${CUBE_FW}/Drivers/STM32F7xx_HAL_Driver/Inc"
  "${CUBE_FW}/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy"
  "${CUBE_FW}/Middlewares/ST/STemWin/inc"
  "${CUBE_FW}/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc"
  "${CUBE_FW}/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc"
  "${CUBE_FW}/Middlewares/ST/STM32_USB_Host_Library/Core/Inc"
  "${CUBE_FW}/Middlewares/Third_Party/FatFs/src"
  "${CUBE_FW}/Middlewares/Third_Party/FatFs/src/drivers"
  "${CUBE_FW}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS"
  "${CUBE_FW}/Middlewares/Third_Party/FreeRTOS/Source/include"
  "${CUBE_FW}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1"
  "${CUBE_FW}/Middlewares/Third_Party/LwIP/src/include"
  "${CUBE_FW}/Middlewares/Third_Party/LwIP/system"
  "${CUBE_FW}/Middlewares/Third_Party/LwIP/system/OS"
  "${CUBE_FW}/Utilities/CPU"
  "${CUBE_FW}/Utilities/JPEG"
)

target_compile_options(${PROJECT_NAME}.elf PRIVATE
  ${CPU_FLAGS}
  $<$<COMPILE_LANGUAGE:C>:-std=gnu11>
  -Os
  -g3
  -ffunction-sections
  -fdata-sections
  -fmessage-length=0
  -Wno-strict-aliasing
  -Wno-unused-parameter
)

target_link_options(${PROJECT_NAME}.elf PRIVATE
  ${CPU_FLAGS}
  -T${LINKER_SCRIPT}
  -specs=nosys.specs
  -specs=nano.specs
  -Wl,--gc-sections
  -Wl,-Map=${PROJECT_NAME}.map
)

target_link_libraries(${PROJECT_NAME}.elf PRIVATE
  -Wl,--start-group
  "${CMAKE_CURRENT_SOURCE_DIR}/Gui/STemWin_Addons/STemWin_Addons_CM7_wc32.a"
  "${CUBE_FW}/Middlewares/ST/STemWin/Lib/STemWin_CM7_OS_wc32_ot.a"
  "${CUBE_FW}/Middlewares/ST/STM32_Audio/Addons/PDM/Lib/libPDMFilter_CM7_GCC_wc32.a"
  c
  m
  gcc
  nosys
  -Wl,--end-group
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
  COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
  BYPRODUCTS ${PROJECT_NAME}.hex
)

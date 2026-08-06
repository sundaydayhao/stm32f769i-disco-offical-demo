set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_BIN "C:/Users/hazh/.local/toolchains/arm-none-eabi-gcc-15.2.1-1.1/bin" CACHE PATH "GNU Arm Embedded toolchain bin directory")

set(CMAKE_C_COMPILER "${TOOLCHAIN_BIN}/arm-none-eabi-gcc.exe")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_BIN}/arm-none-eabi-gcc.exe")
set(CMAKE_OBJCOPY "${TOOLCHAIN_BIN}/arm-none-eabi-objcopy.exe" CACHE FILEPATH "objcopy")
set(CMAKE_SIZE "${TOOLCHAIN_BIN}/arm-none-eabi-size.exe" CACHE FILEPATH "size")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

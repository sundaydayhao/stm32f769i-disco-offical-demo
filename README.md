# STM32F769I-DISCO Official Demo

This repository contains the official STM32F769I-DISCO demonstration projects
copied from STM32CubeF7.

## Contents

- `STemWin/`: official STemWin GUI demonstration
- `TouchGFX/`: official TouchGFX demonstration
- `LICENSE.txt`: ST license file
- `Release_Notes.html`: STM32CubeF7 release notes

The `STemWin` demo also includes a local CMake wrapper that was added to make
the SW4STM32 project buildable with Arm GNU tools.

## External Dependency

The official projects reference drivers and middleware from STM32CubeF7. The
local build wrapper expects STM32CubeF7 at:

```powershell
C:\Users\hazh\STM32Cube\Repository\STM32Cube_FW_F7_V1.17.0
```

## Build STemWin Demo

From PowerShell:

```powershell
$env:Path='C:\Users\hazh\.local\toolchains\arm-none-eabi-gcc-15.2.1-1.1\bin;' + $env:Path
cmake -S C:\projects\stm32f769i-disco-offical-demo\STemWin -B C:\projects\stm32f769i-disco-offical-demo\STemWin\build -G Ninja -DCMAKE_TOOLCHAIN_FILE=C:\projects\stm32f769i-disco-offical-demo\STemWin\cmake\arm-none-eabi-gcc.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build C:\projects\stm32f769i-disco-offical-demo\STemWin\build --parallel
```

The generated firmware image is:

```text
STemWin/build/STM32F769I_DISCO_STemWin_Demo.hex
```

Build outputs are ignored by Git.

## Flashing

The STM32F769I-DISCO board is flashed through the onboard ST-LINK SWD interface.
The virtual COM port is only for serial communication.

The STemWin demo stores resources in external QSPI flash, so flashing requires a
tool/configuration that supports both internal flash and QSPI. The local setup
was verified with Zephyr SDK OpenOCD using `board/stm32f769i-disco.cfg`.

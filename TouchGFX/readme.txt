/**
  @page TouchGFX   STM32F769I-DISCO TouchGFX Demonstration Firmware
 
  @verbatim
  ******************************************************************************
  * @file    Demonstrations/TouchGFX/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of STM32F769I-DISCO TouchGFX Demonstration
  ******************************************************************************
  *
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @endverbatim

@par Demo Description

This is a demonstration based on TouchGFX framework for the STM32F769I Discovery board
with 800x480 LCDs attached.

Requirements:
	Resolution: 800 * 480
	BPP: 24

The demonstration features the following modules:
    - Bird Eat Coin Game
    - 2048 - Game
    - Audio player
    - MJPEG Video player
    - Home Automation
    - Date and Clock
    - Hardware integration (Junction temperature sensor and LCD brightness)


@par Keywords

Demonstration, TouchGFX

@par How to use it ?

In order to program the demonstration, you must do the following:
1- Open STM32CubeProgrammer and click on connect
2- Go to external loaders menu then select MX25L512G_STM32F769I-DISCO to program external OSPI memory
3- From Erasing and programming Menu browse to select the STM32F769I-Discovery_TouchGFX_Demo.hex file from build folder then click on start programming
4- Copy the audio and video files provided under "Utilities/Media/TouchGFX_STM32F769" folder in the USB key
5- Plug a USB micro A-Male to A-Female cable on CN15 connector
6- Plug a headphone into CN7 Connector.)


 */

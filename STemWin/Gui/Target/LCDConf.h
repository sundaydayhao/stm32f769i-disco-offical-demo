/**
  ******************************************************************************
  * @file    lcdconf.h
  * @author  MCD Application Team
  * @brief   Header for LCDConf file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
  
#include "main.h"
#include "GUI.h"
#include "GUIDRV_Lin.h"

#ifndef LCDCONF_H
#define LCDCONF_H

typedef enum
{
  LCD_CTRL_NT35510,
  LCD_CTRL_OTM8009A,
  LCD_CTRL_NONE
} LCD_Driver_t;

typedef struct
{
  int32_t      address;
  __IO int32_t      pending_buffer;
  int32_t      buffer_index;
  int32_t      xSize;
  int32_t      ySize;
  int32_t      BytesPerPixel;
  LCD_API_COLOR_CONV   *pColorConvAPI;
}
LCD_LayerPropTypedef;

#endif /* LCDCONF_H */


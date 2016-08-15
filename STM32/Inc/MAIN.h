/**********************************Mecono.CN***********************************/
/*                                                                            */
/*  @File Name : MAIN.h                                                       */
/*  @Author    : Mecono                                                       */
/*  @version   : V0.01                                                        */
/*  @Date      : 2016-04-06                                                   */
/*  @attention : MainÍ·ÎÄ¼þ                                                   */
/*                                                                            */
/******************************************************************************/
#ifndef _MAIN_
#define _MAIN_

#include "stm32f4xx_hal.h"
//#include <stdio.h>

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

IWDG_HandleTypeDef hiwdg;

SD_HandleTypeDef hsd;
HAL_SD_CardInfoTypedef SDCardInfo;

SPI_HandleTypeDef hspi1;
UART_HandleTypeDef huart1;

SRAM_HandleTypeDef hsram1;



#endif
/**********************************File  END***********************************/

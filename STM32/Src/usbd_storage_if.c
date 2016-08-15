/**
  ******************************************************************************
  * @file           : usbd_storage_if.c
  * @brief          : Memory management layer
  ******************************************************************************
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  * 1. Redistributions of source code must retain the above copyright notice,
  * this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  * this list of conditions and the following disclaimer in the documentation
  * and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of its contributors
  * may be used to endorse or promote products derived from this software
  * without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "usbd_storage_if.h"
/* USER CODE BEGIN INCLUDE */
#include "APP_W25Q128.h"
#include "stdio.h"
/* USER CODE END INCLUDE */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_STORAGE 
  * @brief usbd core module
  * @{
  */ 

/** @defgroup USBD_STORAGE_Private_TypesDefinitions
  * @{
  */ 
/* USER CODE BEGIN PRIVATE_TYPES */


    int8_t USB_STATUS_REG=0;
/* USER CODE END PRIVATE_TYPES */ 
/**
  * @}
  */ 

/** @defgroup USBD_STORAGE_Private_Defines
  * @{
  */ 
#define STORAGE_LUN_NBR                  1  
#define STORAGE_BLK_NBR                  0x10000  
#define STORAGE_BLK_SIZ                  0x200

/* USER CODE BEGIN PRIVATE_DEFINES */
/* USER CODE END PRIVATE_DEFINES */
  
/**
  * @}
  */ 

/** @defgroup USBD_STORAGE_Private_Macros
  * @{
  */ 
/* USER CODE BEGIN PRIVATE_MACRO */
/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */ 

/** @defgroup USBD_STORAGE_IF_Private_Variables
  * @{
  */
/* USB handler declaration */
/* Handle for USB Full Speed IP */

/* Handle for USB High Speed IP */
  USBD_HandleTypeDef  *hUsbDevice_1;
/* USER CODE BEGIN INQUIRY_DATA_HS */ 
/* USB Mass storage Standard Inquiry Data */
const int8_t  STORAGE_Inquirydata_HS[] = {//36
  
  /* LUN 0 */
  0x00,		
  0x80,		
  0x02,		
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x00,
  0x00,	
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0' ,'1',                     /* Version      : 4 Bytes */
}; 
/* USER CODE END INQUIRY_DATA_HS */ 
/* USER CODE BEGIN PRIVATE_VARIABLES */
/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */ 
 
/** @defgroup USBD_STORAGE_IF_Exported_Variables
  * @{
  */ 
  extern USBD_HandleTypeDef hUsbDeviceHS;  
/* USER CODE BEGIN EXPORTED_VARIABLES */


/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */ 
  
/** @defgroup USBD_STORAGE_Private_FunctionPrototypes
  * @{
  */

static int8_t STORAGE_Init_HS (uint8_t lun);
static int8_t STORAGE_GetCapacity_HS (uint8_t lun, 
                           uint32_t *block_num, 
                           uint16_t *block_size);
static int8_t  STORAGE_IsReady_HS (uint8_t lun);
static int8_t  STORAGE_IsWriteProtected_HS (uint8_t lun);
static int8_t STORAGE_Read_HS (uint8_t lun, 
                        uint8_t *buf, 
                        uint32_t blk_addr,
                        uint16_t blk_len);
static int8_t STORAGE_Write_HS (uint8_t lun, 
                        uint8_t *buf, 
                        uint32_t blk_addr,
                        uint16_t blk_len);
static int8_t STORAGE_GetMaxLun_HS (void);
/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */
/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */ 
  

USBD_StorageTypeDef USBD_Storage_Interface_fops_HS =
{
  STORAGE_Init_HS,
  STORAGE_GetCapacity_HS,
  STORAGE_IsReady_HS,
  STORAGE_IsWriteProtected_HS,
  STORAGE_Read_HS,
  STORAGE_Write_HS,
  STORAGE_GetMaxLun_HS,
  (int8_t *)STORAGE_Inquirydata_HS,
};

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : STORAGE_Init_HS
* Description    : 
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Init_HS (uint8_t lun)
{
  /* USER CODE BEGIN 9 */ 
	W25X40_Init();
	printf("Init USB SPI Flash\r\n");
  return (USBD_OK);
  /* USER CODE END 9 */ 
}

/*******************************************************************************
* Function Name  : STORAGE_GetCapacity_HS
* Description    : 
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_GetCapacity_HS (uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  /* USER CODE BEGIN 10 */   
  *block_num  = STORAGE_BLK_NBR;
  *block_size = STORAGE_BLK_SIZ;
//	printf("%X,%X\r\n",*block_num,*block_size);
  return (USBD_OK);
  /* USER CODE END 10 */ 
}

/*******************************************************************************
* Function Name  : STORAGE_IsReady_HS
* Description    : 
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t  STORAGE_IsReady_HS (uint8_t lun)
{
  /* USER CODE BEGIN 11 */ 
	USB_STATUS_REG|=0X10;
  return (USBD_OK);
  /* USER CODE END 11 */ 
}

/*******************************************************************************
* Function Name  : STORAGE_IsWriteProtected_HS
* Description    : 
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t  STORAGE_IsWriteProtected_HS (uint8_t lun)
{
  /* USER CODE BEGIN 12 */ 
  return (USBD_OK);
  /* USER CODE END 12 */ 
}

/*******************************************************************************
* Function Name  : STORAGE_Read_HS
* Description    : 
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Read_HS (uint8_t lun, 
                        uint8_t *buf, 
                        uint32_t blk_addr,                       
                        uint16_t blk_len)
{
  /* USER CODE BEGIN 13 */ 
  int res = 0;
	
  USB_STATUS_REG|=0X02;
	res = W25X40_Sector_Read(blk_addr , buf);
  return res;
  /* USER CODE END 13 */ 
}

/*******************************************************************************
* Function Name  : STORAGE_Write_HS
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Write_HS (uint8_t lun, 
                         uint8_t *buf, 
                         uint32_t blk_addr,
                         uint16_t blk_len)
{
  /* USER CODE BEGIN 14 */ 
  int res = 0;
  USB_STATUS_REG|=0X01;
	
	res = W25X40_Sector_Write(blk_addr, buf);
	
	return res;

  /* USER CODE END 14 */ 
}

/*******************************************************************************
* Function Name  : STORAGE_GetMaxLun_HS
* Description    : 
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_GetMaxLun_HS (void)
{
  /* USER CODE BEGIN 15 */ 
  return (STORAGE_LUN_NBR - 1);
  /* USER CODE END 15 */   
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */
/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */ 

/**
  * @}
  */  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**********************************Mecono.CN***********************************/
/*                                                                            */
/*  @File Name : APP_COG.c                                                    */
/*  @Author    : Mecono                                                       */
/*  @version   : V0.01                                                        */
/*  @Date      : 2014-06-17                                                   */
/*  @attention : COG Ӧ�ú���                                                 */
/*                                                                            */
/******************************************************************************/
#include "APP_COG.h"
#include "ASCII_8x6.c"

static uint8_t COG_Pixel[8][128];
extern char ASCII_8X6[96][6];

/******************************************************************************/
/*  @������   : COG_Init()                                                    */
/*  @����     :                                                               */
/*  @���     :                                                               */
/*  @�޸�ʱ�� : 2014-06-02                                                    */
/*  @����     : COG��ʼ��                                                     */
/******************************************************************************/
void COG_Init()
{
//    COG_BSP_Init();     /* PIN ��ʼ�� */
    COG_SendCMD(0xE2);  /* ����λ */
    COG_SendCMD(0x2C);  /* ��ѹ����1 */
    COG_SendCMD(0x2E);  /* ��ѹ����2 */
    COG_SendCMD(0x2F);  /* ��ѹ����3 */
    COG_SendCMD(0x23);  /* �ֵ��Աȶȣ������÷�Χ 0x20~0x27 */
    COG_SendCMD(0x81);  /* ΢���Աȶ� */
    COG_SendCMD(0x28);  /* ΢���Աȶȵ�ֵ�������÷�Χ 0x00~0x3F */
    COG_SendCMD(0xA2);  /* 1/9 ƫѹ�ȣ�bias��*/
    COG_SendCMD(0xC8);  /* ��ɨ��˳�򣺴��ϵ��� */
    COG_SendCMD(0xA0);  /* ��ɨ��˳�򣺴����� */
    COG_SendCMD(0x40);  /* ��ʼ��:��һ�п�ʼ */
    COG_SendCMD(0xAF);  /* ��ʼ��ʾ */
    COG_SendCMD(0xA4);  /* ��ʾ */
    COG_Clear();
}

/******************************************************************************/
/*  @������   : void COG_Address(uint16_t x, uint8_t y)                       */
/*  @����     : uint16_t x ������                                             */
/*              uint8_t  y ������                                             */
/*  @���     ����                                                            */
/*  @�޸�ʱ�� : 2014-06-08                                                    */
/*  @����     : ��������                                                      */
/******************************************************************************/
void COG_Address(uint16_t x, uint8_t y)
{
    x -= 1;
    y -= 1;
	
    COG_SendCMD(0xB0 + y);
    COG_SendCMD((((uint8_t)x >> 4) & 0x0F) + 0x10);
    COG_SendCMD((uint8_t)x & 0x0F);
}

/******************************************************************************/
/*  @������   : COG_Clear                                                     */
/*  @����     :                                                               */
/*  @���     ����                                                            */
/*  @�޸�ʱ�� : 2014-06-20                                                    */
/*  @����     : ����                                                          */
/******************************************************************************/
void COG_Clear()
{
    uint8_t y = 0;
    uint16_t i = 0;
    for(y = 1; y < 9; y++) {
        COG_Address(1 , y);
        for(i = 0; i < 128; i++)
        COG_SendDATA(0x00);
    }
}

/******************************************************************************/
/*  @������   : COG_SetPixel                                                  */
/*  @����     : uint16_t x   ���غ�����                                       */
/*              uint8_t  y   ����������                                       */
/*              uint8_t  set 1 ��ʾ 0 ����ʾ                                  */
/*  @���     ����                                                            */
/*  @�޸�ʱ�� : 2014-06-08                                                    */
/*  @����     : ������ʾ���ص�                                                */
/******************************************************************************/
void COG_SetPixel(uint16_t x, uint8_t y,uint8_t set)
{
    uint8_t pageY = 0;
    y--;
    pageY = y/8 + 1;
	y %= 8;	
	COG_Pixel[0][7] = 0xff;
    switch(set) {
        case 0:
            COG_Address(x, pageY);
            x--;
            pageY--;
			COG_Pixel[pageY][x] = COG_Pixel[pageY][x] & (~(uint8_t)(1 << y));		  
            COG_SendDATA(COG_Pixel[pageY][x]);
            break;
        case 1:
            COG_Address(x, pageY);
            x--;
            pageY--;
            COG_Pixel[pageY][x] = COG_Pixel[pageY][x] | ((uint8_t)(1 << y));
            COG_SendDATA(COG_Pixel[pageY][x]);
            break;
        default: 
            break;
    }
}


/******************************************************************************/
/*  @������   : COG_DPChar8x6                                                 */
/*  @����     : uint16_t x   ���غ�����                                       */
/*              uint8_t  y   ����������                                       */
/*              char ascii   ��ʾ���ַ�                                       */
/*  @���     ��2 X������Ч                                                   */
/*              1 Y������Ч                                                   */
/*              0 ��ʾ�ɹ�                                                    */
/*  @�޸�ʱ�� : 2014-07-30                                                    */
/*  @����     : ��ʾASCII 8x6 �ַ�                                            */
/******************************************************************************/
uint8_t COG_DPChar8x6(uint16_t x, uint8_t y, char ascii)
{
    uint16_t i;
    uint16_t Xaddress = 0;
    uint8_t  Yaddress = 0;
    if((x + 8) > 128)
        return 2;
    if(y > 4)
        return 1;
    Xaddress = x - 1;
    Yaddress = y - 1;
		ascii = ascii - 0x20;
    COG_Address(Xaddress, Yaddress);
    for(i = 0; i < 6; i++){
        COG_Pixel[Yaddress][Xaddress] = ASCII_8X6[ascii][i];
        COG_SendDATA(COG_Pixel[Yaddress][Xaddress]);
        Xaddress++;
    }
    return 0;
}

/******************************************************************************/
/*  @������   : COG_DPChars8x6                                                */
/*  @����     : uint16_t x      ���غ�����                                    */
/*              uint8_t  y      ����������                                    */
/*              char *address   ��ʾ�ַ����׵�ַ                              */
/*              uint16_t number ��ʾ�ַ�������                                */
/*  @���     ��1 ������Ч                                                    */
/*              0 ��ʾ�ɹ�                                                    */
/*  @�޸�ʱ�� : 2014-07-30                                                    */
/*  @����     : ��ʾASCII 8x6 �ַ�                                            */
/******************************************************************************/
uint8_t COG_DPChars8x6(uint16_t x, uint8_t y, char *address, uint16_t number)
{
    uint16_t i, j;
    uint16_t Xaddress = 0;
    uint8_t  Yaddress = 0;
    if(((x + 8) > 128) || (y > 4))
        return 1;
    else {
        Xaddress = x;
        Yaddress = y;
    }
}

/******************************************************************************/
/*  @������   : W25X40_Read                                                   */
/*  @����     : uint32_t address : 24 bit address                             */
/*              uint16_t len :��ȡ����                                        */
/*              uint8_t *buffer : ��ȡ����buffer��ָ��                        */
/*  @���     ����                                                            */
/*  @�޸�ʱ�� : 2014-06-08                                                    */
/*  @����     : Flash Read                                                    */
/******************************************************************************/


/******************************************************************************/
/*  @������   : W25X40_Write                                                  */
/*  @����     : uint32_t address : 24 bit address                             */
/*              uint16_t len :д�볤��                                        */
/*              uint8_t *buffer : д�뻺��buffer��ָ��                        */
/*  @���     ����                                                            */
/*  @�޸�ʱ�� : 2014-06-08                                                    */
/*  @����     : Flash Write                                                   */
/******************************************************************************/


/******************************************************************************/
/*  @������   : W25X40_Sector_Erase                                           */
/*  @����     : uint32_t address : 24 bit address                             */
/*  @���     ����                                                            */
/*  @�޸�ʱ�� : 2014-06-08                                                    */
/*  @����     : Flash Sector Erase                                            */
/******************************************************************************/


/******************************************************************************/
/*  @������   : SPI1_SendByte                                                 */
/*  @����     :                                                               */
/*  @���     ����                                                            */
/*  @�޸�ʱ�� : 2014-06-02                                                    */
/*  @����     : SPI1��ʼ��                                                    */
/******************************************************************************/

/**********************************File  END***********************************/
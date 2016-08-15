/**********************************Mecono.CN***********************************/
/*                                                                            */
/*  @File Name : DRI_FPGA.c                                                    */
/*  @Author    : Mecono                                                       */
/*  @version   : V0.01                                                        */
/*  @Date      : 2016-05-26                                                   */
/*  @attention :                                                              */
/*                                                                            */
/******************************************************************************/
#include "DRI_FPGA.h"

/******************************************************************************/
/*  @函数名   : FPGA_Init                                                     */
/*  @输入     : fp   文件路径                                                 */
/*              path 文件路径                                                 */
/*  @输出     :                                                               */
/*  @修改时间 : 2016-05-26                                                    */
/*  @描述     : FPGA初始化                                                    */
/******************************************************************************/
FPGA_STATUS FPGA_Init(FIL* fp, const TCHAR* path)
{
    uint16_t i, a, j;
    UINT br;
    BYTE buffer[512];
    i = f_open(fp, path, FA_OPEN_EXISTING | FA_READ);
    br = 1;
//    a = 0;
    nCONFIG_LOW();
    FNSTATUS_LOW();
    FCONG_DONE_LOW();
    nCONFIG_HIGH();
    FNSTATUS_HIGH();

    for(;;) {
        for(a = 0; a < 512; a++)
        buffer[a]=0;
        i = f_read(fp, buffer, sizeof(buffer), &br);
        for(a = 0; a < 512; a++) {
            for(j = 0; j < 8; j++) {
                FDCLK_LOW();
                if(buffer[a] & 0x01)
                    FDATA0_HIGH();
                else
                    FDATA0_LOW();
                FDCLK_HIGH();
                buffer[a] = buffer[a] >> 1;
            }
        }
        if(i || br == 0) break;
    }
    FCONG_DONE_HIGH();
    for(a=0;a<1000;a++){
        FDCLK_LOW();
        FDCLK_HIGH();
    }
    FDCLK_LOW();
    f_close(fp);
    printf("\r\n FPGA Init OK\r\n");

    return FPGA_OK;
}


/**********************************File  END***********************************/

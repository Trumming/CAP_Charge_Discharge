
#include "main.h"

#ifdef FRAMEWORK_H

/****************************************************************************/
/*��������  Package_Float                                                   */
/*����˵����������������ת�������飬�������ϴ�                                 */
/*�����������                                                              */
/*�����������                                                              */
/****************************************************************************/
void Package_Float(float data,u8 *buf)
{
    u8 *addr;
    addr = (u8 *)&data;
    buf[0]=addr[1];
    buf[1]=addr[0];
    buf[2]=addr[3];
    buf[3]=addr[2];
}

/****************************************************************************/
/*��������Un  Package_Float                                                   */
/*����˵�����������յ�������ת�����ڲ�����������                                 */
/*�����������                                                              */
/*�����������                                                              */
/****************************************************************************/
void UnPackage_Float(u8 *buf,float *data)
{
    u8 *addr;
    addr = (u8 *)data;
    addr[0]=buf[1];
    addr[1]=buf[0];
    addr[2]=buf[3];
    addr[3]=buf[2];
}


/****************************************************************************/
/*��������  Error_Indicator                                                 */
/*����˵��������ָʾ�����д�����ʱ��LEDָʾ����˸һ�£�����ת��               */
/*���������time��LED��״̬�ĳ���ʱ��                                         */
/*�����������                                                              */
/****************************************************************************/
void Error_Indicator(u16 time)
{
    if(Get_LED_Status() == OFF)
    {
        Blink_LED_Status(time);
    }
}

/****************************************************************************/
/*��������  Para_Download                                                 */
/*����˵�����������أ��Ȳ�д��д��               */
/*�����������                                         */
/*�����������                                                              */
/****************************************************************************/
void Para_Download(void)
{
    u8 flashdata[512];
    if(CMD_ParaDownload_Independent == ON)
    {
        CMD_ParaDownload_Independent = OFF;
        FlashErase(PARA_BASEADDR,1);
        flashdata[0]=0xAA;
        flashdata[1]=0x55;
        flashdata[2]=0xAA;
        flashdata[3]=0x55;
        memcpy(&flashdata[4],&Global_Variable.Para_Independence,sizeof(Global_Variable.Para_Independence));
        FlashWriteData(PARA_BASEADDR,flashdata,512+4);
        Task_IO_Init();
    }
}



void ReadFlashData(void)
{
    u8 flashdata[512];
    FlashReadData(PARA_BASEADDR,flashdata,512);
    if((flashdata[0]==0xAA)&&(flashdata[1]==0x55)&&(flashdata[2]==0xAA)&&(flashdata[3]==0x55))
    {
        memcpy(&Global_Variable.Para_Independence,&flashdata[4],sizeof(Global_Variable.Para_Independence));
    }
    else
    {
        Global_Variable.Para_Independence.Page1_Index = 0;
    }
    
}


#endif


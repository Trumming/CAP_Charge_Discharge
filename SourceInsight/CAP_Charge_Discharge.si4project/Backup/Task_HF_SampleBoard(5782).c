#include "config.h"
//#include "cmsis_os.h"
#include "string.h"
#include "Task_HF_SampleBoard.h"


static struct RTU_ReqBlock RTU_Req_ReadVoltage_Thres= //RTUÊý¾ÝÇëÇó¿é,¶ÁÈ¡µ±Ç°µç»úÔËÐÐ¹¦ÂÊ
{
	LIST_HEAD_INIT(RTU_Req_ReadVoltage_Thres.Entry),
  0,                                          //执行次数�?-无限�?
	UART_CHN_AD_SAMPLE,                      	//执行通道
	0x01,                                       //从节点站地址
	FUNC_RD_HOLDREG,                            //功能�?3
	EXCUTE_SUCCESS,                             //执行结果,用于�?
	0x0005,                                     //操作寄存器地址
	0x01,                                       //操作寄存器数�?
	(uint16_t*)&VoltageData[0]      	//执行的数据，读取的寄存器数据或写操作的数�?
};


void Platform_Init(void)
{
	uint8_t i;
  for(i=0;i<NUM_UARTCHANNEL;i++)
	{
			if(RTU_CHN_ENABLE[i] == TRUE)
			{
					RTU_Init(i);//第一个参数表示发送间隔时间，第二个参数表示超时时�?
			}
	}
  UartOpFunc[USART_1]._send = USART1_Send_Data;
  UartOpFunc[USART_2]._send = USART2_Send_Data;
  UartOpFunc[USART_3]._send = USART3_Send_Data;
  UartOpFunc[UART_5]._send = UART5_Send_Data;
  UartOpFunc[USART_6]._send = USART6_Send_Data;
  RTU_AddReqBlock(&rtu_ctx[RTU_Req_ReadCurrent_Thres.chnindex],&RTU_Req_ReadCurrent_Thres);
	RTU_AddReqBlock(&rtu_ctx[RTU_Req_ReadVoltage_Thres.chnindex],&RTU_Req_ReadVoltage_Thres);
}


	
/********************************************************************************/
/*��������  HF_SampleBoard_Init                                                             */
/*����˵����ģ���ʼ������                                                        */
/*�����������*/
/*�����������                                                                   */
/********************************************************************************/
void HF_SampleBoard_Init(void)
{//ģ���ʼ��

}

/********************************************************************************/
/*��������  Task_MBRTU_Master                                                       */
/*����˵����RTU master��task, ��ʱ���ã�����CPU load                                         */
/*�����������                                                                        */
/*�����������                                                                        */
/*******************************************************************************/
void HF_SampleBoard_MainFunction(void *p_arg)
{

}


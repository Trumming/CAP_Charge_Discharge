#include "config.h"
#include "cmsis_os.h"
#include "interface.h"
#include "string.h"
#include "Task_LCD_Display.h"
#include "FM_Uart.h"

static uint8_t index;

/********************************************************************************/
/*��������  LCD_Display_Init                                                             */
/*����˵����ģ���ʼ������                                                        */
/*�����������*/
/*�����������                                                                   */
/********************************************************************************/
void LCD_Display_Init(void)
{//ģ���ʼ��
  //RTU_AddReqBlock(&rtu_ctx[RTU_Req_ReadCurrent_Thres.chnindex],&RTU_Req_ReadCurrent_Thres);
  index++;
}

/********************************************************************************/
/*��������  LCD_Display_MainFunction                                                       */
/*����˵����RTU master��task, ��ʱ���ã�����CPU load                                         */
/*�����������                                                                        */
/*�����������                                                                        */
/*******************************************************************************/
void LCD_Display_MainFunction(void *p_arg)
{
  USARTCHN_Recv_t Recv_Data;
  if( Que_UartID[UART_CHN_LCD_DISPLAY] != 0)    
  {// �Ӵ����Ķ����н���һ����Ϣ�������Ϣ��Ч�������ڴ˴�    
    if(xQueueReceive( Que_UartID[UART_CHN_LCD_DISPLAY], &(Recv_Data), ( portTickType ) 10 ) )        
    {// ����pcRxedMessage ָ����vATask����Ͷ�ݽ����Ľṹ��Amessage����        }    }
      index++;
      if(index%3 == 0)
      {
        LCD_Display_Init();
      }
    }
	}
}


#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "main.h"

#define APP_CRC_ADDR   0x308000
#define SER_PDU_SIZE_MAX 500u

enum USART_CHN{//����ͨ��
    USART_1=0,USART_2,USART_3,UART_5,USART_6,
    NUM_UARTCHN
};//UART1 UART2 UART3 UART5 UART6


/******************************************************************************************/
#define LED2_ON             HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
#define LED2_OFF            HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
#define LED3_ON             HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);
#define LED3_OFF            HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);

//RTUͨ������
#define UART_CHN_POWER_CTRL       						UART_5
#define UART_CHN_AD_SAMPLE               			USART_6
#define RTU_ENABLE_LIST \
{\
    FALSE,FALSE,FALSE,TRUE,TRUE \
}//UART1 UART2 UART3 UART5 UART6




/******************************************************************************************/


#define OS_ENTER_CRITICAL() 								taskENTER_CRITICAL()
#define OS_EXIT_CRITICAL() 									taskEXIT_CRITICAL()

#define ON   														1u
#define OFF 														0u

#define TRUE  													1u
#define FALSE 													0u

#define NUM_UARTCHANNEL               5  //����ͨ��������
#define SCI_BUF_MAXLEN              256  //���ڽ��ջ���������ֽ�����






#endif



#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "main.h"

#define APP_CRC_ADDR   0x308000

enum USART_CHN{//����ͨ��
    USART_1=0,USART_2,USART_3,UART_5,USART_6,
    NUM_UARTCHN
};//UART1 UART2 UART3 UART5 UART6

#define NUM_UARTCHANNEL               5  //����ͨ��������
#define SCI_BUF_MAXLEN              256  //���ڽ��ջ���������ֽ�����

/******************************************************************************************/
#define LED2_ON                         HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
#define LED2_OFF                        HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
#define LED2_SETTING(n)    \
  { if(n==1) {HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);} \
    else{HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);}
#define LED3_ON                         HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);
#define LED3_OFF                        HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);
#define LED3_SETTING(n)    \
  { if(n==1) {HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);} \
    else{HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);}


//�����ź�
#define READ_ENABLE_STATUS              HAL_GPIO_ReadPin(INPUT_1_GPIO_Port,INPUT_1_Pin) //ʹ���ź�
#define READ_START_STATUS               HAL_GPIO_ReadPin(INPUT_2_GPIO_Port,INPUT_2_Pin) //�����ź�
  
//����ź�
#define PULSE_OUTPUT

#define DEV_RUNNING_SETTING(n)    \
  { if(n==1) {HAL_GPIO_WritePin(RELAY_1_GPIO_Port,RELAY_1_Pin,GPIO_PIN_SET);} \
    else{HAL_GPIO_WritePin(RELAY_1_GPIO_Port,RELAY_1_Pin,GPIO_PIN_RESET);} //�豸����ָʾ��
#define DEV_WARNING_SETTING(n)    \
      { if(n==1) {HAL_GPIO_WritePin(RELAY_2_GPIO_Port,RELAY_2_Pin,GPIO_PIN_SET);} \
        else{HAL_GPIO_WritePin(RELAY_2_GPIO_Port,RELAY_2_Pin,GPIO_PIN_RESET);} //�豸����ָʾ��
#define TEST_PASS_SETTING(n)    \
  { if(n==1) {HAL_GPIO_WritePin(RELAY_3_GPIO_Port,RELAY_3_Pin,GPIO_PIN_SET);} \
    else{HAL_GPIO_WritePin(RELAY_3_GPIO_Port,RELAY_3_Pin,GPIO_PIN_RESET);} //��Ʒ�ź�
#define TEST_FAILED_SETTING(n)    \
  { if(n==1) {HAL_GPIO_WritePin(RELAY_4_GPIO_Port,RELAY_4_Pin,GPIO_PIN_SET);} \
    else{HAL_GPIO_WritePin(RELAY_4_GPIO_Port,RELAY_4_Pin,GPIO_PIN_RESET);} //�쳣�ź�

#define USART1_485_TX_ENABLE            HAL_GPIO_WritePin(USART1_485_EN_GPIO_Port,USART1_485_EN_Pin,GPIO_PIN_SET);
#define USART1_485_RX_ENABLE            HAL_GPIO_WritePin(USART1_485_EN_GPIO_Port,USART1_485_EN_Pin,GPIO_PIN_RESET);
#define UART5_485_TX_ENABLE             HAL_GPIO_WritePin(UART5_485_EN_GPIO_Port,UART5_485_EN_Pin,GPIO_PIN_SET);
#define UART5_485_RX_ENABLE             HAL_GPIO_WritePin(UART5_485_EN_GPIO_Port,UART5_485_EN_Pin,GPIO_PIN_RESET);


//RTUͨ������
#define UART_CHN_LCD_DISPLAY       						USART_3     //7 inch��ʾ��ͨѶͨ��
#define UART_CHN_POWER_CTRL               		UART_5      //ֱ����ԴͨѶͨ��

//�Զ���Э��
#define UART_CHN_AD_SAMPLE               			USART_6     //��Ƶ������ͨѶͨ��
#define UART_CHN_PC_COMM               			  USART_1     //��λ��ͨѶͨ��


#define RTU_ENABLE_LIST \
{\
    FALSE,FALSE,TRUE,TRUE,FALSE \
}//UART1 UART2 UART3 UART5 UART6




/******************************************************************************************/


#define OS_ENTER_CRITICAL() 								taskENTER_CRITICAL()
#define OS_EXIT_CRITICAL() 									taskEXIT_CRITICAL()

#define ON   														1u
#define OFF 														0u

#define TRUE  													1u
#define FALSE 													0u


#endif



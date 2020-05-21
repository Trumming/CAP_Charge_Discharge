#ifndef __DR_UART_H
#define __DR_UART_H

#include "stm32f2xx_hal.h"
#include "interface.h"

typedef struct USARTCAN_Recv_info
{
		uint8_t newupd;//���ݸ��±�־λ
    uint16_t lenth; //�ֽ�����
    uint8_t datatype;//��������
    uint8_t databuf[SCI_BUF_MAXLEN];//��Ч����
}USARTCHN_Recv_t;
extern USARTCHN_Recv_t USARTCHN_Recv[NUM_UARTCHN];

typedef struct Interface_Info_t
{
    uint8_t Usart[NUM_UARTCHANNEL][uartcfgnum];  //������������
    const struct ProtType_t UsartProt[NUM_UARTCHANNEL];//����֡ͷ֡β����
    uint32_t   addr;//modbus��ʼ��ַ
    uint32_t   datalen;//ÿ��ͨ��mb�ĳ��ȣ�ʵ�ʳ���Ϊ��ֵ-2����Ϊ��������ΪЭ�����ݣ�һ��Ϊ��־λ���ڶ���Ϊ�ֽ�����
    uint8_t  	sid;//վ��ַ
}Interface_Info;
extern Interface_Info UsartCHN_Data;//


#if 0
void USART1_IRQ(unsigned char data);
void USART2_IRQ(unsigned char data);
void USART3_IRQ(unsigned char data);
void UART4_IRQ(unsigned char data);
void UART5_IRQ(unsigned char data);

void USART1_Send_Data(uint8_t *send_buff,uint16_t length);
void USART2_Send_Data(uint8_t *send_buff,uint16_t length);
void USART3_Send_Data(uint8_t *send_buff,uint16_t length);
void UART4_Send_Data(uint8_t *send_buff,uint16_t length);
void UART5_Send_Data(uint8_t *send_buff,uint16_t length);

#endif

void FM_Usart_Init(void);
void USART_Timer100us(void);
void UsartRecieveData(uint8_t channel,uint8_t recdata);
void USART3_Send_Data(uint8_t *send_buff,uint16_t length);
void UART5_Send_Data(uint8_t *send_buff,uint16_t length);




#endif



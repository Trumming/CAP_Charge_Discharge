#include "interface.h"

#ifdef __INTERFACE_H_
#include "stm32f2xx_hal.h"
#include "FM_Uart.h"
#include "Task_MB_RTU_Master.h"


char project_version[] = {"CAP_Charge_Discharge-V0.10 20200518"};

const  uint32_t   APPL_CRC __attribute__((at(APP_CRC_ADDR)))={0xA1A2A3A4};
               
UartOpFunc_t UartOpFunc[NUM_UARTCHANNEL];
uint8_t RTU_CHN_ENABLE[NUM_UARTCHANNEL] = RTU_ENABLE_LIST;

uint16_t CurrentData[10];
uint16_t VoltageData[10];


void Platform_Init(void)
{
	uint8_t i;
  for(i=0;i<NUM_UARTCHANNEL;i++)
	{
			if(RTU_CHN_ENABLE[i] == TRUE)
			{
					RTU_Init(i);//RTU��ʼ��������Ϊͨ����
			}
	}
  UartOpFunc[USART_1]._send = USART1_Send_Data;
  UartOpFunc[USART_2]._send = USART2_Send_Data;
  UartOpFunc[USART_3]._send = USART3_Send_Data;
  UartOpFunc[UART_5]._send = UART5_Send_Data;
  UartOpFunc[USART_6]._send = USART6_Send_Data;
}


uint8_t Check_XOR(uint8_t *data,uint8_t lenth)//���У��
{
    uint8_t i,temp;
    temp=0;
    for(i=0;i<lenth;i++)
    {
        temp ^= data[i];
    }
    return temp;
}

uint8_t AscToHex(uint8_t aChar)//ASCIIתhex�����������Χ0x00-0x0F�����뷶ΧΪ0x30-0x39,0x41-0x46��0x61-0x66
{
    uint8_t ret;
    if((aChar >= 0x30)&&(aChar <= 0x39))
    {
        ret = aChar - 0x30;
    }
    else if((aChar >= 0x41)&&(aChar <= 0x46))
    {
        ret = aChar - 0x37;
    }
    else if((aChar >= 0x61)&&(aChar <= 0x66))
    {
       ret = aChar - 0x57;
    }
    else
    {        
       ret = 0xFF;
    }
    return ret;
}

uint8_t HexToAsc(uint8_t aHex)//HEXתASCII�����������Χ0x30-0x39,0x41-0x46,���뷶ΧΪ0x00-0x0F
{
    uint8_t ret;
    if(aHex <=9 )
    {
        ret = aHex + 0x30;
    }
    else if((aHex >= 10)&&(aHex <= 15)) 
    {
        ret =  aHex + 0x37;
    }
    else
    {
        ret = 0xFF;
    }
    return ret;
}

/****************************************************************************/
/*��������  Float_To_Array                                                   */
/*����˵����������������ת�������飬�������ϴ�                                 */
/*�����������                                                              */
/*�����������                                                              */
/****************************************************************************/
void Float_To_Array(float data,uint8_t *buf)
{
    uint8_t *addr;
    addr = (uint8_t *)&data;
    buf[0]=addr[1];
    buf[1]=addr[0];
    buf[2]=addr[3];
    buf[3]=addr[2];
}

/****************************************************************************/
/*��������Array_To_Float                                                   */
/*����˵�����������յ�������ת�����ڲ�����������                                 */
/*�����������                                                              */
/*�����������                                                              */
/****************************************************************************/
void Array_To_Float(uint8_t *buf,float *data)
{
    uint8_t *addr;
    addr = (uint8_t *)data;
    addr[0]=buf[1];
    addr[1]=buf[0];
    addr[2]=buf[3];
    addr[3]=buf[2];
}



#endif










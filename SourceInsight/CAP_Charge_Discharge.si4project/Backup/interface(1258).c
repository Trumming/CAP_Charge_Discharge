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

typedef struct 
{
  uint8_t set_en;
  uint16_t  set_value;
}SetValueType;

struct DC_Power_Data_t
{
  SetValueType SetVoltage;        //��ѹ����
  SetValueType SetCurrent;        //��������
  SetValueType SetOutSts;         //���״̬����
  SetValueType SetRunMode;        //��Դ����ģʽ
  SetValueType SetPowerReset;     //��Դ��λ
  SetValueType SetPowerCtrlMode;  //��ԴԶ�˻򱾵ؿ���
};
static struct DC_Power_Data_t DC_Power_Data;

//��ȡ���������ѹֵ
//����ֵ���洢��ǰ���صĵ�ѹֵ
//����ֵ������������ʱΪTRUE������ΪFALSE
uint8_t Read_DC_Power_Setting_Voltage(uint16_t* Voltage)
{
  uint8_t ret=FALSE;
  if(DC_Power_Data.SetVoltage.set_en == ON)
  {
    ret = TRUE;
    DC_Power_Data.SetVoltage.set_en = OFF;
  }
  *Voltage = DC_Power_Data.SetVoltage.set_value;
  return ret;
}

//���������ѹֵ
//����ֵ�����õ�ѹֵ
//����ֵ��void
void Write_DC_Power_Setting_Voltage(uint16_t Voltage)
{
  DC_Power_Data.SetVoltage.set_value = Voltage;
  DC_Power_Data.SetVoltage.set_en = ON;
}

//��ȡ�����������ֵ
//����ֵ���洢��ǰ���صĵ���ֵ
//����ֵ�������õ�����ʱΪTRUE������ΪFALSE
uint8_t Read_DC_Power_Setting_Current(uint16_t* Current)
{
  uint8_t ret=FALSE;
  if(DC_Power_Data.SetCurrent.set_en == ON)
  {
    ret = TRUE;
    DC_Power_Data.SetCurrent.set_en = OFF;
  }
  *Current = DC_Power_Data.SetCurrent.set_value;
  return ret;
}

//�����������ֵ
//����ֵ�����õ���ֵ
//����ֵ��void
void Write_DC_Power_Setting_Current(uint16_t Current)
{
  DC_Power_Data.SetCurrent.set_value = Current;
  DC_Power_Data.SetCurrent.set_en = ON;
}

//��ȡ�������״̬����,0x00Ϊ����״̬��0x01Ϊ���״̬
//����ֵ���洢��ǰ���ص����״̬����
//����ֵ������������ʱΪTRUE������ΪFALSE
uint8_t Read_DC_Power_Setting_OutputStatus(uint16_t* OutputStatus)
{
  uint8_t ret=FALSE;
  if(DC_Power_Data.SetOutSts.set_en == ON)
  {
    ret = TRUE;
    DC_Power_Data.SetOutSts.set_en = OFF;
  }
  *OutputStatus = DC_Power_Data.SetOutSts.set_value;
  return ret;
}

//�������״̬����
//����ֵ�����״̬����
//����ֵ��void
void Write_DC_Power_Setting_OutputStatuse(uint16_t OutputStatus)
{
  DC_Power_Data.SetOutSts.set_value = OutputStatus;
  DC_Power_Data.SetOutSts.set_en = ON;
}

//��ȡ���õ�Դ����ģʽ
//����ֵ���洢��ǰ���صĵ�Դ����ģʽ
//����ֵ������������ʱΪTRUE������ΪFALSE
uint8_t Read_DC_Power_Setting_RunMode(uint16_t* RunMode)
{
  uint8_t ret=FALSE;
  if(DC_Power_Data.SetRunMode.set_en == ON)
  {
    ret = TRUE;
    DC_Power_Data.SetRunMode.set_en == OFF;
  }
  *RunMode = DC_Power_Data.SetRunMode.set_value;
  return ret;
}

//���õ�Դ����ģʽ
//����ֵ�����õ�Դ����ģʽ
//����ֵ��void
void Write_DC_Power_Setting_RunMode(uint16_t RunMode)
{
  DC_Power_Data.SetRunMode.set_value = RunMode;
  DC_Power_Data.SetRunMode.set_en = ON;
}

//��ȡ��Դ��λ����
//����ֵ���洢��ǰ���صĵ�Դ��λ����
//����ֵ������������ʱΪTRUE������ΪFALSE
uint8_t Read_DC_Power_Setting_PowerReset(uint16_t* PowerReset)
{
  uint8_t ret=FALSE;
  if(DC_Power_Data.SetPowerReset.set_en == ON)
  {
    ret = TRUE;
    DC_Power_Data.SetPowerReset.set_en = OFF;
  }
  *PowerReset = DC_Power_Data.SetPowerReset.set_value;
  return ret;
}

//���õ�Դ��λ����
//����ֵ�����õ�Դ��λ����
//����ֵ��void
void Write_DC_Power_Setting_PowerReset(uint16_t PowerReset)
{
  DC_Power_Data.SetPowerReset.set_value = PowerReset;
  DC_Power_Data.SetPowerReset.set_en = ON;
}

//��ȡ���õ�Դ����ģʽ
//����ֵ���洢��ǰ���صĵ�Դ����ģʽ
//����ֵ������������ʱΪTRUE������ΪFALSE
uint8_t Read_DC_Power_Setting_PowerCtrlMode(uint16_t* PowerCtrlMode)
{
  uint8_t ret=FALSE;
  if(DC_Power_Data.SetPowerCtrlMode.set_en == ON)
  {
    ret = TRUE;
    DC_Power_Data.SetPowerCtrlMode.set_en = OFF;
  }
  *PowerCtrlMode = DC_Power_Data.SetPowerCtrlMode.set_value;
  return ret;
}

//���õ�Դ����ģʽ
//����ֵ�����õ�Դ����ģʽ
//����ֵ��void
void Write_DC_Power_Setting_PowerCtrlMode(uint16_t PowerCtrlMode)
{
  DC_Power_Data.SetPowerCtrlMode.set_value = PowerCtrlMode;
  DC_Power_Data.SetPowerCtrlMode.set_en = ON;
}



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










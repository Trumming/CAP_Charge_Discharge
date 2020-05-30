#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include "config.h"



struct UART_Conf_Data {
    uint32_t baudrate;
    uint16_t slave_addr;
    uint16_t checksum;
};

typedef union {
    uint8_t Byte;
    struct {
        uint8_t  bit0              :1;
        uint8_t  bit1              :1;
        uint8_t  bit2              :1;
				uint8_t  bit3              :1;
        uint8_t  bit4              :1;
				uint8_t  bit5              :1;
        uint8_t  bit6              :1;
				uint8_t  bit7              :1;
    }Bits;
}Tdef_Byte;


enum UsartType{//�������������Ԫ�صĶ��壬��������ʱ���±ߵ�һ����������
    EnUart=0,uartBaudrate,Databits,Chkbits,Stopbits,Flowctrl,uartDatatype,tmout,
    uartcfgnum
};


typedef union {
  uint16_t T_byte;
  struct {
		uint8_t  btn              :4;   //����֡ͷ��֡β���ֽڸ���
		uint8_t  bit4             :1;
		uint8_t  bit5             :1;
		uint8_t  bit6             :1;
		uint8_t  en               :1;   //����֡ͷ��֡β��־
    uint16_t reserve      :8;   
	} Bits;
}Tdef_Prot;
#define FrameStartEn                  0x80u  //֡ͷʹ�ܺ�
#define FrameEndEn                    0x80u  //֡βʹ�ܺ�
enum numbyte{
  byte_1=1,byte_2,byte_3 ,byte_4 ,byte_5 ,byte_6 ,byte_7 ,byte_8 ,byte_9,byte_10     //֡ͷ��֡β���ֽ�����
};
enum checksum_t{//У��ͷ�ʽ
    CheckSum_None=0,ChkSum_And,ChkSum_Crc16
};
/*********************************************************************************************/ 
/*********************************************************************************************/ 
/*********************************************************************************************/ 

struct ProtType_t
{
    Tdef_Prot FrameStartInfo;//���λ��ʾ�Ƿ�ʹ�ܣ���4λ��ʾ�ֽ�����ֻ��ʹ�����ֽ�������Ч
    uint8_t FrameStart[8];        //֡��ʼ���ֽ���
    Tdef_Prot FrameEndInfo; //���λ��ʾ�Ƿ�ʹ�ܣ���4λ��ʾ�ֽ�����ֻ��ʹ�����ֽ�������Ч
    uint8_t FrameEnd[8];         //֡�������ֽ���
    uint8_t checksum;          //У��(0-�ޣ�1-�ͣ�2-crc16)
    uint8_t inteval;           //�ַ����ʱ�䣬��λ100us
};


typedef struct UartOpFuncTyp
{
	void (*_send)  (uint8_t *sendbuf, uint16_t lenth);
	void (*_recv)  (uint8_t channel, uint8_t data);
}UartOpFunc_t;
extern UartOpFunc_t UartOpFunc[NUM_UARTCHANNEL];



extern char platform_version[];

unsigned char AscToHex(unsigned char aChar);
unsigned char HexToAsc(unsigned char aHex);
void Platform_Init(void);
void Float_To_Array(float data,uint8_t *buf);
void Array_To_Float(uint8_t *buf,float *data);

uint8_t Read_DC_Power_Setting_Voltage(uint16_t* Voltage);
void Write_DC_Power_Setting_Voltage(uint16_t Voltage);
uint8_t Read_DC_Power_Setting_Current(uint16_t* Current);
void Write_DC_Power_Setting_Current(uint16_t Current);
uint8_t Read_DC_Power_Setting_OutputStatus(uint16_t* OutputStatus);
void Write_DC_Power_Setting_OutputStatus(uint16_t OutputStatus);
uint8_t Read_DC_Power_Setting_RunMode(uint16_t* RunMode);
void Write_DC_Power_Setting_RunMode(uint16_t RunMode);
uint8_t Read_DC_Power_Setting_PowerReset(uint16_t* PowerReset);
void Write_DC_Power_Setting_PowerReset(uint16_t PowerReset);
uint8_t Read_DC_Power_Setting_PowerCtrlMode(uint16_t* PowerCtrlMode);
void Write_DC_Power_Setting_PowerCtrlMode(uint16_t PowerCtrlMode);






#endif



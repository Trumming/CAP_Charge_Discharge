//#ifndef __VARIABLE_H_
//#define __VARIABLE_H_

#include "stm32f2xx_hal.h"
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
}BitStatus;


enum UsartType{//�������������Ԫ�صĶ��壬��������ʱ�����±ߵ�һ����������
    EnUart=0,uartBaudrate,Databits,Chkbits,Stopbits,Flowctrl,uartDatatype,tmout,
    uartcfgnum
};

enum CANType{//CAN�����������Ԫ�ض��壬��������ʱ�����±ߵ�һ����������
    EnCAN=0,canBaudrate,LocalID,DeviceID,IDNum,canDatatype,
    cancfgnum
};

enum DataType_t{//�������ͣ���������ʱ�����±ߵ�һ����������
    t_HEX=0,t_ASCII,t_BOOL,
    t_typemax
};
extern char DataType[t_typemax][20];

#define NUM_UARTCHANNEL               5  //������ͨ��
#define SCI_BUF_MAXLEN              256  //���ڷ��͡����ջ���������󳤶�,������Ҫ���ܻ���

enum USARTCAN_CHN{//���ں�CAN��ͨ�����
    RS232_1=0,RS485_1,RS485_2,RS485_3,RS485_4,CAN_CHN,
    NUM_UARTCAN
};

/*********************************************************************************************/   
/*********************************************************************************************/ 
/*********************************************************************************************/    
typedef union {
  uint16_t T_byte;
  struct {
		uint8_t  btn              :4;   //����֡ͷ��֡β���ֽڸ���
		uint8_t  bit4             :1;
		uint8_t  bit5             :1;
		uint8_t  bit6             :1;
		uint8_t  en               :1;   //����֡ͷ��֡β��־
        uint16_t reserve          :8;   
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

extern const uint8_t auchCRC16_Hi[256];
extern const uint8_t auchCRC16_Low[256];

typedef struct USARTCAN_Recv_info
{
	uint8_t newupd;//���ݸ��±�־λ
    uint16_t lenth; //�ֽ�����
    uint8_t datatype;//��������
    uint8_t databuf[SCI_BUF_MAXLEN];//��Ч����
}USARTCAN_Recv_t;
extern USARTCAN_Recv_t USARTCAN_Recv[NUM_UARTCAN];

extern volatile BitStatus Keyboard_Status;
#define CMD_Download_LocalCfg               Keyboard_Status.Bits.bit0
#define CMD_ParaDownload_Independent        Keyboard_Status.Bits.bit1


extern uint16_t g_u16_TCPIPsendlen;           //tcpip���ķ��ͳ���

extern char platform_version[];
extern char funcTion[];
extern const uint32_t RS232_baud[12] ;
extern const uint16_t RS232_lenth[2] ;
extern const uint16_t RS232_stop[2] ;
extern const uint16_t RS232_parity[3] ;
extern const uint16_t RS232_FlowCntl[4] ;

uint16_t Get_rtuCrc16(uint8_t *puchMsg,uint16_t usDataLen);
USARTCAN_Recv_t GET_UsartCAN_Recv_Result(uint8_t chanel);
unsigned char AscToHex(unsigned char aChar);
unsigned char HexToAsc(unsigned char aHex);

float GET_ADC_Result(uint8_t chanel);




//#endif



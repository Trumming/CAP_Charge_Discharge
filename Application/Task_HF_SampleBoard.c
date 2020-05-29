#include "config.h"
#include "cmsis_os.h"
#include "interface.h"
#include "string.h"
#include "Task_HF_SampleBoard.h"


struct data
{
  float  Ua;        //A·��ѹ
  float  Ia;        //A·����
  float  Pa;        //A·����
  float  PFa;       //A·��������
  float  Fa;        //A·Ƶ��
    
  float  Ub;        //B·��ѹ
  float  Ib;        //B·����
  float  Pb;        //B·����
  float  PFb;       //B·��������
  float  Fb;        //B·Ƶ��
  
  float  Uc;        //C·��ѹ
  float  Ic;        //C·����
  float  Pc;        //C·����
  float  PFc;       //C·��������
  float  Fc;        //C·Ƶ��
};

//Species 1����1· 2����2·
//CH 1 A�� 2 B�� 3 C�� 
//num �ڼ���У׼��
//data ����
void Save_Adj_Data(uint8_t Species ,uint8_t CH, uint8_t num,uint8_t *_pWriteBuf)
{
  uint8_t   _ucLen;
  uint16_t  CrcCheck;
  uint8_t   Tbuffer[20];
  _ucLen=0;
  Tbuffer[_ucLen++]=0x5A;
  Tbuffer[_ucLen++]=0x10;
  Tbuffer[_ucLen++]=Species;  // Species 1����1· 2����2·
  Tbuffer[_ucLen++]=CH;     //CH 1 A�� 2 B�� 3 C�� 
  Tbuffer[_ucLen++]=num;   //num �ڼ���У׼��
  Tbuffer[_ucLen++]=_pWriteBuf[0];
  Tbuffer[_ucLen++]=_pWriteBuf[1];
  Tbuffer[_ucLen++]=_pWriteBuf[2];
  Tbuffer[_ucLen++]=_pWriteBuf[3];
  CrcCheck = Get_rtuCrc16(Tbuffer,_ucLen);
  Tbuffer[_ucLen++] =  CrcCheck>>8;
  Tbuffer[_ucLen++] =  CrcCheck;
  UartOpFunc[UART_CHN_AD_SAMPLE]._send(Tbuffer,_ucLen);
}


/********************************************************************************/
/*��������  HF_SampleBoard_Init                                                             */
/*����˵����ģ���ʼ������                                                        */
/*�����������*/
/*�����������                                                                   */
/********************************************************************************/
void HF_SampleBoard_Init(void)
{//ģ���ʼ��
  //RTU_AddReqBlock(&rtu_ctx[RTU_Req_ReadCurrent_Thres.chnindex],&RTU_Req_ReadCurrent_Thres);
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


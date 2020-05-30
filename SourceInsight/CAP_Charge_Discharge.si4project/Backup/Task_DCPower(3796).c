#include "config.h"
#include "cmsis_os.h"
#include "interface.h"
#include "string.h"
#include "Task_DCPower.h"
#include "Task_MB_RTU_Master.h"

enum off_outputstatus{
  off_PowerStatus, off_Voltagge, off_Current, off_Power,
  off_StatusTotal
};//��Դ״̬�������ѹ�����������ʲ���ֵ
static uint16_t DC_OutputStatus[off_StatusTotal];

enum off_Setting{
  off_SetVoltage, off_SetCurrent, off_SetOutSts, off_SetRunMode, off_SetPowerReset,
  off_SettingTotal
};//
static uint16_t DC_OutputStatus[off_StatusTotal];

static RTU_ReqBlock_t RTU_Req_Read_DC_OutputStatus = //RTU���ݶ������-�����������Դ״̬�������ѹ�����������ʲ���ֵ
{
  LIST_HEAD_INIT(RTU_Req_Read_DC_OutputStatus.Entry),
  0,                                          //ִ�д�����0-���޴�
  UART_CHN_AD_SAMPLE,                         //ִ��ͨ��
	SLAVEID_DC_POWER,                           //�ӽڵ�վ��ַ
	FUNC_RD_HOLDREG,                            //������
	EXCUTE_SUCCESS,                             //ִ�н��
	200,                                        //�����Ĵ�����ַ
	off_StatusTotal,                            //�����Ĵ�������
	(uint16_t*)&DC_OutputStatus[off_PowerStatus]     //ִ�е����ݣ���ȡ�ļĴ������ݻ�д����������
};

static RTU_ReqBlock_t RTU_Req_Setting_Voltage = //RTU����д�����-��ѹ����
{
  LIST_HEAD_INIT(RTU_Req_Read_DC_OutputStatus.Entry),
  0,                                          //ִ�д�����0-���޴�
  UART_CHN_AD_SAMPLE,                         //ִ��ͨ��
	SLAVEID_DC_POWER,                           //�ӽڵ�վ��ַ
	FUNC_RD_HOLDREG,                            //������
	EXCUTE_SUCCESS,                             //ִ�н��
	100,                                        //�����Ĵ�����ַ
	off_StatusTotal,                            //�����Ĵ�������
	(uint16_t*)&DC_OutputStatus[off_PowerStatus]     //ִ�е����ݣ���ȡ�ļĴ������ݻ�д����������
};

static RTU_ReqBlock_t RTU_Req_Read_DC_OutputStatus = //RTU���ݶ������-�����������Դ״̬�������ѹ�����������ʲ���ֵ
{
  LIST_HEAD_INIT(RTU_Req_Read_DC_OutputStatus.Entry),
  0,                                          //ִ�д�����0-���޴�
  UART_CHN_AD_SAMPLE,                         //ִ��ͨ��
	SLAVEID_DC_POWER,                           //�ӽڵ�վ��ַ
	FUNC_RD_HOLDREG,                            //������
	EXCUTE_SUCCESS,                             //ִ�н��
	200,                                        //�����Ĵ�����ַ
	off_StatusTotal,                            //�����Ĵ�������
	(uint16_t*)&DC_OutputStatus[off_PowerStatus]     //ִ�е����ݣ���ȡ�ļĴ������ݻ�д����������
};




/********************************************************************************/
/*��������  HF_SampleBoard_Init                                                             */
/*����˵����ģ���ʼ������                                                        */
/*�����������*/
/*�����������                                                                   */
/********************************************************************************/
void DC_POWER_Init(void)
{//ģ���ʼ��
  RTU_AddReqBlock(&rtu_ctx[RTU_Req_Read_DC_OutputStatus.chnindex],&RTU_Req_Read_DC_OutputStatus);
}

/********************************************************************************/
/*��������  Task_MBRTU_Master                                                       */
/*����˵����RTU master��task, ��ʱ���ã�����CPU load                                         */
/*�����������                                                                        */
/*�����������                                                                        */
/*******************************************************************************/
void DC_POWER_MainFunction(void *p_arg)
{
  if(RTU_Req_Read_DC_OutputStatus.Status == EXCUTE_SUCCESS)
  {

  }
}


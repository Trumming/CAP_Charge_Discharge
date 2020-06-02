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
  off_SetVoltage, off_SetCurrent, off_SetOutSts, off_SetRunMode, off_SetPowerReset, off_SetPowerCtrlMode,
  off_SettingTotal
};//��ѹ����/��������/���״̬����/��Դ����ģʽ/��Դ��λ/��ԴԶ�˻򱾵ؿ���
static uint16_t DC_SettingValue[off_SettingTotal];

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
  LIST_HEAD_INIT(RTU_Req_Setting_Voltage.Entry),
  1,                                          //ִ�д�����0-���޴�
  UART_CHN_AD_SAMPLE,                         //ִ��ͨ��
	SLAVEID_DC_POWER,                           //�ӽڵ�վ��ַ
	FUNC_WR_SGREG,                              //������
	EXCUTE_SUCCESS,                             //ִ�н��
	100,                                        //�����Ĵ�����ַ
	1,                                          //�����Ĵ�������
	(uint16_t*)&DC_SettingValue[off_SetVoltage]     //ִ�е����ݣ���ȡ�ļĴ������ݻ�д����������
};

static RTU_ReqBlock_t RTU_Req_Setting_Current = //RTU����д�����-��������
{
  LIST_HEAD_INIT(RTU_Req_Setting_Current.Entry),
  1,                                          //ִ�д�����0-���޴�
  UART_CHN_AD_SAMPLE,                         //ִ��ͨ��
	SLAVEID_DC_POWER,                           //�ӽڵ�վ��ַ
	FUNC_WR_SGREG,                              //������
	EXCUTE_SUCCESS,                             //ִ�н��
	101,                                        //�����Ĵ�����ַ
	1,                                          //�����Ĵ�������
	(uint16_t*)&DC_SettingValue[off_SetCurrent]     //ִ�е����ݣ���ȡ�ļĴ������ݻ�д����������
};

static RTU_ReqBlock_t RTU_Req_Setting_OutStatus = //RTU����д�����-���״̬����
{
  LIST_HEAD_INIT(RTU_Req_Setting_OutStatus.Entry),
  1,                                          //ִ�д�����0-���޴�
  UART_CHN_AD_SAMPLE,                         //ִ��ͨ��
	SLAVEID_DC_POWER,                           //�ӽڵ�վ��ַ
	FUNC_WR_SGREG,                              //������
	EXCUTE_SUCCESS,                             //ִ�н��
	110,                                        //�����Ĵ�����ַ
	1,                                          //�����Ĵ�������
	(uint16_t*)&DC_SettingValue[off_SetOutSts]     //ִ�е����ݣ���ȡ�ļĴ������ݻ�д����������
};

static RTU_ReqBlock_t RTU_Req_Setting_RunMode = //RTU����д�����-��Դ����ģʽ
{
  LIST_HEAD_INIT(RTU_Req_Setting_RunMode.Entry),
  1,                                          //ִ�д�����0-���޴�
  UART_CHN_AD_SAMPLE,                         //ִ��ͨ��
	SLAVEID_DC_POWER,                           //�ӽڵ�վ��ַ
	FUNC_WR_SGREG,                              //������
	EXCUTE_SUCCESS,                             //ִ�н��
	111,                                        //�����Ĵ�����ַ
	1,                                          //�����Ĵ�������
	(uint16_t*)&DC_SettingValue[off_SetRunMode]     //ִ�е����ݣ���ȡ�ļĴ������ݻ�д����������
};

static RTU_ReqBlock_t RTU_Req_Setting_PowerReset = //RTU����д�����-��Դ��λ
{
  LIST_HEAD_INIT(RTU_Req_Setting_PowerReset.Entry),
  1,                                          //ִ�д�����0-���޴�
  UART_CHN_AD_SAMPLE,                         //ִ��ͨ��
	SLAVEID_DC_POWER,                           //�ӽڵ�վ��ַ
	FUNC_WR_SGREG,                              //������
	EXCUTE_SUCCESS,                             //ִ�н��
	112,                                        //�����Ĵ�����ַ
	1,                                          //�����Ĵ�������
	(uint16_t*)&DC_SettingValue[off_SetPowerReset]     //ִ�е����ݣ���ȡ�ļĴ������ݻ�д����������
};

static RTU_ReqBlock_t RTU_Req_Setting_PowerCtrlMode = //RTU����д�����-��ԴԶ�˻򱾵ؿ���
{
  LIST_HEAD_INIT(RTU_Req_Setting_PowerCtrlMode.Entry),
  1,                                          //ִ�д�����0-���޴�
  UART_CHN_AD_SAMPLE,                         //ִ��ͨ��
	SLAVEID_DC_POWER,                           //�ӽڵ�վ��ַ
	FUNC_WR_SGREG,                              //������
	EXCUTE_SUCCESS,                             //ִ�н��
	113,                                        //�����Ĵ�����ַ
	1,                                          //�����Ĵ�������
	(uint16_t*)&DC_SettingValue[off_SetPowerCtrlMode]     //ִ�е����ݣ���ȡ�ļĴ������ݻ�д����������
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

//�����ѹֵ
//����ֵ���洢��ǰ���صĵ�ѹֵ
//����ֵ������͵�ԴͨѶ������ΪTRUE������ΪFALSE
uint8_t Read_DC_Power_Output_Voltage(uint16_t* Voltage)
{
  uint8_t ret=FALSE;
  if(RTU_Req_Read_DC_OutputStatus.Status == EXCUTE_SUCCESS)
  {
    ret = TRUE;
  }
  *Voltage = DC_OutputStatus[off_PowerStatus];
  return ret;
}

/********************************************************************************/
/*��������  Task_MBRTU_Master                                                       */
/*����˵����RTU DC_POWER_MainFunction, ��ʱ���ã�����CPU load                               */
/*�����������                                                                        */
/*�����������                                                                        */
/*******************************************************************************/
void DC_POWER_MainFunction(void *p_arg)
{
  uint8_t ret = FALSE;
  uint16_t read_val=0;
  
  ret = Read_DC_Power_Setting_Voltage(&read_val);
  if(ret == TRUE)
  {
    DC_SettingValue[off_SetVoltage] = read_val;
    RTU_AddReqBlock(&rtu_ctx[RTU_Req_Setting_Voltage.chnindex],&RTU_Req_Setting_Voltage);
  }

  ret = Read_DC_Power_Setting_Current(&read_val);
  if(ret == TRUE)
  {
    DC_SettingValue[off_SetCurrent] = read_val;
    RTU_AddReqBlock(&rtu_ctx[RTU_Req_Setting_Current.chnindex],&RTU_Req_Setting_Current);
  }

  ret = Read_DC_Power_Setting_OutputStatus(&read_val);
  if(ret == TRUE)
  {
    DC_SettingValue[off_SetOutSts] = read_val;
    RTU_AddReqBlock(&rtu_ctx[RTU_Req_Setting_OutStatus.chnindex],&RTU_Req_Setting_OutStatus);
  }

  ret = Read_DC_Power_Setting_RunMode(&read_val);
  if(ret == TRUE)
  {
    DC_SettingValue[off_SetRunMode] = read_val;
    RTU_AddReqBlock(&rtu_ctx[RTU_Req_Setting_RunMode.chnindex],&RTU_Req_Setting_RunMode);
  }

  ret = Read_DC_Power_Setting_PowerReset(&read_val);
  if(ret == TRUE)
  {
    DC_SettingValue[off_SetPowerReset] = read_val;
    RTU_AddReqBlock(&rtu_ctx[RTU_Req_Setting_PowerReset.chnindex],&RTU_Req_Setting_PowerReset);
  }

  ret = Read_DC_Power_Setting_PowerCtrlMode(&read_val);
  if(ret == TRUE)
  {
    DC_SettingValue[off_SetPowerCtrlMode] = read_val;
    RTU_AddReqBlock(&rtu_ctx[RTU_Req_Setting_PowerCtrlMode.chnindex],&RTU_Req_Setting_PowerCtrlMode);
  }
}


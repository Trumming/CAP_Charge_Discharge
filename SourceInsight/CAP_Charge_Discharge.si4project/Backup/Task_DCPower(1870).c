#include "config.h"
#include "cmsis_os.h"
#include "interface.h"
#include "string.h"
#include "Task_DCPower.h"


#if 0
static RTU_ReqBlock_t RTU_Req_ReadWeight_30 = //RTU���ݶ������-ë�� 1
{
  LIST_HEAD_INIT(RTU_Req_ReadWeight_30.Entry),
  0,                                          //ִ�д�����0-���޴�
  UART_CHN_AD_SAMPLE,                     //ִ��ͨ��
	SLAVEID_SAMPLE_BOARD,                             //�ӽڵ�վ��ַ
	FUNC_RD_HOLDREG,                            //������
	EXCUTE_SUCCESS,                             //ִ�н��
	30,                                        //�����Ĵ�����ַ
	0x02,                                       //�����Ĵ�������
	(u16*)&Weight_Sensor_Data[off_Weight_H]               //ִ�е����ݣ���ȡ�ļĴ������ݻ�д����������
};
#endif


/********************************************************************************/
/*��������  HF_SampleBoard_Init                                                             */
/*����˵����ģ���ʼ������                                                        */
/*�����������*/
/*�����������                                                                   */
/********************************************************************************/
void DC_POWER_Init(void)
{//ģ���ʼ��
  //RTU_AddReqBlock(&rtu_ctx[RTU_Req_ReadCurrent_Thres.chnindex],&RTU_Req_ReadCurrent_Thres);
}

/********************************************************************************/
/*��������  Task_MBRTU_Master                                                       */
/*����˵����RTU master��task, ��ʱ���ã�����CPU load                                         */
/*�����������                                                                        */
/*�����������                                                                        */
/*******************************************************************************/
void DC_POWER_MainFunction(void *p_arg)
{

}


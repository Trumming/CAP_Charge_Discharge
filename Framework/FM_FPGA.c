#include "config.h"
#include "cmsis_os.h"
#include "interface.h"
#include "string.h"
#include "FM_FPGA.h"



static uint8_t index;


/********************************************************************************/
/*��������  PC_Comm_Init                                                             */
/*����˵����ģ���ʼ������                                                        */
/*�����������*/
/*�����������                                                                   */
/********************************************************************************/
void FM_FPGA_Init(void)
{//ģ���ʼ��
  //RTU_AddReqBlock(&rtu_ctx[RTU_Req_ReadCurrent_Thres.chnindex],&RTU_Req_ReadCurrent_Thres);
  index=0;
}

/********************************************************************************/
/*��������  PC_Comm_MainFunction                                                       */
/*����˵����RTU master��task, ��ʱ���ã�����CPU load                                         */
/*�����������                                                                        */
/*�����������                                                                        */
/*******************************************************************************/
void FM_FPGA_MainFunction(void *p_arg)
{
  
}


#include "config.h"
#include "cmsis_os.h"
#include "interface.h"
#include "string.h"
#include "Task_APPLogic.h"



/********************************************************************************/
/*��������  APP_Logic_Init                                                             */
/*����˵����ģ���ʼ������                                                        */
/*�����������*/
/*�����������                                                                   */
/********************************************************************************/
void APP_Logic_Init(void)
{//ģ���ʼ��
  //RTU_AddReqBlock(&rtu_ctx[RTU_Req_ReadCurrent_Thres.chnindex],&RTU_Req_ReadCurrent_Thres);
}

/********************************************************************************/
/*��������  Task_APP_Logic                                                       */
/*����˵����RTU master��task, ��ʱ���ã�����CPU load                                         */
/*�����������                                                                        */
/*�����������                                                                        */
/*******************************************************************************/
void APP_Logic_MainFunction(void *p_arg)
{

}


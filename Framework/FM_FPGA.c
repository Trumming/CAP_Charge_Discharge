#include "config.h"
#include "cmsis_os.h"
#include "interface.h"
#include "string.h"
#include "FM_FPGA.h"



static uint8_t index;


/********************************************************************************/
/*函数名：  PC_Comm_Init                                                             */
/*功能说明：模块初始化函数                                                        */
/*输入参数：无*/
/*输出参数：无                                                                   */
/********************************************************************************/
void FM_FPGA_Init(void)
{//模块初始化
  //RTU_AddReqBlock(&rtu_ctx[RTU_Req_ReadCurrent_Thres.chnindex],&RTU_Req_ReadCurrent_Thres);
  index=0;
}

/********************************************************************************/
/*函数名：  PC_Comm_MainFunction                                                       */
/*功能说明：RTU master主task, 分时调用，减少CPU load                                         */
/*输入参数：无                                                                        */
/*输出参数：无                                                                        */
/*******************************************************************************/
void FM_FPGA_MainFunction(void *p_arg)
{
  
}


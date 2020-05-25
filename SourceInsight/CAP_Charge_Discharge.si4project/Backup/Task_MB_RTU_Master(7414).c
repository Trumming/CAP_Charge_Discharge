#include "main.h"
#include "cmsis_os.h"
#include "stm32f2xx.h"                  // Device header
#include "string.h"
#include "Task_MB_RTU_Master.h"


struct Time_Parameter_t
{
    uint16_t interval;
    uint16_t timerout;
};
struct Time_Parameter_t Time_Parameter[NUM_UARTCHANNEL] = TIMER_PARAMETR_LIST;

struct RTU_Ctx rtu_ctx[NUM_UARTCHANNEL];//��������

uint8_t RTU_CHN_ENABLE[NUM_UARTCHANNEL] = RTU_ENABLE_LIST;
uint8_t RTU_Active[NUM_UARTCHANNEL]={OFF,OFF,OFF,OFF};
static uint16_t CommErrCnt[NUM_UARTCHANNEL]; //ͨѶ���������

static volatile Tdef_Prot    	        	_RTUSystemStatus[NUM_UARTCHANNEL];
#define SystemStatus(n)                 _RTUSystemStatus[n].Byte
#define Manual_Req(n)                   _RTUSystemStatus[n].Bits.bit0

void UART_RTU_Recv(uint8_t channel, uint8_t l_u8ReceData);


/********************************************************************************/
/*��������  Record_ErrCnt                                               */
/*����˵�����������                                                */
/*�����������                                         */
/*�����������                                                                   */
/********************************************************************************/
void Record_ErrCnt(uint8_t chn)
{
    if(CommErrCnt[chn] < 0xFFFE)
    {
        CommErrCnt[chn]++;
    }
}

/********************************************************************************/
/*��������  RTU_AddReqBlock_Front                                               */
/*����˵������������ӵ����е�ͷ��                                                */
/*���������_rtuctx-Ŀ����У�_req-������                                         */
/*�����������                                                                   */
/********************************************************************************/
void RTU_AddReqBlock_Front(struct RTU_Ctx* _rtuctx, struct RTU_ReqBlock* _req)
{//����ǰ����ŵ���Ϣ���е���λ
    struct list_head* p;
    p = &_rtuctx->head;
    do
    {
        if(p == _req->Entry.next)
        {
            return;
        }
        p = p->next;
    }
    while(p != &_rtuctx->head);
	__disable_irq();
    list_add(&_req->Entry, &_rtuctx->head);
	__enable_irq();
	//_rtuctx->event=EV_REQ ;
}

/********************************************************************************/
/*��������  RTU_AddReqBlock                                                      */
/*����˵������������ӵ����е�β��                                                */
/*���������_rtuctx-Ŀ����У�_req-������                                         */
/*�����������                                                                   */
/********************************************************************************/
void RTU_AddReqBlock(struct RTU_Ctx* _rtuctx, struct RTU_ReqBlock* _req)
{//����ǰ������뵽����
    struct list_head* p;
    p = &_rtuctx->head;
    do
    {
        if(p == _req->Entry.next)
        {
            return;
        }
        p = p->next;
    }
    while(p != &_rtuctx->head);
		OS_ENTER_CRITICAL();
    _req->Status = EXCUTE_IDLE;
		list_add_tail(&_req->Entry, &_rtuctx->head);
		OS_EXIT_CRITICAL();
    //_rtuctx->event=EV_REQ ;
}

/********************************************************************************/
/*��������  RTU_DelReqBlock                                                      */
/*����˵����ɾ�����еĵ�һ��Ԫ��                                                  */
/*���������_rtuctx-Ŀ�����                                                     */
/*���������ɾ����һ����Ա�����ǰ��һ����Ա��ַ                                   */
/********************************************************************************/
static struct RTU_ReqBlock* RTU_DelReqBlock(struct RTU_Ctx* _rtu_ctx)
{//ɾ����Ϣ���е��׸�����
    struct RTU_ReqBlock* req = 0;
    OS_ENTER_CRITICAL();
    if (!list_empty(&_rtu_ctx->head))
    {
        req = (struct RTU_ReqBlock*)_rtu_ctx->head.next;
        if (req)
        {
            list_del(_rtu_ctx->head.next);
        }
    }
    OS_EXIT_CRITICAL();
    return req;
}

/********************************************************************************/
/*��������  BSP_RTU_StartSend                                                   */
/*����˵��������BSP��������                                                      */
/*���������_rtuctx-Ŀ�����                                                     */
/*�����������                                                                   */
/********************************************************************************/
static void BSP_RTU_StartSend(struct RTU_Ctx* _rturtx)
{//�������ڷ���
	UartOpFunc[_rturtx->curr->chnindex]._send(_rturtx->txbuff,_rturtx->txindex);
	_rturtx->txindex=0;
	_rturtx->TOtimer = _rturtx->guard_time;
	_rturtx->rxindex = 0;
}
	
/********************************************************************************/
/*��������  RTU_Init                                                             */
/*����˵����ģ���ʼ������                                                        */
/*���������chn-��ʼ��ͨ����*/
/*�����������                                                                   */
/********************************************************************************/
void RTU_Init(uint8_t chn)
{//ģ���ʼ��
	uint8_t i;
	//memset(&rtu_ctx, 0, sizeof(rtu_ctx));
	rtu_ctx[chn].fsm_state = RTU_REQ;//��ʼ��������ģʽ
	rtu_ctx[chn].guard_time = Time_Parameter[chn].timerout;//��������������Ӧʱ�䣬����Ϊ��ʱ
	rtu_ctx[chn].poll_interval=Time_Parameter[chn].interval;//��������������ʱ��
	INIT_LIST_HEAD(&rtu_ctx[chn].head);
	RTU_Active[chn] = ON;
	rtu_ctx[chn].TOtimer = rtu_ctx[chn].poll_interval;
	rtu_ctx[chn].event = EV_TO;
	rtu_ctx[chn].Pollevent = EV_NONE;
	UartOpFunc[chn]._recv=UART_RTU_Recv;
	memset(CommErrCnt,0,NUM_UARTCHANNEL);
	for(i=0;i<NUM_UARTCHANNEL;i++)
	{
			if(RTU_CHN_ENABLE[i] == TRUE)
			{
					RTU_Init(i);//��һ��������ʾ���ͼ��ʱ�䣬�ڶ���������ʾ��ʱʱ��
			}
	}
}

/********************************************************************************/
/*��������  RTU_HandleReply                                                     */
/*����˵�����������ݽ���                                                         */
/*���������_rtuctx-Ŀ�����                                                     */
/*�����������                                                                   */
/********************************************************************************/
void RTU_HandleReply(struct RTU_Ctx* _rtuctx)
{
	uint8_t i,j;
	_rtuctx->TOtimer=0;
	if((_rtuctx->rxbuff[1]&MB_RESP_NEG)!=MB_RESP_NEG)
	{
		_rtuctx->curr->Status = EXCUTE_SUCCESS;
	}
	else
	{
		_rtuctx->curr->Status = EXCUTE_FAIL;
		Record_ErrCnt(_rtuctx->curr->chnindex);//��¼һ�δ���
		//Error_Indicator(80);  //LED��80ms����
	}
	if(_rtuctx->OP_Mode==READ)
	{
		OS_ENTER_CRITICAL();
		if((_rtuctx->curr->FuncCode == FUNC_RD_COILSTATUS)||(_rtuctx->curr->FuncCode == FUNC_RD_INPUTSTATUS))
		{
			for(i=0;i<_rtuctx->rxbuff[2];i++)
			{
				for(j=0;j<8;j++)
				{
					_rtuctx->curr->mappedBuff[(8*2*i)+(2*j)]=0x00 + (_rtuctx->rxbuff[3+i]>>j)&0x01;
				}
			}
		}
		else
		{
			for(j=0;j<_rtuctx->rxbuff[2];j=j+2)
			{
				_rtuctx->curr->mappedBuff[j/2] = (_rtuctx->rxbuff[3+j]<<8) + _rtuctx->rxbuff[3+j+1];
			}
		}
		OS_EXIT_CRITICAL();
	}
	memset(_rtuctx->rxbuff,0,_rtuctx->rxindex+1);
	_rtuctx->rxindex=0;
}

/********************************************************************************/
/*��������  RTU_Timer1ms_Handler                                                 */
/*����˵������ʱ״̬����                                                          */
/*�����������                                                                   */
/*�����������                                                                   */
/********************************************************************************/
void RTU_Timer1ms_Handler(void)
{
    uint8_t i;
    for(i=0;i<NUM_UARTCHANNEL;i++)
    {
        if(RTU_CHN_ENABLE[i] == TRUE)
        {
            if(RTU_Active[i] == ON)
            {
        		if((rtu_ctx[i].TOtimer>0)&&(!--rtu_ctx[i].TOtimer))
        		{
        			rtu_ctx[i].event = EV_TO;
        		}
        		
        		if(rtu_ctx[i].fsm_state == FSM_REQ)
        		{
        			if((rtu_ctx[i].Polltimer>0)&&(!--rtu_ctx[i].Polltimer))
        			{
        				rtu_ctx[i].Pollevent = EV_TO;
        			}
        		}
        		else
        		{
        			//rtu_ctx.Polltimer=0;
        		}
            }
        }
    }
}

/********************************************************************************/
/*��������  UART_RTU_Recv                                                        */
/*����˵�������յ������ݽ������ж�ÿ���ֽ��Ƿ���Ч������Ч��������֡����             */
/*���������l_u8ReceData����ǰ���յ�����                                          */
/*�����������                                                                   */
/********************************************************************************/
void UART_RTU_Recv(uint8_t chn, uint8_t l_u8ReceData)
{
	uint16_t CrcCheck;
	
	//����
	if((rtu_ctx[chn].framestart==OFF)&&(l_u8ReceData==rtu_ctx[chn].curr->sta_addr))
	{
		rtu_ctx[chn].framestart=ON;
		rtu_ctx[chn].rxindex=0;
		rtu_ctx[chn].rxbuff[rtu_ctx[chn].rxindex]=l_u8ReceData;
	}
	
	if(rtu_ctx[chn].framestart==ON)
	{
		rtu_ctx[chn].rxbuff[rtu_ctx[chn].rxindex]=l_u8ReceData;
	}
	
	if(((rtu_ctx[chn].rxbuff[2]+5)==(rtu_ctx[chn].rxindex+1))&&(rtu_ctx[chn].OP_Mode==READ))
	{
		CrcCheck=Get_rtuCrc16(rtu_ctx[chn].rxbuff,rtu_ctx[chn].rxbuff[2]+3);
		if(((CrcCheck>>8) == rtu_ctx[chn].rxbuff[rtu_ctx[chn].rxindex-1]) && ((CrcCheck%256) == rtu_ctx[chn].rxbuff[rtu_ctx[chn].rxindex]))
		{
			rtu_ctx[chn].framestart=OFF;
			rtu_ctx[chn].event = EV_RX_OK;
		}
		else
		{
			rtu_ctx[chn].event = EV_RX_CRC_ERR;
		}
	}
	else if((rtu_ctx[chn].rxindex==7)&&(rtu_ctx[chn].OP_Mode==WRITE))
	{
		rtu_ctx[chn].framestart=OFF;
		rtu_ctx[chn].event = EV_RX_OK;
	}
	else
	{
		
	}
	rtu_ctx[chn].rxindex++;
}

/********************************************************************************/
/*��������  RTU_Read                                                             */
/*����˵�������������ݴ��                                                        */
/*���������_rtuctx����ǰ����������Ϣ                                             */
/*�����������                                                                   */
/********************************************************************************/
void RTU_Read(struct RTU_Ctx* _rtuctx)
{
    uint16_t CrcCheck;
    _rtuctx->OP_Mode=READ;
    _rtuctx->curr->FuncCode =(_rtuctx->curr->FuncCode==(MB_FUNC_TYPE_t)0)? (MB_FUNC_TYPE_t)0x03 : _rtuctx->curr->FuncCode ;
    _rtuctx->txbuff[_rtuctx->txindex++] = _rtuctx->curr->sta_addr;
    _rtuctx->txbuff[_rtuctx->txindex++] = _rtuctx->curr->FuncCode;
    _rtuctx->txbuff[_rtuctx->txindex++] = _rtuctx->curr->RegAddr/256;
    _rtuctx->txbuff[_rtuctx->txindex++] = _rtuctx->curr->RegAddr%256;
    _rtuctx->txbuff[_rtuctx->txindex++] = _rtuctx->curr->RegNum/256;
    _rtuctx->txbuff[_rtuctx->txindex++] = _rtuctx->curr->RegNum%256;
    CrcCheck = Get_rtuCrc16(_rtuctx->txbuff,_rtuctx->txindex);
    _rtuctx->txbuff[_rtuctx->txindex++] =  CrcCheck>>8;
    _rtuctx->txbuff[_rtuctx->txindex++] =  CrcCheck;
    BSP_RTU_StartSend(_rtuctx);
}

/********************************************************************************/
/*��������  RTU_Write                                                            */
/*����˵����д�������ݴ��                                                        */
/*���������_rtuctx����ǰ����������Ϣ                                             */
/*�����������                                                                   */
/********************************************************************************/
void RTU_Write(struct RTU_Ctx* _rtuctx)
{
    uint16_t CrcCheck;
    uint8_t temp,i;
    _rtuctx->OP_Mode=WRITE;
    _rtuctx->curr->FuncCode =(_rtuctx->curr->FuncCode==0u)? (MB_FUNC_TYPE_t)0x10 : _rtuctx->curr->FuncCode ;
    _rtuctx->txbuff[_rtuctx->txindex++] = _rtuctx->curr->sta_addr;
    _rtuctx->txbuff[_rtuctx->txindex++] = _rtuctx->curr->FuncCode;
    _rtuctx->txbuff[_rtuctx->txindex++] = _rtuctx->curr->RegAddr/256;
    _rtuctx->txbuff[_rtuctx->txindex++] = _rtuctx->curr->RegAddr%256;
    if(_rtuctx->curr->FuncCode == FUNC_WR_SGCOIL)
    {
        temp=2;
        _rtuctx->curr->mappedBuff[0] = (_rtuctx->curr->mappedBuff[0]==0x01)?0xff00:0x0000;
    }
    else if(_rtuctx->curr->FuncCode == FUNC_WR_MULCOIL)
    {
        temp = (_rtuctx->curr->RegNum/8)+((_rtuctx->curr->RegNum%8)==0?0:1);
    }
    else if(_rtuctx->curr->FuncCode == FUNC_WR_MULREG)
    {
        _rtuctx->txbuff[_rtuctx->txindex++] = _rtuctx->curr->RegNum/256;
        _rtuctx->txbuff[_rtuctx->txindex++] = _rtuctx->curr->RegNum%256;
        temp = _rtuctx->curr->RegNum * 2;
        _rtuctx->txbuff[_rtuctx->txindex++] = temp;
    }
    else
    {
        temp = _rtuctx->curr->RegNum * 2;
    }
    for(i=0;i<temp;i++)
    {
        if(i%2 == 0)
        {
            _rtuctx->txbuff[_rtuctx->txindex++]=_rtuctx->curr->mappedBuff[i/2]>>8;
        }
        else
        {
            _rtuctx->txbuff[_rtuctx->txindex++]=_rtuctx->curr->mappedBuff[i/2]&0xff;
        }
    }
    CrcCheck = Get_rtuCrc16(_rtuctx->txbuff,_rtuctx->txindex);
    _rtuctx->txbuff[_rtuctx->txindex++] =  CrcCheck>>8;
    _rtuctx->txbuff[_rtuctx->txindex++] =  CrcCheck;
    BSP_RTU_StartSend(_rtuctx);
}

/********************************************************************************/
/*��������  RTU_CyclicTask                                                      */
/*����˵����RTU״̬������                                                        */
/*�����������                                                                  */
/*�����������                                                                  */
/*******************************************************************************/
void RTU_CyclicTask(uint8_t chn)
{
    if (rtu_ctx[chn].event == EV_NONE)
    {//����״̬
        return;
    }
	
		switch (rtu_ctx[chn].fsm_state)//�г�ʱ�¼���������block����
    { 
        case RTU_REQ://������״̬
            rtu_ctx[chn].curr = RTU_DelReqBlock(&rtu_ctx[chn]);
            if (rtu_ctx[chn].curr == NULL)
            {
                return;
            }
            rtu_ctx[chn].curr->Status=EXCUTE_START; //���ڴ�����
            if ((rtu_ctx[chn].curr->FuncCode == FUNC_RD_COILSTATUS)||(rtu_ctx[chn].curr->FuncCode == FUNC_RD_INPUTSTATUS)||
                (rtu_ctx[chn].curr->FuncCode == FUNC_RD_HOLDREG)||(rtu_ctx[chn].curr->FuncCode == FUNC_RD_INREG))
            {//���Ĵ���

                RTU_Read(&rtu_ctx[chn]);
            }
            else if((rtu_ctx[chn].curr->FuncCode == FUNC_WR_SGCOIL)||(rtu_ctx[chn].curr->FuncCode == FUNC_WR_SGREG)||(rtu_ctx[chn].curr->FuncCode == FUNC_WR_SGREG_FREQ)||
                (rtu_ctx[chn].curr->FuncCode == FUNC_WR_MULCOIL)||(rtu_ctx[chn].curr->FuncCode == FUNC_WR_MULREG))
            {//д�Ĵ���
                RTU_Write(&rtu_ctx[chn]);
            }
            else
            {

            }
            rtu_ctx[chn].TOtimer = rtu_ctx[chn].guard_time;//ÿ�η�������ʱ���ó�ʱʱ��
            rtu_ctx[chn].fsm_state = RTU_WAITRESP;
            break;
    case RTU_WAITRESP:
        if(rtu_ctx[chn].event == EV_TO)
        {//���͵�����û���յ���Ӧ
            rtu_ctx[chn].fsm_state = RTU_REQ;
            rtu_ctx[chn].curr->Status=EXCUTE_FAIL;
            rtu_ctx[chn].TOtimer = rtu_ctx[chn].poll_interval;
            if (rtu_ctx[chn].curr->Excute_Num > 1u)
            {//�ж��Ƿ����ط������ã�0��ʾ��Ҫ���ڷ��͵����󣬷�0��ʾ��Ҫ���͵Ĵ���
                rtu_ctx[chn].curr->Excute_Num--;
                RTU_AddReqBlock(&rtu_ctx[chn],rtu_ctx[chn].curr);
            }
            else if(rtu_ctx[chn].curr->Excute_Num == 0u)
            {
                RTU_AddReqBlock(&rtu_ctx[chn],rtu_ctx[chn].curr);
            }
            else
            {

            }
            Record_ErrCnt(rtu_ctx[chn].curr->chnindex);//��¼һ�δ���
            //Error_Indicator(80);  //LED��80ms����
        }
        else if(rtu_ctx[chn].event == EV_RX_OK)
        {//�����յ��ӽڵ����Ӧ����
            RTU_HandleReply(&rtu_ctx[chn]);
            rtu_ctx[chn].fsm_state = RTU_REQ;
            rtu_ctx[chn].TOtimer = rtu_ctx[chn].poll_interval;
            if (rtu_ctx[chn].curr->Excute_Num > 1u)
            {//�ж��Ƿ����ط������ã�0��ʾ��Ҫ���ڷ��͵����󣬷�0��ʾ��Ҫ���͵Ĵ���
                rtu_ctx[chn].curr->Excute_Num--;
                RTU_AddReqBlock(&rtu_ctx[chn],rtu_ctx[chn].curr);
            }
            else if(rtu_ctx[chn].curr->Excute_Num == 0u)
            {
                RTU_AddReqBlock(&rtu_ctx[chn],rtu_ctx[chn].curr);
            }
            else
            {

            }
        }
        else
        {

        }
        break;
        default:break;
    }
    rtu_ctx[chn].event = EV_NONE;
}

/********************************************************************************/
/*��������  Task_MBRTU_Master                                                   */
/*����˵����RTU master��task                                                    */
/*�����������                                                                  */
/*�����������                                                                  */
/*******************************************************************************/
void MBRTU_Master_MainFunction(void *p_arg)
{
    uint8_t i;
   	
    for(i=0;i<NUM_UARTCHANNEL;i++)
    {
        if(RTU_CHN_ENABLE[i] == TRUE)
        {
            RTU_CyclicTask(i);
        }
    }
}


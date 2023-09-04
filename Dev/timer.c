#include "config.h"
#include "timer.h"

int timeSyncbit=0;
int ID=0;
int IDBACK=0;
int timer4_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);

	TIM_DeInit(TIM4);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=71;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=9999;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter = 0;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	
	TIM_ICInit(TIM4,&TIM_ICInitStruct);
	
	TIM_ClearITPendingBit(TIM4,TIM_IT_CC2|TIM_IT_Update);
	TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_Update,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM4,ENABLE);
  return 0;
}
INIT_APP_EXPORT(timer4_init);
InputCapture icCapture = {RESET,RESET,0,0,0};
int i=500,j=1500;
void TIM4_IRQHandler()				//��ʱ��4�жϺ���
{
	if(icCapture.icFinishFlag == 0)				//�Ƿ���ɲ���
	{
		if(TIM_GetITStatus(TIM4,TIM_IT_Update) == SET)						//��ȡ�����жϱ�־λ
		{
			if(icCapture.RisFLAG == SET)			//���ز���	
			{
				icCapture.icUpdateCnt++;		//�������+1
				//rt_kprintf("��� %d ��\r\n",icCapture.icUpdateCnt);			//��ӡ�������
			}
			TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update);							//��������жϱ�־λ
		}
		if(TIM_GetITStatus(TIM4,TIM_IT_CC2) == SET)						//��ȡ�����жϱ�־λ
		{
			if(icCapture.RisFLAG == RESET)		//ԭ��û�в���	
			{
				//����
				TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_Update,DISABLE);
				icCapture.RisFLAG = SET;														//���ز���
				//rt_kprintf("The Edge is set\r\n");			//��ӡ������
				TIM_SetCounter(TIM4,0);													//����ֵ��0
				TIM_OC2PolarityConfig(TIM4,TIM_OCPolarity_Low);	//���Ը�Ϊ�½���
				if(timeSyncbit==3)
				{
					timeSyncbit=4;
				}
				rt_hw_us_delay(20);
				TIM_ClearITPendingBit(TIM4,TIM_IT_CC2|TIM_IT_Update);
				TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_Update,ENABLE);
			}
			else													//����
			{
				//����
				TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_Update,DISABLE);
				icCapture.icFinishFlag = 1;
				icCapture.icCaptureVal = TIM_GetCapture2(TIM4);		//������ǰ����ֵ
				/*������ = �������*(ARR+1)+��ǰ����ֵ*/
				icCapture.icTimeLen	= icCapture.icUpdateCnt*9999+icCapture.icCaptureVal;	//����������
//				rt_kprintf("The Time is: %d us\r\n",icCapture.icTimeLen);			//��ӡ������
				if(timeSyncbit==2)
				{
					IDBACK=icCapture.icTimeLen; //��¼ID��λ		
					timeSyncbit=3;
				}
				if(timeSyncbit==1)
				{
					ID=icCapture.icTimeLen; //��¼ID
					timeSyncbit=2;
				}
				if(timeSyncbit==0&&icCapture.icTimeLen>(i/2)&&icCapture.icTimeLen<(j/2)) //��ʼͬ��
				{
					timeSyncbit=1;
				}
				icCapture.icCaptureVal = 0;  //����ֵ��0
				icCapture.icUpdateCnt = 0; 	 //���������0
				icCapture.RisFLAG = RESET;		//���ز���ָ�ΪRESET
				TIM_OC2PolarityConfig(TIM4,TIM_OCPolarity_High);	//���Իָ�Ϊ������
				icCapture.icFinishFlag = 0;		//��־λ��0
				rt_hw_us_delay(20);
				TIM_ClearITPendingBit(TIM4,TIM_IT_Update|TIM_IT_CC2);							//����жϱ�־λ
				TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_Update,ENABLE);
			}
			TIM_ClearITPendingBit(TIM4,TIM_IT_CC2);							//��������жϱ�־λ
		}
	}
	else
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update|TIM_IT_CC2);							//����жϱ�־λ
}

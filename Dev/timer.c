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
void TIM4_IRQHandler()				//定时器4中断函数
{
	if(icCapture.icFinishFlag == 0)				//是否完成捕获
	{
		if(TIM_GetITStatus(TIM4,TIM_IT_Update) == SET)						//获取更新中断标志位
		{
			if(icCapture.RisFLAG == SET)			//边沿捕获到	
			{
				icCapture.icUpdateCnt++;		//溢出置数+1
				//rt_kprintf("溢出 %d 次\r\n",icCapture.icUpdateCnt);			//打印溢出次数
			}
			TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update);							//清除更新中断标志位
		}
		if(TIM_GetITStatus(TIM4,TIM_IT_CC2) == SET)						//获取捕获中断标志位
		{
			if(icCapture.RisFLAG == RESET)		//原来没有捕获到	
			{
				//消抖
				TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_Update,DISABLE);
				icCapture.RisFLAG = SET;														//边沿捕获到
				//rt_kprintf("The Edge is set\r\n");			//打印上升沿
				TIM_SetCounter(TIM4,0);													//计数值清0
				TIM_OC2PolarityConfig(TIM4,TIM_OCPolarity_Low);	//极性改为下降沿
				if(timeSyncbit==3)
				{
					timeSyncbit=4;
				}
				rt_hw_us_delay(20);
				TIM_ClearITPendingBit(TIM4,TIM_IT_CC2|TIM_IT_Update);
				TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_Update,ENABLE);
			}
			else													//捕获到
			{
				//消抖
				TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_Update,DISABLE);
				icCapture.icFinishFlag = 1;
				icCapture.icCaptureVal = TIM_GetCapture2(TIM4);		//读出当前计数值
				/*脉冲宽度 = 溢出次数*(ARR+1)+当前计数值*/
				icCapture.icTimeLen	= icCapture.icUpdateCnt*9999+icCapture.icCaptureVal;	//计算脉冲宽度
//				rt_kprintf("The Time is: %d us\r\n",icCapture.icTimeLen);			//打印脉宽长度
				if(timeSyncbit==2)
				{
					IDBACK=icCapture.icTimeLen; //记录ID反位		
					timeSyncbit=3;
				}
				if(timeSyncbit==1)
				{
					ID=icCapture.icTimeLen; //记录ID
					timeSyncbit=2;
				}
				if(timeSyncbit==0&&icCapture.icTimeLen>(i/2)&&icCapture.icTimeLen<(j/2)) //开始同步
				{
					timeSyncbit=1;
				}
				icCapture.icCaptureVal = 0;  //计数值清0
				icCapture.icUpdateCnt = 0; 	 //溢出次数清0
				icCapture.RisFLAG = RESET;		//边沿捕获恢复为RESET
				TIM_OC2PolarityConfig(TIM4,TIM_OCPolarity_High);	//极性恢复为上升沿
				icCapture.icFinishFlag = 0;		//标志位清0
				rt_hw_us_delay(20);
				TIM_ClearITPendingBit(TIM4,TIM_IT_Update|TIM_IT_CC2);							//清除中断标志位
				TIM_ITConfig(TIM4,TIM_IT_CC2|TIM_IT_Update,ENABLE);
			}
			TIM_ClearITPendingBit(TIM4,TIM_IT_CC2);							//清除捕获中断标志位
		}
	}
	else
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update|TIM_IT_CC2);							//清除中断标志位
}

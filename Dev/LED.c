#include "config.h"
#include "LED.h"

void LedGpioInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_5 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void LedControl(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	//SysTickDelayMs(1000);
	rt_thread_mdelay(1000);
  GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	//SysTickDelayMs(1000);
	rt_thread_mdelay(1000);
	
}


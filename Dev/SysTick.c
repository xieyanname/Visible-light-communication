#include "config.h"
#include "SysTick.h"


void SysTickInit(void)
{
	
	SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);//ÿ��1ms��һ��ϵͳ�δ��ж���Ӧ��������Ƶ72M
	
	
}


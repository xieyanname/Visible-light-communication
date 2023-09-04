#include "config.h"
#include "SysTick.h"


void SysTickInit(void)
{
	
	SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);//每隔1ms进一次系统滴答中断响应函数，主频72M
	
	
}


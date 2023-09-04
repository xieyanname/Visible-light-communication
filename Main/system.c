#include "config.h"
#include "system.h"


void SysInit(void)
{

	//外设驱动初始化
	SysTickInit();//系统滴答定时器初始化
//	LedGpioInit();//LED初始化
	UsartInit();//串口初始化
	
}


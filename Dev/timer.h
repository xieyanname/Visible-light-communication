#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f10x.h"

typedef struct				
{
	FlagStatus RisFLAG;			//边沿是否捕获到，是为set，否为reset
	uint16 icUpdateCnt;			//溢出次数
	uint16	icCaptureVal;			//当前计数值
	uint8 icFinishFlag;			//是否完成捕获
	uint32 icTimeLen;				//捕获时间长度
	
	
}InputCapture;

extern int timeSyncbit;
extern int ID;
extern int IDBACK;
int timer4_init(void);

#endif


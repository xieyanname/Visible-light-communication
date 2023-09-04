#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f10x.h"

typedef struct				
{
	FlagStatus RisFLAG;			//�����Ƿ񲶻񵽣���Ϊset����Ϊreset
	uint16 icUpdateCnt;			//�������
	uint16	icCaptureVal;			//��ǰ����ֵ
	uint8 icFinishFlag;			//�Ƿ���ɲ���
	uint32 icTimeLen;				//����ʱ�䳤��
	
	
}InputCapture;

extern int timeSyncbit;
extern int ID;
extern int IDBACK;
int timer4_init(void);

#endif


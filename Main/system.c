#include "config.h"
#include "system.h"


void SysInit(void)
{

	//����������ʼ��
	SysTickInit();//ϵͳ�δ�ʱ����ʼ��
//	LedGpioInit();//LED��ʼ��
	UsartInit();//���ڳ�ʼ��
	
}


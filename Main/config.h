#ifndef  __CONFIG_H__
#define  __CONFIG_H__

//�޷������͵Ķ���
#define uchar unsigned char
#define uint unsigned int 
	
#define uint8 unsigned char
#define uint16 unsigned short int
#define uint32 unsigned int
	
//----------------------------------------


//ȫ�ֺ궨��
#define CPU_INT_DISABLE()  {__set_PRIMASK(1);} //�ر��ж�
#define CPU_INT_ENABLE()   {__set_PRIMASK(0);}  //���ж�

//ȫ�����Ͷ���
typedef enum{FALSE = 0, TRUE = !FALSE}BOOL;


	
//����ͷ�ļ�����
#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"

//RT-Thread���ͷ�ļ�
#include <rthw.h>
#include <rtthread.h>
	
//-------------------------------------
	
//��������ͷ�ļ�����
#include "system.h"
#include "SysTick.h"
#include "LED.h"
#include "USart.h"
#include "task.h"
#include "timer.h"
#include "ADC.h"
#include "math.h"

#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/

#ifndef  __CONFIG_H__
#define  __CONFIG_H__

//无符号类型的定义
#define uchar unsigned char
#define uint unsigned int 
	
#define uint8 unsigned char
#define uint16 unsigned short int
#define uint32 unsigned int
	
//----------------------------------------


//全局宏定义
#define CPU_INT_DISABLE()  {__set_PRIMASK(1);} //关闭中断
#define CPU_INT_ENABLE()   {__set_PRIMASK(0);}  //打开中断

//全局类型定义
typedef enum{FALSE = 0, TRUE = !FALSE}BOOL;


	
//常用头文件包含
#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"

//RT-Thread相关头文件
#include <rthw.h>
#include <rtthread.h>
	
//-------------------------------------
	
//外设驱动头文件包含
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

#include "config.h"
#include "task.h"
#include <stdlib.h>
ALIGN(RT_ALIGN_SIZE)

/*************************************************************************
*                            变量定义
*************************************************************************
*/

static rt_thread_t dynamic_thread = RT_NULL;//动态线程控制块指针

/*************************************************************************
*                             线程入口函数声明
*************************************************************************
*/
void data_update_task(void *parameter);
	
/*************************************************************************
*                             线程结构体数组(适合线程动态创建)
*************************************************************************
*/
TaskStruct TaskThreads[] = {
			{"data_update_task",data_update_task,RT_NULL,1024,24,10},
			
			/*********************************************************/
			//用户添加线程参数
			//例如：{线程名字,线程入口函数,线程入口函数参数,线程栈大小,线程的优先级,线程时间片},
			{"",RT_NULL, RT_NULL,RT_NULL,RT_NULL,RT_NULL}	
};
int Task_Init()
{
	uint8_t TaskThreadIndex = 0;
	while(1)
 {
	 if(strcmp(TaskThreads[TaskThreadIndex].name,"") != 0)
	 {
			dynamic_thread = rt_thread_create(TaskThreads[TaskThreadIndex].name,       // 线程名字 
															TaskThreads[TaskThreadIndex].entry,  // 线程入口函数 
															TaskThreads[TaskThreadIndex].parameter,           // 线程入口函数参数
															TaskThreads[TaskThreadIndex].stack_size,               // 线程栈大小 
															TaskThreads[TaskThreadIndex].priority,                 // 线程的优先级 
															TaskThreads[TaskThreadIndex].tick                 // 线程时间片
															);
			if(dynamic_thread != RT_NULL)
			{
				rt_thread_startup(dynamic_thread);
			}
			TaskThreadIndex ++;
	 }
	 else
		 break;
	}
	return 0;
}
INIT_APP_EXPORT(Task_Init);

void data_update_task(void *parameter)
{
	int adc=0;
	int ad_data[4][10];
	int adc_avg=0;
	int va=0,vb=0,vc=0,vd=0;

	while(1)
	{
		rt_hw_us_delay(10);
		if(timeSyncbit==4)
		{
			rt_hw_us_delay(100);
			for(int i=0;i<10;i++)
			{	
				adc+=ADC_Get();
				ADC_ClearITPendingBit(ADC1,ADC_FLAG_EOC);
				rt_hw_us_delay(30);
			}
			adc=adc/10;
			if(ID<500&&IDBACK<500) 
			{
				adc_avg=0;
				for(int i=0;i<9;i++)
				{
					ad_data[0][i]=ad_data[0][i+1];
					adc_avg+=ad_data[0][i];
				}
				ad_data[0][9]=adc;
				adc_avg+=adc;
				va=adc_avg/10;
			}
			if(ID<500&&IDBACK>500)
			{
				adc_avg=0;
				for(int i=0;i<9;i++)
				{
					ad_data[1][i]=ad_data[1][i+1];
					adc_avg+=ad_data[1][i];
				}
				ad_data[1][9]=adc;
				adc_avg+=adc;
				vb=adc_avg/10;
			}
			if(ID>500&&IDBACK<500) 
			{
				adc_avg=0;
				for(int i=0;i<9;i++)
				{
					ad_data[2][i]=ad_data[2][i+1];
					adc_avg+=ad_data[2][i];
				}
				ad_data[2][9]=adc;
				adc_avg+=adc;
				vc=adc_avg/10;
			}
			if(ID>500&&IDBACK>500) 			
			{
				adc_avg=0;
				for(int i=0;i<9;i++)
				{
					ad_data[3][i]=ad_data[3][i+1];
					adc_avg+=ad_data[3][i];
				}
				ad_data[3][9]=adc;
				adc_avg+=adc;
				vd=adc_avg/10;
			}
			timeSyncbit=0;
//			rt_kprintf("%d,%d\r\n",ID,IDBACK);
			rt_kprintf("%d,%d,%d,%d\n",va,vb,vc,vd);
		}
	}
}

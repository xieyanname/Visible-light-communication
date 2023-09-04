![image](https://github.com/xieyanname/-/assets/103435971/32c1bd94-2c63-46fa-9e85-9269cf820ba6)# -毕业设计
一个小小的学术垃圾
仅接收部分
发射端在环境环境中发射了原始信号后由接收板进行接收，接收板进行二级放大之后接入ADC采集引脚，再通过比较电路比较出模拟信号后接入定时器捕获引脚。
![image](https://github.com/xieyanname/-/assets/103435971/1990aa8a-b616-4d88-8ef9-171088f6af5a)
#实现流程
初始化了TIM4定时器中断捕获、ADC采集和RT系统线程
TIM4定时器对进行捕获高低电平，
#Dev

#Main
注意config.h里的头文件添加
#RT-Thread
RT系统的配置文件

 # -毕业设计
一个小小的学术垃圾
仅接收部分
发射端在环境环境中发射了原始信号后由接收板进行接收，接收板进行二级放大之后接入ADC采集引脚，再通过比较电路比较出模拟信号后接入定时器捕获引脚。

![image](https://github.com/xieyanname/-/assets/103435971/1990aa8a-b616-4d88-8ef9-171088f6af5a)
## 实现流程
初始化了TIM4定时器中断捕获、ADC采集和RT系统线程。
### TIM定时器捕获
TIM4定时器是否捕获到上升沿，捕获到上升沿后改为下降沿，记录脉宽，在不同状态下将脉宽与信号数据位进行匹配。
![image](https://github.com/xieyanname/-/assets/103435971/c7483d8a-227e-40e2-ac95-5f7c4f0bc208)
### RT系统线程4
在状态位达到4时进入判断，获取ADC采集电压值并且记录，对采集到的电压数据进行平均值滤波处理然后匹配。
![image](https://github.com/xieyanname/-/assets/103435971/61d4e92d-7891-44bf-a96f-1957b547bf72)

## Dev

## Main
注意config.h里的头文件添加
## RT-Thread
RT系统的配置文件
## 接收硬件电路
![image](https://github.com/xieyanname/-/assets/103435971/51df8976-93a4-4a91-bae5-9e15e889e989)

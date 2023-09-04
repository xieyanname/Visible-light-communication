 # -毕业设计
一个小小的学术垃圾
仅接收部分
发射端在环境环境中发射了原始信号后由接收板进行接收，接收板进行二级放大之后接入ADC采集引脚，再通过比较电路比较出模拟信号后接入定时器捕获引脚.

![image](https://github.com/xieyanname/-/assets/103435971/1990aa8a-b616-4d88-8ef9-171088f6af5a)
## 实现流程
初始化了TIM4定时器中断捕获、ADC采集和RT系统线程.
### TIM定时器捕获
TIM4定时器是否捕获到上升沿，捕获到上升沿后改为下降沿，记录脉宽，在不同状态下将脉宽与信号数据位进行匹配.
![image](https://github.com/xieyanname/-/assets/103435971/c7483d8a-227e-40e2-ac95-5f7c4f0bc208)
### RT系统线程4
在状态位达到4时进入判断，获取ADC采集电压值并且记录，对采集到的电压数据进行平均值滤波处理然后匹配.
![image](https://github.com/xieyanname/-/assets/103435971/61d4e92d-7891-44bf-a96f-1957b547bf72)
## 信号的编码与解码
### 单盏灯的信号编码
一盏灯分配五个数据位，分别为同步位，ID1位、ID2位、测压位、停止位.
![image](https://github.com/xieyanname/-/assets/103435971/76b3bd78-cc1f-4383-a5b3-04d6ad8cf540)
下图为示波器采集的单盏灯信号图.
![__UD3@ S Y7NVGIW43CYU$I](https://github.com/xieyanname/-/assets/103435971/e838085c-f94d-444e-a95c-405287384f86)
### 多盏灯信号编码（四盏）
采用时分复用方式发送信号，每盏灯五位数据.
下图为示波器采集四盏灯信号图.
![2{6PMVHY {IV3X$J$WR}{@X](https://github.com/xieyanname/-/assets/103435971/4013b017-827b-42a3-96e8-fa107f91464e)
## 接收硬件电路
![image](https://github.com/xieyanname/-/assets/103435971/51df8976-93a4-4a91-bae5-9e15e889e989)

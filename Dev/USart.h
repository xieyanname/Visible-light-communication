#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"

	

#define  USART1_EN 1
#define  USART2_EN 1
#define  USART3_EN 1


#if USART1_EN == 1
	#define USART1_BAUD         115200
	#define USART1_RX_BUF_SIZE  256
#endif 

#if USART2_EN == 1
	#define USART2_BAUD         115200
	#define USART2_RX_BUF_SIZE  256
#endif 

#if USART3_EN == 1
	#define USART3_BAUD         115200
	#define USART3_RX_BUF_SIZE  256
#endif 


#if USART1_EN == 1
	extern uint8_t   	g_USART1_RxBuf[USART1_RX_BUF_SIZE];//���ڽ��ջ�����
	extern uint16_t 	g_USART1_RecPos;//��ŵ�ǰ���ڽ������ݴ�ŵ�λ��
#endif 

#if USART2_EN == 1
	extern uint8_t   	g_USART2_RxBuf[USART2_RX_BUF_SIZE];//���ڽ��ջ�����
	extern uint16_t 	g_USART2_RecPos;//��ŵ�ǰ���ڽ������ݴ�ŵ�λ��
#endif 

#if USART3_EN == 1
	extern uint8_t  	g_USART3_RxBuf[USART3_RX_BUF_SIZE];//���ڽ��ջ�����
	extern uint16_t 	g_USART3_RecPos;//��ŵ�ǰ���ڽ������ݴ�ŵ�λ��
#endif 

void UsartInit(void);
void UsartSendString(USART_TypeDef* USARTx,uint8_t *str);//�����ַ���


#endif




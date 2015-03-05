#include "dingke_delay.h"
#include "dingke_sysclkchange.h"
////////////////////////////////////////////
//1.�����������ʱ�������ȴ��ķ�ʽ��
//���統����delay_ms�ˣ��ͻ�SysTick_Config(168000); ��stm32f4xx_it.c���и�SysTick_Handler(void)�ͻ�1ms����һ���жϣ�ԭ���һ���֪������������������
//���ж��˾� ntime--;������delay_ms(u16 nms)ֻҪ��һ��ntime��û�б��0����0�˾�˵��ʱ��ĵ���,Ȼ���ֹ�����ж�
//�����˳�delay_ms(u16 nms)������˵������ʱ���Ǽ򵥵����ȴ�
//2.ǧ��Ҫ���˺�	stm32f4xx_it.c ���ʹ��
//3.���ﲻ��Ҫdelay��ʼ��֮��ĺ���
//4.��Ȼ�������ʱʵ������ͨ������ϵͳ���ʱ���ж�������
////////////////////////////////////////////
extern __IO u32 ntime;								    
//ʹ��SysTick���о�ȷ��ʱ

//ms��ʱ
void delay_ms(u16 nms)
{	 		  	  
	ntime=nms;
	
	if(SysClkWasp>CLKCHANGEDELAY1);
	else if(SysClkWasp>CLKCHANGEDELAY2) ntime = ntime<<1;
	else  ntime = ntime<<2;

	SysTick_Config(DelayMsWasp);
	//SysTick_Config(168000);//1ms����һ���ж�,����ntime��1 //���ϵͳʱ��Ϊ168M�����
	while(ntime);//�ȴ�ʱ�䵽��

	SysTick->CTRL=0x00;			  	    
}   
//us��ʱ		    								   
void delay_us(u32 nus)	//������ʱ��10us�����棬��Ҫ����RTC��������us����ʱ���������ʱ��̫Ƶ���ˣ���ϵͳʱ���жϺ�û�г���ȥ�ֽ�ȥ
{		
	ntime=nus;

	if(SysClkWasp>CLKCHANGEDELAY1);
	else if(SysClkWasp>CLKCHANGEDELAY2) ntime = ntime<<1;
	else  ntime = ntime<<2;

//	SysTick_Config(672);//1us����һ���ж�,����ntime��1
	SysTick_Config(DelayUsWasp*4);//1us����һ���ж�,����ntime��1
	
//	while(1)
//	{
//		if((ntime==0)||(ntime>0xffff0000))break;
//	}
	while(ntime);//�ȴ�ʱ�䵽��


	SysTick->CTRL=0x00;
}





























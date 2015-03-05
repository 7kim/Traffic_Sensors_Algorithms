//���ﴮ��1 2 3 6 ��  ��ص�xbee ���� ����6��·ѡ��
//#define ZPPTEMP 0xff 
#include "stm32f4xx_conf.h"
#include "dingke_uart.h"
#include <string.h>

//#include <string.h>
//#ifndef __WASPCONSTANTS_H__
//	#include "WaspConstants.h"
//#endif


#define	UART_LIMIT (RX_BUFFER_SIZE+100)

	unsigned char Rx80Buffer[RX80_BUFFER_SIZE];

	unsigned char rx_buffer3[RX_BUFFER_SIZE_3];
	unsigned char rx_buffer2[RX_BUFFER_SIZE_2];
	unsigned char rx_buffer1[RX_BUFFER_SIZE_1];
	unsigned char rx_buffer6[RX_BUFFER_SIZE_6];
#if USEUSART4==1
	unsigned char rx_buffer4[RX_BUFFER_SIZE_4];
#endif
#if USEUSART5==1
	unsigned char rx_buffer5[RX_BUFFER_SIZE_5];
#endif


	int rxprerx80_buffer_tail3 = 0;

	int Rx80BufferHead = 0;
	int Rx80BufferTail = 0;

	int rx_buffer_head3 = 0;
	int rx_buffer_tail3 = 0;
	int rx_buffer_head2 = 0;
	int rx_buffer_tail2 = 0;
	int rx_buffer_head1 = 0;
	int rx_buffer_tail1 = 0;
	int rx_buffer_head6 = 0;
	int rx_buffer_tail6 = 0;
#if USEUSART4==1
	int rx_buffer_head4 = 0;
	int rx_buffer_tail4 = 0;
#endif
#if USEUSART5==1
	int rx_buffer_head5 = 0;
	int rx_buffer_tail5 = 0;
#endif



static char StrRx80ForMove[300];//�������RecAPIFrameStr��ͬ��RecAPIFrameStr�������н��ܵ���xbee�Ե�Ƭ���Ļظ���StrRx80ֻ����xbee�ӱ��xbee���ܵ�������
static uint16_t LenRx80ForMove=0;








//Ŀǰ֧�ִ���1 2 3
void beginSerial(long baud, uint8_t portNum)
{
	    GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

	//��������3������Ϊ�жϣ����͵������ַ���ʱ�ٿ����жϣ����͵����ֽ�ʱ�ò�ѯ�ķ�ʽ
	if(portNum==3)
	{
	    //GPIO�˿�����	

	
	  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 
	  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);  
	  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);
	
	     //USART3_TX   PD.8
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOD, &GPIO_InitStructure);
	   
	    //USART3_RX	  PD.9
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOD, &GPIO_InitStructure);  
	
	   //Usart3 NVIC ����
	    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//
	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART3
	  
	   //USART ��ʼ������  
		USART_InitStructure.USART_BaudRate = baud;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;	 //û��У��λ

		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	    USART_Init(USART3, &USART_InitStructure);
	   
		USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���
	}
	else if(portNum==1)
	{
	    //GPIO�˿�����	
	  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	  	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);  
	  	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
	
	     //USART1_TX   PB.6
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOB, &GPIO_InitStructure);
	   
	    //USART1_RX	  PB.7
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	   //Usart1 NVIC ����
	    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//
	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1
	  
	   //USART ��ʼ������  
		USART_InitStructure.USART_BaudRate = baud;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	    USART_Init(USART1, &USART_InitStructure);
	   
		USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���

	}
	else if(portNum==2)
	{	
	  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
	  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	  	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);  
	  	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	     //USART2_TX   PA.2
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);
	   
	    //USART2_RX	  PA.3
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
	   //Usart2 NVIC ����
	    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//
	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART2
	  
	   //USART ��ʼ������  
		USART_InitStructure.USART_BaudRate = baud;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		   
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;//û��У��λ

		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	    USART_Init(USART2, &USART_InitStructure);
	   
		USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���	
	}
	else if(portNum==6)
	{
	    //GPIO�˿�����	
	  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 
	  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	
	  	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);  
	  	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
	
	     //USART6_TX   PC.6
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOC, &GPIO_InitStructure);
	   
	    //USART6_RX	  PC.7
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOC, &GPIO_InitStructure);  
	
	   //Usart1 NVIC ����
	    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//
	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1
	  
	   //USART ��ʼ������  
		USART_InitStructure.USART_BaudRate = baud;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	    USART_Init(USART6, &USART_InitStructure);
	   
		USART_Cmd(USART6, ENABLE);                    //ʹ�ܴ���

	}
#if USEUSART4==1
	else if(portNum==4)
	{	
	  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
	  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	
	  	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);  
	  	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);
	
	     //USART4_TX   PA.0
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);
	   
	    //USART4_RX	  PA.1
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
	   //Usart4 NVIC ����
	    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//
	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART4
	  
	   //USART ��ʼ������  
		USART_InitStructure.USART_BaudRate = baud;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	    USART_Init(UART4, &USART_InitStructure);
	   
	    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�����ж� 
	    UART4->CR1&=(~(0x01<<7));//��ֹ�����ж�
		USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ���	
	}
#endif

#if USEUSART5==1
	else if(portNum==5)
	{	
	  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);		 
	  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	
	  	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART4);  
	  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART4);
	
	     //USART5_TX   PC.12
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOC, &GPIO_InitStructure);
	   
	    //USART5_RX	  PD.2
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOD, &GPIO_InitStructure);  
	
	   //Usart5 NVIC ����
	    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//
	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART5
	  
	   //USART ��ʼ������  
		USART_InitStructure.USART_BaudRate = baud;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	    USART_Init(UART5, &USART_InitStructure);
	   
	    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�����ж� 
	    UART5->CR1&=(~(0x01<<7));//��ֹ�����ж�
		USART_Cmd(UART5, ENABLE);                    //ʹ�ܴ���	
	}
#endif
}

void chooseuartinterrupt(uint8_t portNum)
{
	if(portNum==3)
	{	   
	    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж� 
	    USART3->CR1&=(~(0x01<<7));//��ֹ�����ж�
	}
	else if(portNum==1)
	{	   
	    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж� 
	    USART1->CR1&=(~(0x01<<7));//��ֹ�����ж�
	}
	else if(portNum==2)
	{		   
	    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж� 
	    USART2->CR1&=(~(0x01<<7));//��ֹ�����ж�
	}
	else if(portNum==6)
	{	   
	    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//�����ж� 
	    USART6->CR1&=(~(0x01<<7));//��ֹ�����ж�
	}

}

//������3���͵ļ�أ�������3���͵����ݿ���ͨ��usb232���Կ�����
void monitor_onuart3TX(void)
{
// PD15��PD8(uart3 TX)  PA8 ��PD9(usart3 RX)  
  	GPIO_InitTypeDef  GPIO_InitStructured;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  	GPIO_InitStructured.GPIO_Pin = GPIO_Pin_15;
  	GPIO_InitStructured.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructured.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructured.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructured.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOD, &GPIO_InitStructured);

    GPIO_SetBits(GPIOD,GPIO_Pin_15);
}
//������3���յļ�أ�������3���յ����ݿ���ͨ��usb232���Կ�����
void monitor_onuart3RX(void)
{
// PD15��PD8(uart3 TX)  PA8 ��PD9(usart3 RX)  
  	GPIO_InitTypeDef  GPIO_InitStructured;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  	GPIO_InitStructured.GPIO_Pin = GPIO_Pin_8;
  	GPIO_InitStructured.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructured.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructured.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructured.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOA, &GPIO_InitStructured);

    GPIO_SetBits(GPIOA,GPIO_Pin_8);
}

void monitor_offuart3TX(void)
{
// PD15��PD8(uart3 TX)  PA8 ��PD9(usart3 RX)  
  	GPIO_InitTypeDef  GPIO_InitStructured;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  	GPIO_InitStructured.GPIO_Pin = GPIO_Pin_15;
  	GPIO_InitStructured.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructured.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructured.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructured.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOD, &GPIO_InitStructured);

    GPIO_ResetBits(GPIOD,GPIO_Pin_15);
}
void monitor_offuart3RX(void)
{
// PD15��PD8(uart3 TX)  PA8 ��PD9(usart3 RX)  
  	GPIO_InitTypeDef  GPIO_InitStructured;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  	GPIO_InitStructured.GPIO_Pin = GPIO_Pin_8;
  	GPIO_InitStructured.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructured.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructured.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructured.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOA, &GPIO_InitStructured);

    GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}

//Ҫ��USB232�͵ÿ����
//ͬʱ���ǲ����Եģ����Ҫ����·ͼ��
void monitor_on(void)
{
// PD15��PD8(uart3 TX)  PA8 ��PD9(usart3 RX)  
  	GPIO_InitTypeDef  GPIO_InitStructured;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  	GPIO_InitStructured.GPIO_Pin = GPIO_Pin_8;
  	GPIO_InitStructured.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructured.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructured.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructured.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOA, &GPIO_InitStructured);

    GPIO_SetBits(GPIOA,GPIO_Pin_8);


  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  	GPIO_InitStructured.GPIO_Pin = GPIO_Pin_15;
  	GPIO_InitStructured.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructured.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructured.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructured.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOD, &GPIO_InitStructured);

    GPIO_SetBits(GPIOD,GPIO_Pin_15);

}

//xbee��Դ����
void Xbee_poweron(void)
{

// ��PTD11�øߣ�Ҳ������Xbee ģ�鹩�磬����Xbee���ܹ���//�°�����PD11
  	GPIO_InitTypeDef  GPIO_InitStructured;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  	GPIO_InitStructured.GPIO_Pin = GPIO_Pin_11;
  	GPIO_InitStructured.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructured.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructured.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructured.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOD, &GPIO_InitStructured);

   GPIOD->BSRRL=GPIO_Pin_11; //Ŀǰ�����Ӳ�֪��ΪʲôGPIO�����ǵͣ�����ȴ�Ǹߡ����������ʱ����

}

void Xbee_poweroff(void)
{
// �°�����PD11��
  	GPIO_InitTypeDef  GPIO_InitStructured;
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  	GPIO_InitStructured.GPIO_Pin = GPIO_Pin_11;
  	GPIO_InitStructured.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructured.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructured.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructured.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOD, &GPIO_InitStructured);
	
	GPIO_ResetBits(GPIOD,GPIO_Pin_11);
}
//��·ѡ����
void Mux_poweron(void)
{
	GPIO_InitTypeDef  GPIO_InitStructured;
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  	GPIO_InitStructured.GPIO_Pin = GPIO_Pin_8;
  	GPIO_InitStructured.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructured.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructured.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructured.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOE, &GPIO_InitStructured);

	GPIO_SetBits(GPIOE, GPIO_Pin_8);
}

void Mux_poweroff(void)
{
	GPIO_InitTypeDef  GPIO_InitStructured;
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  	GPIO_InitStructured.GPIO_Pin = GPIO_Pin_8;
  	GPIO_InitStructured.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructured.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructured.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructured.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOE, &GPIO_InitStructured);

	GPIO_ResetBits(GPIOE, GPIO_Pin_8);
}
//����6��·ѡ���ʼ����ע��������Ǵ���6��ʼ��
void muluart6init(void)
{
  	GPIO_InitTypeDef  GPIO_InitStructured;

	Mux_poweron();

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  	GPIO_InitStructured.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  	GPIO_InitStructured.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructured.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructured.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructured.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOB, &GPIO_InitStructured);	
}

void muluart6choose(unsigned char choose)
{
	if(choose==1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);	
	}
	else if(choose==2)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
		GPIO_SetBits(GPIOB, GPIO_Pin_0);	
	}
	else if(choose==3)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);	
	}
	else if(choose==4)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
		GPIO_SetBits(GPIOB, GPIO_Pin_0);	
	}
}




void closexbeepwr(void)
{
		//����Xbeeģ��Ͳ��Ṥ����
	   GPIOD->BSRRH=GPIO_Pin_15; //Ŀǰ�����Ӳ�֪��ΪʲôGPIO�����ǵͣ�����ȴ�Ǹߡ����������ʱ����
}

//��������3
//��Xbee����
//����TIM3,1ms�ж�һ�Σ�Ϊ�˼�������ms�������Ϊ��֧��millis(),���������WaspXBeeCore.cpp���õ�
// connects the internal peripheral in the processor and configures it
void beginxbee(long baud, uint8_t portNum)
{	
	//��������3������Ϊ�жϣ����͵������ַ���ʱ�ٿ����жϣ����͵����ֽ�ʱ�ò�ѯ�ķ�ʽ
	beginSerial(baud, portNum);
	chooseuartinterrupt(portNum);//���������жϣ������ж���ʱ�ǽ�ֹ��
	Xbee_poweron();
	//����1ms �ж�һ��
	Timer3_Init(10,10000); //�ڶ���������time��Ƶ�ʣ���һ��������cnt
}


//����ص�XBee�ĵ�Դ������XBee�Ͳ��Ṥ���ˣ�
//���ﲢû�йص���ʱ��3�������Ҫ�ص�����ͻ����
// disconnects the internal peripheral in the processor
void closeSerial(uint8_t portNum)
{
	if(portNum==3)
	{
	   closexbeepwr();
	   USART_Cmd(USART3, DISABLE);
	}
	else if(portNum==1)
	{
	   USART_Cmd(USART1, DISABLE);
	}
	else if(portNum==2)
	{
	   USART_Cmd(USART2, DISABLE);
	}
	else if(portNum==6)
	{
	   USART_Cmd(USART6, DISABLE);
	}
#if USEUSART4==1
	else if(portNum==4)
	{
	   USART_Cmd(UART4, DISABLE);
	}
#endif

#if USEUSART5==1
	else if(portNum==5)
	{
	   USART_Cmd(UART5, DISABLE);
	}
#endif

}
//�ò�ѯ�ķ�ʽ���ʹ���3����
void serialWrite(unsigned char c, uint8_t portNum)
{
	if(portNum==3)
	{
	while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
    USART3->DR = (uint8_t ) c;
	}
	else if(portNum==1)
	{
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (uint8_t ) c;
	}
	else if(portNum==2)
	{
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
    USART2->DR = (uint8_t ) c;
	}
	else if(portNum==6)
	{
	while((USART6->SR&0X40)==0);//ѭ������,ֱ���������   
    USART6->DR = (uint8_t ) c;
	}

#if USEUSART4==1
	else if(portNum==4)
	{
	while((UART4->SR&0X40)==0);//ѭ������,ֱ���������   
    UART4->DR = (uint8_t ) c;
	}
#endif

#if USEUSART5==1
	else if(portNum==5)
	{
	while((UART5->SR&0X40)==0);//ѭ������,ֱ���������   
    UART5->DR = (uint8_t ) c;
	}
#endif


}
//����ǰ����һ��
int serialAvailable(uint8_t portNum)
{
	if (portNum == 3)
		return (RX_BUFFER_SIZE_3 + rx_buffer_head3 - rx_buffer_tail3) % RX_BUFFER_SIZE_3;
	else if (portNum == 1)
		return (RX_BUFFER_SIZE_1 + rx_buffer_head1 - rx_buffer_tail1) % RX_BUFFER_SIZE_1;
	else if (portNum == 2)
		return (RX_BUFFER_SIZE_2 + rx_buffer_head2 - rx_buffer_tail2) % RX_BUFFER_SIZE_2;
	else if (portNum == 6)
		return (RX_BUFFER_SIZE_6 + rx_buffer_head6 - rx_buffer_tail6) % RX_BUFFER_SIZE_6;
#if USEUSART4==1
	else if (portNum == 4)
		return (RX_BUFFER_SIZE_4 + rx_buffer_head4 - rx_buffer_tail4) % RX_BUFFER_SIZE_4;
#endif

#if USEUSART5==1
	else if (portNum == 5)
		return (RX_BUFFER_SIZE_5 + rx_buffer_head5 - rx_buffer_tail5) % RX_BUFFER_SIZE_5;
#endif
	else return 0;
	
}
//����ǰ����һ��
int serialRead(uint8_t portNum)
{
	if (portNum == 3) 
	{
		// if the head isn't ahead of the tail, we don't have any characters
		if (rx_buffer_head3 == rx_buffer_tail3) 
		{
			return UARTRECEMPTY;
		} 
		else 
		{
			unsigned char c = rx_buffer3[rx_buffer_tail3];
			rx_buffer_tail3 = (rx_buffer_tail3 + 1) % RX_BUFFER_SIZE_3;
			return c;
		}
	}
	else if (portNum == 1) 
	{
		// if the head isn't ahead of the tail, we don't have any characters
		if (rx_buffer_head1 == rx_buffer_tail1) 
		{
			return UARTRECEMPTY;
		} 
		else 
		{
			unsigned char c = rx_buffer1[rx_buffer_tail1];
			rx_buffer_tail1 = (rx_buffer_tail1 + 1) % RX_BUFFER_SIZE_1;
			return c;
		}
	}
	else if (portNum == 2) 
	{
		// if the head isn't ahead of the tail, we don't have any characters
		if (rx_buffer_head2 == rx_buffer_tail2) 
		{
			return UARTRECEMPTY;
		} 
		else 
		{
			unsigned char c = rx_buffer2[rx_buffer_tail2];
			rx_buffer_tail2 = (rx_buffer_tail2 + 1) % RX_BUFFER_SIZE_2;
			return c;
		}
	}
	else if (portNum == 6) 
	{
		// if the head isn't ahead of the tail, we don't have any characters
		if (rx_buffer_head6 == rx_buffer_tail6) 
		{
			return UARTRECEMPTY;
		} 
		else 
		{
			unsigned char c = rx_buffer6[rx_buffer_tail6];
			rx_buffer_tail6 = (rx_buffer_tail6 + 1) % RX_BUFFER_SIZE_6;
			return c;
		}
	}
#if USEUSART4==1
	else if (portNum == 4) 
	{
		// if the head isn't ahead of the tail, we don't have any characters
		if (rx_buffer_head4 == rx_buffer_tail4) 
		{
			return UARTRECEMPTY;
		} 
		else 
		{
			unsigned char c = rx_buffer4[rx_buffer_tail4];
			rx_buffer_tail4 = (rx_buffer_tail4 + 1) % RX_BUFFER_SIZE_4;
			return c;
		}
	}
#endif

#if USEUSART5==1
	else if (portNum == 5) 
	{
		// if the head isn't ahead of the tail, we don't have any characters
		if (rx_buffer_head5 == rx_buffer_tail5) 
		{
			return UARTRECEMPTY;
		} 
		else 
		{
			unsigned char c = rx_buffer5[rx_buffer_tail5];
			rx_buffer_tail5 = (rx_buffer_tail5 + 1) % RX_BUFFER_SIZE_5;
			return c;
		}
	}
#endif


	else return UARTRUNSUPPORT;
}


//
int serialPreRx80Available(void)
{
		return (RX_BUFFER_SIZE_3 + rx_buffer_head3 - rxprerx80_buffer_tail3) % RX_BUFFER_SIZE_3;	
}
//
int serialPreRx80Read(void)
{
		// if the head isn't ahead of the tail, we don't have any characters
		if (rx_buffer_head3 == rxprerx80_buffer_tail3) 
		{
			return UARTRECEMPTY;
		} 
		else 
		{
			unsigned char c = rx_buffer3[rxprerx80_buffer_tail3];
			rxprerx80_buffer_tail3 = (rxprerx80_buffer_tail3 + 1) % RX_BUFFER_SIZE_3;
			return c;
		}
}

uint8_t handle1msprerx80(void)
{
	int recnum=0;
	uint8_t ch;
//	uint8_t lenrecapi=0;
	uint8_t check;
	uint8_t icheck=3;
	long i=0;

loopstart:
			if( (recnum=serialPreRx80Available())==0 )
			{
				return 2;//��û���յ�����				
			}
			else
			{
				while(recnum--)
				{
					ch=serialPreRx80Read();
//#if ZPPDEBUGXBEEPRINT==1
					//printf("c%2x",ch);
					//printf("%c",ch);
//#endif
					if(LenRx80ForMove==0)
					{
						if(ch==0x7e)
						{
							StrRx80ForMove[LenRx80ForMove]=ch;
							LenRx80ForMove++;
							continue;
						}
						else
							continue;
					}
					else
					{ 
						if(LenRx80ForMove==2)
						{
//							lenrecapi= (uint16_t)((((uint16_t)StrRx80ForMove[1])<<8)|ch); //�����ch����д�� RecAPIFrameStr[2],��Ϊ[2]��û�и�ֵ����
//#if ZPPDEBUGXBEEPRINT==1
//							printf("lenapi=%2x ",lenrecapi);
//#endif						
							//���Ǽٶ�������С��256���ֽڵģ��������������ж�
							if(StrRx80ForMove[1]!=0)
							{
								LenRx80ForMove=0;
								return 4;
								//continue;
							}
						}
						else if((LenRx80ForMove==3)&&(ch!=0x80))
						{
							LenRx80ForMove=0;
							return 3;
							//continue;
						}
						else if((LenRx80ForMove>3)&&(LenRx80ForMove==(StrRx80ForMove[2]+3)))//���ﲻ��ʹ��lenrecapi���ֵ
						{
							
							check=0;
							for(icheck=3;icheck<LenRx80ForMove;icheck++)
								check = check+StrRx80ForMove[icheck];
#if ZPPDEBUGXBEEPRINT==1
							printf("chk:%2x ",check);
#endif
							check = 0xff -check;
#if ZPPDEBUGXBEEPRINT==1
							printf("chk:%2x <>",check);
							for(uint8_t icheck=0;icheck<LenRx80ForMove;icheck++)
								printf("%2x ",StrRx80ForMove[icheck]);
#endif
							if(check!=ch)
							{
								LenRx80ForMove=0;
								return 5;
								//continue;
							}
							else 
							{
#if ZPPDEBUGXBEEPRINT==1
								printf("find a APIframe ");
#endif
//								if(StrRx80[3]==0x80)

		 						StrRx80ForMove[LenRx80ForMove]=ch;
								LenRx80ForMove++;
								goto end;
//								else return 3;
								//return 0;
							}
						}

						StrRx80ForMove[LenRx80ForMove]=ch;
						LenRx80ForMove++;
					}
#if ZPPDEBUGXBEEPRINT==1
					printf("ofs=%2x ",LenRx80ForMove);	
#endif									
				}
			}
			
	return 1;

//loop4:
	

end:

////	printf("*len=%d lenrx80=%d  ",*len,LenRx80);
//	*len = (*len)<LenRx80ForMove ? (*len):LenRx80ForMove ;
////	printf("*len=%d lenrx80=%d  ",*len,LenRx80);
	for(icheck=0; icheck<LenRx80ForMove; icheck++)
	{
		i = (Rx80BufferHead + 1) % RX80_BUFFER_SIZE;
		//if (i != Rx80BufferTail)
		{
			Rx80Buffer[Rx80BufferHead] = StrRx80ForMove[icheck];
			Rx80BufferHead = i;
			if(Rx80BufferHead==UART_LIMIT)
			{
				Rx80BufferHead=0;
				Rx80BufferTail=0;
			}
		}

	}


	LenRx80ForMove = 0;	
	if(recnum>0)
		goto loopstart;	
	return 0;





}
//
int serialRx80Available(void)
{
		return (RX80_BUFFER_SIZE + Rx80BufferHead - Rx80BufferTail) % RX80_BUFFER_SIZE;	
}
//
int serialRx80Read(void)
{
		// if the head isn't ahead of the tail, we don't have any characters
		if (Rx80BufferHead == Rx80BufferTail) 
		{
			return UARTRECEMPTY;
		} 
		else 
		{
			unsigned char c = Rx80Buffer[Rx80BufferTail];
			Rx80BufferTail = (Rx80BufferTail + 1) % RX80_BUFFER_SIZE;
			return c;
		}
}





//��Ҫ�������ݱ������������򷵻�-1��
//�ѵ��ڽ��������ݶ������������len����������str�����������,������ʣ�µ����ݵȴ��´��ٶ�
//���������û�������򷵻�0�������ݷ��ظ���str���ݸ���
//��������������٣�str��len�����ж��ٶ�����
int serialReadstr(uint8_t *str, uint8_t len,uint8_t portNum)
{
	int i;
	int recvzhi;
	if(len>RX_BUFFER_SIZE)return UARTRECERRELSE;

	for(i=0;i<len;i++)
	{
		recvzhi=serialRead(portNum);
		if(recvzhi>=0)//���յ����ݣ����û�н��յ�������������ݿ϶��Ǹ�������Ϊ���������ﶼ�ø���������ģ�
		{
			str[i]=recvzhi;
		}
		else return i;
	}
	return i;
}


//����ǰ����һ��
void serialFlush(uint8_t portNum)
{
	// don't reverse this or there may be problems if the RX interrupt
	// occurs after reading the value of rx_buffer_head but before writing
	// the value to rx_buffer_tail; the previous value of rx_buffer_head
	// may be written to rx_buffer_tail, making it appear as if the buffer
	// were full, not empty.
	if (portNum == 3){
		rx_buffer_tail3=0;
		rx_buffer_head3 = rx_buffer_tail3;
	}
	else if (portNum == 1)
	{
		rx_buffer_tail1=0;
		rx_buffer_head1 = rx_buffer_tail1;
	}
	else if (portNum == 2)
	{
		rx_buffer_tail2=0;
		rx_buffer_head2 = rx_buffer_tail2;
	}
	else if (portNum == 6)
	{
		rx_buffer_tail6=0;
		rx_buffer_head6 = rx_buffer_tail6;
	}
#if USEUSART4==1
	else if (portNum == 4)
	{
		rx_buffer_tail4=0;
		rx_buffer_head4 = rx_buffer_tail4;
	}
#endif

#if USEUSART5==1
	else if (portNum == 5)
	{
		rx_buffer_tail5=0;
		rx_buffer_head5 = rx_buffer_tail5;
	}
#endif

}



//�������ǰһ�������õĺ�������3�ǲ�ѯ��ʽ����һ���ֽ�
void printByte(unsigned char c, uint8_t portNum)
{
	serialWrite(c, portNum);
}

//void printNewline(uint8_t portNum)
//{
//	printByte('\n', portNum);
//}

//uint8_t USART_RX_BUF3[64];     //���ջ���,���64���ֽ�.
//uint8_t USART_RX_STA3=0;       //����״̬���

//uint8_t USART_RX_BUF1[64];     //���ջ���,���64���ֽ�.
//uint8_t USART_RX_STA1=0;       //����״̬���

//uint8_t USART_RX_BUF2[64];     //���ջ���,���64���ֽ�.
//uint8_t USART_RX_STA2=0;       //����״̬���

uint32_t USARTTCnt3=0;
char *pUSART_TX_BUF3; 

uint32_t USARTTCnt1=0;
char *pUSART_TX_BUF1; 

uint32_t USARTTCnt2=0;
char *pUSART_TX_BUF2; 

uint32_t USARTTCnt6=0;
char *pUSART_TX_BUF6;
 
#if USEUSART4==1
uint32_t USARTTCnt4=0;
char *pUSART_TX_BUF4;
#endif

#if USEUSART5==1
uint32_t USARTTCnt5=0;
char *pUSART_TX_BUF5;
#endif

////��ʼ������3
////���������жϣ���û�п��������жϣ�
////��Ҫ��һ���ֽ�ʱ���õ��ǲ�ѯ�ķ�ʽ���� serialWrite(unsigned char c, uint8_t portNum)
////��Ҫ���ַ���ʱ���õ����жϷ�ʽ���� printString(const char *s, uint8_t portNum) ��	USART3_IRQHandler(void)
//void COM3Init(uint32_t BaudRate)
//{
//      //GPIO�˿�����
//    GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	 
////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_AHB1Periph_GPIOA , ENABLE);
//  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 
//  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
//
//  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);  
//  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);
//
//     //USART1_TX   PD.8
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_Init(GPIOD, &GPIO_InitStructure);
//   
//    //USART1_RX	  PD.9
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_Init(GPIOD, &GPIO_InitStructure);  
//
//   //Usart1 NVIC ����
//
//    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//
//
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1
//  
//   //USART ��ʼ������  
//	USART_InitStructure.USART_BaudRate = BaudRate;//һ������Ϊ9600;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//
//    USART_Init(USART3, &USART_InitStructure);
//   
//    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
//    //USART_ITConfigzpp(USART3, USART_IT_TXE, ENABLE);//�����ж�
//    //USART_ITConfigzpp(USART3, USART_IT_RXNE|USART_IT_TC , ENABLE);//�����ж�  
//    //USART_ITConfigzpp(USART3, USART_IT_RXNE|USART_IT_TXE , ENABLE);//�����ж�  
//    USART3->CR1&=(~(0x01<<7));//��ֹ�����ж�
//	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���
//}
//
//
//




//����3�жϷ������
void USART3_IRQHandler(void)                	
{
	uint8_t Res;	
	int  i;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART3);//(USART3->DR);	//��ȡ���յ�������
		
		i = (rx_buffer_head3 + 1) % RX_BUFFER_SIZE_3;
		// if we should be storing the received character into the location
		// just before the tail (meaning that the head would advance to the
		// current location of the tail), we're about to overflow the buffer
		// and so we don't write the character or advance the head.
		//if (i != rx_buffer_tail3)
		 {
			rx_buffer3[rx_buffer_head3] = Res;
			rx_buffer_head3 = i;
			if(rx_buffer_head3==UART_LIMIT)
			{
				rx_buffer_head3=0;
				rx_buffer_tail3=0;
			}
		}
		//if(Res==0xe5)serialWrite(0xd5, 3);

		//serialWrite(Res, 2);
		if((Res>='A')&&(Res<='Z'))
		//if(Res=='i')
		{
		  //USART_Cmd(USART3, DISABLE);
			//;
			//serialWrite(Res, 3);
			if(Res=='I')
			{

			   //NVIC_SystemReset();
			}
			return;


		}


  		 
     } 
	 else if(USART_GetITStatus(USART3, USART_IT_TXE ) != RESET)
	 {
	 	if(USARTTCnt3>0)
		{
			USART_SendData(USART3, (uint8_t ) pUSART_TX_BUF3[0]);
			   pUSART_TX_BUF3++;
			USARTTCnt3--;		
		}
		else
		{
			USART3->CR1&=(~(0x01<<7));//��ֹ�����ж�
		}

	 }
} 







//Ŀǰ�ò�ѯ�ķ�ʽ�����ַ���
//���￪���жϣ������ͽ�����Ҳ����˵USARTTCnt3=0��ʱ����ص��ж�
void printString(const char *s, uint8_t portNum)
{
uint32_t len,ilen;

	//uartsendstr((char *)s, strlen(s),portNum);
	//USARTTCnt3=strlen(s);
	//pUSART_TX_BUF3=(char *)s;
	//USART3->CR1|=((0x01<<7));//���������ж�

//����ͻ���ϲ�����жϷ�ʽ���ͣ��ò�ѯ��ʽҲ���ԣ������ǲ�ѯ��ʽ ,��Ȼ������Ĵ������ε�
len=strlen(s);
for(ilen=0;ilen<len;ilen++)	
	serialWrite(s[ilen], portNum);


}
void serialWritestr(char *s, uint8_t len,uint8_t portNum)
{
	uartsendstr(s, len,portNum);
}

//�жϷ�ʽ��������
void uartsendstr(char *s, uint8_t len,uint8_t portNum)
{
	if(portNum==3)
	{
		USARTTCnt3=len;
		pUSART_TX_BUF3=(char *)s;
		USART3->CR1|=((0x01<<7));//����������//
	}
	else if(portNum==1)
	{
		USARTTCnt1=len;
		pUSART_TX_BUF1=(char *)s;
		USART1->CR1|=((0x01<<7));//����������
	}
	else if(portNum==2)
	{
		USARTTCnt2=len;
		pUSART_TX_BUF2=(char *)s;
		USART2->CR1|=((0x01<<7));//����������//
	}
	else if(portNum==6)
	{
		USARTTCnt6=len;
		pUSART_TX_BUF6=(char *)s;
		USART6->CR1|=((0x01<<7));//����������//
	}
#if USEUSART4==1
	else if(portNum==4)
	{
		USARTTCnt4=len;
		pUSART_TX_BUF4=(char *)s;
		UART4->CR1|=((0x01<<7));//����������//

	}
#endif

#if USEUSART5==1
	else if(portNum==5)
	{
		USARTTCnt5=len;
		pUSART_TX_BUF5=(char *)s;
		UART5->CR1|=((0x01<<7));//����������//

	}
#endif


}





void USART1_IRQHandler(void)                	//����1�жϷ������
{
	uint8_t Res;
	int  i;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������

		i = (rx_buffer_head1 + 1) % RX_BUFFER_SIZE_1;
		// if we should be storing the received character into the location
		// just before the tail (meaning that the head would advance to the
		// current location of the tail), we're about to overflow the buffer
		// and so we don't write the character or advance the head.
		if (i != rx_buffer_tail1)
		 {
			rx_buffer1[rx_buffer_head1] = Res;
			rx_buffer_head1 = i;
			if(rx_buffer_head1==UART_LIMIT)
			{
				rx_buffer_head1=0;
				rx_buffer_tail1=0;
			}
		}
		//serialWrite(Res, 1);   		 
     }
	 else if(USART_GetITStatus(USART1, USART_IT_TXE ) != RESET)
	 {
	 	if(USARTTCnt1>0)
		{
			USART_SendData(USART1, (uint8_t ) pUSART_TX_BUF1[0]);
			   pUSART_TX_BUF1++;
			USARTTCnt1--;		
		}
		else
		{
			USART1->CR1&=(~(0x01<<7));//��ֹ�����ж�
		}

	 }	  
} 


void USART2_IRQHandler(void)                	//����1�жϷ������
{
	uint8_t Res;
	int  i;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART2);//(USART2->DR);	//��ȡ���յ�������
		
		i = (rx_buffer_head2 + 1) % RX_BUFFER_SIZE_2;
		// if we should be storing the received character into the location
		// just before the tail (meaning that the head would advance to the
		// current location of the tail), we're about to overflow the buffer
		// and so we don't write the character or advance the head.
		if (i != rx_buffer_tail2)
		 {
			rx_buffer2[rx_buffer_head2] = Res;
			rx_buffer_head2 = i;
			if(rx_buffer_head2==UART_LIMIT)
			{
				rx_buffer_head2=0;
				rx_buffer_tail2=0;
			}
		}

  		 
     }
	 else if(USART_GetITStatus(USART2, USART_IT_TXE ) != RESET)
	 {
	 	if(USARTTCnt2>0)
		{
			USART_SendData(USART2, (uint8_t ) pUSART_TX_BUF2[0]);
			   pUSART_TX_BUF2++;
			USARTTCnt2--;		
		}
		else
		{
			USART2->CR1&=(~(0x01<<7));//��ֹ�����ж�
		}

	 }	  
} 
void USART6_IRQHandler(void)                	//����6�жϷ������
{
	uint8_t Res;
	int  i;
	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART6);//(USART6->DR);	//��ȡ���յ�������

		i = (rx_buffer_head6 + 1) % RX_BUFFER_SIZE_6;
		// if we should be storing the received character into the location
		// just before the tail (meaning that the head would advance to the
		// current location of the tail), we're about to overflow the buffer
		// and so we don't write the character or advance the head.
		if (i != rx_buffer_tail6)
		 {
			rx_buffer6[rx_buffer_head6] = Res;
			rx_buffer_head6 = i;
			if(rx_buffer_head6==UART_LIMIT)
			{
				rx_buffer_head6=0;
				rx_buffer_tail6=0;
			}
		}

		 
     }
	 else if(USART_GetITStatus(USART6, USART_IT_TXE ) != RESET)
	 {
	 	if(USARTTCnt6>0)
		{
			USART_SendData(USART6, (uint8_t ) pUSART_TX_BUF6[0]);
			   pUSART_TX_BUF6++;
			USARTTCnt6--;		
		}
		else
		{
			USART6->CR1&=(~(0x01<<7));//��ֹ�����ж�
		}

	 }	  
} 

#if USEUSART4==1
void UART4_IRQHandler(void)                	//����4�жϷ������
{
	uint8_t Res;
	int  i;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(UART4);//(UART4->DR);	//��ȡ���յ�������
		
		i = (rx_buffer_head4 + 1) % RX_BUFFER_SIZE_4;
		// if we should be storing the received character into the location
		// just before the tail (meaning that the head would advance to the
		// current location of the tail), we're about to overflow the buffer
		// and so we don't write the character or advance the head.
		if (i != rx_buffer_tail4)
		 {
			rx_buffer4[rx_buffer_head4] = Res;
			rx_buffer_head4 = i;
			if(rx_buffer_head4==UART_LIMIT)
			{
				rx_buffer_head4=0;
				rx_buffer_tail4=0;
			}
		}
		 
     }
	 else if(USART_GetITStatus(UART4, USART_IT_TXE ) != RESET)
	 {
	 	if(USARTTCnt4>0)
		{
			USART_SendData(UART4, (uint8_t ) pUSART_TX_BUF4[0]);
			   pUSART_TX_BUF4++;
			USARTTCnt4--;		
		}
		else
		{
			UART4->CR1&=(~(0x01<<7));//��ֹ�����ж�
		}

	 }	  
} 
#endif


#if USEUSART5==1
void UART5_IRQHandler(void)                	//����4�жϷ������
{
	uint8_t Res;
	int  i;
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(UART5);//(UART4->DR);	//��ȡ���յ�������
		
		i = (rx_buffer_head5 + 1) % RX_BUFFER_SIZE_5;
		// if we should be storing the received character into the location
		// just before the tail (meaning that the head would advance to the
		// current location of the tail), we're about to overflow the buffer
		// and so we don't write the character or advance the head.
		if (i != rx_buffer_tail5)
		 {
			rx_buffer5[rx_buffer_head5] = Res;
			rx_buffer_head5 = i;
			if(rx_buffer_head5==UART_LIMIT)
			{
				rx_buffer_head5=0;
				rx_buffer_tail5=0;
			}
		}
		 
     }
	 else if(USART_GetITStatus(UART5, USART_IT_TXE ) != RESET)
	 {
	 	if(USARTTCnt5>0)
		{
			USART_SendData(UART5, (uint8_t ) pUSART_TX_BUF5[0]);
			   pUSART_TX_BUF5++;
			USARTTCnt5--;		
		}
		else
		{
			UART5->CR1&=(~(0x01<<7));//��ֹ�����ж�
		}

	 }	  
} 
#endif



//�������ǰ��������1.��ǰ�ǲ�ѯ��ʽһ���������ֽڣ�����ĳ��жϷ�ʽ�����ַ�����2.Ϊ�����жϷ�ʽ�����ַ���������ǰ�ڴ���
//������õ����ò�ѯ��ʽ�����ַ�����
//Ŀǰbase>16��Ϊ�ǷǷ�������ͻ������޸ĵ�
//��ʵ���߾����������������û�д����ԣ������ȫ������sprintf �� uartsendstr ����
void printIntegerInBase(unsigned long n, unsigned long base, uint8_t portNum)
{ 
	unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars. 
	unsigned long i = 0;
	unsigned long len;
	unsigned char temp;

	if (n == 0) {
		buf[0]='0';
		buf[1]=0x00;
		printString((const char *)buf, portNum);
		return;
	} 

	if(base>16)
	{
		sprintf((char *) buf,"error: base>16! ");
		printString((const char *)buf, portNum);
		return;			
	}
	//�õ�[0]=n%base [1]=(n/base)%base ...
	while (n > 0) {
		buf[i++] = n % base;
		n /= base;
	}
	buf[i]=0x00;
	len=i;
	//����һ�� ʹ��[0]Ϊ���λ
	for(i=0;i<(len+1)/2;i++)
	{
		temp=buf[i];
		buf[i]=buf[len-1-i];
		buf[len-1-i]=temp;
	}
	//������ת����ASICC�룬Ŀǰֻ֧��16���Ƽ����£����Ե����ִ���9����ʾA~F������ͻ�Ҫ��֧�ֳ���16���ƣ���Ҫ�ͻ���д��һ��
	for(i=0;i<len;i++)
	{
		if(buf[i]<10)buf[i]+='0';
		else buf[i]+='A'-10;
	}
	//�жϷ�ʽ���ַ�������ȥ
	printString((const char *)buf, portNum);

}


void beginMb7076(void)
{
  	GPIO_InitTypeDef  GPIO_InitStructure;//GPIO��ʼ���ṹ��
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//����ʱ��ʹ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_7);
	beginSerial(9600, 2);
	chooseuartinterrupt(2);
	
}
//return  2 // //û���κ�������	 //rx_buffer_head2==rx_buffer_tail2
//        0	// ����һ��������������	, �����������һ���������յ�������һ�����ݰ���
//                                                     ��һ��,��ǰ���յ��ü�������ǰ������ݰ����������ģ����һ������������ʱ����ǰ�� ���ݰ�����
//        1 // �����ݣ�����Ŀǰ���ݲ���(ֻ�а������,��������İ�������������),��Ҫ�ȴ�һ���,��ʱ���ݷ���ֵΪ�ϴε�����ֵ
// ����յ���������ȷ�������ֵ��value������
int readMb7076( int* value)
{
	int len;
	int strbegain;
	int cengci=0;
	uint8_t zhi;
	uint8_t zhia[6];
	static int LastMb7076Value=0;
	int counterr=0;
	int i;
	int head2 ;
	i= rx_buffer_tail2;	head2= rx_buffer_head2;
//	if(i!=head2)
//	{
		
//		printf(" i=%d head2=%d ",i,head2);
//		while(1)
//		{
//			i++;
//			i %= RX_BUFFER_SIZE_2;	
//			printf(" %2x",rx_buffer2[i]);
//
//			if(i== head2)
//			{
//				break;
//			}
//			
//		}
//
//	}



	if(head2 !=rx_buffer_tail2)
	{
		len = (head2 +RX_BUFFER_SIZE_2-rx_buffer_tail2)%RX_BUFFER_SIZE_2;
//		printf("len=%d",len);
		if(len<6) //// �����ݣ�����Ŀǰ���ݲ���
		{
			*value=LastMb7076Value ;
			return 1; 
		}
//		zhi= rx_buffer2[rx_buffer_head2];
//		if(zhi=='\n'){* value = 11; }
//		else if( (zhi>='0')&&(zhi<='9')){* value = zhi-'0'; }
//		else if(zhi=='R'){* value = 12; }
//		else  {* value = 13; }
//		rx_buffer_tail2 = rx_buffer_head2 ;
//
//		return 0;
		strbegain = (head2 +RX_BUFFER_SIZE_2-5)%RX_BUFFER_SIZE_2;
//		printf(" start:%d ",strbegain);
		while(1)
		{
			for(cengci=0;cengci<6;cengci++)
			{
				zhi= rx_buffer2[(strbegain+cengci)%RX_BUFFER_SIZE_2];
//				printf("zhi=%d ",zhi);
//				printf(" cen=%d ",cengci);
				if(cengci==0)
				{
//					printf(" 000 ");
					if(zhi!='R')break;
				}
				else if((cengci>=1)&&(cengci<=4))
				{
//					printf(" 111444 ");
					if((zhi<'0')||(zhi>'9'))
					{
						printf(" false num cebgci=%d ",cengci);
						break;
					}
					zhia[cengci-1]=zhi-'0';
//					printf(" ce-1 =%d []=%d ",cengci-1,zhia[cengci-1]);
				}
				else if(cengci==5)
				{
//					printf(" 555 ");
					if(zhi!=0x0d)
					{ 
						//printf("no end");
						break; 
					}
				}
				else
				{
					printf("   WRONG    ");
				}
			}
			if(cengci==6)
			{
//				printf(" zhia %d %d %d %d ",zhia[0],zhia[1],zhia[2],zhia[3]);
				*value = ((int)zhia[0])*1000+((int)zhia[1])*100+ ((int)zhia[2])*10+ ((int)zhia[3]);
//				printf(" *value %d ,",*value );
				LastMb7076Value=*value ;
				//rx_buffer_tail2 = (head2 +RX_BUFFER_SIZE_2-5)%RX_BUFFER_SIZE_2;
				rx_buffer_tail2 = head2;
				return 0;
			}
			else
			{
				;
//				printf(" cengci=%d ",cengci);
			}
			
			

			strbegain = (strbegain +RX_BUFFER_SIZE_2-1)%RX_BUFFER_SIZE_2;
//			printf(" start:%d ",strbegain);

			if(strbegain == rx_buffer_tail2)
			{
				rx_buffer_tail2 = (head2 +RX_BUFFER_SIZE_2-6)%RX_BUFFER_SIZE_2;
				*value=LastMb7076Value ;

				return 1;
			}
			delay_ms(1);
			counterr++;
			if(counterr>1000)return 3;
		}

		
	}
	else
	{ 
		
		//*value = 0;
		*value=LastMb7076Value ;
		return 2;//û���κ�������
	}
}



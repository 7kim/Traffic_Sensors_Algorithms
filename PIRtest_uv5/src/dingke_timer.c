
//������Ҫ�Ƕ�ʱ��3 �Ͷ�ʱ��2 �Լ��Ͷ�ʱ��3�йص��Ǹ�delay()
//#include "timer.h"
#include "dingke_timer.h"

//ͨ�ö�ʱ���жϳ�ʼ��

//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
//Ŀǰ�����1ms������
void Timer3_Init(u16 cnt,u32 hz)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  RCC_ClocksTypeDef RCC_ClocksStatus;
  uint32_t flagapb=1;
  uint32_t apbtmclk;


  if(cnt==0)cnt=2;
  else if(cnt==1){cnt=10;hz=hz*10; }

  if(hz==0)hz=1;
  else if(hz>1000000)hz=1000000;



  RCC_GetClocksFreq(&RCC_ClocksStatus);
  if(RCC_ClocksStatus.SYSCLK_Frequency==16000000)//�ڲ�����
  {
	TIM_TimeBaseStructure.TIM_Prescaler =(16000000/hz-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��   
  }
  else
  {
  	if(RCC_ClocksStatus.PCLK1_Frequency==RCC_ClocksStatus.SYSCLK_Frequency);
	else flagapb=2;
	apbtmclk=RCC_ClocksStatus.PCLK1_Frequency*flagapb;
	TIM_TimeBaseStructure.TIM_Prescaler =(apbtmclk/hz-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
  }

	TIM_TimeBaseStructure.TIM_Period = cnt-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����							 
}
volatile unsigned long timer0_overflow_count=0;
uint32_t Flag1ms;
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	int flagerr;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 

	//GPIOC->ODR^=GPIO_Pin_13;//����õģ��Ժ�Ҫɾ��
			timer0_overflow_count++;
			
			Flag1ms++;


//				flagerr=handle1msprerx80();
//				if(flagerr==0)printf("A ");
//				else printf("%c ",flagerr+'A');	



			/*
			if(timer0_overflow_count>10000)
			{  
				// Jump to user application //
				JumpAddress = *(__IO uint32_t*) (USER_FLASH_STARTADDRESS + 4);
				Jump_To_Application = (pFunction) JumpAddress;
		      	// Initialize user application's Stack Pointer //
				__set_MSP(*(__IO uint32_t*) USER_FLASH_STARTADDRESS);
				Jump_To_Application();			

				
			}*/
		}
}


//����ǰһ������
//��������ֵ�仯�ǿ���ʱ��3��1ms�ж���������
unsigned long millis()
{
	return timer0_overflow_count ;

}


//����ǰһ������
//�������ֻ�п�����tim3�����ã������������������
void delay(unsigned long ms)
{
	unsigned long start = millis();
	
	while (millis() - start < ms);
}

unsigned char  Timer2_Init(u16 cnt,u32 hz)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_ClocksTypeDef RCC_ClocksStatus;
	uint32_t flagapb=1;
	uint32_t apbtmclk;
	
	uint32_t prescaler;
	uint32_t period;

  	RCC_GetClocksFreq(&RCC_ClocksStatus);

	while(1)
	{
		if(cnt==0)cnt=2;
		else if(cnt==1){cnt=10;hz=hz*10; }
		
		if(hz==0)hz=1;
		else if(hz>1000000)hz=1000000;
		
		if(RCC_ClocksStatus.SYSCLK_Frequency==16000000)//�ڲ�����
		{
			prescaler =(16000000/hz-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��   
		}
		else
		{
			if(RCC_ClocksStatus.PCLK1_Frequency==RCC_ClocksStatus.SYSCLK_Frequency);
			else flagapb=2;
			apbtmclk=RCC_ClocksStatus.PCLK1_Frequency*flagapb;
			prescaler =(apbtmclk/hz-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
		}
	
		period = cnt-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
		

		if(period>0xffff)return 1;
		else 
		{
			if(prescaler>0xffff)
			{
				hz=hz*10;
				cnt=cnt*10;
				if(hz>10000000)return 2;
			}
			else break;		
		}
		
	}

	TIM_TimeBaseStructure.TIM_Prescaler =prescaler;
	TIM_TimeBaseStructure.TIM_Period = period;


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����	
	return 0;						 
}

void TIM2_IRQHandler(void)   //TIM2�ж�
{
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		GPIO_ToggleBits(GPIOE, GPIO_Pin_1);
//			handle1msprerx80();
	}
}


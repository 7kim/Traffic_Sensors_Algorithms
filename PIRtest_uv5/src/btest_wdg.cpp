/*
����ǰ��ӵ�LED����,��ʽ��maple�Ľӽ���ʹ��setup()��loop()���������������������������ͷ�ļ�	#include "allboardinc.h"
���������¼��֣�    
#define BTESTWDG 0		 ���Ź�����
#define BTESTWDGNULL 100	 ��ѡ��
����ѡ���ĸ�����������setup()��loop()�����֣���ѡ��ѡ�ù������̾�û��������������Ҫ��֤��������������ֻ��һ��setup()��loop()

*/
#include "allboardinc.h"
#define BTESTWDG 0
#define BTESTWDGNULL 100

#define EXAMPLEWDG  BTESTWDGNULL

//LED
#if EXAMPLEWDG==	BTESTWDG
void setup()
{
	uint16_t i=0;	
	Utils.initLEDs();
	for(i=0;i<5;i++)
		Utils.blinkLEDs(100);
	delay_ms(2000);
    //stm32f4�Ŀ��Ź�Ƶ��Ϊ32KHZ������ѡ���Ԥ��Ƶ64 ��Ƶ��/64����˼ Ҳ����Ƶ�ʱ�Ϊ0.5KHZ����2����Ϊһ����׼��λ
	//��������Ƶ���£�����ѡ����װ��1000��Ҳ����2����Ҫιһ�ι�����ʱ�͵�Ƭ����λ
	IWDG_Init(IWDG_Prescaler_64,1000);//2sΪ����ʱ��
	IWDG_Feed();
	//��������ֱ�1.7�� 1.9�� 2.1�� ... ιһ�ι�����ִ����i=800, i=900 ֮��ִ��i=1000ʱ���ȵ�����1�룬Ȼ����һ�룬Ȼ������ʱ100���룬��Ȼ���ʱ�򳬹���ι����ʱ�䣬���Եĵ�Ƭ���Ḵλ
	//����������������ĵ�Ӧ���������Σ���Ƭ����λ�ˡ��������һ���ǵ����״̬û�����꣬��ʱ��λ�ˡ�
	for(i=800;i<2000;i=i+100)
	{
		Utils.setLED(1, 1);
		delay_ms(i);
		Utils.setLED(1, 0);
		delay_ms(i);
		delay_ms(100);
		IWDG_Feed();			
	}
//	while(1)
//	IWDG_Feed();
}

void loop()
{
	uint16_t i=0;	

	for(i=0;i<10;i++)
	{
		//three led light up
		Utils.setLED(0, 1);
		Utils.setLED(1, Utils.getLED(0));
		Utils.setLED(2, Utils.getLED(0));
		delay_ms(100);

		//three led cut down
		Utils.setLED(0, 0);
		Utils.setLED(1, Utils.getLED(0));
		Utils.setLED(2, Utils.getLED(0));
		delay_ms(500);
	}

	for(i=0;i<5;i++)
		Utils.blinkLEDs(1000);
	
}
#endif // end LED





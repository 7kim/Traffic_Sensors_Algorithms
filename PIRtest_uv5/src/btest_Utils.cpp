/*
����ǰ��ӵ�LED����,��ʽ��maple�Ľӽ���ʹ��setup()��loop()���������������������������ͷ�ļ�	#include "allboardinc.h"
���������¼��֣�    
#define BTESTUTILSLED 0		 LED����
#define BTESTUTILSNULL 100	 ��ѡ��Util����
����ѡ���ĸ�����������setup()��loop()�����֣���ѡ��ѡ�ù������̾�û��������������Ҫ��֤��������������ֻ��һ��setup()��loop()

*/
#include "allboardinc.h"
#define BTESTUTILSLED 0
#define BTESTUTILSNULL 100

#define EXAMPLEUTILS  BTESTUTILSNULL
//#define EXAMPLEUTILS  BTESTUTILSLED

//LED
#if EXAMPLEUTILS==	BTESTUTILSLED
void setup()
{
Utils.initLEDs();
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





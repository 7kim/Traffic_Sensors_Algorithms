/*
����ǰ��ӵ�LED����,��ʽ��maple�Ľӽ���ʹ��setup()��loop()���������������������������ͷ�ļ�	#include "allboardinc.h"
���������¼��֣�    
#define BTESTUTILSLED 0		 LED����
#define BTESTUTILSNULL 100	 ��ѡ��Util����
����ѡ���ĸ�����������setup()��loop()�����֣���ѡ��ѡ�ù������̾�û��������������Ҫ��֤��������������ֻ��һ��setup()��loop()

*/
#include "allboardinc.h"
#define BTESTPATTERNLIGHTS 0
#define BTESTPATTERNLIGHTSNULL 100

#define EXAMPLEPATTERNLIGHTS  BTESTPATTERNLIGHTSNULL


//LED
#if EXAMPLEPATTERNLIGHTS==	BTESTPATTERNLIGHTS
void setup()
{
Utils.initLEDs();
}

void loop()
{
	uint16_t i=0;	

	for(i=0;i<12;i++)
	{
		//three led light up
		Utils.setLED(0, 1);
		Utils.setLED(1, 1);
		Utils.setLED(2, 1);
		delay_ms(200);

		//three led cut down
		Utils.setLED(0, 0);
		Utils.setLED(1, 0);
		Utils.setLED(2, 0);
		delay_ms(2000);
	}

	for(i=0;i<10;i++)
	{
		Utils.blinkLEDs(200);
	}
	
	
		for(i=0;i<8;i++)
	{
		Utils.setLED(0,1);
		delay_ms(300);
		Utils.setLED(0,0);
		Utils.setLED(1,1);
		delay_ms(300);
		Utils.setLED(1,0);
		Utils.setLED(2,1);
		delay_ms(300);
		Utils.setLED(2,0);
		delay_ms(300);
		
		
	}
	
	
	delay_ms(1000);
	
}
#endif // end LED





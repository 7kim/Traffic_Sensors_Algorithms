/*
����ǰ��ӵ�LED����,��ʽ��maple�Ľӽ���ʹ��setup()��loop()���������������������������ͷ�ļ�	#include "allboardinc.h"
���������¼��֣�    
#define BTESTUTILSLED 0		 LED����
#define BTESTUTILSNULL 100	 ��ѡ��Util����
����ѡ���ĸ�����������setup()��loop()�����֣���ѡ��ѡ�ù������̾�û��������������Ҫ��֤��������������ֻ��һ��setup()��loop()

*/
#include "allboardinc.h"
#define BTESTUTILSLED1 0
#define BTESTUTILSNULL1 100

//#define EXAMPLEUTILS1  BTESTUTILSLED1
#define EXAMPLEUTILS1  BTESTUTILSNULL1

//LED
#if EXAMPLEUTILS1==	BTESTUTILSLED1
void setup()
{
	  Mux_poweron(); 
    beginSerial(9600, 1);	
Utils.initLEDs();
}

void loop()
{
	uint16_t i=0;	


	for(i=0;i<5;i++){
		Utils.blinkLEDs(1000);
	}
	
	printByte('a',1);
	
	delay_ms(1000);
	
}
#endif // end LED





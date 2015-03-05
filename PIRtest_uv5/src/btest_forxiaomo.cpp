/*
����ǰ��ӵ�I2C����,��ʽ��maple�Ľӽ���ʹ��setup()��loop()���������������������������ͷ�ļ�	#include "allboardinc.h"
���������¼��֣�   
#define BTESTEEPROM 0		 EEPROM	  ��д
#define BTESTI2CRTC 1		 �ⲿRTC ��ʱ�� дʱ�� ���¶�
#define BTESTMLX90614 2		 MLX90614 ���¶� �õ�SMBUSЭ�� //�˳�����ʺ������Ͼ�һ�����⴫���������
#define BTESTI2CNULL 100	 ��ѡ��I2C����
����ѡ���ĸ�����������setup()��loop()�����֣���ѡ��ѡ�ù������̾�û��������������Ҫ��֤��������������ֻ��һ��setup()��loop()

*/
#include "allboardinc.h"
#define BTESTXIAOMO 0

#define BTESTXIAOMONULL 100

#define EXAMPLEXIAOMO BTESTXIAOMONULL
/*
д���ݣ�������
дһ������Ȼ����������Բ���
*/
//EEPROM
#if EXAMPLEXIAOMO==BTESTXIAOMO
void setup()
{

	  Mux_poweron();
    monitor_onuart3TX();
	  beginSerial(115200, 3);
		
/*	
	monitor_offuart3TX();monitor_onuart3RX();//��USB���һ��xbee����	
	beginSerial(9600, 1); chooseuartinterrupt(1);
	printf("1");
	printf("2");	
*/
	
	
	//beginSerial(9600, 3);

	serialWrite('3', 3);//send a char '3' by uart3 //��ѯ��ʽ
	serialWrite('C', 3);//send a char 'c'
	delay_ms(1000);
	
	serialWritestr("\r\nHello world!\n", 15,3);	
	
	
	beginMb7076();
	
	SMBus_Init();
	SMBus_Apply();
	
}

char value_str[10];
char sl_add_char[20];
char temps[40];

void loop()
{
	int valuesonar;
	int flagsonar;	
	
	unsigned int slave_add;
	float tempobject;
	float tempambient;

	
	flagsonar=readMb7076(&valuesonar);
	
	sprintf(value_str,"Dist: %d",valuesonar);
	
	serialWritestr(value_str,10,3);	
	serialWrite('\n', 3);
	delay_ms(1000);
	
	slave_add= readMlx90614Subadd(); 
	sprintf(sl_add_char,"Slave address:%x",slave_add);
	serialWritestr(sl_add_char,20,3);	
	serialWrite('\n', 3);
	
	delay_ms(200);
	
	tempobject=readMlx90614ObjectTemp(slave_add);
	tempambient=readMlx90614AmbientTemp(slave_add);	
	sprintf(temps,"temp obj: %f'C, temp amb: %f'C",tempobject, tempambient);
	serialWritestr(temps,40,3);	
	serialWrite('\n', 3);

	
	
}
#endif //end EEPROM




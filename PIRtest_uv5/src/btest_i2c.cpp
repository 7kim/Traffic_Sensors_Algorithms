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
#define BTESTEEPROM 0
#define BTESTI2CRTC 1
#define BTESTMLX90614 2

#define BTESTI2CNULL 100

#define EXAMPLEI2C BTESTI2CNULL
/*
д���ݣ�������
дһ������Ȼ����������Բ���
*/
//EEPROM
#if EXAMPLEI2C==BTESTEEPROM
void setup()
{
	uint8_t str[30]={"I am a frog!"};
	int readdata;

	beginSerial(115200, PRINTFPORT);
  
	Eeprom.ON();	
	Eeprom.begin();	
	printf("test IIC\n");
	printf("Test client's function\n");
	printf("\n  Write a char 'A' to slaveadress=0xa0, address=0x0001 ");

	Eeprom.start();
	if(Eeprom.setSlaveAddress(0xa0)==I2CTRUE){
		if(Eeprom.writeEEPROM(0X0001,'A')==I2CTRUE){
			printf("write ok.");	
		}
		else{
			printf(" addWRONG");
			while(1);
		}		
	}
	else{
		printf("set slave WRONG");
		while(1);
	}

	printf("\n  Read a char from slaveadress=0xa0, address=0x0001 ");
	Eeprom.start();
	if(Eeprom.setSlaveAddress(0xa0)==I2CTRUE){
		readdata=  Eeprom.readEEPROM(0X0001);
		if(readdata!=I2CFALSE){
			printf("read ok,the data is %c \n",readdata);
			if(readdata!='A'){
				printf(" the data read from IIC not the data wroten in IIC");
				while(1);
			}	
		}
		else{
			printf("WRONG");
			while(1);
		}		
	}
	else{
		printf("WRONG");
		while(1);
	}

	printf("\n\nTest recommended function ");
	printf("\n  Wrtie the char 'B' to slaveadress=0xa0, address=0x0001");
	if(Eeprom.writeEEPROM(0xa0,0X0001,'B')==I2CTRUE){
		printf("write ok");	
	}
	else{
		printf("WRONG");
		while(1);		
	}

	printf("\n  Read a char from slaveadress=0xa0, address=0x0001 ");
	readdata=  Eeprom.readEEPROM(0xa0,0X0001);
	if(readdata!=I2CFALSE){
		printf("read ok,the data is %c \n",readdata);
		if(readdata!='B'){
			printf(" the data read from IIC not the data wroten in IIC");
			while(1);
		}	
	}
	else{
		printf("WRONG");
		while(1);
	}

	printf("\n  Write a string to slaveadress=0xa0, address=0x0001");
	printf("the string is <%s>",str);
	delay_ms(1000);	
	if(Eeprom.writeEEPROMStr(0xa0,0X0001,str,10)==I2CTRUE){
		printf(" write ok ");	
	}

	printf("\n  Read 10 datas from slaveadress=0xa0, address=0x0001 to the string 'str'");
	Eeprom.readEEPROMStr(0xa0,0X0001,str,10);
	printf(" printf the 10 datas:");
	uartsendstr((char *)str, 10,PRINTFPORT);
	delay_ms(1000);
}

void loop()
{
	while(1); 	
}
#endif //end EEPROM
/*
��дʱ�䣬���¶�
*/
//I2CRTC
#if EXAMPLEI2C==BTESTI2CRTC
void setup()
{
	uint16_t i;
	beginSerial(115200, PRINTFPORT); //����	 //��Ϊ������û���ֳɵĵ�Դ��������Ϊ�˷���鿴���ڵ����ݣ���RTC�ĵ�Դ�������ڵ�Դ�Ϳ�����
	printf("test RTC\n");

	printf("  Begin RTC...");
	RTCbianliang.ON();
	RTCbianliang.begin();
	printf("ok. NOTICE: We use the expression RTCbianliang.begin() and RTC init. \r\n");
	printf("The variable is RTCbianliang. \r\n");
	printf("We cant use the variable RTC as client offer, ");
	printf("because the 'RTC' is used as '#define RTC  ((RTC_TypeDef *) RTC_BASE)' in stm32f4xx.h at line 1148\r\n");

	printf("SetTime as Sun, 12/10/04 - 05:59:07 ,and after one second we read time\r\n");
	RTCbianliang.setTime("Sun, 12/10/04 - 05:59:07");
	delay_ms(1000);
	RTCbianliang.getTime();
	printf("%s",RTCbianliang.timeStamp);
	delay_ms(1000);
	printf("  After some seconds, we read time again.\r\n");
	delay_ms(2000);
	RTCbianliang.getTime();
	printf("  year=%d ",RTCbianliang.year) ;//����2��ӡ
	printf(" month=%d ",RTCbianliang.month);
	printf(" date=%d ",RTCbianliang.date) ;
	printf(" hour=%d ",RTCbianliang.hour);
	printf(" minute=%d ",RTCbianliang.minute) ;
	printf(" second=%d \r\n",RTCbianliang.second);

	printf("SetTime as Sun, 2011/12/31 - 23:59:56 ,and after one second we read time\r\n");
	RTCbianliang.setTime(11, 12, 31, 1, 23, 59, 56);
	delay_ms(1000);
	RTCbianliang.getTime();
	printf("%s",RTCbianliang.timeStamp);
	printf("  After some seconds, we read time again.\r\n");
	delay_ms(2000);
	RTCbianliang.getTime();
	printf("  %s\r\n",RTCbianliang.timeStamp);
	delay_ms(2000);
	RTCbianliang.getTime();
	printf("  %s\r\n",RTCbianliang.timeStamp);

	printf("  Read temperature and time about every 2 seconds(notice: )\r\n");
	for(i=1;i<=2070;i++)
	{
		printf("  temperature=%d `C ",RTCbianliang.getTemperature());
		delay_ms(1000);

		RTCbianliang.getTime();
		printf("  %s\r\n",RTCbianliang.timeStamp);
		delay_ms(1000);
	}
}

void loop()
{
	while(1); 	
}
#endif //endRTC

/*
�������¶�
*/
//mlx90614
#if EXAMPLEI2C==BTESTMLX90614  //�˳�����ʺ������Ͼ�һ�����⴫���������
void setup()
{
	long i;

	Mux_poweron(); //����һ����Դ���������õģ������ӡ����
	Utils.initLEDs();
	Utils.blinkLEDs(1000);
	delay_ms(1000);
	monitor_onuart3TX();  monitor_offuart3RX();
	beginSerial(115200, PRINTFPORT);//

	{
		printf("test mlx90614 temperature");
		printf("SMBus_Init");
		delay_ms(10);
	}
	SMBus_Init();//����������1.SMBUS�Ǳߵ�Դ�ϵ磬2��ʼ��I2C�������ڣ� ***ע��***�����I2C��RTC�Ĳ��ǹ��õ�
	printf(" enter the SMBus protocol.");	
	SMBus_Apply();//ʹ��MLX90614��MSBUS�Ĺ���

}

void loop()
{
//	while(1); 	
	unsigned int slave_add;
	float tempobject;
	float tempambient;
	uint8_t i;
	for(i=0;i<2;i++)
		Utils.blinkLEDs(500);

	printf("begin ");		     
	slave_add= readMlx90614Subadd();   //��ȡSMBUS��ַ 
	printf("slave_add %x ",slave_add);

	tempobject=readMlx90614ObjectTemp(slave_add);
	tempambient=readMlx90614AmbientTemp(slave_add);	

	printf("tempobject %f'C, tempambient %f'C \r\n",tempobject,tempambient);delay_ms(1000);	
}
#endif //mlx90614



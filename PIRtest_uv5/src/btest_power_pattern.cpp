/*
����ǰ��ӵĹ�������,��ʽ��maple�Ľӽ���ʹ��setup()��loop()���������������������������ͷ�ļ�	#include "allboardinc.h"
���������¼��֣�
#define BTESTPWR168SIMPLE 0	 �򵥵Ĺ��Ĳ���.��168M��Ƶ�´�RTC��I2C����SD��������2����ع���оƬ�����Ե�����ѹ����¼��SD�����棬��������򵥵Ĳ��Թ�����
#define BTESTPWR168SLEEP 1	 168M��Ƶ����˯�� ������
#define BTESTPWR168STOP 2	 168M��Ƶ����STOP ������
#define BTESTPWR168STANDBY 3 168M��Ƶ����STANDBY ������ //����ģʽ��ȥ�ͻ������� �����ճ���Ҳ�ղ���ȥ��  ���һ�����������ģʽ��������д���������boot0=1����JLINK��д���� 
#define BTESTPWRNULL 100     ��ѡ�ù�������

����ѡ���ĸ�����������setup()��loop()�����֣���ѡ��ѡ�ù������̾�û��������������Ҫ��֤��������������ֻ��һ��setup()��loop()


*/
#include "allboardinc.h"
#define BTESTPWR168SIMPLE 0	  //��RTC��I2C������ع���оƬ������1�����Ե�����ѹ����ӡ����
#define BTESTPWRNULL 100
#define EXAMPLEPWR BTESTPWRNULL 


//#define EXAMPLEPWR BTESTPWR168SIMPLE//

//PWR168SIMPLE
#if EXAMPLEPWR==BTESTPWR168SIMPLE
//static uint8_t AddSDstr[512];

//����ͷҪ��ӡһ��Ƶ��
void setup()
{
	

	
	Utils.initLEDs();
	Utils.setLED(0, 1);
	Utils.setLED(1, Utils.getLED(0));
	Utils.setLED(2, Utils.getLED(0));
	delay_ms(100);

	//three led cut down
	Utils.setLED(0, 0);
	Utils.setLED(1, Utils.getLED(0));
	Utils.setLED(2, Utils.getLED(0));
	delay_ms(500);


	PWR2745.initPower(PWR_BAT|PWR_RTC);//�����������������������ݲ��ܶԣ��������ΪRTC�Ͷ�������ѹоƬ����I2C,Ҫ��ֻ��һ�������ݾͻ�������
	PWR2745.switchesON(PWR_BAT|PWR_RTC);
	
	Mux_poweron(); //����һ����Դ���������õģ������ӡ����	
	monitor_onuart3TX();  monitor_offuart3RX();
	beginSerial(115200, PRINTFPORT); //����
	printf ("\r\n\r\n                  Designed by ZHP,    Built: %s %s ", __DATE__, __TIME__);
	printf("\r\nfile: %s ,",__FILE__); 
	printf("\r\nfunction: %s ,",__func__); 
	printf("\r\nline: %d\r\n",__LINE__); 	

	PWR2745.initBattery();//��ʼ����������ѹ�¶��Ǹ���ʵ�����õ���I2C��Э��	
	PWR2745.initPower(PWR_XBEE|PWR_SD|PWR_SENS_3V3|PWR_SENS1_5V|PWR_SENS2_5V|PWR_SENS3_5V|PWR_MUX_UART6);//��ʼ����ЩGPIO��Ϊ�˲⿪��Щ�ںͲ�����Щ�ڵĵ������
	
	printf("\r\n SD poweron. \r\n");		 
 	SD.ON();//intilise SD 

	printf("SD init. \r\n");    
	SD.init();
	
		if(SD.isFile("Power.txt")==1)
	{
		printf(" Power.txt yes. ");
	}
	else
	{
		printf("  There is no folder dir0, now create the folder. ");
		if(SD.create("Power.txt"))
		{
			printf(" success ");
		}
		else
		{
			printf(" failed  ");
		}
	}			
	
}

uint8_t StrFileName[20]="Power.txt";// Define your txt file name, here it is GPS
static uint8_t  StrWriteSDPower[200];// Define a string to be writen into the SD
static long  OffsetWriteSDPower=0;  //Define the offset length of the current writing 
static long  LenWriteSDPower=0;  //length of the string to be written 
static uint8_t  StrWriteSD[200];
static long  OffsetWriteSD=0;
static long  LenWriteSD=0;
//uint8_t StrFileName[20]="test.txt";//���ֻ�����ʱ��ĵ�


void loop()
{
	int16_t temp_voltage;
	int16_t temp_current;
	int16_t temp_temp;

	PWR2745.switchesOFF(PWR_XBEE|PWR_SENS_3V3|PWR_SENS1_5V|PWR_SENS2_5V|PWR_SENS3_5V|PWR_MUX_UART6); delay_ms(3000);//��Ϊ��·�Ǳߴ�ŵĵ��ݵ����⣬�����ø��õ׳�һ��ʱ�䣬������ĵ�������űȽϴ�	

	delay_ms(100);	
	temp_voltage=PWR2745.getBatteryVolts();
	printf("\r\n");
	printf("Voltage=%dmv  ",temp_voltage);
	delay_ms(100);

	temp_temp=PWR2745.getBatterytemperature();
	printf("    temperature=%d'c  " ,temp_temp);
	delay_ms(100);

	temp_current=PWR2745.getBatteryCurrent();
	printf("Current=%dma  ",temp_current);
	delay_ms(100);

sprintf((char *)StrWriteSD,"\r\n Voltage=%d  Temperature=%d  Current=%d",temp_voltage, temp_temp, temp_current);
			
		OffsetWriteSD=SD.getFileSize((const char *)StrFileName);
		LenWriteSD= strlen((const char *)StrWriteSD);
		SD.writeSD((const char *)StrFileName,StrWriteSD, OffsetWriteSD);
		OffsetWriteSD += LenWriteSD;
		if(OffsetWriteSD>0xfffffff)OffsetWriteSD=0;
		
		
	

	PWR2745.switchesON(PWR_XBEE|PWR_SENS_3V3|PWR_SENS1_5V|PWR_SENS2_5V|PWR_SENS3_5V|PWR_MUX_UART6); delay_ms(5000);	

	delay_ms(100);	
	temp_voltage=PWR2745.getBatteryVolts();
	printf("\r\n");
	printf("    Voltage=%dmv  ",temp_voltage);
	delay_ms(100);

	temp_temp=PWR2745.getBatterytemperature();
	printf("temperature=%d'c  " ,temp_temp);
	delay_ms(100);

	temp_current=PWR2745.getBatteryCurrent();
	printf("Current=%dma  ",temp_current);
	delay_ms(500);
}
#endif // end PWR168SIMPLE


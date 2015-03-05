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
#define BTESTPWR168SLEEP 1	  //__WFI();
#define BTESTPWR168STOP 2
#define BTESTPWR168STANDBY 3//����ģʽ��ȥ�ͻ������� �����ճ���Ҳ�ղ���ȥ��  ��������Ƭ��û��ʲô����	 


#define BTESTPWRCHANGECLK 4	 //����Ƶ�����
#define BTESTPWRNULL 100

#define EXAMPLEPWR BTESTPWRNULL//

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
}

void loop()
{
	int16_t tempb;

	PWR2745.switchesOFF(PWR_XBEE|PWR_SD|PWR_SENS_3V3|PWR_SENS1_5V|PWR_SENS2_5V|PWR_SENS3_5V|PWR_MUX_UART6); delay_ms(3000);//��Ϊ��·�Ǳߴ�ŵĵ��ݵ����⣬�����ø��õ׳�һ��ʱ�䣬������ĵ�������űȽϴ�	

	delay_ms(100);	
	tempb=PWR2745.getBatteryVolts();
	printf("\r\n");
	printf("Voltage=%dmv  ",tempb);
	delay_ms(100);

	tempb=PWR2745.getBatterytemperature();
	printf("    temperature=%d'c  " ,tempb);
	delay_ms(100);

	tempb=PWR2745.getBatteryCurrent();
	printf("Current=%dma  ",tempb);
	delay_ms(500);

	PWR2745.switchesON(PWR_XBEE|PWR_SD|PWR_SENS_3V3|PWR_SENS1_5V|PWR_SENS2_5V|PWR_SENS3_5V|PWR_MUX_UART6); delay_ms(5000);	

	delay_ms(100);	
	tempb=PWR2745.getBatteryVolts();
	printf("\r\n");
	printf("    Voltage=%dmv  ",tempb);
	delay_ms(100);

	tempb=PWR2745.getBatterytemperature();
	printf("temperature=%d'c  " ,tempb);
	delay_ms(100);

	tempb=PWR2745.getBatteryCurrent();
	printf("Current=%dma  ",tempb);
	delay_ms(500);
}
#endif // end PWR168SIMPLE


/*
˯��ģʽ
    ���룺����__WFI(); �о�����������Ǳ���ͣ��
	���ѣ���һһ���жϣ�����������涨����һ���ⲿ�жϣ�PA0�ڣ�,������������˴���PRINTFPORT����ʼ�����������˴��˽����ж�
	һ�������жϣ�����ͻ��ѡ��о����ǳ�������ͣ���Ǹ��ط�����ִ���ˡ�
	
	****** ע�� ******
	*��Ϊ�����ж϶����Ի��ѣ����Լ��翪���˶�ʱ�������翪xbee��ʱ��ͻ�˳���Ѷ�ʱ��3�������Ǹ���1msһ���жϵģ� ����˯�� 1ms������ ���˸о�����Ϊ��û��˯����*
	*******************
*/
//������̸�������ͨ����wakeup�������� ����ͨ������Ǳߵ�PC1�����ػ���
//������ 1������sleep�󣬰�wakeup���� , 2) ����sleep�󣬶�·R40���ﵽģ���ظ�λ��Ȼ����ܻ��ѵ�Ƭ����
//�� GPIO_def();exti_def();NIVC_def();���滹�й���RTC���ӵĻ��ѣ����������е㷱������س���Ͳ�д�������ˣ��� btestdata0902.cpp�������������
#if EXAMPLEPWR==BTESTPWR168SLEEP
void setup()
{
	Utils.initLEDs();
	Utils.setLED(0, 1);
	Utils.setLED(1, Utils.getLED(0));
	Utils.setLED(2, Utils.getLED(0));
	delay_ms(100);

	PWR2745.initPower(PWR_BAT);//���뿪�����ص�Դ��Ҫ��ȻPC1�������ص����Ƚ�2.8V�ģ���������
	PWR2745.switchesON(PWR_BAT);
	Mux_poweron(); //����һ����Դ���������õģ������ӡ����	
	beginSerial(115200, PRINTFPORT); //����
	GPIO_def();//PA0
	exti_def();//PA0
	NIVC_def();//PA0
	
	//three led cut down
	Utils.setLED(0, 0);
	Utils.setLED(1, Utils.getLED(0));
	Utils.setLED(2, Utils.getLED(0));
	delay_ms(500);	
	while(1)
	{
	printf("cnt=%d ",CNTEXIT);
	Utils.blinkLEDs(500);
	CNTEXIT++;

	printf("cnt=%d ",CNTEXIT);
	Utils.blinkLEDs(500);
	CNTEXIT++;
	if(CNTEXIT>=20)break;

	}

	//enter sleep mode, if any interrupt(such as key PA0 put down ,or uart PRINTFPORT receive datas ) hanppen, MCU can wake
    __WFI();//����˯�ߣ��������κ��ж϶����Ի�������������жϱ����ⲿ�жϣ����ڽ��գ������жϿ��Ļ�������ʱ��
	//������wakeup�Ϳ��Ի��ѵ�Ƭ��
	//
	//
	printf("I am back! hello\n");

	while(1)
	{
		printf("cnt=%d ",CNTEXIT);
		Utils.blinkLEDs(1000);
		CNTEXIT++;
		if(CNTEXIT>=2000)CNTEXIT=0;
		if(CNTEXIT==40)
		{
			__WFI();		   	
		}
	}
}

void loop()
{
	while(1);
}
#endif // end BTESTPWR168SLEEP

/*
STOPģʽ
    ���룺����PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI); �о�����������Ǳ���ͣ��
	���ѣ���һһ���ⲿ�жϣ�����������涨����һ���ⲿ�жϣ�PA0�ڣ�,�����ﴮ�ڽ��ղ���
	һ�������жϣ�����ͻ��ѡ��о����ǳ�������ͣ���Ǹ��ط�����ִ���ˣ����Ǵ�ʱϵͳʱ�ӻָ������ڲ�ʱ�ӣ�����Ҫϵͳʱ�ӳ�ʼ��һ��
*/
#if EXAMPLEPWR==BTESTPWR168STOP
void setup()
{
	beginSerial(9600, PRINTFPORT); //����
	GPIO_def();//PA0
	exti_def();//PA0
	NIVC_def();//PA0
	while(1)
	{
	printf("cnt=%d ",CNTEXIT);
	Utils.blinkLEDs(500);
	CNTEXIT++;

	printf("cnt=%d ",CNTEXIT);
	Utils.blinkLEDs(500);
	CNTEXIT++;
	if(CNTEXIT>=20)break;
	}

	printf("%x ",*(__IO uint32_t *)(0xe000ed10));
	printf("%x ",*(__IO uint32_t *)(0x40007004));

//	*(__IO uint32_t *)(0xe000ed10) |=0x02;
//	*(__IO uint32_t *)(0x40007004) |=0x100;

	printf("now=%x ",*(__IO uint32_t *)(0xe000ed10));
	printf("sec=%x ",*(__IO uint32_t *)(0xe000ed10));
	printf("third=%x ",*(__IO uint32_t *)(0xe000ed10));
	printf("%x ",*(__IO uint32_t *)(0xe000ed10));
	printf("%x ",*(__IO uint32_t *)(0x40007004));

	//enter sleep mode, if any ex interrupt(such as key PA0 put down ,but not uart PRINTFPORT receive datas ) hanppen, MCU can wake	
	PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
    //when MCU wake, it sysclk is internal clk. so we must reuse SystemInit();	
	SystemInit();
	printf("I am back!mei hei\n");

	while(1)
	{
		printf("cnt=%d ",CNTEXIT);
		Utils.blinkLEDs(1000);
		CNTEXIT++;
		if(CNTEXIT>=2000)CNTEXIT=0;
		if(CNTEXIT==40)
		{
			PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
		    SystemInit();
			printf("I am back!mei hei\n");		   	
		}
	}
}

void loop()
{
	while(1);
}
#endif // end BTESTPWR168STOP

/*
STANDBYģʽ
    ���룺����PWR_EnterSTANDBYMode(); Ŀǰ�о��������������
	���ѣ��̶��ļ�������
	��Ϊ����û��ʹ���Ǽ����̶��Ļ��ѣ��������ڻ����ѣ�����������д����Ҳд���ˣ���ʱҪ��д���԰� boot0=1��д.
	
	ע�⣺��ģʽ�¼Ĵ���ʲô�Ķ��ص��ˣ��������Щ����Ҳ���ܱ��棬���Բ�����ͻ�ʹ�ô�ģʽ

*/
#if EXAMPLEPWR==BTESTPWR168STANDBY
void setup()
{
	beginSerial(9600, PRINTFPORT); //����
	GPIO_def();//PA0
	exti_def();//PA0
	NIVC_def();//PA0
	while(1)
	{
	printf("cnt=%d ",CNTEXIT);
	Utils.blinkLEDs(500);
	CNTEXIT++;

	printf("cnt=%d ",CNTEXIT);
	Utils.blinkLEDs(200);
	CNTEXIT++;
	if(CNTEXIT>=20)break;
	}

	printf("%x ",*(__IO uint32_t *)(0xe000ed10));
	printf("%x ",*(__IO uint32_t *)(0x40007004));

//	*(__IO uint32_t *)(0xe000ed10) |=0x02;
//	*(__IO uint32_t *)(0x40007004) |=0x100;

	printf("now=%x ",*(__IO uint32_t *)(0xe000ed10));
	printf("sec=%x ",*(__IO uint32_t *)(0xe000ed10));
	printf("third=%x ",*(__IO uint32_t *)(0xe000ed10));
	printf("%x ",*(__IO uint32_t *)(0xe000ed10));
	printf("%x ",*(__IO uint32_t *)(0x40007004));


	PWR_EnterSTANDBYMode();
	//enter sleep mode, if any ex interrupt(such as key PA0 put down ,but not uart PRINTFPORT receive datas ) hanppen, MCU can wake	
    //when MCU wake, it sysclk is internal clk. so we must reuse SystemInit();	
	SystemInit();
	printf("I am back!mei hei\n");

	while(1)
	{
		printf("cnt=%d ",CNTEXIT);
		Utils.blinkLEDs(1000);
		CNTEXIT++;
		if(CNTEXIT>=2000)CNTEXIT=0;
		if(CNTEXIT==40)
		{
			PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
		    SystemInit();
			printf("I am back!mei hei\n");		   	
		}
	}
}

void loop()
{
	while(1);
}
#endif // end BTESTPWR168STANDBY





//BTESTPWRCHANGECLK
#if EXAMPLEPWR==BTESTPWRCHANGECLK


//����ͷҪ��ӡһ��Ƶ��

void setup()
{
	unsigned long testsys=168000000;
	int16_t tempb;	
	RCC_ClocksTypeDef RCC_ClocksStatus;
	
	while(1)
	{
		zppSystemInit();
		Mux_poweron(); //����һ����Դ���������õģ������ӡ����
			delay_ms(10);	
		beginSerial(115200, PRINTFPORT); //����	
		RCC_GetClocksFreq(&RCC_ClocksStatus);
		printf("\r\n\r\nsys=%d,hclk=%d,pclk1=%d,pclk2=%d"\
		,RCC_ClocksStatus.SYSCLK_Frequency,RCC_ClocksStatus.HCLK_Frequency\
		,RCC_ClocksStatus.PCLK1_Frequency,RCC_ClocksStatus.PCLK2_Frequency);
		delay_ms(10);	
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
		PWR2745.switchesON(PWR_BAT|PWR_RTC);//�����������ص����Ĳ��������� 
		PWR2745.initBattery();//��ʼ����������ѹ�¶��Ǹ���ʵ�����õ���I2C��Э��		
		PWR2745.initPower(PWR_XBEE|PWR_SD|PWR_SENS_3V3|PWR_SENS1_5V|PWR_SENS2_5V|PWR_SENS3_5V|PWR_MUX_UART6);//��ʼ����ЩGPIO��Ϊ�˲⿪��Щ�ںͲ�����Щ�ڵĵ������	
	
	
		RTCbianliang.ON(); delay_ms(10);   //��Ϊ�����Ѿ�����RTC��Դ�ˣ�����������ǿ���ʡ����
		RTCbianliang.begin();delay_ms(10); //��Ϊ�����Ѿ�����I2C��ʼ���ˣ�����������ǿ���ʡ����

		RTCbianliang.getTime();
		printf("\r\n  %s",RTCbianliang.timeStamp);
		delay_ms(20);

		PWR2745.switchesOFF(PWR_XBEE|PWR_SD|PWR_SENS_3V3|PWR_SENS1_5V|PWR_SENS2_5V|PWR_SENS3_5V|PWR_MUX_UART6); delay_ms(5000);//��Ϊ��·�Ǳߴ�ŵĵ��ݵ����⣬�����ø��õ׳�һ��ʱ�䣬������ĵ�������űȽϴ�	
	
		delay_ms(100);	
		tempb=PWR2745.getBatteryVolts();
		printf("\r\n");
		printf("  Voltage=%dmv  ",tempb);
		delay_ms(100);
	
		tempb=PWR2745.getBatterytemperature();
		printf("    temperature=%d'c  " ,tempb);
		delay_ms(100);
	
		tempb=PWR2745.getBatteryCurrent();
		printf("Current=%dma  ",tempb);
		delay_ms(500);
	
		PWR2745.switchesON(PWR_XBEE|PWR_SD|PWR_SENS_3V3|PWR_SENS1_5V|PWR_SENS2_5V|PWR_SENS3_5V|PWR_MUX_UART6); delay_ms(5000);	
	
		delay_ms(100);	
		tempb=PWR2745.getBatteryVolts();
		printf("\r\n");
		printf("      Voltage %dmv  ",tempb);
		delay_ms(100);
	
		tempb=PWR2745.getBatterytemperature();
		printf("temperature %d'c  " ,tempb);
		delay_ms(100);
	
		tempb=PWR2745.getBatteryCurrent();
		printf("Current %dma  ",tempb);
		delay_ms(500);


			testsys=testsys-12000000;
			if(testsys<24000000)
			{
				testsys=168000000;
			}
		//�����ڵĲ���Ƶ�ʸ�����Ƶ���ȫ�ֱ������������ʱ��û�б�Ƶ��
		SysClkWasp=testsys;
		//��Щ����׼������������ĵ�PLLM PLLN ��Щ
		SysPreparePara();
	}

}

void loop()
{
while(1);
}
#endif // end BTESTPWRCHANGECLK




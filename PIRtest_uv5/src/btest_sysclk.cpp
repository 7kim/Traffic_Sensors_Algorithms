/*
����ǰ��ӵĻ���Ƶ����,��ʽ��maple�Ľӽ���ʹ��setup()��loop()���������������������������ͷ�ļ�	#include "allboardinc.h"
���������¼��֣�    
#define BTESTSYSCLKWHILECHG 0 //��Ƶ��ͣ�仯�����٣���ÿ�β�1M������8M��ѭ����168M
#define BTESTSYSCLKNULL 100	 ��ѡ�û���Ƶ����
����ѡ���ĸ�����������setup()��loop()�����֣���ѡ��ѡ�ù������̾�û��������������Ҫ��֤��������������ֻ��һ��setup()��loop()

*/

#include "allboardinc.h"
#define BTESTSYSCLKWHILECHG 0 //��Ƶ��ͣ�仯�����٣���ÿ�β�1M������8M��ѭ����168M
#define BTESTSYSCLKNULL 100

#define EXAMPLESYSCLK BTESTSYSCLKNULL 

#if EXAMPLESYSCLK==BTESTSYSCLKWHILECHG
//������ʱ
static void ZPPDelay(u32 count)
{
	while(count--);
}

//����Ǳ����ļ���������
//static 
struct structfiletime
{
	uint8_t year;
	uint8_t month;
	uint8_t date;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
};
//����Ǳ����ļ�ʱ���������
static union unionfiletime
{
	struct structfiletime unstrft;
	uint8_t stringfiletime[sizeof(struct structfiletime)/sizeof(uint8_t)];
}unfltm;	// 

//�������� __DATE__,__TIME__,��
//��ݺ���ǰ�����λ������2013ֻ����13
static void getcomplietime(char * strdate,char * strtime)
{
	char *pstr;
	unsigned shi,fen,miao;
	pstr=strdate;
	pstr[3]=0x00;
	if(strncmp(pstr,"Jan",3)==0){unfltm.unstrft.month=1;}
	else if(strncmp(pstr,"Feb",3)==0){unfltm.unstrft.month=2;}
	else if(strncmp(pstr,"Mar",3)==0){unfltm.unstrft.month=3;}
	else if(strncmp(pstr,"Apr",3)==0){unfltm.unstrft.month=4;}
	else if(strncmp(pstr,"May",3)==0){unfltm.unstrft.month=5;}
	else if(strncmp(pstr,"Jun",3)==0){unfltm.unstrft.month=6;}
	else if(strncmp(pstr,"Jul",3)==0){unfltm.unstrft.month=7;}
	else if(strncmp(pstr,"Aug",3)==0){unfltm.unstrft.month=8;}
	else if(strncmp(pstr,"Sep",3)==0){unfltm.unstrft.month=9;}
	else if(strncmp(pstr,"Oct",3)==0){unfltm.unstrft.month=10;}
	else if(strncmp(pstr,"Nov",3)==0){unfltm.unstrft.month=11;}
	else {unfltm.unstrft.month=12;}

	pstr=strdate+4;
	pstr[2]=0x00;
	unfltm.unstrft.date=(uint8_t) atoi(pstr);

	pstr=strdate+9;
	pstr[2]=0x00;
	unfltm.unstrft.year=(uint8_t) atoi(pstr);

	sscanf(strtime,\
	"%d:%d:%d",\
	&shi,&fen,&miao);

	unfltm.unstrft.hour=(uint8_t)shi;
	unfltm.unstrft.minute=(uint8_t)fen;
	unfltm.unstrft.second=(uint8_t)miao;
}

/*
�鿴RTCʱ���Ƿ���Ҫ��д
����ֵ0������Ҫ��д  	  ����ֵ1����Ҫ��д  
�ó�������ʱ���ʱ���RTCʱ��Ƚ�һ�£����RTCʱ������С�ڱ���ʱ�䣬˵��RTCʱ��϶������⣬��Ҫ��д��
���RTCʱ����ڱ���ʱ�䣬����Ͳ��ܿ϶��ˣ���ʱ���ز���Ҫ��д
*/
static uint8_t ischangertc(void)
{
 //	uint8_t flagchangertc=0;//0����дRTC 1��дRTC
	uint32_t day32file;	
	uint32_t day32rtc;
	uint32_t minute32file;
	uint32_t minute32rtc;

	day32file = unfltm.unstrft.year*10000 +  unfltm.unstrft.month * 100 + unfltm.unstrft.date; 
	day32rtc  =	RTCbianliang.year*10000 + RTCbianliang.month*100 + RTCbianliang.date;

	if(day32rtc>day32file)return 0;//
	else if(day32rtc<day32file)return 1;
	else{
		minute32file = 	unfltm.unstrft.hour*60 +  unfltm.unstrft.minute ;
		minute32rtc  =	RTCbianliang.hour*60 + RTCbianliang.minute;

		if(minute32rtc>minute32file)return 0;
		else if((minute32file-minute32rtc)>20){
			return 1;
		}
		else return 0;
	}
//	return 0;
}

//static uint8_t ReadBuffer[512];


/*
��ͣ����Ƶ���ԡ�
    �����ڣ�I2C��SPI��SD���Ƿ����������У���������ʱ������ݼ�¼��SD������

	����setup()������Ƶ168M�����ƣ���ʱ�������ڣ��õ�RTCֵ���Ҵ�ӡ����ʱ�䣬RTCʱ�䣬��RTC�Ƿ�Ҫ��д
	Ȼ����loop()���治ͣ�ļ�����Ƶֵ�����LED��GPIO�ڣ�����ʱ����ϵͳʱ�ӵ���ʱ��delay_ms�������ڣ�I2C��SPI��SD���������������������SD���¼�¼��Ƶ��RTCʱ��
*/

static	unsigned long testsys=168000000;
static	unsigned char flagfangxiang=0;

static	unsigned long zppSysClkWasp;
static  unsigned long zppDelayMsWasp;
static	unsigned long zppDelayUsWasp;
static	unsigned long zppSysPllN,zppSysPllM,zppSysPllP,zppSysPllQ;
static	unsigned long zppSysFlashWait;

static uint8_t AddSDstr[512];//��Ҫ�����뵽SD�����������
//��Ƶ168M�����ƣ���ʱ�������ڣ��õ�RTCֵ���Ҵ�ӡ����ʱ�䣬RTCʱ�䣬��RTC�Ƿ�Ҫ��д
void setup()
{
	zppSystemInit();
	
	Utils.initLEDs();//���õ�֮ǰ�����ʼ��һ��
	for(int i=0;i<5;i++)
		Utils.blinkLEDs(1000);
				
	Timer3_Init(10,10000);
	Mux_poweron(); //����һ����Դ���������õģ������ӡ����
	beginSerial(115200, PRINTFPORT); //������������ô�����������
	printf ("\n\n                  Designed by ZHP,    Built: %s %s ", __DATE__, __TIME__);
	getcomplietime(__DATE__,__TIME__);
	printf(" strtime=%d %d %d  %d %d %d "\
	,unfltm.unstrft.year,unfltm.unstrft.month,unfltm.unstrft.date\
	,unfltm.unstrft.hour,unfltm.unstrft.minute,unfltm.unstrft.second);

	printf("\nfile: %s ,",__FILE__); 
	printf("\nfunction: %s ,",__func__); 
	printf("\nline: %d\n",__LINE__); 


	RTCbianliang.ON();
	RTCbianliang.begin();
	RTCbianliang.getTime();uartsendstr((char *)RTCbianliang.timeStamp, 30,PRINTFPORT);delay_ms(1000);
	if(ischangertc()==1){
				printf(" differnt time ");
				RTCbianliang.setTime(unfltm.unstrft.year, unfltm.unstrft.month, unfltm.unstrft.date, 1\
				, unfltm.unstrft.hour, unfltm.unstrft.minute, unfltm.unstrft.second);
	}
}
//loop()���治ͣ�ļ�����Ƶֵ�����LED��GPIO�ڣ�����ʱ����ϵͳʱ�ӵ���ʱ��delay_ms�������ڣ�I2C��SPI��SD���������������������SD���¼�¼��Ƶ��RTCʱ��
void loop()
{
	unsigned int i;
	unsigned int cishu=0;
	RCC_ClocksTypeDef RCC_ClocksStatus;
	char filenameorig[20];
	uint8_t eepromdata[30]={"this is test of ic"};
	int32_t filesize=-2;
	uint64_t fsize;

	testsys=168000000;
	for(cishu=0;cishu<1000;cishu++)
	{
		//�����Լ�����ϵͳ��ʼ�������Ƶ����ȫ�ֱ���SysClkWasp����ʼĬ��Ϊ168M
		zppSystemInit();	
		Mux_poweron(); //����һ����Դ���������õģ������ӡ����		
		
		//��ʱ��3��ʼ��������ϵͳʱ����ʲô�����ﶼ����1msһ���жϵ�,��ô������㣬���鿴���涨��
		Timer3_Init(10,10000);
		//����˸���£������漰��ʱ������ϵͳ��ા����ģ�����Ƶ�ʶ��٣������ms us�����Զ������ģ������ms us���涨��
		for(i=0;i<5;i++)Utils.blinkLEDs(100);
		//��ʼ���ڣ�����Ĳ�����Ҳ�Ǹ���ϵͳʱ�ӵ�������ģ���������涨��
		beginSerial(115200, PRINTFPORT);
		//����������򵥵���ʱ������Ϊ����ʱ������ϵͳ����Ǹ���ʱû����õĻ��������ʱ�����򵥲ο�		
		ZPPDelay(0x3456);
		printf(" cishu=%d ",cishu);ZPPDelay(0x34567);
		//�õ���ǰ��ϵͳʱ�ӵ�һЩ���ã��Ҵ�ӡ����
		RCC_GetClocksFreq(&RCC_ClocksStatus);
		printf("sys=%d,hclk=%d,pclk1=%d,pclk2=%d"\
		,RCC_ClocksStatus.SYSCLK_Frequency,RCC_ClocksStatus.HCLK_Frequency\
		,RCC_ClocksStatus.PCLK1_Frequency,RCC_ClocksStatus.PCLK2_Frequency);
		delay_ms(1000);


		


		for(i=0;i<5;i++)
		{		
		  Utils.setLED(0, 1);
		  //û�п���ʱ��	Timer3_Init(10,10000); ������delay(40);����������������ֻ������ֲxbee��ʱ�������������������ΪоƬ��һ����Ϊ�������ʱ�ﵽԭ���������صؿ��˶�ʱ��������
		  //�����ڿ�xbee��ʱ���Զ��Ѷ�ʱ��3Ҳ���ˣ����Լ���������濪��xbee �Ͳ��õ����ڳ�ʼ��һ�¶�ʱ��3��
		  delay(40); 		  printf("i=%d ",i);
		  Utils.setLED(1, 1); 	
		  delay(40); 
		  printf("i=%d ",i);
		}
		for(i=0;i<5;i++)
		{
		  Utils.setLED(0, 1);
		  delay_ms(20); 
		  printf("I=%d ",i);
		  Utils.setLED(1, 1);	
		  delay_ms(20); 
		  printf("I=%d ",i);
		}


		//������λ�Ƶ�ʵĳ��������£��ǿ��Եģ���Ϊflash�����߳�����̫�࣬���԰����������
		printf("\r\nspi init");
		Flash.SPI_Flash_Init();
		uint16_t tmpreg = SPI2->CR1;
		uint16_t spibaudrate = (tmpreg>>3)&0x07;
		uint32_t spifclk =	(RCC_ClocksStatus.PCLK1_Frequency >> (spibaudrate+1));
		printf(" spifclk=%d ",spifclk);

//		int readch=0;
//		while(1){
//			readch=0;
//			for(long i100=0;i100<0xf;i100++){
//				readch=Flash.flashreaddata4add(4092);
//				}
//			printf(" 5result of read =%x ",readch);
//
//
//			readch=0;
//			for(long i100=0;i100<0xffff;i100++){
//				readch=Flash.flashreaddata4add(4092);
//				}
//			printf(" 6result of read =%x ",readch);
//
//			readch=0;
//			for(long i100=0;i100<0xf;i100++){
//				readch=Flash.flashreaddata4add(4092);
//				}
//			printf(" 7result of read =%x ",readch);
//
//		}
		 
//		//�ڵ�ַ4092�Ǳ�д���ַ�'4'(0x34)
//		readch=Flash.writeFlash(4092,(uint8_t)'4');
//		if(readch==FLASHSECTOEWRITEOK)//���д�ɹ���
//		{
//			readch=Flash.flashreaddata4add(4092);
//			printf(" result of read =%x ",readch);
//			if(readch!='4')while(1); 
//		}										 
//		else
//		{
//			printf(" the type of writeerr =%d ",readch);
//			while(1);
//		}
//
//		//�ڵ�ַ4092�Ǳ�д���ַ�'4'(0x34)
//		readch=Flash.writeFlash(4092,(uint8_t)'3');
//		if(readch==FLASHSECTOEWRITEOK)//���д�ɹ���
//		{
//			readch=Flash.flashreaddata4add(4092);
//			printf(" result of read =%x ",readch);
//			if(readch!='3')while(1); 
//		}										 
//		else
//		{
//			printf(" the type of writeerr =%d ",readch);
//			while(1);
//		}


		Eeprom.ON();

		Eeprom.begin();

		printf(" eeprom:");delay_ms(500);
		eepromdata[0]='t';
		if(Eeprom.writeEEPROM(0xa0,0X0001,eepromdata,30)==I2CTRUE){printf("write ok ");	}
		else{printf("fail write");}
		
		Eeprom.readEEPROM(0xa0,0X0001,eepromdata,30);
		uartsendstr((char *)eepromdata, 30,PRINTFPORT);delay_ms(500);
	
		eepromdata[0]='u';
		Eeprom.writeEEPROM(0xa0,0X0001,eepromdata,30);
	
		eepromdata[0]=0;
		Eeprom.readEEPROM(0xa0,0X0001,eepromdata,30);
		uartsendstr((char *)eepromdata, 30,PRINTFPORT);delay_ms(500);
		if(eepromdata[0]!='u')
		{
			printf("wrong");
			while(1);
		}

//��Ϊ�����Ѿ�������eeprom.on�ˣ��������trc.on��һ����PE10�����������ﲻ����trc.onҲ�ǿ��Ե�
		RTCbianliang.ON();

		RTCbianliang.begin();

//	RTCbianliang.setTime("Sun, 12/10/04 - 05:59:07");

		RTCbianliang.getTime();
		//printf("%s",RTCbianliang.timeStamp);delay_ms(1000);
		uartsendstr((char *)RTCbianliang.timeStamp, 30,PRINTFPORT);delay_ms(1000);

	sprintf(filenameorig,"m%02d%x%02d%02d.txt"\
	, RTCbianliang.year, RTCbianliang.month, RTCbianliang.date, RTCbianliang.hour);
	printf("%s",filenameorig);
		

//SD����Դ��
	printf("\n  SD poweron. ");		 
 	SD.ON();
//SD��ʼ�����ɹ��Ļ�Ҳ��ʼ��һ��FAT	
	printf(" SD init. "); //SD���Ǹ���Դ����Ҫ��һ����ڳ�ʼ����Ҫ��Ȼ��ЩоƬ��ʼ����������   
	SD.init();
	if(SD.flag!=NOTHING_FAILED)
	{
//		printf("err=%d ",flagsderr);
		printf("  failed!  ");
		while(1);
	}
	delay_ms(500);
	printf("sdsize=%dMB ",SDCardInfo.CardCapacity>>20);


//�õ�����ʵ����ʹ�õ����пռ�
	printf(" Get disk fat size. ");
	fsize=SD.getDiskSize();
	if(SD.flag==FR_OK)
	{
		printf(" fatsize=%d KB ",(uint32_t)(fsize>>10));
	}
	else
	{
		printf(" errflag=%x ",SD.flag);
		while(1);
	}

	sprintf((char *)AddSDstr,"\r\nsys=%10d,hclk=%10d,pclk1=%10d,pclk2=%10d RTC=%s "\
		,RCC_ClocksStatus.SYSCLK_Frequency,RCC_ClocksStatus.HCLK_Frequency\
		,RCC_ClocksStatus.PCLK1_Frequency,RCC_ClocksStatus.PCLK2_Frequency\
		,RTCbianliang.timeStamp);
//		sprintf(filenameorig,"123456789.txt");
		printf("%s",filenameorig);


   	if(SD.isFile(filenameorig)==1)
	{
		printf(" yes.");
	}
	else
	{	
		printf("no.");
		printf("create it");
		if(SD.create(filenameorig))
		{
			printf(" success ");
		}
		else
		{
			printf(" failed  ");
			while(1);
		}
	}


	filesize=SD.getFileSize(filenameorig);
	if(filesize>=0)
	{
		printf("filesize=%d ",filesize);
	}
	else
	{
			printf(" WRONG! ");
			while(1);	
	}
	SD.writeSD(filenameorig, AddSDstr, filesize);


		//��ʼƵ����168M, Ȼ��ÿ�μ�12M������һ���̶Ⱥ�Ϳ�ʼ��12M���ӵ�һ���������ظ���
		if(flagfangxiang==0)
		{
			testsys=testsys-12000000;
			if(testsys<2000000)
			{
				testsys=168000000;
				flagfangxiang=1;
			}
		}
		else if(flagfangxiang==1)
		{
			testsys=testsys+12000000;
			if(testsys>33600000)
			{
				testsys=168000000;
				flagfangxiang=0;
			}
		}
		delay_ms(3000);
		//�����ڵĲ���Ƶ�ʸ�����Ƶ���ȫ�ֱ������������ʱ��û�б�Ƶ��
		SysClkWasp=testsys;
		//��Щ����׼������������ĵ�PLLM PLLN ��Щ
		SysPreparePara();

		//����ֻ��Ϊ�˴�ӡ���Ĺ����PLLMPLLN��Щֵ
		zppSysClkWasp=SysClkWasp;
		zppSysPllM=SysPllM;
		zppSysPllN=SysPllN;
		zppSysPllP=SysPllP;
		zppSysPllQ=SysPllQ;
		zppSysFlashWait=SysFlashWait;
		zppDelayMsWasp=DelayMsWasp;
		zppDelayUsWasp=DelayUsWasp;
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);
//		TIM_Cmd(TIM3, DISABLE);

		//Ϊ�˷�ֹ��ЩƵ�ʻ���û����ȷ�ڵ�Ƭ�����У�����������ƵΪ168M���Ѹղ�Ҫ��ӡPLLM PLLN��ӡ����
		SysClkWasp=168000000;
		SysPreparePara();
		zppSystemInit();
		Mux_poweron(); //����һ����Դ���������õģ������ӡ����
		beginSerial(115200, PRINTFPORT); //ZPPDelay(0x3456789);

		printf("\npreclk=%d,pllm=%d,n=%d,p=%d,q=%d,wait=%d delayms=%d delayus=%d "\
		,zppSysClkWasp,zppSysPllM,zppSysPllN,zppSysPllP,zppSysPllQ,zppSysFlashWait,zppDelayMsWasp,zppDelayUsWasp);		
		//delay_ms(2000);

		//���ʱ�����±䵽����Ҫ�����Ƶ��
		SysClkWasp=testsys;
		SysPreparePara();
		//�ڱ���Ƶ֮ǰ�ȹص�֮ǰ��Щ���ܿ���
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);
//		TIM_Cmd(TIM3, DISABLE);	ZPPDelay(0x23456);
		//while(1)ѭ������һ�����ִ���Լ�����ϵͳ��ʼ�����Ǹ����������Ŀ�ʼ��Ƶ�ʲ�����.
	}	
}
#endif // end sendachar





#include "allboardinc.h"
#define BTESTSENDACHAR 0
#define BTESTSENDASTRING 1
#define BTESTMULTIUART6 2
#define BTESTMB7076 3
#define BTESTMB7076TOTXT 5
#define BTESTMB7076ANDMLX90614TOTXT 6
#define BTESTFORFACTORY1 7 //�����У���d9 d1(����С��),����3��ӡ��IIC_EEPROM, IIC_RTC, SPI_FLASH, SD, ���ɣ�����2���գ���SMBUS���⴫������
#define BTESTFORFACTORY2 8 //��Ҫ�ǲ�ͬ���ڵĲ���
#define BTESTUARTNULL 100

//#define EXAMPLEUART BTESTUARTNULL//0:�����ַ������� 1:�����ַ����ͽ����ַ��������� 2:����6��·����	 3:M7076
#define EXAMPLEUART BTESTUARTNULL
									//4:׼���������Ĳ���  5:׼�������ɲ��� ���бȽϺõĴ�ӡ
//send a char
#if EXAMPLEUART==BTESTSENDACHAR
void setup()
{
	Mux_poweron(); //����һ����Դ���������õģ������ӡ����

   beginSerial(9600, 3);
   beginSerial(9600, 1);
   beginSerial(9600, 2);
   beginSerial(9600, 6);
#if USEUSART4==1
   beginSerial(9600, 4);
#endif

#if USEUSART5==1
   beginSerial(9600, 5);
#endif
}

void loop()
{
		delay_ms(600);
		serialWrite('3', 3);//send a char '3' by uart3 //��ѯ��ʽ
		serialWrite('c', 3);//send a char 'c'

		serialWrite('1', 1);//send a char '1' by uart1
		serialWrite('a', 1);//send a char 'a'

		serialWrite('2', 2);//send a char '2' by uart2
		serialWrite('b', 2);//send a char 'b'

		serialWrite('6', 6);//send a char '6' by uart6
		serialWrite('f', 6);//send a char 'f'

#if USEUSART4==1
		serialWrite('4', 4);//send a char '4' by uart4
		serialWrite('d', 4);//send a char 'd'
#endif

#if USEUSART5==1
		serialWrite('5', 5);//send a char '5' by uart5
		serialWrite('e', 5);//send a char 'e'	
#endif	
}
#endif // end sendachar

//send a string. check out if RX buffer recive datas, if yes, printf them.
#if EXAMPLEUART==BTESTSENDASTRING
void setup()
{
	Mux_poweron(); //����һ����Դ���������õģ������ӡ����
   
   beginSerial(9600, 3); //����  beginSerial(9600, 3); �ǲ����������жϺͽ����жϵ�
   chooseuartinterrupt(3);//���������жϣ����ڴ������еĽ����ǰ����ж������ġ� ���ⷢ�����жϷ�ʽ�Ͳ�ѯ��ʽ�����忴����
   beginSerial(9600, 1);chooseuartinterrupt(1);
   beginSerial(9600, 2);chooseuartinterrupt(2);
   beginSerial(9600, 6);chooseuartinterrupt(6);
#if USEUSART4==1
   beginSerial(9600, 4);chooseuartinterrupt(4);
#endif

#if USEUSART5==1
   beginSerial(9600, 5);chooseuartinterrupt(5);
#endif
}

void loop()
{
	uint8_t recbuffer[20];
	uint8_t reclenwant=10;
	int reclenfact;
		uartsendstr((char *)"a string by uart 3 ABCDEF", 22,3);//send a string by uart 3. //�жϷ�ʽ
		delay_ms(1000);//��Ϊ�����жϷ�ʽ�����Է�һ���ַ���һ��Ҫ��ʱһ�£� ʱ�������ö�Ӧ��������Ϳ�����

		uartsendstr((char *)"test str by uart 1 GHIJKMNOPQ", 22,1);
		delay_ms(1000);

		uartsendstr((char *)"uart 2:    str and RSTUVWXYZ", 22,2);
		delay_ms(1000);

		uartsendstr((char *)"a string by uart 6 aaaaa ", 22,6);
		delay_ms(1000);

#if USEUSART4==1
		serialWrite('4', 4);//send a char '4' by uart4
		serialWrite('d', 4);//send a char 'd'
		uartsendstr((char *)"a string by uart 4 bbbbb ", 22,4);
		delay_ms(1000);
#endif

#if USEUSART5==1
		serialWrite('5', 5);//send a char '4' by uart4
		serialWrite('e', 5);//send a char 'd'
		uartsendstr((char *)"a string by uart 5 ccc   ", 22,5);
		delay_ms(1000);
#endif
		//if RXbuffer of uart3 receive datas, printf them.
		reclenfact=serialReadstr(recbuffer, reclenwant,3);
		if(reclenfact>0)
		{
			uartsendstr((char *)"receive ", 8,3);
			delay_ms(1000);	
			printIntegerInBase(reclenfact, 10, 3);
			delay_ms(1000);
			uartsendstr((char *)" bytes by uart3, they are   ", 26,3);
			delay_ms(1000);	
			uartsendstr((char *)recbuffer, reclenfact,3);
			delay_ms(1000);															
		}
		else
		{
			uartsendstr((char *)"no or err by uart3    ", 20,3);
			delay_ms(1000);			
		}
		uartsendstr((char *)"\n ", 2,3);


		reclenfact=serialReadstr(recbuffer, reclenwant,1);
		if(reclenfact!=0)
		{
			uartsendstr((char *)"receive ", 8,1);
			delay_ms(1000);	
			printIntegerInBase(reclenfact, 10, 1);//����ǲ�ѯ��ʽ
			delay_ms(1000);
			uartsendstr((char *)" bytes by uart1 ", 16,1);
			delay_ms(1000);						
		}
		else
		{
			uartsendstr((char *)"no by uart1 ", 12,1);
			delay_ms(1000);			
		}

		reclenfact=serialReadstr(recbuffer, reclenwant,2);
		if(reclenfact!=0)
		{
			uartsendstr((char *)"receive ", 8,2);
			delay_ms(1000);	
			printIntegerInBase(reclenfact, 10, 2);
			delay_ms(1000);
			uartsendstr((char *)" bytes by uart2 ", 16,2);
			delay_ms(1000);						
		}
		else
		{
			uartsendstr((char *)"no by uart2 ", 12,2);
			delay_ms(1000);			
		}

		reclenfact=serialReadstr(recbuffer, reclenwant,6);
		if(reclenfact!=0)
		{
			uartsendstr((char *)"receive ", 8,6);
			delay_ms(1000);	
			printIntegerInBase(reclenfact, 10, 6);
			delay_ms(1000);
			uartsendstr((char *)" bytes by uart6,they are     ", 26,6);
			delay_ms(1000);	
			uartsendstr((char *)recbuffer, reclenfact,6);
			delay_ms(1000);								
		}
		else
		{
			uartsendstr((char *)"no by uart6 ", 12,6);
			delay_ms(1000);			
		}

#if USEUSART4==1
		reclenfact=serialReadstr(recbuffer, reclenwant,4);
		if(reclenfact!=0)
		{
			uartsendstr((char *)"receive ", 8,4);
			delay_ms(1000);	
			printIntegerInBase(reclenfact, 10, 4);
			delay_ms(1000);
			uartsendstr((char *)" bytes by uart4,they are     ", 26,4);
			delay_ms(1000);	
			uartsendstr((char *)recbuffer, reclenfact,4);
			delay_ms(1000);								
		}
		else
		{
			uartsendstr((char *)"no by uart4 ", 12,4);
			delay_ms(1000);			
		}
#endif

#if USEUSART5==1
		reclenfact=serialReadstr(recbuffer, reclenwant,5);
		if(reclenfact!=0)
		{
			uartsendstr((char *)"receive ", 8,5);
			delay_ms(1000);	
			printIntegerInBase(reclenfact, 10, 5);
			delay_ms(1000);
			uartsendstr((char *)" bytes by uart5,they are     ", 26,5);
			delay_ms(1000);	
			uartsendstr((char *)recbuffer, reclenfact,5);
			delay_ms(1000);								
		}
		else
		{
			uartsendstr((char *)"no by uart5 ", 12,5);
			delay_ms(1000);			
		}
#endif
}
#endif




//test multiuart6
#if EXAMPLEUART==BTESTMULTIUART6
void setup()
{
   muluart6init();//������Գ䵱���ڵĵ�Դ�� �ü��
   beginSerial(9600, 6);
   
}

void loop()
{
	muluart6choose(1);	
	serialWrite('1', 6);//send a char '3' by uart3
	serialWrite('f', 6);//send a char 'c'
	delay_ms(100);

	muluart6choose(2);	
	serialWrite('2', 6);//send a char '3' by uart3
	serialWrite('f', 6);//send a char 'c'
	delay_ms(100);

	muluart6choose(3);	
	serialWrite('3', 6);//send a char '3' by uart3
	serialWrite('f', 6);//send a char 'c'
	delay_ms(100);

	muluart6choose(4);	
	serialWrite('4', 6);//send a char '3' by uart3
	serialWrite('f', 6);//send a char 'c'
	delay_ms(100);
}
#endif


//test MB7076
//we can get datas from MB7076 by uart2, and printf them by uart6.
#if EXAMPLEUART==BTESTMB7076
void setup()
{	beginMb7076();
//	beginSerial(9600, 2); chooseuartinterrupt(2);//���ɴ����������Ǵ���2��������Ϊ9600 
////	testsenserinit();
//	PWR2745.initPower(PWR_SENS1_5V);//������������ɴ������ĵ�Դ��
//	PWR2745.switchesON(PWR_SENS1_5V);
	Mux_poweron(); //����һ����Դ���������õģ������ӡ����
	beginSerial(115200, 1);

}
//������Ӳ��Ǻ�������ֻ�ǰѽ��յ��Ķ�����ӡ��������û�а�æ����������ζ�Ŷ�����
//��btest_data0902.cpp�����и�BTESTDATE0902_2,�Ǹ������ľ�������ֱ��
void loop()
{
  	uint8_t recbuffer[100];
	uint8_t reclenwant=90;
	int reclenfact;
	
	serialWrite('1', 1);//send a char '3' by uart3
	serialWrite('6', 1);//send a char 'c'
	delay_ms(500);
	reclenfact=serialReadstr(recbuffer, reclenwant,2);
	if(reclenfact>0)
	{
		uartsendstr((char *)"receive ", 8,1);
		delay_ms(10);	
		printIntegerInBase(reclenfact, 10, 1);
		delay_ms(10);
		uartsendstr((char *)" bytes : ", 9,1);
		delay_ms(10);				
		uartsendstr((char *)recbuffer, reclenfact,1);
		delay_ms(150);															
	}
	else
	{
		uartsendstr((char *)"no or err by uart6    ", 20,1);
		delay_ms(100);			
	}
}
#endif



//
#if EXAMPLEUART==BTESTFORFACTORY1
uint8_t ReadStrSd[20]="strhaha";

uint8_t RecBuffer[200];
uint8_t RecLenWant=190;

uint8_t RecBufferLast[200];
uint8_t LastLeftLen=0;

uint8_t RecBufferAddLast[200];
uint8_t ZhengHeLen=0;

int RecLenFact;
#define ARRAYMB7076LENMAX 40
uint16_t ArrayMb7076[ARRAYMB7076LENMAX];
uint8_t LenMb7076Array;

uint8_t BytesMb=0;
uint16_t LastMb7076=0;

int comparerxxxx(uint8_t * recbuffer, uint8_t len)
{
	uint8_t i;
	uint8_t k;

	if(len>=240)return -1;
	for(i=0;i<(len-4);i++)
	{
		if((*(recbuffer+i)=='R'))
		{
			
			for(k=1;k<5;k++)
			{
				if((*(recbuffer+i+k)>='0')&&(*(recbuffer+i+k)<='9'));
				else break;
			}
			if(k==5)return i;
			//return i;
		}
	}
	return -2;		
}

void setup()
{
	uint8_t flagiic=0;
	int  readdata;
	uint32_t shijianqian;
	uint32_t shijianhou;
	int readch;
	int32_t filesize=-2;
	int32_t filesizeold=-2;
	float temperature;

	Mux_poweron(); monitor_on();
	beginSerial(9600, 3);
//	beginSerial(9600, 1);
	beginSerial(9600, 2);
//	beginSerial(9600, 6);

	for(uint16_t i=0;i<5;i++)
		Utils.blinkLEDs(100);

	delay_ms(100);
	serialWrite('3', 3);//send a char '3' by uart3
	serialWrite('c', 3);//send a char 'c'

//	serialWrite('1', 1);//send a char '1' by uart1
//	serialWrite('a', 1);//send a char 'a'
//
//	serialWrite('2', 2);//send a char '2' by uart2
//	serialWrite('b', 2);//send a char 'b'
//
//	serialWrite('6', 6);//send a char '6' by uart6
//	serialWrite('f', 6);//send a char 'f'

//	RTCbianliang.ON();
//	RTCbianliang.begin();



	Eeprom.ON();
	delay_ms(20);	
	Eeprom.begin();	
	//printf("test IIC\r\n");


	Eeprom.start();
	if(Eeprom.setSlaveAddress(0xa0)==I2CTRUE){
		if(Eeprom.writeEEPROM(0X0001,'A')==I2CTRUE){
			//printf("write ok.");
			Eeprom.start();
			if(Eeprom.setSlaveAddress(0xa0)==I2CTRUE){
				readdata=  Eeprom.readEEPROM(0X0001);
				if(readdata!=I2CFALSE){
					if(readdata!='A'){
						printf("\r\nEeprom read!=write WRONG\r\n");
					}
					else
					{
						printf("\r\n\t\tiic_eeprom ok\r\n");
						flagiic=1;//˵��i2Cû�������ˣ�������ܲ���RTC
					}	
				}
				else{
					printf("\r\nEeprom read WRONG\r\n");
				}		
			}
			else{
				printf("\r\nEeprom read setslaveaddress WRONG\r\n");
			}				
		}
		else{
			printf("\r\nEeprom write WRONG\r\n");
		}		
	}
	else{
		printf("\r\nEeprom write setslaveaddress WRONG\r\n");
	}

	//��Ҫ�ǿ��趨ʱ�� ������һ�������������룬ʱ���߲��ߴ������
	//���������IIC��EEPROMû������Ļ���������RTC
	if(flagiic==1)
	{
		RTCbianliang.setTime("Sun, 12/10/04 - 05:59:07");

		RTCbianliang.getTime();
		printf("\r\n\t\t%s\r\n",RTCbianliang.timeStamp);
		if(RTCbianliang.minute!=59){
			printf("\r\nRTC set time WRONG\r\n");
		}

		shijianqian= ((uint32_t)RTCbianliang.hour)*3600+ ((uint32_t)RTCbianliang.minute)*60  + RTCbianliang.second;
		delay_ms(2000);

		RTCbianliang.getTime();
		shijianhou= ((uint32_t)RTCbianliang.hour)*3600+ ((uint32_t)RTCbianliang.minute)*60  + RTCbianliang.second;

		if(shijianhou<shijianqian){
			printf("\r\nRTC time is WRONG\r\n");
		}
		else if(shijianhou==shijianqian){
			printf("\r\nRTC time stop WRONG\r\n");
		}
		else if((shijianhou-shijianqian)>3){
 			printf("\r\nRTC time run faster WRONG\r\n");
		}
		else
		{
			printf("\r\n\t\tiic_rtc ok\r\n");
		}		
	}

	//��ָ����ַ��д��'4'���������ǲ��ǣ��ǵľ�OK . �µ�оƬ����Ӧ��Ҫ������0��Ҫ������ff
	Flash.SPI_Flash_Init();//SPI FLASH��ʼ��	
	//�ڵ�ַ4092�Ǳ�д���ַ�'4'(0x34)
	//printf("\n  Write a char '4' to address=4092.");
	readch=Flash.writeFlash(4092,(uint8_t)'4');
	if(readch==FLASHSECTOEWRITEOK)//���д�ɹ���
	{
		//printf("ok");
		//����ַ4092��������,����������ݰ����ݸ�readch,�����������ݻ������������������Ϣ�����Ǹ�������readch
		//�˺��������Ͽͻ��ṩ�Ķ�����д�������ݿͻ��ṩҲ��uint8_t readFlash1byte(uint32_t add)��uint16_t WaspFLASH::readFlash2byte(uint32_t add),uint32_t WaspFLASH::readFlash4byte(uint32_t add)
		// ���Ǹ��ݿͻ������������������оƬæ֮��ľ�ֻ�ܷ���0�����ܷ�Ӧ������Ϣ��
		//printf("  Read a char from address=4092:");
		readch=Flash.flashreaddata4add(4092);
		if(readch<0)
		{
			printf("\r\nSPI read WRONG \r\n");			
		}
		else
		{
			//�Ѷ����������ݣ���������ͣ��ô���3��ӡ��������ʵ�����printfֻ��Դ���3���������printf����retarget.c�аѴ���3��serialWrite((unsigned char) ch, 3)ӳ�䵽fputc(int ch, FILE *f)�ˡ�
			// ����ͻ���ϲ��������԰�retarget.cɾ�������ڴ�ӡ����wiring_serial.c�����void serialWrite(unsigned char c, uint8_t portNum)
			if(readch!='4')
			{
				printf("\r\nSPI read!=write WRONG \r\n");	
			}
			else
			{
				printf("\r\n\t\tspi_flash ok\r\n");
			}		
		}
	}										 
	else
	{
		printf("\r\nSPI write WRONG \r\n");
	}

	//��filezpp1.txt�������һ�����ݣ�Ȼ���ڶ�����ļ���С��û������1������1����ΪSD OK
 	SD.ON();
	SD.init();
	if(SD.flag!=NOTHING_FAILED)
	{
		printf("\r\nSD WRONG, maybe because SD not be push in \r\n");
	}
	else
	{
		if(SD.isFile("filezpp1.txt")==1)
		{
			filesize = SD.getFileSize("filezpp1.txt");
			if(filesize>10)
			{
				SD.del("filezpp1.txt");
				SD.create("filezpp1.txt");
			}
		}
		else
		{
			SD.create("filezpp1.txt");
		}

		if(SD.isFile("filezpp1.txt")!=1)
		{
			printf("\r\nSD create file WRONG \r\n");
		}
		else
		{
			filesize = SD.getFileSize("filezpp1.txt");
			filesizeold = filesize;
			if(filesize>10)
			{
				printf("\r\nSD  file size WRONG \r\n");
			}
			else
			{
				SD.writeSD("filezpp1.txt", "I", filesizeold);
				filesize = SD.getFileSize("filezpp1.txt");
				if(filesize == (filesizeold+1))
				{
					printf("\r\n\t\tsd ok\r\n");
				}
				else{
					printf("\r\nSD  file write new WRONG \r\n");
				}
				
			}			
		}
	}


	RecLenFact=serialReadstr(RecBuffer, RecLenWant,2);
	
	if(RecLenFact>0)
	{
		if(comparerxxxx(RecBuffer, RecLenFact)>=0)
		{
			printf("\r\n\t\tuart2(Sonar) recive ok\r\n");
		}
		else
		{
			printf("\r\nSonar WRONG\r\n");
		}																	
	}
	else
	{
		printf("\r\nUART2 recive WRONG, maybe 1. sonar not put on,\r\n\t\t\t  2. the circuit of uart2 is wrong\r\n");			
	}

	//printf(" smubs ");
	SMBus_Init();	
	SMBus_Apply();
	temperature = readatemp(0xA0);
	if(((double)temperature>5.0)&&((double)temperature<40.0))
	{
		printf("\r\n\t\tsmbus ok\r\n");
	}
	else{
		printf("\r\nsmbus WRONG,maybe mlx90614 not put on\r\n");
	}
}

void loop()
{
	while(1);	
}
#endif // end BTESTFORFACTORY1

//
#if EXAMPLEUART==BTESTFORFACTORY2
uint8_t ReadStrSd[20]="strhaha";

uint8_t RecBuffer[20];
uint8_t RecLenWant=15;

int RecLenFact;




void setup()
{
	unsigned char testsendch;
	unsigned long i;
//	unsigned char testrecch;
	beginSerial(115200, 3);
	beginSerial(115200, 1);
	beginSerial(115200, 2);
	beginSerial(115200, 6);
//	delay_ms(20);
	monitor_on();
	muluart6init();	
	testsenserinit();
	XBee.begin();	 //���˷�����������
	for(uint16_t i=0;i<5;i++){
		Utils.setLED(2, 1);
		delay_ms(200);
		Utils.setLED(2, 0);
		delay_ms(200);
	}
	serialWrite('1', 1);//send a char '3' by uart3
	serialWrite('a', 1);//send a char 'c'
	serialWrite('2', 2);//send a char '3' by uart3
	serialWrite('b', 2);//send a char 'c'
	serialWrite('3', 3);//send a char '3' by uart3
	serialWrite('c', 3);//send a char 'c'
	printf("test uart1 2 3 6_1 6_2 6_3 6_4");
	muluart6choose(1);
	serialWrite('6', 6);//send a char '3' by uart3
	serialWrite('f', 6);//send a char 'c'
	serialWrite('1', 6);//send a char 'c'
	delay_ms(10);
	muluart6choose(2);
	delay_ms(10);
	serialWrite('6', 6);//send a char '3' by uart3
	serialWrite('f', 6);//send a char 'c'
	serialWrite('2', 6);//send a char 'c'
	delay_ms(10);
	muluart6choose(3);
	delay_ms(10);
	serialWrite('6', 6);//send a char '3' by uart3
	serialWrite('f', 6);//send a char 'c'
	serialWrite('3', 6);//send a char 'c'
	delay_ms(10);
	muluart6choose(4);
	delay_ms(10);
	serialWrite('6', 6);//send a char '3' by uart3
	serialWrite('f', 6);//send a char 'c'
	serialWrite('4', 6);//send a char 'c'
	delay_ms(10);
	while(1)
	{	
			
		delay_ms(10);
		testsendch='f';
		serialWrite(testsendch, 1);
		delay_ms(10);
		printf("\r\n");
		RecLenFact=serialReadstr(RecBuffer, RecLenWant,1);
		if(RecLenFact>0){
			if(RecBuffer[RecLenFact-1]==testsendch){
				printf("uart1 ok");		
			}
			else{
				printf("WRONG uart1,maybe jump jacket not on");					
			}
		}
		else{
			printf("WRONG uart1,maybe jump jacket not on");			
		}


		delay_ms(10);
		testsendch=0x7f;
		serialWrite(testsendch, 2);
		delay_ms(10);
		printf("\r\n");
		RecLenFact=serialReadstr(RecBuffer, RecLenWant,2);
		if(RecLenFact>0){
			if(RecBuffer[RecLenFact-1]==0x40){
				printf("uart2 ok");		
			}
			else{
				printf("WRONG uart2,maybe jump jacket not on");					
			}
		}
		else{
			printf("WRONG uart2,maybe jump jacket not on");			
		}


//		RecLenFact=serialReadstr(RecBuffer, RecLenWant,2);
//		if(RecLenFact>0)
//		{
//			serialWrite(RecBuffer[0], 2);	
//		}


		RecLenFact=serialReadstr(RecBuffer, RecLenWant,3);
		if(RecLenFact>0)
		{
			serialWrite(RecBuffer[0], 3);				
		}

		muluart6choose(1);
		delay_ms(10);
		testsendch='d';
		serialWrite(testsendch, 6);
		delay_ms(10);
		printf("\r\n");
		RecLenFact=serialReadstr(RecBuffer, RecLenWant,6);
		if(RecLenFact>0)
		{
			//serialWrite(RecBuffer[0], 6);	
			if(RecBuffer[RecLenFact-1]==testsendch)
			{
				printf("uart6_1 ok");//delay_ms(3000);		
			}
			else
			{
				printf("WRONG uart6_1,maybe jump jacket not on");//delay_ms(3000);					
			}
		}
		else
		{
			printf("WRONG uart6_1,maybe jump jacket not on");
			//delay_ms(3000);				
		}

		muluart6choose(2);
		delay_ms(10);
		testsendch='c';
		serialWrite(testsendch, 6);
		delay_ms(10);
		printf("\r\n");
		RecLenFact=serialReadstr(RecBuffer, RecLenWant,6);
		if(RecLenFact>0)
		{
			//serialWrite(RecBuffer[0], 6);	
			if(RecBuffer[RecLenFact-1]==testsendch)
			{
				printf("uart6_2 ok");//delay_ms(3000);		
			}
			else
			{
				printf("WRONG uart6_2,maybe jump jacket not on");//delay_ms(3000);					
			}
		}
		else
		{
			printf("WRONG uart6_2,maybe jump jacket not on");
			//delay_ms(3000);				
		}

		muluart6choose(3);
		delay_ms(10);
		testsendch='b';
		serialWrite(testsendch, 6);
		delay_ms(10);
		printf("\r\n");
		RecLenFact=serialReadstr(RecBuffer, RecLenWant,6);
		if(RecLenFact>0)
		{
			//serialWrite(RecBuffer[0], 6);	
			if(RecBuffer[RecLenFact-1]==testsendch)
			{
				printf("uart6_3 ok");//delay_ms(3000);		
			}
			else
			{
				printf("WRONG uart6_3,maybe jump jacket not on");//delay_ms(3000);					
			}
		}
		else
		{
			printf("WRONG uart6_3,maybe jump jacket not on");
			//delay_ms(3000);				
		}

		muluart6choose(4);
		delay_ms(10);
		testsendch='a';
		serialWrite(testsendch, 6);
		delay_ms(10);
		printf("\r\n");
		RecLenFact=serialReadstr(RecBuffer, RecLenWant,6);
		if(RecLenFact>0)
		{
			//serialWrite(RecBuffer[0], 6);	
			if(RecBuffer[RecLenFact-1]==testsendch)
			{
				printf("uart6_4 ok");//delay_ms(3000);		
			}
			else
			{
				printf("WRONG uart6_4,maybe jump jacket not on");//delay_ms(3000);					
			}
		}
		else
		{
			printf("WRONG uart6_4,maybe jump jacket not on");
			//delay_ms(3000);				
		}
		for(i=0;i<9000;i++)
		{
			RecLenFact=serialReadstr(RecBuffer, RecLenWant,3);
			if(RecLenFact>0)
			{
				serialWrite(RecBuffer[0], 3);				
			}
			delay_ms(1);
		}
			


	}



}

void loop()
{
	
}
#endif // end BTESTFORFACTORY2





//
#if EXAMPLEUART==BTESTMB7076TOTXT
uint8_t RecBuffer[200];
uint8_t RecLenWant=190;

uint8_t RecBufferLast[200];
uint8_t LastLeftLen=0;

uint8_t RecBufferAddLast[200];
uint8_t ZhengHeLen=0;

int RecLenFact;
#define ARRAYMB7076LENMAX 40
uint16_t ArrayMb7076[ARRAYMB7076LENMAX];
uint8_t LenMb7076Array;

uint8_t BytesMb=0;
uint16_t LastMb7076=0;
//Rxxxx\n �ֱ�Ϊ R ���� ���� ���� ���� \n�⼸��
int comparerxxxx(uint8_t * recbuffer, uint8_t len)
{
	uint8_t i;
	uint8_t k;

	if(len>=240)return -1;
	for(i=0;i<(len-4);i++)
	{
		if((*(recbuffer+i)=='R'))
		{
			
			for(k=1;k<5;k++)
			{
				if((*(recbuffer+i+k)>='0')&&(*(recbuffer+i+k)<='9'));
				else break;
			}
			if(k==5)return i;
			//return i;
		}
	}
	return -2;		
}
//�õ��ַ���������ٸ���ЧRxxxxn�����ݣ���һ��ָ���¼����
int getmb7076zhi(uint8_t * recbuffer, uint8_t len, uint16_t * array, uint8_t *arraylen)
{
	uint8_t i;
	int kaitou=0;
	uint8_t offset=0;
	uint16_t zhi;
	//uint16_t sum;
	uint8_t *p;

	uint8_t aimlen=0;
	
	//*arraylen=0;
	while(1)
	{
		kaitou=comparerxxxx(recbuffer+offset, len-offset);
		if(kaitou>=0)
		{
			zhi=0;
			p=recbuffer+offset+kaitou+1;
			//printf("jisuan");
			for(i=0;i<4;i++)
			{
				zhi = (zhi)*10 + *(p+i)-'0';
				//printf("%c",*(p+i));	
			}
			*(array+ aimlen) = zhi;
			aimlen ++;
			if(aimlen>ARRAYMB7076LENMAX)break;
			offset=kaitou+offset+5;
//			printf(" k=%d z=%d o=%d ",kaitou,zhi,offset);
		}
		else break;
	}

	*arraylen = aimlen;
	return offset;

}
void setup()
{
	//uint8_t *p;
	Mux_poweron();
   beginSerial(115200, 3);
   beginSerial(9600, 1);

   beginSerial(9600, 6);
#if USEUSART4==1
   beginSerial(9600, 4);
#endif

#if USEUSART5==1
   beginSerial(9600, 5);
#endif
	for(uint16_t i=0;i<5;i++)
		Utils.blinkLEDs(100);

	delay_ms(100);
	serialWrite('3', 3);//send a char '3' by uart3
	serialWrite('c', 3);//send a char 'c'

	printf("\r\n\r\n\r\n\r\n");

	RTCbianliang.ON();
	RTCbianliang.begin();

	RTCbianliang.setTime("Sun, 12/10/04 - 05:59:07\r\n");
	delay_ms(1000);
	RTCbianliang.getTime();
	printf("%s",RTCbianliang.timeStamp);
    beginSerial(9600, 2);
}
//���������Ƶ�������죬���ԣ�û��һ��MB������ʱ�п����µ����ݻ�û���������ʱ���ӡ����һ�ε���Ч���ݣ�
void loop()
{
	delay_ms(20);//
	RTCbianliang.getTime();
	//uartsendstr(RTCbianliang.timeStamp, 10,3);
	//uartsendstr(RTCbianliang.timeStamp, strlen(RTCbianliang.timeStamp),3);
	printf("%s\t",RTCbianliang.timeStamp);
	//delay_ms(50);
	RecLenFact=serialReadstr(RecBuffer, RecLenWant,2);
	
	if(RecLenFact>0)
	{
		for(uint16_t i=0; i< LastLeftLen; i++)
		{
			RecBufferAddLast[i] = RecBufferLast[i];	
		}
		for(uint16_t i=0; i< RecLenFact; i++)
		{
			RecBufferAddLast[LastLeftLen+i]=RecBuffer[i];
		}
		RecBufferAddLast[LastLeftLen+RecLenFact]=0x00;
		ZhengHeLen=LastLeftLen+RecLenFact;


		for(uint16_t i=0; i< ZhengHeLen; i++)
		{	if(RecBufferAddLast[i]==0x00)RecBufferAddLast[i]='S';
		}


		LastLeftLen=getmb7076zhi(RecBufferAddLast, ZhengHeLen, ArrayMb7076, &LenMb7076Array);

		for(uint16_t i=0; i< (ZhengHeLen-LastLeftLen); i++)
		{
			RecBufferLast[i] = RecBufferAddLast[LastLeftLen+i];	
		}
		LastLeftLen=ZhengHeLen-LastLeftLen;

		if(LenMb7076Array>0)
		{
//			if(BytesMb==0)BytesMb=LenMb7076Array-2;
//
//			printf(" len=%d ",BytesMb);
//		   for(uint16_t i=0;i<BytesMb;i++)
//		   {
//		   	printf(" r=%4d ",ArrayMb7076[i]);	
//		   }
//			printf(" len=%d ",LenMb7076Array);
//		   for(uint16_t i=0;i<LenMb7076Array;i++)
//		   {
//		   	printf(" r=%4d ",ArrayMb7076[i]);	
//		   }

//			printf(" len=%d ",LenMb7076Array);
//		   for(uint16_t i=0;i<3;i++)
//		   {
//		   	printf(" %4d",ArrayMb7076[i]);	
//		   }
		   printf("data=\t%4d\tok\r\n",ArrayMb7076[0]);
		   LastMb7076=ArrayMb7076[0];
		}
		else
		{
			printf("data=\t%4d\ter\r\n",LastMb7076);
		}
																	
	}
	else
	{
//		uartsendstr((char *)"no or err by uart6    ", 20,3);
//		delay_ms(100);
		printf("data=\t%4d\tno\r\n",LastMb7076);			
	}

	
}
#endif // BTESTMB7076TOTXT




//BTESTMB7076ANDMLX90614TOTXT

#if EXAMPLEUART==BTESTMB7076ANDMLX90614TOTXT
uint8_t RecBuffer[200];
uint8_t RecLenWant=190;

uint8_t RecBufferLast[200];
uint8_t LastLeftLen=0;

uint8_t RecBufferAddLast[200];
uint8_t ZhengHeLen=0;

int RecLenFact;
#define ARRAYMB7076LENMAX 40
uint16_t ArrayMb7076[ARRAYMB7076LENMAX];
uint8_t LenMb7076Array;

uint8_t BytesMb=0;
uint16_t LastMb7076=0;

unsigned int DATA=0;
unsigned int zhiint,slave_add;
unsigned char slave;
float tempA;
float tempObject;

unsigned int DataYuan[6];
unsigned long DatatoLong[6];



//Rxxxx\n �ֱ�Ϊ R ���� ���� ���� ���� \n�⼸��
int comparerxxxx(uint8_t * recbuffer, uint8_t len)
{
	uint8_t i;
	uint8_t k;

	if(len>=240)return -1;
	for(i=0;i<(len-4);i++)
	{
		if((*(recbuffer+i)=='R'))
		{
			
			for(k=1;k<5;k++)
			{
				if((*(recbuffer+i+k)>='0')&&(*(recbuffer+i+k)<='9'));
				else break;
			}
			if(k==5)return i;
			//return i;
		}
	}
	return -2;		
}
//�õ��ַ���������ٸ���ЧRxxxxn�����ݣ���һ��ָ���¼����
int getmb7076zhi(uint8_t * recbuffer, uint8_t len, uint16_t * array, uint8_t *arraylen)
{
	uint8_t i;
	int kaitou=0;
	uint8_t offset=0;
	uint16_t zhi;
	//uint16_t sum;
	uint8_t *p;

	uint8_t aimlen=0;
	
	//*arraylen=0;
	while(1)
	{
		kaitou=comparerxxxx(recbuffer+offset, len-offset);
		if(kaitou>=0)
		{
			zhi=0;
			p=recbuffer+offset+kaitou+1;
			//printf("jisuan");
			for(i=0;i<4;i++)
			{
				zhi = (zhi)*10 + *(p+i)-'0';
				//printf("%c",*(p+i));	
			}
			*(array+ aimlen) = zhi;
			aimlen ++;
			if(aimlen>ARRAYMB7076LENMAX)break;
			offset=kaitou+offset+5;
//			printf(" k=%d z=%d o=%d ",kaitou,zhi,offset);
		}
		else break;
	}

	*arraylen = aimlen;
	return offset;

}
////���ص����������������緵����27�������27��
//static int trantocentigrade(unsigned int zhi)
//{
//	return ((int)(zhi/50)-273);
//}
////���ص�������������Ϊ��λ�ģ����緵����1987�������19.87��
//static long trantocentigradelongdot2(unsigned int zhi)
//{
//	//return (((long)zhi*100/50)-27315);
//	return (((long)zhi*2)-27315);
//	//(float)((double)((unsigned long)zhi*100/50-27315)/100.00);
//}
////���ص���С�������緵����19.87�������19.87��
//static float trantocentigradefloat(unsigned int zhi)
//{
//	//return (((float)zhi/50.0)-273.15);
//	return (((double)zhi*0.02)-273.15);
//}

void setup()
{
	//uint8_t *p;
	Mux_poweron();
	monitor_on();
	beginSerial(115200, 3);
	beginSerial(9600, 1);
	
	beginSerial(9600, 6);

	for(uint16_t i=0;i<5;i++)
		Utils.blinkLEDs(100);

	delay_ms(100);
	serialWrite('3', 3);//send a char '3' by uart3
	serialWrite('c', 3);//send a char 'c'

	printf("\r\n\r\n\r\n\r\n");

	RTCbianliang.ON();
	RTCbianliang.begin();

	RTCbianliang.setTime("Sun, 12/10/04 - 05:59:07");
	delay_ms(1000);
	RTCbianliang.getTime();
	printf("%s\r\n",RTCbianliang.timeStamp);

	SMBus_Init();	
	SMBus_Apply();


    beginSerial(9600, 2);
}
//���������Ƶ�������죬���ԣ�û��һ��MB������ʱ�п����µ����ݻ�û���������ʱ���ӡ����һ�ε���Ч���ݣ�
void loop()
{
	delay_ms(20);//
	RTCbianliang.getTime();
	printf("%s\t",RTCbianliang.timeStamp);
	RecLenFact=serialReadstr(RecBuffer, RecLenWant,2);
	
	if(RecLenFact>0)
	{
		for(uint16_t i=0; i< LastLeftLen; i++)
		{
			RecBufferAddLast[i] = RecBufferLast[i];	
		}
		for(uint16_t i=0; i< RecLenFact; i++)
		{
			RecBufferAddLast[LastLeftLen+i]=RecBuffer[i];
		}
		RecBufferAddLast[LastLeftLen+RecLenFact]=0x00;
		ZhengHeLen=LastLeftLen+RecLenFact;


		for(uint16_t i=0; i< ZhengHeLen; i++)
		{	if(RecBufferAddLast[i]==0x00)RecBufferAddLast[i]='S';
		}


		LastLeftLen=getmb7076zhi(RecBufferAddLast, ZhengHeLen, ArrayMb7076, &LenMb7076Array);

		for(uint16_t i=0; i< (ZhengHeLen-LastLeftLen); i++)
		{
			RecBufferLast[i] = RecBufferAddLast[LastLeftLen+i];	
		}
		LastLeftLen=ZhengHeLen-LastLeftLen;

		if(LenMb7076Array>0)
		{
		   printf("data=\t%4d\tok\t",ArrayMb7076[0]);
		   LastMb7076=ArrayMb7076[0];
		}
		else
		{
			printf("data=\t%4d\ter\t",LastMb7076);
		}
																	
	}
	else
	{
		printf("data=\t%4d\tno\t",LastMb7076);			
	}

    //slave_add= MEM_READ1(0xA0,0x2E);   //��ȡSMBUS��ַ
	//06:TA//�����¶�  07:TOBJ1//�����¶�   08:TOBJ2//�����¶�
	
	//DATA=MEM_READ1(0xA0,0x06);							DataYuan[0]=DATA;
	//tempA=	trantocentigradefloat(DATA);				DatatoLong[0]=trantocentigradelongdot2(DATA);
	printf("aa=\t%.2f\t",readatemp(0xA0));
	
	//DATA=MEM_READ1(0xA0,0x07);							DataYuan[1]=DATA;	
	//tempObject=	trantocentigradefloat(DATA);			DatatoLong[1]=trantocentigradelongdot2(DATA);
	printf("ao=\t%.2f\t",readobjtemp(0xA0));//delay_ms(500);

	//slave_add= MEM_READ1(0xB0,0x2E);   //��ȡSMBUS��ַ 
	//DATA=MEM_READ1(0xB0,0x06);							DataYuan[2]=DATA;
	//tempA=	trantocentigradefloat(DATA);				DatatoLong[2]=trantocentigradelongdot2(DATA);
	printf("ba=\t%.2f\t",readatemp(0xB0));	
	//DATA=MEM_READ1(0xB0,0x07);							DataYuan[3]=DATA;
	//tempObject=	trantocentigradefloat(DATA);			DatatoLong[3]=trantocentigradelongdot2(DATA);
	printf("bo=\t%.2f\t",readobjtemp(0xB0));


	//slave_add= MEM_READ1(0xC0,0x2E);   //��ȡSMBUS��ַ 	
	//06:TA//�����¶�  07:TOBJ1//�����¶�   08:TOBJ2//�����¶�
	//DATA=MEM_READ1(0xC0,0x06);							DataYuan[4]=DATA;
	//tempA=	trantocentigradefloat(DATA);				DatatoLong[4]=trantocentigradelongdot2(DATA);
	printf("ca=\t%.2f\t",readatemp(0xC0));//delay_ms(1000);	
	//DATA=MEM_READ1(0xC0,0x07);							DataYuan[5]=DATA;
	//tempObject=	trantocentigradefloat(DATA);			DatatoLong[5]=trantocentigradelongdot2(DATA);
	printf("co=\t%.2f\t",readobjtemp(0xC0));

//	for(uint16_t i=0;i<6;i++)
//	{
//		printf(" %d %d\t",DataYuan[i],DatatoLong[i]);
//	}




	printf("\r\n");








	
}
#endif // BTESTMB7076ANDMLX90614TOTXT



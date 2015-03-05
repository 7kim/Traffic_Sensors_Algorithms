#include "allboardinc.h"
#define BTESTXBEESIMPLEONLYFORZHP 1
#define BTESTXBEESENDFASTBROADCASTONLYFORZHP 2
#define BTESTXBEESENDFASTUNICASTONLYFORZHP 3
#define BTESTXBEERECONLYFORZHP 4
#define BTESTXBEERECBYRx80Buffer 5
//#define BTESTXBEERECFASTUNICAST 5
#define BTESTXBEERECTHENFASTBROADCASTONLYFORZHP 6

#define BTESTXBEENULLONLYFORZHP 0

#define EXAMPLEXBEEONLYFORZHP BTESTXBEENULLONLYFORZHP//


extern	int rxprerx80_buffer_tail3 ;
extern int rx_buffer_head3;
extern		int Rx80BufferHead;
extern		int Rx80BufferTail;
extern 	unsigned char Rx80Buffer[];

//send a char
#if EXAMPLEXBEEONLYFORZHP>0

long CntStopOld = 0;
long CntStopCur = 0;
//unsigned char FlagXbeeLinshi =0 ;
unsigned long TimeusLinshi = 0;
//extern uint32_t TimemsArray[];
extern volatile unsigned long timer0_overflow_count;
//extern volatile unsigned long timer0_overflow_count;
char DestMacAdd[17]="0013A200409EDCB6"; // add the mac address for the sink
packetXBee* paq_sent;
uint8_t i=0;
uint8_t destination[8];
char*  data="Test message!";
static char StrPrint[50]; 
 uint8_t broadcastSignalOnlyForZhp(char datastr[],unsigned char lendata)
{
	
   	return xbee802.sendTx64Simple(datastr,lendata,0x00000000,0x0000ffff);

//	//XBee.println("data inside Broadcast ");
//	printf("data inside Broadcast ");
//	//XBee.println(data);
//	//XBee.println(RTCbianliang.getTime());
//	paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
//	paq_sent->mode=BROADCAST;  // BroadCast; you need to update everyone !
//	paq_sent->MY_known=0;
//	paq_sent->packetID=0x52;  //Think about changing it each time you send
//	paq_sent->opt=0;
//	xbee802.hops=0;
//	xbee802.setOriginParams(paq_sent, "5678", MY_TYPE); // Think about this in the future as well
//	xbee802.setDestinationParams(paq_sent, "000000000000FFFF", data, MAC_TYPE, DATA_ABSOLUTE);
//	xbee802.sendXBee(paq_sent);
//	
//	if( !xbee802.error_TX )
//	{
//	//XBee.println("ok");
//	}
//	free(paq_sent);
//	paq_sent=NULL;
              
             
}


//char teststrzpp[]={0x7e,0x0,0x1e,0x0,0x52,0x0,0x13,0xa2,0x0,0x40,0x9e,0xdc,0xb6,
//0x0,0x52,0x1,0x23,0x0,0x56,0x78,0x54,0x65,0x73,0x74 ,0x20 ,0x6d ,0x65 ,0x73 ,0x73 ,0x61 ,0x67 ,0x65 ,0x21 ,0x7e};	//OK
//char teststrzpp[]={0x7e, 0x0, 0x0b, 0x0, 0x52, 0x0, 0x13, 0xa2, 0x0, 0x40, 0x9e, 0xdc, 0xb6, 0x0, 0xff};//WRONG
//char teststrzpp[]={0x7e,0x0,0x11,0x0,0x52,0x0,0x13,0xa2,0x0,0x40,0x9e,0xdc,0xb6,
//0x0,0x52,0x1,0x23,0x0,0x56,0x78, 0x44};//OK

//char teststrzpp[]={0x7e,0x0,0x11,0x0,0x52,0x0,0x13,0xa2,0x0,0x40,0x9e,0xdc,0xb6,
//0x0,0x52,0x1,0x23,0x0, 0x12};//OK
//char teststrzpp[]={0x7e,0x0,0xb,0x0,0x52,0x0,0x13,0xa2,0x0,0x40,0x9e,0xdc,0xb6,
//0x0, 0x88};//��ʱ
//char teststrzpp[]={0x7e,0x0,0xd,0x0,0x52,0x0,0x13,0xa2,0x0,0x40,0x9e,0xdc,0xb6,
//0x0,0x52,0x1, 0x35};//OK

//char teststrzpp[]={0x7e,0x0,0xc,0x0,0x52,0x0,0x13,0xa2,0x0,0x40,0x9e,0xdc,0xb6,
//0x0,0x52, 0x36};//OK

char teststrzpp[]={0x7e,0x0,0xc,0x0,0x52,0x0,0x13,0xa2,0x0,0x40,0x9e,0xdc,0xb6,
0x0,0x53, 0x35};//OK

uint8_t sendUnicastSignalOnlyForZhp(char datastr[],unsigned char lendata,unsigned long addressH,unsigned long addressL)
{
	return xbee802.sendTx64Simple(datastr,lendata, addressH, addressL); 
}
static uint8_t RecBuffer[200];
static uint16_t RecLenWant=190;
int  RecLenFact;


static void handle_received_dataOnlyForZhp()
{
	uint8_t oldlen=190;
//	int recnum;
	uint8_t flagerr=0;
	long i;
	long offset =0;
	long sum=0;
	long k=1;
	//if( (recnum=XBee.Rx80available())>0 )
	//{
//		printf("num=%d ",recnum);

		RecLenWant = oldlen;
		//printf("RecLenWant=%d ",RecLenWant);
		flagerr=xbee802.findRxframe((char *)RecBuffer, &RecLenWant);
		if(flagerr==0)
		{
			//printf("ok");
//			printf("RecLenWant=%d ",RecLenWant);
			//��ӡ���յ�������,���а�ͷ����ַ��У��λ��
//			for(i=0;i<RecLenWant;i++)
//				printf("%2x ",RecBuffer[i]);

			//��ӡ���յ�������,���а�ͷ����ַ��У��λ��
//			for(i=0;i<RecLenWant;i++)
//				printf("%c",RecBuffer[i]);
			if(RecLenWant>14)
			{
				// ��ӡ���յ������ݹؼ�ֵ��Ҳ����ȥ����ͷ����ַ��Щ���Ǵ�����
//				for(i=14;i<(RecLenWant-1);i++)
//					printf("%c",RecBuffer[i]);
				
				//������δ�ӡ������Ǹ�100���ֽ����ݰ�������и�cnt = %8d�����Ǹ�ֵȡ������
				sum = 0;
				for(i=3;i<11;i++)
				{
					if(RecBuffer[RecLenWant-i]==0x20)break;
					sum = (RecBuffer[RecLenWant-i]-'0')*k + sum;
					k=k*10;
				}
				printf(" =%d \r\n",sum);

				
				CntStopCur = sum;
				//����õ���cnt��ֵ��ԭ����Ҫ�󷢴ΰ�cnt++���������ͨ��������ݰ��ǲ��������ģ�����ε�cnt���ϴε��ǲ����������1
				//����������ݰ������������ӡ��Rx80Buffer ���600,��Ҫ�ǿ�����Ϊ�Լ��㷨�ճ���©����������10ms�жϴ����ʱ����ɵ�©��
				if(CntStopOld!=0)
				{
					if((CntStopCur - CntStopOld)>1)
					{
						//if(Rx80BufferHead>1000)
						printf("H=%d T=%d ",Rx80BufferHead,Rx80BufferTail);
						offset = (Rx80BufferHead + RX80_BUFFER_SIZE -600)%RX80_BUFFER_SIZE;
						for(i=0; i<600;i++)
						{
							printf("%2x ",Rx80Buffer[offset]);	
							offset++;
							offset = offset %RX80_BUFFER_SIZE;
						}
						CntStopOld=0;		
					}
				}
				CntStopOld = CntStopCur;

					
								
			}
										
		}
		else
		{
			//���û���յ����õ����ݰ����Ǵ�ӡ�³�����Ϣ
//			printf("flagerr=%d ",flagerr);
//			if(flagerr==2)printf("H=%dT=%d ",Rx80BufferHead,Rx80BufferTail);

			//printf("n");

		}


//		printf("recnum=%d\r\n",recnum);
//		RecLenFact=serialReadstr(RecBuffer, RecLenWant,3);
//		printf("RecLenFact=%d\r\n",RecLenFact);
//		if((RecLenFact>0)&&(RecLenFact<100))
//		{
//			for(i=0;i<RecLenFact;i++)
//				printf("%2x ",RecBuffer[i]);
//		}


//		xbee802.treatData();
//		if( !xbee802.error_RX )
//		{
//		 // Sending answer back
//			while(xbee802.pos>0)
//			{
//				
//				XBee.println(" The whole data received is ");
//				XBee.println(xbee802.packet_finished[xbee802.pos-1]->data);
//				
//				paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee)); 
//				paq_sent->mode=UNICAST;
//				paq_sent->MY_known=0;
//				paq_sent->packetID=0x52;
//				paq_sent->opt=0; 
//				xbee802.hops=0;
//				xbee802.setOriginParams(paq_sent, "ACK", NI_TYPE);
//				while(i<4)
//				{
//					destination[i]=xbee802.packet_finished[xbee802.pos-1]->macSH[i];
//					i++;
//				}
//				while(i<8)
//				{
//					destination[i]=xbee802.packet_finished[xbee802.pos-1]->macSL[i-4];
//					i++;
//				}
//				xbee802.setDestinationParams(paq_sent, destination, data, MAC_TYPE, DATA_ABSOLUTE);
//				xbee802.sendXBee(paq_sent);
//				if( !xbee802.error_TX )
//				{
//					XBee.println("ok");
//				}
//				free(paq_sent);
//				paq_sent=NULL;
//				
//				free(xbee802.packet_finished[xbee802.pos-1]);   
//				xbee802.packet_finished[xbee802.pos-1]=NULL;
//				xbee802.pos--;
//			} 
//		}
	//}

	//delay_ms(2);    
}


void handle_received_databyRx80Buffer()
{
	uint8_t oldlen=190;
//	int recnum;
	uint8_t flagerr=0;
	long i;
	long offset =0;
	long sum=0;
	long k=1;
	//if( (recnum=XBee.Rx80available())>0 )
	//{
//		printf("num=%d ",recnum);

		RecLenWant = oldlen;
		//printf("RecLenWant=%d ",RecLenWant);
		flagerr=xbee802.findRxframeinRx80Buffer((char *)RecBuffer, &RecLenWant);
		if(flagerr==0)
		{
			//printf("ok");
//			printf("RecLenWant=%d ",RecLenWant);
			//��ӡ���յ�������,���а�ͷ����ַ��У��λ��
//			for(i=0;i<RecLenWant;i++)
//				printf("%2x ",RecBuffer[i]);

			//��ӡ���յ�������,���а�ͷ����ַ��У��λ��
//			for(i=0;i<RecLenWant;i++)
//				printf("%c",RecBuffer[i]);
			if(RecLenWant>14)
			{
				// ��ӡ���յ������ݹؼ�ֵ��Ҳ����ȥ����ͷ����ַ��Щ���Ǵ�����
//				for(i=14;i<(RecLenWant-1);i++)
//					printf("%c",RecBuffer[i]);
				
				//������δ�ӡ������Ǹ�100���ֽ����ݰ�������и�cnt = %8d�����Ǹ�ֵȡ������
				sum = 0;
				for(i=3;i<11;i++)
				{
					if(RecBuffer[RecLenWant-i]==0x20)break;
					sum = (RecBuffer[RecLenWant-i]-'0')*k + sum;
					k=k*10;
				}
				printf(" =%d \r\n",sum);

				
				CntStopCur = sum;
				//����õ���cnt��ֵ��ԭ����Ҫ�󷢴ΰ�cnt++���������ͨ��������ݰ��ǲ��������ģ�����ε�cnt���ϴε��ǲ����������1
				//����������ݰ������������ӡ��Rx80Buffer ���600,��Ҫ�ǿ�����Ϊ�Լ��㷨�ճ���©����������10ms�жϴ����ʱ����ɵ�©��
				if(CntStopOld!=0)
				{
					if((CntStopCur - CntStopOld)>1)
					{
						//if(Rx80BufferHead>1000)
						printf("H=%d T=%d ",Rx80BufferHead,Rx80BufferTail);
						offset = (Rx80BufferHead + RX80_BUFFER_SIZE -600)%RX80_BUFFER_SIZE;
						for(i=0; i<600;i++)
						{
							printf("%2x ",Rx80Buffer[offset]);	
							offset++;
							offset = offset %RX80_BUFFER_SIZE;
						}
						CntStopOld=0;		
					}
				}
				CntStopOld = CntStopCur;					
			}
										
		}
		else
		{
			//���û���յ����õ����ݰ����Ǵ�ӡ�³�����Ϣ
//			printf("flagerr=%d ",flagerr);
//			if(flagerr==2)printf("H=%dT=%d ",Rx80BufferHead,Rx80BufferTail);

			//printf("n");

		}






	//delay_ms(2);    
}




void handlerecandbroadcastOnlyForZhp(void)
{
	 

	uint8_t oldlen=190;
//	int recnum;
	uint8_t flagerr=0;
	long i;
	long offset =0;
	long sum=0;
	long k=1;
	//if( (recnum=XBee.Rx80available())>0 )
	//{
//		printf("num=%d ",recnum);

		RecLenWant = oldlen;
		//printf("RecLenWant=%d ",RecLenWant);
		flagerr=xbee802.findRxframe((char *)RecBuffer, &RecLenWant);
		if(flagerr==0)
		{
			printf("ok");
			printf("RecLenWant=%d ",RecLenWant);
//			for(i=0;i<RecLenWant;i++)
//				printf("%2x ",RecBuffer[i]);


			for(i=0;i<RecLenWant;i++)
				printf("%c",RecBuffer[i]);
//			if(RecLenWant>24)
//			{
//				RecBuffer[RecLenWant-14] = 's';
//				k=0;
//				for(i=14;i<(RecLenWant-1);i++)
//				{
//					//printf("%c",RecBuffer[i]);
//					StrPrint[k]=RecBuffer[i];
//					k++;
//				}
//				StrPrint[k]=0x00;
//				flagerr = broadcastSignal(StrPrint,strlen(StrPrint));
//				if(flagerr==0)
//					printf(" OK ");
//				else 
//					printf("err=%d",flagerr);
//					
//				sum = 0;
//				for(i=3;i<11;i++)
//				{
//					if(RecBuffer[RecLenWant-i]==0x20)break;
//					sum = (RecBuffer[RecLenWant-i]-'0')*k + sum;
//					k=k*10;
//				}
//				printf(" =%d \r\n",sum);
//
//				
//				CntStopCur = sum;
//
//				if(CntStopOld!=0)
//				{
//					if((CntStopCur - CntStopOld)>1)
//					{
//						printf("H=%d T=%d ",Rx80BufferHead,Rx80BufferTail);
//						offset = (Rx80BufferHead + RX80_BUFFER_SIZE -600)%RX80_BUFFER_SIZE;
//						for(i=0; i<600;i++)
//						{
//							printf("%2x ",Rx80Buffer[offset]);	
//							offset++;
//							offset = offset %RX80_BUFFER_SIZE;
//						}
//						CntStopOld=0;		
//					}
//				}
//				CntStopOld = CntStopCur;
//					
//			}
										
		}
		else
		{
//			printf("flagerr=%d ",flagerr);
//			if(flagerr==2)printf("H=%dT=%d ",Rx80BufferHead,Rx80BufferTail);

			//printf("n");

		}
		//delay_ms(2);

  
}




char teststrzpp1[]={0x7e,0x00,0x04,0x08,0x52,0x53,0x4c,0x06};//SL
char teststrzpp2[]={0x7e,0x00,0x04,0x08,0x52,0x53,0x48,0x0A};//SH
char teststrzpp3[]={0x7e,0x00,0x04,0x08,0x52,0x4D,0x59,0xff};//MY
char teststrzpp4[]={0x7e,0x00,0x04,0x08,0x52,0x43,0x48,0x1A};//CH




#endif


#if EXAMPLEXBEEONLYFORZHP==BTESTXBEESIMPLEONLYFORZHP


extern uint8_t  NDMacLength;
extern uint64_t NDMacAddress[10];
extern uint16_t NDMyAddress[10];


void setup()
{
	unsigned long flagbreak=0;
	int flagxbeeerr;
	//monitor_on();

	monitor_onuart3TX();
	//monitor_onuart3RX();

	muluart6init();//����һ�µ�Դ����Ҫ��Ȼ����3(1)���ò���

	RTCbianliang.ON();//����һ�µ�Դ����Ҫ��Ȼ����3(1)���ò���
//	beginSerial(115200, 3);
	beginSerial(115200, PRINTFPORT);
	delay_ms(300);
	for(uint16_t i=0;i<5;i++){
		Utils.setLED(2, 1);
		delay_ms(200);
		Utils.setLED(2, 0);
		delay_ms(200);
	}
	printf("zpp!");
//	serialWrite('3', 3);//send a char '3' by uart3
//	serialWrite('c', 3);//send a char 'c'

//	while(1)
//	{
//		serialWrite('3', 3);//send a char '3' by uart3
//		serialWrite('c', 3);//send a char 'c'
//		flagbreak++;
//		if(flagbreak==10000){Utils.setLED(0, 1);}
//		else if(flagbreak==20000){flagbreak=0;Utils.setLED(0, 0);}
//		if(flagbreak>50000)break;
//	}
	DestMacAdd[16]='\0';
	xbee802.init(XBEE_802_15_4,FREQ2_4G,PRO);
	xbee802.ON();
	delay_ms(300);
	RTCbianliang.ON(); 
	delay_ms(300);//XBee.println("xbee test");
	printf("xbee test\r\n");
	flagbreak=0;
	//������������ucast
	while(1)
	{
		flagbreak++;
		if(flagbreak>=2)flagbreak=0;
		if(flagbreak==1){monitor_onuart3TX();monitor_offuart3RX();}
		else{monitor_offuart3TX();monitor_onuart3RX();}

		printf("get own mac address");
		if((flagxbeeerr=xbee802.getOwnMac())==0)printf("machigh=%2x%2x%2x%2x maclow=%2x%2x%2x%2x "\
		,xbee802.sourceMacHigh[0],xbee802.sourceMacHigh[1],xbee802.sourceMacHigh[2],xbee802.sourceMacHigh[3]\
		,xbee802.sourceMacLow[0],xbee802.sourceMacLow[1],xbee802.sourceMacLow[2],xbee802.sourceMacLow[3]\
		);

		else printf("flagxbeeeer=%d ",flagxbeeerr);
		printf("\r\n");

		delay_ms(1000);
//
//
//		printf("get own net address");
//		if((flagxbeeerr=xbee802.getOwnNetAddress())==0)printf("=%2x%2x "\
//		,xbee802.sourceNA[0],xbee802.sourceNA[1]\
//		);
//		else printf("flagxbeeeer=%d ",flagxbeeerr);
//		printf("\r\n");
//		delay_ms(1000);
//	
//		printf("get channel");
//		if((flagxbeeerr=xbee802.getChannel())==0)printf("=%2x"\
//		,xbee802.channel\
//		);
//		else printf("flagxbeeeer=%d ",flagxbeeerr);
//		printf("\r\n");
//		delay_ms(1000);

		printf("scannetwork");
		if((flagxbeeerr=xbee802.scanNetwork())==0)printf("\r\nOK\r\n");
		else printf("flagxbeeeer=%d ",flagxbeeerr);
		printf("\r\n");
		if(NDMacLength>0)
		{	
			for(uint8_t ndi=0; ndi<NDMacLength;ndi++)
				printf(" my=%d mach=%8x L=%8x\t",NDMyAddress[ndi],(uint32_t)(NDMacAddress[ndi]>>32),(uint32_t)(NDMacAddress[ndi]));
		}

		delay_ms(5000);


//		printf("broadcast1:");
//		sprintf(StrPrint,"broadcast1: my Mac H=%2x%2x%2x%2x L=%2x%2x%2x%2x "\
//		,xbee802.sourceMacHigh[0],xbee802.sourceMacHigh[1],xbee802.sourceMacHigh[2],xbee802.sourceMacHigh[3]\
//		,xbee802.sourceMacLow[0],xbee802.sourceMacLow[1],xbee802.sourceMacLow[2],xbee802.sourceMacLow[3]\
//		);
//		flagxbeeerr = broadcastSignal(StrPrint,strlen(StrPrint));
//		if(flagxbeeerr==0)
//		{
//			printf(" ok ");
//		}
//		else printf(" wrong ");
//		printf("\r\n");
//		delay_ms(1000);
//
//		printf("ucast1:");
//		sprintf(StrPrint,"unicast1: my Mac=%2x%2x%2x%2x %2x%2x%2x%2x "\
//		,xbee802.sourceMacHigh[0],xbee802.sourceMacHigh[1],xbee802.sourceMacHigh[2],xbee802.sourceMacHigh[3]\
//		,xbee802.sourceMacLow[0],xbee802.sourceMacLow[1],xbee802.sourceMacLow[2],xbee802.sourceMacLow[3]\
//		);
//	   	flagxbeeerr = sendUnicastSignal(StrPrint,strlen(StrPrint),0x0013a200,0x409edcb6);
//		if(flagxbeeerr==0)
//		{
//			printf(" ok ");
//		}
//		else printf(" wrong ");
//		printf("\r\n");
//		delay_ms(1000);
//
//
//		printf("broadcast2:");
//		sprintf(StrPrint,"broadcast2: my Mac H=%2x%2x%2x%2x L=%2x%2x%2x%2x "\
//		,xbee802.sourceMacHigh[0],xbee802.sourceMacHigh[1],xbee802.sourceMacHigh[2],xbee802.sourceMacHigh[3]\
//		,xbee802.sourceMacLow[0],xbee802.sourceMacLow[1],xbee802.sourceMacLow[2],xbee802.sourceMacLow[3]\
//		);
//		flagxbeeerr = broadcastSignal(StrPrint,strlen(StrPrint));
//		if(flagxbeeerr==0)
//		{
//			printf(" ok ");
//		}
//		else printf(" wrong ");
//		printf("\r\n");
//		delay_ms(1000);
//
//		printf("ucast2:");
//		sprintf(StrPrint,"unicast2: my Mac=%2x%2x%2x%2x %2x%2x%2x%2x "\
//		,xbee802.sourceMacHigh[0],xbee802.sourceMacHigh[1],xbee802.sourceMacHigh[2],xbee802.sourceMacHigh[3]\
//		,xbee802.sourceMacLow[0],xbee802.sourceMacLow[1],xbee802.sourceMacLow[2],xbee802.sourceMacLow[3]\
//		);
//	   	flagxbeeerr = sendUnicastSignal(StrPrint,strlen(StrPrint),0x0013a200,0x409c6c6a);
//		if(flagxbeeerr==0)
//		{
//			printf(" ok ");
//		}
//		else printf(" wrong ");
//		printf("\r\n");
//		delay_ms(1000);
//
//
//
//		delay_ms(6000);
	}
	//���ֻ�Ǽ򵥵İѽ��յĴ�ӡ��������
	while(1)
	handle_received_dataOnlyForZhp();

}


void loop()
{
    delay_ms(3000);
}

#endif


#if EXAMPLEXBEEONLYFORZHP==BTESTXBEESENDFASTBROADCASTONLYFORZHP
//������ǵ����ķ�һ���㲥���ݣ��������ݵ�ʱ�򶼲���MY��ֱ����֮ǰ��ΪΪ0xffff����������Ĳ�������Ϊ�����ķ�һ�������ȴ�xbee�Ļ�����Ȼ���ٷ�һ������
//���Ե����ݰ���ԼΪ42���ֽڣ��ڷ���ȥ��42���ֽڵȴ�xbee����ʱ����ԼΪ6ms(5-6ms)�� 
//������ʱ��Ϊ (1/115200)*10*(42+7) = 4.3ms
//һ���ֽ� һ����Ҫ10������λ����ʼ1λ������8λ��ֹͣ1λ��  ����(1/115200)*10 .
//����ȥ���������Լ��42���ֽڣ����յ���TX�Ļ�����֡����Ϊ7λ�����Դ������е�����Ϊ 42+7��
//����ʱ�����xbee����ʱ��Ϊ 10.3ms
//�ڹ�Ӧ���ṩ��xbee���ӣ���һ��֮���յ��İ���Լ6000��,Ҳ����ʵ���Լÿ��100����

//ע�⣺���ϵķ��㲥����ʱû����MY���������MY���ٸ�MY���������ݰ�֮���ٸĻ�MY�����������xbee��������֪������һ�׹㲥��xbee������ʱ��һ��Ϊ6*4=24ms
//��MY 8������ �ش�11������ ����MY10������ ��Ӧ����9�����ݣ� �������������ػأ������������Ĺ㲥���ݣ�Ҫ57���ַ�
//�ղ������㲥����Ϊ42�Ļ������ϻص�7�����ڼ���MY����Щ��һ��106������
//����ʱ��Ϊ�� (1/115200)*10*106 s + 24 ms= 9.2 ms + 24 ms = 34.2 ms
//����㲥����ʱ��Ϊ 1000/34.2 = 29	�� ÿ��


//���������ϵļ��㷽������Ȼ��֪����100���ֽڹ㲥ʱ��xbee�����Ƕ��٣��ٶ����������6ms����ôһ����ʱ��Ϊ
// (1/115200)*10*(57+107) s + 24 ms= 14.2 ms + 24 ms = 38.2 ms
// 1000/38.2 = 26	�� ÿ��

//����ʵ���������Ϊ100���ֽڵ�

//ͨ��ʵ�ʲ������������Ǹ�MY�ģ�60���Լ3300�������ȴ�xbee������ʱ��Ϊ8ms
//�����£� ����(1/115200)*10*(107)s + 8ms = 9.2ms + 8ms = 17.2ms
//1000/17.2 = 58��ÿ�룬����� 3300/60 = 55��ÿ�� ��һ�µ�

//�ѹ㲥�������������MY������Ϊ0xffff��Ȼ��������Ϊԭ�ȵ�ֵ���ָ�  �� û����MY�Ǹ��� ʵ�⣬
//�㲥���͵�ʱ��ȴ�XBee����8ms	 ����MYΪ0xffffʱ��xbee������2ms
//60���յ�2468����	��ÿ��41����   1/41 = 24.3 ms
//���� (1/115200)*10*(107 + 19*2)s + (8+2+2)ms = 12.6ms + 12ms = 24.6ms
//1000/24.6= 40	��ÿ�룬��һ�µ�
//

void setup()//
{
	unsigned long flagbreak=0;
	int flagxbeeerr;
	unsigned long cntsend=0;
	monitor_onuart3TX();
	muluart6init();//����һ�µ�Դ����Ҫ��Ȼ����3(1)���ò���
	Mux_poweron(); //����һ����Դ���������õģ������ӡ����

	beginSerial(115200, PRINTFPORT);
	delay_ms(300);
	for(uint16_t i=0;i<5;i++){
		Utils.setLED(2, 1);
		delay_ms(200);
		Utils.setLED(2, 0);
		delay_ms(200);
	}
	printf("zpp!");//
	DestMacAdd[16]='\0';//
	xbee802.init(XBEE_802_15_4,FREQ2_4G,PRO);
	xbee802.ON();
	delay_ms(300);
	RTCbianliang.ON(); 
	delay_ms(300);//XBee.println("xbee test");
	printf("xbee test\r\n");

	printf("get own mac address");
	if((flagxbeeerr=xbee802.getOwnMac())==0)printf("machigh=%2x%2x%2x%2x maclow=%2x%2x%2x%2x "\
	,xbee802.sourceMacHigh[0],xbee802.sourceMacHigh[1],xbee802.sourceMacHigh[2],xbee802.sourceMacHigh[3]\
	,xbee802.sourceMacLow[0],xbee802.sourceMacLow[1],xbee802.sourceMacLow[2],xbee802.sourceMacLow[3]\
	);
	else printf("flagxbeeeer=%d ",flagxbeeerr);
	printf("\r\n");
	delay_ms(1000);

	flagbreak=0;

	xbee802.setOwnNetAddress(0x00,0x00);

	//������������broadcast
	while(1)
	{

//		sprintf(StrPrint,"0=%8d1=%8d2=%8d3=%8d4=%8d5=%8dtm=%8dcnt=\r\n%8d\t"\
//		,TimemsArray[0],TimemsArray[1],TimemsArray[2],TimemsArray[3],TimemsArray[4],TimemsArray[5]\
//		,TimeusLinshi\
//		,cntsend
//		);


		sprintf(StrPrint,"tm=%8dcnt=\r\n%8d\t"\
		//,TimemsArray[0],TimemsArray[1],TimemsArray[2],TimemsArray[3],TimemsArray[4],TimemsArray[5]\
		
		,TimeusLinshi\
		,cntsend
		);

		flagxbeeerr = broadcastSignalOnlyForZhp(StrPrint,strlen(StrPrint));
		if(flagxbeeerr==0)
		{
			printf(" ok ");
		}
		else printf(" wrong ");
		printf("\r\n");
		cntsend++;
		//XBee.print("hahha");
		//delay_ms(500);
	}
}


void loop()
{
    delay_ms(3000);
}

#endif

#if EXAMPLEXBEEONLYFORZHP==BTESTXBEESENDFASTUNICASTONLYFORZHP

//����ʵ���������Ϊ100���ֽڵ�	UNICAST
//��UNICAST�������������MY���еģ�
//һ��һ����
//�Է�xbee�ǲ��ڹ�Ӧ���ṩ��ģ�����棨Ҳ����˵�����xbee�ȽϿ��У�,���ڷ��͵�ʱ��ȴ�XBee��9ms	 ����MYΪ0xffffʱ��xbee������2ms
//60���յ�2422����	��ÿ��40����   1/40 = 25 ms
//���� (1/115200)*10*(107 + 19*2)s + (9+2+2)ms = 12.6ms + 12ms = 25.6ms
//1000/24.6= 39	��ÿ�룬��һ�µ�
//

//һ�Զ����ͣ�Ҳ�����ȷ���һ��xbeeģ�飬�ٷ�����һ��xbeeģ���ϣ�����ģ�鶼�����ߵģ����������͵İ������������һ�£�Ҳ�Ǵ�Լÿ��40����


//һ�Զ����ͣ�Ҳ�����ȷ���һ��xbeeģ�飬�ٷ�����һ��xbeeģ���ϣ�����ģ���и������ߵģ�
//60�� 1840��	��Լ30��ÿ��
//���ڲ����ߵ��Ǹ�xbee�������ڷ�TX��xbee�ȴ�xbee�ظ�ʱ������15ms��ʱ��
//����������ʱ�䣬һ��������xbee��һ��������xbee ((1/115200)*10*(107 + 19*2)s + (2+2)ms)*2 + 9ms +25ms = 67.2ms
//1000/(67.2/2) = 29��ÿ��

//����һ���ͣ�Ҳ��������xbeeͬʱ��һ��xbeeģ�鷢�Ͷ���������xbee�����ٶ��������֣�������ϵ����֡�
//�Խ��յ��Ǹ�xbeeģ�飬ֻ�����ڽ��տڵ����ݣ����ó���������֣�,
//��һ��һ���͵�ʱ��֮������û�ж������������Ҳ��������Ϊxbee�����ٶ�Ϊ250000,���ڲ�������115200����ԼΪ���ߵ�һ�룬���Զ���������˵�����ڵ��ٶȽϵͣ����Դ������
//������1ʱ���������еİ���������һ��һ���������ӽ��ܵĴ��ڿ������кܶ��û�н��յ��������ʴ�Լ��1/3�����ӣ����1/3�����ϸ�ļ��ģ����Ǵ�ſ���3�����͵�����ÿ����Լʮ�������������и�����5�������и���2����ʲô��

//��A�巢�͵�����B��ʱ��ÿ100ms��һ�Σ���B��ͬʱ���͵�����C��(�����ʱ�䷢��) ,��������û�й����� 
//��C�崮�ڽ��տ�ֱ�ӿ����ܿڣ����Կ�����B���C������ݰ��������Ǻ����صģ��ӵ�11����133������������C���ֻ��40���յ���
//�ڷ�������ʱ��ⳬʱ��λ100ms��
//�������Ҳ������ζ�ţ���ת�����ͱ��벻©�������������֮���

void setup()
{
	unsigned long flagbreak=0;
	int flagxbeeerr;
	unsigned long cntsend=0;
	monitor_onuart3TX();
	muluart6init();//����һ�µ�Դ����Ҫ��Ȼ����3(1)���ò���
	RTCbianliang.ON();//����һ�µ�Դ����Ҫ��Ȼ����3(1)���ò���
	beginSerial(115200, PRINTFPORT);
	delay_ms(300);
	for(uint16_t i=0;i<5;i++){
		Utils.setLED(2, 1);
		delay_ms(200);
		Utils.setLED(2, 0);
		delay_ms(200);
	}
	printf("zpp!");
	DestMacAdd[16]='\0';
	xbee802.init(XBEE_802_15_4,FREQ2_4G,PRO);
	xbee802.ON();
	delay_ms(300);
	RTCbianliang.ON(); 
	delay_ms(300);//XBee.println("xbee test");
	printf("xbee test\r\n");

	printf("get own mac address");
	if((flagxbeeerr=xbee802.getOwnMac())==0)printf("machigh=%2x%2x%2x%2x maclow=%2x%2x%2x%2x "\
	,xbee802.sourceMacHigh[0],xbee802.sourceMacHigh[1],xbee802.sourceMacHigh[2],xbee802.sourceMacHigh[3]\
	,xbee802.sourceMacLow[0],xbee802.sourceMacLow[1],xbee802.sourceMacLow[2],xbee802.sourceMacLow[3]\
	);
	else printf("flagxbeeeer=%d ",flagxbeeerr);
	printf("\r\n");
	delay_ms(1000);

	flagbreak=0;

	xbee802.setOwnNetAddress(0x00,0x00);

	//������������ucast
	while(1)
	{

//		sprintf(StrPrint,"0=%8d1=%8d2=%8d3=%8d4=%8d5=%8dtm=%8d cnC=%8d\r\n"\
//		,TimemsArray[0],TimemsArray[1],TimemsArray[2],TimemsArray[3],TimemsArray[4],TimemsArray[5]\
//		,TimeusLinshi\
//		,cntsend
//		);
//		flagxbeeerr = sendUnicastSignal(StrPrint,strlen(StrPrint),0x0013a200,0x409edcb6);;
//		if(flagxbeeerr==0)
//		{
//			printf(" ok ");
//		}
//		else printf(" wrong ");
//		printf("\r\n");
//		cntsend++;


//		sprintf(StrPrint,"0=%8d1=%8d2=%8d3=%8d4=%8d5=%8dtm=%8dcnt=\r\n%8d\t"\
//		,TimemsArray[0],TimemsArray[1],TimemsArray[2],TimemsArray[3],TimemsArray[4],TimemsArray[5]\
//		,TimeusLinshi\
//		,cntsend
//		);

		sprintf(StrPrint,"tm=%8dcnt=\r\n%8d\t"\
		,TimeusLinshi\
		,cntsend
		);
		flagxbeeerr = sendUnicastSignalOnlyForZhp(StrPrint,strlen(StrPrint),0x0013a200,0x40710845);
		if(flagxbeeerr==0)
		{
			printf(" ok ");
		}
		else printf(" wrong ");
		printf("\r\n");
		cntsend++;
		//delay_ms(100);

		//XBee.print("hahha");
	}
}


void loop()
{
    delay_ms(3000);
}

#endif


#if EXAMPLEXBEEONLYFORZHP==BTESTXBEERECONLYFORZHP


void setup()
{
	unsigned long flagbreak=0;
	int flagxbeeerr;
	unsigned long cntsend=0;
	//monitor_on();

	monitor_onuart3TX();
	//monitor_onuart3RX();

	muluart6init();//����һ�µ�Դ����Ҫ��Ȼ����3(1)���ò���

	RTCbianliang.ON();//����һ�µ�Դ����Ҫ��Ȼ����3(1)���ò���
//	beginSerial(115200, 3);
	beginSerial(115200, PRINTFPORT);
	delay_ms(300);
	for(uint16_t i=0;i<5;i++){
		Utils.setLED(2, 1);	Utils.setLED(0, 1);
		delay_ms(200);
		Utils.setLED(2, 0);Utils.setLED(0, 0);
		delay_ms(200);
	}
	Timer2_Init(10,1000);//200ms
	printf("zpp!");
	DestMacAdd[16]='\0';
	xbee802.init(XBEE_802_15_4,FREQ2_4G,PRO);
	xbee802.ON();
	delay_ms(10);
	RTCbianliang.ON(); 
	delay_ms(10);//XBee.println("xbee test");
	printf("xbee test\r\n");

	printf("get own mac address");
	if((flagxbeeerr=xbee802.getOwnMac())==0)printf("machigh=%2x%2x%2x%2x maclow=%2x%2x%2x%2x "\
	,xbee802.sourceMacHigh[0],xbee802.sourceMacHigh[1],xbee802.sourceMacHigh[2],xbee802.sourceMacHigh[3]\
	,xbee802.sourceMacLow[0],xbee802.sourceMacLow[1],xbee802.sourceMacLow[2],xbee802.sourceMacLow[3]\
	);
	else printf("flagxbeeeer=%d ",flagxbeeerr);
	printf("\r\n");
	//delay_ms(1000);

	flagbreak=0;
	//������������ucast
	while(1)
	{
		//flagxbeeerr=handle1msprerx80();
//
//				if(flagxbeeerr==0)printf("A ");
//				else printf("%c ",flagxbeeerr+'A');
//
//				if(flagxbeeerr==2)printf("h=%dt=%d ",rx_buffer_head3,rxprerx80_buffer_tail3);
		//delay_ms(100);
		handle_received_dataOnlyForZhp();
	}


}


void loop()
{
    delay_ms(3000);
}

#endif




//һ��xbeeA�㲥��ͣ�ķ���100���ֽڣ��Ǹ�����������MY�ģ����ٶȴ�ԼΪ40��ÿ��
//��һ��xbeeBֻ�ܽ��գ����յ�������һ��0x80RX��ʱ���ʹ�ӡ������	��ӡ��%c��ӡ�ģ�
//        ע�⣺���%2x��ռ�ñȽ϶��ʱ�䣬�ȴ���ӡ���ˣ��ͻᷢ�ִ��ڻ��������泬��100���ֽڣ�Ҳ����һ����������ݣ�
//              ������ǰ���εİ�������ȷ�����������һ����ʱ�򣬾ͽ������ɹ���Ȼ������У��������һ��ʱ������У������0x7e�ˣ���������ȷ��������Ȼ��ѭ��
//              ����%2x ��ӡ��©��
//�ó����ն˱����˴�Լ1���ӵ�B��ӡ���������Լ2400������������Щ��û��©���������Ҳ����˵������ ���ն�����Ϊ0%
//
//�����%2x�����Ҳ˵���ˣ����A��ͣ�ķ������ݣ�40��ÿ�룩��B���Ҫת���Ļ����ܿ��ܻ�ת�����ɹ�����©�����أ�
//������ο���ת�����Ҫ�ú�����

//����ֱ�ӽ��մ���#if EXAMPLEXBEE==BTESTXBEEREC�� ����xbee.read()  �� ��Rx80Buffer�������XBee.Rx80read()��������γ���
//�����յ�һ��������ӡ�㲥���͵Ĵ���cnt=%8d�Ǹ����ݰ�ʱ����ӡ���Ǹ�cntֵ
//���ֲ�������ֱͨ�ӽ��ջ���Rx80Buffer������� ����һ���ӣ����ܹ��յ��㲥�����а� Ҳ����˵������Ϊ0

//����Ĵ������İ�����Rx80Buffer������� ����һ���ӣ�������Ҳ��Ϊ0
#if EXAMPLEXBEEONLYFORZHP==BTESTXBEERECBYRx80Buffer


void setup()
{
	unsigned long flagbreak=0;
	int flagxbeeerr;
	unsigned long cntsend=0;
	//monitor_on();

	monitor_onuart3TX();
	//monitor_onuart3RX();

	muluart6init();//����һ�µ�Դ����Ҫ��Ȼ����3(1)���ò���

	RTCbianliang.ON();//����һ�µ�Դ����Ҫ��Ȼ����3(1)���ò���
//	beginSerial(115200, 3);
	beginSerial(115200, PRINTFPORT);
	delay_ms(300);
	for(uint16_t i=0;i<5;i++){
		Utils.setLED(2, 1);	Utils.setLED(0, 1);
		delay_ms(200);
		Utils.setLED(2, 0);Utils.setLED(0, 0);
		delay_ms(200);
	}
	Timer2_Init(10,1000);//200ms
	printf("zpp!");
	DestMacAdd[16]='\0';
	xbee802.init(XBEE_802_15_4,FREQ2_4G,PRO);
	xbee802.ON();
	delay_ms(10);
	RTCbianliang.ON(); 
	delay_ms(10);//XBee.println("xbee test");
	printf("xbee test\r\n");

	printf("get own mac address");
	if((flagxbeeerr=xbee802.getOwnMac())==0)printf("machigh=%2x%2x%2x%2x maclow=%2x%2x%2x%2x "\
	,xbee802.sourceMacHigh[0],xbee802.sourceMacHigh[1],xbee802.sourceMacHigh[2],xbee802.sourceMacHigh[3]\
	,xbee802.sourceMacLow[0],xbee802.sourceMacLow[1],xbee802.sourceMacLow[2],xbee802.sourceMacLow[3]\
	);
	else printf("flagxbeeeer=%d ",flagxbeeerr);
	printf("\r\n");
	//delay_ms(1000);

	flagbreak=0;
	//������������ucast
	while(1)
	{
		//flagxbeeerr=handle1msprerx80();
//
//				if(flagxbeeerr==0)printf("A ");
//				else printf("%c ",flagxbeeerr+'A');
//
//				if(flagxbeeerr==2)printf("h=%dt=%d ",rx_buffer_head3,rxprerx80_buffer_tail3);
		//delay_ms(100);
		handle_received_databyRx80Buffer();
	}


}


void loop()
{
    delay_ms(3000);
}

#endif












#if EXAMPLEXBEEONLYFORZHP==BTESTXBEERECTHENFASTBROADCASTONLYFORZHP


void setup()
{
	unsigned long flagbreak=0;
	int flagxbeeerr;
	unsigned long cntsend=0;
	//monitor_on();

	monitor_onuart3TX();
	//monitor_onuart3RX();

	muluart6init();//����һ�µ�Դ����Ҫ��Ȼ����3(1)���ò���

	RTCbianliang.ON();//����һ�µ�Դ����Ҫ��Ȼ����3(1)���ò���
//	beginSerial(115200, 3);
	beginSerial(115200, PRINTFPORT);
	delay_ms(300);
	for(uint16_t i=0;i<5;i++){
		Utils.setLED(2, 1);	Utils.setLED(0, 1);
		delay_ms(200);
		Utils.setLED(2, 0);Utils.setLED(0, 0);
		delay_ms(200);
	}
	Timer2_Init(10,1000);//200ms
	printf("zpp!");
	DestMacAdd[16]='\0';
	xbee802.init(XBEE_802_15_4,FREQ2_4G,PRO);
	xbee802.ON();
	delay_ms(10);
	RTCbianliang.ON(); 
	delay_ms(10);//XBee.println("xbee test");
	printf("xbee test\r\n");

	printf("get own mac address");
	if((flagxbeeerr=xbee802.getOwnMac())==0)printf("machigh=%2x%2x%2x%2x maclow=%2x%2x%2x%2x "\
	,xbee802.sourceMacHigh[0],xbee802.sourceMacHigh[1],xbee802.sourceMacHigh[2],xbee802.sourceMacHigh[3]\
	,xbee802.sourceMacLow[0],xbee802.sourceMacLow[1],xbee802.sourceMacLow[2],xbee802.sourceMacLow[3]\
	);
	else printf("flagxbeeeer=%d ",flagxbeeerr);
	printf("\r\n");
	//delay_ms(1000);

	flagbreak=0;
	//������������ucast
	while(1)
	{
		//flagxbeeerr=handle1msprerx80();
//
//				if(flagxbeeerr==0)printf("A ");
//				else printf("%c ",flagxbeeerr+'A');
//
//				if(flagxbeeerr==2)printf("h=%dt=%d ",rx_buffer_head3,rxprerx80_buffer_tail3);
		//delay_ms(100);
		handlerecandbroadcastOnlyForZhp();
	}


}


void loop()
{
    delay_ms(3000);
}

#endif//BTESTXBEERECTHENFASTBROADCAST




























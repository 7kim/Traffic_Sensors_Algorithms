#include "dingke_i2c.h"
#include "dingke_delay.h"
#include "string.h"
#include "dingke_uart.h"
//#include "sysclkchange.h"
//////////////////////////////////////////////////////////////////////////////////	 
// �ⲿRTC  EEPROM  ��ع���оƬ ����һ��i2c����	iic��ͷ����
// MLX90614(SMBUS)��һ��I2C����						   smbus��ͷ����
////////////////////////////////////////////////////////////////////////////////// 	  

//��ʼ��IIC
GPIO_InitTypeDef GPIO_InitStructure;

void i2cOn(void)//PE10
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10  ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOE,GPIO_Pin_10);
}

void i2cOff(void)//PE15
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10  ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOE,GPIO_Pin_10);
}

void i2cInit(void)
{					     
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
    //I2C_SCL PB.8   I2C_SDA PB.9 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

   // I2C PE5 PE6 PE10 
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
			
	  GPIO_SetBits(GPIOB,GPIO_Pin_8);//SCL  
	  GPIO_SetBits(GPIOB,GPIO_Pin_9);//SDA

}

//����IIC��ʼ�ź�
void i2cStart(void)
{
	SDA_OUT();    //sda�����
	GPIO_SetBits(GPIOB,GPIO_Pin_9);//SDA  	  
	GPIO_SetBits(GPIOB,GPIO_Pin_8); //SCL 
	delay_us(4);
 	GPIO_ResetBits(GPIOB,GPIO_Pin_9); //SDA  //START:when CLK is high,DATA change form high to low 
	delay_us(4);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8); //SCL //ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void i2cStop(void)
{
	SDA_OUT();//sda�����
	GPIO_ResetBits(GPIOB,GPIO_Pin_8); //SCL 
	GPIO_ResetBits(GPIOB,GPIO_Pin_9); //SDA //STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	GPIO_SetBits(GPIOB,GPIO_Pin_8); //SCL 
 	delay_us(4);	
	GPIO_SetBits(GPIOB,GPIO_Pin_9);//SDA  //����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��false������Ӧ��ʧ��
//        true������Ӧ��ɹ�
int i2cWait_Ack(void)
{
	uint8_t  ucErrTime=0;

	SDA_OUT(); 
	GPIO_SetBits(GPIOB,GPIO_Pin_9);//SDA  
	delay_us(2);
	SDA_IN();     //SDA����Ϊ����  		   
	GPIO_SetBits(GPIOB,GPIO_Pin_8); //SCL 
	delay_us(2);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			i2cStop();
			return I2CFALSE;
		}
	}
	GPIO_ResetBits(GPIOB,GPIO_Pin_8); //SCL //ʱ�����0 	   
	return I2CTRUE;  
} 
//����ACKӦ��
void i2cAck(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_8); //SCL 
	SDA_OUT();
	GPIO_ResetBits(GPIOB,GPIO_Pin_9); //SDA 
	delay_us(2);
	GPIO_SetBits(GPIOB,GPIO_Pin_8); //SCL 
	delay_us(2);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8); //SCL 
}
//������ACKӦ��		    
void i2cNAck(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_8); //SCL 
	SDA_OUT();
	GPIO_SetBits(GPIOB,GPIO_Pin_9);//SDA  
	delay_us(2); 
	GPIO_SetBits(GPIOB,GPIO_Pin_8); //SCL 
	delay_us(2); 
	GPIO_ResetBits(GPIOB,GPIO_Pin_8); //SCL 
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void i2cSend_Byte(uint8_t  txd)
{                        
    uint8_t  t;   
	 SDA_OUT(); 	    
    GPIO_ResetBits(GPIOB,GPIO_Pin_8); //SCL //����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {   
     if(txd&0x80) 
      GPIO_SetBits(GPIOB,GPIO_Pin_9);		
      else
	  GPIO_ResetBits(GPIOB,GPIO_Pin_9);		
       // IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		GPIO_SetBits(GPIOB,GPIO_Pin_8); //SCL 
		delay_us(2); 
		GPIO_ResetBits(GPIOB,GPIO_Pin_8); //SCL 	
		delay_us(2); 
    }	 
} 	  

int IICSendByteAck(uint8_t txd)
{
	i2cSend_Byte(txd);	   //����д����
	if(i2cWait_Ack()==I2CTRUE)return I2CTRUE;
	else return I2CFALSE;
}


  
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t  i2cRead_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        GPIO_ResetBits(GPIOB,GPIO_Pin_8); //SCL  
        delay_us(2);
		GPIO_SetBits(GPIOB,GPIO_Pin_8); //SCL 
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        i2cNAck();//����nACK
    else
        i2cAck(); //����ACK   
    return receive;
}


void writeprotection(int flag)
{
	if(flag==IICPROTECTON)GPIO_SetBits(GPIOE,GPIO_Pin_11);
	else GPIO_ResetBits(GPIOE,GPIO_Pin_11);
}

void softwarereset (void)
{
	uint8_t i;
	for(i=0;i<9;i++)
	{
		i2cStart();	
	}
}












///////////////////////////////////////////////////////////////////////////////////////////////////
// �ⲿRTC
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//data write -slave receiver mode
//		  slavesddress(r)               word address      data n            data n+1       ...      data n+x 
//host         host           device    host   device     host   device     host   device        host  device       host 
//start        0xD0           ack       xxxxxxxx ack      xxxxxxxx ack      xxxxxxxx ack  	     xxxxxxxx ack       stop

//data read -slave transmitter mode
//		  slavesddress(w)               data n           data n+1    ...      data n+x 
//host         host           device    device   host    device   host 		  device   host      host 
//start        0xD1           ack       xxxxxxxx ack     xxxxxxxx ack    	  xxxxxxxx Nack  	 stop

//data write/read(write pointer, then read) -slave receiver and transmit
//		  slavesddress(w)               word address                   slave address(r)         data n            data n+1       ...     data n+x 
//host         host           device    host   device     host         host           device    device   host     device   host          device   host 	  host   
//start        0xD0           ack       xxxxxxxx ack      start        0xD1           ack       xxxxxxxx ack      xxxxxxxx ack  	     xxxxxxxx Nack       stop


//��Χ
//seconds 0-59
//minutes 0-59
//hour  1-12 am/pm   0-23	//���������24Сʱ�Ƶ�
//day 1-7
//date 1-31
//month 1-12
//year 0-99
static const uint8_t MaxRtcValue[7]={59,59,23, 7,31,12,99};
static const uint8_t MinRtcValue[7]={ 0, 0, 0, 1, 1, 1, 0};
union RTCUNION RTCExternalUn;
char RTCExternalStamp[60];
 const char DAY_s[7][4]={"Sun","Mon","Tue" ,"Wed","Thu","Fri","Sat"};
int readExternalRTC (unsigned char address)
{	
	uint8_t temp=0;
	
	i2cStart(); //�ȷ�������
	if(IICSendByteAck(SLAVEADDRTC)==I2CFALSE)return I2CFALSE; //�����豸��ַ(0) ���ȴ��豸Ӧ��
	if(IICSendByteAck((uint8_t)(address&0x00ff))==I2CFALSE)return I2CFALSE;//����RTC�������ĵ�ַ������ʱ�������ʷֻ���������Щ //���ȴ��豸Ӧ��
	i2cStart(); //���·�������
	
	if(IICSendByteAck(SLAVEADDRTC+1)==I2CFALSE)return I2CFALSE;//�����豸��ַ(1) ���ȴ��豸Ӧ��	
		 										  		    		    	   
    temp=i2cRead_Byte(0);//�����豸������һ���ֽڣ���Ӧ���豸	,��ΪֻҪ����һ���������������豸Ӧ��Ϊ1 	   
    i2cStop();//����ֹͣ	  
	return temp;   
}
int writeExternalRTC (unsigned char address, uint8_t value)
{	
    i2cStart();//�������� 
	if(IICSendByteAck(SLAVEADDRTC)==I2CFALSE)return I2CFALSE;//�����豸��ַ(0) ���ȴ��豸Ӧ��			
	if(IICSendByteAck((uint8_t)(address&0x00ff))==I2CFALSE)return I2CFALSE;//����RTC�������ĵ�ַ��//���ȴ��豸Ӧ��	
	if(IICSendByteAck(value))return I2CFALSE; //���;���Ҫ�ĵ�ֵ��//���ȴ��豸Ӧ��		  		    	   
    i2cStop();//����ֹͣ
	delay_ms(10);	 
	return I2CTRUE;	
} 
uint8_t bcdtobyte(uint8_t bcd)
{
	return ((bcd>>4)*10+ (bcd&0x0f));
}

uint8_t bytetobcd(uint8_t abyte)
{
	return 	((((abyte/10)%10)<<4)|((abyte%10)&0x0f));
}

void getExternalTimestamp() 
{
//  free(timeStamp);
//  timeStamp=NULL;
//  timeStamp=(char*)calloc(31,sizeof(char)); 
//  sprintf (timeStamp, "%s, %02d/%02d/%02d - %02d:%02d:%02d", DAY_s[day-1], year, month, date, hour, minute, second);


//  return RTCExternalStamp;
}

int getExternalTime(void)
{
	uint8_t i;
	int zhi;
	for(i=0;i<7;i++)
	{
		zhi = readExternalRTC(i);
		if(zhi==I2CFALSE) return I2CFALSE;
		RTCExternalUn.unionstr[i]=	bcdtobyte(zhi);		
	}

//	if(RTCExternalUn.structv.wday==0)RTCExternalUn.structv.wday=1;
//	if(RTCExternalUn.structv.wday>7)RTCExternalUn.structv.wday=7;
	//RTCExternalStamp[20]=0x00;RTCExternalStamp[21]=0x00;RTCExternalStamp[22]=0x00;RTCExternalStamp[23]=0x00;
	sprintf (RTCExternalStamp, "%s, %d/%02d/%02d - %02d:%02d:%02d", DAY_s[RTCExternalUn.structv.day-1]
	, RTCExternalUn.structv.year
	, RTCExternalUn.structv.month
	, RTCExternalUn.structv.date
	, RTCExternalUn.structv.hour
	, RTCExternalUn.structv.minute
	, RTCExternalUn.structv.second);

	return I2CTRUE;

}

int setExternalTime(uint8_t _year, uint8_t _month, uint8_t _date, uint8_t day_week, uint8_t _hour, uint8_t _minute, uint8_t _second)
{
	uint8_t i;
	RTCExternalUn.structv.year  =(uint8_t)(_year);
	RTCExternalUn.structv.month =_month;
	RTCExternalUn.structv.date =_date;
	RTCExternalUn.structv.day   =day_week;
	RTCExternalUn.structv.hour  =_hour;
	RTCExternalUn.structv.minute=_minute;
	RTCExternalUn.structv.second=_second;

	for(i=0;i<7;i++)
	{
		if(RTCExternalUn.unionstr[i]>MaxRtcValue[i])RTCExternalUn.unionstr[i]=MaxRtcValue[i];
		else if(RTCExternalUn.unionstr[i]<MinRtcValue[i])RTCExternalUn.unionstr[i]=MinRtcValue[i];
	}
	for(i=0;i<7;i++)
	{
		
		if(writeExternalRTC(i,bytetobcd(RTCExternalUn.unionstr[i]))==I2CFALSE)return I2CFALSE;
	}
	return I2CTRUE;
}
int setExternalTimeStr(const char* timestr)
{
   	uint8_t i;
	
	RTCExternalUn.structv.year  =(timestr[5] - 48)*10+(timestr[6] - 48);
	RTCExternalUn.structv.month =(timestr[8] - 48)*10+(timestr[9] - 48);
	RTCExternalUn.structv.date  =(timestr[11] - 48)*10+(timestr[12] - 48);

	RTCExternalUn.structv.hour  =(timestr[16] - 48)*10+(timestr[17] - 48);
	RTCExternalUn.structv.minute=(timestr[19] - 48)*10+(timestr[20] - 48);
	RTCExternalUn.structv.second=(timestr[22] - 48)*10+(timestr[23] - 48);/**/


	for(i=0;i<7;i++)
	{
		if(strncmp(timestr,DAY_s[i],3)==0)
		{
			RTCExternalUn.structv.day   =i+1;
			break;	
		}
	}
	for(i=0;i<7;i++)
	{
		if(RTCExternalUn.unionstr[i]>MaxRtcValue[i])RTCExternalUn.unionstr[i]=MaxRtcValue[i];
		else if(RTCExternalUn.unionstr[i]<MinRtcValue[i])RTCExternalUn.unionstr[i]=MinRtcValue[i];
	}		
	
	for(i=0;i<7;i++)
	{
		
		if(writeExternalRTC(i,bytetobcd(RTCExternalUn.unionstr[i]))==I2CFALSE)return I2CFALSE;
	}
	return I2CTRUE;
}

//�������ӣ���������������ӣ���������Ҫ�ٵ���int onExternalAlarm1(void)
//type = 0 	 ÿ��һ������
//type = 1 	 ��Ӧ������ƥ��һ�����ӣ���ÿ����һ������
//type = 2 	 ��Ӧ�ķ��Ӻ�����ƥ��һ�����ӣ���ÿСʱһ������
//type = 3 	 ��Ӧ��ʱ����ƥ��һ�����ӣ���ÿ��һ������
//type = 4 	 ��Ӧ�����ڡ�ʱ���֡���ƥ��һ�����ӣ������ÿ��һ������
//type = 5 	 ��Ӧ�����ڡ�ʱ���֡���ƥ��һ�����ӣ���ÿ������һ������
// dateorday ,��type = 4��5ʱ��dateorday��Ӧ���ں�����
//Сʱ��Ҫ��24Сʱ�Ƶ�
int setExternalAlarm1(uint8_t dateorday, uint8_t hour, uint8_t minute, uint8_t second, uint8_t type)
{
	uint8_t temp;
	int flagerr;
	if(type>5)type=5;
	if(second>59)second =59;
	if(minute>59)minute=59;
	if(hour>23)hour=23;
	if((type==4)&&(dateorday>31))dateorday=31;
	else if(type==5)
	{	
		if(dateorday>7)dateorday=7;
		else if(dateorday==0)dateorday=1;

	}

	second =  bytetobcd(second);
	minute =  bytetobcd(minute);
	hour =  bytetobcd(hour);
	dateorday =  bytetobcd(dateorday);
	
	switch(type)
	{
		case 0: second |=0x80;  minute |=0x80;  hour |=0x80;  dateorday |=0x80;  break;
		case 1: second &=~0x80; minute |=0x80;  hour |=0x80;  dateorday |=0x80; break;
		case 2: second &=~0x80; minute &=~0x80; hour |=0x80;  dateorday |=0x80; break;
		case 3: second &=~0x80; minute &=~0x80; hour &=~0x80; dateorday |=0x80; break;
		case 4: second &=~0x80; minute &=~0x80; hour &=~0x80;  dateorday &=~0xc0; break;
		case 5: second &=~0x80; minute &=~0x80; hour &=~0x80; dateorday |=0x40;  dateorday &=~0x80; break;
		default: break;
	}

	if(writeExternalRTC(0x07,second)==I2CFALSE)return I2CFALSE;
	if(writeExternalRTC(0x08,minute)==I2CFALSE)return I2CFALSE;
	if(writeExternalRTC(0x09,hour)==I2CFALSE)return I2CFALSE;
	if(writeExternalRTC(0x0a,dateorday)==I2CFALSE)return I2CFALSE;

	flagerr = readExternalRTC(0x0e);
	if(flagerr==I2CFALSE)return I2CFALSE;
	temp = flagerr; 
	temp = temp|0x05;
	if(writeExternalRTC(0x0e,temp)==I2CFALSE)return I2CFALSE;

	return I2CTRUE;
}


//ֻ�ǰѵ�ǰ�������������ӹص��������ǰѵ�ǰ���õ����Ӹɵ�
int clearExternalAlarm1(void)
{
	uint8_t temp;
	int flagerr;

	flagerr = readExternalRTC(0x0f);
	if(flagerr==I2CFALSE)return I2CFALSE;
	temp = flagerr; 
	temp = temp & 0xfe;
	if(writeExternalRTC(0x0f,temp)==I2CFALSE)return I2CFALSE;

	return I2CTRUE;
}

//����û������
int offExternalAlarm1(void)
{
	uint8_t temp;
	int flagerr;
	flagerr = readExternalRTC(0x0e);
	if(flagerr==I2CFALSE)return I2CFALSE;
	temp = flagerr; 
	temp &= ~0x01;
	if(writeExternalRTC(0x0e,temp)==I2CFALSE)return I2CFALSE;

	return I2CTRUE;
}
//��������1�ж�
int onExternalAlarm1(void)
{
	uint8_t temp;
	int flagerr;

	flagerr = readExternalRTC(0x0e);
	if(flagerr==I2CFALSE)return I2CFALSE;
	temp = flagerr; 
	temp = temp|0x05;
	if(writeExternalRTC(0x0e,temp)==I2CFALSE)return I2CFALSE;

	return I2CTRUE;
}

int setExternalAlarm1AsAwake(uint8_t dateorday, uint8_t hour, uint8_t minute, uint8_t second, uint8_t type)
{
//	GPIO_InitTypeDef  GPIO_InitStructured;
//	EXTI_InitTypeDef EXTI_InitStruct;
//	NVIC_InitTypeDef NVIC_InitStruct;
//
//  	/*RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	*/
//  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
//  	GPIO_InitStructured.GPIO_Pin = GPIO_Pin_12;
//  	GPIO_InitStructured.GPIO_Mode = GPIO_Mode_IN;
//  	GPIO_InitStructured.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  	GPIO_Init(GPIOE, &GPIO_InitStructured);
//
//
//
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
//
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE ,EXTI_PinSource12 );	
//	EXTI_InitStruct.EXTI_Line = EXTI_Line12;
//	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
//	EXTI_InitStruct.EXTI_LineCmd = ENABLE;	
//	EXTI_Init(&EXTI_InitStruct);
//
//
//	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority= 12;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority= 12;
//	NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
//	NVIC_Init(&NVIC_InitStruct);
//	Timer2_Init(200,1000);
//	if(setExternalAlarm1(dateorday, hour, minute, second, type)==I2CFALSE)return I2CFALSE;
	return onExternalAlarm1();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//EEPROM
//////////////////////////////////////////////////////////////////////////////////////////////////////
//���������slaveadress ����0xa0�������������������ǲ��ǿ�����ֱ��ȥ��slaveaddress ���������
int readEeprom (uint8_t slaveadress,int address)
{	
	uint8_t temp=0;

	i2cStart(); 
	if(IICSendByteAck(slaveadress)==I2CFALSE)return I2CFALSE;
	if(IICSendByteAck(address>>8)==I2CFALSE)return I2CFALSE;//���͸ߵ�ַ
	if(IICSendByteAck((uint8_t)(address&0x00ff))==I2CFALSE)return I2CFALSE;//���͵͵�ַ
	i2cStart(); 

	if(IICSendByteAck(slaveadress+1)==I2CFALSE)return I2CFALSE;//�����ֽ�	
		 										  		    		    	   
    temp=i2cRead_Byte(0);		   
    i2cStop();//����һ��ֹͣ����	   
	return temp;   
}
int writeEeprom (uint8_t slaveadress,int address, uint8_t value)
{	
    i2cStart();  
	if(IICSendByteAck(slaveadress)==I2CFALSE)return I2CFALSE;		
	if(IICSendByteAck((uint8_t)(address>>8))==I2CFALSE)return I2CFALSE;//���͸ߵ�ַ	 	
	if(IICSendByteAck((uint8_t)(address&0x00ff))==I2CFALSE)return I2CFALSE;//���͵͵�ַ	
	if(IICSendByteAck(value))return I2CFALSE; //�����ֽ�		  		    	   
    i2cStop();//����һ��ֹͣ���� 
	delay_ms(10);
		 
	return I2CTRUE;	
} 



/////////////////////////////////////////////////////////
//���оƬ��д
// оƬ������Ϊ DS2745
//////////////////////////////////////////////////////////


u8 readDS2745(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
	i2cStart();  
	
	i2cSend_Byte(0X90);	   //����д����
	i2cWait_Ack();
	i2cSend_Byte(ReadAddr);//���͸ߵ�ַ>>8
	i2cWait_Ack();		 
	//IIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	//IIC_Wait_Ack();	    
	i2cStart();  	 	   
	i2cSend_Byte(0X91);           //�������ģʽ			   
	i2cWait_Ack();	 
	temp=i2cRead_Byte(0);		   
	i2cStop();//����һ��ֹͣ����	    
	return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void writeDS2745(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
	i2cStart();  
	
	i2cSend_Byte(0X90);	    //����д����
	i2cWait_Ack();
	i2cSend_Byte(WriteAddr);//���͸ߵ�ַ>>8
	i2cWait_Ack();		 
	
	//IIC_Send_Byte(WriteAddr%256);   //���͵͵�ַ
	//IIC_Wait_Ack(); 	 										  		   
	i2cSend_Byte(DataToWrite);     //�����ֽ�							   
	i2cWait_Ack();  		    	   
	i2cStop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}



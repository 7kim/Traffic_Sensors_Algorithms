/*
 
 */
 

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#include "dingke_delay.h"
#include "dingke_spi.h"
#endif

#define MAXCNT 500

// Constructors ////////////////////////////////////////////////////////////////

WaspFLASH::WaspFLASH()
{
   //SlaveAdress=0x00;
	  Flagaddbit=0;
	  //MaxCnt=500;
}



void WaspFLASH::setADP(void)
{
		RxBuffer[0]=0;
		AT_CS_LOW();
		SPI2_RWByte(0x15);
		RxBuffer[0]=SPI2_RWByte(Dummy);		
		AT_CS_HIGH();

		if(RxBuffer[0]&0x02){;}
		else
		{ 
			AT_CS_LOW();
			SPI2_RWByte(0xb7);		
			AT_CS_HIGH();
		}
}

unsigned char WaspFLASH::checkaddbit(void)
{
	RxBuffer[0]=0;
	AT_CS_LOW();
	SPI2_RWByte(0x15);
	RxBuffer[0]=SPI2_RWByte(Dummy);		
	AT_CS_HIGH();

	if(RxBuffer[0]&0x02){Flagaddbit=32;}
	else
	{
		Flagaddbit=24; 
	}
	return Flagaddbit;	
}

void WaspFLASH::SPI_Flash_Init(void)
{
	unsigned char i;
	SPI2_Init();
	CSPin_init();
	FLASH_SPI_Init();
	for(i=0;i<10;i++)
	{
		setADP();
		if(checkaddbit()==32)break;
	}
	if(i<10);//addbit=32 OK
		
} 
//���æ��ʱ1ms����	FLASHBUSY����æֱ�ӷ���FLASHNOTBUSY
int WaspFLASH::checkbusy(void)
{
	RxBuffer[0]=0;
	AT_CS_LOW();
	SPI2_RWByte(0x05);
	RxBuffer[0]=SPI2_RWByte(Dummy);		
	AT_CS_HIGH();
	//displaychar(TxBuffer[0]);
	if(RxBuffer[0]&0x01)//busy
	{   
		delay_ms(1);
		return FLASHBUSY; 
	}
	else //	not busy
	{ 
		//delay_ms(10);
		return FLASHNOTBUSY;
	}
}
//��дʹ��֮ǰ���ж��Ƿ�æ�������� MAXCNT����æ�򷵻�FLASHTOOBUSY
//��æ��дʹ�ܣ����� FLASHWRITEENABLEDONE
int WaspFLASH::writeEnable(void)
{
  unsigned long cntbusy;
	for(cntbusy=0;cntbusy<MAXCNT;cntbusy++)
	{
		if(checkbusy()!=FLASHBUSY)
		{
			AT_CS_LOW();
			SPI2_RWByte(0x06);//дʹ��
			AT_CS_HIGH();	
			return FLASHWRITEENABLEDONE;													
		}		
	}
	return FLASHTOOBUSY;
}

//��дʹ��֮ǰ���ж��Ƿ�æ�������� MAXCNT����æ�򷵻�FLASHTOOBUSY
//��æ��дʹ�ܣ����� FLASHWRITEDISABLEDONE
int WaspFLASH::writeDisable(void)
{
 unsigned long cntbusy;
	for(cntbusy=0;cntbusy<MAXCNT;cntbusy++)
	{
		if(checkbusy()!=FLASHBUSY)
		{
			AT_CS_LOW();
			SPI2_RWByte(0x04);//дdisable
			AT_CS_HIGH();	
			return FLASHWRITEDISABLEDONE;													
		}		
	}
	return FLASHTOOBUSY;
}


//�ܶ�����Ӧ��ַ�����ݷ��ض�������
//���æ����������MAXCNT ����FLASHBUSY����æ�����һ���ֽ�����
//������
int WaspFLASH::flashreaddata4add(long add)
{
 unsigned long cntbusy;
	for(cntbusy=0;cntbusy<MAXCNT;cntbusy++)
	{
		if(checkbusy()!=FLASHBUSY)//���Ե�ʱ��������д����æ�������ִ����д����Ϳ�ʼ�����ʱ��Ҳ��æ�ģ����Զ�д֮ǰ���ж����Ƿ�æ
		{
			TxBuffer[0]=0;
			AT_CS_LOW();
			SPI2_RWByte(0x13); //read data
			SPI2_RWByte((u8)(add>>24));
			SPI2_RWByte((u8)(add>>16));
			SPI2_RWByte((u8)(add>>8));
			SPI2_RWByte((u8)add);
			RxBuffer[0]=SPI2_RWByte(Dummy);
			AT_CS_HIGH();
			return RxBuffer[0];			
		}
	}
	return FLASHBUSY;		
}
//���������������տͻ��ṩʽ��������������ʽ��û�з���FLAHSæ��æ����Ϣ������æ��ʱ��ֻ�м򵥵ķ���0����
//����æʱ�ͷ���0 ,��æ���ض��������ݣ�
uint8_t WaspFLASH::readFlash1byte(uint32_t add)
{
	int result;
	result=flashreaddata4add(add);
	if(result<0)result=0;
	return (uint8_t)result;	
}

//����æʱ�ͷ���0 ,��æ���ض��������ݣ�
uint16_t WaspFLASH::readFlash2byte(uint32_t add)
{
	int result[2];
	result[0]=flashreaddata4add(add);
	result[1]=flashreaddata4add(add+1);
	if(result[0]<0)result[0]=0;
	if(result[1]<0)result[1]=0;
	return (((uint16_t)result[1])<<8)|((uint16_t)result[0]);
}
//����æʱ�ͷ���0 ,��æ���ض��������ݣ�
uint32_t WaspFLASH::readFlash4byte(uint32_t add)
{
	int result[4];
	result[0]=flashreaddata4add(add);
	result[1]=flashreaddata4add(add+1);
	result[2]=flashreaddata4add(add+2);
	result[3]=flashreaddata4add(add+3);

	if(result[0]<0)result[0]=0;
	if(result[1]<0)result[1]=0;
	if(result[2]<0)result[2]=0;
	if(result[3]<0)result[3]=0;
	return (((uint16_t)result[3])<<24)|(((uint16_t)result[2])<<16)|(((uint16_t)result[1])<<8)|((uint16_t)result[0]);
}
//��һ�����������ݶ���Flashbuf������飬æ�Ĵ�������MAXCNT����FLASHBUSY
int WaspFLASH::readFlashsector(uint32_t add)
{
	uint32_t i;
	//uint8_t  cntrbusy=0,maxrbusy=100;
	int result;
	unsigned long cntbusy;
	cntbusy=0;
	if(add%SECTORBYTE!=0)return FLASHSECTOEADDERR;
	for(i=0;i<SECTORBYTE;i++)
	//for(i=0;i<1500;i++)
	{
		while(1)
		{
			result=flashreaddata4add(add+i);
			if(result<0)//��æ
			{
				cntbusy++;
				if(cntbusy>MAXCNT)
				{
					return FLASHBUSY;
				}
			}
			else break;
		}
		Flashbuf[i]=result;			
	}
	return FLASHSECTOEREADOK;	
}

//pageһ���ֽڣ���æ��ʱ�򷵻�æ����æ�Ļ�page�ҷ��� FLASHPAGEDONE
//�ı�page����֮ǰһ��Ҫ�����߳�һ��
int WaspFLASH::flashpagebyte4add(long add,unsigned char ch)
{
	if(writeEnable()==FLASHWRITEENABLEDONE)
	{
	  	AT_CS_LOW();
		SPI2_RWByte(0x02); //prage program	
		SPI2_RWByte((unsigned char )(add>>24));		
		SPI2_RWByte((unsigned char )(add>>16));
		SPI2_RWByte((unsigned char )(add>>8));
		SPI2_RWByte((unsigned char )add);
		SPI2_RWByte(ch);
		AT_CS_HIGH();
		return FLASHPAGEDONE;		
	}
	else return FLASHBUSY;
}
//page�����ֽڣ���æ��ʱ�򷵻�æ����æ�Ļ�page�ҷ��� FLASHPAGEDONE
//�ı�page����֮ǰһ��Ҫ�����߳�һ��
int WaspFLASH::flashpagestr4add(long add,unsigned char *str,unsigned int len)
{
	unsigned int ilen;
	if(writeEnable()==FLASHWRITEENABLEDONE)
	{
	  	AT_CS_LOW();
		SPI2_RWByte(0x02); //prage program	
		SPI2_RWByte((unsigned char )(add>>24));					
		SPI2_RWByte((unsigned char )(add>>16));
		SPI2_RWByte((unsigned char )(add>>8));
		SPI2_RWByte((unsigned char )add);
		for(ilen=0;ilen<len;ilen++)
		SPI2_RWByte(str[ilen]);
		AT_CS_HIGH();

		return FLASHPAGEDONE;					
	}
	else return FLASHBUSY;
}
//�����߳�
//һ������Ϊ4KB,һҳΪ256�ֽڣ���һ������Ϊ16ҳ
void WaspFLASH::flashsectorerase4add(long add)
{
	AT_CS_LOW();
	SPI2_RWByte(0x06);//дʹ��
	AT_CS_HIGH();

  	AT_CS_LOW();
	SPI2_RWByte(0x20); 			
	SPI2_RWByte((unsigned char )(add>>24));					
	SPI2_RWByte((unsigned char )(add>>16));
	SPI2_RWByte((unsigned char )(add>>8));
	SPI2_RWByte((unsigned char )add);
	AT_CS_HIGH();
}

//�����߳�
void WaspFLASH::sectorerase(uint32_t add)
{
	flashsectorerase4add(add);
}

//��һ����ַ��ָ��дһ�����ݣ����̣�������������߳�������page����
//һ������Ϊ4KB,һҳΪ256�ֽڣ���һ������Ϊ16ҳ
int WaspFLASH::writeFlash(uint32_t add,uint8_t ch)
{
	uint32_t addhead;
	uint32_t addleave;
	uint32_t ipage;
	//uint8_t  cntwbusy=0,maxwbusy=100;
	

	addleave=add%SECTORBYTE;
	addhead=add-addleave;

//�ȶ���ǰ��������,���ݷ���Flashbuf����
	if(readFlashsector(addhead)==FLASHSECTOEREADOK);
	else return FLASHSECTOEREADERR;

//�ѵ�ǰ�������ݶ�Ӧд�ĵط��ı�
	Flashbuf[addleave]=	ch;

//�����߳�
	sectorerase(addhead);
//����������дһ��

	for(ipage=0;ipage<16;ipage++)
	{
		//if(flashpagestr4add(addhead+256*ipage,&Flashbuf[256*ipage],256)==FLASHPAGEDONE);
		if(flashpagestr4add(addhead+256*ipage,&Flashbuf[256*ipage],256)==FLASHPAGEDONE);
		//if(flashpagebyte4add(add,Flashbuf[addleave])==FLASHPAGEDONE);
		else return FLASHSECTOEWRITEERR;			
	}
return FLASHSECTOEWRITEOK;
}


//��һ����ַ��ָ��д�������ݣ����̣�������������߳�������page����
//һ������Ϊ4KB,һҳΪ256�ֽڣ���һ������Ϊ16ҳ
int WaspFLASH::writeFlash(uint32_t add,uint8_t *str,uint32_t len)
{
	uint32_t addhead;
	uint32_t addleave;
	uint32_t ipage;
	uint32_t ilen;
	//uint8_t  cntwbusy=0,maxwbusy=100;
	

	addleave=add%SECTORBYTE;
	addhead=add-addleave;

	if((addleave+len)>SECTORBYTE)return FLASHLENERR;

//�ȶ���ǰ��������,���ݷ���Flashbuf����
	if(readFlashsector(addhead)==FLASHSECTOEREADOK);
	else return FLASHSECTOEREADERR;

//�ѵ�ǰ�������ݶ�Ӧд�ĵط��ı�
	for(ilen=0;ilen<len;ilen++)
	Flashbuf[addleave+ilen]=str[ilen];

//�����߳�
	sectorerase(addhead);
//����������дһ��

	for(ipage=0;ipage<16;ipage++)
	{
		//if(flashpagestr4add(addhead+256*ipage,&Flashbuf[256*ipage],256)==FLASHPAGEDONE);
		if(flashpagestr4add(addhead+256*ipage,&Flashbuf[256*ipage],256)==FLASHPAGEDONE);
		//if(flashpagebyte4add(add,Flashbuf[addleave])==FLASHPAGEDONE);
		else return FLASHSECTOEWRITEERR;			
	}
return FLASHSECTOEWRITEOK;
}


//��һ����ַ��ָ��д���ݣ����̣�������������߳�������page����
//һ������Ϊ4KB,һҳΪ256�ֽڣ���һ������Ϊ16ҳ

int WaspFLASH::writeFlash(uint32_t add,uint16_t data)
{
	uint8_t  str[2]={(uint8_t)data,(uint8_t)(data>>8)};
	return writeFlash(add,str,2);
}

int WaspFLASH::writeFlash(uint32_t add,uint32_t data)
{
	uint8_t  str[4]={(uint8_t)data,(uint8_t)(data>>8),(uint8_t)(data>>16),(uint8_t)(data>>24)};
	return writeFlash(add,str,4);
}


//����3��Ϊ��״̬�Ĵ�����������������κ�ʱ��
//״̬�Ĵ���1
uint8_t WaspFLASH::readStatusRegister1(void)
{
	AT_CS_LOW();
	SPI2_RWByte(0x05); 
	RxBuffer[0]=SPI2_RWByte(Dummy);
	AT_CS_HIGH();
	return RxBuffer[0];			
}

//״̬�Ĵ���2
uint8_t WaspFLASH::readStatusRegister2(void)
{
	AT_CS_LOW();
	SPI2_RWByte(0x35); 
	RxBuffer[0]=SPI2_RWByte(Dummy);
	AT_CS_HIGH();
	return RxBuffer[0];			
}

//״̬�Ĵ���3
uint8_t WaspFLASH::readStatusRegister3(void)
{
	AT_CS_LOW();
	SPI2_RWByte(0x15); 
	RxBuffer[0]=SPI2_RWByte(Dummy);
	AT_CS_HIGH();
	return RxBuffer[0];			
}


int WaspFLASH::writestatusregister1(uint8_t status)
{
	if(writeEnable()==FLASHWRITEENABLEDONE)
	{
	  	AT_CS_LOW();
		SPI2_RWByte(0x01); 	
		SPI2_RWByte(status);
		AT_CS_HIGH();
		return FLASHSTATUSDONE;		
	}
	else return FLASHBUSY;
}

int WaspFLASH::writestatusregister2(uint8_t status)
{
	if(writeEnable()==FLASHWRITEENABLEDONE)
	{
	  	AT_CS_LOW();
		SPI2_RWByte(0x31); 	
		SPI2_RWByte(status);
		AT_CS_HIGH();
		return FLASHSTATUSDONE;		
	}
	else return FLASHBUSY;
}

int WaspFLASH::writestatusregister3(uint8_t status)
{
	if(writeEnable()==FLASHWRITEENABLEDONE)
	{
	  	AT_CS_LOW();
		SPI2_RWByte(0x11); 	
		SPI2_RWByte(status);
		AT_CS_HIGH();
		return FLASHSTATUSDONE;		
	}
	else return FLASHBUSY;
}

void WaspFLASH::reset(void)
{
	  	AT_CS_LOW();
		SPI2_RWByte(0x66); 	
		AT_CS_HIGH();
	  	AT_CS_LOW();
		SPI2_RWByte(0x99); 	
		AT_CS_HIGH();

}

void WaspFLASH::writeprotection(uint8_t sta)
{
	if(sta==FLASHWPROTECTIONON)
	{
		FLASH_PROON(); 	
	}
	else
	{
		FLASH_PROOFF(); 
	}

}





// Preinstantiate Objects //////////////////////////////////////////////////////

WaspFLASH Flash = WaspFLASH();


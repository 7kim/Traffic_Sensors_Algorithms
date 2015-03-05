#ifndef __DINGKE_I2C_H
#define __DINGKE_I2C_H
#include <stm32f4xx.h>
//////////////////////////////////////////////////////////////////////////////////	 

////////////////////////////////////////////////////////////////////////////////// 	  
#include "dingke_smbus.h"


#define I2CTRUE 0
#define I2CFALSE -1

#define I2COK 	I2CTRUE
#define I2CERROR 	I2CFALSE


   	   		   
//IO��������
#define SDA_IN()  {GPIOB->MODER&=0XFFF3FFFF;GPIOB->MODER|=0X00000000;}
#define SDA_OUT() {GPIOB->MODER&=0XFFF3FFFF;GPIOB->MODER|=0X00040000;}

//IO��������	 
#define IIC_SCL    PBout(8) //SCL
#define IIC_SDA    PBout(9) //SDA	 
#define als        PDout(7)
#define READ_SDA   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) //����SDA 

//
 #define IICPROTECTON 1
 #define IICPROTECTOFF 0

#ifdef __cplusplus
extern "C"{
#endif


//IIC���в�������
			 

void i2cAck(void);					//IIC����ACK�ź�
void i2cNAck(void);				//IIC������ACK�ź�

void i2cWrite_One_Byte(u8 daddr,u8 addr,u8 data);
u8 i2cRead_One_Byte(u8 daddr,u8 addr);	
void i2cOn(void);
void i2cOff(void);
void i2cInit(void);                //��ʼ��IIC��IO��	
void i2cStart(void);				//����IIC��ʼ�ź�
void i2cStop(void);	  			//����IICֹͣ�ź�
void i2cSend_Byte(uint8_t txd);			//IIC����һ���ֽ�
int IICSendByteAck(uint8_t txd);
uint8_t i2cRead_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
int i2cWait_Ack(void); 				//IIC�ȴ�ACK�ź�
void writeprotection(int flag);
void softwarereset (void);


// �ⲿRTC
#define SLAVEADDRTC 0xd0
struct RTCSTRUCT
{
    	uint8_t second;
    	uint8_t minute;
    	uint8_t hour;
    	uint8_t day; //�ܵ���
    	uint8_t date; //�µ���
		uint8_t month;
    	uint8_t year;
}; 

union RTCUNION
{
	uint8_t unionstr[sizeof(struct RTCSTRUCT)/sizeof(uint8_t)];
	struct RTCSTRUCT structv;
};

extern union RTCUNION RTCExternalUn;
extern char RTCExternalStamp[60];
extern const char DAY_s[7][4];

extern int readExternalRTC (unsigned char address);
extern int writeExternalRTC (unsigned char address, uint8_t value);
extern uint8_t bcdtobyte(uint8_t bcd);

extern uint8_t bytetobcd(uint8_t abyte);
extern int getExternalTime(void);
extern int setExternalTime(uint8_t _year, uint8_t _month, uint8_t _date, uint8_t day_week, uint8_t _hour, uint8_t _minute, uint8_t _second);
extern int setExternalTimeStr(const char* timestr);

int setExternalAlarm1(uint8_t dateorday, uint8_t hour, uint8_t minute, uint8_t second, uint8_t type);
int clearExternalAlarm1(void);
int offExternalAlarm1(void);
int onExternalAlarm1(void);
int setExternalAlarm1AsAwake(uint8_t dateorday, uint8_t hour, uint8_t minute, uint8_t second, uint8_t type);


//EEPROM
int readEeprom (uint8_t slaveadress,int address);
int writeEeprom (uint8_t slaveadress,int address, uint8_t value);


//���оƬ��д
uint8_t readDS2745(uint16_t ReadAddr);							//ָ����ַ��ȡһ���ֽ�
void writeDS2745(uint16_t WriteAddr,uint8_t DataToWrite);		//ָ����ַд��һ���ֽ�


	
#ifdef __cplusplus
} // extern "C"
#endif 
 
  
#endif

















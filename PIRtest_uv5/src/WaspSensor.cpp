
 

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#include "dingke_delay.h"
 #include "dingke_i2c.h"
#endif

// Constructors ////////////////////////////////////////////////////////////////

WaspSensor::WaspSensor()
{
 //  SlaveAdress=0x00;
}

// Public Methods //////////////////////////////////////////////////////////////
//
void WaspSensor::init()
{
 	i2cInit();
}

//�Ե�ַΪ8λ������
int WaspSensor::readSensor (uint8_t slaveadress,uint8_t address)
{
	uint8_t temp=0;

	i2cStart(); 
	if(IICSendByteAck(slaveadress)==I2CFALSE)return I2CFALSE;
	if(IICSendByteAck((uint8_t)(address&0x00ff))==I2CFALSE)return I2CFALSE;//���͵͵�ַ
	i2cStart(); 

	if(IICSendByteAck(slaveadress+1)==I2CFALSE)return I2CFALSE;//�����ֽ�	
		 										  		    		    	   
    temp=i2cRead_Byte(0);		   
    i2cStop();//����һ��ֹͣ����	   
	return temp; 
}
//�Ե�ַ��16λ������
int WaspSensor::readSensor (uint8_t slaveadress,int address)
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
//�Ե�ַΪ8λ������
int WaspSensor::writeSensor (uint8_t slaveadress,uint8_t address, uint8_t value)
{

    i2cStart();  
	if(IICSendByteAck(slaveadress)==I2CFALSE)return I2CFALSE;			 	
	if(IICSendByteAck((uint8_t)(address&0x00ff))==I2CFALSE)return I2CFALSE;//���͵͵�ַ	
	if(IICSendByteAck(value))return I2CFALSE; //�����ֽ�		  		    	   
    i2cStop();//����һ��ֹͣ���� 
	delay_ms(10);	 
	return I2CTRUE;	
} 

//�Ե�ַ��16λ������
int WaspSensor::writeSensor (uint8_t slaveadress,int address, uint8_t value)
{

    i2cStart();  
	if(IICSendByteAck(slaveadress)==I2CFALSE)return I2CFALSE;		
	if(IICSendByteAck(address>>8)==I2CFALSE)return I2CFALSE;//���͸ߵ�ַ	 	
	if(IICSendByteAck((uint8_t)(address&0x00ff))==I2CFALSE)return I2CFALSE;//���͵͵�ַ	
	if(IICSendByteAck(value))return I2CFALSE; //�����ֽ�		  		    	   
    i2cStop();//����һ��ֹͣ���� 
	delay_ms(10);	 
	return I2CTRUE;	
} 


WaspSensor Sensor = WaspSensor();


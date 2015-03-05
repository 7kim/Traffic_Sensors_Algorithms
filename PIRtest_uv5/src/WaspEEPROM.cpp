#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#include "dingke_delay.h"
 #include "dingke_i2c.h"
//#include "sysclkchange.h"
#endif
// Constructors ////////////////////////////////////////////////////////////////
WaspEEPROM::WaspEEPROM()
{
   SlaveAdress=0x00;
}
// Public Methods //////////////////////////////////////////////////////////////
//

void WaspEEPROM::ON()
{
	i2cOn();
}
void WaspEEPROM::OFF()
{
	i2cOff();
}
void WaspEEPROM::begin()
{
 	i2cInit();
}
//void WaspEEPROM::close()
//{
//}
void WaspEEPROM::WriteProtection(int flag)
{
	writeprotection(flag);
}

void WaspEEPROM::start()
{
	i2cStart(); 
}
void WaspEEPROM::SoftwareReset (void)
{
	softwarereset ();
}
/*
int WaspEEPROM::IICSendByteAck(uint8_t txd)
{
	IIC_Send_Byte(txd);	   //����д����
	if(IIC_Wait_Ack()==I2CTRUE)return I2CTRUE;
	else return I2CFALSE;
}*/
//�ͻ��ṩ�ĺ���ʽ��
int WaspEEPROM::setSlaveAddress(uint8_t slaveadress)
{
	SlaveAdress=slaveadress;
	return IICSendByteAck(SlaveAdress);	
}
//�ͻ��ṩ�ĺ���ʽ��
int WaspEEPROM::writeEEPROM (int address, uint8_t value)
{	
	if(IICSendByteAck((uint8_t)(address>>8))==I2CFALSE)return I2CFALSE;//���͸ߵ�ַ
	if(IICSendByteAck((uint8_t)(address&0x00ff))==I2CFALSE)return I2CFALSE;//���͵͵�ַ
	if(IICSendByteAck(value))return I2CFALSE; //�����ֽ�		 										  		    		    	   
    i2cStop();//����һ��ֹͣ���� 
	delay_ms(10);	 
	return I2CTRUE;	
} 
//�ͻ��ṩ�ĺ���ʽ��
int WaspEEPROM::readEEPROM (int address)
{
	uint8_t temp=0;
	
	if(IICSendByteAck((uint8_t)(address>>8))==I2CFALSE)return I2CFALSE;//���͸ߵ�ַ
	if(IICSendByteAck((uint8_t)(address&0x00ff))==I2CFALSE)return I2CFALSE;//���͵͵�ַ
	i2cStart(); 

	if(IICSendByteAck(SlaveAdress+1))return I2CFALSE; //�����ֽ�	
		 										  		    		    	   
    temp=i2cRead_Byte(0);		   
    i2cStop();//����һ��ֹͣ����	   
	return temp; 
}
//����ϣ����дһ���ֽں�����ʽ��
//��·ͼ�����˰����ϵ�EEPROM��ַΪ0xa0 ,�����·ͼ�ı��ˣ�ֻ��Ҫ�������0xa0�ĳɶ�Ӧ�ĵ�ַ�Ϳ�����
int WaspEEPROM::writeEEPROM (uint8_t slaveadress,int address, uint8_t value)
{
	return writeEeprom (0xa0,address, value);
}


//����ϣ���Ķ�һ���ֽں�����ʽ��
//��·ͼ�����˰����ϵ�EEPROM��ַΪ0xa0 ,�����·ͼ�ı��ˣ�ֻ��Ҫ�������0xa0�ĳɶ�Ӧ�ĵ�ַ�Ϳ�����
int WaspEEPROM::readEEPROM (uint8_t slaveadress,int address)
{ 
    return readEeprom (0xa0,address);
}

//����ϣ����д�ַ���������ʽ��
int WaspEEPROM::writeEEPROMStr(uint8_t slaveadress,uint16_t writeaddr,uint8_t *pbuffer,uint16_t strlen)
{
	while(strlen--)
	{
		if(writeEeprom(slaveadress,writeaddr,*pbuffer)==I2CFALSE)return I2CFALSE;
		writeaddr++;
		pbuffer++;
	}
	return I2CTRUE;
}
//����ϣ���Ķ��ַ���������ʽ��
int WaspEEPROM::readEEPROMStr(uint8_t slaveadress,uint16_t readaddr,uint8_t *pbuffer,uint16_t strlen)
{
	int flag;
	while(strlen)
	{
		flag=readEeprom (slaveadress,readaddr++);
		if(flag==I2CFALSE)return I2CFALSE;
		else *pbuffer++=flag;	
		strlen--;
	}
	return I2CTRUE;
} 
 



// Preinstantiate Objects //////////////////////////////////////////////////////

WaspEEPROM Eeprom = WaspEEPROM();


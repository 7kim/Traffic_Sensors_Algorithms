#ifndef __ALLBOARDINC_H
#define __ALLBOARDINC_H 			   

//////////////////////////////////////////////////////////////////////////////////	 
#include <stm32f4xx.h>
#include<string.h> //strccmp ֮��
#include<stdlib.h> //atoi֮��
#include "dingke_delay.h"
#include "dingke_spi.h"
#include "dingke_i2c.h"
#include "dingke_timer.h"
#include "dingke_uart.h"
#include "dingke_pwr.h"
#include "dingke_exti.h"
#include "dingke_sysclkchange.h" //����Ƶ�õ�

//#include "wiring.h"	��Ҫ��uart
#include "sdio_sd.h"  //sdio
#include "ff.h"		  //fat32(16) ĿǰӦ����sd��
  #include "mysdfat.h"	
#include "matrix.h"


#include "WaspEEPROM.h"	//I2C
#include "Wasprtc.h"	  //I2C
#include "WaspFLASH.h"	  //SPI

#include "WaspSD.h"	  //sdio
#include "WaspUtils.h"//ledʲô��

#include "dingke_wdg.h"


#include "wasppwr.h"
//#include "exti.h"     //PA0��Ϊ�ⲿ�ж� ���統����˯��ģʽʱ����PA0�������κ������ж϶����Ի���



#include "WaspXBee.h"
#include "WaspXBeeCore.h"
#include "WaspXBee802.h"


void setup(void);
void loop(void);
#endif



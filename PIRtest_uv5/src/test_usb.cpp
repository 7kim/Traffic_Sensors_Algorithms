#include <stm32f4xx.h>
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "delay.h"

	
#include "usbd_hid_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"


/****************************************************************************

****************************************************************************/

/****************************************************************************
����˵��
	�������
	����USB OTG�ӿ�������,ͨ������������ģ����깦��
****************************************************************************/

USB_OTG_CORE_HANDLE  USB_OTG_dev;
void Send_Report(u8 byte0,u8 byte1,u8 byte2,u8 byte3);
	u8 zppshow[30];
int testusbhid(void)
{	




		
	//Ӳ����ʼ��
 	//Key_Init();//������ʼ��
	//   beginSerial(9600, 3);

	
	USBD_Init(&USB_OTG_dev,USB_OTG_FS_CORE_ID,&USR_desc,&USBD_HID_cb,&USR_cb);//USB�ӻ���ʼ��

	while(1)
	{
		//�������
		Send_Report(0,0,250,0);//���ͱ���	
		delay_ms(1000);
		//�������
		Send_Report(0,0,6,0);//���ͱ���	
		delay_ms(1000);
		//�������
		Send_Report(0,250,0,0);//���ͱ���	
		delay_ms(1000);
		//�������
		Send_Report(0,6,0,0);//���ͱ���	
		delay_ms(1000);	
	}
}
//����HID����
void Send_Report(u8 byte0,u8 byte1,u8 byte2,u8 byte3)
{
	u8 HID_Buffer[4];
	
	HID_Buffer[0]=byte0;
	HID_Buffer[1]=byte1;
	HID_Buffer[2]=byte2;
	HID_Buffer[3]=byte3;
	USBD_HID_SendReport(&USB_OTG_dev,HID_Buffer,4);
}



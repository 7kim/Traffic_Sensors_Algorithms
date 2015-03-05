
#include "dingke_delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//MLX 9016ʹ��˵����
//1.���и��µģ�δʹ�ù������߲�֪����������ַ��MLX90614�������ӵ�SMBUS�����ϣ�Ҳ����SMBUS������ֻ����һ��MLX90614
//2.��һ�����ĵ�ַ����slave_add= MEM_READ1(0x00,0x2e);slave_add��8λΪ����µ�MLX90614��������ַ�������ԣ�δʹ�õ�һ��Ϊ0x5a
//3.�����MLX90614��������ַ�ĳ�������ַ������0x2a, �����д�� changeMlx90614Subadd(0x00, 0x2a) ����changeMlx90614Subadd(0x5a, 0xa0); �ϵ�����ϵ�����µ�ַ��������
//4.������µ�MLX90614 ������ַ�Ĺ�֮�󣬶����ͬ��������ַ��MLX90614�ſ��Խӵ�һ��
//5.����Ҫ�����������¶�ʱ������	temp1=readMlx90614ObjectTemp(0xa0);	�����0xa0������ĺ�������ַ��temp1�ǵõ����¶�ֵΪ������
//6.���ö������Ѿ�����һ��ʱҲ���Ը�������ַ��ע�� 1. changeMlx90614Subadd(���ڵ�ַ��������0x00��, �µ�ַ)	2.�����ַ֮�����Ҫ�����ϵ�ſ���
//7.����������ַslave_add= MEM_READ1(0x00,0x2e)ֻ�е�������ֻ��һ�������������ĵ�ַ������ȷ�ĵ�ַ��
//
//
/*
ע�����
1.д��֮ǰҪ�Ȳ�����Ҳ������Ҳ��0 ����д�����ݡ�
2.��Ҫ��дʱ������һλ���ݴ��󶼽��������ݴ������⡣
3.��������������ϵͳʱ���ӻ���ַ��ʹ��0x00,������Ĭ�ϵ�ַΪ0x5a.
4.�������������ʱ����ַ�����ı��Ϊ��ͬ�ĵ�ַ���������ݴ���
5.��ֻ���������ĵ�Դ��ȥ����������ĵ�ַ����Ϊ0���������ݴ���
6.�������ͬ��ַ�Ĵ������ı��ַʱ����������ַ����ͬ��
7.�����ͬ�������޸ĵ�ַʱ���赥��һ���޸ģ�д��ַ�����غ����¿�ʼ�����Ч�����Ҫע�⣬��������ַ����Чʱ������Ķ�д���ݲ�������
8.�ѵ��������ĵ�ַֻ��һ��һ���ĸģ� �� ���ǿ��Ե� ������Ҫע���һ�� �����޸���Ϻ���Ҫ��ʱһ��ʱ�䣬�ͷ����ߡ�

*/
////////////////////////////////////////////////////////////////////////////////// 	  
#define TIMEZPPSMBUS 20
#define    SMBusSetSDA()  GPIO_SetBits(GPIOB,GPIO_Pin_11) //
#define    SMBusResetSDA()  GPIO_ResetBits(GPIOB,GPIO_Pin_11)  //
#define    SMBusSetSCL()  GPIO_SetBits(GPIOB,GPIO_Pin_10) //
#define    SMBusResetSCL()  GPIO_ResetBits(GPIOB,GPIO_Pin_10) //
#define    SMBusREAD_SDA   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) //����SDA 

//��ʼ��IIC
void SMBusSDA_OUT(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;					     

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	
	//I2C_SCL PB.8   I2C_SDA PB.9 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11 ;//SDA
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SMBusSDA_IN(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;					     

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	
	//I2C_SCL PB.8   I2C_SDA PB.9 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11 ;	//SDA
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SMBus_poweron(void)//PE3
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4  ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}
//SMBus��ߵ�Դ���ˣ���SDA SCL���ų�ʼ��
void SMBus_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
						     
	SMBus_poweron();
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	
	//I2C_SCL PB.8   I2C_SDA PB.9 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 |GPIO_Pin_11 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	GPIO_SetBits(GPIOB,GPIO_Pin_10);//SCL  
	GPIO_SetBits(GPIOB,GPIO_Pin_11);//SDA
}

//SMBus�������оƬ����SMBus״̬Ҫ������
void SMBus_Apply(void)
{
	 SMBusResetSCL();
				//SMBus����ʱ�䣬��PWMģʽת��ΪSMBusģʽ(����Ϊ2ms)
     delay_ms(3); //��С1.44ms 
	 SMBusSetSCL();
}


void send_bit(unsigned char bit_out)
{
   
  SMBusSDA_OUT();			  //����SDAΪ��©������������ϴ�������


  if(bit_out==0)				  //�˶��ֽڵ�λ
            					  //���bit_out=1������SDA��Ϊ�ߵ�ƽ
             //SDA=0;
	SMBusResetSDA();
  else							  
             //SDA=1;				  //���bit_out=0������SDA��Ϊ�͵�ƽ
	SMBusSetSDA();	

	delay_us(2 );
  //SCL=1;				  //����SCL��Ϊ�ߵ�ƽ
  SMBusSetSCL(); //SCL 
  delay_us(6 );

  //SCL=0;				  //����SCL��Ϊ�͵�ƽ
  SMBusResetSCL(); //SCL
  delay_us(2 );

}

unsigned char receive_bit()
{
  unsigned char bit_in;
  //_SDA_INPUT;				                //����SDAΪ��������
  SMBusSDA_IN();
  delay_us(2 );
  //SCL=1;					   //����SCL��Ϊ�ߵ�ƽ
  SMBusSetSCL(); //SCL 
  delay_us(6 );
  //if(SDA==1)					    //�������϶�ȡһλ������bit_in
  if(SMBusREAD_SDA)
       bit_in=1;
  else
       bit_in=0;
  //SCL=0;					   //����SCL��Ϊ�͵�ƽ
  SMBusResetSCL(); //SCL  
  delay_us(2);
  return bit_in;                                                          //����bit_inֵ
}

unsigned char RX_byte(unsigned char ack_nack)
{
    unsigned char RX_buffer=0;
    unsigned char Bit_counter;
    for(Bit_counter=8;Bit_counter;Bit_counter--)
    {
		if(receive_bit()==1)	                //��SDA�߶�ȡһλ
		   {
			RX_buffer<<=1;		   //���λΪ"1"����"1"��RX_buffer 
			RX_buffer|=0x01;
		   }
		else				   //���λΪ"0"����"0"��RX_buffer
		   {
			RX_buffer<<=1;
			RX_buffer&=0xfe;
		   }		
      } 
	 send_bit(ack_nack);			   //����ȷ��λ

	 return RX_buffer;
}


void TX_byte(unsigned char TX_buffer)
{
   unsigned char Bit_counter;
   unsigned char bit_out;
     
   for(Bit_counter=8;Bit_counter;Bit_counter--)
   {
       if(TX_buffer&0x80)
		     bit_out=1;	               //���TX_buffer�ĵ�ǰλ��1,����bit_outΪ1
		else
		     bit_out=0;	         	  //��������bit_outΪ0
     send_bit(bit_out);			  //����SMBus�����ϵĵ�ǰλ   
     TX_buffer<<=1;		               //�˶���һλ		  
	}			            	                      
}

unsigned char slave_ack()
{
   unsigned char ack;
   ack=0;
   //_SDA_INPUT;				    //����SDAΪ��������
   SMBusSDA_IN();
	delay_us(2 );
   //SCL=1;					    //����SCL��Ϊ�ߵ�ƽ
   SMBusSetSCL();
   	delay_us(6 );
   //if(SDA==1)					    //�������϶�ȡһλ������ack
   if(SMBusREAD_SDA)
         ack=0;
   else
         ack=1; 

   //SCL=0;					    //����SCL��Ϊ�͵�ƽ
   SMBusResetSCL(); //SCL
   	delay_us(2 );   
   return ack;
}



unsigned char PECARR[7];				 //�洢�ѷ����ֽڵĻ�����

/*----------------------------------------------------------------------------------------------------------------------------------------//
����PEC����У����
������: PEC_cal
����: ���ݽ��յ��ֽڼ���PEC��
����: unsigned char pec[], int n
����ֵ: pec[0] - ���ֽڰ�����������crc��ֵ
ע��:	�ο�"ϵͳ��������˵����-�汾2.0"��Ӧ��ָ��"MCU��MLX90614��SMBusͨ��"
//----------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char PEC_cal(unsigned char pec[],int n)
{
     unsigned char crc[6];
     unsigned char Bitposition=n*8-1;
     unsigned char shift;
     unsigned char i;
     unsigned char j;
     unsigned char temp;

	for(i=0;i<7;i++)
	PECARR[i]=pec[i];
   do{
          crc[5]=0;           			       
          crc[4]=0;
          crc[3]=0;
          crc[2]=0;
          crc[1]=0x01;						    //���� CRC��ֵ 0x000000000107
          crc[0]=0x07;
          Bitposition=n*8-1;     		                     //����Bitposition�����ֵΪ47
          shift=0;
          //�ڴ��͵��ֽ����ҳ���һ��"1"

          i=n-1;                			        //������߱�־λ (�����ֽڱ�־)
          j=0;                			        //�ֽ�λ��־�������λ��ʼ
          while((pec[i]&(0x80>>j))==0 && (i>0))	  
	  {
             Bitposition--;
             if(j<7)
	   {
                    j++;
                 }
             else
	      {
                   j=0x00;
                   i--;
                   }
           }//while�����������ҳ�Bitposition��Ϊ"1"�����λλ��
          shift=Bitposition-8;                                   //�õ�CRC��ֵ��Ҫ����/���Ƶ���ֵ"shift"
	                                                              //��CRC��������"shift"λ
          while(shift)
	     {
              for(i=n-1;i<0xFF;i--)
		 {  
                    if((crc[i-1]&0x80) && (i>0))          //�˶��ֽڵ����λ����һλ�Ƿ�Ϊ"1"
		     {   			       //�� - ��ǰ�ֽ� + 1
                          temp=1;		       //�� - ��ǰ�ֽ� + 0
                     }				       //ʵ���ֽ�֮���ƶ�"1"
                    else
	             {
                          temp=0;
                     }
                     crc[i]<<=1;
                     crc[i]+=temp;
                  } 

                  shift--;
              } 
           //pec��crc֮�����������
           for(i=0;i<=n-1;i++)
		   {
                   pec[i]^=crc[i];
		   }  
      }while(Bitposition>8); 
	return pec[0];                                  //���ؼ������õ�crc��ֵ
} 


unsigned char PECwbparr[7];				 //�洢�ѷ����ֽڵĻ�����
unsigned char PECreg;				 //�洢��������PEC�ֽ�

	 
/*----------------------------------------------------------------------------------------------------------------------------------------//
������: start_bit
����: ��SMBus�����ϲ�����ʼ״̬
ע��: �ο�"ϵͳ��������˵����-�汾2.0"
//----------------------------------------------------------------------------------------------------------------------------------------*/
void start_bit()
{
//GPIO_InitTypeDef GPIO_InitStructure;
   SMBusSDA_OUT();
   SMBusSetSDA();//����SDA��Ϊ�ߵ�ƽ		                   				       
   delay_us(2);
   			  
   SMBusSetSCL();// //SCL 				       //����SCL��Ϊ�ߵ�ƽ
   delay_us(5);				       //����ֹ����ʼ״̬֮��������߿���ʱ��(Tbuf=4.7us��Сֵ)
   SMBusResetSDA(); //SDA				       //����SDA��Ϊ�͵�ƽ
   delay_us(5);				      
   //���ظ�����ʼ״̬��ı���ʱ�䣬�ڸ�ʱ��󣬲�����һ��ʱ���ź�
  					       //Thd:sta=4us��Сֵ
   SMBusResetSCL(); //SCL				       //����SCL��Ϊ�͵�ƽ
   delay_us(10);

}


/*----------------------------------------------------------------------------------------------------------------------------------------//
������: stop_bit
����: ��SMBus�����ϲ�����ֹ״̬
ע��: �ο�"ϵͳ��������˵����-�汾2.0"
//----------------------------------------------------------------------------------------------------------------------------------------*/
void stop_bit()
{
  SMBusSDA_OUT();//sda�����				 //����SDAΪ���
  SMBusResetSCL(); //SCL 			     		 //����SCL��Ϊ�͵�ƽ
  delay_us(5);
  SMBusResetSDA(); //SDA 					 //����SDA��Ϊ�͵�ƽ
  delay_us(5);
  SMBusSetSCL(); //SCL				             //����SCL��Ϊ�ߵ�ƽ
  delay_us(5);				             //��ֹ״̬����ʱ��(Tsu:sto=4.0us��Сֵ)
  SMBusSetSDA();//SDA 				             //����SDA��Ϊ�ߵ�ƽ 
}
//�ж�SMBUS��ַ�Ƿ���ڣ� �����ڷ��ص�ַ��������ʱ����0XFF
unsigned char ACKaddress(unsigned char ADDRESS)
{
  unsigned char SLA;
  SLA=(ADDRESS<<1);	             
  start_bit(); 	  //������ʼλ
  TX_byte(SLA);   //�����ܿ�������ַ��д����  
  delay_us(100);            			               					 
  if(!slave_ack())
  {
    stop_bit();
    return 0;
  }
  else
  {
    stop_bit();
    return 1;
  }
}


/*----------------------------------------------------------------------------------------------------------------------------------------//
��MLX90614 RAM/EEPROM ��ȡ������
������: MEM_READ
����: �����ܿص�ַ������ʱ��MLX90614��ȡ����
����: unsigned char slave_addR (�ܿص�ַ)
         unsigned char cmdR (����)
����ֵ: unsigned long int Data
//----------------------------------------------------------------------------------------------------------------------------------------*/
//slave_addR 
//   SMBUS������ַ 	 0000 0000  �㲥���е�ַ				  //0x00
//                       0000 0001  ��ʼ��ַ					  //0x01
//                       0000 001x  CBUS��ַ					  //0x0?
//                       0000 010x  ��ַ������ͬ�����߸�ʽ		//0x0?
//                       0000 011x  ��������ʹ��				  //0x0?
//                       0000 1xxx  ��������ʹ��				  //0x0?
//                       0101 000x  ������ACCESS.bus����	      //0x5?
//                       0110 111x  ������ACCESS.busĬ�ϵĵ�ַ	//0x6?
//                       1111 0xxx  10λ�ӵ�ַ					  //0xf?
//                       1111 1xxx  ��������ʹ��				  //0xf?
//                       0001 000x  SMBus����					  //0x1?
//                       0001 100x  SMBus������Ӧ��ַ			  //0x1?
//                       1100 001x  SMBus�豸Ĭ�ϵ�ַ			  //0xc?



//cmdR 
//   MLX90614  000x xxxx ����RAM  
//             001x xxxx ����EEPROM
//	           1111 0000 ��ȡ��־��
//	           1111 1111 ����SLEEPģʽ

//             EPPROM  00 Tomax	     ʵ��ʹ���ǲ���001x xxxx(����EEPROM������)	Ϊ0x20
//                     01 Tomin		                                             	Ϊ0x21
//                     02 PWMCTRL	                                             	Ϊ0x22
//                     03 Ta��Χ	                                            	Ϊ0x23
//                     04 ������У׼ϵ��                                          Ϊ0x24
//                     05 ���üĴ���1                                            	Ϊ0x25
//                     0e SMBUS��ַ                                            	    Ϊ0x2e
//                     1c ID���
//                     1d ID���
//                     1e ID���
//                     1f ID���

//             RAM     04  ԭʼ����IRͨ��1 
//                     05  ԭʼ����IRͨ��2 
//                     06  Ta �����¶� 
//                     07  Tobj1 Ŀ���¶�1 
//                     08  Tobj1 Ŀ���¶�2 


long MEM_READ1(unsigned char slave_addR, unsigned char cmdR)
{	
	 unsigned char DataL;		                           //
	 unsigned char DataH;				 //��MLX90614��ȡ�����ݰ�
   
   	 unsigned char SLA;
	 unsigned char Pec;
	 unsigned char cntack=0;
	 unsigned char cntrepeat=0;		

			// Initialising of ErrorCounter	

beginread:

	cntrepeat++;//ÿ��������һ�ξͼ�1��������100��˵��smbus��·��ͨ,����-1
	if(cntrepeat>5)return -1;
										
	 SLA=(slave_addR<<1);	             
	 start_bit(); 	  //������ʼλ
	 TX_byte(SLA);   //�����ܿ�������ַ��д����              			               
	 
	 cntack=0;					 
	 while(!slave_ack()){
	 	cntack++;
		if(cntack>=100)
		{
			cntack=0;  
			goto beginread;
		}
	 }
					  //��������
     TX_byte(cmdR);

	 cntack=0;
	 while(!slave_ack()){
	 	cntack++;
		if(cntack>=100)
		{
			cntack=0;  
			goto beginread;
		}
	 }			
	 start_bit(); 	                                                      //�����ظ���ʼλ				
	 TX_byte(SLA+1); 
	 
	 cntack=0; //�����ܿ�������ַ��������                                                 
	 while(!slave_ack()){
	 	cntack++;
		if(cntack>=100)
		{
			cntack=0;
			goto beginread;
		}
	 }


	 DataL=RX_byte(0);				  //
							  //��ȡ�����ֽ�����
	 DataH=RX_byte(0);				  //
	 Pec=RX_byte(1);

	 stop_bit(); 

	 PECwbparr[6]=(Pec);
	 PECwbparr[5]=(SLA);
     PECwbparr[4]=cmdR;
     PECwbparr[3]=(SLA+1);               
     PECwbparr[2]=DataL;
     PECwbparr[1]=DataH;
     PECwbparr[0]=0;                  										 
	 PECreg=PEC_cal(PECwbparr,6);  			  //���ü��� CRC �ĺ���

	  //��ȡMLX90614��PEC��                                                       //������ֹ
	return 	 (   (((unsigned int)DataH)<<8)|(((unsigned int)DataL)&0x00ff)  );
}

/*----------------------------------------------------------------------------------------------------------------------------------------//
��MLX90614 RAM/EEPROM ��ȡ������
������: MEM_READ
����: �����ܿص�ַ������ʱ��MLX90614��ȡ����
����: unsigned char slave_addR (�ܿص�ַ)
         unsigned char cmdR (����)
����ֵ: unsigned long int Data
//----------------------------------------------------------------------------------------------------------------------------------------*/
void MEM_WRITE1(unsigned char slave_addR, unsigned char cmdR,unsigned int data)
{	
   	 unsigned char SLA;
	 unsigned char DataL;		                           //
	 unsigned char DataH;				 //��MLX90614��ȡ�����ݰ�

	 SLA=(slave_addR<<1);
	 DataL=(unsigned char)(data);
	 DataH=(unsigned char)(data>>8);
     PECwbparr[4]=(SLA);
     PECwbparr[3]=cmdR;               
     PECwbparr[2]=DataL;
     PECwbparr[1]=DataH;
     PECwbparr[0]=0;  
	                   										 
	 PECreg=PEC_cal(PECwbparr,5);  			  //���ü��� CRC �ĺ���	
//	 printf(" PECcal=%x ewqd=%x  ",PECreg,PECARR[6]);		
					 	             
	   start_bit(); 	  //������ʼλ

	  TX_byte(SLA);   //�����ܿ�������ַ��д����              			               
	   while(!slave_ack());					  //��������

      TX_byte(cmdR);
	   while(!slave_ack());				                                                      //�����ظ���ʼλ	
	 			
 	  TX_byte(DataL);                                                   //�������ݵ͵�ַ
	  while(!slave_ack());

	  TX_byte(DataH);                                                   //�������ݸ��ֽ�
	  while(!slave_ack());
	 
	    TX_byte(PECreg);                                                   //����PEC
	    while(!slave_ack()); 

	  stop_bit(); 
	 delay_ms(10);
}

//��������ַ��������ֻ��һ�����⴫�������У�Ҫ��Ȼ�������ֵ�����е���ֵ�������ͱ�ͣ�
int readMlx90614Subadd(void) 
{
	long zhi;
	unsigned char flag=0;
	while(1)
	{
		zhi = MEM_READ1(0x00,0x2e);
		if(zhi==-1)		  //zhi=-1˵�������˺ܶ�ζ���������������
		{
			SMBus_Apply();
			return -1;
		}
		if((zhi>=0x01)&&(zhi<=0xff))
		{
			return 	zhi;
		}
		flag++;
		if(flag>100)
		{	
			SMBus_Apply();
			return -1;
		}
	}
}


//�޸��¶ȴ�������ַ��INIT_addR:��ʾ��һ�εĵ�ֵַ��CURR_addR����ʾ��ǰ��ֵַ��Ҳ�����޸ĺ�ĵ�ֵַ
void changeMlx90614Subadd(unsigned char INIT_addR, unsigned int CURR_addR) 
{
  if(ACKaddress(INIT_addR))
  {
    MEM_WRITE1(INIT_addR,0x2E,0);	
	MEM_WRITE1(INIT_addR,0x2E,CURR_addR);
  }
}

//���ص���С�������緵����19.87�������19.87��
static float trantocentigradefloat(unsigned int zhi)
{
	//return (((float)zhi/50.0)-273.15);
	return (((double)zhi*0.02)-273.15);
}


//�������¶� ����ֵΪС��
float readMlx90614AmbientTemp(unsigned char slave_addR)
{	
	long zhi;
	unsigned char flag=0;
	while(1)
	{
		zhi = MEM_READ1(slave_addR,0x06);
		if(zhi==-1)		  //zhi=-1˵�������˺ܶ�ζ���������������
		{
			SMBus_Apply();
			return 0.0;
		}
		if((zhi>=0x2DEA)&&(zhi<=0x4DC4))
		{
			return 	trantocentigradefloat(zhi);
		}
		flag++;
		if(flag>100)
		{	
			SMBus_Apply();
			return 0.0;
		}
	}
}
//��Ŀ���¶�
//����������ֶ���Ӧ��ַ�������������������¶ȴ������ģ��������������һ����һ��������û�нӺû��ߵ�ַ������ɶ����ݴ�����������ⲻ��ʲô�����⣩ ������Ժ��������ַҲ���
float readMlx90614ObjectTemp(unsigned char slave_addR)
{	
	long zhi;
	unsigned char flag=0;
	while(1)
	{
		zhi = MEM_READ1(slave_addR,0x07);
		if(zhi==-1)	//zhi=-1˵�������˺ܶ�ζ���������������
		{
			SMBus_Apply();
			return 0.0;
		}
		
		if((zhi<=0x7fff))
		{
		   return 	trantocentigradefloat(zhi);
		}
		flag++;
		if(flag>2)
		{
			SMBus_Apply();
			return 0.0;
		}
	}
}















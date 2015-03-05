/*
����ǰ��ӵĹ�������,��ʽ��maple�Ľӽ���ʹ��setup()��loop()���������������������������ͷ�ļ�	#include "allboardinc.h"
���������¼��֣�
#define SPIFLASH 0			 FLASH����
#define SPINULL 100			 ��ѡ��SPI����
����ѡ���ĸ�����������setup()��loop()�����֣���ѡ��ѡ�ù������̾�û��������������Ҫ��֤��������������ֻ��һ��setup()��loop()
*/
#include "allboardinc.h"
#define SPIFLASH 0
#define SPINULL 100

#define EXAMPLESPI SPINULL

//SPIFLASH
#if EXAMPLESPI==SPIFLASH
void setup()
{
	int readch;
	unsigned long k;
	uint8_t testflashbuf[4096];
	Mux_poweron(); //����һ����Դ���������õģ������ӡ����
	beginSerial(115200, PRINTFPORT);
	printf("test SPI\n");

	printf("init SPI_FLash");
	Flash.SPI_Flash_Init();//SPI FLASH��ʼ��
	
	//�ڵ�ַ4092�Ǳ�д���ַ�'4'(0x34)
	printf("\n  Write a char '4' to address=4092.");
	readch=Flash.writeFlash(4092,(uint8_t)'4');
	if(readch==FLASHSECTOEWRITEOK)//���д�ɹ���
	{
		printf("ok");
		//����ַ4092��������,����������ݰ����ݸ�readch,�����������ݻ������������������Ϣ�����Ǹ�������readch
		//�˺��������Ͽͻ��ṩ�Ķ�����д�������ݿͻ��ṩҲ��uint8_t readFlash1byte(uint32_t add)��uint16_t WaspFLASH::readFlash2byte(uint32_t add),uint32_t WaspFLASH::readFlash4byte(uint32_t add)
		// ���Ǹ��ݿͻ������������������оƬæ֮��ľ�ֻ�ܷ���0�����ܷ�Ӧ������Ϣ��
		printf("  Read a char from address=4092:");
		readch=Flash.flashreaddata4add(4092);
		if(readch<0)
		{
			printf(" err=%d ",readch);
			while(1);
		}
		else
		{
			//�Ѷ����������ݣ���������ͣ��ô���3��ӡ��������ʵ�����printfֻ��Դ���3���������printf����retarget.c�аѴ���3��serialWrite((unsigned char) ch, 3)ӳ�䵽fputc(int ch, FILE *f)�ˡ�
			// ����ͻ���ϲ��������԰�retarget.cɾ�������ڴ�ӡ����wiring_serial.c�����void serialWrite(unsigned char c, uint8_t portNum)
			printf("%c\n",readch); 		
		}
	}										 
	else
	{
		printf(" the type of writeerr =%d ",readch);
		while(1);
		//delay_ms(30000);
	}

	printf("\n  Read datas with a sector size. if it work, the Array Flashbuf get these datas. ");
	//���ӵ�ַ0��ʼ��һ���������ݣ��������ݸ���Flashbuf[k]
	readch=Flash.readFlashsector(0);
	//������ɹ�����ӡһЩ���� 
	if(readch==FLASHSECTOEREADOK)
	{
		//��ӡ��ַ0-9������
		printf(" show the datas with address=0 to 10:");
		for(k=0;k<10;k++)
		{
			printf("%x ",Flash.Flashbuf[k]);
		}

		//��ӡ��ַ4090-4095������
		printf(" show the datas with address=4090 to 4096:");
		for(k=4090;k<4096;k++)
		{
			printf(" %x",Flash.Flashbuf[k]);delay_ms(500);
		}
		delay_ms(3000); 
	}
	else
	{
		printf(" the type of readerr=%d ",readch);
		while(1);
	}

	testflashbuf[0]='A';testflashbuf[1]='B'; testflashbuf[2]='C';testflashbuf[3]='D';
	
	testflashbuf[4091]=0x61;testflashbuf[4092]=0x62;testflashbuf[4093]=0x63;testflashbuf[4094]=0x64;
	//���ַ���testflashbuf����д����ַ0���ڵ�������д4096������
	printf("\n  Write 4096 datas to sector 0(the first sector)");
	readch=Flash.writeFlash(0,testflashbuf,4096);
	//���д�ɹ���
	if(readch==FLASHSECTOEWRITEOK)
	{	
	    printf("  Read a data from address=0:");
		readch=Flash.flashreaddata4add(0);
		printf("%d\n",readch);
		  
	}
	//���д���ɹ�
	else
	{
		printf(" str writeerr yuanyin=%d ",readch);
		while(1);
	}

	//��һ�����������ݣ��ɹ��ʹ�ӡ��������
	printf("\n  Read again the sector 0.");
	readch=Flash.readFlashsector(0); 
	if(readch==FLASHSECTOEREADOK)
	{
		printf(" show the datas with address=0 to 10:");
		for(k=0;k<10;k++)
		{
			printf("%x ",Flash.Flashbuf[k]);
		}

		printf(" show the datas with address=4090 to 4096:");
		for(k=4090;k<4096;k++)
		{
			printf(" %x",Flash.Flashbuf[k]);delay_ms(300);
		}
		
	}
	else
	{
		printf(" the type of readerr=%d ",readch);
		while(1);
	}

	printf("\n  Read a data from address=0: ");
	printf(" %x ",Flash.readFlash1byte(0));

	printf("\n  Read a short data from address=0: ");
	printf(" %x ",Flash.readFlash2byte(0));

	printf("\n  Read a word data from address=0: ");
	printf(" %x ",Flash.readFlash4byte(0));

	printf("\nOK end");
}

void loop()
{
	while(1); 	
}
#endif //end SPIFLASH




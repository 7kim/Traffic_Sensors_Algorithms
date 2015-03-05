/*
����ǰ��ӵĹ�������,��ʽ��maple�Ľӽ���ʹ��setup()��loop()���������������������������ͷ�ļ�	#include "allboardinc.h"
���������¼��֣�     
#define BTESTSDIOFAT 0		 SD����д����
#define BTESTSDIONULL 100	 ��ѡ�ù�������
����ѡ���ĸ�����������setup()��loop()�����֣���ѡ��ѡ�ù������̾�û��������������Ҫ��֤��������������ֻ��һ��setup()��loop()
*/
#include "allboardinc.h"
#define BTESTSDIOFAT 0
#define BTESTSDIONULL 100

#define EXAMPLESDIO BTESTSDIONULL
/*
SD����д����
    �漰��������SD��Դ��SD��ʼ�����õ�SD�ܿռ䣬����ʣ��ռ䣬���ɡ�ɾ���ļ��к��ļ���
	      �ж��ļ��л��ļ��������ļ������ļ���Ŀ����Ҫ���д�ļ��������ݣ��õ��ļ���С
*/
//SDIOFAT
#if EXAMPLESDIO==BTESTSDIOFAT
void setup()
{
	uint8_t readstr1[512]="strhaha";
	uint64_t fsize;
	int8_t filecnt=-2;
	int32_t filesize=-2;
		
//������
	Mux_poweron(); //����һ����Դ���������õģ������ӡ����
	beginSerial(115200, PRINTFPORT);
	delay_ms(60);
	printf("this is SD FAT test \r\n");

//SD����Դ��
	printf("SD poweron. \r\n");		 
 	SD.ON();//�������Ҫ��ʱһ���ʱ���ڳ�ʼ��SD����Ҫ��ȻĳЩSD����ʼ�����ɹ�

//SD��ʼ�����ɹ��Ļ�Ҳ��ʼ��һ��FAT	
	printf("SD init. \r\n");    
	SD.init();
	if(SD.flag!=NOTHING_FAILED)
	{
		printf("  failed!  ");
		while(1);
	}

//�õ�����ʵ����ʹ�õ����пռ�
	printf("Get disk fat size. \t");
	fsize=SD.getDiskSize();
	if(SD.flag==FR_OK)
	{
		printf(" fatsize=%d KB \r\n",(uint32_t)(fsize>>10));
	}
	else
	{
		printf(" errflag=%x ",SD.flag);
		while(1);
	}

//�õ�����ʵ����ʹ�õ�ʣ��ռ�	
	fsize=SD.getDiskFree();
	printf("Get free fat size. \t");
	if(SD.flag==FR_OK)
	{
		printf("freesize=%d KB \r\n",(uint32_t)(fsize>>10));
	}
	else
	{
		printf(" errflag=%x ",SD.flag);
		while(1);
	}

//��ӡSD����Ϣ
	printf("Get SD information. \t");
	SD.print_disk_info();
	printf("%s\r\n",SD.buffer);


//��Ŀ¼����û��dir0���ļ���
//�������ɾ��������һ���µ��ļ���
	printf("Does the folder dir0 exist? \r\n");
	if(SD.isDir("dir0")==1)
	{
		printf("  yes.");
		printf(" Prepare use fuction del to delete the folder dir0,");
		if(SD.del("dir0"))//������ļ��������ж�����ɾ��������
		{
			printf("  del success. ");
		}
		else
		{
			printf(" errflag=%d.",SD.flag);
			printf(" When dir0 have subfolders or files, it doesnt work if we use the fuction del. We should use deldirall. ");
			printf(" Prepare use fuction deldirall to delete the folder dir0, ");
			if(SD.deldirall("dir0")==1)//����ɾ��
			{
				printf("delall success. ");		
			}
			else 
			{
				printf(" delall err, there are something wrong! please tell author.\n ");
				while(1);
			}
		}
	}
	else
	{	
		printf("no.");
	}


	printf("\r\nDoes the folder dir0 exist? \r\n");
	if(SD.isDir("dir0")==1)
	{
		printf(" yes. ");
		printf(" There are something WRONG! please tell author.\n ");
		while(1);
	}
	else
	{
		printf("  There is no folder dir0, now create the folder. ");
		if(SD.create("dir0"))
		{
			printf(" success ");
		}
		else
		{
			printf(" failed  ");
			while(1);
		}

	}

//��ȡ��Ŀ¼�¶��ٸ��ļ�
	printf("\r\nGet the number of files in the folder dir0, it should be 0. \r\n");
	filecnt=SD.numFiles("dir0");
	if(filecnt<0)
	{
		printf(" err, filecnt=%d ",filecnt);
		while(1);
	}
	else
	{
		printf("filecnt=%d ",filecnt);
		if(filecnt!=0)
		{
			printf(" WRONG! ");
			while(1);
		}	
	}


//���������ļ������ļ���
	printf("\r\nCreate some files and subfolders. \r\n");
	SD.create("dir0/file1.txt");
	SD.create("dir0/file2.txt");
	SD.create("dir0/file3.txt");
	SD.create("dir0/file7.txt");

 	SD.create("dir0/04");
	SD.create("dir0/04/004");
	SD.create("dir0/04/004/0004");
	SD.create("dir0/04/004/file0004.txt");

	SD.mkdir("dir0/05");
	SD.create("dir0/06");

//������ɵ�dir0/05�ļ��д治����
	printf("\r\nDoes the folder dir0/05 exist?\r\n");
	if(SD.isDir("dir0/05")==1)
	{
		printf(" yes. ");

	}
	else
	{
			printf(" WRONG! ");
			while(1);
	}

//��ʹ����ɾ���ļ�������ٴμ���ļ���dir0/05�治����
	printf("\r\nUse the function delDir to delete dir0/05. \r\n");
	SD.delDir("dir0/05");
	printf(" Check if the dir0/05 exist. ");
	if(SD.isDir("dir0/05")==1)
	{
		printf(" exist. ");
		printf(" There are something WRONG! please tell author.\n ");
		while(1);
	}
	else
	{
			printf(" no. ");
	}
		
//������ɵ�dir0/file7.txt�ļ��治����
	printf("\r\nDoes the file dir0/file7.txt exist?\r\n");
	if(SD.isFile("dir0/file7.txt")==1)
	{
		printf(" yes. ");

	}
	else
	{
		printf(" no. ");
		printf(" There are something WRONG! please tell author.\n ");
		while(1);
	}


//�õ���ǰ�ļ���dir0����ļ���������������4��
	printf("\r\nGet the number of files in the folder dir0, it should be 4(file1.txt,file2.txt,file3.txt,file7.txt). \r\n");
	filecnt=SD.numFiles("dir0");
	printf("  filecnt=%d. ",filecnt);
	if(filecnt!=4)
	{
			printf(" WRONG! ");
			while(1);				
	}

//ɾ���ļ�
	printf("\r\nDelete the file file7.txt in the folder dir0\r\n");
	SD.del("dir0/file7.txt");

	printf("\r\n  Get the number of files in the folder dir0, it should be 3(file1.txt,file2.txt,file3.txt). \r\n");
	filecnt=SD.numFiles("dir0");
	printf("  filecnt=%d. ",filecnt);
	if(filecnt!=3)
	{
			printf(" WRONG! ");
			while(1);				
	}

//д�����ݵ��ļ�����
	printf("\r\nWrite some datas in dir0/file1.txt.\r\n");
	SD.writeSD("dir0/file1.txt", "I am a frog, do you like me? My\ngirl\nis\na\ngreat\nwoman\ndont\nshe?\nyes,\nshe\nis !!!!", 0);

//�õ��ļ�dir0/file1.txt�Ĵ�С
	printf("\r\nGet the size of dir0/file1.txt. \r\n");
	filesize=SD.getFileSize("dir0/file1.txt");
	if(filesize>=0)
	{
		printf("filesize=%d ",filesize);
	}
	else
	{
			printf(" WRONG! ");
			while(1);	
	}


//���ļ���������ݶ�����	
	printf("\r\nGet 20 datas in dir0/file1.txt and printf them.\r\n");
	SD.readSD("dir0/file1.txt", readstr1, 0,20);
	printf("<%s>",readstr1);

	printf(" Get 20 datas in dir0/file1.txt from offset=10 and printf them.");
	SD.cat("dir0/file1.txt", 10,20);
	printf("<%s>",SD.buffer);

	printf(" Get 20 datas in dir0/file1.txt from offset=20 and printf them.");
	SD.catBin("dir0/file1.txt", 20,20);
	printf("<%s>",SD.bufferBin);

//���ļ���������ݶ�����	
	readstr1[0]=0x00;
 	printf("\r\nGet 20 datas in dir0/file2.txt printf them. them should nothing.\r\n");
	SD.readSD("dir0/file2.txt", readstr1, 0,20);
	printf("<%s>",readstr1);

//���ж�ȡ�ļ���������� 
	printf("\r\nGet 2 packet datas in dir0/file1.txt from offset=2 and printf them. Notice: the last data of each packet datas is enter(0x13).\r\n");
	SD.catln ("dir0/file1.txt", 1, 4);
	printf("<%s>",SD.buffer);
	
	printf("\r\n OK end");
}

void loop()
{
	while(1);
}
#endif // end SDIOFAT





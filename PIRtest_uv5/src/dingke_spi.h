#ifndef __DINGKE_SPI_H
#define __DINGKE_SPI_H

#ifdef __cplusplus
extern "C"{
#endif

void SPI2_Init(void);


//��SPI2��ʼ��Ϊ����FLASH��;
void FLASH_SPI_Init(void);

//��ʼ������SPI����Ƭѡ���Ų��ø߲�ѡ��
void CSPin_init(void);
u8 SPI2_RWByte(u8 byte);

#ifdef __cplusplus
}
#endif


#endif


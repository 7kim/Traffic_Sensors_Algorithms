#ifndef __DINGKE_DELAY_H
#define __DINGKE_DELAY_H			   
#include <stm32f4xx.h>
//////////////////////////////////////////////////////////////////////////////////	 

#define XINJIUBAN 1 //0�ɰ� 1Ŀǰ�°� 
////////////////////////////////////////////////////////////////////////////////// 
#ifdef __cplusplus
extern "C"{
#endif


void delay_ms(uint16_t nms);
void delay_us(uint32_t nus); 

#ifdef __cplusplus
} // extern "C"
#endif 



#endif






























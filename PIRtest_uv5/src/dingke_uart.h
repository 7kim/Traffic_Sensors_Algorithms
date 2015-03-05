
#ifndef __DINGKE_USART_H
#define __DINGKE_USART_H

#include <stdio.h>
#include <inttypes.h>

//#include "delay.h"	
//#include "retarget.h"
#include "dingke_timer.h" //��Ϊ�����и�����xbee�ĺ�����˳��Ѷ�ʱ��3������
#ifdef __cplusplus
extern "C"{
#endif

#define UARTRECEMPTY  -1//���մ��ڵ����ݣ�����û���������Լ������Ļ����������飩����
#define UARTRUNSUPPORT  -2
#define UARTRECERRELSE  -3//���յ�������������



//���洮��4 5 �ǿ����õģ�����ͨ���ġ� ����������ʹ��ԭ������
#define USEUSART4 0//����4��ӦPA0 PA1�ڣ���PA0�ڱ�ds3231�ģ�/INT SQW��ռ�ã�����Ҫ�ô���4�Ͳ�����ds3231
#define USEUSART5 0//����5��ӦPC2 PD2 �������ڷֱ�SD��clk cmdռ�ã�����Ҫ�ô���5�Ͳ�����SD��


// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer (I think), in which rx_buffer_head is the index of the
// location to which to write the next incoming character and rx_buffer_tail
// is the index of the location from which to read.

//#define RX_BUFFER_SIZE 612
#define RX_BUFFER_SIZE 9000
//#define RX_BUFFER_SIZE_3 4000

#define RX80_BUFFER_SIZE 8000
#define RX_BUFFER_SIZE_3 RX_BUFFER_SIZE
#define RX_BUFFER_SIZE_1 100
#define RX_BUFFER_SIZE_2 500
#define RX_BUFFER_SIZE_6 100
#if USEUSART4==1
#define RX_BUFFER_SIZE_4 RX_BUFFER_SIZE
#endif

#if USEUSART5==1
#define RX_BUFFER_SIZE_5 RX_BUFFER_SIZE
#endif

void Mux_poweron(void);
void Mux_poweroff(void);
void muluart6init(void)	;
void muluart6choose(unsigned char choose);

void monitor_on(void);
void monitor_onuart3TX(void);
void monitor_onuart3RX(void);
void monitor_offuart3TX(void);
void monitor_offuart3RX(void);

void Xbee_poweron(void);
void Xbee_poweroff(void);
void beginxbee(long baud, uint8_t portNum);
void beginSerial(long, uint8_t);
void chooseuartinterrupt(uint8_t portNum);
void closeSerial(uint8_t);
void serialWrite(unsigned char, uint8_t);
int serialAvailable(uint8_t);
int serialRead(uint8_t);
void serialFlush(uint8_t);

int serialPreRx80Available(void) ;
int serialPreRx80Read(void);
uint8_t  handle1msprerx80(void);
int serialRx80Available(void);
int serialRx80Read(void);

//void printMode(int, uint8_t);
void printByte(unsigned char c, uint8_t);
//void printNewline(uint8_t);
void printString(const char *s, uint8_t);
//void printInteger(long n, uint8_t);
//void printHex(unsigned long n, uint8_t);
//void printOctal(unsigned long n, uint8_t);
//void printBinary(unsigned long n, uint8_t);
void printIntegerInBase(unsigned long n, unsigned long base, uint8_t);

void uartsendstr(char *s, uint8_t len,uint8_t portNum);
int serialReadstr(uint8_t *str, uint8_t len,uint8_t portNum);
void serialWritestr(char *s, uint8_t len,uint8_t portNum);

//void setup(void);
//void loop(void);

void beginMb7076(void);
int readMb7076( int* value);




#ifdef __cplusplus
} // extern "C"
#endif




#endif

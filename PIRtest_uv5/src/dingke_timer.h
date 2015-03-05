/*
 *  Modified for Waspmote by D. Cuartielles & A. Bielsa, 2009
 *
 *  Copyright (c) 2005-2006 David A. Mellis
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
   
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 

#ifndef __DINGKE_TIMER_H
#define __DINGKE_TIMER_H

#include <stdio.h>
#include <inttypes.h>

#include "dingke_delay.h"
	
#include "dingke_retarget.h"

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

unsigned long millis(void);
//unsigned long millisTim2(void);
void delay(unsigned long);


void setIPF_(uint8_t peripheral);
void resetIPF_(uint8_t peripheral); 

void setup(void);
void loop(void);

void Timer3_Init(u16 cnt,u32 hz);
unsigned char  Timer2_Init(u16 cnt,u32 hz);

void beginMb7076(void);
int readMb7076( int* value);




#ifdef __cplusplus
} // extern "C"
#endif




#endif

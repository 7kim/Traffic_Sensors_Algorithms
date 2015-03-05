
/*
�����ã�    �ú�������Ҫ������������Լ��������صĲ���
�����ߣ�    ���ܱ�
����ʱ�䣺  09��5��29��
�汾�ţ�    v1.0
//////////////////////////////////////////////////////////////
�⺯����
��������롢���
����ļӷ����������������˷�
���󡣡���������
*/
#ifndef _MATRIX_H
#define _MATRIX_H
#endif


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#include <memory.h>
#include <stdint.h>




#ifndef uint 
#define uint unsigned int 
#endif

#ifndef uchar
#define uchar unsigned char
#endif  

#ifndef ulong
#define ulong unsigned long
#endif  

//////////////////////////////////////////////////////////////////
//�������Ͷ���
typedef enum  tagMAT_DATA_TYPE
{
    MAT_DATA_TYPE_CHAR    =     1,
    MAT_DATA_TYPE_UCHAR   =    2,
	MAT_DATA_TYPE_INT     =     3,
	MAT_DATA_TYPE_UINT    =		4,
	MAT_DATA_TYPE_LONG    =		5,
    MAT_DATA_TYPE_ULONG   =    6,
	MAT_DATA_TYPE_FLOAT   =		7,
	MAT_DATA_TYPE_DOUBLE  =		8,
	MAT_DATA_TYPE_MAX     =		8,
	MAT_DATA_TYPE_NULL    =     0
}MAT_DATA_TYPE;

//////////////////////////////////////////////////////////////////
//����Ľṹ
typedef struct tagMat
{
    uint  type;    //��������
	uint  step;
    union         //����ָ��
    {
        uchar   * ptr;
        uchar   * uc;   
		char    * c  ;		
        int		* i;		
		uint    * ui;		
		long    * l;		
		ulong   * ul;	    
        float   * fl;		
        double  * db;		
    } data;

    uint rows;    //��������
    uint cols;    //��������

}CMat;

#ifdef __cplusplus
extern "C"{
#endif

//�����ĸ���������ƤƤ�Լ�д��
int zppinversematrix(float *a, uint16_t k,float *c);
//A+B->C
void zppaddmatrix(uint16_t numRows,uint16_t numCols,float *A,float *B,float *C)	;
//A*B->C
void zppmulmatrix(uint16_t numRows,uint16_t numCols,float *A,float *B,float *C);
//A->C
void zpptransposematrix(uint16_t numRows,uint16_t numCols,float *A,float *C);

//����������ʵ�������һ����ֻ������uint16_t��
void zppaddmatrix16(uint16_t numRows,uint16_t numCols,int16_t *A,int16_t *B,int16_t *C);
//A*B->C
void zppmulmatrix16(uint16_t numRows,uint16_t numCols,int16_t *A,int16_t *B,int16_t *C);
//A->C
void zpptransposematrix16(uint16_t numRows,uint16_t numCols,int16_t *A,int16_t *C);



//////////////////////////////////////////////////////////////////
//�궨��
//�ж��ǲ���һ������,������һ���������͵�ָ��
#define IS_MAT(mat) \
	    (((CMat*)mat)->type <= MAT_DATA_TYPE_MAX) \
         &&( ((CMat*)mat)->rows > 0 )\
         &&( ((CMat*)mat)->cols > 0  \
        )

//�жϾ����Ƿ�Ϊ��
#define IS_EMPTY_MAT(mat)\
	    (IS_MAT(mat) &&  ((CMat*)mat)->data.ptr != NULL)

//�ж����������Ƿ���ȷ
#define IS_RIGHT_DATATYPE(type) \
	    ((MAT_DATA_TYPE)type <= MAT_DATA_TYPE_MAX)

//�ж������Ƿ���Ч
#define IS_VALID_XY(mat,x,y) \
	    (x >= 0 && x < ((CMat*)mat)->cols \
         && y >= 0 && y < ((CMat*)mat)->rows)
//////////////////////////////////////////////////////////////////

extern CMat   *CreateMat(uint cols,uint rows,MAT_DATA_TYPE type, void *data);
extern CMat   *SetMatData(CMat* mat , void *data);
extern void   *RealseMat(CMat* mat);
extern double GetData2D(CMat* mat,uint cols,uint rows);
extern double SetData2D(CMat* mat,uint cols,uint rows,double val,MAT_DATA_TYPE type);
extern void   PrintMat(CMat* mat);
extern CMat *ReshapeMat(CMat *mat,uint rows,uint cols);
extern CMat *AddMat(CMat *mat ,CMat *mat1,CMat *mat2);
extern CMat *SubMat(CMat *mat ,CMat *mat1,CMat *mat2);
extern CMat *MulMat(CMat *mat ,CMat *mat1,CMat *mat2);

extern CMat *TransposeMat(CMat *mat1,CMat *mat2);
//////////////////////////////////////////////////////////////////////////////////////////////////////
//������һЩ�ڲ�����
extern void* DataTypeTo(void *data,MAT_DATA_TYPE type);//>>>
extern uchar  mSizeOf(MAT_DATA_TYPE type);
extern uchar  *mGetAddr(CMat *mat , uint x ,uint y);
extern double mGetRealData(uchar * addr , MAT_DATA_TYPE type);
extern double mSetRealData(uchar * addr , MAT_DATA_TYPE type , double val);


#ifdef __cplusplus
} // extern "C"
#endif

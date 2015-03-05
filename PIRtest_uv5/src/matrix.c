#include "matrix.h"
#include <stdint.h>

//A+B->C
void zppaddmatrix16(uint16_t numRows,uint16_t numCols,int16_t *A,int16_t *B,int16_t *C)
{
	uint16_t i;
	uint16_t k;	
  for( i=0;i<numRows;i++){ 
    for( k=0;k<numCols;k++)
    {
      (*(C+i*numCols+k)) = (*(A+i*numCols+k)) + (*(B+i*numCols+k));
    }
  }
}
//A*B->C
void zppmulmatrix16(uint16_t numRows,uint16_t numCols,int16_t *A,int16_t *B,int16_t *C)
{
	uint16_t i;
	uint16_t k;	
  for(i=0;i<numRows;i++){ 
    for(k=0;k<numCols;k++)
    {
      (*(C+i*numCols+k)) = (int16_t)((*(A+i*numCols+k)) * (*(B+i*numCols+k)));
    }
  }
}
//A->C
void zpptransposematrix16(uint16_t numRows,uint16_t numCols,int16_t *A,int16_t *C)//
{
	uint16_t i;
	uint16_t k;	
  for(i=0;i<numRows;i++){ 
    for(k=0;k<numCols;k++)
    {
      (*(C+k*numRows+i)) = (int16_t)(*(A+i*numCols+k)) ;
    }
  }
}


//A+B->C
void zppaddmatrix(uint16_t numRows,uint16_t numCols,float *A,float *B,float *C)
{
	uint16_t i;
	uint16_t k;	
  for( i=0;i<numRows;i++){ 
    for( k=0;k<numCols;k++)
    {
      (*(C+i*numCols+k)) = (*(A+i*numCols+k)) + (*(B+i*numCols+k));
    }
  }
}
//A*B->C
void zppmulmatrix(uint16_t numRows,uint16_t numCols,float *A,float *B,float *C)
{
	uint16_t i;
	uint16_t k;	
  for(i=0;i<numRows;i++){ 
    for(k=0;k<numCols;k++)
    {
      (*(C+i*numCols+k)) = ((*(A+i*numCols+k)) * (*(B+i*numCols+k)));
    }
  }
}
//A->C
void zpptransposematrix(uint16_t numRows,uint16_t numCols,float *A,float *C)//
{
	uint16_t i;
	uint16_t k;	
  for(i=0;i<numRows;i++){ 
    for(k=0;k<numCols;k++)
    {
      (*(C+k*numRows+i)) = (*(A+i*numCols+k)) ;
    }
  }
}
//������Щ���ɸ���������Ϊ��������׼���ġ�
//�����кܶ෽ʽ�����������������10���󣨾����Ǹ��Խ��߶���1����Ȼ���б任�õ������
//���û�������᷵��-1
//�����жԻ�
void zijuhangchange(float *a,uint16_t row, uint16_t col, uint16_t row1, uint16_t row2)
{
	uint16_t i;
	float temp;
	for(i=0;i<col;i++)
	{
		temp = *(a+col*row1+i);
		*(a+col*row1+i) = *(a+col*row2+i);		
		 *(a+col*row2+i) = temp;
	}
}/**/
//a row*col -> c row1 * 2col//��a�ֲ�����������֣��ұߵ�Ϊcol1����c
void jianjietoyou(float *a, float *c, uint16_t row, uint16_t col,uint16_t col1)
{
	uint16_t m,n;
	for(m=0;m<row;m++)
	{
		for(n=0;n<col1;n++)
		{
			*(c+m*col1+n) =*(a+m*col+(col-col1)+n) ;
		}
	}
}

//a row*col b row*col   -> c row * 2col//����ƴ�Ӿ���
void pingjiezuoyou(float *a, float *b, float *c, uint16_t row, uint16_t col)
{
	uint16_t m,n;
	for(m=0;m<row;m++)
	{
		for(n=0;n<col;n++)
		{
			*(c+m*2*col+n) = *(a+m*col+n);
		}
		for(n=0;n<col;n++)
		{
			*(c+m*2*col+col+n) = *(b+m*col+n);
		}
	}
}
//��ʼ����������Խ���Ϊ1������Ϊ0
void init10juzhen(float *a, uint16_t k)
{
	uint16_t i;
	for(i=0;i<k*k;i++)
		*(a+i)=0;
	for(i=0;i<k;i++)
		*(a+i*k+i)=1;
}
float absfloat(float a)
{
	if(a<0.0)return -a;
	else return a;
}

//Ѱ�Ҿ���ָ��jibie�������½ǣ�������ǰjiebie���У��ľ��� ��ͷֵ��С����һ��//�������С��ָ����ֵ��С
int minkaitou(float *a, uint16_t row, uint16_t col, uint16_t jibie)
{
	uint16_t m;
	float min;
	int minjibie;
	float panbie0;
	//���ж���û�з�0 ��ֵ���������0ֵ���Ƿ��ش���-1����������ǿ϶�û��������
	//��һ����0ֵΪ minֵ��
	minjibie=-1;
	for(m=jibie;m<row;m++)
	{
		panbie0 = absfloat(*(a+m*col+jibie));
		if((panbie0>-0.0001)&&(panbie0<0.0001));
		else 
		{
			minjibie=m;
			min = panbie0;
			break;
		}
	}
	if(minjibie==-1)return -1;


	//printf("first min =%f \n",min);
	for(m=jibie+1;m<row;m++)
	{
		//printf("m=%d zhi=%f ",m,*(a+m*col+jibie));
		panbie0 = absfloat(*(a+m*col+jibie));
		if((panbie0>-0.0001)&&(panbie0<0.0001))continue;

		if(panbie0<min)
		{			
			min = panbie0;
			minjibie = m;
			//printf(" now min =%f  minjibie+%d \n",min,minjibie);
		}
	}
	return minjibie;
}

//����ָ����i jԪ�ر��1����ô������һ����Ҫ���Զ��٣�����һ�ж������������Ŀ�ľ���Ϊ��i j���Ԫ�ر�Ϊ1
void juzhenchangelementto1(float *a, uint16_t row, uint16_t col, uint16_t i, uint16_t j)
{
	uint16_t m;
	if((*(a+i*col+j)>0.9999)&&(*(a+i*col+j)<1.0001))return;

	for(m=0;m<col;m++)
	{
		if(m==j)continue;
		else *(a+i*col+m) = *(a+i*col+m)/(*(a+i*col+j));
	}
	*(a+i*col+j)=1.0;
}

//���� ָ���м�ȥ��һ��ָ���е�*bei
void juzhensub(float *a, uint16_t row, uint16_t col, uint16_t row1, float bei, uint16_t row2)
{
	uint16_t m;
	if((bei>-0.0001)&&(bei<0.0001))return;
	for(m=0;m<col;m++)
	{
		*(a+row2*col+m) = *(a+row2*col+m) - (*(a+row1*col+m))*bei;
	}
}
//���������������10���󣨾����Ǹ��Խ��߶���1����Ȼ���б任�õ������
//���û�������᷵��-1
int zppinversematrix(float *a, uint16_t k,float *c)
{
	float *b;
	float *d;
	uint16_t m,n;
	uint16_t jibie=0;
	int hang=0;
	uint16_t i1;
	b = (float *)malloc(sizeof(float)*k*2*k);
	if(b==NULL){
		//printf(" no enough room for fb ");
		return -2;
	}

	d = (float *)malloc(sizeof(float)*k*k);
	if(d==NULL){
		//printf(" no enough room for fd ");
		return -3;
	}
	//�õ��Խ��߶���1���Ǹ�����
	init10juzhen(d, k);
	//��ԭ����ͶԽ��߶���1�ľ�������ƴ��һ��
	pingjiezuoyou(a, d, b, k, k);
	free(d);
//	for(m=0;m<k;m++)
//	{
//		for(n=0;n<2*k;n++)
//			printf("%f ",*(b+m*2*k+n));
//		printf("\n");
//	}

	for(jibie=0;jibie<k;jibie++)
	{
		hang=minkaitou(b, k, 2*k, jibie);		
//		printf("hang=%d \n",hang);
		if(hang==-1)
		{
			printf(" no inv \n");
			return -1;
		}

		zijuhangchange(b,k, 2*k, jibie, hang);
//		for(m=0;m<k;m++)
//		{
//			for(n=0;n<2*k;n++)
//				printf("%f ",*(b+m*2*k+n));
//			printf("\n");
//		}

		juzhenchangelementto1(b, k, 2*k, jibie, jibie);
//		for(m=0;m<k;m++)
//		{
//			for(n=0;n<2*k;n++)
//				printf("%f ",*(b+m*2*k+n));
//			printf("\n");
//		}
//		printf("to 1\n");

//		for(i1=0;i1<k;i1++)
//		{
//			if(i1==jibie)continue;
//			printf(" *(b+i1*2*k+jibie)=%f \n",*(b+i1*2*k+jibie));
//			juzhensub(b, k, 2*k, jibie, *(b+i1*2*k+jibie), i1);	
//		}
//		for(m=0;m<k;m++)
//		{
//			for(n=0;n<2*k;n++)
//				printf("%f ",*(b+m*2*k+n));
//			printf("\n");
//		}
//		printf("sub\n");
	}


	jianjietoyou(b, c, k, 2*k,k);
//	for(m=0;m<k;m++)
//	{
//		for(n=0;n<k;n++)
//			printf("%f ",*(c+m*k+n));
//		printf("\n");
//	}


	free (b);

	return 0;

}









/*************************************************
�������� mSizeOf
�������� ��������������ռ���ֽ���
������MAT_DATA_TYPE ���͵ı���
���أ������ͷָ��
˵����
**************************************************/
uchar mSizeOf(MAT_DATA_TYPE type)
{
     if (IS_RIGHT_DATATYPE(type))
     {
		 switch (type)
		 {
		 case MAT_DATA_TYPE_CHAR:
			 return sizeof(uchar);
			 //break;
		 case MAT_DATA_TYPE_UCHAR:
			 return sizeof(char);
			 //break;
		 case MAT_DATA_TYPE_INT:
			 return sizeof(int);
			 //break;
		 case MAT_DATA_TYPE_UINT:
			 return sizeof(uint);
			 //break;
		 case MAT_DATA_TYPE_LONG:
			 return sizeof(long);
			 //break;
		 case MAT_DATA_TYPE_ULONG:
			 return sizeof(ulong);
			 //break;
		 case MAT_DATA_TYPE_FLOAT:
			 return sizeof(float);
			 //break;
		 case MAT_DATA_TYPE_DOUBLE:
			 return sizeof(double);
			 //break;
     }

	}
	 return 0;
}
/*************************************************
��������   DataTypeTo
�������� �������ݽ���ת��
������     MAT_DATA_TYPE ���͵ı���
           data void*ָ��
���أ�     ����ת�����ָ�룬
˵����     ���غ�����ݱ������ǿ����ת��
**************************************************/
void* DataTypeTo(void *data,MAT_DATA_TYPE type)
{
     if (IS_RIGHT_DATATYPE(type))
     {
		 switch (type)
		 {
		 case MAT_DATA_TYPE_CHAR:
			 return (uchar*)data;
			 //break;
		 case MAT_DATA_TYPE_UCHAR:
			 return (char*)data;
			 //break;
		 case MAT_DATA_TYPE_INT:
			 return (int*)data;
			 //break;
		 case MAT_DATA_TYPE_UINT:
			 return (uint*)data;
			 //break;
		 case MAT_DATA_TYPE_LONG:
			 return (long*)data;
			 //break;
		 case MAT_DATA_TYPE_ULONG:
			 return (ulong*)data;
			 //break;
		 case MAT_DATA_TYPE_FLOAT:
			 return (float*)data;
			 //break;
		 case MAT_DATA_TYPE_DOUBLE:
			 return (double*)data;
			 //break;
     }

	}
	 return NULL;
}
/*************************************************
��������   mGetAddr()
�������� ������ָ��x y �ĵ�ַ
������     
���أ�     ��������uchar *
˵����
**************************************************/
uchar * mGetAddr(CMat *mat , uint x ,uint y)
{
	uchar *ptr;
	if ( mat==NULL )
    {
		return NULL;
    }
	if ( !IS_MAT(mat) )       //is mat
    {
		return NULL;
    }
	if (! IS_EMPTY_MAT(mat)) //data is valid
	{
		return NULL;
	}
    if (IS_VALID_XY(mat,x,y) ) //�ж�xy��Ч
    {
		ptr = (uchar*)(mat->data.ptr + y * mat->step + x * mSizeOf(mat->type));
    }
	return ptr ;	
}
/*************************************************
��������   mGetRealData()
�������� �������������ͷ��ظõ�ַ��������
������     
���أ�     double����
˵����     
**************************************************/
double mGetRealData(uchar * addr , MAT_DATA_TYPE type)
{
	 double val = 0 ;
     
     if (IS_RIGHT_DATATYPE(type))
     {
		 switch (type)
		 {
		 case MAT_DATA_TYPE_CHAR:
			 val = * ((char*)addr);
			 break;
		 case MAT_DATA_TYPE_UCHAR:
			 val =  * ((uchar*)addr);
			 break;
		 case MAT_DATA_TYPE_INT:
		 	 val =  * ((int*)addr);
			 break;
		 case MAT_DATA_TYPE_UINT:
			 val =  * ((uint*)addr);
			 break;
		 case MAT_DATA_TYPE_LONG:
			 val =  * ((long*)addr);
			 break;
		 case MAT_DATA_TYPE_ULONG:
			 val = * ((ulong*)addr);
			 break;
		 case MAT_DATA_TYPE_FLOAT:
			 val =  * ((float*)addr);
			 break;
		 case MAT_DATA_TYPE_DOUBLE:
			 val =  * ((double*)addr);
			 break;
		 }
		 
	 }
	 else
	 {
		return -1;
	 }

	 return val ;
}
/*************************************************
��������   mSetRealData()
�������� �������������ͷ��ظõ�ַ��������
������     
���أ�     double����
˵����     
**************************************************/
double mSetRealData(uchar * addr , MAT_DATA_TYPE type , double val)
{   
     if (IS_RIGHT_DATATYPE(type))
     {
		 switch (type)
		 {
		 case MAT_DATA_TYPE_CHAR:
			 * ((char*)addr) = (char)val;
			 break;
		 case MAT_DATA_TYPE_UCHAR:
			 * ((uchar*)addr) = (uchar)val;
			 break;
		 case MAT_DATA_TYPE_INT:
		 	 * ((int*)addr) = (int)val;
			 break;
		 case MAT_DATA_TYPE_UINT:
			 * ((uint*)addr) = (uint)val;
			 break;
		 case MAT_DATA_TYPE_LONG:
			 * ((long*)addr) = (long)val;
			 break;
		 case MAT_DATA_TYPE_ULONG:
			 * ((ulong*)addr) = (ulong)val;
			 break;
		 case MAT_DATA_TYPE_FLOAT:
			 * ((float*)addr) = (float)val;
			 break;
		 case MAT_DATA_TYPE_DOUBLE:
			 * ((double*)addr) = (double)val;
			 break;
		 }
		 
	 }
	 else
	 {
		return -1;
	 }

	 return val ;
}
/*************************************************
�������� CreateMatHeader
�������� ������һ������
������
     cols ����
	 rows ����
	 type ��������
	 data ����ָ��
���أ������ͷָ��
˵����������ʹ�õ�ʱ�����data == NULL ���򴴽��ռ�
**************************************************/
CMat *CreateMat(uint cols,uint rows,MAT_DATA_TYPE type, void *data)
{
	CMat *tmat ;
	tmat = (CMat *)malloc(sizeof(CMat));                   //������Ҫ���¿�һ�£�voidָ�벻֪�����ٶ��ٿռ�
	if(cols <= 0 || rows <= 0 || type > MAT_DATA_TYPE_MAX)
	{
		return (CMat*)NULL;
	}
	tmat->rows = rows;
	tmat->cols = cols;
	tmat->type = type;
	tmat->step = mSizeOf(type) * cols;
    tmat->data.ptr = malloc(rows*tmat->step);
	memset(tmat->data.ptr,0,rows *tmat->step);
	if (data != NULL)
	{
		memcpy(tmat->data.ptr,data,rows *tmat->step);
	}
	return tmat ;	   
}
/*************************************************
��������SetMatData
�������� �����þ��������
������
    mat  �����ָ��
	data ����
���أ������ͷָ��
˵����
**************************************************/
CMat *SetMatData(CMat* mat , void *data)
{
	if ( mat==NULL )
    {
		return NULL;
    }
    if ( !IS_MAT(mat) )
    {
		return (CMat *)NULL;
    }
    memcpy(mat->data.ptr,data,mat->rows *mat->step);
    return mat ;	   
}
/*************************************************
��������RealseMat
�������� ���ͷž���ռ�Ŀռ�
������
    mat  �����ָ��
���أ�
˵����
**************************************************/
void *RealseMat(CMat* mat)
{
	if ( mat==NULL )
    {
		return NULL;
    }
    if ( !IS_MAT(mat) )
    {
		return (CMat *)NULL;
    }
	free(mat->data.ptr);
	free(mat);
    return mat ;	   
}
/*************************************************
��������GetData2D
�������� ����þ��������
������
    mat  �����ָ��
	rows -->y
	cols -->x
���أ�
˵����
**************************************************/
double GetData2D(CMat* mat,uint cols,uint rows)
{
	uchar *ptr = NULL;
	double val =0 ;
	if ( mat==NULL )
    {
		return -1;
    }
    if ( !IS_MAT(mat) )
    {
		return -1;
    }
	if (! IS_EMPTY_MAT(mat))
	{
		return -1;
	}
    
	ptr = mGetAddr(mat,cols,rows);
	if (ptr)
	{
		val = mGetRealData(ptr,mat->type);
	}

	return val;	
}
/*************************************************
��������SetData2D
�������� ����þ��������
������
    mat  �����ָ��
	rows -->y
	cols -->x
	val  -->���õ�ֵ����������
	type -->���õ����ͣ����Ϊ0��ʹ��Ĭ�Ͼ�������ͣ�Ҳ����db���ͣ�����ʹ�����õ�����
���أ�
˵����
**************************************************/
double SetData2D(CMat* mat,uint cols,uint rows,double val,MAT_DATA_TYPE type)
{
	uchar *ptr = NULL;

    if ( mat==NULL )
    {
		return -1;
    }
    if ( !IS_MAT(mat) )
    {
		return -1;
    }
	if (! IS_EMPTY_MAT(mat))
	{
		return -1;
	}
    
	ptr  = mGetAddr(mat,cols,rows);
	if (type == MAT_DATA_TYPE_NULL)
	{
		if (mSetRealData(ptr,mat->type,val) != val)
		{
			return -1;
		}
	}
	else
	{
		if (mSetRealData(ptr,type,val) != val)
		{
			return -1;
		}
	}

    return val;
}
/*************************************************
��������PrintMat
�������� ���������
������
    mat  �����ָ��
���أ�
˵����
**************************************************/
void  PrintMat(CMat* mat)
{
	uint rows=0;
	uint cols=0;
    if (IS_EMPTY_MAT(mat) )
    {
		for(rows=0; rows < mat->rows; rows++)//��
		{
			printf("\r\n");
			for (cols = 0 ;cols < mat->cols ; cols ++)
			{
				if (IS_RIGHT_DATATYPE(mat->type))
				{
					switch (mat->type)
					{
					case MAT_DATA_TYPE_CHAR:
						printf(" %4d " , (char)GetData2D(mat,cols,rows));
						break;
					case MAT_DATA_TYPE_UCHAR:
						printf(" %4d " , (uchar)GetData2D(mat,cols,rows));
						break;
					case MAT_DATA_TYPE_INT:
						printf(" %d" , (int)GetData2D(mat,cols,rows));
						break;
					case MAT_DATA_TYPE_UINT:
						printf(" %d" ,  (uint)GetData2D(mat,cols,rows));
						break;
					case MAT_DATA_TYPE_LONG:
						printf(" %d " ,  (long)GetData2D(mat,cols,rows));
						break;
					case MAT_DATA_TYPE_ULONG:
						printf(" %d " , (ulong)GetData2D(mat,cols,rows));
						break;
					case MAT_DATA_TYPE_FLOAT:
						printf(" %f " , (float)GetData2D(mat,cols,rows));
						break;
					case MAT_DATA_TYPE_DOUBLE:
						printf(" %f " , (double)GetData2D(mat,cols,rows));
						break;
					}
					
				}
			}
		}

	}
 
}
/*************************************************
��������    ReshapeMat
��������    �ı���������������
������
            mat
���أ�      �ı��Ժ�ľ���c*r = c1 * r1
˵����      
**************************************************/
CMat *ReshapeMat(CMat *mat,uint rows,uint cols)
{
	if (mat == NULL)
	{
		return NULL;
	}
	if (!IS_MAT(mat))
	{
		return NULL;
	}
	if (mat->cols * mat->rows != rows * cols)
	{
		return NULL;
	}
	mat->cols = cols;
	mat->rows = rows;
	mat->step = cols * mSizeOf(mat->type);

	return mat;
}
/*************************************************
��������    AddMat
��������    ����ӷ�
������
            mat mat1 mat2 ����ָ��
���أ�      ������ͬ��С�ľ���
˵����      mat���ⲿû�п��ٿռ�Ļ������ڲ�����ݼ�������ȥ������Ӧ�Ŀռ�
            mat�Ľ����mat�����������ͬ
			���mat����������е�һ����ͬ����ômat����ͬ���Ǹ����������ٶ�mat�ڲ���data�����ͷŸ����¿��ٵĲ���
			mat = mat1+mat2
**************************************************/
CMat *AddMat(CMat *mat ,CMat *mat1,CMat *mat2)
{
	uint rows =0;
	uint cols = 0;
	uint i = 0;
	uint j = 0;	
	double val =0 ;
	if (mat1 == NULL || mat2 == NULL )
	{   
		return NULL;
	}
	if (!IS_MAT(mat1) || !IS_MAT(mat2) )
	{   
		return NULL;
	}
	if (mat1->rows != mat2->rows || mat1->cols != mat2->cols )
	{
		return NULL;
	}
	rows = mat1->rows;
	cols = mat1->cols;
//	���������ж��ǲ��Ǿ�����Ϊ�����ⲿû�г�ʼ��������ʹ��IS_MAt
    if (mat == NULL)                                       //���mat���Ǿ��󣬸���MAT11��MAT2���������½�����
	{
		if (mat1->type == mat2->type)
		{
			mat = CreateMat(cols,rows,mat1->type,NULL);
		}
		else
		{
			mat = CreateMat(cols,rows,MAT_DATA_TYPE_DOUBLE,NULL);
		}
	}
	
	if (mat->cols != cols || mat->rows != rows)       
	{
		return NULL;
	}

    if ( !(mat->type > MAT_DATA_TYPE_NULL && mat->type <= MAT_DATA_TYPE_MAX) )    	 //���ԭ���������ǿյ�                
    {
		free(mat->data.ptr);
		mat->data.ptr = malloc(rows * cols * mSizeOf(MAT_DATA_TYPE_DOUBLE));
		for (i =0 ; i < rows ; i ++)
		{
			for (j =0 ;j < cols ;j++)
			{
				val = GetData2D(mat1,j,i) + GetData2D(mat2,j,i);
				if (SetData2D(mat,j,i,val,MAT_DATA_TYPE_DOUBLE) != val)
				{
					return NULL;
				}		
			}
		}
    }
	else
	{
		if (mat != mat1 && mat != mat2)                              //���mat��mat1 mat2������һ������
		{
			free(mat->data.ptr);                                     //�ͷ�ԭ�еĿռ䣬��������ڴ�й©
			mat->data.ptr = malloc(rows * cols * mSizeOf(mat->type));//���·���ռ�,����mat����������
			for (i =0 ; i < rows ; i ++)
			{
				for (j =0 ;j < cols ;j++)
				{
					val = GetData2D(mat1,j,i) + GetData2D(mat2,j,i);
					if (SetData2D(mat,j,i,val,mat->type) != val)
					{
						return NULL;
					}		
				}
			}
		}
		else if (mat == mat1 ||  mat == mat2)
		{
			for (i =0 ; i < rows ; i ++)
			{
				for (j =0 ;j < cols ;j++)
				{
					val = GetData2D(mat1,j,i) + GetData2D(mat2,j,i);
					if (SetData2D(mat,j,i,val,mat->type) != val)
					{
						return NULL;
					}		
				}
			}
		}
	
	}

	return mat;		
}


CMat *TransposeMat(CMat *mat1,CMat *mat2)
{
	uint rows =0;
	uint cols = 0;
	uint i = 0;
	uint j = 0;	
	double val =0 ;
	if (mat1 == NULL || mat2 == NULL )
	{   
		return NULL;
	}
	if (!IS_MAT(mat1) || !IS_MAT(mat2) )
	{   
		return NULL;
	}
	if (mat1->rows != mat2-> cols|| mat1->cols != mat2->rows )
	{
		return NULL;
	}

	rows = mat1->rows;
	cols = mat1->cols;
	for (i =0 ; i < rows ; i ++)
	{
		for (j =0 ;j < cols ;j++)
		{
			val = GetData2D(mat1,j,i) ;
			//val = 5;
			if (SetData2D(mat2,i,j,val,mat2->type) != val)
			{
				return NULL;
			}		
		}
	}
	return mat2;		
}




/*************************************************
��������    SubMat
��������    �������
������
            mat mat1 mat2 ����ָ��
���أ�      ������ͬ��С�ľ���
˵����      �� AddMat ��˵��
            mat = mat1 - mat2;
**************************************************/
CMat *SubMat(CMat *mat ,CMat *mat1,CMat *mat2)
{
	uint rows =0;
	uint cols = 0;
	uint i = 0;
	uint j = 0;	
	double val =0 ;
	if (mat1 == NULL || mat2 == NULL )
	{   
		return NULL;
	}
	if (!IS_MAT(mat1) || !IS_MAT(mat2) )
	{   
		return NULL;
	}
	if (mat1->rows != mat2->rows || mat1->cols != mat2->cols )
	{
		return NULL;
	}
	rows = mat1->rows;
	cols = mat1->cols;
	//	���������ж��ǲ��Ǿ�����Ϊ�����ⲿû�г�ʼ��������ʹ��IS_MAt
    if (mat == NULL)                                       //���mat���Ǿ��󣬸���MAT11��MAT2���������½�����
	{
		if (mat1->type == mat2->type)
		{
			mat = CreateMat(cols,rows,mat1->type,NULL);
		}
		else
		{
			mat = CreateMat(cols,rows,MAT_DATA_TYPE_DOUBLE,NULL);
		}
	}
	
	if (mat->cols != cols || mat->rows != rows)       
	{
		return NULL;
	}
	
    if ( !(mat->type > MAT_DATA_TYPE_NULL && mat->type <= MAT_DATA_TYPE_MAX)  )      	 //���ԭ���������ǿյ�                
    {
		free(mat->data.ptr);
		mat->data.ptr = malloc(rows * cols * mSizeOf(MAT_DATA_TYPE_DOUBLE));
		for (i =0 ; i < rows ; i ++)
		{
			for (j =0 ;j < cols ;j++)
			{
				val = GetData2D(mat1,j,i) - GetData2D(mat2,j,i);
				if (SetData2D(mat,j,i,val,MAT_DATA_TYPE_DOUBLE) != val)
				{
					return NULL;
				}		
			}
		}
    }
	else
	{
		if (mat != mat1 && mat != mat2)                              //���mat��mat1 mat2������һ������
		{
			free(mat->data.ptr);                                     //�ͷ�ԭ�еĿռ䣬��������ڴ�й©
			mat->data.ptr = malloc(rows * cols * mSizeOf(mat->type));//���·���ռ�,����mat����������
			for (i =0 ; i < rows ; i ++)
			{
				for (j =0 ;j < cols ;j++)
				{
					val = GetData2D(mat1,j,i) - GetData2D(mat2,j,i);
					if (SetData2D(mat,j,i,val,mat->type) != val)
					{
						return NULL;
					}		
				}
			}
		}
		else if (mat == mat1 ||  mat == mat2)
		{
			for (i =0 ; i < rows ; i ++)
			{
				for (j =0 ;j < cols ;j++)
				{
					val = GetData2D(mat1,j,i) - GetData2D(mat2,j,i);
					if (SetData2D(mat,j,i,val,mat->type) != val)
					{
						return NULL;
					}		
				}
			}
		}
		
	}
	
	return mat;		
	
}
/*************************************************
��������    MulMat
��������    ����˷�
������
            mat mat1 mat2 ����ָ��
���أ�      
˵����      �˷������� mat1��cols������������mat2��rows��������
**************************************************/
CMat *MulMat(CMat *mat ,CMat *mat1,CMat *mat2)
{
	uint rows =0;
	uint cols = 0;
	uint i = 0 ;
	uint j = 0 ;	
	uint n = 0 ;
	double val =0 ;
	if (mat1 == NULL || mat2 == NULL )
	{   
		return NULL;
	}
	if (!IS_MAT(mat1) || !IS_MAT(mat2) )
	{   
		return NULL;
	}
	if (mat1->cols != mat2->rows )    //�˷������� mat1��cols������������mat2��rows��������
	{
		return NULL;
	}
	rows = mat1->rows;                //�õ��Ľ����mat������rows����mat1�� ���� ������cols������mat2��cols
	cols = mat2->cols;
	//	���������ж��ǲ��Ǿ�����Ϊ�����ⲿû�г�ʼ��������ʹ��IS_MAt
    if (mat == NULL)                                       //���mat���Ǿ��󣬸���MAT11��MAT2���������½�����
	{
		if (mat1->type == mat2->type)
		{
			mat = CreateMat(cols,rows,mat1->type,NULL);
		}
		else
		{
			mat = CreateMat(cols,rows,MAT_DATA_TYPE_DOUBLE,NULL);
		}
	}
	
	if (mat->cols != cols || mat->rows != rows)       
	{
		return NULL;
	}
	
    if ( !(mat->type > MAT_DATA_TYPE_NULL && mat->type <= MAT_DATA_TYPE_MAX) )      	 //���ԭ�������Ͳ�����Ҫ��              
    {
		free(mat->data.ptr);
		mat->data.ptr = malloc(rows * cols * mSizeOf(MAT_DATA_TYPE_DOUBLE));
		for (i =0 ; i < rows ; i ++)
		{
			for (j =0 ;j < cols ;j++)
			{
				val = 0;
				for (n = 0 ; n < mat1->cols ; n++)
				{
					val += GetData2D(mat1,n,i) * GetData2D(mat2,j,n);				
				}	
				if (SetData2D(mat,j,i,val,MAT_DATA_TYPE_DOUBLE) != val)
				{
					return NULL;
				}	
			}
		}
    }
	else
	{
		if (mat != mat1 && mat != mat2)                              //���mat��mat1 mat2������һ������
		{
			free(mat->data.ptr);                                     //�ͷ�ԭ�еĿռ䣬��������ڴ�й©
			mat->data.ptr = malloc(rows * cols * mSizeOf(mat->type));//���·���ռ�,����mat����������
			for (i =0 ; i < rows ; i ++)
			{
				for (j =0 ;j < cols ;j++)
				{
					val = 0;
					for (n = 0 ; n < mat1->cols ; n++)
					{
						val += GetData2D(mat1,n,i) * GetData2D(mat2,j,n);				
					}	
					if (SetData2D(mat,j,i,val,mat->type) != val)
					{
						return NULL;
					}	
				}
			}
		}
		else if (mat == mat1 ||  mat == mat2)
		{
			for (i =0 ; i < rows ; i ++)
			{
				for (j =0 ;j < cols ;j++)
				{
					val = 0;
					for (n = 0 ; n < mat1->cols ; n++)
					{
						val += GetData2D(mat1,n,i) * GetData2D(mat2,j,n);				
					}	
					if (SetData2D(mat,j,i,val,mat->type) != val)
					{
						return NULL;
					}	
				}
			}
		}
		
	}

	return mat;		
}


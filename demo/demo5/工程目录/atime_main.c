#include "STC15F2K60S2.H"		 //�����滻REG52.H������ʹ�����ͷ�ļ�
#include "atime_iic.h"
#include "atime_debug.h"
#include "atime_app.c"


void main()
{
	unsigned int i;
	debug_init();

	while(1)
	{
		printf("%d \n",(unsigned int)debug_rand());
		for(i=0;i<50000;i++)
			wait_iicbus();

	}
}
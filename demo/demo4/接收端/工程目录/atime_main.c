#include "STC89C5xRC.H"		 //可以替换REG52.H，建议使用这个头文件
#include "atime_serial.h" 
#include "atime_lcd1602.h"	 //需要载入其他文件自行载入	
#include "atime_interrupt.c" //中断函数集合，存放中断函数，不需要可以不载入	 

void main()
{
	unsigned char a[14];
	unsigned char b[18];
	unsigned int ii;

	int_lcd1602(rightmove, cursornotdisplay);
	serial_int(enable, baud9600, disable);

	while(1)
	{
		if(temp[0]=='T')
		{
			a[0] =temp[0];	
			a[1] =temp[1];
			a[2] =temp[2];
			a[3] =temp[3];
			a[4] =temp[4];
			a[5] =temp[5];
			a[6] =temp[6];
			a[7] =temp[7];
			a[8] =temp[8];
			a[9] =temp[9];
			a[10] =temp[10];
			a[11] =temp[11];
			a[12] ='\0';
			a[13] ='\0';
			for(ii=0;ii<16;ii++)
			{
				if(a[ii]=='c')
					a[ii+1]='\0';
			}
		}
		if(temp[0]=='S')
		{
			b[0] =temp[0];	
			b[1] =temp[1];
			b[2] =temp[2];
			b[3] =temp[3];
			b[4] =temp[4];
			b[5] =temp[5];
			b[6] =temp[6];
			b[7] =temp[7];
			b[8] =temp[8];
			b[9] =temp[9];
			b[10] =temp[10];
			b[11] =temp[11];
			b[12] =temp[12];
			b[13] =temp[13];	
			b[14] =temp[14];
			b[15] ='\0';
			b[16] ='\0';
			b[17] ='\0';
			for(ii=0;ii<=16;ii++)
			{
				if(b[ii]=='m')
				{	
					b[ii+1]=' ';
					b[ii+2]=' ';
					b[ii+3]=' ';
				}

			}

		}
		print1602(a,0,1);
		print1602(b,1,1);
	}
}
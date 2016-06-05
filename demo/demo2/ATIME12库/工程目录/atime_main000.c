#include "STC12C5A60S2.H" 		 //�����滻REG52.H������ʹ�����ͷ�ļ�
#include "atime_lcd1602.h"	 	 //��Ҫ���������ļ���������	
#include "atime_18b20.h"

void main()
{
	unsigned char a[8];
	float i;
	bit j;
	int_lcd1602(rightmove, cursornotdisplay);
	while(1)
	{
		j =int_18b20();
		if(j ==0)
		{
			i =read_temper();
			translate(i,a);
			set1602(clear1602);
			print1602(a,1,3);
			waitms(1000);
		}
		else
		{
			print1602("Please Cheak",1,2);
		}
	}
}
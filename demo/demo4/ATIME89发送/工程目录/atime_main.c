#include "STC89C5xRC.H"		 //可以替换REG52.H，建议使用这个头文件
#include "atime_lcd1602.h"	 //需要载入其他文件自行载入	
#include "atime_18b20.h"
#include "atime_supersonic.h"
#include "atime_serial.h"


void main()
{
	bit j;
	float temper;
	unsigned int i;	
	unsigned char lcd_temp[6];

	int_lcd1602(rightmove, cursornotdisplay);
	serial_int(enable, baud9600, disable);
	while(1)
	{
		i =supersonic_test();
		translate_code(i,a);
		print1602(a,0,3);
		
		j =int_18b20();
		if(j == 0)
		{
			temper =read_temper();
			translate(temper,lcd_temp);
			print1602(lcd_temp,1,3);
			waitms(1000);
		}
		else
		{
			print1602("Please Cheak",1,2);
			waitms(500);			
			set1602(clear1602);
		}
	}
}
#include "STC12C5A60S2.H" 
#include "atime_lcd1602.h"
#include "atime_18b20_1.h"
#include "atime_serial.h"

float tem;
unsigned char temp_h=30,temp_l=25;


void main()
{
	
				unsigned char a[8];
				float i;
				bit j;
				int_lcd1602(rightmove, cursornotdisplay);
				while(1)
				{
					j =int_18b20_1();
					if(j ==0)
					{
						i =read_temper_1();
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
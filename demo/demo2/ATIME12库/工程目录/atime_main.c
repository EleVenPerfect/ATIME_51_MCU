#include "STC12C5A60S2.H" 
#include "atime_lcd1602.h"
#include "atime_18b20.h"
#include "atime_serial.h"
#include "atime_timer.h"
#include "atime_interrupt.c"


void main()
{
	unsigned char display_temp[8];

	led_1 = 0;
	led_2 = 0;
	serial_int(enable, baud9600, disable);
	int_lcd1602( rightmove, cursornotdisplay);
	int_interrupt( 0, negative_jump);
	int_interrupt( 1, negative_jump);
	main_timer(on,0);
	timer_8_int(0,200,normal);
	main_interrupt(on);

	while(1)
	{
		display_temp[0] = temp_set/10%10+0x30;
		display_temp[1] = temp_set%10+0x30;
		display_temp[2] = '\0';
		print1602( display_temp, 0,14);
		printchar1602(' ', 1, 15);

		ds18b20_exit =int_18b20();
		if( ds18b20_exit ==0 )
		{
			temperature = read_temper();
			translate( temperature, display_temp);
			clear1602_10(0);
			print1602( display_temp, 0, 0);
		}
		else
		{
			print1602( "Check IIC", 0, 1);

		}

		waitms(500);
	}
}

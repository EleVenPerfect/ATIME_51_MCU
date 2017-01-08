#include "STC12C5A60S2.H"		 //可以替换REG52.H，建议使用这个头文件
#include "atime_serial.h" 
#include "atime_iic.h"
#include "atime_app.c"

void main()
{
	serial_int(enable, baud14400, disable);

	while(1)
	{
		
	}
}
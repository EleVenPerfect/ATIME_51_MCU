#include "STC15F2K60S2.H"		 //可以替换REG52.H，建议使用这个头文件
#include "atime_debug.h"
#include "atime_app.c"
#include "atime_pca9685.h"

void main()
{
	debug_init();
	pca9685_reset();
	pca9685_setfreq(66);

	pca9685_setpwm(0,0,200);
	pca9685_setpwm(1,0,580);

   	pca9685_setpwm(2,0,400);
	pca9685_setpwm(3,0,220);

	while(1);
}
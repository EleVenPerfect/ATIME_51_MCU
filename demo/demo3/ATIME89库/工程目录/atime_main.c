#include "STC89C5xRC.H"		 //可以替换REG52.H，建议使用这个头文件 
#include "atime_timer.h"	 //中断配套函数库，如果需要调用中断相关子函数，需要载入
#include "atime_lcd1602.h"	 //需要载入其他文件自行载入	


void Timer0Init(void)		//5毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x00;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void Timer1Init(void)		//5毫秒@11.0592MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x00;		//设置定时初值
	TH1 = 0x00;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
}

void trans_to_lcd(unsigned int n,unsigned char lcd_temp[])
{
	lcd_temp[0] = n/10000       +0x30;
	lcd_temp[1] = n%10000/1000 +0x30;
	lcd_temp[2] = n%1000/100 +0x30;
	lcd_temp[3] = n%100/10 +0x30;
	lcd_temp[4] = n%10   +0x30;
	lcd_temp[5] = '\0';	
}

#include "atime_interrupt.c" 

void main()
{
	unsigned char lcd_temp[6];

	int_lcd1602(rightmove, cursornotdisplay);
	int_interrupt(0,negative_jump);
	int_interrupt(1,low_ele);
   	print1602("FREQ:",0,1);
	print1602("PWM :",1,1);	
	Timer0Init();
	Timer1Init();

	while(1)
	{
		EA =0;
		trans_to_lcd(cycle,lcd_temp);
		print1602(lcd_temp,0,7);
		trans_to_lcd(pwm,lcd_temp);
		print1602(lcd_temp,1,7);
		EA =1;
		waitms(500);	
	}
}
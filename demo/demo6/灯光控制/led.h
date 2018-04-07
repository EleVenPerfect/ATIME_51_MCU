#ifndef _LED_H_
#define _LED_H_
#include   <intrins.h>
#include   <STDIO.H>

sbit led1io = P0^0;
sbit led2io = P0^1;
sbit led3io = P0^2;

enum led_status {on,off,turn};

void led1(enum led_status a)
{
		if(a == on)
		{
				led1io = 0;
				printf("LED1 is ON\n");
		}
		else
		if(a == off)
		{
				led1io = 1;
				printf("LED1 is OFF\n");
		}
		else
		if(a == turn)
		{
				if(led1io==1)
						led1io = 0;
				else
						led1io = 1;
				printf("LED1 is TURN\n");
		}
}

void led2(enum led_status a)
{
		if(a == on)
		{
				led2io = 0;
				printf("LED2 is ON\n");
		}
		else
		if(a == off)
		{
				led2io = 1;
				printf("LED2 is OFF\n");
		}
		else
		if(a == turn)
		{
				if(led2io==1)
						led2io = 0;
				else
						led2io = 1;
				printf("LED2 is TURN\n");
		}
}

void led3(enum led_status a)
{
		if(a == on)
		{
				led3io = 0;
				printf("LED3 is ON\n");
		}
		else
		if(a == off)
		{
				led3io = 1;
				printf("LED3 is OFF\n");
		}
		else
		if(a == turn)
		{
				if(led3io==1)
						led3io = 0;
				else
						led3io = 1;
				printf("LED3 is TURN\n");
		}
}



void led_init()
{
		led1(off);
		led2(off);
		led3(off);
		printf("LED Inint OK!\n");
}

#endif
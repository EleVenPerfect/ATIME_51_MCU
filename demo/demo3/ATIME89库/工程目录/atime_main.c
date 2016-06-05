#include "STC89C5xRC.H"		 //�����滻REG52.H������ʹ�����ͷ�ļ� 
#include "atime_timer.h"	 //�ж����׺����⣬�����Ҫ�����ж�����Ӻ�������Ҫ����
#include "atime_lcd1602.h"	 //��Ҫ���������ļ���������	


void Timer0Init(void)		//5����@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0x00;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void Timer1Init(void)		//5����@11.0592MHz
{
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0x00;		//���ö�ʱ��ֵ
	TH1 = 0x00;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
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
#include "STC89C5xRC.H"		 //�����滻REG52.H������ʹ�����ͷ�ļ� 
#include "atime_timer.h"	 //�ж����׺����⣬�����Ҫ�����ж�����Ӻ�������Ҫ����
#include "atime_lcd1602.h"	 //��Ҫ���������ļ���������	


void Timer0Init(void)		//5����@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
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
	
		EA =0;
		trans_to_lcd(cycle,lcd_temp);
		print1602(lcd_temp,0,7);
		trans_to_lcd(pwm,lcd_temp);
		print1602(lcd_temp,1,7);
		EA =1;
		waitms(500);	
	}
}
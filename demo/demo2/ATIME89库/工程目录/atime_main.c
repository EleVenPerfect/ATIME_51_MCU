#include "STC89C5xRC.H" 
#include "atime_lcd1602.h"
#include "atime_18b20.h"
#include "atime_ds1302.h"
#include "atime_serial.h"

unsigned char temp_set=30;		//���ó�ʼ�¶�
float temperature;				//�����洢�¶�����
unsigned char temp;				//�洢char���¶�����
unsigned char display_temp[8];	//��ʾ����
sbit led_1 = P0^0;				//ָʾ��������
sbit led_2 = P0^1; 				//ָʾ��������
sbit key_1 = P3^2;				//����������
sbit key_2 = P3^3;				//����������
sbit BEEP  = P1^3; 				//������������

void warning(void)
{
	unsigned char i,j;
		
	for(i=0;i<230;i++)
	{
		BEEP =~BEEP;
		for(j=0;j<250;j++);
	}
		
}

void main()
{
	bit  ds18b20_exit;	 			//�洢ds18b20�Ƿ����
	int time_temp;					//�洢ʱ������
	unsigned char temp;				//�洢char���¶�

	led_1 = 1;
	led_2 = 1;
	BEEP = 1;
	warning();
	serial_int(enable, baud9600, disable);
	int_lcd1602( rightmove, cursornotdisplay);

	setds1302(second,0);
	setds1302(minute,42);
	setds1302(hour,19);
	setds1302(year,14);
	setds1302(month,2);
	setds1302(day,7);
	setds1302(weekday,5);
	ele_mode(1);
	EA = 1;

	while(1)
	{
		/*��ʾ�¶���ֵ*/
		display_temp[0] = temp_set/10%10+0x30;
		display_temp[1] = temp_set%10+0x30;
		display_temp[2] = '\0';
		print1602( display_temp, 0,14);
		printchar1602(' ', 1, 15);

		/*��ʼ�����¶�*/
		ds18b20_exit =int_18b20();
		if( ds18b20_exit ==0 )
		{
			temperature = read_temper(); 
			if(temperature<=80.0)
			{
				translate( temperature, display_temp);
				print1602( display_temp, 0, 0);
			}
		}
		else
		{
			print1602( "Not Found", 0, 1);
			led_1 = 0;
			led_2 = 0;
			warning();
			waitms(500);
			clear1602_10(0);
		}
		
		/*�����¶���ֵ*/
		if(key_1==0)
			temp_set++;
		if(key_2==0)
			temp_set--;
		if(temp_set<10)
			temp_set = 10;
		if(temp_set>70)
			temp_set = 70;

		/*��ʼ�ж��¶Ȳ�ָʾ���½���*/
		temp = (unsigned char)temperature; 
		if(temp>temp_set)
		{
			
			if(temp-temp_set>1)
			{
				 led_1 = 1;
				 led_2 = 0;
				 warning();
			}
			else
			{
				 led_1 = 1;
				 led_2 = 1;
			}
		}
		else
		{
		   	if(temp_set-temp>1)
			{
				 led_1 = 0;
				 led_2 = 1;
				 warning();
			}
			else
			{
				 led_1 = 1;
				 led_2 = 1;
			}
		}

		/*��ʼ��ʾʱ��*/
		time_temp =read1302(hour);
		if(time_temp<=23)
		{
			translate_print(time_temp,display_temp);
			print1602(display_temp,1,2);
		}
				    
		time_temp =read1302(minute);
		if(time_temp<=60)
		{
			translate_print(time_temp,display_temp);
			print1602(display_temp,1,5);
		}
			
		time_temp =read1302(second);
		time_temp =read1302(second);		//��ȡ����Ϊ�˱�֤�ܹ���ȡ���ݳɹ�
		if(time_temp<=60)
		{
			translate_print(time_temp,display_temp);
			print1602(display_temp,1,8);


			/*����ð����˸*/
			if(time_temp%2!=1)
			{
		    	print1602(" ",1,4);	
				print1602(" ",1,7);
			}
			else
			{
				print1602(":",1,4);
				print1602(":",1,7);	
			}
		}


	}
}



void interrupt_serial1(void) interrupt 4
{
	unsigned char k;
	k =receive_char();
	printchar1602(k , 1, 15);
	if(k=='A')
	{
		temp_set++;
		if(temp_set>70)
			temp_set = 70;
	}
	if(k=='B')
	{
		temp_set--;	
		if(temp_set<10)
			temp_set = 10;		
	}
	if(k=='T')
	{
		temp = (unsigned char)temperature; 
		send_char(temp%100/10+0x30);	
		send_char(temp%10+0x30);
		temp = (unsigned char)(temperature*100); 
		send_char('.');
		send_char(temp%100/10+0x30);	
		send_char(temp%10+0x30);
		send_char(' ');	
	}

	send_char(k);
	send_char(' ');
	send_char('O');
	send_char('K');
	send_char('\n');
}	

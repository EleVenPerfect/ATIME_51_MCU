#include <reg52.h>
#include "atime_ds1302.h"
#include "ascii_char.h"
#include "atime_tft_1_8.h"
#include "atime_18b20.h"
#include "atime_iic.h"
#include "atime_infrared.h"
#include "atime_buzzer.h"


unsigned char temp[3];
unsigned char  inf[4];
unsigned char  pcf[5];
unsigned char wendu[5];


unsigned char code card_sw[9][8] ={{"set ok \0"},
								   {"cl hou \0"},
								   {"clo min\0"},
								   {"year   \0"},
								   {"month  \0"},
								   {"week   \0"},
								   {"date   \0"},
								   {"hour   \0"},
								   {"minute \0"}};
enum pitch_buzzer code ok[27] ={  h3,m0,h3,m0,h3
								 ,m0,m0,m0,h3,m0
								 ,h3,m0,h3,m0,m0
								 ,m0,h3,m0,h5,m0
								 ,h1,m0,h2,m0,h3
								 ,m0,mstop };	


void transpot(unsigned char a, unsigned char b[])
{									  //BCD转两位ASCII数组
	b[0] =a/10+0x30;
	b[1] =(a%10)+0x30;
}

void transporttemp(float i, unsigned char r[])
{									   //float转四位ASCII数组
   	unsigned int j;
	i =i*100;
	j =(int)i;
	r[0] =(j%10000)/1000+48;
	r[1] =(j%1000)/100+48;
	r[2] ='.';
	r[3] =(j%100)/10+48;
}


void transv(unsigned char i, unsigned char u[])
{									   //int转四位ASCII数组
	u[0] =i/100+0x30;
	u[1] =(i%100)/10+0x30;
	u[3] =(i%10)+0x30;
	u[2] ='.';
}


unsigned char change_value(unsigned char a)
{										//红外接收转码
	switch(a)
	{
		case 0x07 :return 'E';
		case 0x15 :return 'C';
		case 0x09 :return 'D';
		case 0x16 :return 0;
		case 0x0c :return 1;
		case 0x18 :return 2;
		case 0x5e :return 3;
		case 0x08 :return 4;
		case 0x1c :return 5;
		case 0x5a :return 6;
		case 0x42 :return 7;
		case 0x52 :return 8;
		case 0x4a :return 9;
		default   :return 'A';
	}									 
}


void main()
{
	float i;
	bit j,ek=0;
	unsigned char vot[5];
	unsigned char t,hh =8,mm =0, kk=0, ii, jj, card;
									 //定义变量
	LCD_init();
	LCD_clear(7);
	temp[2] ='\0';
	wendu[4] ='\0';
	int_infrared(0);
	setds1302(second,0);
	setds1302(minute,0);
	setds1302(hour,23);
	setds1302(year,14);
	setds1302(month,2);
	setds1302(day,17);
	setds1302(weekday,1);					// 时钟显示器红外初始化
	ele_mode(1);
	LCD_ShowString("CLOCK",45,5,colors[1],colors[7]);
	LCD_ShowString("  20  -  -  ",5,25,colors[2],colors[7]);
	LCD_ShowString("TIME:  :  :",5,45,colors[2],colors[7]);
	LCD_ShowString("WEEK:  U=    V",5,65,colors[2],colors[7]);
	LCD_ShowString("CLOCK:  :",5,85,colors[2],colors[7]);
	LCD_ShowString("TEMPER:",5,105,colors[2],colors[7]);
	LCD_ShowString("SET:",5,125,colors[6],colors[7]);
	LCD_ShowString("Design By ATIME",5,145,colors[0],colors[7]);
											// 显示初值
	while(1)
	{		
		t =read1302(year);
		transpot(t,temp);
		LCD_ShowString(temp,37,25,colors[2],colors[7]);

		t =read1302(month);
		transpot(t,temp);
		LCD_ShowString(temp,61,25,colors[2],colors[7]);

		t =read1302(day);
		transpot(t,temp);
		LCD_ShowString(temp,85,25,colors[2],colors[7]);

		t =read1302(weekday);
		transpot(t,temp);
		LCD_ShowChar(45,65,colors[2],colors[7],temp[1]);

		t =read1302(hour);
		transpot(t,temp);						//显示时间
		LCD_ShowString(temp,45,45,colors[2],colors[7]);
		if(t ==hh)
			ek =1;
		else 
			ek =0;								//闹钟判断

		t =read1302(minute);
		transpot(t,temp);
		LCD_ShowString(temp,69,45,colors[2],colors[7]);
		if(t ==mm)
		{	
			if(ek==1)
			{
				  buzzer(ok);
			}								   //闹钟判断
		}

		t =read1302(second);
		transpot(t,temp);
		LCD_ShowString(temp,93,45,colors[2],colors[7]);

	
		transpot(hh,temp);
		LCD_ShowString(temp,52,85,colors[2],colors[7]);
		transpot(mm,temp);
		LCD_ShowString(temp,76,85,colors[2],colors[7]);
		
			


		j =int_18b20();
		if(j==0)
		{
			i =read_temper();
			transporttemp(i,wendu);
			LCD_ShowString(wendu,60,105,colors[2],colors[7]);
			LCD_ShowString("'c    ",93,105,colors[2],colors[7]);	
		}
		else	   
			LCD_ShowString("Not Link",60,105,colors[2],colors[7]); 	
													 //温度检测，如果没有检测到18B20就显示NOT LINK
		


		iic_read(0x90,0x44,4,vot);
		transv((vot[1]-150)/2,wendu);
		LCD_ShowString(wendu,75,65,colors[2],colors[7]);  
													//电压表检测数据并显示
		
		
		int_infrared(0);
		read_infrared(inf);
		card =change_value(inf[2]);
		if(card =='E')
		{
			kk ='E';
			while(kk >9||kk <0)
			{
				int_infrared(0);					//红外检测设置信号
				read_infrared(inf);
				kk =change_value(inf[2]);
			}
		}
		LCD_ShowString(card_sw[kk],35,125,colors[6],colors[7]);
		if(kk !=0)
		{
			switch(kk)								//不同设置项进入不同设置模块
			{
				case 1:	{
							while(ii >9||ii <0)
							{
								int_infrared(0);
								read_infrared(inf);
								ii =change_value(inf[2]);
							}
							while(jj >9||jj <0)
							{
								int_infrared(0);
								read_infrared(inf);
								jj =change_value(inf[2]);
							}
							hh =10*ii+jj;
							ii ='E';
							jj ='E';
							kk =0;
							 break;					 
						}
				case 2:	{
							while(ii >9||ii <0)
							{
								int_infrared(0);
								read_infrared(inf);
								ii =change_value(inf[2]);
							}
							while(jj >9||jj <0)
							{
								int_infrared(0);
								read_infrared(inf);
								jj =change_value(inf[2]);
							}
							mm =10*ii+jj;
							ii ='E';
							jj ='E';
							kk =0;
							 break;			
						}
				case 3:{
							while(ii >9||ii <0)
							{
								int_infrared(0);
								read_infrared(inf);
								ii =change_value(inf[2]);
							}
							while(jj >9||jj <0)
							{
								int_infrared(0);
								read_infrared(inf);
								jj =change_value(inf[2]);
							}
							setds1302(year,(10*ii+jj));
							ii ='E';
							jj ='E';
							kk =0;
							 break;			
						}
				case 4:{
							while(ii >9||ii <0)
							{
								int_infrared(0);
								read_infrared(inf);
								ii =change_value(inf[2]);
							}
							while(jj >9||jj <0)
							{
								int_infrared(0);
								read_infrared(inf);
								jj =change_value(inf[2]);
							}
							setds1302(month,(10*ii+jj));
							ii ='E';
							jj ='E';
							kk =0;
							 break;			
						}
				case 5:{
							while(ii >9||ii <0)
							{
								int_infrared(0);
								read_infrared(inf);
								ii =change_value(inf[2]);
							}
							while(jj >9||jj <0)
							{
								int_infrared(0);
								read_infrared(inf);
								jj =change_value(inf[2]);
							}
							setds1302(weekday,(10*ii+jj));
							ii ='E';
							jj ='E';
							kk =0;
							 break;			
						}
				case 6:{
							while(ii >9||ii <0)
							{
								int_infrared(0);
								read_infrared(inf);
								ii =change_value(inf[2]);
							}
							while(jj >9||jj <0)
							{
								int_infrared(0);
								read_infrared(inf);
								jj =change_value(inf[2]);
							}
							setds1302(day,(10*ii+jj));
							ii ='E';
							jj ='E';
							kk =0;
							 break;			
						}
				case 7:{
							while(ii >9||ii <0)
							{
								int_infrared(0);
								read_infrared(inf);
								ii =change_value(inf[2]);
							}
							while(jj >9||jj <0)
							{
								int_infrared(0);
								read_infrared(inf);
								jj =change_value(inf[2]);
							}
							setds1302(hour,(10*ii+jj));
							ii ='E';
							jj ='E';
							kk =0;
							 break;			
						}
				case 8:{
							while(ii >9||ii <0)
							{
								int_infrared(0);
								read_infrared(inf);
								ii =change_value(inf[2]);
							}
							while(jj >9||jj <0)
							{
								int_infrared(0);
								read_infrared(inf);
								jj =change_value(inf[2]);
							}
							setds1302(minute,(10*ii+jj));
							ii ='E';
							jj ='E';
							kk =0;
							 break;			
						}
				default :  break;
			}
		}					
	}	  
}




void interrupt_int0(void) interrupt 0				   //红外检测外部中断0服务程序
{
	start_code();
}
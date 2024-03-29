/***********************************************************************************************************/
//HC-SR04 超声波测距模块 DEMO 程序
//晶振：11。0592
//接线：模块TRIG接 P1.2  ECH0 接P1.1
//串口波特率9600
/***********************************************************************************************************/	  
	#include   <AT89X51.H>
	#include   <intrins.h>
    #include   <STDIO.H>
	#include  "atime_18b20.h"
	#include  "atime_lcd1602.h"

    #define uchar unsigned  char
    #define uint  unsigned   int  
	#define  RX  P1_1
    #define  TX  P1_2
  

	unsigned int  time=0;
	unsigned int  timer=0;
	float         S=0;
    bit           flag =0;

    unsigned char a[8];
	unsigned char b[4];	

/********************************************************/
    void Conut(void)
	{
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	 S=(time*1.87)/100;     //算出来是CM
	 if(flag==1)		    //超出测量
	 {
	  flag=0;
	  printf("-----\n"); 
	 }
	  printf("T=%s 'c\n",a);
	  waitms(1500);
	  printf("S=%f cm\n",S); 
	}
/********************************************************/ 
void delayms(unsigned int ms)
{
	unsigned char i=100,j;
	for(;ms;ms--)
	{
		while(--i)
		{
			j=10;
			while(--j);
		}
	}
}
/********************************************************/
     void zd0() interrupt 1 		 //T0中断用来计数器溢出,超过测距范围
  {
    flag=1;							 //中断溢出标志
  }
/********************************************************/
   void  StartModule() 		         //T1中断用来扫描数码管和计800MS启动模块
  {
	  TX=1;			                 //800MS  启动一次模块
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  TX=0;
  }
/********************************************************/
void main(void)
{  

	float i;
	bit j;
	unsigned int ss;
	int_lcd1602(rightmove, cursornotdisplay);
	
	TMOD=0x21;		   //设T0为方式1，GATE=1；
	SCON=0x50;
	TH1=0xFD;
	TL1=0xFD;
	TH0=0;
	TL0=0; 
	TR0=1;  
	ET0=1;             //允许T0中断
	TR1=1;			   //开启定时器
	TI=1;

	EA=1;			   //开启总中断


	while(1)
	{
	 StartModule();
	 while(!RX);		//当RX为零时等待
	 TR0=1;			    //开启计数
	 while(RX);			//当RX为1计数并等待
	 TR0=0;				//关闭计数
     Conut();			//计算
	 delayms(100);		//100MS
	 
	
	j =int_18b20();
	if(j == 0)
	{
		i =read_temper();
		translate(i,a);
		print1602(a,1,1);
		print1602("'C",1,8);
	}
	else
	{
		print1602("Please Cheak",1,2);
		waitms(1000);
		set1602(clear1602);
	}

	ss =(unsigned int)S;

	b[0] = ss%1000/100+0x30;
	b[1] = ss%100/10+0x30;
	b[2] = ss%10+0x30;
	b[3] = '\0';
	print1602(b,0,4); 
	print1602("cm",0,7);
	}

}              
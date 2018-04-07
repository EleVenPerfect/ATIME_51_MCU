#ifndef _CEJV_H_
#define _CEJV_H_
#include   <intrins.h>
#include   <STDIO.H>
/***********************************************************************************************************/
//HC-SR04 超声波测距模块程序
//晶振：11。0592
//接线：模块TRIG接 P2.1  ECH0 接P2.0
//串口波特率9600
/***********************************************************************************************************/	  
sbit  CSB_RX = P2^1;			//定义接受引脚
sbit  CSB_TX = P2^0;			//定义发送引脚

float         S=0;				//存储距离
bit           flag =0;		//存储
unsigned int  time=0;			//超出测量距离标志

/********************************************************/
void Conut(void)
{
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	 S=(time*1.87)/100;     //算出来是CM
	 if(flag==1)		    		//超出测量
	 {
			flag=0;
			printf("-----\n"); 
	 }
	 printf("S=%f\n",S); 
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
	  CSB_TX=1;			                 //800MS  启动一次模块
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
	  CSB_TX=0;
 }

 void cj_init()
 {
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
		printf("CJ Inint OK!\n");
}


void cj_run()
{
		StartModule();
		while(!CSB_RX);		//当RX为零时等待
		TR0=1;			    //开启计数
		while(CSB_RX);			//当RX为1计数并等待
		TR0=0;				//关闭计数
    Conut();			//计算
}
#endif
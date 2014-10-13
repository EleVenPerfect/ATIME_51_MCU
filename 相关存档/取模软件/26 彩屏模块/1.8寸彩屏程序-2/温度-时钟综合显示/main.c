/**********************************************************************
*                                                                     *
*           TFT液晶红温度和时钟综合显示程序                           *
*              （  普中科技  ）                                       *
*                                                                     *
* 实验目的：1.掌握TFT彩屏驱动程序的编写、							  *
*           2.学会运用取字模软件应用(取字符和汉字数组)				  *
*			3.学会怎样处理字模数组数据                                *
*                                                                     *                                                                     *
*实验现象： 彩屏中显示温度和时钟                                      *
*                                                                     *
***********************************************************************/

#include <reg52.h>
#include <intrins.h>
#include "lcd.h"


unsigned char   Tempera_Val[3] ,temp;  //温度
unsigned char   RTC_Val[15];          //时钟数组
unsigned int xdata TIM,TIM1;    //用于间隔读取温度和时钟
extern unsigned int  idata Temperature;	 //温度
extern unsigned  char xdata D[8];    //读取时钟放到D数组中

extern void Read_RTC(void);
extern void GetTemp (void);
extern void Set_RTC(void); //set RTC 


/**********************************************************
         配置定时器参数
 **********************************************************/
void Timer_Ini()
{
    TMOD|= 0x11;
    TH1 = 0xD8;    //10
    TL1 = 0xF0;	
	IE = 0x8A;	
    TR1  = 1;
}

/**********************************************************

  主函数

**********************************************************/
void main(void)
{  
    P2 = 0xff;
    P0 = 0xff;

   	Timer_Ini();	 //初始化
    LCD_init();      //初始化
    LCD_clear(5);    //清屏
  
    ChineseChar(14,10,2,colors[2],colors[7],1);	  //普
    ChineseChar(38,10,2,colors[2],colors[7],2);	  //中
    ChineseChar(62,10,2,colors[2],colors[7],3);	  //科
    ChineseChar(86,10,2,colors[2],colors[7],4);	  //技
  
    ChineseChar(24,50,1,colors[2],colors[7],10);  //温
	ChineseChar(40,50,1,colors[2],colors[7],11);  //度
    ChineseChar(80,50,1,colors[2],colors[7],12);  //℃

    ChineseChar(30,80,1,colors[2],colors[7],13);  //实
	ChineseChar(46,80,1,colors[2],colors[7],14);  //时
	ChineseChar(62,80,1,colors[2],colors[7],14);  //时
    ChineseChar(76,80,1,colors[2],colors[7],15);  //钟
   
	Set_RTC();

   while(1)	
  {	  
      if( TIM1 >= 10)  //每隔 10ms 读取ds1302
	  {
	    TIM1  =  0;
		Read_RTC();  //读取DS1302
	  }
        GetTemp();
		//*****温度***********************
        Tempera_Val[0] = Temperature%100/10 + 0x30;    //Temperature;
        Tempera_Val[1] = Temperature%10 + 0x30;

		//******月***********************
		temp =   ((D[4]&0x70)>>4)*10 + (D[4]&0x0f);	  
		RTC_Val[0] = temp/10 + 0x30;     //将10位转成ASCII码
		RTC_Val[1] = temp%10 + 0x30;     //将个位转成ASCII码
		
		RTC_Val[2] = '-'  ;	     //短横线
		 //*****日***********************
		temp =   ((D[3]&0x70)>>4)*10 + (D[3]&0x0f);	  
		RTC_Val[3] =  temp/10 + 0x30;
		RTC_Val[4] =  temp%10 + 0x30;
		RTC_Val[5] = ' '  ;
		//******时***********************
		temp =   ((D[2]&0x70)>>4)*10 + (D[2]&0x0f);	   
		RTC_Val[6] = temp/10 + 0x30;
		RTC_Val[7] = temp%10 + 0x30;

		RTC_Val[8] = ':'	;	  //冒号
		 //******分***********************
		temp =   ((D[1]&0x70)>>4)*10 + (D[1]&0x0f);	  
		RTC_Val[9] =  temp/10 + 0x30;
		RTC_Val[10] = temp%10 + 0x30;

		RTC_Val[11] = ':';
		 //******秒***********************
	    temp =   ((D[0]&0x70)>>4)*10 + (D[0]&0x0f);		
		RTC_Val[12] = temp/10 + 0x30;
		RTC_Val[13] = temp%10 + 0x30;

	  	   
	    LCD_ShowString(60,50,colors[7],colors[2], Tempera_Val); //将字符送到彩屏中显示
		LCD_ShowString(10,100,colors[7],colors[2], RTC_Val);     //将字符送到彩屏中显示

  }  
}


/*************************************
 [ t1 (10ms)中断] 中断
*************************************/
void T1zd(void) interrupt 3 
{
   TH1 = 0xD8;    //10
   TL1 = 0xF0;
   TIM++;
   TIM1++;
}




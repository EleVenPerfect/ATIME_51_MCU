/************************************
库功能：并口1.8寸液晶函数库
库要求：主函数中已定义：
		#include <reg52.h>
		#include "char.h"
		要求char.h在本库函数前面，提供ASCII码服务
应用函数：
	unsigned int trans_rgb(unsigned char r, unsigned char g, unsigned char b)    本函数尚未测试
	wait_tft18_ms(unsigned int n)
	LCD_SetRamAddr(unsigned int xStart, unsigned int xEnd, unsigned int yStart, unsigned int yEnd) 
	LCD_init(void)
	LCD_clear(unsigned char n)
	pic_play(unsigned char a[],unsigned int Start_X, unsigned int End_X,unsigned int Start_Y,unsigned int End_Y)
	文件后面还有部分函数被注释需要使用时解除注释即可使用
修改历史：2014-02-25
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2013-02-11
作者： ATIME	版权所有
实例程序：
	#include <reg52.h>
	#include "char.h"
	#include "atime_tft_1_8.h"
	
	void main()
	{
		P1 =0XF0;
		LCD_init();
		wait_tft18_ms(1000);
		P1 =~P1;
	    while(1)
		{
			LCD_clear(2);
			wait_tft18_ms(500);
			P1 =~P1;
			LCD_ShowString("A T I M E",12,40,colors[0],colors[7]);
		  	wait_tft18_ms(500);
		}	
	}

	#include <reg52.h>
	#include "a.c"
	#include "atime_tft_1_8.h"
	
	void main()
	{
		P1 =0XF0;
		LCD_init();
		wait_tft18_ms(1000);
		P1 =~P1;
	    while(1)
		{
			LCD_clear(7);
			wait_tft18_ms(500);
			P1 =~P1;
		 	pic_play(a,7,61,8,74);
		    pic_play(a,68,122,8,74);
		    pic_play(a,7,61,82,148);
		    pic_play(a,68,122,82,148);
		  	wait_tft18_ms(500);
		}	
	}

常见错误解释：
	123.C(22): error C249: 'DATA': SEGMENT TOO LARGE  ：文件太大，内存不足；解决办法：将数组定义为code型数组，如果仍然报错，尝试简化你的程序，去除不用的部分
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
注：
	显示图片要根据图片大小写函数的起始位置，否则显示图片会有扭曲错位
	保存文件名任意，数组名称任意，但数组要定义为code数组。
	不用的函数最好屏蔽用：/*  */
/***************************************/

#ifndef _ATIME_TFT_1_8_H_ 
#define _ATIME_TFT_1_8_H_

/************************************
库全局变量组
***************************************/

#define  DATA   P0	
sbit LCD_WR   = P2^4;
sbit LCD_RS   = P2^5;
sbit LCD_CS   = P2^6;
sbit LCD_RST  = P2^7;

unsigned int code colors[8]={ 
 0xf800,0x07e0,0x001f,0xffe0,0x0000,0x07ff,0xf81f,0xffff };
//红      绿     蓝     黄     黑    浅蓝	红紫    白

/************************************
函数功能：延时n毫秒
传递参数：空
返回值：空	
***************************************/
void wait_tft18_ms(unsigned int n)
{
    int i;
	while(n--)
	{
		for(i=0; i<75; i++)
		{
			;
		}	
	}
}


/************************************
函数功能：向屏幕写一字节数据
传递参数：value： 待写入数据
返回值：空
***************************************/
void WriteDAT(unsigned char value)    // color data
{
	LCD_CS  =  0;
	LCD_RS 	=  1;
	LCD_WR  =  0;
	DATA 	=  value;
    LCD_WR  =  0;
	LCD_WR  =  1;
   	LCD_CS  =  1;
}

/************************************
函数功能：向液晶写入一字节指令
传递参数：value：待写入指令
返回值：空	
***************************************/
void WriteCOM(unsigned char value)    // color data
{
	LCD_CS  =  0;
	LCD_RS 	=  0;
	LCD_WR  =  0;
	DATA 	=  value;
	LCD_WR  =  0;
	LCD_WR  =  1;
   	LCD_CS  =  1;
}

/************************************
函数功能：设置显示起止位置
传递参数：
		  xStart:横向显示起始点
		  xEnd ：横向显示结束点
		  yStart:纵向显示起始点
		  yEnd : 纵向显示结束点
返回值：空	
***************************************/
void LCD_SetRamAddr(unsigned int xStart, unsigned int xEnd, unsigned int yStart, unsigned int yEnd) 
{
	WriteCOM(0x2a);		   //行
	WriteDAT(xStart>>8);   //XS15-XS8
	WriteDAT(xStart);	   //XS7-XS0    (X start address)
	WriteDAT(xEnd>>8);	   //XE15-XE8
	WriteDAT(xEnd);		   //XE7-XE0    (X end address)

	WriteCOM(0x2b);		   //列	row address set (RASET)
	WriteDAT(yStart>>8);   //YS15-YS8
	WriteDAT(yStart);	   //YS7-YS0    (Y start address)
	WriteDAT(yEnd>>8);	   //YE15-YE8
	WriteDAT(yEnd);		   //YE7-YE0    (Y end address)

    WriteCOM(0x2c);		   //display on	显示打开命令  
}


/************************************
函数功能：液晶初始化
传递参数：空
返回值：空	
***************************************/
void  LCD_clear(unsigned char n);	 //声明一个准备调用的函数
void LCD_init(void)					 //液晶初始化程序开始
{	                    //请看数据手册的命令部分 了解其个命令的功能
	LCD_RST=1;
	wait_tft18_ms(100);
	LCD_RST=0;
	wait_tft18_ms(100);
	LCD_RST=1;
	wait_tft18_ms(100);
	
	WriteCOM(0x01);	    //software reset软件复位
	wait_tft18_ms(100);
	WriteCOM(0x11);	    //sleep out/power on(SLPOUT) 退出睡眠
	wait_tft18_ms(50);
	WriteCOM(0x20);		//display inversion off 关闭取反
	wait_tft18_ms(50);
	WriteCOM(0x38);	    //ID mode off (IDMOFF)
	wait_tft18_ms(50);
	WriteCOM(0x13);	    //Normal display mode on (Partial mode off)
	
	WriteCOM(0x3a);	    //color mode Interface pixel format  (COLMOD)
	WriteDAT(0x05);		//16-bit/pixel , 1-times data transfer
	
	WriteCOM(0xc0);		//power control 1      (PWCTR1)
	WriteDAT(0x03);		//default value  LCM=0 set the GVDD voltage=4.65
	
//	WriteCOM(0xc5);	   
//	WriteDAT(0xc8);	   //VCOMH voltage set 4.300V
	
	WriteCOM(0xc6);
	WriteDAT(0x1f);	   //VCOMAC voltage set 5.550V ;
	wait_tft18_ms(10);
	
	WriteCOM(0xfe);
	WriteDAT(0x00);
	WriteDAT(0x04);
	
	WriteCOM(0x26);	   //gamma sel
	WriteDAT(0x04);
	
	
	WriteCOM(0x2a);	   //column address set (CASET)
	WriteDAT(0x00);	   //XS15-XS8
	WriteDAT(0x00);	   //XS7-XS0    (X start address)
	WriteDAT(0x00);	   //XE15-XE8
	WriteDAT(0x7f);	   //XE7-XE0    (X end address)
	
	WriteCOM(0x2b);	   //row address set (RASET)
	WriteDAT(0x00);	   //YS15-YS8
	WriteDAT(0x00);	   //YS7-YS0    (Y start address)
	WriteDAT(0x00);	   //YE15-YE8
	WriteDAT(0x9f);	   //YE7-YE0    (Y end address)
	
	WriteCOM(0x36);	   //memory data access control  (MADCTR)
	WriteDAT(0xc0);
	
	WriteCOM(0x29);	  // display on

}


/************************************
函数功能：清空液晶屏
传递参数：n:清屏后颜色
返回值：空	
***************************************/
void  LCD_clear(unsigned char n)
{
   unsigned int num;
   
   LCD_SetRamAddr(2,129,1,160);  //设置显示的坐标

   for(num=20480;num>0;num--)          //160*128=20480
   {
  	 WriteDAT(colors[n]>>8);   //高8位
	 WriteDAT(colors[n]);	   //低8位
   }
}


/************************************
函数功能：颜色转换
传递参数：
	R:红色
	G:绿色
	B:蓝色
	取值均为0~255
返回值：16位真彩色颜色整形值	
***************************************/
unsigned int trans_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return((unsigned int)(r&0xf8)<<8|(unsigned int)(g&0xfc)<<3|(unsigned int)(b&0xf8)>>3);
}


/************************************
函数功能：向某位置显示某数组的数据
传递参数：
		  a[]:	   带显示数组
		  Start_X: 横向位置起始点
		  End__X:  横向位置结束点
		  Start_Y: 纵向位置起始点
		  End_Y:   纵向未知结束点
返回值：空
***************************************/
void  pic_play(unsigned char a[],unsigned int Start_X, unsigned int End_X,unsigned int Start_Y,unsigned int End_Y)
{
   unsigned int m;
   LCD_CS = 0;
   LCD_SetRamAddr(Start_X,End_X-1,Start_Y,End_Y-1) ;   //设置地址
   LCD_RS = 1; 

   for(m=0; m<((End_X-Start_X)*(End_Y-Start_Y)); m++)	
   {		
      WriteDAT(a[m*2+1]);	//高位在前
	  WriteDAT(a[m*2]);     //低位在后
   }
   LCD_CS = 1;
}


/************************************
函数功能：向某位置显示一个字符
传递参数：
		  x:  横向位置
		  y:  纵向位置
		  For_color: 字符颜色
		  Bk_color:	 背景颜色
		  ch:	 待显示字母
返回值：空
***************************************/
/*
void LCD_ShowChar(unsigned char x,unsigned char y,unsigned int For_color,unsigned int Bk_color, char ch)
{       
   unsigned char temp;
   unsigned char pos,t;
   unsigned char CHAR_W,CHAR_H;
   
   CHAR_W = 8;         //8*16
   CHAR_H = 16;

   LCD_SetRamAddr(x, x+CHAR_W-1, y, y+CHAR_H-1);	  //设置显示的坐标
   ch = ch-32;                       //按照ASCII编码顺序的到相应字母的编码

   for(pos=0; pos<CHAR_H; pos++)  
   {
      temp= Font8x16[ch][pos];
      
      for(t=0; t<CHAR_W; t++)
      {                 
	    if(temp&0x80)
	     {WriteDAT(For_color>>8); WriteDAT(For_color); } //textcolor  //字体颜色
    
	 else 
		 {WriteDAT(Bk_color>>8) ; WriteDAT(Bk_color) ;  	}
	
		
        temp<<=1; 
	
      }
	  
   }
}  
										 */

/************************************
函数功能：向某位置显示一个字符串
传递参数：
		  x:  横向位置
		  y:  纵向位置
		  For_color: 字符颜色
		  Bk_color:	 背景颜色
		  *p:	 待显示字母数组首地址
返回值：空
***************************************/
/*
void LCD_ShowString(unsigned char *p, unsigned char x, unsigned char y, unsigned int For_color, unsigned int Bk_color)
{         
  	 while(*p!='\0')
     {       
     	LCD_ShowChar(x,y,For_color,Bk_color,*p);
    	 x +=8 ;	  //字体的宽度
    	 p++ ;
    }
}							   */



/************************************
函数功能：向某位置显示一个汉字
传递参数：
		  x:  横向位置
		  y:  纵向位置
		  For_color: 文字颜色
		  Bk_color:	 背景颜色
		  c：待显示汉字
		  size：
返回值：空
示例：
			   ChineseChar(1,20,40,0,colors[0],colors[7]);	//带
			   ChineseChar(2,32,40,0,colors[0],colors[7]);	//您
			   ChineseChar(3,44,40,0,colors[0],colors[7]);	//进
			   ChineseChar(4,56,40,0,colors[0],colors[7]);	//入
			   ChineseChar(5,68,40,0,colors[0],colors[7]);	//单
			   ChineseChar(6,80,40,0,colors[0],colors[7]);	//片
			   ChineseChar(7,92,40,0,colors[0],colors[7]);	//机
			   ChineseChar(8,104,40,0,colors[0],colors[7]);	//世
			   ChineseChar(9,116,40,0,colors[0],colors[7]);	//界 

***************************************/
/*
void ChineseChar(char c, unsigned int x, unsigned int y, int size, unsigned int For_color,unsigned int Bk_color)
{
   int e=0,i,j;
   int ed;
   
   unsigned int  ncols;
   unsigned int  nrows;
   unsigned int  nbytes;

   unsigned char *pfont;
   unsigned char *pchar;
   unsigned char *fonttable[]={(unsigned char *)hz12,(unsigned char *)hz16,(unsigned char *)hz24};		//将字体的首地址放在fortable数组中
   
   pfont=(unsigned char *)fonttable[size];

   if(size==0)
   {
     ncols =12-1;
     nrows =12-1;
     nbytes =24;	 //(12*12)/8
   }
   else
   if(size==1)
   {
     ncols =16-1;
     nrows =16-1;
     nbytes =32;  //(16*16)/8
   }
   else
   if(size==2)
   {
     ncols =24-1;
     nrows =24-1;
     nbytes =72;   //(24*24)/8
   }
   
   pchar=pfont + (nbytes*(c-1));

   LCD_SetRamAddr(x, x+nrows, y,y+ncols);  //设置显示的坐标
   
   for(i=0;i<nbytes;i++)
   {
     ed=*pchar++;
	 if(size==0)
	 {
       if(i%2==0)
       e=8;
       else
       e=4;
	 }
	 else
	 e=8;
     
     for(j=0;j<e;j++)
     if((ed>>j)&0x01)
     {
       WriteDAT(For_color>>8);  //textcolor	文字颜色
	   WriteDAT(For_color);
	 }
     else
     {
       WriteDAT(Bk_color>>8);  //backcolor 背景颜色
	   WriteDAT(Bk_color);
	 }
  }
}
*/


#endif
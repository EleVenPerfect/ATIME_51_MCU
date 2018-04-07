/************************************
库功能：并口1.8寸液晶函数库
库要求：主函数中已定义：
		#include "STC12C5A60S2.H"
		#include "ascii_char.h"
		要求char.h在本库函数前面，提供ASCII码服务
应用函数：
	unsigned int trans_rgb(unsigned char r, unsigned char g, unsigned char b)    本函数尚未测试
	lcd_init(void)
	lcd_clear(unsigned char n)
	lcd_pict(unsigned char a[],unsigned int Start_X, unsigned int End_X,unsigned int Start_Y,unsigned int End_Y)
    	lcd_point( unsigned char x, unsigned char y, unsigned int color)
	lcd_line( unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned int color)
	lcd_printchar( unsigned char ch, unsigned char x, unsigned char y, unsigned int color)
	lcd_printstring(unsigned char *p, unsigned char x, unsigned char y, unsigned int color)
	lcd_printchinese(unsigned char c[32], unsigned int x, unsigned int y, unsigned int color)
修改历史：2014-02-25
		   	 ‘修改人’   ‘修改内容’ 			 ‘修改时间’
			  ATIME		 修改函数			  2014-05-01
			  			 lcd_SetRamAddr(unsigned int xStart, unsigned int xEnd, unsigned int yStart, unsigned int yEnd) 
						 pic_play(unsigned char a[],unsigned int Start_X, unsigned int End_X,unsigned int Start_Y,unsigned int End_Y)
						 更改为统一的名称，并更改坐标点的参数顺序 ，并修改了例程
			  ATIME		 添加函数			  2014-05-01
			  			 void lcd_point( unsigned char x, unsigned char y, unsigned int color)
						 void write_line_right_down( unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned int color)
						 void write_line_right_up( unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned int color)
						 void lcd_line( unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned int color)
						 void lcd_printchar( unsigned char ch, unsigned char x, unsigned char y, unsigned int color)
						void lcd_printstring(unsigned char *p, unsigned char x, unsigned char y, unsigned int color)
						void lcd_printchinese(unsigned char c[32], unsigned int x, unsigned int y, unsigned int color)
						提高库函数的可用性
最后修改时间：2013-02-11
作者： ATIME	版权所有
实例程序：
例程一：
	#include <reg52.h>
	#include "a.c"
	#include "atime_tft_1_8.h"
	
	void main()
	{
		P1 =0XF0;
		lcd_init();
		wait_tft18_ms(1000);
		P1 =~P1;
	    while(1)
		{
			lcd_clear(7);
			wait_tft18_ms(500);
			P1 =~P1;
		 	lcd_pict(a,7,8,61,74);
		    lcd_pict(a,68,8,122,74);
		    lcd_pict(a,7,8261,,148);
		    lcd_pict(a,68,82,122,148);
		  	wait_tft18_ms(500);
		}	
	}
例程二：
	#include "STC12C5A60S2.H" 
	#include "ascii_char.h"
	#include "b.c"
	#include "atime_tft_1_8.h"
	
	void main()
	{
		
		lcd_init();
		lcd_clear( 7);
		lcd_line(50,10,50,50,0xf800);	
		lcd_line(90,50,50,50,0xf800);
	
		lcd_clear(7);
	 	lcd_pict(a,20,0,109,160);
		while(1);	
	}

例程三：
		#include "STC12C5A60S2.H" 
		#include "ascii_char.h"
		#include "b.c"
		#include "atime_tft_1_8.h"
		unsigned char code c[7][32]=      
		{
		{0x01,0x00,0x01,0x00,0x01,0x10,0x3F,0xF8,
			  0x02,0x00,0x02,0x04,0xFF,0xFE,0x04,0x00,
			  0x04,0x00,0x0F,0xF8,0x00,0x10,0x00,0x20,
			  0x00,0x40,0x06,0x80,0x01,0x80,0x00,0x40,},	//专
		{0x00,0x80,0x40,0x40,0x30,0x44,0x17,0xFE,
			  0x80,0x40,0x60,0x40,0x20,0x40,0x08,0x48,
			  0x17,0xFC,0x20,0x40,0xE0,0x40,0x20,0x40,
			  0x20,0x40,0x20,0x44,0x2F,0xFE,0x20,0x00},		//注
		{0x08,0x04,0x08,0x04,0x14,0x04,0x12,0x24,
			  0x21,0xA4,0x20,0xA4,0x7E,0x24,0xA2,0x24,
			  0x22,0x24,0x2A,0x24,0x24,0x24,0x20,0x04,
			  0x21,0x04,0x21,0x04,0x1F,0x14,0x00,0x08},		//创
		{0x00,0x40,0x42,0x40,0x32,0x50,0x13,0xF8,
			  0x04,0x40,0x00,0x44,0xF7,0xFE,0x10,0x08,
			  0x13,0xFC,0x12,0x08,0x12,0x08,0x12,0x08,
			  0x13,0xF8,0x28,0x06,0x47,0xFC,0x00,0x00},		//造
		{0x01,0x00,0x01,0x10,0x3F,0xF8,0x02,0x80,
			  0x04,0x60,0x08,0x24,0xFF,0xFE,0x00,0x10,
			  0x00,0x90,0x1F,0xD0,0x10,0x90,0x10,0x90,
			  0x1F,0x90,0x10,0x90,0x00,0x50,0x00,0x20},		//奇
		{0x01,0x00,0x40,0xC0,0x20,0x48,0x2F,0xFC,
			  0x01,0x20,0x01,0x20,0xE5,0x28,0x25,0x24,
			  0x25,0x24,0x29,0x24,0x21,0x20,0x21,0x20,
			  0x22,0x60,0x50,0x06,0x8F,0xFC,0x00,0x00},		//迹
		{0x00,0x00,0x01,0x80,0x03,0xC0,0x03,0xC0,
			  0x03,0xC0,0x03,0xC0,0x03,0xC0,0x01,0x80,
			  0x01,0x80,0x01,0x80,0x00,0x00,0x01,0x80,
			  0x03,0xC0,0x01,0x80,0x00,0x00,0x00,0x00}		//！
		};

		void main()
		{
			lcd_init();
			lcd_clear( 7);
			lcd_clear(7);
			lcd_pict(a,20,0,109,160);
			lcd_clear(7);
			lcd_printstring("A T I M E !",20,20,0xf0f0);			
			lcd_printchinese(c[0],55,39,0xf80f);
			lcd_printchinese(c[1],55,55,0xf80f);
			lcd_printchinese(c[2],55,55+16,0xf80f);
			lcd_printchinese(c[3],55,55+16+16,0xf80f);
			lcd_printchinese(c[4],55,55+16+16+16,0xf80f);
			lcd_printchinese(c[5],55,55+16+16+16+16,0xf80f);
			lcd_printchinese(c[6],55,55+16+16+16+16+16,0xf80f);
			while(1);	
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
#define MCUDELAY 580		   //89系列选择75,12系列选择580

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
		for(i=0; i<MCUDELAY; i++)		 
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
void lcd_SetRamAddr(unsigned int xStart, unsigned int xEnd, unsigned int yStart, unsigned int yEnd) 
{
	xStart+=2;
	xEnd  +=2;			   //位置调整

	yStart+=1;
	yEnd  +=1;			   //位置调整
	
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
void  lcd_clear(unsigned char n);	 //声明一个准备调用的函数
void lcd_init(void)					 //液晶初始化程序开始
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
void  lcd_clear(unsigned char n)
{
   unsigned int num;
   
   lcd_SetRamAddr(0,127,0,159);  //设置显示的坐标

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
函数功能：向某矩形区域显示图片
传递参数：
		  a[]:	   带显示数组
		  Start_X: 横向位置起始点
		  End__X:  横向位置结束点
		  Start_Y: 纵向位置起始点
		  End_Y:   纵向未知结束点
返回值：空
取模方式：16位真彩色，水平扫描，从左到右，从上到下，C语言数组格式
		需要将数组设置为code型
***************************************/
void lcd_pict(unsigned char a[],unsigned int Start_X,unsigned int Start_Y, unsigned int End_X, unsigned int End_Y)
{
   unsigned int m;
   LCD_CS = 0;
   lcd_SetRamAddr(Start_X,End_X-1,Start_Y,End_Y-1) ;   //设置地址
   LCD_RS = 1; 

   for(m=0; m<((End_X-Start_X)*(End_Y-Start_Y)); m++)	
   {		
      WriteDAT(a[m*2+1]);	//高位在前
	  WriteDAT(a[m*2]);     //低位在后
   }
   LCD_CS = 1;
}



/************************************
函数功能：在某位置画点
传递参数：
			x	:点的横坐标	0~127
			y	:点的纵坐标	0~159
			color：点的颜色
返回值：
***************************************/
void lcd_point( unsigned char x, unsigned char y, unsigned int color)
{
	unsigned char a[2];
	a[0] =color;
	a[1] =color/0x100;
	lcd_pict(a, x, y, x+1, y+1);	
}

/************************************
函数功能：向右下画线
传递参数：
			xs	:点的起始横坐标	0~127
			ys	:点的起始纵坐标	0~159
			xe	:点的结束横坐标	0~127
			ye	:点的结束纵坐标	0~159
			color：点的颜色
返回值：空
***************************************/
void write_line_right_down( unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned int color)
{
	unsigned char dx, dy, kk, i ,j, dis;
	float k;
	dx =xe-xs;
	dy =ye-ys;
	if(dx >= dy)
		k =dx/dy;
	if(dy > dx)
		k =dy/dx;
	kk =(unsigned char)k;
	if(dx >= dy)
	{
		for(i=0,j=0,dis=0; i<dx; i++)
		{
			dis++;
			if(dis == kk)
			{
				dis =0;
				lcd_point( xs+i, ys+j, color);
				j++;
			}
			lcd_point( xs+i, ys+j, color);		
		}			
	}
	else
	{
		for(i=0,j=0,dis=0; j<dy; j++)
		{
			dis++;
			if(dis == kk)
			{
				dis =0;
				lcd_point( xs+i, ys+j, color);
				i++;
			}
			lcd_point( xs+i, ys+j, color);		
		}
	}	
}




/************************************
函数功能：向右上画线
传递参数：
			xs	:点的起始横坐标	0~127
			ys	:点的起始纵坐标	0~159
			xe	:点的结束横坐标	0~127
			ye	:点的结束纵坐标	0~159
			color：点的颜色
返回值：空
***************************************/
void write_line_right_up( unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned int color)
{
	unsigned char dx, dy, kk, i ,j, dis;
	float k;
	dx =xe-xs;
	dy =ys-ye;
	if(dx >= dy)
		k =dx/dy;
	if(dy > dx)
		k =dy/dx;
	kk =(unsigned char)k;
	if(dx >= dy)
	{
		for(i=0,j=0,dis=0; i<dx; i++)
		{
			dis++;
			if(dis == kk)
			{
				dis =0;
				lcd_point( xe-i, ye+j, color);
				j++;
			}
			lcd_point( xe-i, ye+j, color);		
		}			
	}
	else
	{
		for(i=0,j=0,dis=0; j<dy; j++)
		{
			dis++;
			if(dis == kk)
			{
				dis =0;
				lcd_point( xs+i, ys-j, color);
				i++;
			}
			lcd_point( xs+i, ys-j, color);		
		}
	}	
}




 /************************************
函数功能：任意两点画线
传递参数：
			xs	:点的起始横坐标	0~127
			ys	:点的起始纵坐标	0~159
			xe	:点的结束横坐标	0~127
			ye	:点的结束纵坐标	0~159
			color：点的颜色
返回值：空
***************************************/
void lcd_line( unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned int color)
{
	if(xs <= xe)
	{
		if(ys <= ye)
		{
			write_line_right_down( xs, ys, xe, ye, color);
		}
		else 
		{
			write_line_right_up( xs, ys, xe, ye, color);
		}
	}
	else 
	{
		if(ys <= ye)
		{
			write_line_right_up( xe, ye, xs, ys, color);
		}
		else 
		{
			write_line_right_down( xe, ye, xs, ys, color);
		}	
	}
}


/************************************
函数功能：向某位置显示一个8*16字符
传递参数：
		  x:  横向位置
		  y:  纵向位置
		  color: 字符颜色
		  ch:	 待显示字母
返回值：空
***************************************/
void lcd_printchar( unsigned char ch, unsigned char x, unsigned char y, unsigned int color)
{
	unsigned char temp;
	unsigned char pos,t;

	ch =ch-32;
	for(pos=0; pos<16; pos++)  
	{
		temp= Font8x16[ch][pos];
      
		for(t=0; t<8; t++)
		{                 
			if(temp&0x80)
			{	
				lcd_point( t+x, pos+y, color); 			//字体颜色
			} 									 
			temp<<=1; 
		}
	}
}




/************************************
函数功能：向某位置显示一个字符串
传递参数：
		  x:  横向位置
		  y:  纵向位置
		  color: 字符颜色
		  *p:	 待显示字母数组首地址
返回值：空
***************************************/
void lcd_printstring(unsigned char *p, unsigned char x, unsigned char y, unsigned int color)
{         
  	 while(*p!='\0')
     {       
     	lcd_printchar( *p, x, y, color);
    	 x +=8 ;	  //字体的宽度
    	 p++ ;
    }
}						




/************************************
函数功能：向某位置显示一个汉字
传递参数：
		  x:  横向位置
		  y:  纵向位置
		  color: 文字颜色
		  c:	字符
返回值：空
取模方式：16*16点阵从左到右，从上到下依次取模
		  需要将数组设置为code型。
***************************************/
void lcd_printchinese(unsigned char c[32], unsigned int x, unsigned int y, unsigned int color)
{
 	unsigned char temp;
	unsigned char pos,t;
	for(pos=0; pos<16; pos++)  
	{
		temp= c[2*pos];
		for(t=0; t<8; t++)
		{                 
			
			if(temp&0x80)
			{	
				lcd_point( t+x, pos+y, color); 			//字体颜色
			} 									 
			temp<<=1; 
		}
		temp= c[2*pos+1];
		for(t=0; t<8; t++)
		{                 
			
			if(temp&0x80)
			{	
				lcd_point( t+x+8, pos+y, color); 		//字体颜色
			} 									 
			temp<<=1; 
		}
	}
}


#endif
/************************************
�⹦�ܣ�����1.8��Һ��������
��Ҫ�����������Ѷ��壺
		#include "STC12C5A60S2.H"
		#include "ascii_char.h"
		Ҫ��char.h�ڱ��⺯��ǰ�棬�ṩASCII�����
Ӧ�ú�����
	unsigned int trans_rgb(unsigned char r, unsigned char g, unsigned char b)    ��������δ����
	lcd_init(void)
	lcd_clear(unsigned char n)
	lcd_pict(unsigned char a[],unsigned int Start_X, unsigned int End_X,unsigned int Start_Y,unsigned int End_Y)
    	lcd_point( unsigned char x, unsigned char y, unsigned int color)
	lcd_line( unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned int color)
	lcd_printchar( unsigned char ch, unsigned char x, unsigned char y, unsigned int color)
	lcd_printstring(unsigned char *p, unsigned char x, unsigned char y, unsigned int color)
	lcd_printchinese(unsigned char c[32], unsigned int x, unsigned int y, unsigned int color)
�޸���ʷ��2014-02-25
		   	 ���޸��ˡ�   ���޸����ݡ� 			 ���޸�ʱ�䡯
			  ATIME		 �޸ĺ���			  2014-05-01
			  			 lcd_SetRamAddr(unsigned int xStart, unsigned int xEnd, unsigned int yStart, unsigned int yEnd) 
						 pic_play(unsigned char a[],unsigned int Start_X, unsigned int End_X,unsigned int Start_Y,unsigned int End_Y)
						 ����Ϊͳһ�����ƣ������������Ĳ���˳�� �����޸�������
			  ATIME		 ��Ӻ���			  2014-05-01
			  			 void lcd_point( unsigned char x, unsigned char y, unsigned int color)
						 void write_line_right_down( unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned int color)
						 void write_line_right_up( unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned int color)
						 void lcd_line( unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned int color)
						 void lcd_printchar( unsigned char ch, unsigned char x, unsigned char y, unsigned int color)
						void lcd_printstring(unsigned char *p, unsigned char x, unsigned char y, unsigned int color)
						void lcd_printchinese(unsigned char c[32], unsigned int x, unsigned int y, unsigned int color)
						��߿⺯���Ŀ�����
����޸�ʱ�䣺2013-02-11
���ߣ� ATIME	��Ȩ����
ʵ������
����һ��
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
���̶���
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

��������
		#include "STC12C5A60S2.H" 
		#include "ascii_char.h"
		#include "b.c"
		#include "atime_tft_1_8.h"
		unsigned char code c[7][32]=      
		{
		{0x01,0x00,0x01,0x00,0x01,0x10,0x3F,0xF8,
			  0x02,0x00,0x02,0x04,0xFF,0xFE,0x04,0x00,
			  0x04,0x00,0x0F,0xF8,0x00,0x10,0x00,0x20,
			  0x00,0x40,0x06,0x80,0x01,0x80,0x00,0x40,},	//ר
		{0x00,0x80,0x40,0x40,0x30,0x44,0x17,0xFE,
			  0x80,0x40,0x60,0x40,0x20,0x40,0x08,0x48,
			  0x17,0xFC,0x20,0x40,0xE0,0x40,0x20,0x40,
			  0x20,0x40,0x20,0x44,0x2F,0xFE,0x20,0x00},		//ע
		{0x08,0x04,0x08,0x04,0x14,0x04,0x12,0x24,
			  0x21,0xA4,0x20,0xA4,0x7E,0x24,0xA2,0x24,
			  0x22,0x24,0x2A,0x24,0x24,0x24,0x20,0x04,
			  0x21,0x04,0x21,0x04,0x1F,0x14,0x00,0x08},		//��
		{0x00,0x40,0x42,0x40,0x32,0x50,0x13,0xF8,
			  0x04,0x40,0x00,0x44,0xF7,0xFE,0x10,0x08,
			  0x13,0xFC,0x12,0x08,0x12,0x08,0x12,0x08,
			  0x13,0xF8,0x28,0x06,0x47,0xFC,0x00,0x00},		//��
		{0x01,0x00,0x01,0x10,0x3F,0xF8,0x02,0x80,
			  0x04,0x60,0x08,0x24,0xFF,0xFE,0x00,0x10,
			  0x00,0x90,0x1F,0xD0,0x10,0x90,0x10,0x90,
			  0x1F,0x90,0x10,0x90,0x00,0x50,0x00,0x20},		//��
		{0x01,0x00,0x40,0xC0,0x20,0x48,0x2F,0xFC,
			  0x01,0x20,0x01,0x20,0xE5,0x28,0x25,0x24,
			  0x25,0x24,0x29,0x24,0x21,0x20,0x21,0x20,
			  0x22,0x60,0x50,0x06,0x8F,0xFC,0x00,0x00},		//��
		{0x00,0x00,0x01,0x80,0x03,0xC0,0x03,0xC0,
			  0x03,0xC0,0x03,0xC0,0x03,0xC0,0x01,0x80,
			  0x01,0x80,0x01,0x80,0x00,0x00,0x01,0x80,
			  0x03,0xC0,0x01,0x80,0x00,0x00,0x00,0x00}		//��
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
		
		
����������ͣ�
	123.C(22): error C249: 'DATA': SEGMENT TOO LARGE  ���ļ�̫���ڴ治�㣻����취�������鶨��Ϊcode�����飬�����Ȼ�������Լ���ĳ���ȥ�����õĲ���
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
ע��
	��ʾͼƬҪ����ͼƬ��Сд��������ʼλ�ã�������ʾͼƬ����Ť����λ
	�����ļ������⣬�����������⣬������Ҫ����Ϊcode���顣
	���õĺ�����������ã�/*  */
/***************************************/

#ifndef _ATIME_TFT_1_8_H_ 
#define _ATIME_TFT_1_8_H_

/************************************
��ȫ�ֱ�����
***************************************/

#define  DATA   P0	
sbit LCD_WR   = P2^4;
sbit LCD_RS   = P2^5;
sbit LCD_CS   = P2^6;
sbit LCD_RST  = P2^7;

unsigned int code colors[8]={ 
 0xf800,0x07e0,0x001f,0xffe0,0x0000,0x07ff,0xf81f,0xffff };
//��      ��     ��     ��     ��    ǳ��	����    ��
#define MCUDELAY 580		   //89ϵ��ѡ��75,12ϵ��ѡ��580

/************************************
�������ܣ���ʱn����
���ݲ�������
����ֵ����	
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
�������ܣ�����Ļдһ�ֽ�����
���ݲ�����value�� ��д������
����ֵ����
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
�������ܣ���Һ��д��һ�ֽ�ָ��
���ݲ�����value����д��ָ��
����ֵ����	
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
�������ܣ�������ʾ��ֹλ��
���ݲ�����
		  xStart:������ʾ��ʼ��
		  xEnd ��������ʾ������
		  yStart:������ʾ��ʼ��
		  yEnd : ������ʾ������
����ֵ����	
***************************************/
void lcd_SetRamAddr(unsigned int xStart, unsigned int xEnd, unsigned int yStart, unsigned int yEnd) 
{
	xStart+=2;
	xEnd  +=2;			   //λ�õ���

	yStart+=1;
	yEnd  +=1;			   //λ�õ���
	
	WriteCOM(0x2a);		   //��
	WriteDAT(xStart>>8);   //XS15-XS8
	WriteDAT(xStart);	   //XS7-XS0    (X start address)
	WriteDAT(xEnd>>8);	   //XE15-XE8
	WriteDAT(xEnd);		   //XE7-XE0    (X end address)

	WriteCOM(0x2b);		   //��	row address set (RASET)
	WriteDAT(yStart>>8);   //YS15-YS8
	WriteDAT(yStart);	   //YS7-YS0    (Y start address)
	WriteDAT(yEnd>>8);	   //YE15-YE8
	WriteDAT(yEnd);		   //YE7-YE0    (Y end address)

    WriteCOM(0x2c);		   //display on	��ʾ������  
}


/************************************
�������ܣ�Һ����ʼ��
���ݲ�������
����ֵ����	
***************************************/
void  lcd_clear(unsigned char n);	 //����һ��׼�����õĺ���
void lcd_init(void)					 //Һ����ʼ������ʼ
{	                    //�뿴�����ֲ������� �˽��������Ĺ���
	LCD_RST=1;
	wait_tft18_ms(100);
	LCD_RST=0;
	wait_tft18_ms(100);
	LCD_RST=1;
	wait_tft18_ms(100);
	
	WriteCOM(0x01);	    //software reset�����λ
	wait_tft18_ms(100);
	WriteCOM(0x11);	    //sleep out/power on(SLPOUT) �˳�˯��
	wait_tft18_ms(50);
	WriteCOM(0x20);		//display inversion off �ر�ȡ��
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
�������ܣ����Һ����
���ݲ�����n:��������ɫ
����ֵ����	
***************************************/
void  lcd_clear(unsigned char n)
{
   unsigned int num;
   
   lcd_SetRamAddr(0,127,0,159);  //������ʾ������

   for(num=20480;num>0;num--)          //160*128=20480
   {
  	 WriteDAT(colors[n]>>8);   //��8λ
	 WriteDAT(colors[n]);	   //��8λ
   }
}


/************************************
�������ܣ���ɫת��
���ݲ�����
	R:��ɫ
	G:��ɫ
	B:��ɫ
	ȡֵ��Ϊ0~255
����ֵ��16λ���ɫ��ɫ����ֵ	
***************************************/
unsigned int trans_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return((unsigned int)(r&0xf8)<<8|(unsigned int)(g&0xfc)<<3|(unsigned int)(b&0xf8)>>3);
}


/************************************
�������ܣ���ĳ����������ʾͼƬ
���ݲ�����
		  a[]:	   ����ʾ����
		  Start_X: ����λ����ʼ��
		  End__X:  ����λ�ý�����
		  Start_Y: ����λ����ʼ��
		  End_Y:   ����δ֪������
����ֵ����
ȡģ��ʽ��16λ���ɫ��ˮƽɨ�裬�����ң����ϵ��£�C���������ʽ
		��Ҫ����������Ϊcode��
***************************************/
void lcd_pict(unsigned char a[],unsigned int Start_X,unsigned int Start_Y, unsigned int End_X, unsigned int End_Y)
{
   unsigned int m;
   LCD_CS = 0;
   lcd_SetRamAddr(Start_X,End_X-1,Start_Y,End_Y-1) ;   //���õ�ַ
   LCD_RS = 1; 

   for(m=0; m<((End_X-Start_X)*(End_Y-Start_Y)); m++)	
   {		
      WriteDAT(a[m*2+1]);	//��λ��ǰ
	  WriteDAT(a[m*2]);     //��λ�ں�
   }
   LCD_CS = 1;
}



/************************************
�������ܣ���ĳλ�û���
���ݲ�����
			x	:��ĺ�����	0~127
			y	:���������	0~159
			color�������ɫ
����ֵ��
***************************************/
void lcd_point( unsigned char x, unsigned char y, unsigned int color)
{
	unsigned char a[2];
	a[0] =color;
	a[1] =color/0x100;
	lcd_pict(a, x, y, x+1, y+1);	
}

/************************************
�������ܣ������»���
���ݲ�����
			xs	:�����ʼ������	0~127
			ys	:�����ʼ������	0~159
			xe	:��Ľ���������	0~127
			ye	:��Ľ���������	0~159
			color�������ɫ
����ֵ����
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
�������ܣ������ϻ���
���ݲ�����
			xs	:�����ʼ������	0~127
			ys	:�����ʼ������	0~159
			xe	:��Ľ���������	0~127
			ye	:��Ľ���������	0~159
			color�������ɫ
����ֵ����
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
�������ܣ��������㻭��
���ݲ�����
			xs	:�����ʼ������	0~127
			ys	:�����ʼ������	0~159
			xe	:��Ľ���������	0~127
			ye	:��Ľ���������	0~159
			color�������ɫ
����ֵ����
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
�������ܣ���ĳλ����ʾһ��8*16�ַ�
���ݲ�����
		  x:  ����λ��
		  y:  ����λ��
		  color: �ַ���ɫ
		  ch:	 ����ʾ��ĸ
����ֵ����
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
				lcd_point( t+x, pos+y, color); 			//������ɫ
			} 									 
			temp<<=1; 
		}
	}
}




/************************************
�������ܣ���ĳλ����ʾһ���ַ���
���ݲ�����
		  x:  ����λ��
		  y:  ����λ��
		  color: �ַ���ɫ
		  *p:	 ����ʾ��ĸ�����׵�ַ
����ֵ����
***************************************/
void lcd_printstring(unsigned char *p, unsigned char x, unsigned char y, unsigned int color)
{         
  	 while(*p!='\0')
     {       
     	lcd_printchar( *p, x, y, color);
    	 x +=8 ;	  //����Ŀ��
    	 p++ ;
    }
}						




/************************************
�������ܣ���ĳλ����ʾһ������
���ݲ�����
		  x:  ����λ��
		  y:  ����λ��
		  color: ������ɫ
		  c:	�ַ�
����ֵ����
ȡģ��ʽ��16*16��������ң����ϵ�������ȡģ
		  ��Ҫ����������Ϊcode�͡�
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
				lcd_point( t+x, pos+y, color); 			//������ɫ
			} 									 
			temp<<=1; 
		}
		temp= c[2*pos+1];
		for(t=0; t<8; t++)
		{                 
			
			if(temp&0x80)
			{	
				lcd_point( t+x+8, pos+y, color); 		//������ɫ
			} 									 
			temp<<=1; 
		}
	}
}


#endif
/*******************************************************************/
/*                         GUI 图形化用户界面                      */
/* 文件名: gui.c                                                  */
/* 平台: TOP51 + keil C51                                            */
/* 公司: 爱晶电子                                                  */
/* 网址：http://www.ajdz.net                                       */
// 描  述: TFT图形用户接口层程序集
/* 作者              		日期         		注释       */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* 王伟民		08/10/20			原始文件   */
/* 王伟民		2010/3/30		V1.1移植到STC 高速51单片机*/
/* 王伟民		2010/4/29		V1.2完善了显示预定义汉字字符串函数，不再需要人工修改字符数了*/
/*                        增加了画矩形和显示长整数和长变量函数*/
/*******************************************************************/
/*说明： 数字、英文字符为8*16点阵字形 中文字符为16*16点阵字形                                        */
/*******************************************************************/
#include "stc.h"
#include "top51.h"
#include "GUI/gui.h"
#include "LCM/ILI9325.h"
#include "bmp.h"
#include "16x8.h"
#include "chinese.h"

/************************************
清屏
入口参数： b_color是背景颜色。
出口参数: 无
说明：使用背景颜色清除TFT模块屏幕的全部显示内容。
*************************************/
void GUI_clearscreen(uint b_color)
{
	uint i,j;
	LCD_setwindow(0,0,240,320);
	for (i=0;i<320;i++)
	{
		for(j=0;j<240;j++)
			write_data_u16(b_color);
	}
}


/*********************************************
画点
入口参数： (x，y)是点的坐标，color 是点的颜色。
出口参数: 无
说明：用指定的颜色在指定的坐标位置上画出一个点。
**********************************************/
void GUI_Point(uchar x, uint y, uint color)
{  
	LCD_setxy(x,y);
	write_data_u16(color);
}


/**********************************************************
无符号字符型数以二进制形式显示
入口参数：(x，y)是显示内容的左上角坐标，color 是显示字符的颜色，
          b_color是背景颜色。
出口参数: 无
说明：无符号字符型数用指定的颜色和背景颜色在指定的坐标位置上
以二进制形式显示出来。
************************************************************/
void GUI_sprintf_chartobit(uchar x, uint y,uchar dat, uint color,uint b_color)
{  
	uchar i ;
	for(i=0;i<8;i++)
	{
		if((dat&(0x80>>i))==(0x80>>i))
		{
			GUI_sprintf_nu(x,y,1,color,b_color) ;
		}
		else 
		{
			GUI_sprintf_nu(x,y,0,color,b_color) ;
		}
		x+=8 ;
	}
}


/**********************************************************
无符号字符型数以十六进制形式显示
入口参数：(x，y)是显示内容的左上角坐标，dat 是欲显示的无符号字符型数，
          color 是显示字符的颜色，b_color是背景颜色。
出口参数: 无
说明：无符号字符型数用指定的颜色和背景颜色在指定的坐标位置上
      以十六进制形式显示出来。
************************************************************/
void GUI_sprintf_chartohex(uchar x, uint y,uchar dat, uint color,uint b_color)
{  
	uchar i ;
	GUI_sprintf_nu(x,y,dat>>4,color,b_color) ;
	x+=8 ;
	GUI_sprintf_nu(x,y,dat&0x0f,color,b_color) ;
}


/**********************************************************
无符号字符型数以十进制形式显示
入口参数：(x，y)是显示内容的左上角坐标，dat是欲显示的无符号字符型数，
          color 是显示字符的颜色，b_color是背景颜色。
出口参数: 无
说明：无符号字符型数用指定的颜色和背景颜色在指定的坐标位置上
      以十进制形式显示出来。
************************************************************/
void GUI_sprintf_chartodec(uchar x,uint y,uchar dat,uint color,uint b_color)
{
	GUI_sprintf_char(x,y,dat/100+'0',color,b_color);
	GUI_sprintf_char(x+8,y,dat/10%10+'0',color,b_color);
	GUI_sprintf_char(x+16,y,dat%10+'0',color,b_color);
}


/*********************************************
显示1位16进制数
入口参数： (x，y) 是显示内容的左上角坐标，c：欲显示的1位16进制数，color:颜色,b_color:背景颜色。
出口参数: 无
说明：用指定位置上显示1位16进制数。
**********************************************/
void GUI_sprintf_nu(uchar x, uint y,uchar nu, uint color,uint b_color)
{  
  	uchar  s_x=0 ,s_y=0, temp=0 ;
  	uint j;
   if (nu>9)
  	{nu=nu+7;} 
   nu=nu+16;
   for(s_y=0;s_y<16;s_y++)
   {
	 	if(s_y+y<320)
	   {
			j=nu;
		   j=j*16+s_y;
		   temp=font16x8[j];
	      //temp = font16x8[nu*16+s_y] ;
	  	   for( s_x=0 ; s_x<8 ; s_x++ )
	      {
		     	if(x+s_x<240)
		      {
			     	if((temp&(0x80>>(s_x))) == (0x80>>(s_x))  )
			      {
				   	GUI_Point(x+s_x, y+s_y,color) ;
			      }
			     	else
			      {
				     	GUI_Point(x+s_x, y+s_y,b_color) ;
				   }
			   }
		   }
	   }
	}
}

/**********************************************************
画横线
入口参数： (x，y)是横线起点坐标，length是横线长度，color 是横线颜色。
出口参数: 无
说明：用指定的颜色在指定位置上画出指定长度的一条横线。
************************************************************/
void GUI_HLine(uchar x, uint y, uchar length, uint color) 
{  
	LCD_setwindow(x,y,x+length-1,y);
	do
	{  
		write_data_u16(color);//逐点显示，描出水平线
		length--;
	}while(length);
}

/**********************************************************
画竖线
入口参数： (x，y)是竖线起点坐标，high 竖线高度，color 是竖线颜色。
出口参数: 无
说明：用指定的颜色在指定位置上画出指定长度的一条竖线。
************************************************************/
void GUI_RLine(uchar x, uint y, uint high, uint color) 
{  
   LCD_setwindow(x,y,x,y+high-1);
   do
   {  
		write_data_u16(color);// 逐点显示，描出垂直线
		high--;
   }while(high);	
}


/******************************************************************** 
画直线（可以画任意方向直线，包括横线、竖线、斜线）。
入口参数： (x1,y1)起点, (x2,y2)终点, color颜色。
出口参数: 无
说明：用指定的颜色在指定的两点间画出一条直线。
***********************************************************************/
void GUI_line(uint x1,uint y1,uint x2,uint y2,uint color)  
{  
    uint t;  
    int xerr=0,yerr=0,delta_x,delta_y,distance;  
    int incx,incy;  
    uint row,col;  
    delta_x = x2-x1;//计算坐标增量  
    delta_y = y2-y1;  
    col=x1;  
    row=y1;  
    if(delta_x>0) incx=1;//设置单步方向  
    else   
    {  
        if(delta_x==0) incx=0;//垂直线  
        else {incx=-1;delta_x=-delta_x;}  
    }  
    if(delta_y>0)incy=1;  
    else  
    {  
        if(delta_y==0) incy=0;//水平线  
        else {incy=-1;delta_y=-delta_y;}  
    }  
    if(delta_x>delta_y) distance=delta_x;//选取基本增量坐标轴  
    else distance=delta_y;  

    for(t=0;t<=distance+1;t++)  
	{                                     //画线输出  
	    GUI_Point(col, row, color);
        xerr+=delta_x;  
        yerr+=delta_y;  
      	if(xerr>distance)  
        {  
            xerr-=distance;  
            col+=incx;  
        }  
        if(yerr>distance)  
        {  
            yerr-=distance;  
            row+=incy;  
        }  
    }  
}


/**********************************************************
显示图片(图标)
入口参数：(x，y)是开始点的坐标，length是图片长度，high是图片高度。//pic 图片数组的指针
出口参数: 无
说明：用指定位置上显示事先定义的图片。
要显示的图片事先定义在bmp.h中的pic[]数组中，
如果想修改图片大小、内容，请修改bmp.h中的pic[]数组，
建议用Image2Lcd软件将你要显示的图象自动转换为数组数据。 
************************************************************/
//void GUI_DisPicture(uchar x, uint y, uchar length, uint high ,const uchar *pic)
void GUI_DisPicture(uchar x, uint y, uchar length, uint high)
{
   uint temp=0,tmp=0,num=0;
	LCD_setwindow(x,y,x+length-1,y+high-1);
	num=length*high*2;
	do
	{  
	   //temp=pic[tmp]|( pic[tmp+1]<<8);
	   temp=pic[tmp+1];
	   temp=temp<<8;
	   temp=temp|pic[tmp];
	   write_data_u16(temp);//逐点显示
	   tmp+=2;
	}while(tmp<num);
}


/*********************************************
显示英文或数字字符
入口参数：(x，y) 是显示内容的左上角坐标，c：显示的英文字符，
          color:颜色,b_color:背景颜色。
出口参数: 无
说明：用指定位置上显示单个英文字符或数字字符。
**********************************************/
void GUI_sprintf_char(uchar x, uint y,uchar c, uint color,uint b_color)
{  
	uchar  s_x ,s_y, temp ;
  	uint j;
  	c -= 32;
  	for( s_y=0 ; s_y < 16 ; s_y++ )
   {
		if(s_y+y<320)
	   {
			j=c;
		   j=j*16+s_y;
		   temp=font16x8[j];
	     	//temp = font16x8[c*16+s_y] ;
	  	   for( s_x=0 ; s_x<8 ; s_x++ )
	      {
		    	if(x+s_x<240)
		      {
			     	if((temp&(0x80>>(s_x))) == (0x80>>(s_x))  )
			      {
				   	GUI_Point(x+s_x, y+s_y,color) ;
			      }
			     	else
			      {
				     	GUI_Point(x+s_x, y+s_y,b_color) ;
				   }
			   }
		   }
	   }
	}
}



/*********************************************
显示英文字符串
入口参数：(x，y) 是显示内容的左上角坐标，*s：英文字符串指针，
          color:颜色,b_color:背景颜色。
出口参数: 无
说明：在指定位置上显示英文字符串。
**********************************************/
void GUI_sprintf_string(uchar x, uint y,char code *s, uint color,uint b_color)
{  
	for(;*s!='\0';s++)
	{
		GUI_sprintf_char(x, y,*s, color,b_color);
		x=x+8;
	}
	
	//while (*s) 
	//	{
	//	GUI_sprintf_char(x, y,*s, color,b_color);
	//	s++;
	//	x=x+8;
	//	}
}


/*********************************************
显示预定义汉字字符串
入口参数：(x，y) 是显示内容的左上角坐标，color:颜色,b_color:背景颜色。
出口参数: 无
说明：在指定位置上显示预定义的中文字符串。
      要显示的中文字符串事先定义在chinese.h中的china_char[]数组中，
		如果想修改中文字符串长度、内容，请修改chinese.h中的
		china_char[]数组，建议用字模提取软件zimoV2.2将你要显示的
		中文字符串自动转换为数组数据。
**********************************************/
void GUI_sprintf_HZ(uchar x, uint y, uint color,uint b_color)
{ 
	uchar  s_x=0 ,s_y=0, temp=0 ;  
	uchar n;
	uint j,words;
	words=sizeof(china_char)/32;
	for( n=0 ; n<words ; n++ )
  	{
	 	for( s_x=0 ; s_x<16 ; s_x++ ) 
	  	{
	   	if(s_x+x<240)
	   	{
	   	   j=n;
	   	   j=j*32+s_x;
	   	   temp = china_char[j] ;
	   	   //temp = china_char[n*32+s_x] ;
	   		for( s_y=0 ; s_y<8 ; s_y++ )
	       	{
		     		if(y+s_y<320)
		       	{
			     		if((temp&(0x80>>(s_y))) == (0x80>>(s_y))  )
			       	{
				      	GUI_Point(x+s_x+n*16, y+s_y,color) ;
			       	}
			     		else
			       	{
				      	GUI_Point(x+s_x+n*16, y+s_y,b_color) ;
				   	}
					}
		   	}
		   }
		}
		for( s_x=0 ; s_x<16 ; s_x++ ) 
	  	{
	   	if(s_x+x<240)
	   	{
	   		j=n;
	   		j=j*32+s_x+16;
	   		temp = china_char[j] ;
	   		//temp = china_char[n*32+s_x+16] ;
		    	for( s_y=0 ; s_y<8 ; s_y++ )
	       	{
		     		if(y+s_y<320)
		       	{
			     		if((temp&(0x80>>(s_y))) == (0x80>>(s_y))  )
			       	{
				      	GUI_Point(x+s_x+n*16, y+s_y+8,color) ;
			       	}
			     		else
			       	{
				      	GUI_Point(x+s_x+n*16, y+s_y+8,b_color) ;
				   	}
					}
		   	}
		   }
		}
	}
}



/*********************************************
画实心矩形
入口参数： (sx,sy)左上角顶点坐标, (ex,ey)右下角顶点坐标, color颜色
出口参数: 无
说明：在指定位置上画出实心矩形。
**********************************************/
void GUI_box(uchar sx,uint sy,uchar ex,uint ey,uint color)
{ 
	uint temp;   
	LCD_setwindow(sx,sy,ex,ey); 
   sx=ex-sx+1;
	sy=ey-sy+1;

	while(sx--)
	{
	 	temp=sy;
		while(temp--)
	 	{	
			write_data_u16(color);
		}
	}
}


/*********************************************
画空心矩形
入口参数： (sx,sy)左上角顶点坐标, (ex,ey)右下角顶点坐标, color颜色
出口参数: 无
说明：在指定位置上画出空心矩形。
**********************************************/
void GUI_rectangle( uchar sx,uint sy,uchar ex,uint ey,uint color)
{
	GUI_line(sx,sy,ex,sy,color);
	GUI_line(sx,sy,sx,ey,color);
	GUI_line(ex,sy,ex,ey,color);
	GUI_line(sx,ey,ex,ey,color);
}

/*********************************************
以十进制形式显示无符号长整型数
入口参数：(x，y) 是显示内容的右上角坐标；
			 num是欲显示的无符号长整型数
	       num的数值范围为：0~4,294,967,295(十进制)，
			 也就是说利用该函数，我们最多将一个10位十进制数显示在LCD屏上；
			 color:颜色,b_color:背景颜色。
出口参数: 无
说明：将一个无符号长整型数以十进制形式显示在TFT屏上。
注意：在使用该函数时，不论最终显示的数有几位，它都将在LCD屏幕上
      占10个字符的空间（显示的多位十进制数不足10位时，
		本函数会在有效显示数字前面补空格）。
**********************************************/
void GUI_wrul(uchar x, uint y, unsigned long num, uint color,uint b_color)
{
	unsigned long temp; 
	uchar i;
	for(i=0;i<10;i++)
	{
		if(num!=0)
		{
			temp=num/10;
			GUI_sprintf_char(x-7,y,num-temp*10+'0',color,b_color);
			num=temp;
		}
		else/*往前写满10位，也就是前面都写空格*/
		{
			GUI_sprintf_char(x-7,y,' ',color,b_color);
		}
		x=x-8;/*设置光标在文字插入后自动左移*/
	}
}

/*********************************************
以十进制形式显示长变量
入口参数： 
   x，y ----是显示内容的右上角坐标 
    num ----欲显示的长变量
   bits ----允许显示的位数
     dp ----小数点位置
  color ----颜色
b_color ----背景颜色
出口参数: 无
说明： 
将一个长变量的数值以十进制形式显示在TFT屏上，可以根据需要确定
是否显示小数点以及小数点位置，也可以确定在TFT屏幕上显示的位数。
注意：
1、要显示的数据比规定的显示位数多，规定的位全部写－，表示数据溢出。
2、本函数实际上相当于GUI_wrul函数的增强版，如果我们指定bits=10 dp=0，
如下所示：
GUI_wrlval(20，239，tp，10，0,WHITE,BLACK);
那么，其作用和GUI_wrul函数完全一样。
**********************************************/
void GUI_wrlval(uchar x, uint y,unsigned long num,uchar bits,uchar dp,uint color,uint b_color)
{
	char str[10];/*无符号长整型数转换为字符串是10个，所以需要10个单元存储*/	
	unsigned long temp; 
	uchar i;
	//LCD_wrcmd(CUR_AUTO_L);/*设置光标在文字插入后自动左移*/
	for(i=0;i<bits;i++)
	{
		if(num!=0)
		{
			temp=num/10;
			str[i]=num-temp*10+'0';
			num=temp;
		}
		else/*往前写*/
		{
			if(i>=dp)str[i]=0x20;/*小数点前零都变空格*/
			else str[i]='0';/*小数点后零保留*/
		}
	}
	i=0;
	if (num!=0)/*要显示的数据比规定的显示位数多，数据显示溢出*/
	{
		while(i<bits)/*往前写满规定的位数，也就是前面都写空格，直到规定的位数*/
		{
			GUI_sprintf_char(x-7,y,'-',color,b_color);/*规定的位全部写-，表示数据溢出*/
			i++;
			x=x-8;
			if (i==dp) 
			{
				GUI_sprintf_char(x-7,y,'.',color,b_color);/*插入小数点*/
				x=x-8;
			}
		}
	}
	else
	{
		while(i<bits)/*显示前面的有效数字*/
		{
			if ((i==dp)&(str[dp]==0x20))
			{
				GUI_sprintf_char(x-7,y,'.',color,b_color);/*插入小数点*/
				x=x-8;
				GUI_sprintf_char(x-7,y,'0',color,b_color);/*小数点前为0时要补写0*/
				x=x-8;
			}
			else
			{
				if ((i==dp)&(i!=0)) 
				{
					GUI_sprintf_char(x-7,y,'.',color,b_color);/*插入小数点*/
					x=x-8;
				}
				GUI_sprintf_char(x-7,y,str[i],color,b_color);
				x=x-8;
			}
			i++;				
		}
	}
}


/********************************************* 
RGB颜色混合
入口参数：R（红色分量）0-255,G（绿色分量）0-255,B（蓝色分量）0-255
出口参数: 按R5-G6-B5格式混合后的16位颜色码。
说明：将电脑上常见的R8-G8-B8格式转换成8位单片机常用的R5-G6-B5格式。
**********************************************/
uint RGB(uchar R,uchar G,uchar B)
{
	return((uint)(R&0XF8)<<8|(uint)(G&0XFC)<<3|(uint)(B&0XF8)>>3);
}


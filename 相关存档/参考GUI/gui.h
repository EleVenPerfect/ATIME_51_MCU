#ifndef GUI_H
#define GUI_H

#include"config.h"

/*GUI函数*/
void GUI_clearscreen(uint b_color);//清屏
void GUI_Point(uchar x, uint y, uint color);//画点
void GUI_sprintf_chartobit(uchar x, uint y,uchar dat, uint color,uint b_color);//无符号字符型数以二进制形式显示
void GUI_sprintf_chartohex(uchar x, uint y,uchar dat, uint color,uint b_color);//无符号字符型数以十六进制形式显示
void GUI_sprintf_chartodec(uchar x,uint y,uchar dat,uint color,uint b_color);//无符号字符型数以十进制形式显示
void GUI_sprintf_nu(uchar x, uint y,uchar nu, uint color,uint b_color);//显示1位16进制数
void GUI_HLine(uchar x, uint y, uchar length, uint color);//画横线
void GUI_RLine(uchar x, uint y, uint high, uint color);//画竖线
void GUI_line(uint x1,uint y1,uint x2,uint y2,uint color);//画直线
void GUI_DisPicture(uchar x, uint y, uchar length, uint high);//显示图片(图标)
void GUI_sprintf_char(uchar x, uint y,uchar c, uint color,uint b_color);//显示英文或数字字符
void GUI_sprintf_string(uchar x, uint y,char code *s, uint color,uint b_color);//显示英文字符串
void GUI_sprintf_HZ(uchar x, uint y, uint color,uint b_color);//显示预定义汉字字符串
void GUI_box(uchar sx,uint sy,uchar ex,uint ey,uint color);//画实心矩形
void GUI_rectangle( uchar sx,uint sy,uchar ex,uint ey,uint color);//画空心矩形
void GUI_wrul(uchar x, uint y, unsigned long num, uint color,uint b_color);//以十进制形式显示无符号长整型数
void GUI_wrlval(uchar x, uint y,unsigned long num,uchar bits,uchar dp,uint color,uint b_color);//以十进制形式显示长变量
uint RGB(uchar R,uchar G,uchar B);//RGB颜色混合


/*定义常用颜色的颜色码*/
#define RED 0xf800	//红
#define YELLOW 0xffe0	//黄
#define GREEN 0x07e0	//绿
#define CYAN 0x07ff	//青
#define BLUE 0x001f	//蓝
#define PURPLE 0xf81f	//紫
#define BLACK 0x0000	//黑
#define WHITE 0xffff	//白
#define GRAY 0x7bef	//灰


#endif














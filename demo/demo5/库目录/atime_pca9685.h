/************************************
库功能：PCA9685
库要求：主函数中已定义：
		#include <reg52.h>
应用函数：
			key4_4( )
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-01-29
作者： ATIME	版权所有
实例程序：

常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
***************************************/


#ifndef _ATIME_PCA9685_H_ 
#define _ATIME_PCA9685_H_

#include "atime_iic.h"

/************************************
库全局变量组
***************************************/

#define PCA9685_ADDR 		0x80			//定义PCA9685硬件地址
#define PCA9685_MODE1 		0x00
#define PCA9685_PRESCALE	0xfe
#define LED0_ON_L 			0x6
#define LED0_ON_H 			0x7
#define LED0_OFF_L 			0x8
#define LED0_OFF_H 			0x9
/************************************
函数功能：写数据到指定地址
传递参数：transdata：数据
		  addr	   ：指定地址
返回值：空	
***************************************/
void pca9685_write( unsigned char addr, unsigned char transdata)
{
	iic_write_char( PCA9685_ADDR, addr, transdata);
}



/************************************
函数功能：读指定地址数据
传递参数：
		  addr	   ：指定地址
返回值：transdata：数据
***************************************/
unsigned char pca9685_read( unsigned char addr)
{
	unsigned char transdata;
	transdata = iic_read_char( PCA9685_ADDR, addr);
	return transdata;
}



/************************************
函数功能：复位
传递参数：空
返回值：空	
***************************************/
void pca9685_reset()
{
	pca9685_write( PCA9685_MODE1, 0x0);
}


/************************************
函数功能：设置频率
传递参数：freq：频率
返回值：空	
***************************************/
void pca9685_setfreq(float freq)
{
	unsigned char lastmode,newmode,prescale;
	float prescaleval;
	freq *= 0.92;  // Correct for overshoot in the frequency setting
	prescaleval = 6103.515;
	prescaleval /= freq;
    prescaleval -= 1;
    prescale = (unsigned char)(prescaleval + 0.5);	

	lastmode = pca9685_read(PCA9685_MODE1);
	newmode = (lastmode&0x7F)|0x10; // sleep
	pca9685_write( PCA9685_MODE1, newmode);
	pca9685_write( PCA9685_PRESCALE, prescale);
	pca9685_write( PCA9685_MODE1, lastmode);
	for( newmode=0; newmode<200; newmode++);   //延时
	pca9685_write( PCA9685_MODE1,lastmode|0xa1);
}

/************************************
函数功能：设置占空比
传递参数：
返回值：空	
***************************************/
void pca9685_setpwm(unsigned char num, unsigned int on, unsigned int off) 
{
    pca9685_write(LED0_ON_L+4*num,on);
    pca9685_write(LED0_ON_H+4*num,on>>8);
    pca9685_write(LED0_OFF_L+4*num,off);
    pca9685_write(LED0_OFF_H+4*num,off>>8);
}

#endif
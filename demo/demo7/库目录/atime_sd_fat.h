/************************************
库功能：FAT文件系统
库要求：程序已经载入：
		#include <reg52.h>
		#include "atime_spi.h"
		#include "atime_spi_sdcard.h"
		#include "atime_sd_fat.h"	
应用函数：
			unsigned char int_fat(void)
			unsigned char read_file_start512(unsigned long cluster, unsigned char number)
			unsigned char read_file_continue512(unsigned char part)
			unsigned char search_file_name( unsigned long cluster, unsigned char name[12])
修改历史：
		   	 ‘修改人’       ‘修改内容’  			‘修改时间’
最后完成时间：2014-04-12
作者： ATIME	版权所有
实例程序：
例程01：分配单元采用512字节：
			#include <reg52.h>
			#include "atime_serial.h"
			#include "atime_spi.h"
			#include "atime_spi_sdcard.h"
			#include "atime_sd_fat.h"
			
			
			void main()
			{
				unsigned char offset;
				unsigned int i;
				serial_int(disable, baud9600, disable);
			
				int_fat();
				read_file_start512(fat_info.fat_clu_dir, 4);
			
				for(offset=FAT_READING; offset!=FAT_READ_OK; )
				{
					offset =read_file_continue512(0);
			
					for(i=0; i<512; i++)
						send_char(fat_temp[i]);
			
				}
			
				while(1);
			}
例程02：分配单元采用1024字节：			
			#include <reg52.h>
			#include "atime_serial.h"
			#include "atime_spi.h"
			#include "atime_spi_sdcard.h"
			#include "atime_sd_fat.h"
			
			
			void main()
			{
				unsigned char offset,j;
				unsigned int i;
				serial_int(disable, baud9600, disable);
			
				int_fat();
			
				send_char(fat_info.fat_cluster);
				read_file_start512(fat_info.fat_clu_dir, 4);
				for(i=0; i<512; i++)
					send_char(fat_temp[i]);
				read_file_continue512(1);
				for(i=0; i<512; i++)
					send_char(fat_temp[i]);
				for(offset=FAT_READING; offset!=FAT_READ_OK; )
				{
					for(j=0; j<fat_info.fat_cluster; j++)
					{
						offset =read_file_continue512(j);
				
						for(i=0; i<512; i++)
							send_char(fat_temp[i]);
					}
				}
			
				while(1);
			}

例程03：通过文件名查找并打开文件
			#include <reg52.h>
			#include "atime_serial.h"
			#include "atime_spi.h"
			#include "atime_spi_sdcard.h"
			#include "atime_sd_fat.h"
			
			void main()
			{
				unsigned char number,offset;
				unsigned int i;
				serial_int(disable, baud9600, disable);
				int_fat();
			
				number =search_file_name( fat_info.fat_clu_dir, "CHAR    .TXT");	 //需要文件系统根目录保存有CHAR.TXT文件
				send_char(number);
			
				read_file_start512(fat_info.fat_clu_dir, number);
				for(i=0; i<512; i++)
					send_char(fat_temp[i]);
				for(offset=FAT_READING; offset!=FAT_READ_OK; )
				{
					offset =read_file_continue512(0);
				
					for(i=0; i<512; i++)
						send_char(fat_temp[i]);
				}
			
				while(1);
			}

常见错误解释：
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库前面几行
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
注意：
	本文件系统为FAT32文件系统，目前仅支持读取文件数据，并不提供写数据功能，
	文件名只支持少于8字节的段文件名，文件名应用大写字母表示。
	读取文件过程中，只是用了第一个FAT表，对于FAT表1和表2存在的差别无法判断，
	本库函数不提供文件读取后的数据处理，
	因此文件数据的读取数量并不取决于文件的真实大小，而是按照扇区的数目，将每个读取了的扇区数据全部呈现出来，
	库函数内部只含有一个读取数据的缓存fat_temp[512]，因此，调用完读取数据的函数后应该立即取走所需的数据，防止下一个函数将缓存数据覆盖，
	文件系统初始化后，文件系统信息fat_info将不会更改，
	读取文件后，文件信息除了下一个簇的簇号会改变外，其他信息将与当前读取文件的信息保持一致。
	所有文件、文件夹的读取都视为对文件数据的读取，如果需要判断是否为文件夹，需要再判断文件大小、文件标志等。
	函数库中的全局标量都已经设置为XDATA，有些型号单片机可能会内存不足，可以尝试取消部分变量的XDATA属性。	

	本库的调试是在512M的sd卡上进行的，格式化时选择文件系统FAT32，分配单元大小512字节，没有选择还原设备的默认值。
***************************************/


#ifndef _ATIME_SD_FAT_H_ 
#define _ATIME_SD_FAT_H_


/************************************
库全局变量组
***************************************/

unsigned char xdata fat_temp[512] ={0};		//FAT数据缓存

/************************************
文件系统结构体组
***************************************/

struct fat_info
{
	unsigned long fat_offset;				//引导扇区起始扇区数
	unsigned long fat_directory;			//根目录扇区数
	unsigned long fat_clu_dir;				//根目录起始簇数
	unsigned long fat_fat1;					//fat表扇区数
	unsigned char fat_cluster;				//每簇扇区数
}xdata fat_info;


struct file_info
{
	unsigned char file_name[9];				//文件名，最后一位设置为0。
	unsigned char file_extension[4];		//扩展名，最后一位设置为0。
	unsigned long file_size;				//文件大小
	unsigned long file_position;			//文件起始簇簇号
	unsigned long file_next_pos;			//文件的下一个簇的簇号
}xdata file_info;

/************************************
错误宏定义组组
***************************************/

#define NOT_FAT			0X01				//不是FAT文件系统
#define FAT_OK			0X00				//FAT32准备就绪
#define FAT_READ_OK		0x03			    //读取文件数据完成
#define FAT_READING		0x04				//文件正在读取中，且仍可以继续读取
/************************************
函数功能：FAT文件系统MBR初始化
传递参数：空
返回值：起始扇区数
错误返回值：NOT_FAT:不是FAT文件系统或没有检测到SD卡
***************************************/
unsigned long int_mbr_fat(void)
{
	unsigned int i;
	unsigned char not_exit;
	unsigned long offset;

	for(i=0; i<100; i++);
	not_exit =sd_res();
	if(not_exit == 0x01)
		return( NOT_FAT);
	sd_read512( 0, fat_temp);
	if(fat_temp[510] != 0x55 ||fat_temp[511] !=0xAA)
		return( NOT_FAT);
	if(fat_temp[450] != 0x0B)
		return( NOT_FAT);
	if(fat_temp[0] == 0xEB)
		return(0);

	offset =fat_temp[454] +fat_temp[455]*0x100 +
			fat_temp[456]*0x10000 +fat_temp[457]*0x1000000;
		    

	return ( offset);
}


/************************************
函数功能：FAT文件系统DBR初始化
传递参数：offset：起始扇区数
返回值：根目录扇区数
错误返回值：NOT_FAT:不是FAT文件系统或没有检测到SD卡
***************************************/
unsigned long int_dbr_fat(unsigned long offset)
{
	unsigned long directory;
	unsigned char not_exit;

	not_exit =sd_read512( offset, fat_temp);
	if(not_exit == 0x04)
		return(NOT_FAT);
	if(fat_temp[0] != 0xEB)
		return ( NOT_FAT);
	directory =offset +fat_temp[14] +fat_temp[15]*0x100
		       +fat_temp[16]*(fat_temp[36] +fat_temp[37]*0x100	
			   +fat_temp[38]*0x10000 +fat_temp[39]*0x1000000);	
			  
	return ( directory);
}



/************************************
函数功能：每簇扇区数
传递参数：offset：起始扇区数
返回值：每簇扇区数
***************************************/
unsigned char cluster_sector(unsigned long offset)
{
	sd_read512( offset, fat_temp);
	return( fat_temp[13]);
}


/************************************
函数功能：FAT文件系统DBR初始化
传递参数：offset：起始扇区数
返回值：FAT表1的扇区数
***************************************/
unsigned long int_dbr_fat_dir(unsigned long offset)
{
	unsigned long directory;

	sd_read512( offset, fat_temp);

	directory =offset +fat_temp[14] +fat_temp[15]*0x100;	
			  
	return ( directory);	
}


/************************************
函数功能：读取根目录起始簇数
传递参数：offset：起始扇区数
返回值：根目录起始簇数
***************************************/
unsigned long int_dbr_clu_dir(unsigned long offset)
{
	sd_read512( offset, fat_temp);
	return( fat_temp[44] +fat_temp[45]*0x100 +fat_temp[46]*0x10000 +fat_temp[47]*0x1000000);
}


/************************************
函数功能：fat32文件系统初始化
传递参数：空
返回值：初始化结果
		FAT_OK  :文件系统准备就绪
		NOT_FAT	:不是FAT文件系统或没有插SD卡
错误返回值：NOT_FAT:不是FAT文件系统或没有检测到SD卡
***************************************/
unsigned char int_fat(void)
{
	fat_info.fat_offset		=int_mbr_fat();
	if(fat_info.fat_offset == NOT_FAT)
		return( NOT_FAT);
	fat_info.fat_directory	=int_dbr_fat( fat_info.fat_offset);
	if(fat_info.fat_directory == NOT_FAT)
		return( NOT_FAT);
	fat_info.fat_fat1		=int_dbr_fat_dir( fat_info.fat_offset);
	fat_info.fat_cluster	=cluster_sector( fat_info.fat_offset);
    fat_info.fat_clu_dir	=int_dbr_clu_dir( fat_info.fat_offset);

	return(FAT_OK);
}


/************************************
函数功能：FAT表中查找下一个簇位置，并更新到文件项缓存中
传递参数：空
返回值：空
***************************************/
void find_next_cluster(void)
{
	unsigned long next_cluster =0;
	next_cluster =fat_info.fat_fat1 +file_info.file_next_pos/128;	
	sd_read512( next_cluster, fat_temp);
	file_info.file_next_pos =fat_temp[(file_info.file_next_pos%128)*4]+
				  			 fat_temp[(file_info.file_next_pos%128)*4+1]*0x100+	
				   			 fat_temp[(file_info.file_next_pos%128)*4+2]*0x10000+
				  			 fat_temp[(file_info.file_next_pos%128)*4+3]*0x1000000;

}								



/************************************
函数功能：簇转换为扇区
传递参数：cluster：簇数
返回值：扇区数
***************************************/
unsigned long cluster_to_offset(unsigned long cluster)
{
	unsigned long offset;
	if(cluster < fat_info.fat_clu_dir)
		return (NOT_FAT);
	offset =fat_info.fat_directory +( cluster -fat_info.fat_clu_dir)*fat_info.fat_cluster;
	return ( offset);
}



/************************************
函数功能：读取文件项信息
传递参数：cluster：文件项所在簇数
		  number：文件项编号（从0开始）
返回值：空
***************************************/
void read_filetable(unsigned long cluster, unsigned char number)
{
	unsigned long offset;

	offset =cluster_to_offset( cluster);	 
	offset =offset +number/16;
			    
	sd_read512( offset, fat_temp);

	file_info.file_name[0] =fat_temp[(number%16)*32];
	file_info.file_name[1] =fat_temp[(number%16)*32+1];
	file_info.file_name[2] =fat_temp[(number%16)*32+2];
	file_info.file_name[3] =fat_temp[(number%16)*32+3];
	file_info.file_name[4] =fat_temp[(number%16)*32+4];
	file_info.file_name[5] =fat_temp[(number%16)*32+5];
	file_info.file_name[6] =fat_temp[(number%16)*32+6];
	file_info.file_name[7] =fat_temp[(number%16)*32+7];
	file_info.file_name[8] =0x00;

	file_info.file_extension[0] =fat_temp[(number%16)*32+8];
	file_info.file_extension[1] =fat_temp[(number%16)*32+9];
	file_info.file_extension[2] =fat_temp[(number%16)*32+10];
	file_info.file_extension[3] =0x00;

	file_info.file_size =fat_temp[(number%16)*32+31]+
						 fat_temp[(number%16)*32+30]*0x100+
						 fat_temp[(number%16)*32+29]*0x10000+
						 fat_temp[(number%16)*32+28]*0x1000000;

	file_info.file_position =fat_temp[(number%16)*32+26]+
							 fat_temp[(number%16)*32+27]*0x100+
							 fat_temp[(number%16)*32+20]*0x10000+
							 fat_temp[(number%16)*32+21]*0x1000000;

	file_info.file_next_pos =fat_temp[(number%16)*32+26]+
							 fat_temp[(number%16)*32+27]*0x100+
							 fat_temp[(number%16)*32+20]*0x10000+
							 fat_temp[(number%16)*32+21]*0x1000000;

}


/************************************
函数功能：开始读取文件内容
传递参数：cluster：文件项所在簇，
		  number：文件项序列号（从0开始计数）。
返回值：读取文件按状态
		FAT_READ_OK：读取完成
		FAT_READING:文件正在读取中
***************************************/
unsigned char read_file_start512(unsigned long cluster, unsigned char number)
{
	unsigned long offset;
	read_filetable( cluster, number);														
	offset =cluster_to_offset( file_info.file_next_pos);	
	if(fat_info.fat_cluster == 0x01)
		find_next_cluster();
	sd_read512( offset, fat_temp);			    	//要在判断读取下一个数据之后读取数据，防止被更改
	if(file_info.file_next_pos*0x10 >= 0X00000020 && file_info.file_next_pos*0x10 <= 0XFFFFFEF0)
		return( FAT_READING);	
	
	return( FAT_READ_OK);
}

/************************************
函数功能：继续读取文件内容
传递参数：part：文件内容所在簇的第几个扇区
返回值：读取文件按状态
		FAT_READ_OK：读取完成
		FAT_READING:文件正在读取中
***************************************/
unsigned char read_file_continue512(unsigned char part)
{
	unsigned long offset;
	offset =cluster_to_offset( file_info.file_next_pos) +part;
	if((part+1) == fat_info.fat_cluster)
		find_next_cluster();	
	sd_read512( offset, fat_temp);					//要在判断读取下一个数据之后读取数据，防止被更改
	if( file_info.file_next_pos*0x10 >= 0X00000020 && file_info.file_next_pos*0x10 <= 0XFFFFFEF0)
		return( FAT_READING);	
	
	return( FAT_READ_OK);
}


/************************************
函数功能：查找文件项序列号
传递参数：cluster：待查找文件项所在簇
		  name[11]:文件名及扩展名，空格用0x20填充。
		  格式说明：name[0~7]:文件名，name[8]:小数点，name[9~11]: 扩展名，名字不够长度用空格填充。
返回值：文件项序列号，如果号码大于簇的最大包含文件项数，则没有找到文件
	    一个文件项32字节，一个扇区512个字节，因此有一个簇多少扇区就有16X个文件项
		即：16*fat_info.fat_cluster
***************************************/
unsigned char search_file_name( unsigned long cluster, unsigned char name[12])
{
	unsigned char i;

	for(i=0; i<16*fat_info.fat_cluster; i++)
	{
		read_filetable( cluster, i);
		if(name[0] != file_info.file_name[0])
			continue;
		if(name[1] != file_info.file_name[1])
			continue;
		if(name[2] != file_info.file_name[2])
			continue;
		if(name[3] != file_info.file_name[3])
			continue;
		if(name[4] != file_info.file_name[4])
			continue;
		if(name[5] != file_info.file_name[5])
			continue;
		if(name[6] != file_info.file_name[6])
			continue;
		if(name[7] != file_info.file_name[7])
			continue;
		
		if(name[ 9] != file_info.file_extension[0])
			continue;
		if(name[10] != file_info.file_extension[1])
			continue;
		if(name[11] != file_info.file_extension[2])
			continue;
		
		break;		
	}
	return (i);
}





/************************************
函数功能：
传递参数：
返回值：
***************************************/

#endif
/***************************************************************/

#ifndef  __fat_H__             //��������ָ��
#define  __fat_H__             //�����ظ�����

#include "mmc.h"

#define	FAT16	8
#define	FAT32	7
#define MBR_ERR		0x01
#define	DBR_ERR		0x02
#define SECTORS_ERR		0x30
#define CLUSTER_COUNT_ERR	0x31

#define  uchar   unsigned char
#define  uint    unsigned int
#define  uint8   unsigned char
#define  int8    signed char
#define  uint16  unsigned int
#define  int16   signed int
#define  uint32  unsigned long
#define  int32   signed long

extern  xdata  uchar buffer[];


extern  uint8   BPBSecPerClust;   // ÿ�ص�������
extern  uint16  FirstFATSector;   // ��FAT��ʼ����
extern  uint16  FirstDirSector;   // ��Ŀ¼��ʼ����
extern  uint16  FirstDataSector;  // ��������ʼ����
extern  uint32  FatClusSec;       // �غ����ڵ�����
extern  uint32  FirstDircluster;  // FAT32��Ŀ¼�״غ�
extern  uint8   DirSecitemCunt;   // FDTÿ����Ŀ¼����� FAT16=8 FAT32=7


extern xdata  uint16 BPBbytesPerSec;		// ÿ�������ֽ���
extern xdata	uint16 BPBRevdFATSec;		// FAT1ǰ�ı���������
extern xdata	uint8  ParNumberFATs;		// �÷����ϵ�FAT����
//	uint16 BPBRootDirCunt;			// ��Ŀ¼����
extern xdata	uint16 BPBTotSector16;		// 16λ������
extern xdata	uint16 BPBFATPerSec16;		// 16bitÿFATռ�õ�������
extern xdata	uint16 BPBhiddsector;		// �÷���ϵͳ����������
extern xdata	uint32 BPBTotSector32;		// 32λ������
extern xdata	uint32 DataClusterCount;	// ����������
extern xdata	uint32 Sector;				// ��������

extern  uint8 FAT_init();

#endif                      //�����������

/****************************************************************/
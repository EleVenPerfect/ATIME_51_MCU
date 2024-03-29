
//};

const unsigned char code hz24[]={

/*------------------------------------------------------------------------------

;  源文件 / 文字 : 普
;  宽×高（像素）: 24×24
;  字模格式/大小 : 单色点阵液晶字模，横向取模，字节倒序/72字节

------------------------------------------------------------------------------*/
/*--  宽度x高度=24x24  --*/
0xc0,0x80,0x00,0x80,0x83,0x03,0x00,0xc7,0x01,0x00,0xc6,0x10,0xfc,0xff,0x3f,0x08,
0xe7,0x04,0x18,0x66,0x0c,0x30,0x66,0x0c,0x60,0x66,0x06,0xe0,0x66,0x03,0x40,0xe6,
0x31,0xff,0xff,0x7f,0x00,0x00,0x00,0x40,0x00,0x02,0xc0,0xff,0x0f,0xc0,0x00,0x07,
0xc0,0x00,0x03,0xc0,0xff,0x07,0xc0,0xff,0x07,0xc0,0x00,0x07,0xc0,0x00,0x07,0xc0,
0xff,0x07,0xc0,0x00,0x07,0x40,0x00,0x00,   

/*------------------------------------------------------------------------------

;  源文件 / 文字 :  中
;  宽×高（像素）: 24×24
;  字模格式/大小 : 单色点阵液晶字模，横向取模，字节倒序/72字节

------------------------------------------------------------------------------*/
/*--  宽度x高度=24x24  --*/
0x00,0x04,0x00,0x00,0x3c,0x00,0x00,0x1c,0x00,0x00,0x1c,0x00,0x00,0x1c,0x00,0x03,
0x1c,0x60,0xff,0xff,0xff,0x07,0x1c,0x60,0x07,0x1c,0x60,0x07,0x1c,0x60,0x07,0x1c,
0x60,0x07,0x1c,0x60,0x07,0x1c,0x70,0xff,0xff,0x7f,0x07,0x1c,0x60,0x03,0x1c,0x20,
0x00,0x1c,0x00,0x00,0x1c,0x00,0x00,0x1c,0x00,0x00,0x1c,0x00,0x00,0x1c,0x00,0x00,
0x1c,0x00,0x00,0x1c,0x00,0x00,0x0c,0x00,

/*------------------------------------------------------------------------------

;  源文件 / 文字 : 科
;  宽×高（像素）: 24×24
;  字模格式/大小 : 单色点阵液晶字模，横向取模，字节倒序/72字节

------------------------------------------------------------------------------*/
0x00,0x00,0x06,0x00,0x03,0x1c,0xe0,0x07,0x0c,0xfe,0x00,0x0c,0xc0,0x30,0x0c,0xc0,
0x60,0x0c,0xc0,0xc0,0x0c,0xc0,0x44,0x0c,0xff,0x0f,0x0c,0xe0,0x10,0x0c,0xe0,0x30,
0x0c,0xe0,0x61,0x0c,0xf0,0x63,0x2c,0xf8,0x06,0x6c,0xd8,0x04,0xfe,0xcc,0xf0,0x0f,
0xc6,0x1e,0x0c,0xc2,0x00,0x0c,0xc1,0x00,0x0c,0xc0,0x00,0x0c,0xc0,0x00,0x0c,0xc0,
0x00,0x0c,0xc0,0x00,0x0c,0x00,0x00,0x04,
	
/*------------------------------------------------------------------------------

;  源文件 / 文字 : 技
;  宽×高（像素）: 24×24
;  字模格式/大小 : 单色点阵液晶字模，横向取模，字节倒序/72字节

------------------------------------------------------------------------------*/
0x20,0x80,0x00,0xe0,0x80,0x03,0x60,0x80,0x01,0x60,0x80,0x01,0x60,0x80,0x01,0x60,
0x80,0x21,0xff,0xff,0x7f,0x60,0x80,0x01,0x60,0x80,0x01,0x60,0x80,0x01,0x60,0xd7,
0x11,0xe0,0xf9,0x3f,0x78,0x10,0x18,0x7f,0x30,0x0c,0x66,0x20,0x0c,0x60,0x60,0x06,
0x60,0x60,0x07,0x60,0xc0,0x03,0x60,0x80,0x01,0x60,0xc0,0x03,0x62,0x70,0x0f,0x7e,
0x3c,0xfc,0x38,0x0f,0x78,0x90,0x01,0x20,
};	  

const unsigned char code hz16[]= {

/*------------------------------------------------------------------------------
/*--  文字:  专  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x80,0x00,0x80,0x00,0xFC,0x1F,0x40,0x00,0x40,0x00,0xFF,0x7F,0x20,0x00,0x10,0x04,
0xF0,0x0F,0x00,0x04,0x00,0x02,0x40,0x01,0x80,0x00,0x00,0x01,0x00,0x02,0x00,0x00,


/*------------------------------------------------------------------------------

/*--  文字:  业  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x20,0x02,0x20,0x02,0x20,0x02,0x20,0x22,0x22,0x62,0x24,0x32,0x24,0x12,0x28,0x0A,
0x38,0x0A,0x28,0x06,0x20,0x02,0x20,0x02,0x20,0x22,0xFF,0x7F,0x00,0x00,0x00,0x00,


/*------------------------------------------------------------------------------

/*--  文字:  技  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x08,0x04,0x08,0x04,0x08,0x04,0xBF,0x7F,0x08,0x04,0x28,0x04,0x98,0x3F,0x8C,0x10,
0x0B,0x11,0x08,0x09,0x08,0x06,0x08,0x06,0x08,0x09,0x88,0x70,0x6A,0x20,0x04,0x00,

/*--  文字:  术  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x80,0x00,0x80,0x04,0x80,0x08,0x80,0x00,0xFF,0x7F,0x80,0x00,0xC0,0x01,0xA0,0x02,
0xA0,0x04,0x90,0x08,0x88,0x18,0x84,0x70,0x83,0x20,0x80,0x00,0x80,0x00,0x00,0x00,

/*--  文字:  论  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x02,0x02,0x04,0x02,0x0C,0x05,0x04,0x09,0x80,0x10,0x40,0x60,0xA7,0x20,0x84,0x08,
0x84,0x1C,0x84,0x03,0x84,0x00,0xA4,0x00,0x94,0x20,0x8C,0x20,0x04,0x3F,0x00,0x00,

/*--  文字:  坛  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x88,0x3F,0x08,0x00,0x08,0x00,0x08,0x00,0x3F,0x00,0xC8,0x7F,0x08,0x02,
0x08,0x06,0x08,0x01,0x38,0x11,0x8C,0x20,0x43,0x7E,0xE0,0x63,0x40,0x20,0x00,0x00,

  

};


const unsigned char code hz12[] = {

/*------------------------------------------------------------------------------

/*--  文字:  带  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x12  --*/
0x28,0x01,0xFF,0x07,0x28,0x01,0x28,0x01,0xFF,0x07,0x21,0x04,0xFC,0x01,0x24,0x01,
0x24,0x01,0xA4,0x01,0x20,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
/*--  文字:  您  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x12  --*/
0x24,0x00,0xE4,0x07,0x12,0x02,0xAB,0x01,0x92,0x02,0x8A,0x04,0xE2,0x00,0x10,0x00,
0x2A,0x03,0x0A,0x05,0xF9,0x01,0x00,0x00,


/*------------------------------------------------------------------------------
/*--  文字:  进  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x12  --*/
0x22,0x01,0x24,0x01,0xF8,0x07,0x20,0x01,0x23,0x01,0xFA,0x07,0x22,0x01,0x22,0x01,
0x12,0x01,0x0D,0x01,0xF9,0x07,0x00,0x00,

	
/*------------------------------------------------------------------------------

/*--  文字:  入  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x12  --*/
0x18,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x50,0x00,0x50,0x00,0x88,0x00,0x88,0x00,
0x04,0x01,0x02,0x02,0x01,0x04,0x00,0x00,

/*------------------------------------------------------------------------------
/*--  文字:  单  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x12  --*/
0x88,0x00,0x50,0x00,0xFC,0x03,0x24,0x02,0xFC,0x03,0x24,0x02,0xFC,0x03,0x20,0x00,
0xFF,0x07,0x20,0x00,0x20,0x00,0x00,0x00,


/*------------------------------------------------------------------------------
/*--  文字:  片  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x12  --*/
0x44,0x00,0x44,0x00,0x44,0x00,0xFC,0x07,0x04,0x00,0x04,0x00,0xFC,0x00,0x84,0x00,
0x84,0x00,0x82,0x00,0x81,0x00,0x00,0x00,


/*------------------------------------------------------------------------------
/*--  文字:  机  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x12  --*/
0x04,0x01,0xE4,0x03,0x3F,0x01,0x24,0x01,0x24,0x01,0x2E,0x01,0x36,0x01,0x25,0x01,
0x25,0x05,0x14,0x05,0x0C,0x07,0x00,0x00,


/*------------------------------------------------------------------------------
/*--  文字:  世  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x12  --*/
0x10,0x01,0x12,0x01,0x12,0x01,0xFF,0x07,0x12,0x01,0x12,0x01,0x12,0x01,0xF2,0x01,
0x12,0x01,0x02,0x00,0xFE,0x07,0x00,0x00,



/*------------------------------------------------------------------------------
/*--  文字:  界  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=16x12  --*/
0xFC,0x03,0x24,0x02,0xFC,0x03,0x24,0x02,0xFC,0x03,0x88,0x00,0x94,0x01,0x93,0x06,
0x90,0x00,0x88,0x00,0x86,0x00,0x00,0x00,

};



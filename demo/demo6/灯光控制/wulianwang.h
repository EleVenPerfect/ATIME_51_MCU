#ifndef _WULIANWANG_H_
#define _WULIANWANG_H_

sbit wlw_gnd = P1^0;
sbit wlw1 = P1^3;
sbit wlw2 = P1^2;
sbit wlw3 = P1^1;

sbit key1 =	P0^6;
sbit key2 = P0^5;
sbit key3 = P0^4;
sbit key4 = P0^3;
  
bit key1_last = 0;
bit key2_last = 0;
bit key3_last = 0;

bit wlw1_last = 0;
bit wlw2_last = 0;
bit wlw3_last = 0;

void key_init()
{
		key1_last = key1;
		key2_last = key2;
		key3_last = key3;
		printf("KEY Inint OK!\n");
}

void wlw_init()
{		
		wlw_gnd = 0;
		wlw1_last = wlw1;
		wlw2_last = wlw2;
		wlw3_last = wlw3;
		printf("WLW Inint OK!\n");
}

void get_wlw_data()
{		
		wlw_gnd = 0;
		wlw1 = 1;
		wlw2 = 1;
		wlw3 = 1;
		if(wlw1==0)
				printf("Wlw1 is ON\n");
		else
				printf("Wlw1 is OFF\n");
		if(wlw2==0)
				printf("Wlw2 is ON\n");
		else
				printf("Wlw2 is OFF\n");
		if(wlw3==0)
				printf("Wlw3 is ON\n");
		else
				printf("Wlw3 is OFF\n");
}

void get_key_data()
{
		if(key1==0)
				printf("Key1 is ON\n");
		else
				printf("Key1 is OFF\n");
		if(key2==0)
				printf("Key2 is ON\n");
		else
				printf("Key2 is OFF\n");
		if(key3==0)
				printf("Key3 is ON\n");
		else
				printf("Key3 is OFF\n");
		if(key4==0)
				printf("Key4 is ON\n");
		else
				printf("Key4 is OFF\n");
}

#endif
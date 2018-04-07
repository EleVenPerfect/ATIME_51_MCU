#ifndef _KONGZHI_C_
#define _KONGZHI_C_


void led_body20cm()
{
		if(S<=20.0)
		{
				if(gq_int_status <200)
				{
						led1(on);
						led2(on);
						led3(on);
				}
				else
				if(gq_int_status <2000)
				{
						led1(on);
						led2(on);
						led3(off);
				}
				else
				if(gq_int_status <8000)
				{
						led1(off);
						led2(on);
						led3(off);
				}
		}
		else
		{
				led1(off);
				led2(off);
				led3(off);
		}
}
void led_body10cm()
{
		if(S<=10.0)
		{
				if(gq_int_status <500)
				{
						led1(on);
						led2(on);
						led3(on);
				}
				else
				if(gq_int_status <5000)
				{
						led1(on);
						led2(on);
						led3(off);
				}
				else
				if(gq_int_status <10000)
				{
						led1(off);
						led2(on);
						led3(off);
				}
		}
}

void led_kongzhi()
{
		if(key1!=key1_last)
		{
				led1(turn);
				key1_last = key1;
		}
		if(key2!=key2_last)
		{
				led2(turn);
				key2_last = key2;
		}
		if(key3!=key3_last)
		{
				led3(turn);
				key3_last = key3;
		}
		
		if(wlw1!=wlw1_last)
		{
				led1(turn);
				wlw1_last = wlw1;
		}
		if(wlw2!=wlw2_last)
		{
				led2(turn);
				wlw2_last = wlw2;
		}
		if(wlw3!=wlw3_last)
		{
				led3(turn);
				wlw3_last = wlw3;
		}
}
#endif

#include <at89x52.h>

//計時時間 = 50000 * 1us = 50ms
#define	CNT_M1	500
#define	TH_M1	(65536-CNT_M1)/256
#define	TL_M1	(65536-CNT_M1)%256

#define LOOP_M1	20
int TCnt=0;
unsigned int i = 0;
unsigned int num_display =  2;

unsigned char __code num_array[] ={
        0x1e, 0x1d,
//    0x1e,0x4e, 0x6d, 0x7e,
//    0x1d, 0x2e, 0x2d, 0x8e,

};


void myTimer0() __interrupt(1)
{
	//重新設定計數值
	TH0 = TH_M1;
	TL0 = TL_M1;

	//中斷程式碼
	if (++TCnt == LOOP_M1)
	{
		TCnt = 0;

     if(i < num_display){
            P1 = num_array[i];
            ++i;
        }else{
            i = 0;
        }


//        P0 = ~P0;
	}

}

void main()
{
	//啟動Timer0
	IE = 0x82;

	//GATE  = 0 -> 當TR0為1，則可正式啟動
	//C/T   = 0 -> 使用內部12MHz振盪(計時模式)
	//M1,M0 = 01-> 使用Mode1，16位元振盪器(0~65535)
	TMOD = 0x01;

	//設定計數值
	TH0 = TH_M1;
	TL0 = TL_M1;

	//啟動Timer0，正式計時開始!!
	TR0 = 1;

    P0 = 0x81;
	//主程式碼
	while(1)
	{

	}
}

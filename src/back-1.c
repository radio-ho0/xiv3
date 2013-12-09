
#include <at89x52.h>

//計時時間 = 50000 * 1us = 50ms
#define	CNT_M1	50000
#define	TH_M1	(65536-CNT_M1)/256
#define	TL_M1	(65536-CNT_M1)%256

//如果想要計時的時間超過 65536 * 1us = 65.536ms (約65ms)
//則使用(中黛OOP_M1次，才執行中斷程式碼)，以增加計時時間
//計時時間 = LOOP_M1 * CNT_M1 * 1us = 1s
#define LOOP_M1	20
int TCnt=0;

void myTimer0() __interrupt(1)
{
	//重新設定計數值
	TH0 = TH_M1;
	TL0 = TL_M1;

	//中斷程式碼
	if (++TCnt == LOOP_M1)
	{
		TCnt = 0;
        P0 = ~P0;
		//計時時間 = LOOP_M1 * CNT_M1 * 1us = 1s
		//這的程式碼要 1秒 才執行到一次
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

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>

#define K (DWORD)

int main()
{
	system("title 紅蓮華");
	system("mode con cols=30 lines=6");
	DWORD p=60*1000/120; 	//红莲华的BPM是135，所以每一拍的时间就是60/135秒
	int flag=1;
	char r;		//结束时输入r或R重新开始
	int f_g1[]={0,784,880,987,1046,1174,1318,1480};
	int f[]={0,392,440,493,523,587,659,740};
	int f_d1[]={0,196,220,247,261,293,329,370};		//f数组表示频率，d1低八度，g1高八度
	int f_g2[]={0,1568};
	while(flag)
	{
		system("cls");
		printf("\n\n\tC酱演唱中...");
		Beep(f[1],K p*3/4);
		Beep(f_d1[7],K p*3/4);
		Beep(f[1],K p*3/2);
		Beep(0,K p);
		Beep(f[1],K p*3/4);
		Beep(f_d1[7], (DWORD)p*3/4);
		Beep(f[1], (DWORD)p*3/2);
		Beep(0, (DWORD)p/2);
		Beep(f_d1[1], (DWORD)p/2);
		Beep(f[1], (DWORD)p*3/4);
		Beep(f_d1[7], (DWORD)p*3/4);
		Beep(f_d1[6], (DWORD)p*2);
		Beep(f_d1[5], (DWORD)p*5/4);
		Beep(0, (DWORD)p*7/4);
		Beep(f[3], (DWORD)p);
		Beep(f[5], (DWORD)p/2);
		Beep(f[6], (DWORD)p*3/2);
		Beep(0, (DWORD)p);
		Beep(f[6], (DWORD)p);
		Beep(f_g1[1], (DWORD)p/2);
		Beep(f_g1[2], (DWORD)p*2);
		Beep(0, (DWORD)p/2);
		Beep(f_g1[1], (DWORD)p);
		Beep(f_g1[2], (DWORD)p/2);
		Beep(f_g1[3], (DWORD)p*2);
		printf("\n\t\t（假装有伴奏）");
		Beep(0, (DWORD)p*14);
		system("cls");
		printf("\n\n\tC酱演唱中...");
		Beep(f[6], (DWORD)p*3/4);
		Beep(f_g1[1], (DWORD)p*3/4);
		Beep(f[7], (DWORD)p/2);
		Beep(f[5], (DWORD)p);
		Beep(f[6], (DWORD)p*3/4);
		Beep(f[5], (DWORD)p*5/4);
		Beep(0, (DWORD)p);
		Beep(f[2], (DWORD)p/2);
		Beep(f[1], (DWORD)p/4);
		Beep(f[1], (DWORD)p/4);
		Beep(f[2], (DWORD)p/2);
		Beep(f[4], (DWORD)p/2);
		Beep(f[3], (DWORD)p/2);
		Beep(f_d1[6], (DWORD)p*3/2);
		Beep(0, (DWORD)p*5/2);
		Beep(f_d1[6], (DWORD)p/2);
		Beep(f[1], (DWORD)p/4);
		Beep(f[2], (DWORD)p/2);
		Beep(f[3], (DWORD)p*3/4);
		Beep(f[2], (DWORD)p/2);
		Beep(f[3], (DWORD)p/2);
		Beep(f[5], (DWORD)p/2);
		Beep(f[6], (DWORD)p*3/4);
		Beep(f_g1[1], (DWORD)p*3/4);
		Beep(f[7], (DWORD)p);
		Beep(f[5], (DWORD)p/2);
		Beep(f[6], (DWORD)p*3/4);
		Beep(f[5], (DWORD)p*5/4);
		Beep(0, (DWORD)p);
		Beep(f[5], (DWORD)p/4);
		Beep(f[5], (DWORD)p/4);
		Beep(f_g1[3], (DWORD)p/4);
		Beep(f_g1[2], (DWORD)p/4);
		Beep(f_g1[3], (DWORD)p/4);
		Beep(f_g1[2], (DWORD)p/4);
		Beep(f_g1[3], (DWORD)p/2);
		Beep(f_g1[4], (DWORD)p/4);
		Beep(f_g1[3], (DWORD)p/2);
		Beep(f_g1[1], (DWORD)p*3/4);
		Beep(0, (DWORD)p*5/2);
		Beep(f_g1[1], (DWORD)p/2);
		Beep(f[7], (DWORD)p*3/4);
		Beep(f[7], (DWORD)p*3/4);
		Beep(f_g1[1], (DWORD)p/2);
		Beep(f_g1[2], (DWORD)p);
		Beep(0, (DWORD)p/2);
		Beep(f_g1[1], (DWORD)p/2);
		Beep(f_g1[2], (DWORD)p*3/4);
		Beep(f_g1[1], (DWORD)p*3/4);
		Beep(f[6], (DWORD)p*3/4);
		Beep(f_g1[1], (DWORD)p*3/4);
		Beep(f_g1[3], (DWORD)p*3/4);
		Beep(f_g1[2], (DWORD)p*3/4);
		Beep(0, (DWORD)p*3);
		Beep(f_g1[1], (DWORD)p/2);
		Beep(f_g1[2], (DWORD)p*3/4);
		Beep(f_g1[1], (DWORD)p*3/4);
		Beep(f[6], (DWORD)p);
		Beep(f_g1[1], (DWORD)p/2);
		Beep(f_g1[5], (DWORD)p*3/2);
		Beep(0, (DWORD)p*3);
		Beep(f_g1[1], (DWORD)p/2);	//23
		Beep(f_g1[2], (DWORD)p*3/4);
		Beep(f_g1[1], (DWORD)p*3/4);
		Beep(f[6], (DWORD)p);
		Beep(f_g1[1], (DWORD)p/2);
		Beep(f_g1[3], (DWORD)p*3/4);
		Beep(f_g1[2], (DWORD)p*3/4);
		Beep(0, (DWORD)p/2);
		Beep(f_g1[2], (DWORD)p/2);	//24
		Beep(f_g1[3], (DWORD)p/2);
		Beep(f_g1[2], (DWORD)p/2);
		Beep(f_g1[3], (DWORD)p/2);
		Beep(f_g1[5], (DWORD)p/2);
		Beep(f_g1[3], (DWORD)p/2);
		Beep(f_g1[2], (DWORD)p*3/4);	//25
		Beep(f_g1[1], (DWORD)p*3/4);
		Beep(0, (DWORD)p*2);
		Beep(f_g1[1], (DWORD)p/2);
		Beep(f[7], (DWORD)p*3/4);	//26
		Beep(f[7], (DWORD)p*3/4);
		Beep(f_g1[1], (DWORD)p/2);
		Beep(f_g1[2], (DWORD)p);
		Beep(0, (DWORD)p);
		Beep(f_g1[1], (DWORD)p*3/4);	//27
		Beep(f[7], (DWORD)p/2);
		Beep(f_g1[1], (DWORD)p*3/2);
		Beep(0, (DWORD)p);
		Beep(f_g1[1], (DWORD)p*3/4);
		Beep(f[7], (DWORD)p/2);
		Beep(f_g1[1], (DWORD)p*3/2);
		Beep(0, (DWORD)p/2);
		Beep(f[5], (DWORD)p/2);
		Beep(f_g1[1], (DWORD)p*3/4);
		Beep(f[7], (DWORD)p*3/4);
		Beep(f[6], (DWORD)p*2);
		Beep(f[5], (DWORD)p*5/2);
		Beep(0, (DWORD)p/2);
		Beep(f[3], (DWORD)p);
		Beep(f[5], (DWORD)p/2);
		Beep(f[6], (DWORD)p*2);	//31
		Beep(0, (DWORD)p/2);
		Beep(f[6], (DWORD)p);
		Beep(f_g1[1], (DWORD)p/2);
		Beep(f_g1[2], (DWORD)p*2);
		Beep(0, (DWORD)p/2);
		Beep(f_g1[1], (DWORD)p);
		Beep(f_g1[2], (DWORD)p/2);		//33
		Beep(f_g1[3], (DWORD)p*7/2);
		Beep(0, (DWORD)p);	//34
		Beep(f[5], (DWORD)p);
		Beep(f[5], (DWORD)p);
		Beep(f_g1[3], (DWORD)p);
		Beep(f_g1[2], (DWORD)p/2);
		Beep(f_g1[3], (DWORD)p/2);
		Beep(f_g1[5], (DWORD)p/2);
		Beep(f_g1[3], (DWORD)p/2);
		Beep(f_g1[2], (DWORD)p/2);
		Beep(f_g1[3], (DWORD)p/4);
		Beep(f_g1[3], (DWORD)p/4);
		Beep(0, (DWORD)p/2);
		Beep(f_g1[1], (DWORD)p/2);
		Beep(f_g1[2],p/2);
		Beep(f_g1[3],p/2);
		Beep(f_g1[5],p/2);
		Beep(f_g1[3],p/2);
		Beep(f_g1[2],p/2);
		Beep(f_g1[3],p/4);
		Beep(f_g1[3],p/4);
		Beep(0,p/2);
		Beep(f_d1[5],p/2);
		Beep(f_d1[5],p/2);
		Beep(f[1],p/4);
		Beep(f[1],p/4);
		Beep(0,p/2);
		Beep(f_d1[5],p/2);
		Beep(f_d1[5],p/2);
		Beep(f[1],p/2);
		Beep(f[2],p/2);
		Beep(f[1],p/2);
		Beep(f[5],p);		//38
		Beep(f[4],p);
		Beep(f[3],p*3/4);
		Beep(f[2],p*3/4);
		Beep(f[1],p/2);
		Beep(f[1],p);		//39
		Beep(0,p/2);
		Beep(f_g1[1],p);
		Beep(f_g1[2],p/2);
		Beep(f_g1[3],p/2);
		Beep(f_g1[2],p/2);
		Beep(0,p);		//40
		Beep(f[5],p/2);
		Beep(f_g1[2],p);
		Beep(f_g1[3],p/2);
		Beep(f_g1[5],p/2);
		Beep(f_g1[3],p*7/3);
		Beep(0,p*2);			//41
		Beep(f[5],p);
		Beep(f[5],p);
		Beep(f_g1[3],p);
		Beep(f_g1[2],p/2);
		Beep(f_g1[3],p/2);
		Beep(f_g1[5],p/2);
		Beep(f_g1[3],p/2);
		Beep(f_g1[2],p/2);
		Beep(f_g1[3],p/4);
		Beep(f_g1[3],p/4);
		Beep(0,p/2);
		Beep(f_g1[1],p/4);
		Beep(f_g1[1],p/4);
		Beep(f_g1[2],p/2);
		Beep(f_g1[3],p/2);
		Beep(f_g1[5],p/2);
		Beep(f_g1[3],p/2);
		Beep(f_g1[2],p/2);
		Beep(f_g1[3],p/4);
		Beep(f_g1[1],p/4);
		Beep(0,p/2);
		Beep(f_g1[1],p/2);
		Beep(f_g1[1],p);
		Beep(f_g1[2],p/2);
		Beep(f_g1[3],p);
		Beep(f_g1[3],p/2);
		Beep(f_g2[1],p/2);
		Beep(f_g1[7],p*3/2);
		Beep(f_g1[5],p);
		Beep(f_g1[3],p*3/4);
		Beep(f_g1[2],p/4);
		Beep(f_g1[2],p/2);
		Beep(f_g1[1],p/2);
		Beep(f_g1[1],p);
		Beep(0,p/2);
		Beep(f_g1[1],p);
		Beep(f_g1[2],p/2);
		Beep(f_g1[3],p/2);
		Beep(f_g1[2],p/2);
		Beep(0,p*3/2);
		Beep(f_g1[2],p/2);
		Beep(f_g1[2],p);
		Beep(f_g1[2],p);
		Beep(f_g1[3],p*3);
		system("cls");
		printf("\n\n\t按R键再来一次");
		fflush(stdin);
		r=_getch();
		if(r=='r' || r=='R')
			flag=1;
		else
			flag=0; 
	}
	return 0;
}

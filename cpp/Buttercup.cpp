
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
int main()
{
	system("title Buttercup");
	system("mode con cols=30 lines=5");
	int b=500,flag=1;
	int d[]={0,293,329,370,392,440,493};
	char a;
	while(flag)
	{
		system("cls");
		printf("\n\n\tC酱演唱中...");
		Beep(d[1],b);
		Sleep(b);
		Beep(d[1],b);
		Beep(d[2],b);
		Beep(d[4],b);
		Sleep(b/2);
		Beep(d[5],b/2);
		Beep(d[6],b+b/2);
		Beep(d[5],b/2);
		Beep(d[5],b/2);
		Beep(d[4],b/2);
		Beep(d[3],b/2);
		Beep(d[4],b/2);
		Beep(d[3],b/2);
		Sleep(b/2);
		Beep(d[4],b/2);
		Sleep(b/2);
		Beep(d[3],b/2);
		Sleep(b+b/2);
		Beep(d[3],b/2);
		Beep(d[2],b/2);
		Beep(d[1],b/2);
		Beep(d[2],b/2);
		Beep(d[3],b/2);
		Beep(d[2],b/2);
		Beep(d[1],b/2);
		Sleep(2*b+b/2);
		Beep(d[4],b);
		Sleep(b/2);
		Beep(d[5],b/2);
		Beep(d[6],b+b/2);
		Beep(d[5],b/2);
		Beep(d[5],b/2);
		Beep(d[4],b/2);
		Beep(d[3],b/2);
		Beep(d[4],b/2);
		Beep(d[3],b/2);
		Sleep(b/2);
		Beep(d[4],b/2);
		Sleep(b/2);
		Beep(d[3],b/2);
		Sleep(b+b/2);
		Beep(d[3],b/2);
		Beep(d[2],b/2);
		Beep(d[1],b/2);
		Beep(d[2],b/2);
		Beep(d[3],b/2);
		system("cls");
		printf("\n\n\tR键重新开始");
		a=_getch();
		if(a=='R' || a=='r')
			flag=1;
		else
			flag=0;
	}
	return 0;
}

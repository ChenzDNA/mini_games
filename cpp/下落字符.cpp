#include<stdio.h>
#include<windows.h>
void goto_xy(int x, int y)	//定位光标位置到指定坐标
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//获取标准输出句柄 
	COORD pos={x,y};			//坐标结构体 
	SetConsoleCursorPosition(hOut,pos);	//定位光标位置 
}
void exchange(char *a,char *b)
{
	char t;
	t=*a,*a=*b,*b=t;
}
int main()
{
	system("color 02");	//全局黑底绿字 
	system("mode con cols=40 lines=19");
	int b[40]={0};
	char a[20][40];
	int i,j,k,s;
	int std1,std2,std3;
	for(i=0;i<20;i++)
		for(j=0;j<40;j++)
			a[i][j]=' ';	//a初始化 
	while(1)
	{
	//	system("cls");
		goto_xy(0,0);
		for(i=rand()%40;b[i]!=0;i=rand()%40);	//确保随机出来的b[i]为0 
		b[i]=rand()%4+4;		//给b[i]随机赋值，范围是4~7，表示这个位置的字符条长度 
		for(j=18;j>-1;j--)
			for(k=0;k<40;k++)
				if(a[j][k]!=' ')
					exchange(&a[j][k],&a[j+1][k]);		//用交换方式下落 
		for(j=0;j<40;j++)
			if(b[j])			//根据b[]给a[][]的第一行赋值 
			{
				s=rand()%3;	//随机的s=0就是数字，1大写字母，2小写字母 
				if(s==0)
					a[0][j]=rand()%10+48;
				else if(s==1)
					a[0][j]=rand()%26+65;
				else
					a[0][j]=rand()%26+97;	//随机赋值大小写字母或数字 
			}
		for(j=0;j<40;j++)
			a[19][j]=' ';		//最后一行应该是空的，不然就没得换 
		for(j=0;j<19;j++)			//打印 
		{
			for(k=0;k<40;k++)
				putchar(a[j][k]);
			putchar(10);
		}
		for(j=0;j<40;j++)
			if(b[j])
				b[j]--;		//b[]值减少1，限制下落字符长度 
		Sleep(50);
	}
	return 0;
}

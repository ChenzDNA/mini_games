#include<stdio.h>
#include<windows.h>
#include<conio.h>
#define LIM_X 50
#define LIM_Y 25
void goto_xy(int x, int y)	//��λ���λ�õ�ָ������
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//��ȡ��׼������ 
	COORD pos={x,y};			//����ṹ�� 
	SetConsoleCursorPosition(hOut,pos);	//��λ���λ�� 
}
int limit_x(int n)
{
	if(n==LIM_X)
		return 0;
	else if(n==-1)
		return LIM_X-1;
	else
		return n;
}
int limit_y(int n)
{
	if(n==LIM_Y)
		return 0;
	else if(n==-1)
		return LIM_Y-1;
	else
		return n;
}
int main()
{
	int len=6;
	int food=1;
	int food_x,food_y;
	int a[50][100]={0};
	int life=1;
	char input='d';
	char direction='d';
	int x=0,y=0;
	int i,j;
	int right=1,left=0;
	int score=0;
	system("mode con cols=50 lines=26");
	while(life)
	{
		if(food)
		{
			do{
				food_x=rand()%LIM_X;
				food_y=rand()%LIM_Y;
			}while(a[food_y][food_x]>1);
			a[food_y][food_x]=-1;
			food=0;
			score+=1;
			if(len==LIM_X*LIM_Y)
				break;
		}
		if(right==1)
		{
			direction='d';
			right=0;
		}
		else if(left==1)
		{
			direction='a';
			left=0;
		}
	/*	else switch(x)
		{
			case 0:
				right=1;
				direction='s';
				break;
			case 99:
				left=1;
				direction='s';
				break;
		}	*/
		if(kbhit())
		{
			input=getch();
			switch(input)
			{
				case 'w':
					if(direction=='s')
						break;
					direction='w';
					break;
				case 'a':
					if(direction=='d')
						break;
					direction='a';
					break;
				case 's':
					if(direction=='w')
						break;
					direction='s';
					break;
				case 'd':
					if(direction=='a')
						break;
					direction='d';
					break;
			}
		}
		switch(direction)
		{
			case 'w':
			//	y=(y-1)%LIM_Y;
				y=limit_y(y-1);
				if(a[y][x]==-1)
				{
					len+=1;
					food=1;
				}
				a[y][x]=len;
				break;
			case 'a':
			//	x=(x-1)%LIM_X;
				x=limit_x(x-1);
				if(a[y][x]==-1)
				{
					len+=1;
					food=1;
				}
				a[y][x]=len;
				break;
			case 's':
			//	y=(y+1)%LIM_Y;
				y=limit_y(y+1);
				if(a[y][x]==-1)
				{
					len+=1;
					food=1;
				}
				a[y][x]=len;
				break;
			case 'd':
			//	x=(x+1)%LIM_X;
				x=limit_x(x+1);
				if(a[y][x]==-1)
				{
					len+=1;
					food=1;
				}
				a[y][x]=len;
				break;
		}
		for(i=0;i<LIM_Y;i++)
			for(j=0;j<LIM_X;j++)
				if(a[i][j]>0)
					a[i][j]-=1;
		for(i=0;i<LIM_Y;i++)
			for(j=0;j<LIM_X;j++)
				if(a[i][j]>0)
					printf("*");
				else if(a[i][j]<0)
					printf("0");
				else
					printf(" ");
					printf("x=%d  \ty=%d  \t\t������%d",x,y,score);
		goto_xy(0,0);
	}
	goto_xy(0,0);
	if(life)
		printf("��ͼ����");
	return 0;
}

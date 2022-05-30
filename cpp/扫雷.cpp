#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>

#define L 20

void goto_xy(int x, int y)	//定位光标位置到指定坐标
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//获取标准输出句柄 
	COORD pos={x,y};			//坐标结构体 
	SetConsoleCursorPosition(hOut,pos);	//定位光标位置 
}

void wa(int y,int x,char a[L][L],int b[L][L],int *ming,char *temp,int *shan)		//挖开当前选定的格子
{
	int i;
	if(a[y][x]=='F' || *temp=='F')		//有旗子就不挖开
		return;
	if(b[y][x]==-1)			//是雷就生命值清零
	{
		*ming=0;
		return;
	}
	else if(b[y][x]>0)		//是数字就只挖开这一格 
	{
		a[y][x]=48+b[y][x];
		*shan=1;
		return;
	}
	else if(b[y][x]==0 || a[y][x]=='#')		//是空地就挖开周围的格子
	{
		a[y][x]=' ';
		b[y][x]=-2;
		*temp=a[y][x];
		if(y!=19 && b[y+1][x]!=-1)
			wa(y+1,x,a,b,ming,temp,shan);
		if(x!=19 && b[y][x+1]!=-1)
			wa(y,x+1,a,b,ming,temp,shan);
		if(y!=19 && x!=19 && b[y+1][x+1]!=-1)
			wa(y+1,x+1,a,b,ming,temp,shan);
		if(y!=0 && x!=0 && b[y-1][x-1]!=-1)
			wa(y-1,x-1,a,b,ming,temp,shan);
		if(y!=0 && b[y-1][x]!=-1)
			wa(y-1,x,a,b,ming,temp,shan);
		if(x!=0 && b[y][x-1]!=-1)
			wa(y,x-1,a,b,ming,temp,shan);
		if(y!=0 && x!=19 && b[y-1][x+1]!=-1)
			wa(y-1,x+1,a,b,ming,temp,shan);
		if(y!=19 && x!=0 && b[y+1][x-1]!=-1)
			wa(y+1,x-1,a,b,ming,temp,shan);
	}
}

void biao(int y,int x,char a[L][L],int *flag,int *n,char *temp)		//标记（插旗）
{
	if(!*n && (a[y][x]!='F' || *temp!='F'))		//旗插完了就没旗插了（保证旗数=雷数）
		return;
	if(a[y][x]=='F' || *temp=='F')		//上面有旗就回收旗
	{
		a[y][x]='#';
		*temp='#';
		*flag-=1;
		*n+=1;
		return;
	}
	a[y][x]='F';		//插旗
	*flag+=1;
	*n-=1;
	*temp='F';
}

int xianzhi(int x)		//限制光标运动范围
{
	if(x==L)
		return 0;
	else if(x==-1)
		return 19;
	return x;
}

void dilei(int n,int b[L][L])		//埋地雷
{
	int i,j,x,y;
	while(n)	//随机生成地雷
	{
		x=rand()%L;
		y=rand()%L;
		if(b[y][x]==0)
		{
			b[y][x]=-1;
			n-=1;
		}	
	}
	for(i=0;i<L;i++)	//遍历地雷周围的格子，每格b值+1
		for(j=0;j<L;j++)
		{
			if(b[i][j]==-1)
			{
				if(i!=19 && b[i+1][j]!=-1)
					b[i+1][j]+=1;
				if(j!=19 && b[i][j+1]!=-1)
					b[i][j+1]+=1;
				if(i!=19 && j!=19 && b[i+1][j+1]!=-1)
					b[i+1][j+1]+=1;
				if(i!=0 && j!=0 && b[i-1][j-1]!=-1)
					b[i-1][j-1]+=1;
				if(i!=0 && b[i-1][j]!=-1)
					b[i-1][j]+=1;
				if(j!=0 && b[i][j-1]!=-1)
					b[i][j-1]+=1;
				if(i!=0 && j!=19 && b[i-1][j+1]!=-1)
					b[i-1][j+1]+=1;
				if(i!=19 && j!=0 && b[i+1][j-1]!=-1)
					b[i+1][j-1]+=1;
			}
		}
	
}

void ditu(int *y,int *x,char a[L][L],int *flag,int *n)			 //打印地图
{
	int i,j;
	for(i=0;i<23;i++)	//打印地图
		{
			if(i==0)
				printf("  X  0   2   4   6   8  10  12  14  16  18\n");
			else if(i==1)
				printf(" Y     1   3   5   7   9  11  13  15  17  19\n");
			else if(i==2)
				printf("\n");
			else
			{	
				printf("%2d  ",i-3);
				for(j=0;j<L;j++)
					printf(" %c",a[i-3][j]);
				printf(" ");
			}
		}
		printf("\n\n\t已标记数:%d\t总雷数:%d\n\n\t光标坐标 x:%d\ty:%d",*flag,*n,*x,*y);
	return;
}

void danandu(char nandu)			//打印难度
{
	if(nandu=='1')
		printf("\t\t嬲坨\n");
	else if(nandu=='2')
		printf("\t\t还可以咯\n");
	else if(nandu=='3')
		printf("\t\t蛮勇\n");
	else
		printf("\t\t大哥nb\n");
}

int main()
{
	system("title 阿征扫雷");
	system("mode con cols=45 lines=32");
	char r='r';
	while(r=='r' || r=='R')
	{
		char a[L][L],dong,temp,nandu='0';
		int b[L][L]={0},i,j,ming=1,y=0,x=0,flag=0,shan=1,n=0,dan1=0,dan2=0,dan3=0,zdan=0,check=0;
		system("cls");
		printf("\n\n    WASD控制光标移动\n    E键挖开光标所在的格子\n    F键标记有雷\n\n    选择难度：\n\n\t1.嬲坨\n\n\t2.还可以咯\n\n\t3.蛮勇\n\n\t4.大哥nb\n\n\t(输入数字1~4)\n");
		while(nandu<49 || nandu>52)		//输入难度（数字1~4）
			nandu=getch();
		if(nandu=='1')		//根据难度调整雷数
			n=10;
		else if(nandu=='2')
			n=20;
		else if(nandu=='3')
			n=30;
		else
			n=50;
		zdan=n;		//zdan在后面用来判断胜利条件
		dilei(n,b);		//埋雷
		for(i=0;i<L;i++)
			for(j=0;j<L;j++)
				a[i][j]='#';		//初始化地图
		system("cls");
		while(ming)			//生命值不为0时一直循环
		{
			//system("cls");
			goto_xy(0,0);
			danandu(nandu);
			ditu(&y,&x,a,&flag,&n);
			if(kbhit())		//输入
			{
				dong=getch();
				switch (dong)
				{
					case 'W':
					case 'w': a[y][x]=temp; y=xianzhi(y-1); shan=1; break;
					case 'S':
					case 's': a[y][x]=temp; y=xianzhi(y+1); shan=1; break;
					case 'A':
					case 'a': a[y][x]=temp; x=xianzhi(x-1); shan=1; break;
					case 'D':
					case 'd': a[y][x]=temp; x=xianzhi(x+1); shan=1; break;		//WASD移动光标 
					case 'E':
					case 'e': wa(y,x,a,b,&ming,&temp,&shan); break;		//e键挖雷
					case 'F':
					case 'f': biao(y,x,a,&flag,&n,&temp); break;		//f键插旗
				}
			}
				
			if(shan)		//光标闪动
			{
				shan=0;
				temp=a[y][x];
				a[y][x]=' ';
			}
			else
			{
				a[y][x]=temp;
				shan=1;
			}
			
			dan3=dan1=zdan;		//判断胜利条件
			dan2=0;
			for(i=0;i<L;i++)
				for(j=0;j<L;j++)
				{
					if(a[i][j]=='F' || a[i][j]=='#')
					{
						dan1-=1;
						if(b[i][j]==-1)
							dan2+=1;
					}
					if(a[i][j]=='F' && b[i][j]==-1)
						dan3-=1;
				}
			if(dan1==0 && dan2==zdan)		//所有的雷都被找出来（一部分雷上插旗） 则游戏胜利 
			{
				check=1;
				break;
			}
			if(!dan3)		//在所有的雷上插了旗则游戏胜利
			{
				check=1;
				break;
			}
			else if(flag==zdan)
				printf("\n\n\t某个位置标记有错误！");
			Sleep(500);
		}
		
		if(!ming) 			//生命值为0则失败
		{
			system("cls");
			goto_xy(0,0);
			danandu(nandu);
			for(i=0;i<L;i++)
				for(j=0;j<L;j++)
					if(a[i][j]!='F' && b[i][j]==-1)
						a[i][j]='x';		//失败时显示所有的雷
			ditu(&y,&x,a,&flag,&n);
			printf("\n\n\tYOU LOSE!\n\tR键重新开始");
			r=getch();
		}
		if(check)			//游戏胜利
		{
			system("cls");
			putchar(10);
			danandu(nandu);
			printf("\n\n\n\n\tYOU WIN!\n\n\tR键重新开始");
			r=getch();
		}
	}
	return 0;
} 

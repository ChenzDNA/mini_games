#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
void goto_xy(int x, int y)	//定位光标位置到指定坐标
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//获取标准输出句柄 
	COORD pos={x,y};			//坐标结构体 
	SetConsoleCursorPosition(hOut,pos);	//定位光标位置 
}
void updown(char a[15][50],int *iy,int *ming,int s)	//移动鸟，s=1向上，0向下
{
	if(s)
	{
		*iy-=1;			//先移动鸟的坐标
		if(a[*iy][7]=='#')	//
			*ming=0;	//撞到墙壁就没ming
		a[*iy][7]='*';		//
		a[*iy+1][7]=' ';	//鸟是'*'，鸟原来的位置变为空格
	}
	else
	{
		*iy+=1;
		if(a[*iy][7]=='#')
			*ming=0;
		a[*iy][7]='*';
		a[*iy-1][7]=' ';
	}
}

int main()
{
	system("mode con cols=50 lines=16");
	system("title flapy bird");
	
	int dong=7,ming,step=1,i,j,iy,fen=0,fly=0,wall=0,zgfen=0,wuhu;
	char a[15][50];
	char shuru,r=' ';
	
	while(r==' ')				//游戏结束时按空格键重开
	{
		for(i=0;i<14;i++)		// 
			for(j=0;j<50;j++)	// 
				a[i][j]=' ';	//初始化地图
			
		for(i=0;i<50;i++)		//
		{
			a[0][i]='#';		//铺天花板
			a[14][i]='#';		//铺地板
		}
		
		iy=7;				//
		a[iy][7]='*';			//初始位置
		
		ming=1;
		fen=0;
		wuhu=1;
		dong=7;
		
		while(ming)
		{
			//system("cls");						//
			goto_xy(0,0);
			for(i=0;i<15;i++)					//
			{							//
				for(j=0;j<50;j++)				//
					putchar(a[i][j]);			//
				putchar(10);					//
			}							//
			printf("\t你的分数：%d\t最高分：%d  ",fen,zgfen);	//打印地图和分数
			if(wuhu)						//
				printf("按空格键飞");				//
			else							//
				printf("芜湖~~起飞");				//芜湖~起飞~
			
			
			if(fly)				//如果fly不为0，鸟上升1格
			{				//
				updown(a,&iy,&ming,1);	//
				fly-=1;			//
			}
			
			if(_kbhit())			//
			{				//
				shuru=_getch();		//
				if(shuru==' ')		//空格键上升
				{			//
					fly=2;		//fly=2，鸟上升2格
					wuhu=0;		//芜湖用来控制芜湖的打印(见打印地图部分)
				}			//
			}				//
			else if(step%2==0 && fly==0)	//
				updown(a,&iy,&ming,0);	//每前进2格，鸟下落1格
		
		
			if(step%20==0)					//每前进20格，生成一堵墙
			{						// 
				wall=rand()%(13-dong)+2;		// 
				for(i=1;i<14;i++)			// 
				{					// 
					if(i<wall || i>=wall+dong)	//留出dong大小的空洞
						a[i][49]='#';		// 
					else				// 
						a[i][49]=' ';		// 
				}
			}
			
			for(j=0;j<50;j++)					//移动墙
				if(a[1][j]=='#')				// 
				{						//
					if(j==0)				//
						for(i=1;i<14;i++)		//墙走到头就消掉,变成空格 
							a[i][j]=' ';		//
					else					// 
					{					//
						for(i=1;i<14;i++)		// 
							if(a[i][j]=='#')	// 
							{			// 
								a[i][j-1]='#';	// 
								a[i][j]=' ';	// 
							}			// 
						if(j==7)			//墙经过鸟就加1分
							fen+=1;			//
					}
				}
			
			zgfen=(fen>zgfen)?fen:zgfen;	//更新最高分
			
			if(step%90==0)		//
				dong-=1;	//每前进90格缩小洞
			
			step+=1;
			Sleep(100);	//程序休眠100毫秒，相当于每秒10帧
		}			//实际上因为打印速度，帧率会更低
		
		system("cls");
		printf("\n\n\t你鸟没了！\n\n\t你的分数：%d\t最高分：%d\n\n",fen,zgfen);
		printf("\t\t按空格键重新开始");
		r=_getch();
	}
	return 0;
}

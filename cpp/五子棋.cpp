#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<conio.h>

#define limit(x,y) ((x)>-1&&(x)<40&&(y)>-1&&(y)<40)	//判断x，y有没有在地图内 

void goto_xy(int x, int y)	//定位光标位置到指定坐标
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//获取标准输出句柄 
	COORD pos={x,y};			//坐标结构体 
	SetConsoleCursorPosition(hOut,pos);	//定位光标位置 
}

void ditu(char a[40][80],int swt,int mode,int win)	//打印地图 
{
	int i,j;
	//system("cls");	//清屏 
	goto_xy(0,0);
	printf(	"  x 00  02  04  06  08  10  12  14  16  18  20  22  24  26  28  30  32  34  36  38  \n"
		" y    01  03  05  07  09  11  13  15  17  19  21  23  25  27  29  31  33  35  37  39\n");
	for(i=0;i<40;i++)
	{
		printf("%3d ",i);
		for(j=0;j<80;j++)
			printf("%c",a[i][j]);
		putchar(10);
	}
	if(mode==1 && win)
		(swt==0)?printf("\n\t\t\t黑方落子(x y)："):printf("\n\t\t\t白方落子(x y)："); 
	//mode用来说明是pvp还是cvc。1是pvp，需要提示黑方白方 
	//swt（switch缩）是0就是轮到黑方下，是1就表示轮到白方下 
} 

int panduan(char a[40][80],int ix,int iy)
{
	int close[32]={-1,2,0,2,1,2,1,0,1,-2,0,-2,-1,-2,-1,0,-1,2,0,2,1,2,1,0,1,-2,0,-2,-1,-2,-1,0};
	//close用来遍历相邻的格子，两两一对 
	int i,point,x,y,j;
	ix+=1;		//黑子●的值是-95 -15，白子○的值是-95 -15。ix的位置是第一个，区分不了黑白，所以自增1 
	for(i=0;i<16;i+=2)
	{
		point=0;
		if(a[iy+close[i]][ix+close[i+1]]==a[iy][ix]) 
		{	//如果以iy ix为中心的九宫格内有棋子和iy ix相同 
			for((x=ix,y=iy);(a[y+close[i]][x+close[i+1]]==a[iy][ix]);(x+=close[i+1],y+=close[i]))
				point+=1;
			//沿这个方向“搜索”棋子，如果与中心相同就point+1 
			j=i+8;	//j用来搜索反方向。close给32个值就是方便“掉头” 
			for((x=ix,y=iy);(a[y+close[j]][x+close[j+1]]==a[iy][ix]);(x+=close[j+1],y+=close[j]))
				point+=1;
			//沿反方向搜索棋子，与中心相同就point+1 
			if(point>3)
				return 1;
			//point>3的话就说明5子或6子、7子连在一起了（因为中心的棋子没加point），给主函数返回1，表示胜负已分 
		}
	}
	return 0;	//没有5子就返回0 
}

int main()
{
	system("color F0");	//设置前景色为黑色，背景色为白色 
	system("mode con cols=85 lines=47");	//设置窗口大小为85列，47行 
	int i,j,ix,x=0,iy=0,swt=0,mode=0,win=1,hei=0,bai=0;
	char a[40][80],str[100],back[]="back",r='r';
	while(r=='r' || r=='R')
	{	//r用来判断是继续游戏还是退出游戏 
		win=1;
		swt=0;
		hei=0,bai=0;
		system("cls");
		printf("\n\n\n\t\t\t1.pvp\n\n\t\t\t2.看2个憨批电脑对战\n\n\t\t\t输入1或2继续：");
		while(1)	//此循环用来输入 
		{
			while((scanf("%d",&mode))!=1)	//scanf函数的返回值是成功赋值的数目。 
				gets(str);	//这一句scanf()==0为真的话，说明我们不小心输入了字符，用gets()把缓冲区的数据清掉 
			if(mode>0 && mode<3)
				break;		//如果mode为1或2就退出循环，结束输入。 
		}
		if(mode==1)	//判断模式，pvp模式就把空地变为点阵，方便看坐标 
			for(i=0;i<40;i++)
				for(j=0;j<80;j+=2)
					a[i][j]=-95,a[i][j+1]=-92;	//·的值是-95 -92 
		else
			for(i=0;i<40;i++)	//cvc模式就把空地变为空格 
				for(j=0;j<80;j++)
					a[i][j]=' ';
		while(1)
		{
			ditu(a,swt,mode,win);
			if(mode==1)	//pvp模式 
			{
				do	//pvp模式就需要玩家输入落子的坐标（没错这个do-while循环就是输入） 
				{
					while((scanf("%d%d",&x,&iy))<2)
					{
						gets(str);			//和之前一样是输入保护 
						if(!(strcmp(str,back)))		//如果输入是"back"，就悔棋（玩家有可能看错坐标） 
						{
							a[iy][ix]=-95,a[iy][ix+1]=-92;	//把之前输入的坐标位置变回· 
							(swt==1)?(swt=0):(swt=1);	//改变swt(switch缩)的值 
						}
						ditu(a,swt,mode,win);	//悔棋或者输入错误的时候打印一遍地图（清屏） 
						system("cls");
					}
				}while(!limit(x,iy));		//输入的坐标要在地图之内 
				ix=x*2;		//控制台窗口两格连起来刚好是一个正方形，所以把输入的x坐标*2，对应控制台窗口的位置 
				if(a[iy][ix+1]==-15 || a[iy][ix+1]==-16)
					continue;	//如果输入的坐标上有棋子了，就重新输入 
			}
			else	//cvc模式 
			{
			//	Sleep(100);	//电脑下的太快了，Sleep冻结程序。里面的参数是冻结多少毫秒 
				do
				{
					x=rand()%40;	// 
					iy=rand()%40;	//因为是憨批电脑所以随机下了（谜之因果关系） 
					ix=x*2;		//x坐标依旧要*2 
				}while(a[iy][ix+1]==-15 || a[iy][ix+1]==-16);	//保证下在空地 
			}
			(swt==1)?(a[iy][ix]=-95,a[iy][ix+1]=-16,swt=0):(a[iy][ix]=-95,a[iy][ix+1]=-15,swt=1);
			//swt是1就下黑棋，swt是0就下白棋，下完后改变swt的值 
			if(panduan(a,ix,iy))	//判断胜负 
			{
				win=0;
				break;
			}
		}
		ditu(a,swt,mode,win);
		(swt==1)?printf("\n\n\t\t\t黑方胜利！"):printf("\n\n\t\t\t白方胜利！");		//根据swt的值打印哪方胜利 
		for(i=0;i<40;i++)
			for(j=1;j<80;j+=2)
				if(a[i][j]==-15)
					hei+=1;
				else if(a[i][j]==-16)
					bai+=1;
		//printf("hei=%d,bai=%d\n",hei,bai);
		printf("\t\t\t按R键重新开始,按E键退出游戏");
		while(r=getch())
			if(r=='R' || r=='r')
				break;
			else if(r=='E' || r=='e')
				return 0;
	}
}

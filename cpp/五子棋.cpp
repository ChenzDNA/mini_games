#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<conio.h>

#define limit(x,y) ((x)>-1&&(x)<40&&(y)>-1&&(y)<40)	//�ж�x��y��û���ڵ�ͼ�� 

void goto_xy(int x, int y)	//��λ���λ�õ�ָ������
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//��ȡ��׼������ 
	COORD pos={x,y};			//����ṹ�� 
	SetConsoleCursorPosition(hOut,pos);	//��λ���λ�� 
}

void ditu(char a[40][80],int swt,int mode,int win)	//��ӡ��ͼ 
{
	int i,j;
	//system("cls");	//���� 
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
		(swt==0)?printf("\n\t\t\t�ڷ�����(x y)��"):printf("\n\t\t\t�׷�����(x y)��"); 
	//mode����˵����pvp����cvc��1��pvp����Ҫ��ʾ�ڷ��׷� 
	//swt��switch������0�����ֵ��ڷ��£���1�ͱ�ʾ�ֵ��׷��� 
} 

int panduan(char a[40][80],int ix,int iy)
{
	int close[32]={-1,2,0,2,1,2,1,0,1,-2,0,-2,-1,-2,-1,0,-1,2,0,2,1,2,1,0,1,-2,0,-2,-1,-2,-1,0};
	//close�����������ڵĸ��ӣ�����һ�� 
	int i,point,x,y,j;
	ix+=1;		//���ӡ��ֵ��-95 -15�����ӡ��ֵ��-95 -15��ix��λ���ǵ�һ�������ֲ��˺ڰף���������1 
	for(i=0;i<16;i+=2)
	{
		point=0;
		if(a[iy+close[i]][ix+close[i+1]]==a[iy][ix]) 
		{	//�����iy ixΪ���ĵľŹ����������Ӻ�iy ix��ͬ 
			for((x=ix,y=iy);(a[y+close[i]][x+close[i+1]]==a[iy][ix]);(x+=close[i+1],y+=close[i]))
				point+=1;
			//������������������ӣ������������ͬ��point+1 
			j=i+8;	//j��������������close��32��ֵ���Ƿ��㡰��ͷ�� 
			for((x=ix,y=iy);(a[y+close[j]][x+close[j+1]]==a[iy][ix]);(x+=close[j+1],y+=close[j]))
				point+=1;
			//�ط������������ӣ���������ͬ��point+1 
			if(point>3)
				return 1;
			//point>3�Ļ���˵��5�ӻ�6�ӡ�7������һ���ˣ���Ϊ���ĵ�����û��point����������������1����ʾʤ���ѷ� 
		}
	}
	return 0;	//û��5�Ӿͷ���0 
}

int main()
{
	system("color F0");	//����ǰ��ɫΪ��ɫ������ɫΪ��ɫ 
	system("mode con cols=85 lines=47");	//���ô��ڴ�СΪ85�У�47�� 
	int i,j,ix,x=0,iy=0,swt=0,mode=0,win=1,hei=0,bai=0;
	char a[40][80],str[100],back[]="back",r='r';
	while(r=='r' || r=='R')
	{	//r�����ж��Ǽ�����Ϸ�����˳���Ϸ 
		win=1;
		swt=0;
		hei=0,bai=0;
		system("cls");
		printf("\n\n\n\t\t\t1.pvp\n\n\t\t\t2.��2���������Զ�ս\n\n\t\t\t����1��2������");
		while(1)	//��ѭ���������� 
		{
			while((scanf("%d",&mode))!=1)	//scanf�����ķ���ֵ�ǳɹ���ֵ����Ŀ�� 
				gets(str);	//��һ��scanf()==0Ϊ��Ļ���˵�����ǲ�С���������ַ�����gets()�ѻ�������������� 
			if(mode>0 && mode<3)
				break;		//���modeΪ1��2���˳�ѭ�����������롣 
		}
		if(mode==1)	//�ж�ģʽ��pvpģʽ�Ͱѿյر�Ϊ���󣬷��㿴���� 
			for(i=0;i<40;i++)
				for(j=0;j<80;j+=2)
					a[i][j]=-95,a[i][j+1]=-92;	//����ֵ��-95 -92 
		else
			for(i=0;i<40;i++)	//cvcģʽ�Ͱѿյر�Ϊ�ո� 
				for(j=0;j<80;j++)
					a[i][j]=' ';
		while(1)
		{
			ditu(a,swt,mode,win);
			if(mode==1)	//pvpģʽ 
			{
				do	//pvpģʽ����Ҫ����������ӵ����꣨û�����do-whileѭ���������룩 
				{
					while((scanf("%d%d",&x,&iy))<2)
					{
						gets(str);			//��֮ǰһ�������뱣�� 
						if(!(strcmp(str,back)))		//���������"back"���ͻ��壨����п��ܿ������꣩ 
						{
							a[iy][ix]=-95,a[iy][ix+1]=-92;	//��֮ǰ���������λ�ñ�ء� 
							(swt==1)?(swt=0):(swt=1);	//�ı�swt(switch��)��ֵ 
						}
						ditu(a,swt,mode,win);	//���������������ʱ���ӡһ���ͼ�������� 
						system("cls");
					}
				}while(!limit(x,iy));		//���������Ҫ�ڵ�ͼ֮�� 
				ix=x*2;		//����̨���������������պ���һ�������Σ����԰������x����*2����Ӧ����̨���ڵ�λ�� 
				if(a[iy][ix+1]==-15 || a[iy][ix+1]==-16)
					continue;	//���������������������ˣ����������� 
			}
			else	//cvcģʽ 
			{
			//	Sleep(100);	//�����µ�̫���ˣ�Sleep�����������Ĳ����Ƕ�����ٺ��� 
				do
				{
					x=rand()%40;	// 
					iy=rand()%40;	//��Ϊ�Ǻ�����������������ˣ���֮�����ϵ�� 
					ix=x*2;		//x��������Ҫ*2 
				}while(a[iy][ix+1]==-15 || a[iy][ix+1]==-16);	//��֤���ڿյ� 
			}
			(swt==1)?(a[iy][ix]=-95,a[iy][ix+1]=-16,swt=0):(a[iy][ix]=-95,a[iy][ix+1]=-15,swt=1);
			//swt��1���º��壬swt��0���°��壬�����ı�swt��ֵ 
			if(panduan(a,ix,iy))	//�ж�ʤ�� 
			{
				win=0;
				break;
			}
		}
		ditu(a,swt,mode,win);
		(swt==1)?printf("\n\n\t\t\t�ڷ�ʤ����"):printf("\n\n\t\t\t�׷�ʤ����");		//����swt��ֵ��ӡ�ķ�ʤ�� 
		for(i=0;i<40;i++)
			for(j=1;j<80;j+=2)
				if(a[i][j]==-15)
					hei+=1;
				else if(a[i][j]==-16)
					bai+=1;
		//printf("hei=%d,bai=%d\n",hei,bai);
		printf("\t\t\t��R�����¿�ʼ,��E���˳���Ϸ");
		while(r=getch())
			if(r=='R' || r=='r')
				break;
			else if(r=='E' || r=='e')
				return 0;
	}
}

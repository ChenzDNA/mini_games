#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
void goto_xy(int x, int y)	//��λ���λ�õ�ָ������
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//��ȡ��׼������ 
	COORD pos={x,y};			//����ṹ�� 
	SetConsoleCursorPosition(hOut,pos);	//��λ���λ�� 
}
void updown(char a[15][50],int *iy,int *ming,int s)	//�ƶ���s=1���ϣ�0����
{
	if(s)
	{
		*iy-=1;			//���ƶ��������
		if(a[*iy][7]=='#')	//
			*ming=0;	//ײ��ǽ�ھ�ûming
		a[*iy][7]='*';		//
		a[*iy+1][7]=' ';	//����'*'����ԭ����λ�ñ�Ϊ�ո�
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
	
	while(r==' ')				//��Ϸ����ʱ���ո���ؿ�
	{
		for(i=0;i<14;i++)		// 
			for(j=0;j<50;j++)	// 
				a[i][j]=' ';	//��ʼ����ͼ
			
		for(i=0;i<50;i++)		//
		{
			a[0][i]='#';		//���컨��
			a[14][i]='#';		//�̵ذ�
		}
		
		iy=7;				//
		a[iy][7]='*';			//��ʼλ��
		
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
			printf("\t��ķ�����%d\t��߷֣�%d  ",fen,zgfen);	//��ӡ��ͼ�ͷ���
			if(wuhu)						//
				printf("���ո����");				//
			else							//
				printf("�ߺ�~~���");				//�ߺ�~���~
			
			
			if(fly)				//���fly��Ϊ0��������1��
			{				//
				updown(a,&iy,&ming,1);	//
				fly-=1;			//
			}
			
			if(_kbhit())			//
			{				//
				shuru=_getch();		//
				if(shuru==' ')		//�ո������
				{			//
					fly=2;		//fly=2��������2��
					wuhu=0;		//�ߺ����������ߺ��Ĵ�ӡ(����ӡ��ͼ����)
				}			//
			}				//
			else if(step%2==0 && fly==0)	//
				updown(a,&iy,&ming,0);	//ÿǰ��2��������1��
		
		
			if(step%20==0)					//ÿǰ��20������һ��ǽ
			{						// 
				wall=rand()%(13-dong)+2;		// 
				for(i=1;i<14;i++)			// 
				{					// 
					if(i<wall || i>=wall+dong)	//����dong��С�Ŀն�
						a[i][49]='#';		// 
					else				// 
						a[i][49]=' ';		// 
				}
			}
			
			for(j=0;j<50;j++)					//�ƶ�ǽ
				if(a[1][j]=='#')				// 
				{						//
					if(j==0)				//
						for(i=1;i<14;i++)		//ǽ�ߵ�ͷ������,��ɿո� 
							a[i][j]=' ';		//
					else					// 
					{					//
						for(i=1;i<14;i++)		// 
							if(a[i][j]=='#')	// 
							{			// 
								a[i][j-1]='#';	// 
								a[i][j]=' ';	// 
							}			// 
						if(j==7)			//ǽ������ͼ�1��
							fen+=1;			//
					}
				}
			
			zgfen=(fen>zgfen)?fen:zgfen;	//������߷�
			
			if(step%90==0)		//
				dong-=1;	//ÿǰ��90����С��
			
			step+=1;
			Sleep(100);	//��������100���룬�൱��ÿ��10֡
		}			//ʵ������Ϊ��ӡ�ٶȣ�֡�ʻ����
		
		system("cls");
		printf("\n\n\t����û�ˣ�\n\n\t��ķ�����%d\t��߷֣�%d\n\n",fen,zgfen);
		printf("\t\t���ո�����¿�ʼ");
		r=_getch();
	}
	return 0;
}

#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <stdio.h>

#include <mmsystem.h> // mci��ͷ�ļ�
#pragma comment(lib, "winmm.lib")

 

#define WINDOW_WIDTH 640	//���ڿ��
#define WINDOW_HEIGHT 480	//���ڸ߶�
#define SCORE_TEXT_X 520	//����������x����
#define SCORE_NUMBER_X 580	//���������֡���x����
#define SCORE_Y 20			//������"��y����

//��ɫ
COLORREF columnColor[10] = {
	RGB(0x00,0x00,0xff),	//��ɫ
	RGB(0x00,0xff,0x00),	//��ɫ
	RGB(0xff,0xff,0x00),	//��ɫ
	RGB(0xff,0x00,0x00),	//��ɫ
	RGB(0x00,0xff,0xff),	//��ɫ
	RGB(0xcc,0x32,0x99),	//������
	RGB(0xff,0x24,0x00),	//�Ⱥ�ɫ
	RGB(0x7f,0x00,0xff),	//��ʯ����
	RGB(0xff,0x7f,0x00),	//��ɫ
	RGB(0x4d,0x4d,0xff),	//�޺���
};

//�����С
int fontSize[6] = { 30,	70,	90,	110, 130, 150};

//�÷�
int gScores;


// ��ӭ����
void welcome()
{

	// �����Ļ��ʾ
	cleardevice();		//�����ͼ�豸
	setcolor(YELLOW);	//��ɫ
	settextstyle(64, 0, _T("����"));
	outtextxy(160, 50, _T("����Գ���ɼ�"));
	setcolor(WHITE);
	settextstyle(16, 0, _T("����"));
	outtextxy(240, 200, _T("����������������һ��ָ���뷨"));
	outtextxy(240, 240, _T("����ɶ��ĸ�������ɶ��ĸ"));
	outtextxy(240, 280, _T("����ˣ����ͻ���ʧ�������!"));
	
	// ʵ����˸�ġ��������������
	int c=255;
	while(!_kbhit())//�������
	{
		setcolor(RGB(c, 0, 0));
		outtextxy(280, 400, _T("�����������"));
		c -= 8;
		if (c < 0) c = 255;
		Sleep(20);
	}
	_getch();
	cleardevice();

	srand(time(NULL));			// �����������
}

// �˳�����
void goodbye()
{
	cleardevice();
	setcolor(YELLOW);
	settextstyle(48, 0, _T("����"));
	outtextxy(104, 180, _T("�����߰ɣ�һ��ͺͷ��"));
	_getch();
}

void printScores()
{
	setcolor(RED);
	settextstyle(fontSize[0], 0, _T("΢���ź�"));	// ������ĸ������ʹ�С

	outtextxy(SCORE_TEXT_X, SCORE_Y, _T("������ "));

	char buf[10];
	sprintf_s(buf, "%d", gScores);
	outtextxy(SCORE_NUMBER_X, SCORE_Y, buf);
}

void play()
{
	char target;	// Ŀ����ĸ
	char key;		// �û��İ���
	int x, y;		// ��ĸ��λ��

	//��������
	mciSendString("open welcome.mp3 alias welcome", NULL, 0, NULL);
	mciSendString("play welcome repeat", NULL, 0, NULL);

	printScores();

	// ��ѭ��
	while (true)
	{
		target = 65 + rand() % 26;		// ���������д��ĸ
		x = rand() % WINDOW_WIDTH - 20;	// ������������λ��

		COLORREF color = columnColor[rand() % 10];//���ɫ

		int size = fontSize[rand() % 6];		//����ֺ�
		settextstyle(size, 0, _T("΢���ź�"));	// ������ĸ������ʹ�С



		for (y = 0; y < WINDOW_HEIGHT - 20; y++)
		{
			setcolor(color);//������ɫ

			if (x >= SCORE_TEXT_X - 20 && y <= SCORE_Y + 30)
			{
				cleardevice();
				printScores();
			}

			outtextxy(x, y, target);	// ��ʾ��ĸ


			if (_kbhit())//keyboardhit ��������Ӧ���������¼�
			{
				key = _getch();			// ��ȡ�û�����

				//�����
				if ((key == target) || (key == target + 32))
				{
					mciSendString("close gotmusic", NULL, 0, NULL);
					mciSendString("open effect.mp3 alias gotmusic", NULL, 0, NULL);
					mciSendString("play gotmusic", NULL, 0, NULL);

					// ������ȷ�������䡱��ĸ������ɫ���������
					//bar(x, y, x + 16, y + 30);//�ޱ߿�������

					gScores += 10;	//ÿ�ε�10��
					cleardevice();

					printScores();
					break;				// ����ѭ����������һ����ĸ
				}
				else if (key == 27)//ESC��
				{
					//�˳���Ϸ
					goodbye();
					getchar();

					// �ر�ͼ�ν���
					closegraph();
				}
			}
			Sleep(10);// ��ʱ
		}
	}
}



// ������
void main()
{
	HWND hwnd;
	int screenhight, screenwidth;
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);		// ��ʼ����ĻΪ 640x480
	hwnd = GetHWnd();
	//SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE - WS_CAPTION));
	screenhight = GetSystemMetrics(SM_CYSCREEN);
	screenwidth = GetSystemMetrics(SM_CXSCREEN);
	//MoveWindow(hwnd, screenwidth /4 , screenhight/2, WINDOW_WIDTH, WINDOW_HEIGHT, false);
	 
	welcome();					// ��ʾ��ӭ����
	//SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE - WS_CAPTION));
	play();
	
}
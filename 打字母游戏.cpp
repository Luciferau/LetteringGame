#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <stdio.h>

#include <mmsystem.h> // mci库头文件
#pragma comment(lib, "winmm.lib")

 

#define WINDOW_WIDTH 640	//窗口宽度
#define WINDOW_HEIGHT 480	//窗口高度
#define SCORE_TEXT_X 520	//“分数”的x坐标
#define SCORE_NUMBER_X 580	//“分数数字”的x坐标
#define SCORE_Y 20			//“分数"的y坐标

//颜色
COLORREF columnColor[10] = {
	RGB(0x00,0x00,0xff),	//蓝色
	RGB(0x00,0xff,0x00),	//绿色
	RGB(0xff,0xff,0x00),	//黄色
	RGB(0xff,0x00,0x00),	//红色
	RGB(0x00,0xff,0xff),	//青色
	RGB(0xcc,0x32,0x99),	//紫罗兰
	RGB(0xff,0x24,0x00),	//橙红色
	RGB(0x7f,0x00,0xff),	//中石板蓝
	RGB(0xff,0x7f,0x00),	//橙色
	RGB(0x4d,0x4d,0xff),	//霓虹蓝
};

//字体大小
int fontSize[6] = { 30,	70,	90,	110, 130, 150};

//得分
int gScores;


// 欢迎界面
void welcome()
{

	// 输出屏幕提示
	cleardevice();		//清理绘图设备
	setcolor(YELLOW);	//黄色
	settextstyle(64, 0, _T("黑体"));
	outtextxy(160, 50, _T("程序猿炼成记"));
	setcolor(WHITE);
	settextstyle(16, 0, _T("宋体"));
	outtextxy(240, 200, _T("来来来啦！告别你的一阳指输入法"));
	outtextxy(240, 240, _T("出来啥字母你就输入啥字母"));
	outtextxy(240, 280, _T("输对了，它就会消失！开玩吧!"));
	
	// 实现闪烁的“按任意键继续”
	int c=255;
	while(!_kbhit())//按任意键
	{
		setcolor(RGB(c, 0, 0));
		outtextxy(280, 400, _T("按任意键继续"));
		c -= 8;
		if (c < 0) c = 255;
		Sleep(20);
	}
	_getch();
	cleardevice();

	srand(time(NULL));			// 设置随机种子
}

// 退出界面
void goodbye()
{
	cleardevice();
	setcolor(YELLOW);
	settextstyle(48, 0, _T("黑体"));
	outtextxy(104, 180, _T("跟我走吧，一起秃头吧"));
	_getch();
}

void printScores()
{
	setcolor(RED);
	settextstyle(fontSize[0], 0, _T("微软雅黑"));	// 设置字母的字体和大小

	outtextxy(SCORE_TEXT_X, SCORE_Y, _T("分数： "));

	char buf[10];
	sprintf_s(buf, "%d", gScores);
	outtextxy(SCORE_NUMBER_X, SCORE_Y, buf);
}

void play()
{
	char target;	// 目标字母
	char key;		// 用户的按键
	int x, y;		// 字母的位置

	//启动音乐
	mciSendString("open welcome.mp3 alias welcome", NULL, 0, NULL);
	mciSendString("play welcome repeat", NULL, 0, NULL);

	printScores();

	// 主循环
	while (true)
	{
		target = 65 + rand() % 26;		// 产生任意大写字母
		x = rand() % WINDOW_WIDTH - 20;	// 产生任意下落位置

		COLORREF color = columnColor[rand() % 10];//随机色

		int size = fontSize[rand() % 6];		//随机字号
		settextstyle(size, 0, _T("微软雅黑"));	// 设置字母的字体和大小



		for (y = 0; y < WINDOW_HEIGHT - 20; y++)
		{
			setcolor(color);//字体颜色

			if (x >= SCORE_TEXT_X - 20 && y <= SCORE_Y + 30)
			{
				cleardevice();
				printScores();
			}

			outtextxy(x, y, target);	// 显示字母


			if (_kbhit())//keyboardhit 非阻塞响应键盘输入事件
			{
				key = _getch();			// 获取用户按键

				//答对了
				if ((key == target) || (key == target + 32))
				{
					mciSendString("close gotmusic", NULL, 0, NULL);
					mciSendString("open effect.mp3 alias gotmusic", NULL, 0, NULL);
					mciSendString("play gotmusic", NULL, 0, NULL);

					// 按键正确，“击落”字母（画黑色方块擦除）
					//bar(x, y, x + 16, y + 30);//无边框填充矩形

					gScores += 10;	//每次得10分
					cleardevice();

					printScores();
					break;				// 跳出循环，进行下一个字母
				}
				else if (key == 27)//ESC键
				{
					//退出游戏
					goodbye();
					getchar();

					// 关闭图形界面
					closegraph();
				}
			}
			Sleep(10);// 延时
		}
	}
}



// 主函数
void main()
{
	HWND hwnd;
	int screenhight, screenwidth;
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);		// 初始化屏幕为 640x480
	hwnd = GetHWnd();
	//SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE - WS_CAPTION));
	screenhight = GetSystemMetrics(SM_CYSCREEN);
	screenwidth = GetSystemMetrics(SM_CXSCREEN);
	//MoveWindow(hwnd, screenwidth /4 , screenhight/2, WINDOW_WIDTH, WINDOW_HEIGHT, false);
	 
	welcome();					// 显示欢迎界面
	//SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE - WS_CAPTION));
	play();
	
}
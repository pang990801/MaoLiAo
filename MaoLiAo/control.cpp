#include<graphics.h>
#include "control.h"
#include"conio.h"
#include "stdio.h"
#include"define.h"

extern int world;	//声明全局变量关卡 在进入FLAPPY BIRD关卡判定会用到

//构造
Control::Control(void)
{
	key = 0;
	loadimage(&img_bg, "res\\home.bmp", XSIZE, 5 * YSIZE);
}
//析构
Control::~Control(void)
{}

//声明过场动画

//游戏结束时的动画
void Control::showGameOver()
{
	IMAGE img;
	loadimage(&img, "res\\home.bmp", XSIZE, 5 * YSIZE);
	putimage(0, -YSIZE, &img);
	Sleep(6500);
}

//通过某一关的画面
void Control::showPassed(int world)
{
	cleardevice();
	IMAGE img;
	loadimage(&img, "res\\home.bmp", XSIZE, 5 * YSIZE);
	putimage(0, -2 * YSIZE, &img);
	char s1[20] = "LEVEL:  ";
	char s2[2];
	_itoa_s(world, s2, 10);
	outtextxy(XSIZE / 2 - 20, YSIZE / 2 - 5, s1);
	outtextxy(XSIZE / 2, YSIZE / 2 - 5, s2);
	Sleep(2000);
}

//通关所有的动画
void Control::showPassedAll()
{
	IMAGE img;
	loadimage(&img, "res\\home.bmp", XSIZE, 5 * YSIZE);
	putimage(0, -3 * YSIZE, &img);
	Sleep(7800);
}

//键盘中转 返回key
int Control::GetCommand()
{
	int c = 0;

	//由于接收的信号不只一个，所以需要异步输入
	//异步输入函数：利用Windows API中的GetAsyncKeyState函数

	if (GetAsyncKeyState('A') & 0x8000)
		c |= CMD_LEFT;
	if (GetAsyncKeyState('D') & 0x8000)
		c |= CMD_RIGHT;
	if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState('K') & 0x8000))
		c |= CMD_UP;
	if (GetAsyncKeyState('S') & 0x8000)
		c |= CMD_DOWN;
	if (GetAsyncKeyState('J') & 0x8000)
		c |= CMD_SHOOT;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		c |= CMD_ESC;
	return c;
}

//绘制暂停的函数
void Control::pauseClick()
{

	//绘制UI界面
	BeginBatchDraw();

	//确定页面顶点
	POINT points[8] = { { XSIZE / 2 - 45,YSIZE / 3 },{ XSIZE / 2 + 45,YSIZE / 3 },{ XSIZE / 2 + 45,YSIZE / 3 + 120 },{ XSIZE / 2 - 45,YSIZE / 3 + 120 } };
	setfillcolor(GREEN);
	fillpolygon(points, 4); //绘制多边形
	setbkmode(TRANSPARENT); //设置背景模式-透明
	//设置字体
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 18;						// 设置字体高度为 15
	_tcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = 1000;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式


	//darwtext Windows自带的矩形文本 可以用outtextxy()代替的 由于可以使用RECT来储存文本矩形的参数 所有用起来更方便一些
	//RECT：rect这个对象是用来存储成对出现的参数，比如，一个矩形框的左上角坐标、宽度和高度
	//DT_SINGLELINE :单行显示
	//DT_CENTER:居中显示
	//DT_VCENTER : 垂直居中显示
	//输出文字

	RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 };			//回到游戏
	rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
	drawtext("返回游戏", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 };		//重新开始
	rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	drawtext("重新开始", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 };		//主菜单
	rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
	drawtext("退出游戏", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r5 = { XSIZE / 2 - 45,YSIZE / 3 + 90,XSIZE / 2 + 45,YSIZE / 3 + 120 };		//存档
	rectangle(XSIZE / 2 - 45, YSIZE / 3 + 90, XSIZE / 2 + 45, YSIZE / 3 + 120);
	drawtext("进行存档", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	FlushBatchDraw();

	FlushMouseMsgBuffer();//清空鼠标消息队列，否则会出错 //因为延时的存在，所以需要这样正确处理鼠标消息

	//绘制暂停时候的UI交互
	while (true)
	{
		BeginBatchDraw();
		MOUSEMSG m = GetMouseMsg();
		if ((m.uMsg == WM_LBUTTONDOWN))
		{
			EndBatchDraw();
			if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 && m.y < YSIZE / 3 + 30)//如果选择“回到游戏”，则返回VIR_RETURN
			{
				key = VIR_RETURN;
				return;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 30 && m.y < YSIZE / 3 + 60)//如果选择“重新开始”，则返回VIR_RESTART
			{
				key = VIR_RESTART;
				return;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 60 && m.y < YSIZE / 3 + 90)//如果选择“主菜单”，则返回VIR_HOME
			{
				key = VIR_HOME;
				return;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 90 && m.y < YSIZE / 3 + 120)//如果选择“主菜单”，则返回VIR_HOME
			{
				FILE* fp = NULL;
				fopen_s(&fp, "gameRecord.dat", "w");
				fprintf_s(fp, "%d", world);
				fclose(fp);
				key = VIR_RETURN;
				return;
			}
		}

		if ((m.uMsg == WM_MOUSEMOVE))
		{
			RECT r;
			int i;
			for (i = 0; i < 4; i++)	//相当于重新绘制一遍 用不同的颜色突出
			{
				//当鼠标移动到该区域时
				if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + i * 30 && m.y < YSIZE / 3 + 30 + i * 30)
				{
					r.left = XSIZE / 2 - 45;
					r.top = YSIZE / 3 + i * 30;
					r.right = XSIZE / 2 + 45;
					r.bottom = YSIZE / 3 + 30 + i * 30;
					POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
					setfillcolor(BLUE);
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
					settextstyle(18, 0, "黑体");
					switch (i)
					{
					case 0:
						drawtext("Return", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					case 1:
						drawtext("start again", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					case 2:
						drawtext("The menu", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					case 3:
						drawtext("Write Data", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
				}
				else
				{
					//当鼠标移出该区域时
					if (getpixel(XSIZE / 2 - 45 + 1, YSIZE / 3 + i * 30 + 1) == BLUE) //获取点的颜色
					{
						r.left = XSIZE / 2 - 45;
						r.top = YSIZE / 3 + i * 30;
						r.right = XSIZE / 2 + 45;
						r.bottom = YSIZE / 3 + 30 + i * 30;
						POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
						setfillcolor(GREEN);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						settextstyle(18, 0, "黑体");
						switch (i)
						{
						case 0:
							drawtext("返回游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 1:
							drawtext("重新开始", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
							drawtext("退出游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 3:
							drawtext("进行存档", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					FlushBatchDraw();
				}
			}
		}
	}
}

//获取键盘
int Control::getKey()
{
	if (_kbhit())
	{
		key = GetCommand();
	}
	if (key & CMD_ESC) //当按Esc键时弹出暂停菜单
	{
		pauseClick();
	}
	return key;
}

//进入时的开始界面
void Control::gameStart()
{
	cleardevice(); //清屏
	setbkmode(TRANSPARENT); //设置背景模式-透明
	putimage(0, 0, &img_bg);
	settextstyle(40, 0, "Gill Sans");
	RECT r1 = { 0, 0, XSIZE, YSIZE / 3 };
	//drawtext("猫里奥", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//主界面(同时也是界面1)
	POINT points[8] = { { XSIZE / 2 - 45,YSIZE / 3 },{ XSIZE / 2 + 45,YSIZE / 3 },{ XSIZE / 2 + 45,YSIZE / 3 + 150 },{ XSIZE / 2 - 45,YSIZE / 3 + 150 } };
	setfillcolor(0x666666);
	fillpolygon(points, 4); //绘制多边形
	setbkmode(TRANSPARENT); //设置背景模式-透明
		//设置字体
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 20;						// 设置字体高度为 20
	_tcscpy_s(f.lfFaceName, _T("黑体"));	// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = 0;						// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式

	RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 }; rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
	RECT r5 = { XSIZE / 2 - 45,YSIZE / 3 + 90,XSIZE / 2 + 45,YSIZE / 3 + 120 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 90, XSIZE / 2 + 45, YSIZE / 3 + 120);
	RECT r6 = { XSIZE / 2 - 45,YSIZE / 3 + 120,XSIZE / 2 + 45,YSIZE / 3 + 150 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 120, XSIZE / 2 + 45, YSIZE / 3 + 150);

	drawtext("开始", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("介绍", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("指导", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("退出", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("读档", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	bool _HOME = true, _INTRODUCTION = false, _OPERATION = false, _READ = false; //true表示处于当前页面 UI界面三个

	MOUSEMSG m;
	while (_HOME) //当在界面1时的UI交互
	{
		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN: //点击选择
			EndBatchDraw();
			if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 && m.y < YSIZE / 3 + 30 && _HOME == 1 && _INTRODUCTION == 0 && _OPERATION == 0)//如果选择“开始游戏”
			{
				_HOME = false;
				break;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 30 && m.y < YSIZE / 3 + 60 && _HOME == 1 && _OPERATION == 0)//如果选择“游戏介绍”
			{
				_INTRODUCTION = true;	//界面2的绘制
				cleardevice();
				putimage(0, 0, &img_bg);
				settextstyle(20, 0, _T("黑体"));
				outtextxy(215, 115, "游戏介绍");
				settextstyle(16, 0, _T("黑体"));
				outtextxy(190, 155, "这是一款横版过关");
				outtextxy(190, 180, "游戏。游戏主角叫");
				outtextxy(190, 205, "猫里奥，共有三关");
				outtextxy(190, 230, "第三关为跳跃关卡");
				outtextxy(190, 255, "游戏开发者：PWB");
				RECT R1 = { XSIZE - 46,YSIZE - 26,XSIZE - 2,YSIZE - 2 }; rectangle(XSIZE - 46, YSIZE - 26, XSIZE - 2, YSIZE - 2);
				drawtext("返回", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 60 && m.y < YSIZE / 3 + 90 && _HOME == 1 && _INTRODUCTION == 0)//如果选择“操作说明”
			{
				_OPERATION = true;	//界面3的绘制
				cleardevice();
				putimage(0, 0, &img_bg);
				settextstyle(20, 0, _T("黑体"));
				outtextxy(215, 115, "操作指南");
				settextstyle(16, 0, _T("黑体"));
				outtextxy(200, 155, "向左移动：A键");
				outtextxy(200, 180, "向右移动：D键");
				outtextxy(200, 205, "开火射击：J键");
				outtextxy(200, 230, "跳跃：W键/K键");
				outtextxy(200, 255, "暂停键：Esc键");
				RECT R2 = { XSIZE - 46,YSIZE - 26,XSIZE - 2,YSIZE - 2 }; rectangle(XSIZE - 46, YSIZE - 26, XSIZE - 2, YSIZE - 2);
				drawtext("返回", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 90 && m.y < YSIZE / 3 + 120 && _HOME == 1 && _INTRODUCTION == 0 && _OPERATION == 0)//如果选择“退出游戏”
				exit(0);
			else if (m.x > XSIZE - 46 && m.x<XSIZE - 3 && m.y>YSIZE - 26 && m.y < YSIZE - 3 && (_INTRODUCTION == 1 || _OPERATION == 1))//如果选择“返回”
			{
				cleardevice();
				_HOME = false, _INTRODUCTION = false, _OPERATION = false;
				gameStart();
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 120 && m.y < YSIZE / 3 + 150 && _HOME == 1 && _INTRODUCTION == 0 && _OPERATION == 0) //如果选择"读取存档"
			{
				//读档在此加入
				FILE* fp;
				int flag;
				fopen_s(&fp, "gameRecord.dat", "r");
				fscanf_s(fp, "%d", &flag);
				if (flag >= 4 || flag <= 0) {
					printf("%d\n", MessageBox(GetForegroundWindow(), "提醒", "存档缺失，请检查存档", 1));
				}
				else {
					world = flag;
					fclose(fp);
					_HOME = false;
					break;
				}
			}
			else
				break;
		case WM_MOUSEMOVE:	//绘制移动鼠标到选项上高亮显示的选项
			RECT r;
			if (_INTRODUCTION == 1 || _OPERATION == 1)
			{
				if (m.x > XSIZE - 46 && m.x<XSIZE - 3 && m.y>YSIZE - 26 && m.y < YSIZE - 3)
				{
					r.left = XSIZE - 46;
					r.top = YSIZE - 26;
					r.right = XSIZE - 2;
					r.bottom = YSIZE - 2;
					POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
					setfillcolor(RED);
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
					drawtext("Return", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else
				{
					if (getpixel(XSIZE - 46 + 1, YSIZE - 26 + 1) == RED)
					{
						r.left = XSIZE - 46;
						r.top = YSIZE - 26;
						r.right = XSIZE - 2;
						r.bottom = YSIZE - 2;
						POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
						setfillcolor(BLACK);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						drawtext("返回", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}
			}
			else
			{
				for (int i = 0; i < 5; i++)
				{
					if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + i * 30 && m.y < YSIZE / 3 + 30 + i * 30)
					{
						r.left = XSIZE / 2 - 45;
						r.top = YSIZE / 3 + i * 30;
						r.right = XSIZE / 2 + 45;
						r.bottom = YSIZE / 3 + 30 + i * 30;
						POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
						setfillcolor(GREEN);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						settextstyle(14, 0, "黑体");
						switch (i)
						{
						case 0:
							drawtext("Start", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 1:
							drawtext("Introduction", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
							drawtext("Directions", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 3:
							drawtext("Exit", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 4:
							drawtext("Read Load", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					else
					{
						if (getpixel(XSIZE / 2 - 45 + 1, YSIZE / 3 + i * 30 + 1) == GREEN)
						{
							r.left = XSIZE / 2 - 45;
							r.top = YSIZE / 3 + i * 30;
							r.right = XSIZE / 2 + 45;
							r.bottom = YSIZE / 3 + 30 + i * 30;
							POINT points[4] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
							setfillcolor(0x666666);
							fillpolygon(points, 4);
							settextstyle(20, 0, "黑体");
							switch (i)
							{
							case 0:
								drawtext("开始", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 1:
								drawtext("介绍", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 2:
								drawtext("指导", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 3:
								drawtext("退出", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 4:
								drawtext("读档", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							}
						}
					}
				}
			}
			FlushBatchDraw();
			break;
		default:
			break;
		}
	}
}

//显示分数
void Control::showScore(int score)
{
	settextstyle(0, 0, "Cooper");
	char s1[20] = "得分:  ";
	char s2[5];
	_itoa_s(score, s2, 10);	//功能：将任意类型的数字转换为字符串。在<stdlib.h>中与之有相反功能的函数是atoi。sprintf同样功能 
	strcat_s(s1, s2);
	setbkmode(TRANSPARENT); //文本UI的最上显示 layout
	outtextxy(10, 10, s1);  //左边显示
	setbkmode(OPAQUE);
}

//显示关卡
void Control::showLevel(int level)
{
	settextstyle(0, 0, "Cooper");
	char s1[20] = "关卡:  ";
	char s2[2];
	_itoa_s(level, s2, 10);
	strcat_s(s1, s2);
	setbkmode(TRANSPARENT);
	outtextxy(XSIZE - 90, 10, s1);
	setbkmode(OPAQUE);
}

//主角死亡时的动画 告诉生命值
void Control::showDied(int life)
{
	settextstyle(0, 0, "Goudy Stout");
	cleardevice();
	IMAGE img;
	loadimage(&img, "res\\home.bmp", XSIZE, 5 * YSIZE);
	IMAGE img_hero;
	loadimage(&img_hero, "res\\role.bmp");
	putimage(0, -2 * YSIZE, &img);
	if (life == 1) {
		putimage(XSIZE / 2 - 16, YSIZE / 2 - 16, WIDTH, HEIGHT, &img_hero, 2 * WIDTH, 0, SRCPAINT);
	}
	if (life == 2) {
		putimage(XSIZE / 2 - 37, YSIZE / 2 - 16, WIDTH, HEIGHT, &img_hero, 2 * WIDTH, 0, SRCPAINT);
		putimage(XSIZE / 2 + 5, YSIZE / 2 - 16, WIDTH, HEIGHT, &img_hero, 2 * WIDTH, 0, SRCPAINT);
	}
	if (life == 3) {
		putimage(XSIZE / 2 - 58, YSIZE / 2 - 16, WIDTH, HEIGHT, &img_hero, 2 * WIDTH, 0, SRCPAINT);
		putimage(XSIZE / 2 - 16, YSIZE / 2 - 16, WIDTH, HEIGHT, &img_hero, 2 * WIDTH, 0, SRCPAINT);
		putimage(XSIZE / 2 + 26, YSIZE / 2 - 16, WIDTH, HEIGHT, &img_hero, 2 * WIDTH, 0, SRCPAINT);
	}
	if (life == 4) {
		putimage(XSIZE / 2 - 79, YSIZE / 2 - 16, WIDTH, HEIGHT, &img_hero, 2 * WIDTH, 0, SRCPAINT);
		putimage(XSIZE / 2 - 37, YSIZE / 2 - 16, WIDTH, HEIGHT, &img_hero, 2 * WIDTH, 0, SRCPAINT);
		putimage(XSIZE / 2 + 5, YSIZE / 2 - 16, WIDTH, HEIGHT, &img_hero, 2 * WIDTH, 0, SRCPAINT);
		putimage(XSIZE / 2 + 47, YSIZE / 2 - 16, WIDTH, HEIGHT, &img_hero, 2 * WIDTH, 0, SRCPAINT);
	}
	Sleep(2000);
}


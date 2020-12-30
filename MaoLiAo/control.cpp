#include<graphics.h>
#include "control.h"
#include"conio.h"
#include "stdio.h"
#include"define.h"

extern int world;	//����ȫ�ֱ����ؿ� �ڽ���FLAPPY BIRD�ؿ��ж����õ�

//����
Control::Control(void)
{
	key = 0;
	loadimage(&img_bg, "res\\home.bmp", XSIZE, 5 * YSIZE);
}
//����
Control::~Control(void)
{}

//������������

//��Ϸ����ʱ�Ķ���
void Control::showGameOver()
{
	IMAGE img;
	loadimage(&img, "res\\home.bmp", XSIZE, 5 * YSIZE);
	putimage(0, -YSIZE, &img);
	Sleep(6500);
}

//ͨ��ĳһ�صĻ���
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

//ͨ�����еĶ���
void Control::showPassedAll()
{
	IMAGE img;
	loadimage(&img, "res\\home.bmp", XSIZE, 5 * YSIZE);
	putimage(0, -3 * YSIZE, &img);
	Sleep(7800);
}

//������ת ����key
int Control::GetCommand()
{
	int c = 0;

	//���ڽ��յ��źŲ�ֻһ����������Ҫ�첽����
	//�첽���뺯��������Windows API�е�GetAsyncKeyState����

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

//������ͣ�ĺ���
void Control::pauseClick()
{

	//����UI����
	BeginBatchDraw();

	//ȷ��ҳ�涥��
	POINT points[8] = { { XSIZE / 2 - 45,YSIZE / 3 },{ XSIZE / 2 + 45,YSIZE / 3 },{ XSIZE / 2 + 45,YSIZE / 3 + 120 },{ XSIZE / 2 - 45,YSIZE / 3 + 120 } };
	setfillcolor(GREEN);
	fillpolygon(points, 4); //���ƶ����
	setbkmode(TRANSPARENT); //���ñ���ģʽ-͸��
	//��������
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 18;						// ��������߶�Ϊ 15
	_tcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = 1000;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ


	//darwtext Windows�Դ��ľ����ı� ������outtextxy()����� ���ڿ���ʹ��RECT�������ı����εĲ��� ����������������һЩ
	//RECT��rect��������������洢�ɶԳ��ֵĲ��������磬һ�����ο�����Ͻ����ꡢ��Ⱥ͸߶�
	//DT_SINGLELINE :������ʾ
	//DT_CENTER:������ʾ
	//DT_VCENTER : ��ֱ������ʾ
	//�������

	RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 };			//�ص���Ϸ
	rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
	drawtext("������Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 };		//���¿�ʼ
	rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	drawtext("���¿�ʼ", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 };		//���˵�
	rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
	drawtext("�˳���Ϸ", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r5 = { XSIZE / 2 - 45,YSIZE / 3 + 90,XSIZE / 2 + 45,YSIZE / 3 + 120 };		//�浵
	rectangle(XSIZE / 2 - 45, YSIZE / 3 + 90, XSIZE / 2 + 45, YSIZE / 3 + 120);
	drawtext("���д浵", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	FlushBatchDraw();

	FlushMouseMsgBuffer();//��������Ϣ���У��������� //��Ϊ��ʱ�Ĵ��ڣ�������Ҫ������ȷ���������Ϣ

	//������ͣʱ���UI����
	while (true)
	{
		BeginBatchDraw();
		MOUSEMSG m = GetMouseMsg();
		if ((m.uMsg == WM_LBUTTONDOWN))
		{
			EndBatchDraw();
			if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 && m.y < YSIZE / 3 + 30)//���ѡ�񡰻ص���Ϸ�����򷵻�VIR_RETURN
			{
				key = VIR_RETURN;
				return;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 30 && m.y < YSIZE / 3 + 60)//���ѡ�����¿�ʼ�����򷵻�VIR_RESTART
			{
				key = VIR_RESTART;
				return;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 60 && m.y < YSIZE / 3 + 90)//���ѡ�����˵������򷵻�VIR_HOME
			{
				key = VIR_HOME;
				return;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 90 && m.y < YSIZE / 3 + 120)//���ѡ�����˵������򷵻�VIR_HOME
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
			for (i = 0; i < 4; i++)	//�൱�����»���һ�� �ò�ͬ����ɫͻ��
			{
				//������ƶ���������ʱ
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
					settextstyle(18, 0, "����");
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
					//������Ƴ�������ʱ
					if (getpixel(XSIZE / 2 - 45 + 1, YSIZE / 3 + i * 30 + 1) == BLUE) //��ȡ�����ɫ
					{
						r.left = XSIZE / 2 - 45;
						r.top = YSIZE / 3 + i * 30;
						r.right = XSIZE / 2 + 45;
						r.bottom = YSIZE / 3 + 30 + i * 30;
						POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
						setfillcolor(GREEN);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						settextstyle(18, 0, "����");
						switch (i)
						{
						case 0:
							drawtext("������Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 1:
							drawtext("���¿�ʼ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
							drawtext("�˳���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 3:
							drawtext("���д浵", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					FlushBatchDraw();
				}
			}
		}
	}
}

//��ȡ����
int Control::getKey()
{
	if (_kbhit())
	{
		key = GetCommand();
	}
	if (key & CMD_ESC) //����Esc��ʱ������ͣ�˵�
	{
		pauseClick();
	}
	return key;
}

//����ʱ�Ŀ�ʼ����
void Control::gameStart()
{
	cleardevice(); //����
	setbkmode(TRANSPARENT); //���ñ���ģʽ-͸��
	putimage(0, 0, &img_bg);
	settextstyle(40, 0, "Gill Sans");
	RECT r1 = { 0, 0, XSIZE, YSIZE / 3 };
	//drawtext("è���", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//������(ͬʱҲ�ǽ���1)
	POINT points[8] = { { XSIZE / 2 - 45,YSIZE / 3 },{ XSIZE / 2 + 45,YSIZE / 3 },{ XSIZE / 2 + 45,YSIZE / 3 + 150 },{ XSIZE / 2 - 45,YSIZE / 3 + 150 } };
	setfillcolor(0x666666);
	fillpolygon(points, 4); //���ƶ����
	setbkmode(TRANSPARENT); //���ñ���ģʽ-͸��
		//��������
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 20;						// ��������߶�Ϊ 20
	_tcscpy_s(f.lfFaceName, _T("����"));	// ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = 0;						// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ

	RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 }; rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
	RECT r5 = { XSIZE / 2 - 45,YSIZE / 3 + 90,XSIZE / 2 + 45,YSIZE / 3 + 120 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 90, XSIZE / 2 + 45, YSIZE / 3 + 120);
	RECT r6 = { XSIZE / 2 - 45,YSIZE / 3 + 120,XSIZE / 2 + 45,YSIZE / 3 + 150 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 120, XSIZE / 2 + 45, YSIZE / 3 + 150);

	drawtext("��ʼ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("����", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("ָ��", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("�˳�", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("����", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	bool _HOME = true, _INTRODUCTION = false, _OPERATION = false, _READ = false; //true��ʾ���ڵ�ǰҳ�� UI��������

	MOUSEMSG m;
	while (_HOME) //���ڽ���1ʱ��UI����
	{
		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN: //���ѡ��
			EndBatchDraw();
			if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 && m.y < YSIZE / 3 + 30 && _HOME == 1 && _INTRODUCTION == 0 && _OPERATION == 0)//���ѡ�񡰿�ʼ��Ϸ��
			{
				_HOME = false;
				break;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 30 && m.y < YSIZE / 3 + 60 && _HOME == 1 && _OPERATION == 0)//���ѡ����Ϸ���ܡ�
			{
				_INTRODUCTION = true;	//����2�Ļ���
				cleardevice();
				putimage(0, 0, &img_bg);
				settextstyle(20, 0, _T("����"));
				outtextxy(215, 115, "��Ϸ����");
				settextstyle(16, 0, _T("����"));
				outtextxy(190, 155, "����һ�������");
				outtextxy(190, 180, "��Ϸ����Ϸ���ǽ�");
				outtextxy(190, 205, "è��£���������");
				outtextxy(190, 230, "������Ϊ��Ծ�ؿ�");
				outtextxy(190, 255, "��Ϸ�����ߣ�PWB");
				RECT R1 = { XSIZE - 46,YSIZE - 26,XSIZE - 2,YSIZE - 2 }; rectangle(XSIZE - 46, YSIZE - 26, XSIZE - 2, YSIZE - 2);
				drawtext("����", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 60 && m.y < YSIZE / 3 + 90 && _HOME == 1 && _INTRODUCTION == 0)//���ѡ�񡰲���˵����
			{
				_OPERATION = true;	//����3�Ļ���
				cleardevice();
				putimage(0, 0, &img_bg);
				settextstyle(20, 0, _T("����"));
				outtextxy(215, 115, "����ָ��");
				settextstyle(16, 0, _T("����"));
				outtextxy(200, 155, "�����ƶ���A��");
				outtextxy(200, 180, "�����ƶ���D��");
				outtextxy(200, 205, "���������J��");
				outtextxy(200, 230, "��Ծ��W��/K��");
				outtextxy(200, 255, "��ͣ����Esc��");
				RECT R2 = { XSIZE - 46,YSIZE - 26,XSIZE - 2,YSIZE - 2 }; rectangle(XSIZE - 46, YSIZE - 26, XSIZE - 2, YSIZE - 2);
				drawtext("����", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 90 && m.y < YSIZE / 3 + 120 && _HOME == 1 && _INTRODUCTION == 0 && _OPERATION == 0)//���ѡ���˳���Ϸ��
				exit(0);
			else if (m.x > XSIZE - 46 && m.x<XSIZE - 3 && m.y>YSIZE - 26 && m.y < YSIZE - 3 && (_INTRODUCTION == 1 || _OPERATION == 1))//���ѡ�񡰷��ء�
			{
				cleardevice();
				_HOME = false, _INTRODUCTION = false, _OPERATION = false;
				gameStart();
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 120 && m.y < YSIZE / 3 + 150 && _HOME == 1 && _INTRODUCTION == 0 && _OPERATION == 0) //���ѡ��"��ȡ�浵"
			{
				//�����ڴ˼���
				FILE* fp;
				int flag;
				fopen_s(&fp, "gameRecord.dat", "r");
				fscanf_s(fp, "%d", &flag);
				if (flag >= 4 || flag <= 0) {
					printf("%d\n", MessageBox(GetForegroundWindow(), "����", "�浵ȱʧ������浵", 1));
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
		case WM_MOUSEMOVE:	//�����ƶ���굽ѡ���ϸ�����ʾ��ѡ��
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
						drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
						settextstyle(14, 0, "����");
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
							settextstyle(20, 0, "����");
							switch (i)
							{
							case 0:
								drawtext("��ʼ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 1:
								drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 2:
								drawtext("ָ��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 3:
								drawtext("�˳�", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 4:
								drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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

//��ʾ����
void Control::showScore(int score)
{
	settextstyle(0, 0, "Cooper");
	char s1[20] = "�÷�:  ";
	char s2[5];
	_itoa_s(score, s2, 10);	//���ܣ����������͵�����ת��Ϊ�ַ�������<stdlib.h>����֮���෴���ܵĺ�����atoi��sprintfͬ������ 
	strcat_s(s1, s2);
	setbkmode(TRANSPARENT); //�ı�UI��������ʾ layout
	outtextxy(10, 10, s1);  //�����ʾ
	setbkmode(OPAQUE);
}

//��ʾ�ؿ�
void Control::showLevel(int level)
{
	settextstyle(0, 0, "Cooper");
	char s1[20] = "�ؿ�:  ";
	char s2[2];
	_itoa_s(level, s2, 10);
	strcat_s(s1, s2);
	setbkmode(TRANSPARENT);
	outtextxy(XSIZE - 90, 10, s1);
	setbkmode(OPAQUE);
}

//��������ʱ�Ķ��� ��������ֵ
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


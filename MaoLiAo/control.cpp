#include "control.h"
#include<graphics.h>
#include"conio.h"
#include"mydefine.h"
#include "stdio.h"
extern int world;	//����ȫ�ֱ���

control::control(void) //����
{
	key = 0;
}   
control::~control(void) //����
{}  

int control::GetCommand() //������ת ����key
{
	int c = 0;
	
	//���ڽ��յ��źŲ�֪һ����������Ҫ�첽����
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
void control::pauseClick()
{

	//����UI����
	BeginBatchDraw();

	//ȷ��ҳ�涥��
	POINT points[8] = { { XSIZE / 2 - 45,YSIZE / 3 },{ XSIZE / 2 + 45,YSIZE / 3 },{ XSIZE / 2 + 45,YSIZE / 3 + 120 },{ XSIZE / 2 - 45,YSIZE / 3 + 120 } };
	setfillcolor(GREEN);
	fillpolygon(points, 4); //���ƶ����
	setbkmode(TRANSPARENT); //���ñ���ģʽ-͸��
	
	//����Text
	settextstyle(15, 0, "��������");

	//darwtext Windows�Դ��ľ����ı� ������outtextxy()����� ���ڿ���ʹ��RECT�������ı����εĲ��� ����������������һЩ
	//RECT��rect��������������洢�ɶԳ��ֵĲ��������磬һ�����ο�����Ͻ����ꡢ��Ⱥ͸߶�
	//DT_SINGLELINE :������ʾ
	//DT_CENTER:������ʾ
	//DT_VCENTER : ��ֱ������ʾ

	RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 };	//�ص���Ϸ
	rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
	drawtext("������Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 };	//���¿�ʼ
	rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	drawtext("����һ��", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 };	//���˵�
	rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
	drawtext("����ؼ�", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	RECT r5 = { XSIZE / 2 - 45,YSIZE / 3 + 90,XSIZE / 2 + 45,YSIZE / 3 + 120 };	//���˵�
	rectangle(XSIZE / 2 - 45, YSIZE / 3 + 90, XSIZE / 2 + 45, YSIZE / 3 + 120);
	drawtext("����浵", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//��������
	FlushBatchDraw();

	FlushMouseMsgBuffer();//��������Ϣ���У��������� //��Ϊ��ʱ�Ĵ��ڣ�������Ҫ������ȷ���������Ϣ

	//������ͣʱ���UI����
	while (true)
	{
		BeginBatchDraw();
		MOUSEMSG m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN: //���ѡ��
			EndBatchDraw();
			if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 && m.y<YSIZE / 3 + 30)//���ѡ�񡰻ص���Ϸ�����򷵻�VIR_RETURN
			{
				key = VIR_RETURN;
				return;
			}
			else if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 30 && m.y<YSIZE / 3 + 60)//���ѡ�����¿�ʼ�����򷵻�VIR_RESTART
			{
				key = VIR_RESTART;
				return;
			}
			else if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 60 && m.y<YSIZE / 3 + 90)//���ѡ�����˵������򷵻�VIR_HOME
			{
				key = VIR_HOME;
				return;
			}
			else if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 90 && m.y<YSIZE / 3 + 120)//���ѡ�����˵������򷵻�VIR_HOME
			{
				FILE *fp=NULL;
				fopen_s(&fp ,"gameRecord.dat", "w");
				fprintf_s(fp, "%d",world );
				fclose(fp);
				key = VIR_RETURN;
				return;
			}

		case WM_MOUSEMOVE: //�ƶ�����
			RECT r;
			int i;
			for (i = 0; i<4; i++)	//�൱�����»���һ�� �ò�ͬ����ɫͻ��
			{
				//������ƶ���������ʱ
				if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + i * 30 && m.y<YSIZE / 3 + 30 + i * 30)
				{
					r.left = XSIZE / 2 - 45;
					r.top = YSIZE / 3 + i * 30;
					r.right = XSIZE / 2 + 45;
					r.bottom = YSIZE / 3 + 30 + i * 30;
					POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
					setfillcolor(BLUE);
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
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
						drawtext("Write Dat", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
						switch (i)
						{
						case 0:
							drawtext("������Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 1:
							drawtext("����һ��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
							drawtext("����ؼ�", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 3:
							drawtext("����浵", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					FlushBatchDraw();
				}
			}
		}
	}
}

int control::getKey() //��ȡ����
{
	if (_kbhit())
	{
		key = GetCommand();
	}
	if (key&CMD_ESC) //����Esc��ʱ������ͣ�˵�
	{
		pauseClick();
	}
	return key;
}
void control::gameStart() //����ʱ�Ŀ�ʼ����
{
	cleardevice(); //����
	settextstyle(40, 0, "Gill Sans");
	RECT r1 = { 0, 0, XSIZE, YSIZE / 3 };
	drawtext("���������v1.0", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//������(ͬʱҲ�ǽ���1)
	settextstyle(20, 0, "Agency FB");
	RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 }; rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
	drawtext("��ʼ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	drawtext("����", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
	drawtext("ָ��", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5 = { XSIZE / 2 - 45,YSIZE / 3 + 90,XSIZE / 2 + 45,YSIZE / 3 + 120 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 90, XSIZE / 2 + 45, YSIZE / 3 + 120);
	drawtext("�˳�", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r6 = { XSIZE / 2 - 45,YSIZE / 3 + 120,XSIZE / 2 + 45,YSIZE / 3 + 150 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 120, XSIZE / 2 + 45, YSIZE / 3 + 150);
	drawtext("����", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	bool _HOME = true, _INTRODUCTION = false, _OPERATION = false,_READ=false; //true��ʾ���ڵ�ǰҳ�� UI��������

	MOUSEMSG m;
	while (_HOME) //���ڽ���1ʱ��UI����
	{
		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN: //���ѡ��
			EndBatchDraw();
			if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 && m.y<YSIZE / 3 + 30 && _HOME == 1 && _INTRODUCTION == 0 && _OPERATION == 0)//���ѡ�񡰿�ʼ��Ϸ��
			{
				_HOME = false;
				break;
			}
			else if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 30 && m.y<YSIZE / 3 + 60 && _HOME == 1 && _OPERATION == 0)//���ѡ����Ϸ���ܡ�
			{
				_INTRODUCTION = true;	//����2�Ļ���
				cleardevice();
				rectangle(50, 50, 213, 220);
				outtextxy(52, 52, "��Ϸ���ܣ�");
				outtextxy(52, 82, "����һ���������Ϸ");
				outtextxy(52, 102, "���ǽ�è���");
				outtextxy(52, 132, "��Ϸ�����ߣ�");
				outtextxy(52, 152, "���Ĳ�");
				RECT R1 = { XSIZE - 46,YSIZE - 26,XSIZE - 2,YSIZE - 2 }; rectangle(XSIZE - 46, YSIZE - 26, XSIZE - 2, YSIZE - 2);
				drawtext("����", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 60 && m.y<YSIZE / 3 + 90 && _HOME == 1 && _INTRODUCTION == 0)//���ѡ�񡰲���˵����
			{
				_OPERATION = true;	//����3�Ļ���
				cleardevice();
				rectangle(50, 50, 213, 220);
				outtextxy(52, 52, "Introduction��");
				outtextxy(52, 72, "move LEFT��A��");
				outtextxy(52, 92, "move RIGHT��D��");
				outtextxy(52, 112, "Fire��J��");
				outtextxy(52, 132, "Jump��W��/K��");
				outtextxy(52, 152, "Pause��Esc��");
				RECT R2 = { XSIZE - 46,YSIZE - 26,XSIZE - 2,YSIZE - 2 }; rectangle(XSIZE - 46, YSIZE - 26, XSIZE - 2, YSIZE - 2);
				drawtext("����", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 90 && m.y<YSIZE / 3 + 120 && _HOME == 1 && _INTRODUCTION == 0 && _OPERATION == 0)//���ѡ���˳���Ϸ��
				exit(0);
			else if (m.x>XSIZE - 46 && m.x<XSIZE - 3 && m.y>YSIZE - 26 && m.y<YSIZE - 3 && (_INTRODUCTION == 1 || _OPERATION == 1))//���ѡ�񡰷��ء�
			{
				cleardevice();
				_HOME = false, _INTRODUCTION = false, _OPERATION = false;
				gameStart();
			}
			else if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 120 && m.y<YSIZE / 3 + 150 && _HOME == 1 && _INTRODUCTION == 0 && _OPERATION == 0) //���ѡ��"��ȡ�浵"
			{
				//�����ڴ˼���
				FILE *fp;
				int flag;
				fopen_s(&fp, "gameRecord.dat","r");
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
		case WM_MOUSEMOVE:	//������ʾ
			RECT r;
			if (_INTRODUCTION == 1 || _OPERATION == 1)
			{
				if (m.x>XSIZE - 46 && m.x<XSIZE - 3 && m.y>YSIZE - 26 && m.y<YSIZE - 3)
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
				for (int i = 0; i<5; i++)
				{
					if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + i * 30 && m.y<YSIZE / 3 + 30 + i * 30)
					{
						r.left = XSIZE / 2 - 45;
						r.top = YSIZE / 3 + i * 30;
						r.right = XSIZE / 2 + 45;
						r.bottom = YSIZE / 3 + 30 + i * 30;
						POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
						setfillcolor(RED);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						switch (i)
						{
						case 0:
							drawtext("Start game", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 1:
							drawtext("Introduction", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
							drawtext("directions", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 3:
							drawtext("Exit", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 4:
							drawtext("Read", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					else
					{
						if (getpixel(XSIZE / 2 - 45 + 1, YSIZE / 3 + i * 30 + 1) == RED)
						{
							r.left = XSIZE / 2 - 45;
							r.top = YSIZE / 3 + i * 30;
							r.right = XSIZE / 2 + 45;
							r.bottom = YSIZE / 3 + 30 + i * 30;
							POINT points[4] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
							setfillcolor(BLACK);
							fillpolygon(points, 4);
							setbkmode(TRANSPARENT);
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
void control::showScore(int score) //��ʾ����
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
void control::showLevel(int level) //��ʾ�ؿ�
{
	settextstyle(0, 0, "Cooper");
	char s1[20] = "�ؿ�:  ";
	char s2[2];
	_itoa_s(level, s2, 10);	//ͬ��
	strcat_s(s1, s2);	
	setbkmode(TRANSPARENT);	//�ұ���ʾ
	outtextxy(XSIZE - 90, 10, s1);
	setbkmode(OPAQUE);
}
void control::showDied(int life) //��������ʱ�Ķ��� ��������ֵ
{
	settextstyle(0, 0, "Goudy Stout");
	cleardevice();
	IMAGE img_hero;
	loadimage(&img_hero, "res\\role.bmp");
	putimage(XSIZE / 2 - 65, YSIZE / 2 - 30,  WIDTH,  HEIGHT, &img_hero, 2 * WIDTH, 0, SRCPAINT);
	settextstyle(30, 0, "Gill Sans");
	char s2[2];
	_itoa_s(life, s2, 10);
	outtextxy(XSIZE / 2 - 20, YSIZE / 2 - 30, 'X');
	outtextxy(XSIZE / 2 + 20, YSIZE / 2 - 30,  s2);
	Sleep(2000);
}
void control::showGameOver() //��Ϸ����ʱ�Ķ���
{
	IMAGE img;
	loadimage(&img, "res\\home.bmp", XSIZE, 5 * YSIZE);
	putimage(0, -YSIZE, &img);
	Sleep(6500);
}
void control::showPassed(int world) //ͨ��ĳһ�صĻ���
{
	cleardevice();
	char s1[20] = "LEVEL:  ";
	char s2[2];
	_itoa_s(world, s2, 10);
	outtextxy(XSIZE / 2 - 20, YSIZE / 3, s1);
	outtextxy(XSIZE / 2, YSIZE / 2 - 20, s2);
	Sleep(2000);
}
void control::showPassedAll() //ͨ�����еĶ���
{
	IMAGE img;
	loadimage(&img, "res\\home.bmp", XSIZE, 5 * YSIZE);
	putimage(0, -3 * YSIZE, &img);
	Sleep(7800);
}
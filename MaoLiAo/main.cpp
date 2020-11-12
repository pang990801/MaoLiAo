#include"graphics.h"
#include"conio.h"
#include"stdio.h"

#include"MyTimer.h"
#include"mydefine.h"
#include"control.h"
#include"role.h"
#include"scene.h"
#pragma comment(lib,"Winmm.lib")   //����Ϸ�������Ҫ�õ���

//ȫ�ֱ���
int life = LIFE;
int world = 1;

int main()
{
	initgraph(XSIZE, YSIZE);

	HWND hwnd = GetHWnd();	//��ȡ���ھ��
	SetWindowText(hwnd, "è���");

	control myCtrl;        //����һ����Ϸ����
	myCtrl.gameStart();//��Ϸ�Ŀ�ʼ����

	role myRole(world);    //�����ɫ
	scene myScene(world);  //������Ϸ����

					   //�����Ϸ����
	mciSendString("open res\\��������.mp3 alias music_bg", NULL, 0, NULL);
	mciSendString("open res\\ʤ��.mp3 alias music_win", NULL, 0, NULL);
	mciSendString("open res\\ͨ��.mp3 alias music_passedAll", NULL, 0, NULL);
	mciSendString("open res\\��Ϸ����.mp3 alias music_end", NULL, 0, NULL);
	mciSendString("play music_bg repeat", NULL, 0, NULL);

	myTimer mytimer;//��ȷ�ӳ�

	while (1)
	{
		int key = myCtrl.getKey(); //��ȡ��Ұ��µļ�                              
		if (key == VIR_RESTART)     //�����Ϸ������ѡ���ˡ����¿�ʼ��
		{
			myScene = scene(world); mciSendString("play music_bg from 0", NULL, 0, NULL);
			myRole = role(world);
		}
		else if (key == VIR_HOME)   //�����Ϸ������ѡ���ˡ����˵���
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			life = LIFE;
			world = 1;
			myCtrl.gameStart();
			myRole = role(world);
			myScene = scene(world);
			mciSendString("play music_bg from 0", NULL, 0, NULL);
		}

		myRole.action(key, &myScene);

		myScene.action(&myRole);

		if (myRole.isDied())     //�����������
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			BeginBatchDraw();
			myScene.show();
			myRole.show();
			myCtrl.showScore(myRole.getScore());
			myCtrl.showLevel(world);
			EndBatchDraw();

			mytimer.Sleep(3500);
			life--;
			if (life == 0)
			{
				mciSendString("play music_end from 0", NULL, 0, NULL);
				myCtrl.showGameOver();
				life = LIFE;
				world = 1;
				myCtrl.gameStart();
				myRole = role(world);
				myScene = scene(world);
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
			else
			{
				myCtrl.showDied(life);
				myRole = role(world);
				myScene = scene(world);
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
		}
		if (myRole.isPassed())   //������ǹ���
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			if (world == 3)//�������ͨ��
			{
				mciSendString("play music_win from 0", NULL, 0, NULL);
				mytimer.Sleep(6500);
				mciSendString("play music_passedAll from 0", NULL, 0, NULL);
				myCtrl.showPassedAll();
				life = LIFE;
				world = 1;
				myRole = role(world);
				myScene = scene(world);
				myCtrl.gameStart();
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
			else
			{
				mciSendString("play music_win from 0", NULL, 0, NULL);
				mytimer.Sleep(6500);
				world++;
				myCtrl.showPassed(world);
				myRole = role(world);
				myScene = scene(world);
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
		}


		//��ʾ����
		BeginBatchDraw();
		myScene.show();
		myRole.show();
		myCtrl.showScore(myRole.getScore());
		myCtrl.showLevel(world);
		EndBatchDraw();

		//�ӳ�
		mytimer.Sleep((int)(TIME * 1000));
	}

	mciSendString("close all", NULL, 0, NULL);//�ر����ж�ý�������ļ�
	closegraph();
}

/*void writeRecordFile(control myCon,role myRole,scene myScene)	//�浵
{
	FILE *fp;
	fp = fopen_s(".\\gameRecord.dat", "w");
//	fprintf_s(fp, "", );
	fclose(fp);
}*/

/*void readRecordFile(control myCon, role myRole, scene myScene)	//����
{
	FILE *fp;
	fp = fopen_s(".\\gameRecord.dat", "r");
//	fscanf_s(fp, "", );
	fclose(fp);
}*/
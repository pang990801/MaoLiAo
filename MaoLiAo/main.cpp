#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include"timer.h"
#include"define.h"
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

	//��ȡ���ھ��
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "è��� V2.0");

	//��Ϸ����gameCtrl
	Control gameCtrl;
	gameCtrl.gameStart();//��Ϸ�Ŀ�ʼ����

	//��ɫgameRole
	Role gameRole(world);

	//��Ϸ����gameScene
	Scene gameScene(world);

	//�����Ϸ����
	mciSendString("open res\\��������.mp3 alias music_bg", NULL, 0, NULL);
	mciSendString("open res\\ʤ��.mp3 alias music_win", NULL, 0, NULL);
	mciSendString("open res\\ͨ��.mp3 alias music_passedAll", NULL, 0, NULL);
	mciSendString("open res\\��Ϸ����.mp3 alias music_end", NULL, 0, NULL);
	mciSendString("play music_bg repeat", NULL, 0, NULL);

	Timer gameTimer;//��ȷ�ӳ�

	while (true)
	{
		int key = gameCtrl.getKey();	//��ȡ��Ұ��µļ�                              
		if (key == VIR_RESTART)			//�����Ϸ������ѡ���ˡ����¿�ʼ��
		{
			gameScene = Scene(world); mciSendString("play music_bg from 0", NULL, 0, NULL);
			gameRole = Role(world);
		}
		else if (key == VIR_HOME)		//�����Ϸ������ѡ���ˡ����˵���
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			life = LIFE;
			world = 1;
			gameCtrl.gameStart();
			gameRole = Role(world);
			gameScene = Scene(world);
			mciSendString("play music_bg from 0", NULL, 0, NULL);
		}

		gameRole.action(key, &gameScene, world);

		gameScene.action(&gameRole);

		if (gameRole.isDied())     //�����������
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			BeginBatchDraw();
			gameScene.show();
			gameRole.show();
			gameCtrl.showScore(gameRole.getScore());
			gameCtrl.showLevel(world);
			EndBatchDraw();

			gameTimer.Sleep(3500);
			life--;
			if (life == 0)
			{
				mciSendString("play music_end from 0", NULL, 0, NULL);
				gameCtrl.showGameOver();
				life = LIFE;
				world = 1;
				gameCtrl.gameStart();
				gameRole = Role(world);
				gameScene = Scene(world);
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
			else
			{
				gameCtrl.showDied(life);
				gameRole = Role(world);
				gameScene = Scene(world);
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
		}
		if (gameRole.isPassed())   //������ǹ���
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			if (world == 3)//�������ͨ��
			{
				mciSendString("play music_win from 0", NULL, 0, NULL);
				gameTimer.Sleep(6500);
				mciSendString("play music_passedAll from 0", NULL, 0, NULL);
				gameCtrl.showPassedAll();
				life = LIFE;
				world = 1;
				gameRole = Role(world);
				gameScene = Scene(world);
				gameCtrl.gameStart();
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
			else
			{
				mciSendString("play music_win from 0", NULL, 0, NULL);
				gameTimer.Sleep(6500);
				world++;
				gameCtrl.showPassed(world);
				gameRole = Role(world);
				gameScene = Scene(world);
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
		}


		//��ʾ����
		BeginBatchDraw();
		gameScene.show();
		gameRole.show();
		gameCtrl.showScore(gameRole.getScore());
		gameCtrl.showLevel(world);
		EndBatchDraw();

		//�ӳ�
		gameTimer.Sleep((int)(TIME * 1000));
	}

	mciSendString("close all", NULL, 0, NULL);//�ر����ж�ý�������ļ�
	closegraph();
}
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include"timer.h"
#include"define.h"
#include"control.h"
#include"role.h"
#include"scene.h"
#pragma comment(lib,"Winmm.lib")   //给游戏添加音乐要用到它

//全局保存
int life = LIFE;
int world = 1;

int main()
{
	initgraph(XSIZE, YSIZE);

	//获取窗口句柄
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "猫里奥 V2.0");

	//游戏控制gameCtrl
	Control gameCtrl;
	gameCtrl.gameStart();//游戏的开始界面

	//角色gameRole
	Role gameRole(world);

	//游戏场景gameScene
	Scene gameScene(world);

	//添加游戏音乐
	mciSendString("open res\\背景音乐.mp3 alias music_bg", NULL, 0, NULL);
	mciSendString("open res\\胜利.mp3 alias music_win", NULL, 0, NULL);
	mciSendString("open res\\通关.mp3 alias music_passedAll", NULL, 0, NULL);
	mciSendString("open res\\游戏结束.mp3 alias music_end", NULL, 0, NULL);
	mciSendString("play music_bg repeat", NULL, 0, NULL);

	Timer gameTimer;//精确延迟

	while (true)
	{
		int key = gameCtrl.getKey();	//获取玩家按下的键                              
		if (key == VIR_RESTART)			//如果游戏过程中选择了“重新开始”
		{
			gameScene = Scene(world); mciSendString("play music_bg from 0", NULL, 0, NULL);
			gameRole = Role(world);
		}
		else if (key == VIR_HOME)		//如果游戏过程中选择了“主菜单”
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

		if (gameRole.isDied())     //如果主角死亡
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
		if (gameRole.isPassed())   //如果主角过关
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			if (world == 3)//如果主角通关
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


		//显示画面
		BeginBatchDraw();
		gameScene.show();
		gameRole.show();
		gameCtrl.showScore(gameRole.getScore());
		gameCtrl.showLevel(world);
		EndBatchDraw();

		//延迟
		gameTimer.Sleep((int)(TIME * 1000));
	}

	mciSendString("close all", NULL, 0, NULL);//关闭所有多媒体音乐文件
	closegraph();
}
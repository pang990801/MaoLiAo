#pragma once						//避免include同一头文件多次
#include<graphics.h>

class Control						//鼠标 键盘控制类
{
private:
	int key;
private:
	int GetCommand();
	void pauseClick();
public:
	Control(void);
	~Control(void);
	int getKey();					//获取键盘
	void gameStart();				//进入时的开始界面
	void showScore(int score);		//显示分数
	void showLevel(int level);		//显示关卡
	void showDied(int life);		//主角死亡时的动画
	void showGameOver();			//游戏结束时的动画
	void showPassed(int world);		//通过某一关的画面
	void showPassedAll();			//通关所有的动画
	IMAGE img_bg;
};

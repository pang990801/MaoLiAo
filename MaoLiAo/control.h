#pragma once						//����includeͬһͷ�ļ����
#include<graphics.h>

class Control						//��� ���̿�����
{
private:
	int key;
private:
	int GetCommand();
	void pauseClick();
public:
	Control(void);
	~Control(void);
	int getKey();					//��ȡ����
	void gameStart();				//����ʱ�Ŀ�ʼ����
	void showScore(int score);		//��ʾ����
	void showLevel(int level);		//��ʾ�ؿ�
	void showDied(int life);		//��������ʱ�Ķ���
	void showGameOver();			//��Ϸ����ʱ�Ķ���
	void showPassed(int world);		//ͨ��ĳһ�صĻ���
	void showPassedAll();			//ͨ�����еĶ���
	IMAGE img_bg;
};

#pragma once
#include<graphics.h>
#include"define.h"

const int MAP_NUMBER = 30;	//
const int COINS_NUMBER = 70; //Ӳ������
const int SCORE_NUMBER = 5;		//����
const int FOOD_NUMBER = 5;	//Ģ����

class Role;//��ǰ˵�������Ա����ظ�����ͷ�ļ���
//��Ϊmap���а���role������ݳ�Ա��ʹ�����ַ�ʽ��������ѭ��
//ֻ����������������ָ�������Ӧ�� 
//���������������������ߺ����ı�����

#ifndef _MAP	//�ú궨��ʵ���Զ�������
#define _MAP
struct Map//��ͼ�Ľṹ�� //���ŵ�ͼ���ɹؿ�
{
	int x;
	int y;
	int id;
	int xAmount;//������ռ��ͼ��ĸ���	 ���������ײ��
	int yAmount;//������ռ��ͼ��ĸ���   ���������ײ��
	double u;//Ħ������
};
#endif
class Scene
{
private:
	double xBg;//��������
	double yBg;
	int xMap;//��ͼ����
	int yMap;
	Map map[MAP_NUMBER];	//��������������
	POINT coins[COINS_NUMBER];
	POINT score[SCORE_NUMBER];
	POINT food[FOOD_NUMBER];
	IMAGE img_bg;
	IMAGE img_map;
	IMAGE img_scenery;
	IMAGE img_coin;
	IMAGE img_food;
	double scenery_iframe;//֡��
	double coin_iframe;
	double score_iframe[SCORE_NUMBER];
	double food_iframe;
	int world;//��world��
public:
	Scene(int world);
	~Scene(void);
	Map* getMap() { return map; }
	POINT* getCoins() { return coins; }
	POINT* getFood() { return food; }
	void setScorePos(int x, int y);
	void setFood(int x, int y);
	void createMap(int world);//�����world�صĵ�ͼ	
	void createCoin();
	void createFood();
	void action(Role* myRole);
	void show();
	bool isEnding(int distance);
};
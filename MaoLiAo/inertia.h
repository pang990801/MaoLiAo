#pragma once
#include"graphics.h"
#include"mydefine.h"
#include"scene.h"

class inertia	//������
{
	inertia(void);
	~inertia(void);
public:
	static double move(double& v, double t, double a);	//����ϵλ�Ƽ���
}; 

#pragma once
#include<graphics.h>
#include"define.h"
#include"scene.h"

class Inertia											//������
{
	Inertia(void);
	~Inertia(void);
public:
	static double move(double& v, double t, double a);	//����ϵλ�Ƽ���
};

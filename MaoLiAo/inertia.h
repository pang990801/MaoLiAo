#pragma once
#include<graphics.h>
#include"define.h"
#include"scene.h"

class CInertia											//������
{
	CInertia(void);
	~CInertia(void);
public:
	static double move(double& v, double t, double a);	//����ϵλ�Ƽ���
};

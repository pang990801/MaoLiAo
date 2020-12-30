#pragma once
#include<graphics.h>
#include"define.h"
#include"scene.h"

class CInertia											//惯性类
{
	CInertia(void);
	~CInertia(void);
public:
	static double move(double& v, double t, double a);	//惯性系位移计算
};

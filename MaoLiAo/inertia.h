#pragma once
#include<graphics.h>
#include"define.h"
#include"scene.h"

class Inertia											//惯性类
{
	Inertia(void);
	~Inertia(void);
public:
	static double move(double& v, double t, double a);	//惯性系位移计算
};

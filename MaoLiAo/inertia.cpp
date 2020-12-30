#pragma once

#include<math.h>
#include"inertia.h"

Inertia::Inertia(void)
{}

Inertia::~Inertia(void)
{}

double Inertia::move(double& v, double t, double a)	//计算移动距离
{
	//声明位移量
	double X = 0;
	X = v * t + 1.0 / 2.0 * a * t * t;
	v = v + a * t;
	return X;
}
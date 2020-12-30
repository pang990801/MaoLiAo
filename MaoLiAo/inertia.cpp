#pragma once

#include<math.h>
#include"inertia.h"

CInertia::CInertia(void)
{}

CInertia::~CInertia(void)
{}

double CInertia::move(double& v, double t, double a)	//º∆À„“∆∂Øæ‡¿Î
{
	double X = 0;
	X = v * t + 1.0 / 2.0 * a * pow(t, 2);
	v = v + a * t;
	return X;
}
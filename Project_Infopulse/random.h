#include "stdafx.h"
#pragma once

class CRandom
{
private:
	int m_max;
public:
	CRandom();
	void Reinit(int max);
	int Get();
};
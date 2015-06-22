#include "stdafx.h"
#include "random.h"

#define BOARD_CELL_MAX (64)


CRandom::CRandom()
{
	Reinit(INT_MAX);
}

void CRandom::Reinit(int max)
{
	m_max = max;
	srand((unsigned)time(NULL));
}

int CRandom::Get()
{
	return rand() % m_max;
}

#pragma once

#include "KnightStep.h"
#include "SingleList.h"
#include "GlobalConst.h"
#include "ChessBoard.h"

class KnightStep : public Node
{
private:

	PathElement		m_Point;
	List			m_possibleMoves;
	static ChessBoard*	s_pChessBoard;

	bool isMovePossible(PathElement point)
	{
		if (point.getX() >= 0 && point.getX() < MAX_ROW_SIZE && point.getY() >= 0 && point.getY() < MAX_COLUMN_SIZE)
		{
			if (!s_pChessBoard)
				return false;
			else if (!s_pChessBoard->traversed(point.getX(), point.getY())) 
				return true;
			else
				return false;
		}
		else
		{
			return false;
		}
	}
public:
	static void setChessBoard(ChessBoard* pChessBoard)
	{
		s_pChessBoard = pChessBoard;
	}
	KnightStep()
	{
		m_Point.setX(0);
		m_Point.setY(0);
	};

	KnightStep(int x, int y)
	{
		m_Point.setX(x);
		m_Point.setY(y);
	};
	KnightStep(const PathElement& el)
	{
		m_Point.setX(el.getX());
		m_Point.setY(el.getY());
	}
	int getX() const
	{
		return m_Point.getX();
	}
	int getY() const
	{
		return m_Point.getY();
	}

	List* fillPossibleMoves()
	{
		// PathElement aPossibleMoves[] = { { 2, -1 }, { 2, 1 }, { -2, -1 }, { -2, 1 }, { 1, -2 }, { 1, 2 }, { -1, -2 }, { -1, -2 } };
		struct Moves 
		{
			int x; 
			int y;
		} moves[] = { { 2, -1 }, { 2, 1 }, { -2, -1 }, { -2, 1 }, { 1, -2 }, { 1, 2 }, { -1, -2 }, { -1, -2 } };
		
		PathElement aPossibleMoves[sizeof(moves)/sizeof(moves[0])];
		for (int i = 0; i < (sizeof(aPossibleMoves) / sizeof(aPossibleMoves[0])); i++)
		{
			aPossibleMoves[i].setX(moves[i].x);
			aPossibleMoves[i].setY(moves[i].y);
		}

		for (int i = 0; i < (sizeof(aPossibleMoves) / sizeof(aPossibleMoves[0])); i++)
		{
			PathElement* temp = new PathElement(m_Point.getX() + aPossibleMoves[i].getX(), m_Point.getY() + aPossibleMoves[i].getY());
			if (!temp)
			{
				return NULL;
			}

			if (isMovePossible(*temp))
			{
				if (!m_possibleMoves.insert(m_possibleMoves.head(), temp))
				{
					return NULL;
				}
			}
		}
		return &m_possibleMoves;
	}
	
};


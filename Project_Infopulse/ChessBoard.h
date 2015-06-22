#pragma once

#include "SingleList.h"
#include "GlobalConst.h"


typedef enum { EnumEmpty = 0, EnumFriendChess, EnumKnight, EnumKing } EnumChessType;

struct Cell
{
	EnumChessType	m_chessType;
	bool			m_traversed;

	Cell() : m_chessType(EnumEmpty), m_traversed(false) {};
	Cell(EnumChessType chessType, bool traversed = false) : m_chessType(chessType), m_traversed(traversed) {};
};

class ChessBoard
{

private:

	Cell*		m_chessList;
	List		m_currentPath;

	void remove()
	{
		delete[] m_chessList;
		m_chessList = NULL;
	}
	void checkInitiated()
	{
		if (!m_chessList)
		{
			throw std::bad_exception();
		}
	}
	
public:
	typedef enum { EnumManualMethod = 0, EnumRandomMethod, EnumReadFileMethod, EnumMaxMethod } EnumMethod;
	
	ChessBoard()
	{
		m_chessList = NULL;
	}
	~ChessBoard()
	{
		remove();
	}

	bool create()
	{
		Cell* pChesslist = new Cell[MAX_ROW_SIZE*MAX_COLUMN_SIZE];
		if (pChesslist)
		{
			memset(pChesslist, 0, sizeof(Cell) * MAX_ROW_SIZE * MAX_COLUMN_SIZE);
			delete [] m_chessList;
			m_chessList = pChesslist;
			return true;
		}
		return false;
	}

	Cell get(int i, int j)
	{
		if (!m_chessList)
		{
			throw std::bad_exception();
		}
		return m_chessList[i*MAX_ROW_SIZE + j];
	}
	void set(int i, int j, Cell value)
	{
		m_chessList[i*MAX_ROW_SIZE + j]= value;
	}

	void choice(int methodNumber);
	bool isRange(int x, int y)
	{
		if (x >= 0 && x < MAX_ROW_SIZE && y >= 0 && y < MAX_COLUMN_SIZE)
		{
			return true;
		}
		else 
		{
			return false; 
		}
	}

	void setTraversed(int i, int j, bool traverseState)
	{
		if (isRange(i, j))
		{
			m_chessList[i*MAX_ROW_SIZE + j].m_traversed = traverseState;
		}
		else
		{
			throw std::bad_exception();
		}
	}

	bool traversed(int i, int j)
	{
		if (isRange(i,j))
		{
			return m_chessList[i*MAX_ROW_SIZE + j].m_traversed;
		}
		else
		{
			throw std::bad_exception();
		}
	}
	
	bool fillRandomly();
	bool fillFromFile();
	bool fillFromKeyboard();

	bool getKnight(int& x, int& y);
	bool getKing(int& x, int& y);

	
	List* findSolution();
	void print ();

private:

	bool getPiece(EnumChessType chessType, int& x, int& y);
};
std::istream& operator>>(std::istream& is, EnumChessType& chessType);
std::ostream& operator<<(std::ostream& os, PathElement& elem);




#include "stdafx.h"

#include "ChessBoard.h"
#include "KnightStep.h"
#include "random.h"
#include "SingleList.h"


void ChessBoard::choice(int methodNumber)
{
	switch (methodNumber)
	{
	case EnumManualMethod: ChessBoard::fillRandomly();
		break;
	case EnumRandomMethod: ChessBoard::fillFromFile();
		break;
	case EnumReadFileMethod: ChessBoard::fillFromKeyboard();
		break;
	default: break;
	};
}

bool  ChessBoard::fillFromFile()
{
	create();
	checkInitiated();
	std::fstream fIn;
	int knightCounter = 0;
	int kingCounter = 0;
	int FriendChessCounter = 0;
	fIn.open("chessboard.txt");
	std::cout << "1) Выбран метод чтение из файла" << std::endl;
	if (!fIn.is_open())
	{
		std::cout << "Ошибка чтения файла! Повторите попытку ввода файла!" << std::endl;
	}
	while (!fIn.eof())
	{
		for (int i = 0; i < MAX_COLUMN_SIZE; i++)
		{
			for (int j = 0; j < MAX_ROW_SIZE; j++)
			{
				fIn >> m_chessList[i*MAX_ROW_SIZE + j].m_chessType;
				if (get(i, j).m_chessType <= MAX_METHOD_NUMBER)
				{
					if (get(i, j).m_chessType == EnumKnight)
					{
						if (!knightCounter)
						{
							knightCounter++;
						}
						else
						{
							std::cout << "Превышено количество фигур: Конь! Исправьте исходный файл и запустите программу заново!" << std::endl;
							std::cout << "Элемент  [" << i << ", " << j << "] введен не правильно" << std::endl;
						}
					}
					else if (get(i, j).m_chessType == EnumKing)
					{
						if (!kingCounter)
						{
							kingCounter++;
						}
						else
						{
							std::cout << "Превышено количество фигур: Король! Исправьте исходный файл и запустите программу заново!" << std::endl;
							std::cout << "Элемент  [" << i << ", " << j << "] введен не правильно" << std::endl;
							return false;
						}
					}
					else if (get(i, j).m_chessType == EnumFriendChess)
					{
						
						if (FriendChessCounter < MAX_FRIENDS_VALUE)
						{
							FriendChessCounter++;
						}
						else
						{
							std::cout << "Превышено количество фигур: Дружественная фигура.Исправьте исходный файл и запустите программу заново!" << std::endl;
							std::cout << "Элемент  [" << i << ", " << j << "] введен не правильно" << std::endl;
							return false;
						}
					}
					
				}
			}
		};
		if (knightCounter == 0)
		{
			std::cout << "Вами не введены необходимые данные (конь)! Проверьте документ и повторите попытку!" << std::endl;
			return false;
		}
		else if (kingCounter == 0)
		{
			std::cout << "Вами не введены необходимые данные (король)! Проверьте документ и повторите попытку!" << std::endl;
			return false;
		}
	};
	return true;
}

bool  ChessBoard::fillFromKeyboard()
{
	create();
	checkInitiated();

	int chessValue = 0;
	int x = 0;
	int y = 0;

	std::cout << "2) Выбран метод ввода с клавиатуры" << std::endl;
	std::cout << "Введите количество фигур:(Не более " << MAX_VALUE_CHESS << " и не менее " << MIN_NEEDED_CHESS << ")"<< std::endl;

	std::cin >> chessValue;

	while (chessValue < MIN_NEEDED_CHESS || chessValue > MAX_VALUE_CHESS)
	{
		std::cout << "Неправильное количество фигур! Повторите ввод!" << std::endl;
		std::cin >> chessValue;
	}
	if (chessValue <= MAX_VALUE_CHESS)
	{
		std::cout << "Введите расположение фигуры и тип фигуры:\n(координаты х и у)";
		std::cout << "(1 - союзные фигуры, 2 - конь, 3 - король)" << std::endl;

		EnumChessType typeFigure = EnumEmpty;
		int count = 0;
		do
		{
			std::cout << "Фигура № " << count + 1;
			std::cout << "\nX:";
			std::cin >> x;
			std::cout << "Y:";
			std::cin >> y;

			if (isRange(x, y) && get(x, y).m_chessType == 0)
			{
				do
				{
					std::cout << "Тип фигуры: ";
					std::cin >> typeFigure;
					

					static int knightCounter = 0;
					static int kingCounter = 0;
					static int friendCounter = 0;

					if (typeFigure == EnumKnight)
					{
						if (knightCounter == 0)
						{
							knightCounter++;
							break;
						}
						else
						{
							std::cout << "Превышено количество фигур: Конь" << std::endl;
							continue;
						}
					}
					else if (typeFigure == EnumKing)
					{
						if (kingCounter == 0)
						{
							kingCounter++;
							break;
						}
						else
						{
							std::cout << "Превышено количество фигур: Король" << std::endl;
							continue;
						}
					}
					else if (typeFigure == EnumFriendChess)
					{
						if (friendCounter < (chessValue - MIN_NEEDED_CHESS))
						{
							friendCounter++;
							break;
						}
						else
						{
							std::cout << "Превышено количество фигур: Дружественная фигура" << std::endl;
							continue;
						}
					}
					else
					{
						std::cout << "Неправильный тип" << std::endl;
						continue;
					}

				} while (true);
				set(x, y, Cell(typeFigure));
				count++;
			}
			else
			{
				std::cout << "Ячейка занята!" << std::endl;
			}
			std::cout << "**********************" << std::endl;
			
		} while (count < chessValue);
	}
	return true;
}

bool ChessBoard::fillRandomly()
{
	int chessValue = 0;
	create();
	checkInitiated();

	std::cout << "0) Выбран метод случайного размещения фигур " << std::endl;
	std::cout << "Введите количество фигур:(Не более " << MAX_VALUE_CHESS << " и не менее " << MIN_NEEDED_CHESS << ")" << std::endl;

	std::cin >> chessValue;

	while (chessValue < MIN_NEEDED_CHESS || chessValue > MAX_VALUE_CHESS)
	{
		std::cout << "Неправильное количество фигур! Повторите ввод!" << std::endl;
		std::cin >> chessValue;
	}
	if (chessValue <= MAX_VALUE_CHESS)
	{
		CRandom rnd;
		rnd.Reinit(MAX_ROW_SIZE*MAX_COLUMN_SIZE);
		int chessCounter = 0;

		for (int k = 0; k < chessValue; k++)
		{
			int number = 0;
			int tmp;
			static int knightCounter = 0;
			static int kingCounter = 0;
			static int friendCounter = 0;

			tmp = rnd.Get();
			while (tmp == number)
			{
				tmp = rnd.Get();
			}
			number = tmp;
			if (m_chessList[number].m_chessType == EnumEmpty)
			{
				if (knightCounter == 0)
				{
					m_chessList[number].m_chessType = EnumKnight;
					knightCounter++;
				}
				else if (kingCounter == 0)
				{
					m_chessList[number].m_chessType = EnumKing;
					kingCounter++;
				}
				else if (friendCounter < (chessValue - MIN_NEEDED_CHESS))
				{
					m_chessList[number].m_chessType = EnumFriendChess;
					friendCounter++;
				}

			}
		}
	}
	return true;
}

bool ChessBoard::getPiece(EnumChessType chessType, int& x, int& y)
{
	for (int i = 0; i < MAX_COLUMN_SIZE; i++)
	{
		for (int j = 0; j < MAX_COLUMN_SIZE; j++)
		{
			if (get(i, j).m_chessType == chessType)
			{
				//std::cout << get(i, j).m_chessType << std::endl;
				x = i;
				y = j;
				return true;
			}
		}
	}
	return false;
}

bool ChessBoard::getKnight(int& x, int& y)
{
	return getPiece(EnumKnight, x, y);
}

bool ChessBoard::getKing(int& x, int& y)
{
	return getPiece(EnumKing, x, y);
}

void ChessBoard::print()
{
	std::cout << "Вы ввели следующие размещение фигур: " << std::endl;
	for (int i = 0; i < MAX_COLUMN_SIZE; i++)
	{
		for (int j = 0; j < MAX_COLUMN_SIZE; j++)
		{
			std::cout << get(i, j).m_chessType;
		}
		std::cout << std::endl;
	}
}

List* ChessBoard::findSolution()
{
	int knightX = 0;
	int knightY = 0;
	if (!getKnight(knightX, knightY))
	{
		std::cout << "Ошибка! Не найдена фигура Конь!" << std::endl;
		return NULL;
	}

	int kingX = 0;
	int kingY = 0;
	if (!getKing(kingX, kingY))
	{
		std::cout << "Ошибка! Не найдена фигура Король!" << std::endl;
		return NULL;
	}

	List* pCurrentWayList = new List;
	List* pVictoryList = new List;
	KnightStep* pCurrentStep = new KnightStep(knightX, knightY);
	if (!pCurrentStep)
	{
		return NULL;
	}

	while (pCurrentStep)
	{
		List* list = pCurrentStep->fillPossibleMoves();
		if (!list)
		{
			return NULL;
		}

		PathElement* pCurrent = static_cast<PathElement*>(list->pop());
		if (!pCurrent)
		{
			pCurrentStep = static_cast<KnightStep*>(pCurrentWayList->pop());
			continue;
		} 
		else
		{
			KnightStep* pNextStep = new KnightStep(*pCurrent);
			if (!pNextStep)
			{
				return NULL;
			}

			if (pNextStep->getX() == kingX && pNextStep->getY() == kingY)
			{
				List* pVictoryWay = new List;
				if (!pVictoryWay)
				{
					return NULL;
				}
				pVictoryWay->setHead(NULL);
				Node* pCurrentNode = pCurrentWayList->head();
				Node* pPreviousNode = NULL;
				while (pCurrentNode)
				{
					if (pPreviousNode)
					{
						pVictoryWay->insert(pPreviousNode, pCurrentNode);
					}
					else
					{
						pVictoryWay->insert(pVictoryWay->head(), pCurrentNode);
					}
					pPreviousNode = pCurrentNode;
					pCurrentNode = pCurrentWayList->next(pCurrentNode);
				}
				// TODO: insert pNextStep step
				ListNode* pVictoryListNode = new ListNode(pVictoryWay);
				pVictoryList->push(pVictoryListNode);
			}
			else
			{
				if (pCurrentWayList->getSize() < MAX_WAY_SIZE)
				{
					pCurrentWayList->push(pCurrentStep);
					setTraversed(pCurrentStep->getX(), pCurrentStep->getY(), true);
					pCurrentStep = pNextStep;
				}
				else
				{
					pCurrentStep = static_cast<KnightStep*>(pCurrentWayList->pop());
				}
			}
		}
	}
	return pVictoryList;
}


std::istream& operator>>(std::istream& is, EnumChessType& chessType)
{
	int tmp;
	if (is >> tmp)
		chessType = static_cast<EnumChessType>(tmp);
	return is;
}
std::ostream& operator<<(std::ostream& os, PathElement& elem)
{
	os << "x: " << elem.getX() << " " << "y:" << elem.getY();
	return os;
}

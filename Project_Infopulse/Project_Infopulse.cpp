#include "stdafx.h"
#include "ChessBoard.h"
#include "KnightStep.h"
#include "random.h"
#include "SingleList.h"

std::istream& operator>>(std::istream& is, ChessBoard::EnumMethod& method)
{
	int tmp;
	if (is >> tmp)
		method = static_cast<ChessBoard::EnumMethod>(tmp);
	return is;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	try
	{
		ChessBoard chessBoard;

		ChessBoard::EnumMethod methodNumber;
		do
		{
			std::cout << "Выберите метод ввода:\n" << "(0 - использовать случайную растановку)\n"
				<< "(1 - прочитать из файла)\n" << "(2 - установить с клавиатуры" << std::endl;
			std::cin >> methodNumber;
			system("cls");
		} while (methodNumber >= ChessBoard::EnumMaxMethod);

		system("cls");

		chessBoard.choice(methodNumber);
		chessBoard.print();

		KnightStep::setChessBoard(&chessBoard);
		chessBoard.findSolution();
	}

	catch (std::exception& ex)
	{
		
		std::cout << "Fatal error: " << ex.what() << std::endl;
	}

	/*List list;
	for (int i = 0; i < 20; i++)
	{
		PathElement* pEl = new PathElement(i, i+1);
		if (pEl)
		{
			list.insert(list.head(), pEl);
		}
		
	}

	Node* pElem = list.head()->next();
	while (pElem)
	{
		PathElement* pPathEl = static_cast<PathElement*>(pElem);
		std::cout << *pPathEl << std::endl;
		pElem = pElem->next();
	}
	*/

 	return 0;
}


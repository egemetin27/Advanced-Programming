#include "egemetin_Metin_Ege_hw6_Board.h"



template<class Type>
Board<Type>::Board(const int & r, const int & c)
{
	row = r;
	col = c;
	myBoard = new boardNode<Type> *[row];
	for (int a = 0; a < row; a++)
	{
		myBoard[a] = new boardNode<Type> [col];
	}
}

template<class Type>
Board<Type>::~Board(void)
{
	for (int a = 0; a < row; a++)
	{
		delete [] myBoard[a];
	}
	delete [] myBoard;
}


template<class Type>
void Board<Type>::closeCard(const int & row, const int & col)
{
	myBoard[row][col].openness = false;
}


template<class Type>
void Board<Type>::displayBoard() const
{
	for (int a = 0; a < row; a++)
	{
		for (int b = 0; b < col; b++)
		{
			if (myBoard[a][b].openness == false) 
			{
				cout << "X";
			}
			else
			{
				cout << myBoard[a][b].value;
			}
		}
		cout << endl;
	}
}


template<class Type>
Type Board<Type>::getRow()
{
	return row;
}


template<class Type>
Type Board<Type>::getColumn()
{
	return col;
}


template<class Type>
void Board<Type>::readBoardFromFile(ifstream &inp)
{
	Type data;
	for (int a = 0; a < row; a++)
	{
		for (int b = 0; b < col; b++)
		{
			inp >> data;
			boardNode<Type> *temp = new boardNode<Type>(data);
			myBoard[a][b] = *temp;
		}
	}
}


template<class Type>
Type Board<Type>::returnValue(const int &rw, const int &cl)
{
	return myBoard[rw][cl].value;
}


template<class Type>
bool Board<Type>::isOpen(const int &rw, const int &cl) const
{
	if ( rw >= row || cl >= col || myBoard[rw][cl].openness == true )
	{
		return false;
	}
	return true;
}


template<class Type>
void Board<Type>::open(const int &rw, const int &cl)
{
	myBoard[rw][cl].openness = true;
}

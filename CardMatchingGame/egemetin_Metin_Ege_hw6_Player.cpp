#include "egemetin_Metin_Ege_hw6_Player.h"
#include "egemetin_Metin_Ege_hw6_Board.h"



template <class Type>
Player<Type>::Player(Board<Type> &userBoard) : myBoard(userBoard)
{
	score = 0;
}


template <class Type>
Player<Type>::~Player(void)
{
}


template <class Type>
Type Player<Type>::openCard(const int &row, const int &col)
{
	myBoard.open(row,col);
	return myBoard.returnValue(row,col);
}


template <class Type>
bool Player<Type>::validMove(const int &r, const int &c)
{
	return myBoard.isOpen(r,c);
}


template <class Type>
void Player<Type>::increaseNumberOfSuccess()
{
	score++;
}


template <class Type>
int Player<Type>::getNumberOfSuccess()
{
	return score;
}
#ifndef _PLAYER_H
#define _PLAYER_H


#include <iostream>

using namespace std;


template <class Type>
class Player
{
	public:
		Player(Board<Type>&);
		~Player(void);
		Type openCard(const int &, const int &);	// open the card on particular position and return the value
		bool validMove(const int &, const int &);	// checks the given coordinates are available to move
		void increaseNumberOfSuccess();				// increase score by 1
		int getNumberOfSuccess();		// returns the score
	private:
		int score;
		Board<Type> &myBoard;
};

#include "egemetin_Metin_Ege_hw6_Player.cpp"

#endif


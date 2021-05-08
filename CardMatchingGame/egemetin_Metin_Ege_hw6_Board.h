#ifndef _BOARD_H
#define _BOARD_H

#include <iostream>
#include <string>

using namespace std;


template<class Type>
struct boardNode 
{
	Type value;
	bool openness;
	boardNode()
	{}
	boardNode(const Type &val)
		: value(val), openness(false)
	{}
};


template<class Type>
class Board
{
	public:
		Board(const int &, const int &);
		~Board(void);
		void closeCard(const int &, const int &);
		void displayBoard() const;
		Type getRow(void);
		Type getColumn(void);
		void readBoardFromFile(ifstream &);
		Type returnValue(const int &, const int &);
		bool isOpen(const int &, const int &) const;
		void open(const int &, const int &);
	private:
		boardNode<Type> **myBoard;
		int row, col;
};

#include "egemetin_Metin_Ege_hw6_Board.cpp"

#endif


#include <iostream>
#include <string>
#include <fstream>
#include "egemetin_Metin_Ege_hw4_myclass.h"

using namespace std;


int main()
{
	string str, filename, line;
	int row, col, last_location;	
	cout << "Please enter the number of rows: ";
	cin >> row;
	cout << "Please enter the number of columns: ";
	cin >> col;
	cout << "Please enter the name of the input file that contains the matrix: ";
	ifstream input;
	cin >> filename;
	input.open(filename.c_str());
	while ( input.fail() ) {			// if file does not exist
		input.clear(); 
		cout << "File cannot be opened." << endl;
		cout << "Please enter the name of the input file again: ";
		cin >> filename;
		input.open(filename.c_str());
	}
	cout << endl << "Please enter a string of bits to search (CTRL+Z to quit): ";

	while ( cin >> str ) {
		myStack stack;
		int idx = 0;		// current idx of the string
		int str_len = str.length(), x = 0, y = 0;		// x = current row, y = current column
		int size = row * col;

		cellStruct *matrix = new cellStruct[size];			// 1d matrix (pseudo 2d)
		int count = 0;
		ifstream input;
		input.open(filename.c_str());
		while ( getline(input,line) ) {						// filling the matrix from txt input
			for ( int a = 0; a < col; a++ ) {
				matrix[count*col+a].ch = line[a];
				matrix[count*col+a].flag = false;
			}
			count++;
		}

		if ( str[idx] != matrix[x*col+y].ch ) {			// if the first character of str is not same with (0,0)th element of matrix
			cout << "The bit string " << str << " could not be found.";

		}
		else {
			idx++;
			stack.push(0);
			while ( idx != str_len && matrix[0].flag == false ) {
				if ( y != col-1 && str[idx] == matrix[x*col+y+1].ch && matrix[x*col+y+1].flag == false ) {		// check right box current matrix element
					y++;
					idx++;
					stack.push(x*col+y);
				}
				else if ( x != row-1 && str[idx] == matrix[(x+1)*col+y].ch && matrix[(x+1)*col+y].flag == false) {	// check down box current matrix element
					x++;
					idx++;
					stack.push(x*col+y);
				}
				else {
					matrix[x*col+y].flag = true;
					idx--;
					stack.pop(last_location);
					if ( idx != -1 ) {
						stack.pop(last_location);
						y = last_location % col;
						x = last_location / col;
						stack.push(last_location);
					}
					else break;
				}
			}
			if ( matrix[0].flag == true ) stack.pop(last_location);
			if ( stack.isEmpty() ) {		 // after operations, if stack is empty
				cout << "The bit string " << str << " could not be found.";
			}
			else {
				cout << "The bit string " << str << " is found following these cells:" << endl;
				myStack reverse;
				while ( ! stack.isEmpty() ) {	
					stack.pop(last_location);
					reverse.push(last_location);
				}
				while ( ! reverse.isEmpty() ) {
					reverse.pop(last_location);
					x = last_location / col;
					y = last_location % col;
					cout << "(" << x << "," << y << ")\t";
				}
			}
		}
		delete [] matrix;		// deleting matrix at the end
		cout << endl << "---------------------------------------------------------" << endl;
		cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
	}
	cout << "Program ended successfully!" << endl << endl;
	return 0;
}

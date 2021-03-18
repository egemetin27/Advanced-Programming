#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


void fitIntoMatrix(string word, int row, int col, string direction, string orientation, vector<vector <char>> & matrix)
// this function checks that if the word fits into the matrix
{
	string mainDirection = direction;
	int startPoint_row = row, startPoint_col = col;
	bool check = true;
	vector<vector< char>> tempMatrix = matrix;				// template matrix
	unsigned int num_char = 0;
	if ( matrix[row][col] != '-' ) {						// check for empty place to put first character
		check = false; 
	}
	else													// check for the rest of the word (after first character)
	{
		tempMatrix[row][col] = word[num_char];				// place first character to matrix
		num_char++;
		int counter = 0;									// number of direction changes ( if becomes 4, word cannot be put into matrix )
		while ( num_char < word.length()) {
			if ( direction == "u" ) {
				if ( row-1 < 0 || tempMatrix[row-1][col] != '-' ) {						// if you cannot go up due to out of range, look for alternative way
					if ( orientation == "CCW" ) {
						direction = "l";
						counter++;
					}
					else if (orientation == "CW" ) {
						direction = "r";
						counter++;
					}
				}
				else {
					row--;																// if available direction is empty, update row or column to proceed
					tempMatrix[row][col] = word[num_char];								// put the char in matrix
					num_char++;
					counter = 0;
					direction = mainDirection;
				}
			}
			else if ( direction == "l" ) {
				if ( col-1 < 0 || tempMatrix[row][col-1] != '-' ) {						// if you cannot go left...
					if ( orientation == "CCW" ) {
						direction = "d";
						counter++;
					}
					else if (orientation == "CW" ) {
						direction = "u";
						counter++;
					}
				}
				else {
					col--;	
					tempMatrix[row][col] = word[num_char];
					counter = 0;
					num_char++;
					direction = mainDirection;
				}
			}
			else if ( direction == "d" ) {
				if ( unsigned(row+1) >= tempMatrix.size() || tempMatrix[row+1][col] != '-' ) {					// if you cannot go down...
					if ( orientation == "CCW" ) {
						direction = "r";
						counter++;
					}
					else if (orientation == "CW" ) {
						direction = "l";
						counter++;
					}
				}
				else {
					row++;	
					tempMatrix[row][col] = word[num_char];
					num_char++;
					counter = 0;
					direction = mainDirection;
				}
			}
			else if ( direction == "r" ) {
				if ( unsigned(col+1) >= tempMatrix[0].size() || tempMatrix[row][col+1] != '-' ) {				// if you cannot go right...
					if ( orientation == "CCW" ) {
						direction = "u";
						counter++;
					}
					else if (orientation == "CW" ) {
						direction = "d";
						counter++;
					}
				}
				else {
					col++;		
					tempMatrix[row][col] = word[num_char];
					num_char++;
					counter = 0;
					direction = mainDirection;
				}
			}
			if ( counter == 4 ) {					// if counter becomes 4, it means 4 times direction has changed and there is no other way so return false
				num_char = word.length();
				check = false;
			}
		}
	}
	if ( check == true ) {
		cout << "\"" << word << "\"" << " was put into the matrix with given starting point: " << startPoint_row << "," << startPoint_col << " direction: " << direction << " orientation: " << orientation << endl;
		matrix = tempMatrix;

	}
	else {
		cout << "\"" << word << "\"" << " could not be put into the matrix with given starting point: " << startPoint_row << "," << startPoint_col << " direction: " << direction << " orientation: " << orientation << endl;
	}
	for ( unsigned int a = 0; a < matrix.size(); a++ ) {
		for ( unsigned int k = 0; k < matrix[0].size(); k++ ) {
			cout << matrix[a][k];
		}
		cout << endl;
	}
}


int main()
{
	ifstream input;
	string filename, line, word;
	int no_row, no_col;
	cout << "Please enter the name of the file: ";
	cin >> filename;
	input.open(filename.c_str());
	while ( input.fail() ) {
		cout << "File name is incorrect, please enter again: ";
		input.clear();
		cin >> filename;
		input.open(filename.c_str());
	}
	getline(input,line);
	istringstream firstline(line);
	firstline >> no_row >> no_col;
	if ( no_col <= 0 || no_row <= 0 ) {
		cout << "Invalid number for row and/or column!" << endl;
		return 0;
	}
	vector<vector <char>> matrix(no_row, vector<char>(no_col, '-'));		// creating a matrix number of rows x number of columns

	while ( getline(input,line) ) {
		int num_values = 0;
		istringstream check_num_values(line);						// check that number of values is equal to 5 with this input words
		while ( check_num_values >> word ) {
			num_values++;
		}
		if ( num_values != 5 ) {
			cout << "Invalid line! Number of values is different than 5." << endl;
		}
		else {
			istringstream check_words(line);
			string direction, orientation;
			int startPoint_row, startPoint_col;
			check_words >> word >> startPoint_row >> startPoint_col >> direction >> orientation;

			if ( startPoint_row < 0 || startPoint_row > no_row -1 || startPoint_col < 0 || startPoint_col > no_col -1 ) {
				cout << "Starting point is out of range! Point: " << startPoint_row << "," << startPoint_col << endl;
			}
			else if ( direction != "r" && direction != "l" && direction != "u" &&  direction != "d" ) {
				cout << "Invalid input for direction! Direction: " << direction << endl;
			}
			else if ( orientation != "CCW" && orientation != "CW" ) {
				cout << "Invalid input for orientation! Orientation: " << orientation << endl;
			}
			// If all values and words are valid in a line.
			else {
				fitIntoMatrix(word, startPoint_row, startPoint_col, direction, orientation, matrix);
			}
		}
	}
	return 0;
}
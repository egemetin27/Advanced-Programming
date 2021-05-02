#include <iostream>
#include <sstream>
#include <string>
#include "egemetin_Metin_Ege_hw3_strutils.h"
#include "egemetin_Metin_Ege_hw3_myclass.h"


using namespace std;


int main()
{
	SubSeqsList linkedData;
	int num;
	string numbers, no;
	cout << "Please enter the numbers in a line: ";
	getline(cin,numbers);
	cout << endl;
	istringstream inp_nums(numbers);
	while ( inp_nums >> no ) {
		num = atoi(no);
		if ( num < 0 ) {
			num *= -1;
			if ( linkedData.SubSeqsCheck(num) ) {
				linkedData.SubSeqsDelete(num);
				cout << "All subsequence(s) containing " << num << " has/have been deleted" << endl;
			}
			else 
				cout << "There is no subsequence that contains " << num << " to be deleted" << endl;
		}
		else {
			if ( linkedData.SubSeqsCheck(num) ) {
				cout << num << " is already in the list!" << endl;
			}
			else {		// inserting number to the list
				linkedData.SubSeqsInsert(num);
				cout << "Subsequence(s) containing " << num << " has/have been added" << endl;
			}
		}
	}
	linkedData.SubSeqsDisplay();
	return 0;
}

#include <iostream>
#include <string>
#include <sstream>
#include "strutils.h"

using namespace std;


struct node
{
	int value;
	node *next;
	node::node()
		: value(0), next (NULL)
	{}
	node::node(int n, node *pp)
		: value(n), next(pp)
	{}
};

node *AddInOrder (node *head, int val, string mode) 
{
	node *ptr = head, *prev = new node();				// ptr is a template of head and prev is a pointer to keep the previous pointer for ordering
	cout << "Next number: " << val << endl;
	if ( head == NULL || (val < head->value && mode == "A") || (val > head->value && mode == "D"))	{
		head = new node(val, NULL);
	}
	else {												// after the head pointer, we are checking number and acting accordingly
		while ( ptr != NULL ) {
			if ( (val > ptr->value && mode == "A") || (val < ptr->value && mode == "D") ) {		// if not correct place to put the number, proceed to next
				prev = ptr;
				ptr = ptr->next;
			}
			else if ( val == ptr->value ) {				// if our number and the value of the pointer is equal
				cout << val << " is already in the list!" << endl;
				cout << "List content:";
				node *temp = head;
				while ( temp != NULL ) {
					cout << " " << temp->value;
					temp = temp->next;
				}
				cout << endl;
				return head;			
			}
			else {										// if the value is does not fit to rule we break the loop and make appropriate changes 
				break;
			}
		}
		prev->next = new node(val,NULL);				// Updating the part to be deleted with NULL
	}
	cout << "Deleted nodes:";
	if ( ptr == NULL ) {
		cout << " None";
	}
	node *temp;
	while ( ptr != NULL ) {								// delete the rest from our number
		cout << " " << ptr->value;
		temp = ptr->next;
		delete ptr;
		ptr = temp;
	}
	cout << endl << "Appended: " << val << endl;
	temp = head;
	cout << "List content:";
	while ( temp != NULL ) {
		cout << " " << temp->value;
		temp = temp->next;
	}
	cout << endl;
	return head;
}

void DeleteLinkedList(node *head)				// function which deletes the linkedlist at the end of the program
{
	node *templ = head;
	if ( head == NULL ) {						// if head ptr is empty, there is nothing to delete
		cout << "The list is empty at the end of the program and nothing is deleted" << endl; 
	}
	else {
		cout << "All the nodes are deleted at the end of the program:";
		while ( head != NULL ) {
			templ = head->next;
			cout << " " << head->value;
			delete head;
			head = templ;
		}
		cout << endl;
	}
}

int main()
{
	string orderMode, each_num;
	int num;
	cout << "Please enter the order mode (A/D): ";
	cin >> orderMode;											// take input for order mod (ascending or descending)
	while ( orderMode != "A" && orderMode != "D" )	{
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "Please enter the order mode again (A/D): ";
		cin >> orderMode;
	}
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	string numbers;
	cout << "Please enter the numbers in a line: ";
	getline(cin,numbers);
	if ( numbers != "" ) {										// if some number was entered
		istringstream stream_num(numbers);
		node *head = NULL, *next_ptr = NULL;					// head and next pointers of the linked list intialized to NULL
		while ( stream_num >> each_num ) {
				num = atoi(each_num);
				head = AddInOrder(head, num, orderMode);
		}
		DeleteLinkedList(head);			// to delete remaining linkedlist if exist at the end
	}
	else {
		cout << "The list is empty at the end of the program and nothing is deleted" << endl;
	}
	return 0;
}

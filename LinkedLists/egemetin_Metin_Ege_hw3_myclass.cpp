#include <iostream>
#include <vector>
#include "egemetin_Metin_Ege_hw3_myclass.h"

using namespace std;


SubSeqsList::SubSeqsList()							// Default constructor that creates an empty list
{
	hHead = NULL;
}


SubSeqHeadNode* SubSeqsList::newNode(SubSeqHeadNode * prev, int num) 
{
	SubSeqHeadNode *newHead = new SubSeqHeadNode(prev->size+1,NULL);
	SubSeqNode *subnode = prev->sHead, *head  = new SubSeqNode(NULL,NULL), *p = head, *pp = head;
	while ( subnode != NULL ) {
		SubSeqNode *sub = new SubSeqNode(subnode->value, NULL);
		pp->next = sub;
		pp = pp->next;
		subnode = subnode->next;
	} 
	pp->next = new SubSeqNode(num, NULL);
	newHead->sHead = p->next;
	return newHead;
}


SubSeqHeadNode * SubSeqsList::placeNewNode(SubSeqHeadNode * newnode, SubSeqHeadNode * head) 
{
	SubSeqHeadNode *temp = head->next, *prev = head->next;
	while ( temp != NULL ) {
		bool check = true, sameness = true;
		if ( temp->size == newnode->size ) {
			SubSeqNode *ptr = temp->sHead, *newtemp = newnode->sHead;
			for ( int a = 0; a < temp->size; a++ ) {
				if ( check == true && ptr->value > newtemp->value ) {
					check = false;
					a = temp->size;
				}
				if ( ptr->value < newtemp->value ) a = temp->size;
				if ( ptr->value != newtemp->value) sameness = false;
				ptr = ptr->next;
				newtemp = newtemp->next;
			}
			if ( !check ) {
				prev->next = newnode;
				newnode->next = temp;
				return head;
			}
			if ( check == true && temp->next == NULL && sameness == false) {
				temp->next = newnode;
				return head;
			}
			else if ( temp->next != NULL && check == true && temp->next->size != newnode->size ) {
				newnode->next = temp->next;
				temp->next = newnode;
				return head;
			}
		}
		else {
			if ( check == true && temp->next == NULL ) {
				temp->next = newnode;
				return head;
			}
		}
		prev = temp;
		temp = temp->next;
	}
	return head;
}


bool SubSeqsList::isBigger(int num, SubSeqNode * ptr)
{
	SubSeqNode *temp = ptr;
	while (temp != NULL) {
		if ( num <= temp->value ) return false;
		temp = temp->next;
	}
	return true;
}


void SubSeqsList::SubSeqsDisplay()					// Prints the whole matrix
{
	cout << endl << "FINAL CONTENT" << endl;
	if ( hHead == NULL || hHead->next == NULL ) {
		cout << "List is empty!" << endl;
	}
	else {
		SubSeqHeadNode *temp = hHead->next;
		while ( temp != NULL ) {
			SubSeqNode *t = temp->sHead;			// t is template of subHead list
			cout << temp->size << " | " << t->value;
			if ( temp->size > 1 ) {
				t = t->next;
				while ( t != NULL ) {
					cout << " --> " << t->value;
					t = t->next;
				}
			}
			cout << endl;
			temp = temp->next;
		}
	}

}


void SubSeqsList::SubSeqsDelete(int num)		// Delete one or more elements
{
	SubSeqHeadNode *prev = hHead, *temp = hHead->next;		// prev is one before element of temp(copy of hHead)
	while ( temp != NULL ) {								// if it is not the first head node to be deleted
		SubSeqNode *p = temp->sHead;	
		while ( p != NULL ) {
			if ( num == p->value ) {						// if value of a subnode is equal to the number, we will delete that head node
				SubSeqNode *toBeDeleted = temp->sHead;
				while ( toBeDeleted != NULL ) {
					SubSeqNode *tempDelete = toBeDeleted->next;
					delete toBeDeleted;
					toBeDeleted = tempDelete;
				}
				prev->next = temp->next;
				delete temp;		
				temp = prev;
				break;
			}
			p = p->next;
		}
		prev = temp;
		temp = temp->next;
	}
}


void SubSeqsList::SubSeqsInsert(int num)						// Insert one or more elements
{
	SubSeqHeadNode *newptr = new SubSeqHeadNode(1,NULL);		// new node to be added to head list with size 1
	newptr->sHead = new SubSeqNode(num, NULL);					// subnode of this new head node
	//tail->next = newptr;
	SubSeqHeadNode *tempHead = hHead, *prevHead = hHead;		// prevHead is one before tempHead node
	if ( tempHead == NULL || tempHead->next == NULL ) {
		hHead = new SubSeqHeadNode(NULL, newptr);
	}
	else {
		tempHead = hHead->next;
		prevHead = hHead;
		while ( tempHead != NULL ) {
			if ( (prevHead->size == NULL) && (!isBigger(num, tempHead->sHead)) ) {		// checking the first node
				prevHead->next = newptr;
				newptr->next = tempHead;
			}
			else if ( isBigger(num,tempHead->sHead) ) {
				if ( tempHead->next != NULL && tempHead->size == 1 && (!isBigger(num,tempHead->next->sHead) || tempHead->next->size != 1) ) {
					newptr->next = tempHead->next;
					tempHead->next = newptr;
				}
				else if ( tempHead->next == NULL && tempHead->size == 1 ) {
					tempHead->next = newptr;
				}
				SubSeqHeadNode *newnode = newNode(tempHead, num);
				hHead = placeNewNode(newnode,hHead);
			}
			prevHead = tempHead;
			tempHead = tempHead->next;
		}
	}
}


bool SubSeqsList::SubSeqsCheck(int num)				// Check whether the number is in the matrix
{
	SubSeqHeadNode *p = hHead;
	while ( p != NULL ) {
		SubSeqNode *temp = p->sHead;				// template of each subsnodes
		while ( temp != NULL ) {
			if ( temp->value == num )	return true;
			temp = temp->next;
		}
		p = p->next;
	}
	return false;
}

#include "egemetin_Metin_Ege_hw4_myclass.h"


/* Begin: code taken from DynIntStack.cpp and updated */

myStack::myStack(void)
{
	top = NULL;
}


myStack::~myStack(void)
{
	StackNode *ptr = top;
	while (ptr != NULL) 
	{
		 StackNode *temp = ptr->next;
		 delete ptr;
		 ptr = temp;
	}
}


bool myStack::isEmpty(void)
{
	return top == NULL;
}


void myStack::push(int num)
{
	StackNode *newNode;
	newNode = new StackNode(num);
	if ( isEmpty() )
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}

}


void myStack::pop(int & num)
{
	if ( ! isEmpty() ) {
		StackNode *temp;
		num = top->value;
		temp = top->next;
		delete top;
		top = temp;
	}
}

/* End: code taken from DynIntStack.cpp */





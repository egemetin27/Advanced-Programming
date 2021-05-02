#include <iostream>

using namespace std;

struct cellStruct
{
	char ch;
	bool flag;
};

struct StackNode
{
	int value;
	StackNode *next;
	StackNode::StackNode()
	{}
	StackNode::StackNode(int num)
		: value(num), next(NULL)
	{}
};

class myStack
{
	public:
		myStack();			// default constructor
		~myStack();			// destructor
		void push(int);		// pushing values into stack
		void pop(int &);	// removing values from stack
		bool isEmpty();		// checks whether stack is empty
	private:
		StackNode *top;
};


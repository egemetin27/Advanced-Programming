#include <iostream>
#include <vector>

using namespace std;


struct SubSeqNode
{
	int value;
	SubSeqNode * next;
	SubSeqNode::SubSeqNode() {}
	SubSeqNode::SubSeqNode(int num, SubSeqNode* p)
		:	value(num), next(p)
	{}
};

struct SubSeqHeadNode
{
	int size; // number of elements in the subsequence
	SubSeqNode * sHead; // head of the subsequence list
	SubSeqHeadNode * next;
	SubSeqHeadNode::SubSeqHeadNode() 
	{}
	SubSeqHeadNode::SubSeqHeadNode(int s, SubSeqHeadNode *p) 
		: size(s), next(p), sHead(NULL)
	{}
};


class SubSeqsList
{
	public:
		SubSeqsList();					// Default constructor that creates an empty list
		void SubSeqsDisplay();			// Prints the ordered numbers
		void SubSeqsDelete(int num);	// Delete one or more elements
		void SubSeqsInsert(int num);	// Insert one or more elements
		bool SubSeqsCheck(int num);		// Check whether the value is is the data
		bool isBigger(int num, SubSeqNode *ptr);			// check whether our number is bigger than the last element of subnode(SubSeqNode) list
		SubSeqHeadNode* newNode(SubSeqHeadNode *prev, int num);		// creates a new node with our new number added to appropriate SubSeqNode
		SubSeqHeadNode* placeNewNode(SubSeqHeadNode*newnode, SubSeqHeadNode* head);		// Puts new head node created in the other function to appropiate space in the list
	private:
		SubSeqHeadNode * hHead;
};

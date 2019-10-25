#ifndef _LINKED_LIST_
#define _LINKED_LIST_

class LinkedList {
private: node * head, *tail;
		 int nodeCount;
public: LinkedList(void);
		LinkedList(int);
		void display(void);
		void splitFirst(int);
		void splitLast(int);
		void insertHead(int);
		void insertTail(int);
		void insertAtPosition(int, int);
		void deleteHead(void);
		void deleteTail(void);
		void deleteAtPosition(int);
		int getNodeCount(void);
};

#endif

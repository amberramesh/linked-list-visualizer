#include "GlobalDeclarations.h"

node *placeholder = new node;
node *demo = new node;
LinkedList linkedList;

LinkedList::LinkedList(void) {
	head = NULL;
	tail = NULL;
	nodeCount = 0;
}

LinkedList::LinkedList(int value) {
	node *temp = new node;
	temp->data = value;
	temp->next = NULL;

	temp->alphaNode = 0.0f;
	temp->alphaValue = 0.0f;
	temp->alphaNext = 0.0f;
	temp->alphaArrow = 0.0f;

	head = temp;
	tail = temp;
	temp = NULL;
	nodeCount = 1;

}

void LinkedList::display(void) {
	int x = 20, y = 250;
	bool nextLink = false;
	node *temp = new node;
	temp = head;

	while (temp) {
		// std::cout << temp->data << "\t";

		// Draw the node
		if (state == Animate && action == InsertTail && !temp->next)
			renderNode(x, y, temp, 6);
		else if (state == Animate && action == DeleteTail && !temp->next) {
			temp->next = placeholder->next;
			renderNode(x, y, temp, 6);
			temp->next = NULL;
		}
		else if ((temp->alphaNode < 1.0f) && (temp->alphaArrow < 1.0f))
			renderNode(x, y, temp, 1);
		else if (temp->alphaNode < 1.0f)
			renderNode(x, y, temp, 2);
		else if (temp->alphaArrow < 1.0f)
			renderNode(x, y, temp, 3);
		else
			renderNode(x, y, temp, 0);

		// Changes for next node
		temp = temp->next;
		x += 150;
	}
	// std::cout << "\n";
	// std::cout << "NodeCount = " << nodeCount << std::endl;
}

void LinkedList::splitFirst(int pos) {
	int x = 20, y = 250;
	node *temp = new node;
	temp = head;
	int i = 1;

	while (temp) {
		++i;
		if (state == Animate && action == InsertByPostionIndex && i == pos) {
			renderNode(x, y, temp, 6);
			break;
		}
		else if (state == Animate && action == DeleteByPosition && i == pos) {
			temp->next = placeholder->next;
			renderNode(x, y, temp, 6);
			temp->next = demo->next;
			break;
		}
		else
			renderNode(x, y, temp, 0);

		temp = temp->next;
		x += 150;
	}
}

void LinkedList::splitLast(int pos) {
	int x = 20, y = 250;
	node *temp = new node;
	temp = head;
	int i = 0;

	while (temp) {
		++i;
		if (i >= pos) {
			renderNode(x, y, temp, 0);
			x += 150;
		}

		temp = temp->next;
	}
}

void LinkedList::insertHead(int value) {
	node *temp = new node;
	temp->data = value;
	temp->next = head;

	temp->alphaNode = 1.0f;
	temp->alphaValue = 1.0f;
	temp->alphaNext = 0.0f;
	temp->alphaArrow = 0.0f;

	head = temp;
	if (tail == NULL)
		tail = temp;
	nodeCount++;
}

void LinkedList::insertTail(int value) {
	node *temp = new node;
	if (head == NULL)
		head = temp;
	else
		tail->next = temp;
	tail = temp;
	temp->data = value;
	temp->next = NULL;

	temp->alphaNode = 1.0f;
	temp->alphaValue = 1.0f;
	temp->alphaNext = 0.0f;
	temp->alphaArrow = 0.0f;

	nodeCount++;
}

void LinkedList::insertAtPosition(int pos, int value) {
	node *prev = new node;
	node *curr = new node;
	node *temp = new node;
	curr = head;
	for (int i = 1; i < pos; i++) {
		prev = curr;
		curr = curr->next;
		if (prev == tail) {
			insertTail(value);
			return;
		}
	}
	temp->data = value;
	temp->alphaNode = 1.0f;
	temp->alphaValue = 1.0f;
	temp->alphaNext = 0.0f;
	temp->alphaArrow = 0.0f;

	if (curr == head) {
		insertHead(value);
		return;
	}
	else {
		prev->next = temp;
		temp->next = curr;
	}
	nodeCount++;
}

void LinkedList::deleteHead() {
	if (head == NULL)
		return;
	*demo = *head;

	node *temp = new node;
	temp = head;

	if (head == tail) {
		head = NULL;
		tail = NULL;
		delete temp;
	}
	else {
		head = head->next;
		delete temp;
	}
	nodeCount--;
}

void LinkedList::deleteTail() {
	if (head == NULL)
		return;
	*demo = *tail;

	node *prev = new node;
	node *curr = new node;
	curr = head;
	while (curr->next) {
		prev = curr;
		curr = curr->next;
	}
	if (head == tail) {

		head = NULL;
		tail = NULL;
		delete curr;
	}
	else {
		*placeholder = *prev;

		tail = prev;
		prev->next = NULL;
		delete curr;
	}
	nodeCount--;
}

void LinkedList::deleteAtPosition(int pos) {
	if (head == NULL)
		return;
	node *curr = new node;
	node *prev = new node;
	curr = head;
	for (int i = 1; i < pos; i++) {
		prev = curr;
		curr = curr->next;
		if (curr == tail) {
			tail = prev;
			prev->next = NULL;
			delete curr;
			nodeCount--;
			return;
		}
	}
	if (curr == head) {
		deleteHead();
		return;
	}
	else {
		*demo = *curr;
		*placeholder = *prev;

		prev->next = curr->next;
		delete curr;
		nodeCount--;
	}
}

int LinkedList::getNodeCount() {
	return nodeCount;
}

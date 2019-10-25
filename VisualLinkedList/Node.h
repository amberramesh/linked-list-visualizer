#ifndef _NODE_
#define _NODE_
typedef float GLfloat;

struct node {
	int data;
	node *next;
	GLfloat alphaNode;
	GLfloat alphaValue;
	GLfloat alphaNext;
	GLfloat alphaArrow;
};
#endif

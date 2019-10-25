#ifndef _GLOBAL_
#define _GLOBAL_

#include <windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <GL/glut.h>
#include "Node.h"
#include "LinkedList.h"

// GLOBAL VARIABLES

enum States { Title, Input, Idle, Animate, Error };
enum Actions { InsertHead, InsertTail, InsertByPositionValue, InsertByPostionIndex, DeleteHead, DeleteTail, DeleteByPosition };
extern States state;
extern Actions action;

extern int nodePos;
extern int errorCode;

extern GLint winHeight, winWidth;
extern GLdouble xMin, xMax, yMin, yMax;

extern GLint window, main_menu, insert_menu, delete_menu;
extern GLint curX, curY;
extern GLfloat tx, ty;

extern GLint SPEED;
extern GLfloat speedTextAlpha;
extern GLfloat alphaFillRate;
extern GLfloat translateRate;

extern std::string key_string;

extern node *placeholder;
extern node *demo;
extern LinkedList linkedList;

// GLOBAL FUNCTIONS

// HANDLER FUNCTIONS
void titleHandler(void);
void animationHandler(void);
void errorHandler(void);
void ioHandler(void);
void keyStringHandler(void);

// RENDER FUNCTIONS
void renderNode(int, int, node*, int);
void renderText(int, int, const char *);

#endif


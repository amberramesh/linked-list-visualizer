/*
Linked List Visualization using OpenGL
Program written as part of mini project for subject 15CSL68

@author Amber Ramesh
@version 1.0
@since 2018-04-10
*/

#include "GlobalDeclarations.h"
	
States state = Title;
Actions action = InsertHead;

int nodePos;
int errorCode;

GLint winHeight = 500, winWidth = 1000;
GLdouble xMin = 0.0, xMax = 1000.0, yMin = 0.0, yMax = 500.0;

GLint window, main_menu, insert_menu, delete_menu;
GLint curX, curY;
GLfloat tx, ty;

GLint SPEED = 4;
GLfloat speedTextAlpha = 0.2f;
GLfloat alphaFillRate = 0.01f * 0.25f * ((SPEED-1) ? (SPEED-1) : SPEED);
GLfloat translateRate = 1.0f * 0.2f * SPEED;

std::string key_string;

void display() {

	if (linkedList.getNodeCount() > 5) {
		if ((state == Animate) && (xMax < (linkedList.getNodeCount() - 5) * 152 + 900.0)) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(xMin, xMax += 4, --yMin, ++yMax);
			glMatrixMode(GL_MODELVIEW);
			glutPostRedisplay();
		} else if ((linkedList.getNodeCount() > 6) && (state == Idle) && (xMax > (linkedList.getNodeCount() - 6) * 152 + 900.0)) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(xMin, xMax -= 4, ++yMin, --yMax);
			glMatrixMode(GL_MODELVIEW);
			glutPostRedisplay();
		}
	}

	glClearColor(0.96f, 0.96f, 0.862f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 0);
	glutSetMenu(main_menu);

	if (state == Title) {
		
		// CALL TO TITLE HANDLER
		titleHandler();
	} 
	else {

		glLineWidth(1.0f);
		glColor4f(0.2f,0.2f,0.2f,speedTextAlpha);
		glPushMatrix();
		glTranslatef((float)(xMin + xMax) / 2.0f - 155.0f,(float)yMax - 60.0f, 0);
		glScalef(0.75f,0.75f,0.0f);
		glTranslatef(-((float)(xMin + xMax) / 2.0f - 155.0f), -((float)yMax - 60.0f), 0);
		if (SPEED > 1) {
			renderText((xMin + xMax) / 2 - 155, (int)yMax - 40, "[-] Decrease Speed");
			if (speedTextAlpha > 0.2f) {
				if (SPEED == 5)
					speedTextAlpha -= 0.005f;
				else
					speedTextAlpha -= 0.0025f;
				glutPostRedisplay();
			}
		}
		if (SPEED < 5) {
			renderText((xMin + xMax) / 2 + 55, (int)yMax - 40, "[+] Increase Speed");
			if (speedTextAlpha > 0.2f) {
				if (SPEED == 1)
					speedTextAlpha -= 0.005f;
				else
					speedTextAlpha -= 0.0025f;
				glutPostRedisplay();
			}
		}
		glPopMatrix();

		if (state == Animate) {
			glutDetachMenu(GLUT_RIGHT_BUTTON);
			// CALL TO ANIMATION HANDLER
			animationHandler();
			glutPostRedisplay();
		}
		else {

			glColor3f(0.7, 0, 0);
			renderText(20, 300, "Value");
			glColor3f(0.2, 0.2, 0.2);
			renderText(20, 180, "Next");
			linkedList.display();

			if (state == Error) {
				// CALL TO ERROR HANDLER
				errorHandler();
			} 
			else if (state == Input) {
				// CALL TO IO HANDLER
				ioHandler();
			}
		}
	}

	renderText(curX, curY, key_string.c_str());

	glFlush();
} 

void menu(int num) {
	switch (num) {
	case 0: glutDestroyWindow(window);
			exit(0);
		break;
	case 1: state = Input;
		action = InsertHead; // INSERT HEAD
		break;
	case 2: state = Input;
		action = InsertTail; // INSERT TAIL
		break;
	case 3: state = Input;
		action = InsertByPositionValue; // INSERT BY POSITION (VALUE)
		break;
	case 4: if (linkedList.getNodeCount() < 1) {
				state = Error;
				errorCode = 1;
			}
			else {
				state = Animate;
				action = DeleteHead; // DELETE HEAD
				tx = 150; ty = 0;
				linkedList.deleteHead();
			}
			break;
	case 5: if (linkedList.getNodeCount() < 1) {
				state = Error;
				errorCode = 1;
			}
			else {
				state = Animate;
				action = DeleteTail; // DELETE TAIL
				tx = (linkedList.getNodeCount() - 1) * 150; ty = 0;
				linkedList.deleteTail();
			}
		break;
	case 6: if (linkedList.getNodeCount() < 1) {
				state = Error;
				errorCode = 1;
			}
			else {
				state = Input;
				action = DeleteByPosition; // DELETE BY POSITION
			}
		break;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (state == Idle || state == Animate || state == Error) {
		key_string = "";
		switch (key) {
		case 43: if (SPEED < 5) {
			SPEED++;
			speedTextAlpha = 1.0f;
			alphaFillRate = 0.01f * 0.25f * ((SPEED - 1) ? (SPEED - 1) : SPEED);
			translateRate = 1.0f * 0.2f * SPEED;
			glutPostRedisplay();
		}
				 break;
		case 45: if (SPEED > 1) {
			SPEED--;
			speedTextAlpha = 1.0f;
			alphaFillRate = 0.01f * 0.25f * ((SPEED - 1) ? (SPEED - 1) : SPEED);
			translateRate = 1.0f * 0.2f * SPEED;
			glutPostRedisplay();
		}
				 break;
		default: 
			break;
		}
	}
	else {
		switch (key) {
		case 13:
			keyStringHandler();
			break;
		case 8:
			if(key_string != "")
				key_string.erase(key_string.end() - 1);
			break;
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
			key_string += char(key);
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}
}

void createMenu() {
	insert_menu = glutCreateMenu(menu);
	glutAddMenuEntry("Insert head", 1);
	glutAddMenuEntry("Insert tail", 2);
	glutAddMenuEntry("Insert at position", 3);
	delete_menu = glutCreateMenu(menu);
	glutAddMenuEntry("Delete head", 4);
	glutAddMenuEntry("Delete tail", 5);
	glutAddMenuEntry("Delete at position", 6);
	main_menu = glutCreateMenu(menu);
	glutAddSubMenu("Insert", insert_menu);
	glutAddSubMenu("Delete", delete_menu);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(GLint newWidth,GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}

int main(int argc, char **argv) {

	std::cout << "Linked List Visualization using OpenGL" << std::endl;
	std::cout << "Program written as part of mini project for subject 15CSL68" << std::endl <<std::endl;

	std::cout << "@author Amber Ramesh" << std::endl;
	std::cout << "@version 1.0" << std::endl;
	std::cout << "@since 2018-04-10" << std::endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	window = glutCreateWindow("Linked List Visualization");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xMin,xMax,yMin,yMax);
	glMatrixMode(GL_MODELVIEW);
	createMenu();
	glutFullScreen();

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

#include "GlobalDeclarations.h"

void titleHandler(void) {
	glutDetachMenu(GLUT_RIGHT_BUTTON);
	curX = 680; curY = 50;

	glLineWidth(2.0);
	glColor3f(0, 0, 1);
	renderText(370, 450, "B.N.M. Institute of Technology");
	glColor3f(1, 0.5, 0);
	renderText(390, 420, "Linked List Visualization");

	glColor3f(0.7, 0, 0);
	renderText(810, 200, "Amber Ramesh");
	renderText(810, 175, "1BG12CS011");

	glColor3f(0, 0, 0);
	renderText(280, 50, "Enter a number to initialize linked list: ");
}

void animationHandler(void) {
	// ANIMATE_InsertHead
	if (action == InsertHead) {

		glPushMatrix();
		glTranslatef(tx, 0, 0);
		linkedList.display();
		glPopMatrix();

		if (tx < 150) {
			tx += translateRate;
		}
		else {
			glPushMatrix();
			glTranslatef(0, ty, 0);
			renderNode(20, 150, demo, 2);
			glPopMatrix();

			if (ty < 100)
				ty += translateRate;

			else {
				linkedList.insertHead(demo->data);
				state = Idle;
				glutAttachMenu(GLUT_RIGHT_BUTTON);
			}
		}
	}
	// ANIMATE_InsertTail
	else if (action == InsertTail) {

		glPushMatrix();
		linkedList.display();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(tx, ty, 0);
		renderNode(20, 150, demo, 2);
		glPopMatrix();

		if (ty < 100)
			ty += translateRate;
		else {
			linkedList.insertTail(demo->data);
			state = Idle;
			glutAttachMenu(GLUT_RIGHT_BUTTON);
		}

	}
	// ANIMATE_InsertByPosition
	else if (action == InsertByPostionIndex) {

		glPushMatrix();
		linkedList.splitFirst(nodePos);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(tx, 0, 0);
		linkedList.splitLast(nodePos);
		glPopMatrix();

		if (tx < nodePos * 150)
			tx += translateRate;
		else {

			glPushMatrix();
			glTranslatef(0, ty, 0);
			renderNode((nodePos - 1) * 150 + 20, 150, demo, 2);
			glPopMatrix();

			if (ty < 100)
				ty += translateRate;
			else {
				linkedList.insertAtPosition(nodePos, demo->data);
				state = Idle;
				glutAttachMenu(GLUT_RIGHT_BUTTON);
			}
		}
	}
	// ANIMATE_DeleteHead
	else if (action == DeleteHead) {

		glPushMatrix();
		glTranslatef(tx, 0, 0);
		linkedList.display();
		glPopMatrix();

		if (demo->alphaArrow > 0.0f) {
			glPushMatrix();
			renderNode(20, 250, demo, 6);
			glPopMatrix();
		}
		else if (demo->alphaNode > 0.0f) {
			glPushMatrix();
			glTranslatef(0, ty -= translateRate, 0);
			renderNode(20, 250, demo, 5);
			glPopMatrix();
		}
		else {
			if (tx > 0)
				tx -= translateRate;
			else {
				state = Idle;
				glutAttachMenu(GLUT_RIGHT_BUTTON);
			}
		}
	}
	// ANIMATE_DeleteTail
	else if (action == DeleteTail) {

		glPushMatrix();
		linkedList.display();
		glPopMatrix();

		if (demo->alphaArrow > 0.0f) {
			glPushMatrix();
			glTranslatef(tx, 0, 0);
			renderNode(20, 250, demo, 6);
			glPopMatrix();
		}
		else if (demo->alphaNode > 0.0f) {
			glPushMatrix();
			glTranslatef(tx, ty -= translateRate, 0);
			renderNode(20, 250, demo, 5);
			glPopMatrix();
		}
		else {
			state = Idle;
			glutAttachMenu(GLUT_RIGHT_BUTTON);
		}
	}
	// ANIMATE_DeleteByPosition
	else if (action == DeleteByPosition) {

		glPushMatrix();
		linkedList.splitFirst(nodePos);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(tx, 0, 0);
		linkedList.splitLast(nodePos);
		glPopMatrix();

		if (demo->alphaArrow > 0.0f) {
			glPushMatrix();
			glTranslatef(tx - 150, 0, 0);
			renderNode(20, 250, demo, 6);
			glPopMatrix();
		}
		else if (demo->alphaNode > 0.0f) {
			glPushMatrix();
			glTranslatef(tx - 150, ty -= translateRate, 0);
			renderNode(20, 250, demo, 5);
			glPopMatrix();
		}
		else {
			if (tx > ((nodePos - 1) * 150))
				tx -= translateRate;
			else {
				state = Idle;
				glutAttachMenu(GLUT_RIGHT_BUTTON);
			}
		}
	}
}

void errorHandler(void) {
	glutSetMenu(main_menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glColor3f(0.7, 0.0, 0.0);
	std::string errorString;
	// ---- ERROR CODES ----
	switch (errorCode) {
	case 0: errorString = "ERROR: Value is too large.";
		break;
	case 1: errorString = "ERROR: List is empty.";
		break;
	case 2: errorString = "ERROR: Position must be between 1 to n.";
		break;
	}
	char const *errorMsg = errorString.c_str();
	renderText(70, 50, errorMsg);
}

void ioHandler(void) {
	glColor3f(0.2, 0.2, 0.2);
	if (action == InsertHead || action == InsertTail || action == InsertByPositionValue) {
		curX = 180; curY = 50;
		renderText(50, 50, "Enter value: ");
	}
	else if (action == InsertByPostionIndex || action == DeleteByPosition) {
		curX = 200; curY = 50;
		renderText(50, 50, "Enter position: ");
	}
}

void keyStringHandler(void) {
	if (!key_string.empty()) {
		if (strlen(key_string.c_str()) < 9) {
			if (state == Title) {
				demo->data = stoi(key_string);
				linkedList = LinkedList(demo->data);
				state = Idle;
				glutAttachMenu(GLUT_RIGHT_BUTTON);
			}
			else if (state == Input && (action == InsertHead || action == InsertTail || action == InsertByPositionValue)) {
				demo->data = stoi(key_string);
				key_string = "";
				if (action == InsertHead) {
					state = Animate;
					tx = 0; ty = 0;
					if (linkedList.getNodeCount() < 1)
						tx = 150;
					demo->alphaNode = 0.0f;
					demo->alphaValue = 0.0f;
					demo->alphaArrow = 0.0f;
					demo->alphaNext = 0.0f;
				}
				else if (action == InsertTail) {
					state = Animate;
					tx = linkedList.getNodeCount() * 150;
					ty = 0;
					demo->alphaNode = 0.0f;
					demo->alphaValue = 0.0f;
					demo->alphaArrow = 0.0f;
					demo->alphaNext = 0.0f;
				}
				else if (action == InsertByPositionValue)
					action = InsertByPostionIndex;
			}
			else if (state == Input && (action == InsertByPostionIndex || action == DeleteByPosition)) {
				nodePos = stoi(key_string);
				if (action == InsertByPostionIndex) {
					if (nodePos > 1 && nodePos <= linkedList.getNodeCount()) {
						state = Animate;
						tx = (nodePos - 1) * 150;
						ty = 0;
						demo->alphaNode = 0.0f;
						demo->alphaValue = 0.0f;
						demo->alphaArrow = 0.0f;
						demo->alphaNext = 0.0f;
					}
					else {
						state = Error;
						errorCode = 2;
					}
				}
				else {
					if (nodePos > 1 && nodePos < linkedList.getNodeCount()) {
						state = Animate;
						linkedList.deleteAtPosition(nodePos);
						tx = nodePos * 150;
						ty = 0;
					}
					else {
						state = Error;
						errorCode = 2;
					}
				}
			}
		}
		else {
			state = Error;
			errorCode = 0;
		}
	}
	key_string = "";
}

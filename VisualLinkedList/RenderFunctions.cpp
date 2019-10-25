#include "GlobalDeclarations.h"

void renderText(int x, int y, const char *string) {
	glLineWidth(2.0);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(0.15, 0.15, 0.15);
	while (*string)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *string++);
	glPopMatrix();
}

void renderNode(int nodeX, int nodeY, node* temp, int setting) {

	// ---- SETTINGS ----
	// 0 - Default, no alpha transitions
	// 1 - Full node creation, fade_in(all alpha channels)
	// 2 - Node creation, fade_in(alphaNode,alphaValue)
	// 3 - Link creation, fade_in(alphaArrow,alphaNext)
	// 4 - Node deletion, fade_out(all alpha channels)
	// 5 - Value deletion, fade_out(alphaNode,alphaValue)
	// 6 - Link deletion, fade_out(alphaArrow,alphaNext)

	// Drawing value block
	glLineWidth(2.0);
	glColor4f(0.7, 0, 0, temp->alphaNode);
	glBegin(GL_POLYGON);
	glVertex2i(nodeX, nodeY);
	glVertex2i(nodeX + 100, nodeY);
	glVertex2i(nodeX + 100, nodeY + 35);
	glVertex2i(nodeX + 95, nodeY + 40);
	glVertex2i(nodeX + 5, nodeY + 40);
	glVertex2i(nodeX, nodeY + 35);
	glEnd();

	// Display value of node
	glColor4f(1.0, 1.0, 1.0, temp->alphaValue);
	std::string s = std::to_string(temp->data);
	char const *valueText = s.c_str();
	renderText((int)(nodeX + 50 - (5.5 * strlen(valueText))), nodeY + 10, valueText);

	// Drawing next block
	glLineWidth(2.0);
	glColor4f(0.2, 0.2, 0.2, temp->alphaNode);
	glBegin(GL_POLYGON);
	glVertex2i(nodeX, nodeY);
	glVertex2i(nodeX, nodeY - 35);
	glVertex2i(nodeX + 5, nodeY - 40);
	glVertex2i(nodeX + 95, nodeY - 40);
	glVertex2i(nodeX + 100, nodeY - 35);
	glVertex2i(nodeX + 100, nodeY);
	glEnd();

	// Determine and draw node address
	std::ostringstream oss;
	oss << temp->next;
	std::string address = oss.str();
	if (address == "00000000") {
		char const *addrText = "NULL";
		glColor4f(1.0, 1.0, 1.0, temp->alphaNext);
		renderText(nodeX + 27, nodeY - 28, addrText);
	} else {
		char const *addrText = address.c_str();
		glColor4f(1.0, 1.0, 1.0, temp->alphaNext);
		renderText(nodeX + 3, nodeY - 30, addrText);
	}


	// Drawing arrows
	if (temp->next) {
		glLineWidth(2.0);
		glColor4f(0.3, 0.3, 0.3, temp->alphaArrow);
		glBegin(GL_LINES);
		glVertex2i(nodeX + 100, nodeY);
		glVertex2i(nodeX + 150, nodeY);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2i(nodeX + 150, nodeY);
		glVertex2i(nodeX + 140, nodeY + 10);
		glVertex2i(nodeX + 140, nodeY - 10);
		glEnd();
	}

	switch (setting) {
	case 0: break;
	case 1:
		if (temp->alphaNode < 1.0f) {
			temp->alphaNode += alphaFillRate;
			temp->alphaValue += alphaFillRate;
			temp->alphaArrow += alphaFillRate;
			temp->alphaNext += alphaFillRate;
			glutPostRedisplay();
		}
		break;
	case 2: 
		if(temp ->alphaNode < 1.0f) {
			temp->alphaNode += alphaFillRate;
			temp->alphaValue += alphaFillRate;
			glutPostRedisplay();
		}
		break;
	case 3: 
		if (temp->alphaArrow < 1.0f) {
			temp->alphaArrow += alphaFillRate;
			temp->alphaNext += alphaFillRate;
			glutPostRedisplay();
		}
		break;
	case 4:
		if (temp->alphaNode > 0.0f) {
			temp->alphaNode -= alphaFillRate;
			temp->alphaValue -= alphaFillRate;
			temp->alphaArrow -= alphaFillRate;
			temp->alphaNext -= alphaFillRate;
			glutPostRedisplay();
		}
		break;
	case 5:
		if (temp->alphaNode > 0.0f) {
			temp->alphaNode -= alphaFillRate;
			temp->alphaValue -= alphaFillRate;
			glutPostRedisplay();
		}
		break;
	case 6:
		if (temp->alphaArrow > 0.0f) {
			temp->alphaArrow -= alphaFillRate;
			temp->alphaNext -= alphaFillRate;
			glutPostRedisplay();
		}
		break;
	}
}

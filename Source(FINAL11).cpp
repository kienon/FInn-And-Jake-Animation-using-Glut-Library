#include <windows.h>
#include <stdlib.h>
#include <gl\glew.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\freeglut.h>



#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768
#define PI 3.1415926535897932384626433832795
#define FPS 120

double theta = 0.0;
float  counter = 300.0, count = -1800.0, finnmovementscene1 = 30;
int X = 0;
int Y = 0;
GLint a = 0, b = 700, c = 600, g = 500, h = 600, x = 0, i = 0;


void initOpenGl(void)
{ /* prepare the window for displaying on it */
	glClearColor(0.0, 0.7, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, -SCREEN_WIDTH / 2, SCREEN_WIDTH / 2);
	glMatrixMode(GL_MODELVIEW);
}

void update(int value)
{
	a += 1;
	glutPostRedisplay();
	glutTimerFunc(100, update, 0);
}

void triangle(int x, int y, int w, int h) {
	glBegin(GL_TRIANGLES);
	glColor3ub(34, 139, 34);
	glVertex2d(x - w, y - h);
	glVertex2d(x + w, y - h);
	glVertex2d(x, y);
	glEnd();
}

void rectangle(int x, int y, int w, int h) {
	glBegin(GL_POLYGON);
	glVertex2d(x + counter, y);
	glVertex2d(x + w + counter, y);
	glVertex2d(x + w + counter, y + h);
	glVertex2d(x + counter, y + h);
	glEnd();
}

void rectangle2(int x, int y, int w, int h) {
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x + w, y);
	glVertex2d(x + w, y + h);
	glVertex2d(x, y + h);
	glEnd();
}

void rectangle3(int x, int y, int w, int h) {
	glBegin(GL_POLYGON);
	glVertex2d(x + finnmovementscene1, y);
	glVertex2d(x + w + finnmovementscene1, y);
	glVertex2d(x + w + finnmovementscene1, y + h);
	glVertex2d(x + finnmovementscene1, y + h);
	glEnd();
}

void circle2(int x, int y, int rX, int rY) {
	const float DEG2RAD = 3.14159 / 180;

	glBegin(GL_POLYGON);
	for (int i = -1; i < 360; i++) {
		float degInRad = i * DEG2RAD;
		glVertex2d(x + cos(degInRad) * rX, y + sin(degInRad) * rY);
	}
	glEnd();
}

//draw cloud
void cloud() {
	int x = X, y = Y;

	glColor3ub(255, 255, 255);
	circle2(x, y - 5, 80, 75);
	glColor3ub(255, 255, 255);
	circle2(x + 25, y - 15, 45, 75);
	glColor3ub(255, 255, 255);
	circle2(x + 25, y + 15, 35, 65);
	glColor3ub(255, 255, 255);
	circle2(x - 25, y + 15, 35, 65);
	glColor3ub(255, 255, 255);
	circle2(x, y + 15, 35, 85);
	glColor3ub(255, 255, 255);
	circle2(x - 25, y - 15, 45, 75);
}

//Cloud Position
void cloudPos(double x, double y, double a, double b) {
	glPushMatrix();
	glTranslated(x, y, 0.0);
	glScaled(a, b, 0.0);
	cloud();
	glPopMatrix();
}

//draw sun
void sun2() {
	int x = X, y = Y;

	glColor3ub(255, 204, 0);
	circle2(x, y, 100, 100);

}

//Sun position
void sunPos(double x, double y, double a, double b) {
	glPushMatrix();
	glTranslated(x, y, 0.0);
	glScaled(a, b, 0.0);
	sun2();
	glPopMatrix();

}

//Draw tree
void tree(int x, int y, int w) {
	glColor3ub(139, 69, 19);
	rectangle2(x - w / 2, y - w, w, -w * 1.8);

	for (int i = 20; i <= 100; i += 20) {
		for (int j = 10; j <= 50; j += 10) {

			triangle(x, y - i, w + i, w);
		}
	}

}

//Tree Position
void treePos(double x, double y) {
	glPushMatrix();
	glTranslated(x, y, 0.0);
	glScaled(-0.3, 4.0, 0.0);
	tree(X, Y, 80);
	glPopMatrix();
}

//Draw ground
void ground(int x, int y, int w, int h) {
	glColor3ub(139, 69, 19);
	glBegin(GL_POLYGON);
	glVertex2d(x - w / 3, y - h);
	glVertex2d(x + w / 3, y - h);
	glVertex2d(x + w / 3, y - h / 2);
	glVertex2d(x - w / 3, y - h / 2);
	glEnd();

	glColor3ub(34, 139, 34);
	glBegin(GL_POLYGON);
	glVertex2d(x - w / 3, y - h / 1.8);
	glVertex2d(x + w / 3, y - h / 1.8);
	glVertex2d(x + w / 3, y - h / 2.2);
	glVertex2d(x - w / 3, y - h / 2.2);
	glEnd();
}

//Draw roof
void roof(int x, int y, int w) {
	glColor3ub(100, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(x - w / 8, y + (2.0 / 3.0) * w);
	glVertex2d(x + w + w / 8, y + (2.0 / 3.0) * w);
	glVertex2d(x + w, y + (2.0 / 3.0) * w + w / 4);
	glVertex2d(x, y + (2.0 / 3.0) * w + w / 4);
	glEnd();
}

//Draw house
void house() {
	glColor3ub(1000, 1000, 1000);
	rectangle2(0, -360, 300, 560);
	glColor3ub(139, 69, 19);
	rectangle2(125, -360, 60, 280);
	glColor3ub(0, 0, 0);
	rectangle2(30, -150, 60, 180);
	rectangle2(215, -150, 60, 180);
}

//Draw gun
void gun() {
	glPushMatrix();
	glTranslated(20, -240, 0.0);

	//Upper
	glColor3ub(112, 128, 144);
	rectangle(0, 0, 40, 20);
	glColor3ub(0, 0, 0);
	rectangle(5, 10, 30, 10);

	//Lower
	glColor3ub(112, 128, 144);
	rectangle(40, -30, 10, 50);
	glColor3ub(0, 0, 0);
	rectangle(45, -30, 5, 40);

	glPopMatrix();
}

//Jake The Animal
void animal() {
	glPushMatrix();
	glTranslated(-310, -400, 0.0);
	glScaled(0.4, 0.7, 0);

	//lining head
	glColor3ub(0, 0, 0);
	rectangle2(90, 200, 110, 140);//top line
	glColor3ub(0, 0, 0);
	rectangle2(80, 210, 130, 120);
	glColor3ub(0, 0, 0);
	rectangle2(70, 240, 150, 80);
	glColor3ub(0, 0, 0);
	rectangle2(60, 230, 170, 80);

	//lining body
	glColor3ub(0, 0, 0);
	rectangle2(90, 110, 120, 130);//top line
	glColor3ub(0, 0, 0);
	rectangle2(70, 120, 150, 110);
	glColor3ub(0, 0, 0);
	rectangle2(60, 130, 170, 90);
	glColor3ub(0, 0, 0);
	rectangle2(50, 140, 190, 70);
	//smallsquareleft
	glColor3ub(0, 0, 0);
	rectangle2(70, 110, 20, 10);
	//smallsquareleft
	glColor3ub(0, 0, 0);
	rectangle2(60, 120, 10, 10);
	//smallsquareright
	glColor3ub(0, 0, 0);
	rectangle2(210, 110, 10, 10);
	//lining leg left
	glColor3ub(0, 0, 0);
	rectangle2(90, 40, 30, 70);
	rectangle2(80, 40, 10, 20);
	//lining leg right
	glColor3ub(0, 0, 0);
	rectangle2(170, 40, 30, 70);
	rectangle2(200, 40, 10, 20);
	//leg
	glColor3ub(0, 0, 0);
	rectangle2(120, 100, 50, 10);

	//body
	glColor3ub(255, 255, 0);
	rectangle2(90, 110, 110, 220);//top line
	//bodyleft
	glColor3ub(255, 255, 0);
	rectangle2(80, 120, 10, 200);
	//bodyright
	glColor3ub(255, 255, 0);
	rectangle2(200, 120, 10, 200);
	//headright
	glColor3ub(255, 255, 0);
	rectangle2(210, 230, 10, 80);
	//headleft
	glColor3ub(255, 255, 0);
	rectangle2(70, 230, 10, 80);
	//squareForTail
	glColor3ub(255, 255, 0);
	rectangle2(70, 120, 10, 10);
	//squarerighUp
	glColor3ub(255, 255, 0);
	rectangle2(210, 210, 10, 10);
	//legleft
	glColor3ub(255, 255, 0);
	rectangle2(100, 50, 10, 60);
	//legleftshoe
	glColor3ub(255, 255, 0);
	rectangle2(90, 50, 10, 10);
	//legright
	glColor3ub(255, 255, 0);
	rectangle2(180, 50, 10, 60);
	//legrightshoe
	glColor3ub(255, 255, 0);
	rectangle2(190, 50, 10, 10);

	//handleft
	glColor3ub(255, 255, 0);
	rectangle2(60, 150, 10, 60);
	//handleftsquare
	glColor3ub(255, 255, 0);
	rectangle2(70, 210, 10, 10);
	//handright
	glColor3ub(255, 255, 0);
	rectangle2(220, 150, 10, 60);

	//eyeleft
	glColor3ub(255, 255, 255);
	rectangle2(100, 250, 40, 40);
	//eyeRetinaleftBottom
	glColor3ub(50, 55, 55);
	rectangle2(100, 250, 40, 10);
	//eyeRetinaleftUp
	glColor3ub(50, 55, 55);
	rectangle2(100, 250, 10, 40);

	//eyeRight
	glColor3ub(255, 255, 255);
	rectangle2(180, 250, 40, 40);
	//eyeRetinarightBottom
	glColor3ub(50, 55, 55);
	rectangle2(180, 250, 40, 10);
	//eyeRetinarightUp
	glColor3ub(50, 55, 55);
	rectangle2(180, 250, 10, 40);

	//NoseUpperLayer
	glColor3ub(70, 75, 75);
	rectangle2(150, 220, 20, 20);
	//Nose
	glColor3ub(100, 105, 105);
	rectangle2(150, 220, 10, 10);

	//ShadingNoseLeft
	glColor3ub(218, 215, 0);
	rectangle2(140, 210, 10, 10);
	//ShadingNoseLeftUp
	glColor3ub(218, 215, 0);
	rectangle2(130, 210, 10, 40);
	//ShadingNoseRight
	glColor3ub(218, 215, 0);
	rectangle2(170, 210, 10, 10);
	//ShadingNoseRightUp
	glColor3ub(218, 215, 0);
	rectangle2(180, 210, 10, 40);
	//ShadingNoseRightUp
	glColor3ub(218, 215, 0);
	rectangle2(140, 240, 40, 10);

	//Shadingeyeheadleft
	glColor3ub(218, 215, 0);
	rectangle2(90, 240, 10, 50);
	//Shadingeyeheadleft
	glColor3ub(218, 215, 0);
	rectangle2(80, 240, 10, 10);
	//ShadingeyeheadleftUpHead
	glColor3ub(218, 215, 0);
	rectangle2(90, 320, 100, 10);
	//Shadingeyeheadright
	glColor3ub(218, 215, 0);
	rectangle2(210, 240, 10, 10);
	//ShadingeyeheadrightUp
	glColor3ub(218, 215, 0);
	rectangle2(210, 290, 10, 20);
	//ShadingeyeheadrightUpLeft
	glColor3ub(218, 215, 0);
	rectangle2(200, 300, 10, 20);
	//ShadingeyeheadrightUpLeftLeft
	glColor3ub(218, 215, 0);
	rectangle2(190, 310, 10, 20);
	glPopMatrix();
}
void animal1() {
	glPushMatrix();
	glTranslated(-310, -400, 0.0);
	glScaled(0.4, 0.7, 0);

	//lining head
	glColor3ub(0, 0, 0);
	rectangle2(90, 200, 110, 140);//top line
	glColor3ub(0, 0, 0);
	rectangle2(80, 210, 130, 120);
	glColor3ub(0, 0, 0);
	rectangle2(70, 240, 150, 80);
	glColor3ub(0, 0, 0);
	rectangle2(60, 230, 170, 80);

	//lining body
	glColor3ub(0, 0, 0);
	rectangle2(90, 110, 120, 130);//top line
	glColor3ub(0, 0, 0);
	rectangle2(70, 120, 150, 110);
	glColor3ub(0, 0, 0);
	rectangle2(60, 130, 170, 90);
	glColor3ub(0, 0, 0);
	rectangle2(50, 140, 190, 70);
	//smallsquareleft
	glColor3ub(0, 0, 0);
	rectangle2(70, 110, 20, 10);
	//smallsquareleft
	glColor3ub(0, 0, 0);
	rectangle2(60, 120, 10, 10);
	//smallsquareright
	glColor3ub(0, 0, 0);
	rectangle2(210, 110, 10, 10);
	//lining leg left
	glColor3ub(0, 0, 0);
	rectangle2(90, 40, 30, 70);
	rectangle2(80, 40, 10, 20);
	//lining leg right
	glColor3ub(0, 0, 0);
	rectangle2(170, 40, 30, 70);
	rectangle2(200, 40, 10, 20);
	//leg
	glColor3ub(0, 0, 0);
	rectangle2(120, 100, 50, 10);

	//body
	glColor3ub(0, 0, 0);
	rectangle2(90, 110, 110, 220);//top line
	//bodyleft
	glColor3ub(0, 0, 0);
	rectangle2(80, 120, 10, 200);
	//bodyright
	glColor3ub(0, 0, 0);
	rectangle2(200, 120, 10, 200);
	//headright
	glColor3ub(0, 0, 0);
	rectangle2(210, 230, 10, 80);
	//headleft
	glColor3ub(0, 0, 0);
	rectangle2(70, 230, 10, 80);
	//squareForTail
	glColor3ub(0, 0, 0);
	rectangle2(70, 120, 10, 10);
	//squarerighUp
	glColor3ub(0, 0, 0);
	rectangle2(210, 210, 10, 10);
	//legleft
	glColor3ub(0, 0, 0);
	rectangle2(100, 50, 10, 60);
	//legleftshoe
	glColor3ub(0, 0, 0);
	rectangle2(90, 50, 10, 10);
	//legright
	glColor3ub(0, 0, 0);
	rectangle2(180, 50, 10, 60);
	//legrightshoe
	glColor3ub(0, 0, 0);
	rectangle2(190, 50, 10, 10);

	//handleft
	glColor3ub(0, 0, 0);
	rectangle2(60, 150, 10, 60);
	//handleftsquare
	glColor3ub(0, 0, 0);
	rectangle2(70, 210, 10, 10);
	//handright
	glColor3ub(0, 0, 0);
	rectangle2(220, 150, 10, 60);

	//eyeleft
	glColor3ub(0, 0, 0);
	rectangle2(100, 250, 40, 40);
	//eyeRetinaleftBottom
	glColor3ub(0, 0, 0);
	rectangle2(100, 250, 40, 10);
	//eyeRetinaleftUp
	glColor3ub(0, 0, 0);
	rectangle2(100, 250, 10, 40);

	//eyeRight
	glColor3ub(0, 0, 0);
	rectangle2(180, 250, 40, 40);
	//eyeRetinarightBottom
	glColor3ub(0, 0, 0);
	rectangle2(180, 250, 40, 10);
	//eyeRetinarightUp
	glColor3ub(0, 0, 0);
	rectangle2(180, 250, 10, 40);

	//NoseUpperLayer
	glColor3ub(0, 0, 0);
	rectangle2(150, 220, 20, 20);
	//Nose
	glColor3ub(0, 0, 0);
	rectangle2(150, 220, 10, 10);

	//ShadingNoseLeft
	glColor3ub(0, 0, 0);
	rectangle2(140, 210, 10, 10);
	//ShadingNoseLeftUp
	glColor3ub(0, 0, 0);
	rectangle2(130, 210, 10, 40);
	//ShadingNoseRight
	glColor3ub(0, 0, 0);
	rectangle2(170, 210, 10, 10);
	//ShadingNoseRightUp
	glColor3ub(0, 0, 0);
	rectangle2(180, 210, 10, 40);
	//ShadingNoseRightUp
	glColor3ub(0, 0, 0);
	rectangle2(140, 240, 40, 10);

	//Shadingeyeheadleft
	glColor3ub(0, 0, 0);
	rectangle2(90, 240, 10, 50);
	//Shadingeyeheadleft
	glColor3ub(0, 0, 0);
	rectangle2(80, 240, 10, 10);
	//ShadingeyeheadleftUpHead
	glColor3ub(0, 0, 0);
	rectangle2(90, 320, 100, 10);
	//Shadingeyeheadright
	glColor3ub(0, 0, 0);
	rectangle2(210, 240, 10, 10);
	//ShadingeyeheadrightUp
	glColor3ub(0, 0, 0);
	rectangle2(210, 290, 10, 20);
	//ShadingeyeheadrightUpLeft
	glColor3ub(0, 0, 0);
	rectangle2(200, 300, 10, 20);
	//ShadingeyeheadrightUpLeftLeft
	glColor3ub(0, 0, 0);
	rectangle2(190, 310, 10, 20);
	glPopMatrix();
}

//Finn's left hand
void handLeft() {

	glPushMatrix();
	glTranslated(60, -400, 0.0);

	//blacklininghand
	glColor3ub(0, 0, 0);
	rectangle(20, 80, 10, 80);
	//blackliningShirt shoulder left
	glColor3ub(0, 0, 0);
	rectangle(15, 85, 5, 75);

	//Handleft
	glColor3ub(255, 191, 128);
	rectangle(20, 85, 5, 70);
	//Shirt shoulder left
	glColor3ub(30, 144, 255);
	rectangle(20, 135, 5, 25);

	glPopMatrix();
}

//Left hand rotated
void rotateHand() {
	glPushMatrix();

	glTranslated(59.5 - counter / 6, -390 - counter - 3, 0);
	glRotated(90, 0, 0, 1);
	glScaled(-2.5, -0.375, 0);
	handLeft();

	glPopMatrix();

	gun();
}

//Left hand up (NO ROTATION) #UNUSED
void handLeftUp() {
	glPushMatrix();
	glTranslated(60, -400, 0.0);

	//blacklininghand
	glColor3ub(0, 0, 0);
	rectangle(-3, 153, 70, 15);
	rectangle(-3, 132, 70, 35);
	//blackliningShirt shoulder left
	glColor3ub(0, 0, 0);
	rectangle(25, 85, 15, 75);
	//Handleft
	glColor3ub(255, 191, 128);
	rectangle(0, 145, 65, 15);
	//Shirt shoulder left
	glColor3ub(30, 144, 255);
	rectangle(20, 137, 5, 23);
	glPopMatrix();

	gun();
}

//The bullet
void bullet() {

	glutPostRedisplay();
	glPushMatrix();
	glTranslated(-a + 155, -10, 0.0);
	glScaled(0.67, 1, 0);
	glColor3b(120, 10, 10);
	rectangle(-380, -280, 400, 100);
	glColor3b(120, 10, 10);
	rectangle(-400, -320, 400, 200);
	glColor3b(120, 10, 10);
	rectangle(-420, -370, 400, 300);
	glPopMatrix();
	glutPostRedisplay();
}

//Left hand in action
void hunterHandOut() {
	if (counter <= -100) {
		animal1();
		bullet();
		rotateHand();
		glutPostRedisplay();
	}
	else {
		animal();
		handLeft();
		glutPostRedisplay();
	}
}

void hunter()
{
	glPushMatrix();
	glTranslated(60, -400, 0.0);

	//blacklining head
	//blacklining1left
	glColor3ub(0, 0, 0);
	rectangle(20, 160, 5, 75);
	//blacklining1right
	glColor3ub(0, 0, 0);
	rectangle(80, 165, 5, 70);
	//blacklining2left
	glColor3ub(0, 0, 0);
	rectangle(25, 230, 10, 5);
	//blacklining2right
	glColor3ub(0, 0, 0);
	rectangle(70, 230, 10, 5);
	//blacklining3
	glColor3ub(0, 0, 0);
	rectangle(35, 220, 35, 5);
	//blacklining4left
	glColor3ub(0, 0, 0);
	rectangle(35, 225, 5, 5);
	//blacklining4right
	glColor3ub(0, 0, 0);
	rectangle(65, 225, 5, 5);
	//blacklining5
	glColor3ub(0, 0, 0);
	rectangle(85, 165, 5, 5);
	//blacklining6
	glColor3ub(0, 0, 0);
	rectangle(90, 160, 5, 5);
	//blacklining7
	glColor3ub(0, 0, 0);
	rectangle(95, 115, 5, 45);

	//blackliningbeg mostrightbottomleftbottom
	glColor3ub(0, 0, 0);
	rectangle(60, 85, 30, 60);
	//blackliningbeg mostrightbottom
	glColor3ub(0, 0, 0);
	rectangle(80, 80, 5, 5);
	//blacklininglegright
	glColor3ub(0, 0, 0);
	rectangle(65, 10, 15, 75);
	//blackliningstockin
	glColor3ub(0, 0, 0);
	rectangle(63, 5, 25, 15);
	//blacklininglegleft
	glColor3ub(0, 0, 0);
	rectangle(25, 10, 15, 135);
	//blackliningstockin
	glColor3ub(0, 0, 0);
	rectangle(20, 5, 25, 15);



	//face
	glColor3ub(255, 191, 128);
	rectangle(30, 170, 40, 45);
	//sidefaceleft
	glColor3ub(255, 191, 125);
	rectangle(25, 175, 5, 35);
	//sidefaceright
	glColor3ub(255, 191, 128);
	rectangle(70, 175, 5, 35);
	//forehead
	glColor3ub(255, 255, 255);
	rectangle(25, 215, 55, 5);

	//ear left
	glColor3ub(220, 220, 220);
	rectangle(25, 208, 5, 23);
	//smallsquareear
	glColor3ub(255, 255, 255);
	rectangle(30, 220, 5, 5);
	//smallsquareear
	glColor3ub(220, 220, 220);
	rectangle(30, 225, 5, 6);

	//ear right
	glColor3ub(220, 220, 220);
	rectangle(70, 208, 5, 23);
	//till jaw
	glColor3ub(255, 255, 255);
	rectangle(75, 170, 5, 55);
	//smallquareear
	glColor3ub(220, 220, 220);
	rectangle(75, 225, 5, 6);

	//neck right
	glColor3ub(255, 255, 255);
	rectangle(70, 170, 5, 10);
	//neck left
	glColor3ub(220, 220, 220);
	rectangle(25, 165, 5, 15);
	//neck
	glColor3ub(255, 255, 255);
	rectangle(25, 165, 55, 5);


	//body1
	glColor3ub(65, 105, 225);
	rectangle(30, 100, 45, 65);
	//body2
	glColor3ub(0, 191, 255);
	rectangle(35, 100, 40, 60);

	//beg shoulder left
	glColor3ub(173, 255, 47);
	rectangle(25, 150, 5, 15);
	//beg shoulder right
	glColor3ub(173, 255, 47);
	rectangle(75, 150, 5, 20);
	//beg right
	glColor3ub(173, 255, 47);
	rectangle(80, 155, 10, 10);
	//beg mostright
	glColor3ub(124, 252, 0);
	rectangle(85, 150, 10, 10);
	//beg mostrightbottomleftbottom
	glColor3ub(73, 255, 47);
	rectangle(85, 110, 10, 10);
	//beg mostrightbottom
	glColor3ub(50, 205, 50);
	rectangle(85, 115, 10, 40);
	//beg mostrightbottomleft
	glColor3ub(30, 200, 30);
	rectangle(85, 115, 5, 45);

	//handright
	glColor3ub(255, 191, 128);
	rectangle(80, 85, 5, 70);
	//shirt shoulder right
	glColor3ub(30, 144, 255);
	rectangle(80, 135, 5, 25);

	//legright
	glColor3ub(255, 191, 128);
	rectangle(70, 25, 5, 65);
	//stockin
	glColor3ub(255, 255, 255);
	rectangle(70, 18, 5, 7);
	//pant right
	glColor3ub(0, 0, 200);
	rectangle(70, 55, 5, 45);

	//legleft
	glColor3ub(255, 191, 128);
	rectangle(30, 25, 5, 65);
	//stockin
	glColor3ub(255, 255, 255);
	rectangle(30, 18, 5, 7);
	//pant right
	glColor3ub(0, 0, 200);
	rectangle(30, 55, 5, 45);
	//lowerboder
	glColor3ub(0, 0, 225);
	rectangle(30, 80, 45, 20);

	//eye left
	glColor3ub(0, 0, 0);
	rectangle(30, 195, 5, 7);
	//eye right
	glColor3ub(0, 0, 0);
	rectangle(65, 195, 5, 7);
	//mouth
	glColor3ub(0, 0, 0);
	rectangle(47, 180, 15, 5);

	//shoe left
	glBegin(GL_POLYGON);
	glColor3ub(105, 105, 105);
	glVertex2i(counter + 260 - 220, 55 - 36); //(x+ve-x-ve,y+ve-y-ve)
	glVertex2i(counter + 260 - 220, 46 - 36);
	glVertex2i(counter + 242 - 220, 46 - 36);
	glVertex2i(counter + 250 - 220, 55 - 36);
	glEnd();

	//shoe right
	glBegin(GL_POLYGON);
	glColor3ub(105, 105, 105);
	glVertex2i(counter + 290 - 220, 55 - 36);
	glVertex2i(counter + 290 - 220, 46 - 36);
	glVertex2i(counter + 308 - 220, 46 - 36);
	glVertex2i(counter + 300 - 220, 55 - 36);
	glEnd();

	glPopMatrix();
}
void hunter1()
{
	glPushMatrix();
	glTranslated(60, -400, 0.0);

	//blacklining head
	//blacklining1left
	glColor3ub(0, 0, 0);
	rectangle3(20, 160, 5, 75);
	//blacklining1right
	glColor3ub(0, 0, 0);
	rectangle3(80, 165, 5, 70);
	//blacklining2left
	glColor3ub(0, 0, 0);
	rectangle3(25, 230, 10, 5);
	//blacklining2right
	glColor3ub(0, 0, 0);
	rectangle3(70, 230, 10, 5);
	//blacklining3
	glColor3ub(0, 0, 0);
	rectangle3(35, 220, 35, 5);
	//blacklining4left
	glColor3ub(0, 0, 0);
	rectangle3(35, 225, 5, 5);
	//blacklining4right
	glColor3ub(0, 0, 0);
	rectangle3(65, 225, 5, 5);
	//blacklining5
	glColor3ub(0, 0, 0);
	rectangle3(85, 165, 5, 5);
	//blacklining6
	glColor3ub(0, 0, 0);
	rectangle3(90, 160, 5, 5);
	//blacklining7
	glColor3ub(0, 0, 0);
	rectangle3(95, 115, 5, 45);

	//blacklininghand
	glColor3ub(0, 0, 0);
	rectangle3(20, 80, 10, 65);
	//blackliningShirt shoulder left
	glColor3ub(0, 0, 0);
	rectangle3(15, 85, 5, 75);

	//Handleft
	glColor3ub(255, 191, 128);
	rectangle3(20, 85, 5, 70);
	//Shirt shoulder left
	glColor3ub(30, 144, 255);
	rectangle3(20, 135, 5, 25);

	//blackliningbeg mostrightbottomleftbottom
	glColor3ub(0, 0, 0);
	rectangle3(60, 85, 30, 60);
	//blackliningbeg mostrightbottom
	glColor3ub(0, 0, 0);
	rectangle3(80, 80, 5, 5);
	//blacklininglegright
	glColor3ub(0, 0, 0);
	rectangle3(65, 10, 15, 75);
	//blackliningstockin
	glColor3ub(0, 0, 0);
	rectangle3(63, 5, 25, 15);
	//blacklininglegleft
	glColor3ub(0, 0, 0);
	rectangle3(25, 10, 15, 135);
	//blackliningstockin
	glColor3ub(0, 0, 0);
	rectangle3(20, 5, 25, 15);



	//face
	glColor3ub(255, 191, 128);
	rectangle3(30, 170, 40, 45);
	//sidefaceleft
	glColor3ub(255, 191, 125);
	rectangle3(25, 175, 5, 35);
	//sidefaceright
	glColor3ub(255, 191, 128);
	rectangle3(70, 175, 5, 35);
	//forehead
	glColor3ub(255, 255, 255);
	rectangle3(25, 215, 55, 5);

	//ear left
	glColor3ub(220, 220, 220);
	rectangle3(25, 208, 5, 23);
	//smallsquareear
	glColor3ub(255, 255, 255);
	rectangle3(30, 220, 5, 5);
	//smallsquareear
	glColor3ub(220, 220, 220);
	rectangle3(30, 225, 5, 6);

	//ear right
	glColor3ub(220, 220, 220);
	rectangle3(70, 208, 5, 23);
	//till jaw
	glColor3ub(255, 255, 255);
	rectangle3(75, 170, 5, 55);
	//smallquareear
	glColor3ub(220, 220, 220);
	rectangle3(75, 225, 5, 6);

	//neck right
	glColor3ub(255, 255, 255);
	rectangle3(70, 170, 5, 10);
	//neck left
	glColor3ub(220, 220, 220);
	rectangle3(25, 165, 5, 15);
	//neck
	glColor3ub(255, 255, 255);
	rectangle3(25, 165, 55, 5);


	//body1
	glColor3ub(65, 105, 225);
	rectangle3(30, 100, 45, 65);
	//body2
	glColor3ub(0, 191, 255);
	rectangle3(35, 100, 40, 60);

	//beg shoulder left
	glColor3ub(173, 255, 47);
	rectangle3(25, 150, 5, 15);
	//beg shoulder right
	glColor3ub(173, 255, 47);
	rectangle3(75, 150, 5, 20);
	//beg right
	glColor3ub(173, 255, 47);
	rectangle3(80, 155, 10, 10);
	//beg mostright
	glColor3ub(124, 252, 0);
	rectangle3(85, 150, 10, 10);
	//beg mostrightbottomleftbottom
	glColor3ub(73, 255, 47);
	rectangle3(85, 110, 10, 10);
	//beg mostrightbottom
	glColor3ub(50, 205, 50);
	rectangle3(85, 115, 10, 40);
	//beg mostrightbottomleft
	glColor3ub(30, 200, 30);
	rectangle3(85, 115, 5, 45);

	//handright
	glColor3ub(255, 191, 128);
	rectangle3(80, 85, 5, 70);
	//shirt shoulder right
	glColor3ub(30, 144, 255);
	rectangle3(80, 135, 5, 25);

	//legright
	glColor3ub(255, 191, 128);
	rectangle3(70, 25, 5, 65);
	//stockin
	glColor3ub(255, 255, 255);
	rectangle3(70, 18, 5, 7);
	//pant right
	glColor3ub(0, 0, 200);
	rectangle3(70, 55, 5, 45);

	//legleft
	glColor3ub(255, 191, 128);
	rectangle3(30, 25, 5, 65);
	//stockin
	glColor3ub(255, 255, 255);
	rectangle3(30, 18, 5, 7);
	//pant right
	glColor3ub(0, 0, 200);
	rectangle3(30, 55, 5, 45);
	//lowerboder
	glColor3ub(0, 0, 225);
	rectangle3(30, 80, 45, 20);

	//eye left
	glColor3ub(0, 0, 0);
	rectangle3(30, 195, 5, 7);
	//eye right
	glColor3ub(0, 0, 0);
	rectangle3(65, 195, 5, 7);
	//mouth
	glColor3ub(0, 0, 0);
	rectangle3(47, 180, 15, 5);

	//shoe left
	glBegin(GL_POLYGON);
	glColor3ub(105, 105, 105);
	glVertex2i(finnmovementscene1 + 260 - 220, 55 - 36); //(x+ve-x-ve,y+ve-y-ve)
	glVertex2i(finnmovementscene1 + 260 - 220, 46 - 36);
	glVertex2i(finnmovementscene1 + 242 - 220, 46 - 36);
	glVertex2i(finnmovementscene1 + 250 - 220, 55 - 36);
	glEnd();

	//shoe right
	glBegin(GL_POLYGON);
	glColor3ub(105, 105, 105);
	glVertex2i(finnmovementscene1 + 290 - 220, 55 - 36);
	glVertex2i(finnmovementscene1 + 290 - 220, 46 - 36);
	glVertex2i(finnmovementscene1 + 308 - 220, 46 - 36);
	glVertex2i(finnmovementscene1 + 300 - 220, 55 - 36);
	glEnd();

	glPopMatrix();
}

void fullbodyHunter() {
	glPushMatrix();
	glLoadIdentity();

	if (counter > -100)
		counter = counter - 0.5;// x position will keep updating until reach coordinate

	glutPostRedisplay();
	hunterHandOut();
	hunter();
	glPopMatrix();
}
void MovementHunter1() {
	glPushMatrix();
	glLoadIdentity();

	if (finnmovementscene1 > -500)
		finnmovementscene1 = finnmovementscene1 - 0.5;// x position will keep updating until reach coordinate

	glutPostRedisplay();
	hunter1();
	glPopMatrix();
}

void theEnd() {
	glPushMatrix();

	glColor3ub(1, 1, 1);
	glTranslated(-180, count, 0.0);
	glScaled(0.5, 2, 0);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"THE END");

	glPopMatrix();

}

void wordMovement() {

	glPushMatrix();
	glLoadIdentity();

	if (count < -100)
		count = count + 0.5;// y position will keep updating until reach coordinate

	glutPostRedisplay();
	theEnd();
	glPopMatrix();
}

void Scene1() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3ub(0, 100, 255);
	sunPos(-300, 460, 0.5, 1.5);

	glPushMatrix();

	glTranslated(a, 500, 0.0);

	cloudPos(300, -60, 0.3, 0.4);
	cloudPos(160, 0, 0.3, 0.3);
	cloudPos(100, 0, 0.7, 0.7);
	cloudPos(40, -30, 0.3, 0.3);
	cloudPos(-125, -20, 0.5, 0.5);
	cloudPos(-300, -40, 0.4, 0.4);

	cloudPos(-400, -30, 0.4, 0.4);
	cloudPos(-480, 0, 0.7, 0.7);
	cloudPos(-550, -20, 0.5, 0.5);
	cloudPos(-750, -30, 0.3, 0.3);
	cloudPos(-830, 0, 0.7, 0.7);
	cloudPos(-910, -20, 0.5, 0.5);

	///////////////////////////////////////////////////

	cloudPos(-400 - b, -30, 0.4, 0.4);
	cloudPos(-480 - b, 0, 0.7, 0.7);
	cloudPos(-550 - b, -20, 0.5, 0.5);
	cloudPos(-750 - b, -30, 0.3, 0.3);
	cloudPos(-830 - b, 0, 0.7, 0.7);
	cloudPos(-910 - b, -20, 0.5, 0.5);

	cloudPos(-400 - b - c, -30, 0.4, 0.4);
	cloudPos(-480 - b - c, 0, 0.7, 0.7);
	cloudPos(-550 - b - c, -20, 0.5, 0.5);
	cloudPos(-750 - b - c, -30, 0.3, 0.3);
	cloudPos(-830 - b - c, 0, 0.7, 0.7);
	cloudPos(-910 - b - c, -20, 0.5, 0.5);

	glPopMatrix();

	treePos(-250, 450);
	ground(X, Y, SCREEN_WIDTH, SCREEN_HEIGHT);

	roof(0, 0, 300);
	house();
	MovementHunter1();

	glFlush();
	glutSwapBuffers();


}

void Scene2() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3ub(0, 100, 255);
	sunPos(-300, 460, 0.5, 1.5);


	glPushMatrix();
	glTranslated(a, 500, 0.0);

	cloudPos(300, -60, 0.3, 0.4);
	cloudPos(160, 0, 0.3, 0.3);
	cloudPos(100, 0, 0.7, 0.7);
	cloudPos(40, -30, 0.3, 0.3);
	cloudPos(-125, -20, 0.5, 0.5);
	cloudPos(-300, -40, 0.4, 0.4);

	cloudPos(-400, -30, 0.4, 0.4);
	cloudPos(-480, 0, 0.7, 0.7);
	cloudPos(-550, -20, 0.5, 0.5);
	cloudPos(-750, -30, 0.3, 0.3);
	cloudPos(-830, 0, 0.7, 0.7);
	cloudPos(-910, -20, 0.5, 0.5);

	///////////////////////////////////////////////////

	cloudPos(-400 - b, -30, 0.4, 0.4);
	cloudPos(-480 - b, 0, 0.7, 0.7);
	cloudPos(-550 - b, -20, 0.5, 0.5);
	cloudPos(-750 - b, -30, 0.3, 0.3);
	cloudPos(-830 - b, 0, 0.7, 0.7);
	cloudPos(-910 - b, -20, 0.5, 0.5);

	cloudPos(-400 - b - c, -30, 0.4, 0.4);
	cloudPos(-480 - b - c, 0, 0.7, 0.7);
	cloudPos(-550 - b - c, -20, 0.5, 0.5);
	cloudPos(-750 - b - c, -30, 0.3, 0.3);
	cloudPos(-830 - b - c, 0, 0.7, 0.7);
	cloudPos(-910 - b - c, -20, 0.5, 0.5);

	glPopMatrix();

	wordMovement();
	treePos(-250, 450);
	ground(X, Y, SCREEN_WIDTH, SCREEN_HEIGHT);

	fullbodyHunter();

	treePos(250, 490);
	
	glFlush();
	glutSwapBuffers();
}

void Animation() {
	if (finnmovementscene1 >= -490) {
		Scene1();
		glutPostRedisplay();
	}
	else {
		Scene2();
		glutPostRedisplay();
	}
}

void display() {
	Animation();
}

int main(int argc, char** argv) {

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("HUNTER HUNTS");
	initOpenGl();
	glutDisplayFunc(display);
	sun2();
	glutTimerFunc(100, update, 0);

	glutMainLoop();
}
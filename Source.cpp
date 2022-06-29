#include <GLFW\glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <time.h>

using namespace std;

const float DEG2RAD = 3.14159 / 180;

void processInput(GLFWwindow* window);

enum BRICKTYPE { REFLECTIVE, DESTRUCTABLE };
enum ONOFF { ON, OFF };

class Brick
{
public:
	float red, green, blue;
	float x, y, width;
	BRICKTYPE brick_type;
	ONOFF onoff;

	Brick(BRICKTYPE bt, float xx, float yy, float ww, float rr, float gg, float bb)
	{
		brick_type = bt; x = xx; y = yy, width = ww; red = rr, green = gg, blue = bb;
		onoff = ON;
	};

	void drawBrick()
	{
		if (onoff == ON)
		{
			double halfside = width / 2;

			glColor3d(red, green, blue);
			glBegin(GL_POLYGON);

			glVertex2d(x + halfside, y + halfside);
			glVertex2d(x + halfside, y - halfside);
			glVertex2d(x - halfside, y - halfside);
			glVertex2d(x - halfside, y + halfside);

			glEnd();
		}
	}
};


class Circle
{
public:
	float red, green, blue;
	float radius;
	float x;
	float y;
	float speed = 0.03;
	int direction; // 1=up 2=right 3=down 4=left 5 = up right   6 = up left  7 = down right  8= down left

	Circle(double xx, double yy, double rr, int dir, float rad, float r, float g, float b)
	{
		x = xx;
		y = yy;
		radius = rr;
		red = r;
		green = g;
		blue = b;
		radius = rad;
		direction = dir;
	}

	void CheckCollision(Brick* brk)
	{
		if (brk->brick_type == REFLECTIVE)
		{
			if ((x > brk->x - brk->width && x <= brk->x + brk->width) && (y > brk->y - brk->width && y <= brk->y + brk->width))
			{
				direction = GetRandomDirection();
				x = x + 0.03;
				y = y + 0.04;
			}
		}
		else if (brk->brick_type == DESTRUCTABLE)
		{
			if ((x > brk->x - brk->width && x <= brk->x + brk->width) && (y > brk->y - brk->width && y <= brk->y + brk->width))
			{
				brk->onoff = OFF;
			}
		}
	}

	int GetRandomDirection()
	{
		return (rand() % 8) + 1;
	}

	void MoveOneStep()
	{
		if (direction == 1 || direction == 5 || direction == 6)  // up
		{
			if (y > -1 + radius)
			{
				y -= speed;
			}
			else
			{
				direction = GetRandomDirection();
			}
		}

		if (direction == 2 || direction == 5 || direction == 7)  // right
		{
			if (x < 1 - radius)
			{
				x += speed;
			}
			else
			{
				direction = GetRandomDirection();
			}
		}

		if (direction == 3 || direction == 7 || direction == 8)  // down
		{
			if (y < 1 - radius) {
				y += speed;
			}
			else
			{
				direction = GetRandomDirection();
			}
		}

		if (direction == 4 || direction == 6 || direction == 8)  // left
		{
			if (x > -1 + radius) {
				x -= speed;
			}
			else
			{
				direction = GetRandomDirection();
			}
		}
	}

	void DrawCircle()
	{
		glColor3f(red, green, blue);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++) {
			float degInRad = i * DEG2RAD;
			glVertex2f((cos(degInRad) * radius) + x, (sin(degInRad) * radius) + y);
		}
		glEnd();
	}
};


vector<Circle> world;


int main(void) {
	srand(time(NULL));

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(480, 480, "Sergio Udave Checkerboard!", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);


	// Bottom Row
	Brick brick5(DESTRUCTABLE, -0.8, -0.3, 0.2, 1, 0.5, 0.5);
	Brick brick6(REFLECTIVE, -0.6,   -0.3, 0.2, 1, 0.5, 0.5);
	Brick brick7(DESTRUCTABLE, -0.4, -0.3, 0.2, 1, 0.5, 0.5);
	Brick brick8(REFLECTIVE, -0.2,   -0.3, 0.2, 1, 0.5, 0.5);
	Brick brick9(DESTRUCTABLE, 0,    -0.3, 0.2, 1, 0.5, 0.5);
	Brick brick10(REFLECTIVE, 0.2,   -0.3, 0.2, 1, 0.5, 0.5);
	Brick brick11(DESTRUCTABLE, 0.4, -0.3, 0.2, 1, 0.5, 0.5);
	Brick brick12(REFLECTIVE, 0.6,   -0.3, 0.2, 1, 0.5, 0.5);
	Brick brick13(DESTRUCTABLE, 0.8, -0.3, 0.2, 1, 0.5, 0.5);

	// Next Row
	Brick brick15(DESTRUCTABLE, -1.0, -0.1, 0.2, 1, 0.5, 0.5);
	Brick brick16(REFLECTIVE, -0.8,   -0.1, 0.2, 1, 0.5, 0.5);
	Brick brick17(DESTRUCTABLE, -0.6, -0.1, 0.2, 1, 0.5, 0.5);
	Brick brick18(REFLECTIVE, -0.4,   -0.1, 0.2, 1, 0.5, 0.5);
	Brick brick19(DESTRUCTABLE, -0.2, -0.1, 0.2, 1, 0.5, 0.5);
	Brick brick20(REFLECTIVE, 0,      -0.1, 0.2, 1, 0.5, 0.5);
	Brick brick21(DESTRUCTABLE, 0.2,  -0.1, 0.2, 1, 0.5, 0.5);
	Brick brick22(REFLECTIVE, 0.4,    -0.1, 0.2, 1, 0.5, 0.5);
	Brick brick23(DESTRUCTABLE, 0.6,  -0.1, 0.2, 1, 0.5, 0.5);
	Brick brick24(REFLECTIVE, 0.8,    -0.1, 0.2, 1, 0.5, 0.5);
	Brick brick25(DESTRUCTABLE, 1.0,  -0.1, 0.2, 1, 0.5, 0.5);

	// Middle Row
	Brick brick30(DESTRUCTABLE, -0.8, 0.1, 0.2, 1, 0.5, 0.5);
	Brick brick31(REFLECTIVE, -0.6, 0.1, 0.2, 1, 0.5, 0.5);
	Brick brick32(DESTRUCTABLE, -0.4, 0.1, 0.2, 1, 0.5, 0.5);
	Brick brick33(REFLECTIVE, -0.2, 0.1, 0.2, 1, 0.5, 0.5);
	Brick brick34(DESTRUCTABLE, 0, 0.1, 0.2, 1, 0.5, 0.5);
	Brick brick35(REFLECTIVE, 0.2, 0.1, 0.2, 1, 0.5, 0.5);
	Brick brick36(DESTRUCTABLE, 0.4, 0.1, 0.2, 1, 0.5, 0.5);
	Brick brick37(REFLECTIVE, 0.6, 0.1, 0.2, 1, 0.5, 0.5);
	Brick brick38(DESTRUCTABLE, 0.8, 0.1, 0.2, 1, 0.5, 0.5);

	// Top Row
	Brick brick39(DESTRUCTABLE, -1.0, 0.3, 0.2, 1, 0.5, 0.5);
	Brick brick40(REFLECTIVE, -0.8, 0.3, 0.2, 1, 0.5, 0.5);
	Brick brick41(DESTRUCTABLE, -0.6, 0.3, 0.2, 1, 0.5, 0.5);
	Brick brick42(REFLECTIVE, -0.4, 0.3, 0.2, 1, 0.5, 0.5);
	Brick brick43(DESTRUCTABLE, -0.2, 0.3, 0.2, 1, 0.5, 0.5);
	Brick brick44(REFLECTIVE, 0, 0.3, 0.2, 1, 0.5, 0.5);
	Brick brick45(DESTRUCTABLE, 0.2, 0.3, 0.2, 1, 0.5, 0.5);
	Brick brick46(REFLECTIVE, 0.4, 0.3, 0.2, 1, 0.5, 0.5);
	Brick brick47(DESTRUCTABLE, 0.6, 0.3, 0.2, 1, 0.5, 0.5);
	Brick brick48(REFLECTIVE, 0.8, 0.3, 0.2, 1, 0.5, 0.5);
	Brick brick49(DESTRUCTABLE, 1.0, 0.3, 0.2, 1, 0.5, 0.5);


	while (!glfwWindowShouldClose(window)) {
		//Setup View
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);

		//Movement
		for (int i = 0; i < world.size(); i++)
		{
			world[i].CheckCollision(&brick5);
			world[i].CheckCollision(&brick6);
			world[i].CheckCollision(&brick7);
			world[i].CheckCollision(&brick8);
			world[i].CheckCollision(&brick9);
			world[i].CheckCollision(&brick10);
			world[i].CheckCollision(&brick11);
			world[i].CheckCollision(&brick12);
			world[i].CheckCollision(&brick13);
			world[i].CheckCollision(&brick15);
			world[i].CheckCollision(&brick16);
			world[i].CheckCollision(&brick17);
			world[i].CheckCollision(&brick18);
			world[i].CheckCollision(&brick19);
			world[i].CheckCollision(&brick20);
			world[i].CheckCollision(&brick21);
			world[i].CheckCollision(&brick22);
			world[i].CheckCollision(&brick23);
			world[i].CheckCollision(&brick24);
			world[i].CheckCollision(&brick25);
			world[i].CheckCollision(&brick30);
			world[i].CheckCollision(&brick31);
			world[i].CheckCollision(&brick32);
			world[i].CheckCollision(&brick33);
			world[i].CheckCollision(&brick34);
			world[i].CheckCollision(&brick35);
			world[i].CheckCollision(&brick36);
			world[i].CheckCollision(&brick37);
			world[i].CheckCollision(&brick38);
			world[i].CheckCollision(&brick39);
			world[i].CheckCollision(&brick40);
			world[i].CheckCollision(&brick41);
			world[i].CheckCollision(&brick42);
			world[i].CheckCollision(&brick43);
			world[i].CheckCollision(&brick44);
			world[i].CheckCollision(&brick45);
			world[i].CheckCollision(&brick46);
			world[i].CheckCollision(&brick47);
			world[i].CheckCollision(&brick48);
			world[i].CheckCollision(&brick49);
			world[i].MoveOneStep();
			world[i].DrawCircle();

		}

		brick5.drawBrick();
		brick6.drawBrick();
		brick7.drawBrick();
		brick8.drawBrick();
		brick9.drawBrick();
		brick10.drawBrick();
		brick11.drawBrick();
		brick12.drawBrick();
		brick13.drawBrick();
		brick15.drawBrick();
		brick16.drawBrick();
		brick17.drawBrick();
		brick18.drawBrick();
		brick19.drawBrick();
		brick20.drawBrick();
		brick21.drawBrick();
		brick22.drawBrick();
		brick23.drawBrick();
		brick24.drawBrick();
		brick25.drawBrick();
		brick30.drawBrick();
		brick31.drawBrick();
		brick32.drawBrick();
		brick33.drawBrick();
		brick34.drawBrick();
		brick35.drawBrick();
		brick36.drawBrick();
		brick37.drawBrick();
		brick38.drawBrick();
		brick39.drawBrick();
		brick40.drawBrick();
		brick41.drawBrick();
		brick42.drawBrick();
		brick43.drawBrick();
		brick44.drawBrick();
		brick45.drawBrick();
		brick46.drawBrick();
		brick47.drawBrick();
		brick48.drawBrick();
		brick49.drawBrick();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate;
	exit(EXIT_SUCCESS);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		double r, g, b;
		r = rand() / 10000;
		g = rand() / 10000;
		b = rand() / 10000;
		Circle B(0, 0, 02, 2, 0.05, r, g, b);
		world.push_back(B);
	}
}
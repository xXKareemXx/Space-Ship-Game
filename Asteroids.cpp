#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

class Asteroids{
	public:
	    int x = 5 + rand() % 90;
        int y = 100;
        int r = 3;
        int color = 1 + rand() % 3;
		void Circle(float cx, float cy, float radius, int num_segments, int color)
		{
                if (color == 1)
		            glColor3f(1, 0, 0);
		        else if (color == 2)
		            glColor3f(0, 1, 0);
		        else
		            glColor3f(0, 0, 1);
		        glBegin(GL_POLYGON);
		        for (int i = 0; i < num_segments; i++)
                    {
		            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); //get the current angle in radians
		            float x = radius * cosf(theta);                                   //calculate the x component
		            float y = radius * sinf(theta);                                   //calculate the y component
		            glVertex2f(x + cx, y + cy);                                       //output vertex
                }
	        glEnd();
        }
        void ReCreate()
        {
            x = 10 + rand() % 100;
            y = 100;
            color = 1 + rand() % 3;
        }
        void Create()
        {
            Circle(x, y, r, 300, color);
        }
};

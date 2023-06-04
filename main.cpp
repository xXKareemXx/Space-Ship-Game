#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Asteroids.cpp"

using namespace std;

int phyWidth = 800;
int phyHeight = 700;

int logWidth = 100;
int logHeight = 100;

int centerX = logWidth / 2;
int centerY = logHeight / 2;

int mouseX = centerX;
int mouseY = centerY;

int AsterNum = 25;  //Number of Asteroids
int GameTime = 21;   //Total game time

int LaserColor = 1; //The LaseBeam's initial color
int Score = 0;   //Initial scoring

bool state = 1;   //State of the game

Asteroids ast = Asteroids();    //Create an object of asteroids

/*---------------------Score&Time_Texts---------------------*/
void Text(string str,float x,float y, float r, float g, float b)
{
    glColor3f (r, g, b);
    glRasterPos2d(x,y);
    for (auto c: str)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    glFlush();
}

/*---------------------Game_Over---------------------*/
void EndGame()
{
    glClear(GL_COLOR_BUFFER_BIT);
    stringstream ss3;
    string s3;
    ss3 << Score;
    ss3 >> s3;
    Text("TIME'S UP", centerX-8, centerY+10, 1, 0, 0);
    Text("\nScore: " + s3, centerX-5, centerY-5, 0, 0, 1);
    Text("\nPress 'F1' to play again", centerX-14,centerY-10, 1, 1, 1);

}

/*---------------------Replay---------------------*/
void Restart(int key, int x, int y)
{
    if(key == GLUT_KEY_F1)
    {
        Score = 0;
        GameTime = 21;
        AsterNum = 25;
        state = 1;
    }
}

/*---------------------Starts_In_Space---------------------*/
void Stars()
{
    glColor3f(1, 1, 1);
        glPointSize(2);
        glBegin(GL_POINTS);
        for( int i = 1; i < 1000; i++ )
        {
            int x = rand() % 500;
            int y = rand() % 500;
            glVertex2i(x, y);
        }
    glEnd();
}

/*---------------------Rocket_Shape---------------------*/
void Rocket(int x, int y, int LaserColor)
{
        //Rocket Body
        glColor3f(.2, .2, .2);
        glBegin(GL_POLYGON);
        glVertex2f(x - 3, y + 4);
        glVertex2f(x + 3, y + 4);
        glVertex2f(x + 3, y - 4);
        glVertex2f(x - 3, y - 4);
        glEnd();

        //Rocket Head
        glColor3f(.5, .5, .5);
        glBegin(GL_POLYGON);
        glVertex2f(x - 3, y + 4);
        glVertex2f(x + 3, y + 4);
        glVertex2f(x, y + 8);
        glEnd();

        //Rocket Left Wing
        glColor3f(.5, .5, .5);
        glBegin(GL_POLYGON);
        glVertex2f(x - 3, y - 4);
        glVertex2f(x - 6, y - 4);
        glVertex2f(x - 3, y);
        glEnd();

        //Rocket Right Wing
        glColor3f(.5, .5, .5);
        glBegin(GL_POLYGON);
        glVertex2f(x + 3, y - 4);
        glVertex2f(x + 6, y - 4);
        glVertex2f(x + 3, y);
        glEnd();

        //Rocket Fire
        glColor3f(0.9, 0.33, 0.15);
        glBegin(GL_POLYGON);
        glVertex2f(x - 2, y - 4);
        glVertex2f(x + 2, y - 4);
        glVertex2f(x + 2, y - 5);
        glVertex2f(x - 2, y - 5);
        glEnd();

        //Laser Beam
        switch(LaserColor){
        case 1:
            glColor3f(1,0,0);
            break;
        case 2:
            glColor3f(0,1,0);
            break;
        case 3:
            glColor3f(0,0,1);
            break;
        }

        glBegin(GL_POLYGON);
        glVertex2f(x, y + 8);
        glVertex2f(x + 3, y + 10);
        glVertex2f(x + 3, y + logHeight);
        glVertex2f(x - 3, y + logHeight);
        glVertex2f(x - 3, y + 10);
        glEnd();
}


/*---------------------Asteroids_Falling---------------------*/
void Aster(){
    ast.Create();
    ast.y -= 0.5;
    if (!ast.y){
        AsterNum--;
        ast.ReCreate();
    }
    int LaserX1 = mouseX-3, LaserX2 = mouseX+3;
    int LaserY = mouseY+8;
    if(ast.color == LaserColor && ast.x >= LaserX1 && ast.x <= LaserX2 && ast.y > LaserY){
        Score++;
        ast.y = 0;
    }
}

/*---------------------Timers_For_Redisplaying---------------------*/
void Timer(int val)
{
    glutTimerFunc(10, Timer, val);
    glutPostRedisplay();
}
void DecTimer(int val)
{
    GameTime--;
    if(GameTime <= 0 || AsterNum <= 0){
        EndGame();
        state = 0;
    }
    glutTimerFunc(1000, DecTimer, val);
    glutPostRedisplay();
}

/*---------------------Laser---------------------*/
void ChangeLaser(unsigned char key, int x, int y)
{
    if(key==' ') LaserColor++;
    if(LaserColor > 3) LaserColor = 1;
    glutPostRedisplay();
}

/*---------------------Mouse_Motion---------------------*/
void passiveMouse(int x, int y)
{
    mouseX = x;
    mouseX = 0.5 + 1 * mouseX * logWidth / phyWidth;
    mouseY = phyHeight - y;
    mouseY = 0.5 + 1 * mouseY * logHeight / phyHeight;
    glutPostRedisplay();
}

/*--------------------Game_Displaying---------------------*/
void display()
{
    if(state){
        glClear(GL_COLOR_BUFFER_BIT);
        Rocket(mouseX, mouseY, LaserColor);
        Stars();
        Aster();
        stringstream ss1;
        string s1;
        ss1 << Score;
        ss1 >> s1;
        Text("Score: " + s1, 2, 95, 1, 1, 1);
        stringstream ss2;
        string s2;
        ss2 << GameTime;
        ss2 >> s2;
        Text("Time: " + s2, 88, 95, 1, 1, 1);
    }
    if(GameTime <= 0 || AsterNum <= 0){
        EndGame();
        state = 0;
    }
    glutSwapBuffers();
    glFlush();
}

/*---------------------Initial_Window---------------------*/
void init()
{
    glClearColor( 0, 0, 0, 0); // COLOR BACKGROUND
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D( 0, logWidth, 0, logHeight);

}

/*---------------------Program_Entry---------------------*/
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(phyWidth, phyHeight);
    glutInitWindowPosition(logWidth, logHeight);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("THE SPACESHIP GAME");
    init();
    glutDisplayFunc(display);

    glutKeyboardFunc(ChangeLaser);
    glutPassiveMotionFunc(passiveMouse);
    glutSpecialFunc(Restart);

    Timer(0);
    DecTimer(0);

    glutMainLoop();
    return EXIT_SUCCESS;
}

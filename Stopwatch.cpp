/*Name: Mansi Gupta
Date: 22/5/2021

Description: STOPWATCH USING GLUT
Keyboard key 'r' or 'R': to Restart
Keyboard key 's' or 'S': to Stop and Start */


#include<Windows.h>    // first include Windows.h header file which is required    
#include<stdio.h>    
#include<gl/GL.h>   // GL.h header file    
#include<gl/GLU.h> // GLU.h header file    
#include<gl/glut.h>  // glut.h header file from freeglut\include\GL folder    
#include<conio.h>    
#include<iostream> 
#include<math.h> 
# define PI 3.14

using namespace std;
int height = 500;
int width = 500;
int secTikAngle, minTikAngle = 0;
const int font = (int)GLUT_BITMAP_9_BY_15;
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
float theta;
int frame = 16;
bool stop = TRUE;

void Display_Objects(void);
void renderBitmapString(float x, float y, void* font, const char* string);
void Init_OpenGL();
void Reshape(int w, int h);
void timer(int);



void keyUp(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R')
    {
        secTikAngle = 0;
        minTikAngle = 0;
    }
    if (key == 's' || key == 'S')
    {
        stop = !stop;
    }
}

int main(int argc, char** argv)
{     
    glutInit(&argc, argv); // glut Initialize
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //glut Display Mode  
    glutInitWindowSize(width, height);   // Window Size
    glutInitWindowPosition(50, 50);  // Window position  
    glutCreateWindow("Stop Watch");  //Window Name
     
    Init_OpenGL(); //Opengl Initialize
    glutDisplayFunc(Display_Objects);        //glut Display Function 
    glutTimerFunc(1000 / frame, timer, 0);  //glut timer Function 
    glutReshapeFunc(Reshape);               //glut Reshape Function 
    glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events
    //glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
    glutMainLoop();
    return 0;
}

void Init_OpenGL()
{     
    glClearColor(0.0, 0.0, 0.0, 0.0);  // set background color to Black    
}

void timer(int)
{
    Display_Objects();
    glutTimerFunc(1000 / 1, timer, 0);
}

void renderBitmapString(float x, float y, void* font, const char* string) 
{
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void Reshape(int w, int h)
{     
    height = h;
    width = w;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-(w / 2), (w / 2), -(h / 2), (h / 2)); 
}

void Display_Objects(void)
{
    int watchRadius = height / 2;
    glMatrixMode(GL_MODELVIEW);
    // again  load the identity of matrix    
    glLoadIdentity();

    // clearing the window or remove all drawn objects    
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);

    //Outer Circle
    for (float i = 0; i <= 359; i++)
    {
        double theta1 = i * (PI / 180);
        float x1 = watchRadius * cos(theta1);
        float y1 = watchRadius * sin(theta1);

        double theta2 = (i + 1) * (PI / 180);
        float x2 = watchRadius * cos(theta2);
        float y2 = watchRadius * sin(theta2);
        glLineWidth(2.5);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex3f(x1, y1, 0);
        glVertex3f(x2, y2, 0);
        glEnd();
    }

    //Center Point
    glPointSize(4.5);
    glBegin(GL_POINTS);
    glVertex3f(0, 0, 0);
    glEnd();

    //points of each min
    for (int i = 12; i >0; i--)
    {
        string num;
        char snum[3];
        _itoa_s(i, snum, 10);
        num.append(snum);
        glColor3f(0.0, 0.0, 0.0);
        float theta1 = ((i) * 30) * (PI / 180.0f);
        float x1 = watchRadius * 0.90f * sin(theta1);
        float y1 = watchRadius * 0.90f * cos(theta1);
        renderBitmapString(x1, y1, (void*)font1, num.c_str());
    }

    if (stop == FALSE)
    {
        secTikAngle += 6;
    }

    if (secTikAngle == 360)
    {
        if (stop == FALSE)
        {
            minTikAngle += 6;            
        }

        secTikAngle = 0;
    }

    double theta3 = (90 - secTikAngle) * (PI / 180);
    float x3 = watchRadius * 0.85f * cos(theta3);
    float y3 = watchRadius * 0.85f * sin(theta3);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.25, 0.25, 0);
    glVertex3f(x3, y3, 0);
    glEnd();

    if (minTikAngle == 360)
    {
        minTikAngle = 0;
    }

    double theta4 = (90 - minTikAngle) * (PI / 180);
    float x4 = watchRadius * 0.55f * cos(theta4);
    float y4 = watchRadius * 0.55f * sin(theta4);

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.25, 0.25, 0);
    glVertex3f(x4, y4, 0);
    glEnd();

    string m;
    char snum[3];
    m.append("Timer -> ");
    _itoa_s((minTikAngle / 6), snum, 10);
    m.append(snum);
    m.append(":");
    _itoa_s((secTikAngle / 6), snum, 10);
    m.append(snum);
    auto xCoord = (-5.0f) * m.size();
    renderBitmapString(xCoord, xCoord, (void*)font, m.c_str());
    renderBitmapString(-(height / 8.0f), -(height / 4.0f), (void*)font, "Mansi Gupta");

    glutSwapBuffers();
}



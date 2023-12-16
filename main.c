#include <GL/glut.h>

#include <stdbool.h>

#include <math.h>



#define SOL_RADIUS 0.5

#define EARTH_RADIUS 0.2

#define PLANET1_RADIUS 0.1

#define PLANET2_RADIUS 0.15



GLfloat sunAngle = 0.0;

GLfloat earthAngle = 0.0;

GLfloat planet1Angle = 0.0;

GLfloat planet2Angle = 0.0;



GLfloat cameraDistance = 5.0;

GLfloat cameraAngleX = 45.0;

GLfloat cameraAngleY = 45.0;

GLfloat lastX = 0.0;

GLfloat lastY = 0.0;

GLboolean isDragging = false;



GLfloat sunColor[] = {1.0, 1.0, 0.0, 1.0}; // Amarelo

GLfloat earthColor[] = {0.0, 0.0, 1.0, 1.0}; // Azul

GLfloat planet1Color[] = {1.0, 0.0, 0.0, 1.0}; // Vermelho

GLfloat planet2Color[] = {0.0, 1.0, 0.0, 1.0}; // Verde



GLfloat sunPosition[] = {0.0, 0.0, 0.0, 1.0};

GLfloat planet1Position[] = {2.0, 0.0, 0.0, 1.0};

GLfloat planet2Position[] = {-3.0, 0.0, 0.0, 1.0};



// Posições das luzes na borda do Sol

GLfloat lightPositions[][4] = {

    {1.5, 0.0, 0.0, 1.0},

    {-1.5, 0.0, 0.0, 1.0},

    {0.0, 1.5, 0.0, 1.0},

    {0.0, -1.5, 0.0, 1.0},

    {1.06, 1.06, 0.0, 1.0},

    {-1.06, 1.06, 0.0, 1.0},

    {1.06, -1.06, 0.0, 1.0},

    {-1.06, -1.06, 0.0, 1.0},

};



void drawSphere(GLfloat radius, GLfloat slices, GLfloat stacks, GLfloat* color) {

    GLUquadricObj *quadric = gluNewQuadric();

    gluQuadricDrawStyle(quadric, GLU_FILL);



    glMaterialfv(GL_FRONT, GL_DIFFUSE, color); // Definir a cor do material



    gluSphere(quadric, radius, slices, stacks);



    gluDeleteQuadric(quadric);

}



void drawSun() {

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);



    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunColor);

    

    // Luzes adicionais na borda do Sol

    for (int i = 1; i <= 7; ++i) {

        glEnable(GL_LIGHT0 + i);

        glLightfv(GL_LIGHT0 + i, GL_POSITION, lightPositions[i - 1]);

        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, sunColor);

    }



    drawSphere(SOL_RADIUS, 50, 50, sunColor);

    // Desativar todas as luzes adicionais

    for (int i = 1; i <= 7; ++i) {

        glDisable(GL_LIGHT0 + i);

    }

    glDisable(GL_LIGHTING);

    glDisable(GL_LIGHT0);

}



void drawEarth() {

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);



    glLightfv(GL_LIGHT0, GL_POSITION, sunPosition); // Posição da luz no Sol

    glLightfv(GL_LIGHT0, GL_DIFFUSE, earthColor);



    glRotatef(earthAngle, 0.0, 1.0, 0.0);

    glTranslatef(1.5, 0.0, 0.0);



    drawSphere(EARTH_RADIUS, 30, 30, earthColor);



    glDisable(GL_LIGHTING);

    glDisable(GL_LIGHT0);

}



void drawPlanet1() {

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT1);



    glLightfv(GL_LIGHT1, GL_POSITION, planet1Position); // Posição da luz no planeta1

    glLightfv(GL_LIGHT1, GL_DIFFUSE, planet1Color);



    glRotatef(planet1Angle, 0.0, 1.0, 0.0);

    glTranslatef(2.0, 0.0, 0.0);



    drawSphere(PLANET1_RADIUS, 20, 20, planet1Color);



    glDisable(GL_LIGHTING);

    glDisable(GL_LIGHT1);

}



void drawPlanet2() {

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT2);



    glLightfv(GL_LIGHT2, GL_POSITION, planet2Position); // Posição da luz no planeta2

    glLightfv(GL_LIGHT2, GL_DIFFUSE, planet2Color);



    glRotatef(planet2Angle, 0.0, 1.0, 0.0);

    glTranslatef(-3.0, 0.0, 0.0);



    drawSphere(PLANET2_RADIUS, 25, 25, planet2Color);



    glDisable(GL_LIGHTING);

    glDisable(GL_LIGHT2);

}



void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();



    gluLookAt(

        cameraDistance * sin(cameraAngleY * 3.14159 / 180.0) * cos(cameraAngleX * 3.14159 / 180.0),

        cameraDistance * sin(cameraAngleX * 3.14159 / 180.0),

        cameraDistance * cos(cameraAngleY * 3.14159 / 180.0) * cos(cameraAngleX * 3.14159 / 180.0),

        0.0, 0.0, 0.0,

        0.0, 1.0, 0.0

    );



    glPushMatrix();

    drawSun();

    glPopMatrix();



    glPushMatrix();

    drawEarth();

    glPopMatrix();



    glPushMatrix();

    drawPlanet1();

    glPopMatrix();



    glPushMatrix();

    drawPlanet2();

    glPopMatrix();



    glutSwapBuffers();

}



void reshape(int width, int height) {

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}



void update(int value) {

    sunAngle += 0.5;

    earthAngle += 1.0;

    planet1Angle += 0.8;

    planet2Angle += 0.4;



    if (earthAngle > 360.0) {

        earthAngle -= 360.0;

    }



    if (planet1Angle > 360.0) {

        planet1Angle -= 360.0;

    }



    if (planet2Angle > 360.0) {

        planet2Angle -= 360.0;

    }



    glutPostRedisplay();

    glutTimerFunc(16, update, 0);

}



void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON) {

        if (state == GLUT_DOWN) {

            isDragging = true;

            lastX = x;

            lastY = y;

        } else if (state == GLUT_UP) {

            isDragging = false;

        }

    }

}



void motion(int x, int y) {

    if (isDragging) {

        GLfloat sensitivity = 0.1;

        GLfloat deltaX = x - lastX;

        GLfloat deltaY = y - lastY;



        cameraAngleX += deltaY * sensitivity;

        cameraAngleY += deltaX * sensitivity;



        if (cameraAngleX > 89.0) cameraAngleX = 89.0;

        if (cameraAngleX < -89.0) cameraAngleX = -89.0;



        lastX = x;

        lastY = y;



        glutPostRedisplay();

    }

}



int main(int argc, char **argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow("Sistema Solar com Iluminação");

    glEnable(GL_DEPTH_TEST);



    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutTimerFunc(25, update, 0);

    glutMouseFunc(mouse);

    glutMotionFunc(motion);



    // Adiciona luz ambiente para melhorar a iluminação geral

    GLfloat ambientLight[] = {0.2, 0.2, 0.2, 1.0};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);



    glShadeModel(GL_SMOOTH);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_COLOR_MATERIAL);



    glutMainLoop();



    return 0;

}


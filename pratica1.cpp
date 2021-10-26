#include <GL/glut.h>       
#define IMAGE_ROWS 64      
#define IMAGE_COLS 64

#define DEGREES_PER_PIXEL  0.6f

GLfloat roll = 0, pitch = 0, yaw = 0;

typedef struct {
    bool leftButton;
    bool rightButton;
    int x;
    int y;
} MouseState;

MouseState mouseState = { false, false, 0, 0 };

char title[] = "Texture - Checkerboard Pattern"; 
int windowWidth = 640;     
int windowHeight = 480;    
int windowPosX = 50;      
int windowPosY = 50;      
bool fullScreenMode = true;

GLubyte imageData[IMAGE_ROWS][IMAGE_COLS][3];

GLfloat xAngle = 0.0f;  
GLfloat yAngle = 0.0f;  

void loadTextureChess() {
    int value;
    for (int row = 0; row < IMAGE_ROWS; row++) {
        for (int col = 0; col < IMAGE_COLS; col++) {
            value = (((row & 0x8) == 0) ^ ((col & 0x8) == 0)) * 255;
            imageData[row][col][0] = (GLubyte)value;
            imageData[row][col][1] = (GLubyte)value;
            imageData[row][col][2] = (GLubyte)value;
        }
    }
}

void loadTextureBrown() {
    for (int row = 0; row < IMAGE_ROWS; row++) {
        for (int col = 0; col < IMAGE_COLS; col++) {
            imageData[row][col][0] = (GLubyte)85;
            imageData[row][col][1] = (GLubyte)64;
            imageData[row][col][2] = (GLubyte)33;
        }
    }
}

void loadLampTexture() {
    for (int row = 0; row < IMAGE_ROWS; row++) {
        for (int col = 0; col < IMAGE_COLS; col++) {
            imageData[row][col][0] = (GLubyte)255;
            imageData[row][col][1] = (GLubyte)253;
            imageData[row][col][2] = (GLubyte)208;
        }
    }
}

void loadLampStickTexture() {
    for (int row = 0; row < IMAGE_ROWS; row++) {
        for (int col = 0; col < IMAGE_COLS; col++) {
            imageData[row][col][0] = (GLubyte)36;
            imageData[row][col][1] = (GLubyte)36;
            imageData[row][col][2] = (GLubyte)36;
        }
    }
}


void loadCarpetTexture() {
    for (int row = 0; row < IMAGE_ROWS; row++) {
        for (int col = 0; col < IMAGE_COLS; col++) {
            imageData[row][col][0] = (GLubyte)100;
            imageData[row][col][1] = (GLubyte)36;
            imageData[row][col][2] = (GLubyte)36;
        }
    }
}


void initGL(GLvoid) {
    glShadeModel(GL_SMOOTH);              
    glClearColor(0.4f, 0.5f, 1.0f, 1.0f);  

    glClearDepth(1.0f);     
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); 

    loadTextureChess();  
    glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB,
        GL_UNSIGNED_BYTE, imageData); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glEnable(GL_TEXTURE_2D); 

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void new_plan( float width=5.0f,float height=1.0f) {
   

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.5f);
    glVertex3d(0.0 * width, 0.0, 0.0* height);

    glTexCoord2f(0.5f, 0.5f);
    glVertex3d(0.0 * width + width, 0.0, -0.0 * height);

    glTexCoord2f(0.5f, 0.0f);
    glVertex3d(0.0 * width + width, 0.0, -0.0 * height + height);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(0.0 * width, 0.0, -0.0 * height + height);
    glEnd();
}

void tableTop() {

    glRotatef(90, 1, 0, 0);
    //base
    glTranslatef(-0.5f,0.0f,-3.5);    
    new_plan(4.5,4.5);
    //topo
    glTranslatef(0.0f,-0.2f,0.0);    
    new_plan(4.5,4.5);
    
    //lados
    glRotatef(90, 0, 0, 1);
    new_plan(0.2,4.5);

    glRotatef(90, 1, 0, 0);
    new_plan(0.2,4.5);

    glTranslatef(0.0f,4.5f,4.5f);    
    glRotatef(90, 1, 0, 0);  
    new_plan(0.2,4.5);


    glRotatef(90, 1, 0, 0);  
    new_plan(0.2,4.5);


    


}

void tableLeg() {
    new_plan(0.5f,3.0f);
    glTranslatef(0.0f,0.5f,0.0);    
    new_plan(0.5f,3.0f);

    glRotatef(270, 0, 0, 1);
    new_plan(0.5f,3.0f);

    glTranslatef(0.0f,0.5f,0.0);    
    new_plan(0.5f,3.0f);
}

void tableLegs(){
    //(+X-) (+longe y -perto) (+ baixo z - alto)
    glTranslatef(1.25f,1.25f,0.25f);
    tableLeg();

    glTranslatef(0.0f,2.5f,0.0f);
    tableLeg();
    
    glTranslatef(0.0f,2.5f,0.0f);
    tableLeg();

    glTranslatef(0.0f,2.5f,0.0f);
    tableLeg();
}

void lampTop() {
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricTexture(quadObj, GL_TRUE);

    glTranslatef(0, 0, 0);
    glRotatef(0, 0, 0, 1);
    gluDisk(gluNewQuadric(), 0, 1, 100,1);
    gluDeleteQuadric(quadObj);
}

void lampBase() {
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricTexture(quadObj, GL_TRUE);

    glTranslatef(0, 0, 5);
    glRotatef(0, 0, 0, 1);
    gluDisk(gluNewQuadric(), 0, 1, 1000,1000);
    glTranslatef(0.0f, 0.0f, 0.2f);
    gluDisk(gluNewQuadric(), 0, 1, 1000,1000);

    glTranslatef(0.0f, 0.0f, -0.2f);
    glRotatef(90, 0, 0, 1);
    gluCylinder(quadObj, 1.0f,1.0f,0.2f,100,100);

    gluDeleteQuadric(quadObj);
}

void lampStick() {
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricTexture(quadObj, GL_TRUE);

    glTranslatef(0, 0, 0);
    glRotatef(90, 0, 0, 1);
    gluCylinder(quadObj, 0.2f,0.2f,5.0f,500,500);
    gluDeleteQuadric(quadObj);
}

void lampHead() {
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricTexture(quadObj, GL_TRUE);
    
    glTranslatef(0, 3, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(quadObj, 1.0f,2.0f,2.0f,500,500);
    gluDeleteQuadric(quadObj);
}

void carpet(int multiplierW, int multiplierH) {

    glRotatef(90, 0, 0, 1);
    //base
    glTranslatef(-0.5f,0.0f,-3.5);    
    new_plan(multiplierW * 4.5, multiplierH * 4.5);
    //topo
    glTranslatef(0.0f,-0.2f,0.0);    
    new_plan(multiplierW*4.5,multiplierH*4.5);
    
    //lados
    glRotatef(90, 0, 0, 1);
    new_plan(0.2,multiplierH*4.5);

    glRotatef(90, 1, 0, 0);
    new_plan(0.2,multiplierW*4.5);

    glTranslatef(0.0f,multiplierH*4.5f,multiplierH*4.5f+9.0);    
    glRotatef(90, 1, 0, 0);  
    new_plan(0.2,multiplierH*4.5);


    glRotatef(90, 1, 0, 0);  
    new_plan(0.2,multiplierW*4.5);
}

void sofa() {
    new_plan(2.0f,5.0f);
    glTranslatef(0.0f,5.0f,0.0);    
    new_plan(2.0f,5.0f);

    glRotatef(270, 0, 0, 1);
    new_plan(5.0f,2.0f);
    new_plan(5.0f,5.0f);
    //topo
    glTranslatef(0.0f,2.0f,0.0);    
    new_plan(5.0f,5.0f);

    glTranslatef(0.0f,-2.0f,0.0);    
    glRotatef(270, 1, 0, 0);
    new_plan(5.0f,5.0f);

    glTranslatef(0.0f,-1.0f,0.0);    
    new_plan(5.0f,5.0f);

    glRotatef(270, 1, 0, 0);
    glTranslatef(0.0f,-5.0f,0.0);    
    new_plan(5.0f,1.0f);

    glRotatef(90, 0, 0, 1);
    new_plan(5.0f,1.0f);

    glTranslatef(0.0f,-5.0f,0.0);    
    new_plan(5.0f,1.0f);

    glTranslatef(3.0f,0.0f,-4.0);    
    glRotatef(90, 0, 1, 0);
    glRotatef(90, 0, 0, 1);
    new_plan(5.0f,2.0f);
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    //rotate
    glLoadIdentity();  
    //posição da camera
    glTranslatef(0.0f, 0.0f, -35.0f);
    glRotatef(375, 0.0f, 1.0f, 0.0f);
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);

    glRotatef(roll, 1, 0, 0);  
    glRotatef(pitch, 0, 1, 0); 
    glRotatef(yaw, 0, 0, 1);  

    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0); 

    GLfloat ambient_color[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_color);

    // spot
    // GLfloat directional_pos[] = { 1.0, 1.0, 1.0, 0.0 };     
    // glLightfv(GL_LIGHT0, GL_POSITION, directional_pos);

    GLfloat point_pos[] = { -1.0, 0.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, point_pos); // posição

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 360); // corte do spot

    GLfloat spot_position[] = { 0.0,6.0, 0.0};     //
    glLightfv(GL_LIGHT0, GL_POSITION, spot_position);

    GLfloat light_ambient[] = { 0.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    GLfloat light_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


    GLfloat mat_diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    
    // objetos
    loadLampTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    lampHead(); //1
    
    
    loadLampStickTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    lampStick(); //2
    lampTop(); //3
    lampBase() ; //4

    loadTextureBrown();  
    glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glTranslatef(-3.0f,0.0f,0.0f);   
    tableLegs(); //5
    tableTop(); //6

    loadCarpetTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glTranslatef(3.2f,-10.0f,-3.5f);   
    carpet(6,4); //7


    loadLampStickTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    sofa(); //8


    
    glutSwapBuffers(); 

}

void reshape(GLsizei width, GLsizei height) {  
    if (height == 0) height = 1; 
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();             
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();            
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
            mouseState.leftButton = true;
        else
            mouseState.leftButton = false;
    }
    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
            mouseState.rightButton = true;
        else
            mouseState.rightButton = false;
    }

    mouseState.x = x;
    mouseState.y = y;
}

void mouseMove(int x, int y)
{
    int xDelta = mouseState.x - x;
    int yDelta = mouseState.y - y;

    mouseState.x = x;
    mouseState.y = y;

    if (mouseState.leftButton) {
        xAngle -= yDelta * DEGREES_PER_PIXEL;
        yAngle -= xDelta * DEGREES_PER_PIXEL;
    }
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key) {

    case GLUT_KEY_LEFT:  pitch -= 5;  break;
    case GLUT_KEY_RIGHT:  pitch += 5;  break;
    case GLUT_KEY_UP:  roll -= 5;  break;
    case GLUT_KEY_DOWN:  roll += 5;  break;
    case 'q': roll += 5;  break;
    case 'w': roll -= 5;  break;
    }

    glutPostRedisplay();
}

void special_keys(int key, int x, int y)
{
    switch (key) {

    case GLUT_KEY_LEFT:  pitch -= 5;  break;
    case GLUT_KEY_RIGHT:  pitch += 5;  break;
    case GLUT_KEY_UP:  roll -= 5;  break;
    case GLUT_KEY_DOWN:  roll += 5;  break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowPosX, windowPosY); 
    glutCreateWindow(title); 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keys); 
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
    initGL();          
    glutMainLoop();    
    return 0;
}
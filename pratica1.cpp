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

void draw_sphere()
{
    
    GLUquadric* quadObj = gluNewQuadric();

    gluQuadricTexture(quadObj, GL_TRUE);
    gluSphere(quadObj, 1, 100, 100);
    gluDeleteQuadric(quadObj);

}

void draw_plane(
    int rotationAngle=0, 

    int xDimension=0, 
    int yDimension=0, 
    int zDimension=0,

    int width=4,
    int height=4,

    double sideLenMultiplier=1.0,

    float zOffset=0.0f,
    float xOffset=0.0f, 
    float yOffset=0.0f 
    )
{
    int i, j;

    glPushMatrix();
    glRotatef(rotationAngle, xDimension, yDimension, zDimension);
    glTranslatef(sideLenMultiplier+xOffset,zOffset,sideLenMultiplier + yOffset);
    for (j = 0; j < height; ++j) {
        for (i = 0; i < width; ++i) {
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.5f);
            glVertex3d(i * sideLenMultiplier, 0.0, -j * sideLenMultiplier);

            glTexCoord2f(0.5f, 0.5f);
            glVertex3d(i * sideLenMultiplier + sideLenMultiplier, 0.0, -j * sideLenMultiplier);

            glTexCoord2f(0.5f, 0.0f);
            glVertex3d(i * sideLenMultiplier + sideLenMultiplier, 0.0, -j * sideLenMultiplier + sideLenMultiplier);
            
            glTexCoord2f(0.0f, 0.0f);
            glVertex3d(i * sideLenMultiplier, 0.0, -j * sideLenMultiplier + sideLenMultiplier);
            glEnd();
        }
    }
    glPopMatrix();
}

void plan(float xpos, float ypos, float zpos, float width, float height){
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(xpos, xpos, zpos);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(xpos, xpos+width, zpos);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(ypos, ypos, zpos);
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(ypos, ypos+height, zpos);
    glEnd();
}

void tableTop() {
    

    glTranslatef(-3.0f,0.0f,0.0f);

    //superfícies
    draw_plane(90, 1,0,0, 4,4, 1.0f, 0.2f,0.0f,0.0f);
    draw_plane(90, 1,0,0, 4,4, 1.0f, 0.4f,0.0f,0.0f);

    //lados
    draw_plane(90, 0,0,0, 20,1, 0.2f, 1.8f+0.2f,0.75f,0.0f);
    draw_plane(90, 0,0,0, 20,1, 0.2f, -2.2f+0.2f,0.75f,0.0f);

    draw_plane(90, 0,0,1, 20,1, 0.2f, -1.0f,-2.2f,0.0f);
    draw_plane(90, 0,0,1, 20,1, 0.2f, -5.0f,-2.2f,0.0f); 
}


void tableLeg() {
    //superfícies
    draw_plane(90, 1,0,0, 1,1, 0.5f, 0.2f,0.0f,0.0f);
    draw_plane(90, 1,0,0, 1,1, 0.5f, 3.7f,0.0f,0.0f);

    //lados
    draw_plane(90, 0,0,0, 5,35, 0.1f, -0.5f,0.4f,3.5f);
    draw_plane(90, 0,0,0, 5,35, 0.1f, -1.0f,0.4f,3.5f);

    draw_plane(90, 0,0,1, 5,35, 0.1f, -0.5f,-1.1f,3.5f);
    draw_plane(90, 0,0,1, 5,35, 0.1f, -1.0f,-1.1f,3.5f);

}

void tableLegs(){
    
    glTranslatef(0.75f,-0.75f,0.0f);
    tableLeg();

    glTranslatef(0.0f,3.0f,0.0f);
    tableLeg();

    glTranslatef(3.0f,0.0f,0.0f);
    tableLeg();
    glTranslatef(0.0f,-3.0f,0.0f);
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
    gluDisk(gluNewQuadric(), 0, 1, 100,1);
    glTranslatef(0.0f, 0.0f, 0.2f);
    gluDisk(gluNewQuadric(), 0, 1, 100,1);

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
    gluCylinder(quadObj, 0.2f,0.2f,5.0f,100,100);
    gluDeleteQuadric(quadObj);
}

void lampHead() {
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricTexture(quadObj, GL_TRUE);
    
    glTranslatef(0, 3, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(quadObj, 1.0f,2.0f,2.0f,100,100);
    gluDeleteQuadric(quadObj);
}

void draw_pyramid(){
  glBegin(GL_TRIANGLES);
      glColor3f(1.0f, 0.0f, 0.0f); 
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);  
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);   
      glVertex3f(1.0f, -1.0f, 1.0f);
 
      glColor3f(1.0f, 0.0f, 0.0f);  
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);    
      glVertex3f(1.0f, -1.0f, -1.0f);
 
      glColor3f(1.0f, 0.0f, 0.0f);  
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);  
      glVertex3f(1.0f, -1.0f, -1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);   
      glVertex3f(-1.0f, -1.0f, -1.0f);
 
      glColor3f(1.0f,0.0f,0.0f);      
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f,0.0f,1.0f);       
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glColor3f(0.0f,1.0f,0.0f);   
      glVertex3f(-1.0f,-1.0f, 1.0f);
   glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    //rotate
    glLoadIdentity();  
    //posição da camera
    glTranslatef(0.0f, 0.0f, -15.0f);
    glRotatef(30, 0.0f, 1.0f, 0.0f);
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);

    glRotatef(roll, 1, 0, 0);  
    glRotatef(pitch, 0, 1, 0); 
    glRotatef(yaw, 0, 0, 1);  

    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0); 
    GLfloat ambient_color[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_color);

    GLfloat directional_pos[] = { 1.0, 1.0, 1.0, 0.0 }; 
    
    glLightfv(GL_LIGHT0, GL_POSITION, directional_pos);

    GLfloat point_pos[] = { 10.0, 10.0, 10.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, point_pos);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45);
    GLfloat spot_position[] = { 5.0, 20.0, 40.0, 1.0 }; 
    glLightfv(GL_LIGHT0, GL_POSITION, spot_position);

  

    GLfloat light_ambient[] = { 0.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    GLfloat light_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


    GLfloat mat_diffuse[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    
    // objetos
    loadLampTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    lampHead();
    
    
    loadLampStickTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    lampStick();
    lampTop();
    lampBase() ;

    loadTextureBrown();  
    glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    tableTop();
    tableLegs();
    

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
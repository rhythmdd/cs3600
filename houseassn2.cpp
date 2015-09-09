#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//#include<SDL/SDL.h>
#define checkImageHeight 30
#define checkImageWidth 30
using namespace std;

static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}
GLuint texName;
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0); 
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
}

void handleResize(int w, int h) {
	glViewport(0, 0,(GLsizei) w,(GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = -70.0f;
unsigned int tex;

void loadtex(void){
	int i,j,c;
	for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
	
}
/*void loadTexture(void){
	//SDL_Surface* img=SDL_LoadBMP(filename);
	unsigned int id;
	glGenTextures(1,&id);
	glBindTexture(GL_TEXTURE_2D,id);
	//glTexImage(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,img->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAX_FILTER,GL_LINEAR);
	//SDL_FreeSurface(img);
	//return id;
}*/
void init(void)
{    
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);
    

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    GLfloat lightpos[] = { 0.0, 15.0, 15.0 };
    GLfloat lightcolor[] = { 0.5, 0.5, 0.5 };
    GLfloat ambcolor[] = { 0.2, 0.2, 0.0 };
    
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambcolor);
    
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,lightcolor);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightcolor);
    glLightfv(GL_LIGHT0,GL_SPECULAR,lightcolor);


   loadtex();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, 
                checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                checkImage);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -8.0f);
	
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f};

	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
	glRotatef(_angle, 0.0f, 1.0f, 0.0f);
	
	
	
	
	
	
	
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texName);
	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0,0.0);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.5f, -1.0f, 1.5f);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1.5f, 1.0f, 1.5f);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-1.5f, 1.0f, 1.5f);
	
	glDisable(GL_TEXTURE_2D);
	//top right
	//glNormal3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(1.5f, 1.0f, 1.5f);
	//glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.5f, 1.0f, -1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.5f, -1.5f);
	//glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.5f, 1.5f);
	
	//top left
	glVertex3f(-1.5f, 1.0f, 1.5f);
	glVertex3f(-1.5f, 1.0f, -1.5f);
	glVertex3f(0.0f, 1.5f, -1.5f);
	glVertex3f(0.0f, 1.5f, 1.5f);
	
	glColor3f(.0f, .0f, 1.0f);
	
	//door offset
	glVertex3f(1.55f, 0.5f, 0.5f);
	glVertex3f(1.5f, 0.5f, 0.5f);
	glVertex3f(1.5f, -1.0f, 0.5f);
	glVertex3f(1.55f, -1.0f, 0.5f);
	
	//door offset
	glVertex3f(1.55f, 0.5f, -0.5f);
	glVertex3f(1.5f, 0.5f, -0.5f);
	glVertex3f(1.5f, -1.0f, -0.5f);
	glVertex3f(1.55f, -1.0f, -0.5f);
	
	//door offset
	glVertex3f(1.55f, 0.5f, 0.5f);
	glVertex3f(1.5f, 0.5f, 0.5f);
	glVertex3f(1.5f, 0.5f, -0.5f);
	glVertex3f(1.55f, 0.5f, -0.5f);
	
	//door
	glColor3f(0.0f, 1.0f, 0.0f);
	
	
	glVertex3f(1.55f, -1.0f, -.5f);
	glVertex3f(1.55f, 0.5f, -.5f);
	glVertex3f(1.55f, .5f, .5f);
	glVertex3f(1.55f, -1.0f, .5f);
	
	glEnd();
	
	
	//front covering
	glColor3f(0.5f,0.7,0.9);
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.5,1.0,1.5);
	glVertex3f(0.0,1.5,1.5);
	glVertex3f(1.5,1.0,1.5);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.5,1.0,-1.5);
	glVertex3f(0.0,1.5,-1.5);
	glVertex3f(1.5,1.0,-1.5);
	
	glEnd();
	
	
	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texName);
	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0,0.0);
	glVertex3f(1.5f, -1.0f, -1.5f);
	glTexCoord2f(0.0,1.0);
	glVertex3f(1.5f, 1.0f, -1.5f);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1.5f, 1.0f, 1.5f);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.5f, -1.0f, 1.5f);
	
	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	glVertex3f(-1.5f, 1.0f, -1.5f);
	glVertex3f(1.5f, 1.0f, -1.5f);
	glVertex3f(1.5f, -1.0f, -1.5f);
	
	//Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.5f, -1.0f, -1.5f);
	glVertex3f(-1.5f, -1.0f, 1.5f);
	glVertex3f(-1.5f, 1.0f, 1.5f);
	glVertex3f(-1.5f, 1.0f, -1.5f);
	glDisable(GL_TEXTURE_2D);
	glEnd();
	
	glutSwapBuffers();
}

void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}
	
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	//Create the window
	glutCreateWindow("Lighting - videotutorialsrock.com");
	initRendering();
	//init();
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(25, update, 0); //Add a timer
	
	glutMainLoop();
	return 0;
}


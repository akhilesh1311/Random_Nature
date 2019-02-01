#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/freeglut.h>
#include<GL/glu.h>
#include<stdlib.h>
#include<math.h>

void init();
void display();
void reshape();
void mousePassive(int,int);
void christmasTree();
void special(int key, int x, int y);
void house();
void snowman();
void flowerleaf();
void tree();
void terrain();
void processSpecialKeys(int key, int xx, int yy);
void snowfall();
void sunrise();
void rocket();

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
   glutInitWindowSize(1280,800);
   glutInitWindowPosition(10,10);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("OpenGL Test Final");
    init();
    glutSpecialFunc(processSpecialKeys);
    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mousePassive);
    glutMainLoop();
    return 1;
}

void init(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(1,1,1,0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum (-0.5, 0.5, -0.35, 0.35, 1.5, 20.0);
//    gluPerspective(120.0, 2.0, 1.5, 20.0);

    printf("%d",GL_INVALID_VALUE);
   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   
    glutSwapBuffers();
}

void reshape (int w, int h)
{
glViewport (0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
glFrustum (-0.5, 0.5, -0.35, 0.35, 1.5, 20.0);
glMatrixMode (GL_MODELVIEW);
}

    GLfloat sun_direction[] = { 0.0, 2.0, -1.0, 1.0 };
    GLfloat sun_intensity[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat ambient_intensity[] = { 0.3, 0.3, 0.3, 1.0 };

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

void display(){
//while(1){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   
   
   
    glEnable(GL_DEPTH_TEST);            // Draw only closest surfaces
   
    glEnable(GL_LIGHTING);              // Set up ambient light.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);
   
    glEnable(GL_LIGHT0);                // Set up sunlight.
    glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);
   
    glEnable(GL_COLOR_MATERIAL);        // Configure glColor().
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    //glEnable(GL_DEPTH_TEST);

    //glRotatef(5,0,1,0);
    //terrain();
    /*gluLookAt(
    0,6,0,     //eyes
    0,0,-5,      //look at
    0,1,0       //up direction
    );*/
    glLoadIdentity();
   
   gluLookAt(    x, 0.1f, z,
            x+lx, 0.1f,  z+lz,
            0.0f, 1.0f,  0.0f);

   
 

	glPushMatrix();
    glTranslatef(0,0,-5);
    terrain();
	 glPopMatrix();

	glPushMatrix();
        glTranslatef(-2,0,0);
			glRotatef(60,0,1,0);
        house();
    glPopMatrix();

	glPushMatrix();
        glTranslatef(-1,0,0.5);
			glRotatef(40,0,1,0);
        house();
    glPopMatrix();

	glPushMatrix();
        glTranslatef(2,0,-3);
			glRotatef(6,0,1,0);
        house();
    glPopMatrix();

	glPushMatrix();
        glTranslatef(2,0,-1);
			glRotatef(0,0,1,0);
        tree();
    glPopMatrix();

	glPushMatrix();
        glTranslatef(-0.5,0,-1.5);
			glRotatef(0,0,1,0);
        christmasTree();
    glPopMatrix();



	glPushMatrix();
		sunrise();
	glPopMatrix();

	glPushMatrix();
		rocket();
	glPopMatrix();
   
   
    glutSwapBuffers();
//	}
}

float sun=0;
float r=0,b=0,g=0;

float up=0;
float fire=0;

void sunrise(){
	glPushMatrix();
		glColor3f(1,1,0);
		glRotatef(sun,1,0,0);
		glTranslatef(0,0,-12);
		glutSolidSphere(0.4,100,100);
		sun=sun+0.8;
		
		if(((int)(sun)%360)>200 && ((int)(sun)%360)<330){
			glClearColor(0,0,0,1);
		printf("bebo");
		glRotatef(-sun,1,0,0);
		glTranslatef(0,0,12);
			glPushMatrix();
	//	glLoadIdentity();
		rocket();
		glPopMatrix();
	}
		else if(((int)(sun)%360)<160 && ((int)(sun)%360)>20){
		glClearColor(1,1,1,1);
		up=0;
		fire=0;
	}
		else if(((int)(sun)%360)>330 | ((int)(sun)%360)<20){	
		r=r+0.05;
		g=g+0.05;
		b=b+0.05;
	//	glClearColor(((r*100)%1)/100,((g*100)%1)/100,((b*100)%1)/100,1);
		glClearColor(r,b,g,1);
	}
	else{
		r=r-0.05;
		g=g-0.05;
		b=b-0.05;
		glClearColor(r,b,g,1);
	}
	glPopMatrix();
}



void rocket(){
	if(((int)(sun)%360)>200 && ((int)(sun)%360)<330 && up<2){
	glPushMatrix();
		glTranslatef(0,up,0);
		glPushMatrix();
			glColor3f(0,0,1);
			//glRotatef(sun,1,0,0);
			//glTranslatef(0,2,4);
			glRotatef(90,1,0,0);
			glutSolidCylinder(0.02,0.5,20,20);
			glColor3f(1,1,0);
			glRotatef(180,1,0,0);
			glutSolidCone(0.05,0.1,5,5);
		glPopMatrix();
		up=up+0.05;
	glPopMatrix();
	
}

/*if(up>=2){
		glPushMatrix();
		for(int i=0;i<10;i++){
			
			glColor3f(0,1,1);
			glRotatef(10,0,0,1);
			for(int j=0;j<10;j++)
			glTranslatef(fire,1,0);
			glutSolidSphere(0.1,20,20);
			
			fire=fire+0.1;
			}
		glPopMatrix();
		}*/
}


void snowfall(){

float snowy=0;
float snowx=0;
while(1){
			for(int i=1;i<10;i++){
			for(int j=0;j<10;j++){
	glPushMatrix();			
		glLoadIdentity();												//
		glTranslatef(i*3-snowx,j*3-snowy,-8.5);
		glColor3f(0.99,0.99,0.99);
		glutSolidSphere(0.2,20,20);
		
		glLoadIdentity();
		glTranslatef(-i*3-snowx,j*3-snowy,-8.5);
		glColor3f(0.99,0.99,0.99);
		glutSolidSphere(0.2,20,20);

		glLoadIdentity();
		glTranslatef(4.5-i*3-snowx,-1.5+j*3-snowy,-9.5);
		glColor3f(0.99,0.99,0.99);
		glutSolidSphere(0.2,20,20);


		glLoadIdentity();
		glTranslatef(1.5+i*3-snowx,-1.5+j*3-snowy,-9.5);
		glColor3f(0.99,0.99,0.99);
		glutSolidSphere(0.2,20,20);

		glLoadIdentity();
		glTranslatef(0.5-i*3-snowx,-0.5-j*3-snowy,-7.5);
		glColor3f(0.99,0.99,0.99);
		glutSolidSphere(0.2,20,20);

		glLoadIdentity();
		glTranslatef(0.5+i*3-snowx,-0.5-j*3-snowy,-7.5);
		glColor3f(0.99,0.99,0.99);
		glutSolidSphere(0.2,20,20);

		glLoadIdentity();
		glTranslatef(4.5-i*3-snowx,-2.5-j*3-snowy,-7.5);
		glColor3f(0.99,0.99,0.99);
		glutSolidSphere(0.2,20,20);
	glPopMatrix();
			}
		}

snowy=snowy+0.1;
snowx=snowx+0.03;

if(snowy>10){
	snowy=0;	
}
if(snowx>10){
	snowx=0;
}
	glutSpecialFunc(processSpecialKeys);
		   glutSwapBuffers();
	}
}

void terrain(){
    glPushMatrix();
        glColor3f(0.1,0,0.0);

        glTranslatef(0,-0.26,-0);
        glScalef(3,0.01,12);
        glutSolidCube(2);
    glPopMatrix();

	glPushMatrix();																//curving road
		glColor3f(0.6,0.6,0.6);
        glTranslatef(-1.3,-0.24,-1);
			
        glRotatef(90,1,0,0);
			glRotatef(70,0,0,1);
			glScalef(4,1.3,1.8);
        GLUquadric *quadric = gluNewQuadric();
        gluQuadricNormals(quadric, GLU_SMOOTH);       
        gluPartialDisk(quadric,0.5,1,100,100,270,180);
		glPushMatrix();		     
			glTranslatef(1.5,0,0);
			gluPartialDisk(quadric,0.5,1,100,100,90,180);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,1,0);
		glPushMatrix();
			glTranslatef(0,-2.9,-4);																//mountains
			glScalef(1.8,4,0.8);
			glutSolidSphere(1,100,100);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.5,-3.4,-5);																//mountains
			glScalef(3.2,4,0.8);
			glutSolidSphere(1,100,100);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.5,-2.5,-6);																//mountains
			glScalef(1.8,4,0.8);
			glutSolidSphere(1,100,100);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1,-2.6,-4.6);																//mountains
			glScalef(1.8,4.5,0.9);
			glutSolidSphere(1,100,100);
		glPopMatrix();
	glPopMatrix();
   
}


void christmasTree(){
    glPushMatrix();

       
        glTranslatef(0,0,-5);
        glRotatef(90,1,0,0);
        glColor3f(0.27,0.164,0.054);
        glutSolidCylinder(0.08,0.3,100,100);
        glPushMatrix();
            glRotatef(180,1,0,0);
            glColor3f(0.145,0.541,0.074);
            glutSolidCone(0.25,0.3,100,100);

            glTranslatef(0,0,0.25);           
           glColor3f(0.145,0.541,0.074);
            glutSolidCone(0.25,0.3,100,100);

            glTranslatef(0,0,0.25);           
             glColor3f(0.145,0.541,0.074);
            glutSolidCone(0.25,0.3,100,100);
        glPopMatrix();
    glPopMatrix();
}

void house(){
    glPushMatrix();
    //    glTranslatef(0,0,-5);
        glColor3f(0,0,1);
        glutSolidCube(0.5);
        glPushMatrix();
            glColor3f(1,0,0);
            glTranslatef(0,0.25,0);
            glRotatef(-90,1,0,0);
            //glRotatef(-90,1,0,0);
            glRotatef(45,0,0,1);
            glutSolidCone(0.4,0.3,4,4);
        glPopMatrix();
		glPushMatrix();
			glColor3f(1,1,0);
			glTranslatef(-0.25,-0.1,0);
			glScalef(0.02,0.3,0.09);
			glutSolidCube(1);
		glPopMatrix();
    glPopMatrix();
//    glLoadIdentity();
}


void snowman(){
   // glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        glTranslatef(0,0,-5);
		  glScalef(0.5,0.5,0.5);                        //main body-stomach legs and all
        glColor3f(0.99,0.99,0.99);
        glutSolidSphere(0.25,20,20);
    //glPopMatrix();


    //    glLoadIdentity();                                                //head
        glTranslatef(0,0.35,0);
        glColor3f(0.99,0.99,0.99);
        glutSolidSphere(0.15,20,20);



        glPushMatrix();                                            //left eye
        glTranslatef(-0.05,0.05,0.2);
        glColor3f(1,0,0);
        glutSolidSphere(0.02,20,20);
        glPopMatrix();


        glPushMatrix();                                            //right eye
        glTranslatef(0.05,0.05,0.2);
        glColor3f(1,0,0);
        glutSolidSphere(0.02,20,20);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0,0,0.2);
        glRotatef(-10,0,1,0);
        glutSolidCone(0.02,0.1,3,4);
        glPopMatrix();
    glPopMatrix();
 //   glutSwapBuffers();
}

void tree(){
    glPushMatrix();
        glTranslatef(0,0,-5);
        glRotatef(90,1,0,0);
        glColor3f(0.27,0.164,0.054);
        glutSolidCylinder(0.08,0.3,100,100);
       
        glTranslatef(0,0,-0.2);                                                    //main body-stomach legs and all
         glColor3f(0.145,0.541,0.074);
        glutSolidSphere(0.25,20,20);

        glTranslatef(0,0,-0.25);
         glColor3f(0.145,0.541,0.074);
        glutSolidSphere(0.15,20,20);


    glPopMatrix();
}
int oldx=0,oldy=0;

void mousePassive(int x, int y){
    float fraction = 0.005f;
    //printf("Saturday");
    //printf("%d",x);
    if(x-oldx>2){
        //glRotatef(-0.1,0,1,0);
        angle += 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            display();
       
    }
    if(x-oldx<-2){
        //glRotatef(0.1,0,1,0);
        angle -= 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            display();
       
    }
    if(y-oldy>2){
        //glRotatef(0.1,1,0,0);
        x -= lx * fraction;
            z -= lz * fraction;
            display();
       
    }
    if(y-oldy<-2){
        //glRotatef(-0.1,1,0,0);
        x += lx * fraction;
            z += lz * fraction;
            display();
       
    }   
    //display();
    oldx=x;
    oldy=y;
}




void processSpecialKeys(int key, int xx, int yy) {

    float fraction = 0.1f;

    switch (key) {
        case GLUT_KEY_LEFT :
            angle -= 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            display();
            break;
        case GLUT_KEY_RIGHT :
            angle += 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            display();
            break;
        case GLUT_KEY_UP :
            x += lx * fraction;
            z += lz * fraction;
            display();
            break;
        case GLUT_KEY_DOWN :
            x -= lx * fraction;
            z -= lz * fraction;
            display();
            break;
        case 'q':
            printf("ssup");
            break;
    }
   
}

void flowerleaf(){
    glPushMatrix();
        glTranslatef(0,0,-5);
        glRotatef(90,1,0,0);
        glColor3f(0,1,0);
        glutSolidCylinder(0.01,0.4,100,100);
       
        glColor3f(1,0,0);
        glTranslatef(0,0.07,0);
        glutSolidSphere(0.05,100,100);

        glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(0,0,0);
        glRotatef(-90,1,0,0);
        glutSolidCone(0.02,0.2,3,9);
   
        glRotatef(-30,1,1,0);
        glutSolidCone(0.02,0.2,3,9);

        glRotatef(-30,1,1,0);
        glutSolidCone(0.02,0.2,3,9);

        glRotatef(-30,1,1,0);
        glutSolidCone(0.02,0.2,3,9);

        glRotatef(-30,1,1,0);
        glutSolidCone(0.02,0.2,3,9);

        glRotatef(-30,1,1,0);
        glutSolidCone(0.02,0.2,3,9);

        glRotatef(-30,1,1,0);
        glutSolidCone(0.02,0.2,3,9);

        glRotatef(-30,1,1,0);
        glutSolidCone(0.02,0.2,3,9);

        glRotatef(-30,1,1,0);
        glutSolidCone(0.02,0.2,3,9);

        glRotatef(-30,1,1,0);
        glutSolidCone(0.02,0.2,3,9);

        glRotatef(-30,1,1,0);
        glutSolidCone(0.02,0.2,3,9);

        glRotatef(-30,1,1,0);
        glutSolidCone(0.02,0.2,3,9);

        glRotatef(-30,1,1,0);
        glutSolidCone(0.02,0.2,3,9);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0,1,0);
        glTranslatef(0.1,0,0.1);
        glRotatef(60,1,0,0);
        GLUquadric *quadric = gluNewQuadric();
        gluQuadricNormals(quadric, GLU_SMOOTH);       
        gluDisk(quadric,0,0.05,100,100);   
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0,0.2);
        glRotatef(135,0,1,0);
        glutSolidCone(0.02,0.15,3,9);
        glPopMatrix();
   
    glPopMatrix();
}

void scenegraph(){
   
}

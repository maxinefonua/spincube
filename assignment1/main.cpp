# include <cstdlib>
# include <cmath>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <GLUT/glut.h>

using namespace std;

// presets of vertices and colors: allows organization of vertex info

GLfloat vertPos[][3] = {
	{ -1.0, -1.0, -1.0 },
	{  1.0, -1.0, -1.0 },
	{  1.0,  1.0, -1.0 },
	{ -1.0,  1.0, -1.0 },
	{ -1.0, -1.0,  1.0 },
	{  1.0, -1.0,  1.0 },
	{  1.0,  1.0,  1.0 },
	{ -1.0,  1.0,  1.0 } 
};

GLfloat vertCol[][3] = {
	{ 0.0, 0.0, 0.0 },
	{ 1.0, 0.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{ 1.0, 0.0, 1.0 },
	{ 1.0, 1.0, 1.0 },
	{ 0.0, 1.0, 1.0 } 
};

// aboutAxis: allows axis to be adjusted by specific keyboard commands
static GLint aboutAxis = 1;

// speed: allows angle to be adjusted by 'f' and 's' keys to simulate speed.
static GLdouble speed = .75;

// rotateAngle: allows for continuous adjustment of rotation angle for animation
static GLfloat rotateAngle[3] = { 0.0, 0.0, 0.0 };

int win_width = 600;
int win_height = 600;

/* void buildFaces (int v1, int v2, int v3)
 * ------------------------------------------------------------
 * Constructs a partial face of the cube with the given vertices.
 */
void buildFace (int v1, int v2, int v3, int v4) {
	glBegin(GL_TRIANGLE_STRIP);
	glLoadIdentity();
	
	glColor3fv( vertCol[v1] );		
	glVertex3fv( vertPos[v1] );
	
	glColor3fv( vertCol[v2] );		
	glVertex3fv( vertPos[v2] );
	
	glColor3fv( vertCol[v3] );		
	glVertex3fv( vertPos[v3] );
	
	glColor3fv( vertCol[v4] );
	glVertex3fv( vertPos[v4] );
	
	glEnd();
	return;
}

/* void drawEdgeLineT (int start, int end)
 * ------------------------------------------------------------
 * Draws some of the edges using translate.
 */
void drawEdgeLineT(int start, int end) {
	glLineWidth(4.);
	glBegin(GL_LINES);
	glColor3f(1.f,1.f,1.f);
	glLoadIdentity();
	
	glVertex3fv(vertPos[start]);
	glVertex3fv(vertPos[end]);
	glEnd();
	
	glPushMatrix(); //push identity
	glTranslatef(0.f,-2.f,0.f);
	glBegin(GL_LINES);
	glVertex3fv(vertPos[start]);
	glVertex3fv(vertPos[end]);
	glEnd();
	
	glPushMatrix(); //push identity
	glTranslatef(0.f,2.f,2.f);
	glBegin(GL_LINES);
	glVertex3fv(vertPos[start]);
	glVertex3fv(vertPos[end]);
	glEnd();
	
	glPushMatrix(); //push identity
	glTranslatef(0.f,-2.f,0.f);
	glBegin(GL_LINES);
	glVertex3fv(vertPos[start]);
	glVertex3fv(vertPos[end]);
	glEnd();
}

/* void drawEdgeLine (int start, int end)
 * ------------------------------------------------------------
 * Draws the rest of the edges.
 */
void drawEdgeLine(int start, int end) {
	glLineWidth(4.);
	glBegin(GL_LINES);
	glColor3f(1.f,1.f,1.f);
	glLoadIdentity();
	
	glVertex3fv(vertPos[1]);
	glVertex3fv(vertPos[2]);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3fv(vertPos[0]);
	glVertex3fv(vertPos[3]);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3fv(vertPos[5]);
	glVertex3fv(vertPos[6]);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3fv(vertPos[4]);
	glVertex3fv(vertPos[7]);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3fv(vertPos[3]);
	glVertex3fv(vertPos[7]);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3fv(vertPos[2]);
	glVertex3fv(vertPos[6]);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3fv(vertPos[1]);
	glVertex3fv(vertPos[5]);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3fv(vertPos[0]);
	glVertex3fv(vertPos[4]);
	glEnd();
}


/* void display ( )
 * ------------------------------------------------------------
 * This clears the window, adjusts the angle of rotation,
 * and displays the constructed cube.
 */
void display ( ) {
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity ( );
	
	glRotatef ( rotateAngle[0], 1.0, 0.0, 0.0 );
	glRotatef ( rotateAngle[1], 0.0, 1.0, 0.0 );
	glRotatef ( rotateAngle[2], 0.0, 0.0, 1.0 );
	
	buildFace(3,2,0,1);
	buildFace(3,7,2,6);
	buildFace(4,7,0,3);
	buildFace(2,6,1,5);
	buildFace(5,6,4,7);
	buildFace(1,5,0,4);
	drawEdgeLine(1,2);
	drawEdgeLineT(3,2);
	
	glFlush ( );
	glutSwapBuffers ( );
	
	return;
}

/* void keyboard ( unsigned char key, int x, int y )
 * ------------------------------------------------------------
 * KEYBOARD allows user to change axis of rotation by pressing
 * keys 1, 2, or 3. Also allows user to adjust angle of rotation
 * to simulate speed, and allows them to exit program by pushing
 * escape button.
 */
void keyboard( unsigned char key, int x, int y ) {
	switch(key) {
		case '1':
			aboutAxis = 0;
			break;
		case '2':
			aboutAxis = 1;
			break;
		case '3':
			aboutAxis = 2;
			break;
		case 'f':
			if (speed < 3)
			speed += .25;
			break;
		case 's':
			if (speed > .25)
			speed -= .25;
			break;
		case 'n':
			speed = .5;
			break;
		case 32:	// spacebar
			if (speed == 0) speed = .5;
			else speed = 0;
			break;
		case 27:	// escape key
			exit(0);
			break;
	}
	return;
}

/* void reshpae ( int w, int h )
 * ------------------------------------------------------------
 * This maps the image to the window.
 */
void reshape ( int w, int h ) {
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ( );
	
	if ( w <= h ) {
		glOrtho ( -2.0, 2.0, -2.0 * ( GLfloat ) h / ( GLfloat ) w,
				 2.0 * ( GLfloat ) h / ( GLfloat ) w, -10.0, 10.0 );
	} else if (w >= h ) {
		glOrtho ( -2.0 * ( GLfloat ) w / ( GLfloat ) h, 2.0 * ( GLfloat ) w / ( GLfloat ) h,
				 -2.0, 2.0, -10.0, 10.0 );
	} else {
		glOrtho( -2., 2., -2., 2., -10., 10. );
	}
	
	glViewport ( 0, 0, w, h );
	glMatrixMode ( GL_MODELVIEW );
	return;
}

/* void spinCube ( )
 * ------------------------------------------------------------
 * SPINCUBE adjusts the angle of rotation and redisplays the
 * picture.
 */
void spinCube ( ) {
	rotateAngle[aboutAxis] = rotateAngle[aboutAxis] + speed;
	if ( 360.0 < rotateAngle[aboutAxis] ) {
		rotateAngle[aboutAxis] = rotateAngle[aboutAxis] - 360.0;
	}
	glutPostRedisplay ( );
	return;
}

/* void main ( int argc, char *argv[] )
 * ------------------------------------------------------------
 * This program draws a cube using triangle strips. Each vertex of
 * the cube is preset to a certain color. The program initially displays
 * the cube rotating about the Y axis. Using the keyboard keys, 1,
 * 2, and 3, the viewer can change about which axis the cube rotates.
 */
int main ( int argc, char *argv[] ) {
	glutInit ( &argc, argv );
	
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL);
	glutInitWindowSize ( win_width, win_height );
	
	glutCreateWindow ( "Maxine Fonua: Cube Rotating about Adjustable Axis" );

	glutDisplayFunc ( display );
	glutReshapeFunc ( reshape );
	glutIdleFunc ( spinCube );
	glutKeyboardFunc( keyboard );
	
	//  Enable hidden surface removal.
	glEnable ( GL_DEPTH_TEST );
	glutMainLoop ( );
}
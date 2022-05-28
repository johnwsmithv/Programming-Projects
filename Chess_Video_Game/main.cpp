#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glut.h>

#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4

// Global vars for demonstration purposes
float angle = 0.0f;
float red = 1, green = 0.5, blue = 0.5;

// Global Camera Position Variables
float cameraDirectionX = 0.0, cameraDirectionZ = -1; // Vectors defining our line of sight
float cameraPosX = 0.0, cameraPosZ = 5.0; 

// Camera-movement variable
float deltaAngle = 0.0;
int xOrigin = -1;

void renderBitmapString(float x, float y, float z, void *font, char * string) {
    glRasterPos3f(x, y, z);
    for(char * c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }

}

/**
 * @brief When the Menu options are clicked, we are going to change the colors based on what the user clicked
 * 
 * @param option The option that the user clicked
 */
void processMenuEvents(int option) {
    switch(option) {
        case RED:
            red   = 1.0;
            green = 0.0;
            blue  = 0.0;
            break;
        case GREEN:
            red   = 0.0;
            green = 1.0;
            blue  = 0.0;
            break;
        case BLUE:
            red   = 0.0;
            green = 0.0;
            blue  = 1.0;
            break;
        case ORANGE:
            red   = 1.0;
            green = 0.5;
            blue  = 0.5;
            break;
    }
}

/**
 * @brief The menu that appears when the user hits the right mouse button
 */
void createGLUTMenus() {
    int menu;

    // We need to create the menu; we need to tell glut that "processMenuEvents" will handle the events
    menu = glutCreateMenu(processMenuEvents);

    // We need to add some entries to the menu
    glutAddMenuEntry("Red", RED);
    glutAddMenuEntry("Blue", BLUE);
    glutAddMenuEntry("Green", GREEN);
    glutAddMenuEntry("Orange", ORANGE);

    // Attach the menu to a button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// For detecting mice input, the functions we can use are the following:
// 1. glutEntryFunc: tells the code when the mouse has entered the window
// 2. glutMotionFunc: these functions are responsible for the respective mouse motion
// 3. glutPassiveMotionFunc: 

/**
 * @brief When the user hits the left mouse button and drags the mouse, the camera moves either left or right
 * 
 * @param button The button that the user presses
 * @param state Whether the callback (Up/Down) was a release or a press respectively
 * @param x The X-coordinate which this took place at
 * @param y The Y-coordinate which this took place at
 */
void mouseButtonClick(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_UP) {
            angle += deltaAngle;
            xOrigin = -1;
        } else { // This is specifically for GLUT_DOWN. We are stopping the 
            xOrigin = x;
        }
    }
}

/**
 * @brief The actual camera direction movement when the left mouse-button is clicked and the user moves the mouse
 * 
 * @param x The X-coordinate which this took place at
 * @param y The Y-coordinate which this took place at
 */
void mouseMove(int x, int y) {
    if(xOrigin >= 0) {
        deltaAngle = (x - xOrigin) * 0.001;

        // Need to also update the camera direction
        cameraDirectionX = sin(angle + deltaAngle);
        cameraDirectionZ = -cos(angle + deltaAngle);
    }
}

/**
 * @brief This tutorial is from: http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/
 */
void drawSnowMan() {
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

    // Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

    // Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); // Black
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

    // Draw Nose
	glColor3f(red, green, blue);
	glutSolidCone(0.08f,0.5f,10,2);
}

/**
 * @brief This scene contains snowmen, a simple black sky and a white (maybe snow) ground
 */
void renderScene(void) {
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera => Look at Point = Line of Sight + Camera Position
	gluLookAt(cameraPosX,                    1.0f, cameraPosX,
			  cameraPosX + cameraDirectionX, 1.0f, cameraPosX + cameraDirectionZ,
			  0.0f,                          1.0f, 0.0f                          );

    // Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

    // Draw 36 SnowMen
	for(int i = -3; i < 3; i++) {
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 10.0, 0, j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}
    }

	glutSwapBuffers();
}

/**
 * @brief This function is going to handle what to do when the user presses certain keys
 * 
 * @param key OpenGL will return the Key that was pressed
 * @param x   OpenGL will return the X coordinate where said key pressed
 * @param y   OpenGL will return the Y coordinate where said key pressed
 */
void processNormalKeys(unsigned char key, int x, int y) {
    // On the ASCII Table, key # 27 is the ESC key
    float fraction = 0.5;
    switch(key) {
        case 27:
            exit(0);
        case 'a':
            angle -= 0.01f;
            cameraDirectionX = sin(angle);
            cameraDirectionZ = -cos(angle);
            break;
        case 'd':
            angle += 0.01f;
            cameraDirectionX = sin(angle);
            cameraDirectionZ = -cos(angle);
            break;
        case 'w':
            cameraPosX += cameraDirectionX * fraction;
            cameraPosZ += cameraDirectionZ * fraction;
            break;
        case 's':
            cameraPosX -= cameraDirectionX * fraction;
            cameraPosZ -= cameraDirectionZ * fraction;
            break;
    }
}

/**
 * @brief The goal of this function is to handle special keys like F1-F12, etc
 * 
 * @param key OpenGL will return the Key that was pressed
 * @param x OpenGL will return the X coordinate where said key pressed
 * @param y OpenGL will return the Y coordinate where said key pressed
 */
void processSpecialKeys(int key, int x, int y) {
    float fraction = 0.1;

    switch(key) {
        case GLUT_KEY_F1:
            red = 1;
            green = 0;
            blue = 0;
            break;
        case GLUT_KEY_F2:
            red = 0;
            green = 1;
            blue = 0;
            break;
        case GLUT_KEY_F3:
            red = 0;
            green = 0;
            blue = 1;
            break;
        case GLUT_KEY_UP:
            cameraPosX += cameraDirectionX * fraction;
            cameraPosZ += cameraDirectionZ * fraction;
            break;
        case GLUT_KEY_DOWN:
            cameraPosX -= cameraDirectionX * fraction;
            cameraPosZ -= cameraDirectionZ * fraction;
            break;
    }
}

/**
 * @brief This function simple does what we tell it to do
 * 
 */
void spinTriangle(void) {
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	0.0f, 0.0f, 10.0f,
			    0.0f, 0.0f,  0.0f,
			    0.0f, 1.0f,  0.0f);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // This function is using the global variables, red, green and blue which are going to be set with the F1, F2 and F3 keys respectively
    glColor3f(red, green, blue);
	glBegin(GL_TRIANGLES);
		glVertex3f(-2.0f,-2.0f, 0.0f);
		glVertex3f( 2.0f, 0.0f, 0.0);
		glVertex3f( 0.0f, 2.0f, 0.0);
	glEnd();

	angle += 0.1;

	glutSwapBuffers();
}

/**
 * @brief Registering a Callback
 * 
 */
void displayMe(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glVertex3f(-2 ,  -2, -5.0);
		glVertex3f(2  , 0.0, -5.0);
		glVertex3f(0.0,   2, -5.0);
	glEnd();

    glutSwapBuffers();
}

/**
 * @brief This function handles the changing of the window size
 * 
 * @param width OpenGL will return the width of the window
 * @param height OpenGL will return the height of the window
 */
void changeSize(int width, int height) {
    // Need to prevent dividing by zero
    if(height == 0) {
        height = 1;
    }

    // Computes the ratio of the window size
    float ratio = (1.0 * width) / height;

    /**
     *  Uses the Projection Matrix. The point of this is to define the viewing volume, we then load the identify matrix to initialize it
     * 
     *                    |1  0  0|
     * Identity Matrix =  |0  1  0|
     *                    |0  0  1|
     */ 
    
    glMatrixMode(GL_PROJECTION);

    // Resets the Matrix
    glLoadIdentity();

    // Set the view port to be the entire window
    glViewport(0, 0, width, height);

    // Sets the correct perspective
    gluPerspective(30, ratio, 1, 100);

    // Go back to the Model View Matrix
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    // The size of the window
    glutInitWindowSize(1920, 1080);
    
    // The (X, Y) starting position of the window
    glutInitWindowPosition(0, 0);

    // Creating the Window and giving it a title
    glutCreateWindow("Chess");
    
    // The function that is being called and displaying the triangle
    glutDisplayFunc(renderScene);

    // Handles the changing of the window size and the objects within
    glutReshapeFunc(changeSize);

    // Does things
    glutIdleFunc(renderScene);

    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    // Handle mouse movement and mouse clicks
    glutMouseFunc(mouseButtonClick);
    glutMotionFunc(mouseMove);
    
    // When the user right-clicks the mouse button, the menu appears; when it is clicked again, the menu disappears
    createGLUTMenus();

    // OpenGL init
	glEnable(GL_DEPTH_TEST);

    // Enter the GLUT Event Processing
    glutMainLoop();

    return 0;
}
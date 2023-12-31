#include <GL/glut.h> 
#include <math.h>
#include <iostream>
#include "life_simulator.cpp"
using namespace std;

#define WINDOW_HEIGHT 512.0f*2
#define WINDOW_WIDTH 512.0f*2
#define GRID_TO_WIDTH(x) (  )
#define GRID_TO_HEIGHT(y) (  )

#define PAN_SPEED 0.05f
#define ZOOM_LEVEL 1.25f

#define LIFE_SIMULATOR HighLifeSimulator

// How big each cell should be
float point_size = 1.0f;

LifeLikeSimulator* sim;

void draw_grid(int grid[GRID_SIZE][GRID_SIZE]) {
	glPushMatrix();
	glBegin(GL_POINTS);

	for (int i=0; i < GRID_SIZE; i++) 
		for (int j=0; j < GRID_SIZE; j++)
			if(grid[i][j] > 0) glVertex3f((point_size * 1.5f)*(float) i/GRID_SIZE, (point_size * 1.5f)*(float) j/GRID_SIZE, 0);

	glEnd();
	glPopMatrix();
}

void display() {
	glPointSize(point_size);
	glClear( GL_COLOR_BUFFER_BIT);  
	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();
		draw_grid(sim->current_grid);	
		glTranslatef(GRID_SIZE*point_size/2, 0.0f, 0);
	glPopMatrix();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {

	// Allow the user to pan around
	if (key == 'w') glTranslatef(0.0f, -PAN_SPEED, 0.0f);
	if (key == 's') glTranslatef(0.0f, PAN_SPEED, 0.0f);
	if (key == 'd') glTranslatef(-PAN_SPEED, 0.0f, 0.0f);
	if (key == 'a') glTranslatef(PAN_SPEED, 0.0f, 0.0f);

	if (key == '=') {
			//glScalef(ZOOM_LEVEL, ZOOM_LEVEL, ZOOM_LEVEL);
			point_size *= ZOOM_LEVEL;
	}
	if (key == '-') {
		//glScalef(1/ZOOM_LEVEL, 1/ZOOM_LEVEL, 1/ZOOM_LEVEL);
		point_size /= ZOOM_LEVEL;
	}

	if (key == 'r') sim->initialize_grid();

	// Continue runnig the simulation
	if (key == ' ') sim->update_grid();

	display();
}

int main(int argc, char **argv) {
	// Setup the OpenGL context
	glutInit(&argc, argv);  
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  

	// Let the user select between High Life and the original
	// We'll do it down here so we can change the window title to the ruleset
	if (argc <= 1 || *argv[1] == 'o') {
		sim = new LifeSimulator();
		glutCreateWindow("John Conway's Game of Life");  
	} else if (*argv[1] == 'h') {
		sim = new HighLifeSimulator();
		glutCreateWindow("Nathan Thompson's High Life");  
	} else {
		cout << "You didn't enter a valid ruleset character. Valid rule characters are:\n o -> for the original game\n h -> for high life.\n";
		exit(-1);
	}


	glutDisplayFunc(display);  

	// We only need to draw when something happens
	//glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();  
}

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

// How big each cell should be
float point_size = 1.0f;

LifeSimulator* sim;

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
}

int main(int argc, char **argv) {
	sim = new LifeSimulator();

	glutInit(&argc, argv);  
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
	glutCreateWindow("Life!");  
	glutDisplayFunc(display);  
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();  
}

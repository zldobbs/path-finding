// Project work
#include <stdio.h>

typedef struct robot {
	int x; // column number of the position
	int y; // row number of the position 
	int dx; // move in x
	int dy; // move in y
	int s; // speed of robot
} Robot;

typedef struct move {
	int dx; // move in x
	int dy; // move in y
} Moves;

void plan(Robot* a, int x, int y);
void move(Robot* a);
void wall(Robot* a, int size);
int findSet(Robot a);
void check(Robot* a, Robot c, Robot d, Moves* set, int size);


int main() {
	
	/* An array of preferred order of moves to take for each
		possible move is to be defined and utilized throughout the program */
		
	Moves dict[8][3];
	// 8 rows for the 8 possible directions, should only compare at most 3 moves
	
	dict[0][0].dx = 0;
	dict[0][0].dy = -1;
	dict[0][1].dx = 1;
	dict[0][1].dy = -1;
	dict[0][2].dx = -1;
	dict[0][2].dy = -1;
	
	dict[1][0].dx = 1;
	dict[1][0].dy = -1;
	dict[1][1].dx = 1;
	dict[1][1].dy = 0;
	dict[1][2].dx = 0;
	dict[1][2].dy = -1;
	
	dict[2][0].dx = 1;
	dict[2][0].dy = 0;
	dict[2][1].dx = 1;
	dict[2][1].dy = 1;
	dict[2][2].dx = 1;
	dict[2][2].dy = -1;
	
	dict[3][0].dx = 1;
	dict[3][0].dy = 1;
	dict[3][1].dx = 0;
	dict[3][1].dy = 1;
	dict[3][2].dx = 1;
	dict[3][2].dy = 0;
	
	dict[4][0].dx = 0;
	dict[4][0].dy = 1;
	dict[4][1].dx = -1;
	dict[4][1].dy = 1;
	dict[4][2].dx = 1;
	dict[4][2].dy = 1;
	
	dict[5][0].dx = -1;
	dict[5][0].dy = 1;
	dict[5][1].dx = -1;
	dict[5][1].dy = 0;
	dict[5][2].dx = 0;
	dict[5][2].dy = 1;
	
	dict[6][0].dx = -1;
	dict[6][0].dy = 0;
	dict[6][1].dx = -1;
	dict[6][1].dy = -1;
	dict[6][2].dx = -1;
	dict[6][2].dy = 1;
	
	dict[7][0].dx = -1;
	dict[7][0].dy = -1;
	dict[7][1].dx = -1;
	dict[7][1].dy = 0;
	dict[7][2].dx = 0;
	dict[7][2].dy = -1;
	
	// Finish filling dictionary of preferred moves
	
	Robot a; // Your robot
	Robot c, d; // Obstacle robots
	int size = 10; // Length of one edge of square room
	
	// Define starting positions and movement
	a.x = 3;
	a.y = 1;
	a.s = 1;
	
	c.x = 8;
	c.y = 10;
	c.dx = 1;
	c.dy = 0;
	c.s = 1;
	
	d.x = 2;
	d.y = 2;
	d.dx = 1;
	d.dy = -1;
	d.s = 1;
	
	int ex = 9; // Ending x position
	int ey = 10; // Ending y position
	
	int i = 1; // Current time
	int j; // Used for counting
	int z; // Holds index of row from dictionary to use
	
	while (a.x != ex || a.y != ey) {
		// loop until the robot reaches the end position
		plan(&a, ex, ey);
		for (j = 0; j < c.s; j++) {
			wall(&c, size);
			move(&c);
		}
		for (j = 0; j < d.s; j++) {
			wall(&d, size);
			move(&d);
		}
		z = findSet(a);
		check(&a, c, d, dict[z], size);
		move(&a);
		printf("Time - %d\n", i);
		printf("Robot - (%d,%d)\n", a.y, a.x);
		printf("Obstacle 1 - (%d,%d)\n", c.y, c.x);
		printf("Obstacle 2 - (%d,%d)\n", d.y, d.x);
		i++;
	}
	return 0;
}

void plan(Robot* a, int x, int y) {
	// Plans the movement of the robot
	if (a->x > x)
		a->dx = -1;
	else if (a->x < x)
		a->dx = 1;
	else
		a->dx = 0;
	
	if (a->y > y)
		a->dy = -1;
	else if (a->y < y)
		a->dy = 1;
	else 
		a->dy = 0;
}

void move(Robot* a) {
	// Moves the robot using dx, dy
	a->x += a->dx;
	a->y += a->dy;
}

void wall(Robot* a, int size) {
	if (a->x + a->dx > size || a->x + a->dx < 1)
		a->dx = -1 * a->dx;
	if (a->y + a->dy > size || a->y + a->dy < 1)
		a->dy = -1 * a->dy;
}

int findSet(Robot a) {
	switch(a.dx) {
		case -1:
			switch(a.dy) {
				case -1:
					return 7;
					break;
				case 1:
					return 5;
					break;
				case 0:
					return 6;
					break;
			}
			break;
		case 1:
			switch(a.dy) {
				case -1:
					return 1;
					break;
				case 1:
					return 3;
					break;
				case 0:
					return 2;
					break;
			}
			break;
		case 0:
			switch(a.dy) {
				case -1:
					return 0;
					break;
				case 1:
					return 4;
					break;
			}
			break;
		default:
			printf("Something went wrong with the vectors in a!\n");
			break;
	}
	
	// Function should not reach this point
	return -1;
}

void check(Robot* a, Robot c, Robot d, Moves* set, int size) {
	int i; // Counting variable
	int nx; // Position x robot a would be at after taking dx
	int ny; // Position y robot a would be at after taking dy
	for (i=0; i<3; i++) {
		nx = a->x + set[i].dx;
		ny = a->y + set[i].dy;
		if ( (nx != c.x || ny != c.y) && (nx != d.x || ny != d.y) )
			// if true, will avoid collision with obstacles
			if (nx > 0 && nx <= size && ny > 0 && ny <= size) {
				/* if true, robot will not pass through a wall
					this is enough information to satisfy a valid move */
					a->dx = set[i].dx;
					a->dy = set[i].dy;
					return;
			}
	}
	/* If the function reaches this point, none of the preferred moves are 
		available. Set the robot to stay in position and try to move next time */
	a->dx = 0;
	a->dy = 0;
	return;
}

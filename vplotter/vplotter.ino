#include <Stepper.h>
#include <Servo.h>

#define PAS 84

#define MAX_X 600 // Distance entre les deux moteurs
#define MAX_Y 100 // Hauteur max du dessin

#define PEN_ON 1
#define PEN_OFF 0

/*
instructions :
	gr... -> go right of ... points
	gl... -> go left of ... points
	gd... -> go down of ... points
	gu... -> go up of ... points
	po    -> set the pen is write position
	pf    -> set the pen is not write position
*/

typedef struct s_vplot
{
	int		x;
	int		y;
	int		pen;
}	t_vplot;


Servo	servo;	// create servo object to control a servo

Stepper	motor_left(4096, 6, 7, 8, 9);
Stepper	motor_right(4096, 2, 3, 4, 5);

t_vplot	vplot;

int	printState = 0;

// variable to store the servo position
int	pos = 0;

// Move functions
static void	move_x(int dist)
{
	int	nx = vplot.x + dist;

	// Check is the move is legal
	if (0 > nx || nx > MAX_X)
		return ;

	int	y2 = vplot.y * vplot.y;

	int	moveML = 0;
	int	moveMR = 0;

	if (dist > 0)
	{
		for (int i = 0; i < dist; i++)
		{
			// Calculate new x
			nx = vplot.x + 1;

			// Calculate move step for each motors
			moveML = sqrt((nx * nx) + y2)
					- sqrt((vplot.x * vplot.x) + y2);

			moveMR = sqrt(((MAX_X - nx) * (MAX_X - nx)) + y2)
				- sqrt(((MAX_X - vplot.x) * (MAX_X - vplot.x)) + y2);

			// Apply move to each motors
			motor_left.step(PAS * moveML);
			motor_right.step(PAS * moveMR);

			// Update the x coordonate
			vplot.x += 1;
		}
	}
	else if (dist < 0)
	{
		dist *= -1;
		for (int i = 0; i < dist; i++)
		{
			// Calculate new x
			nx = vplot.x - 1;

			// Calculate move step for each motors
			moveML = sqrt((nx * nx) + y2)
					- sqrt((vplot.x * vplot.x) + y2);

			moveMR = sqrt(((MAX_X - nx) * (MAX_X - nx)) + y2)
				- sqrt(((MAX_X - vplot.x) * (MAX_X - vplot.x)) + y2);

			// Apply move to each motors
			motor_left.step(PAS * moveML);
			motor_right.step(PAS * moveMR);

			// Update the x coordonate
			vplot.x -= 1;
		}
	}
}

static void	move_y(int dist)
{
	int	ny = vplot.y + dist;

	// Check is the move is legal
	if (0 > ny || ny > MAX_Y)
		return ;

	int	x2 = vplot.x * vplot.x;

	int	moveML = 0;
	int	moveMR = 0;

	if (dist > 0)
	{
		for (int i = 0; i < dist; i++)
		{
			// Calculate new x
			ny = vplot.y + 1;

			// Calculate move step for each motors
			moveML = sqrt(x2 + (ny * ny))
					- sqrt(x2 + (vplot.y * vplot.y));

			moveMR = sqrt(x2 + ((MAX_Y - ny) * (MAX_Y - ny)))
				- sqrt(x2 + ((MAX_Y - vplot.y) * (MAX_Y - vplot.y)));

			// Apply move to each motors
			motor_left.step(PAS * moveML);
			motor_right.step(PAS * moveMR);

			// Update the y coordonate
			vplot.y += 1;

		}
	}
	else if (dist < 0)
	{
		dist *= -1;
		for (int i = 0; i < dist; i++)
		{
			// Calculate new x
			ny = vplot.y- 1;

			// Calculate move step for each motors
			moveML = sqrt(x2 + (ny * ny))
					- sqrt(x2 + (vplot.y * vplot.y));

			moveMR = sqrt(x2 + ((MAX_Y - ny) * (MAX_Y - ny)))
				- sqrt(x2 + ((MAX_Y - vplot.y) * (MAX_Y - vplot.y)));

			// Apply move to each motors
			motor_left.step(PAS * moveML);
			motor_right.step(PAS * moveMR);

			// Update the x coordonate
			vplot.y -= 1;
		}
	}
}

static void	pen_on()
{
	if (vplot.pen == PEN_ON)
		return ;
	for (pos = 0; pos <= 180; pos += 1)
	{
		// rotate from 0 degrees to 180 degrees
		// in steps of 1 degree
		// tell servo to go to position in variable 'pos'
		servo.write(pos);
		// waits 10ms for the servo to reach the position
		delay(10);
	}
}

static void	pen_off()
{
	if (vplot.pen == PEN_OFF)
		return ;
	for (pos = 180; pos >= 0; pos -= 1)
	{
		// rotate from 180 degrees to 0 degrees
		// tell servo to go to position in variable 'pos'
		servo.write(pos);
		// waits 10ms for the servo to reach the position
		delay(10);
	}
}



// Mains functions
void	setup()
{
  Serial.begin(9600);
  //pinMode(17, INPUT);
	//pinMode(30, INPUT);
	//pinMode(3, INPUT);
//	pinMode(4, INPUT);
	//set motors speed
  motor_left.setSpeed(6);
	motor_right.setSpeed(6);

	// attaches the servo on pin 9 to the servo object
	servo.attach(10);

	// creation of vploter
	vplot.x = MAX_X / 2; // Position initial du vploter en X
	vplot.y = 0; // Position initial du vploter en Y
	vplot.pen = PEN_ON;

  delay(1000);
}

void	loop()
{
  delay(2000);
  Serial.println("oskour1\n");
  move_x(-25);
  //Serial.println("oskour2\n");
  //pen_off();
  //move_x(50);
  //Serial.println("oskour4\n");
  //move_y(50);
  //Serial.println("oskour5\n");
  //move_x(-50);
  //Serial.println("oskour6\n");
  //move_y(-50);
  //Serial.println("oskour7\n");
  //pen_on();
}

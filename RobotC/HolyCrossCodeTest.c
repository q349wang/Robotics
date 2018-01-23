#pragma config(Sensor, in2,    s1,             sensorPotentiometer)
#pragma config(Sensor, dgtl1,  s3,             sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  s4,             sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  s2,             sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  selector,       sensorDigitalIn)
#pragma config(Sensor, dgtl8,  whichSquare,    sensorDigitalIn)
#pragma config(Sensor, dgtl9,  onlyCube,       sensorDigitalIn)
#pragma config(Motor,  port2,           d2,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           l2,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           g1,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           l1,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           l6,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           g2,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           l4,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           d1,            tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/


int driveL = 0;
int driveR = 0;

bool lowPow =  false;

int  clawPos = 0;
bool setPos =  false;

int state = 0;

const int clawStart = 0;
const int clawHalf = clawStart + 1300;
const int clawFull = clawStart + 2820;
const int clawQuarter = clawStart + 400;
bool clawDone =  false;

const int liftBig = 73;
const int liftCube = 85;
const int liftStars = 90;

bool liftDone = false;

int clawVal = SensorValue[s1];
int liftVal = SensorValue[s2];

int leftVal = SensorValue[s3];
int rightVal = -SensorValue[s4];

bool driveDone = false;
bool leftDone = false;
bool rightDone = false;

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void claw(int degree)	{ // Method to adjust claw position with the direction and degree

	int leeway = 60;

	clawVal = SensorValue[s1];

	if(!clawDone && (clawVal != 246))	{

		if(clawVal >= (degree + leeway))	{ // If claw wants to open

			motor[g1] = -127;
			motor[g2] = -127;

			clawDone = false;

			}	else if (clawVal <= (degree - leeway))	{ // If claw wants to close

			motor[g1] = 127;
			motor[g2] = 127;

			clawDone = false;

			}	else	{

			motor[g1] = 0;
			motor[g2] = 0;

			clawDone = true;

		}

	}

}

void lift(int degree)	{ // Method to adjust lift arm position by direction of change in rotation

	int leeway = 1;

	liftVal = SensorValue[s2];

	if(!liftDone)	{

		if (liftVal >= (degree + leeway))	{

			motor[l1] = -127;
			motor[l2] = -127;

			motor[l4] = -127;
			motor[l6] = -127;

			liftDone = false;

			}	else if (liftVal <= (degree - leeway))	{

			motor[l1] = 127;
			motor[l2] = 127;
			motor[l4] = 127;
			motor[l6] = 127;

			liftDone = false;

			}	else	{

			motor[l1] = 0;
			motor[l2] = 0;
			motor[l4] = 0;
			motor[l6] = 0;

			liftDone = true;

		}

	}

}

void drive(int left, int right, int speed)	{ // Method which automatically drives the robot

	int leeway = 1;

	int currentL = SensorValue[s3];
	int currentR = -SensorValue[s4];

	if (SensorValue[whichSquare] == 0)	{

	int temp = left;
	left = right;
	right = temp;

}

	if(!leftDone)	{

		if (currentL >= (left + leeway))	{

			motor[d1] = -speed;

			leftDone = false;

			}	else if(currentL <= (left - leeway))	{

			motor[d1] = speed;

			leftDone = false;

			}	else	{

			motor[d1] = 0;

			leftDone = true;

		}

	}

	if(!rightDone)	{

		if (currentR >= (right + leeway))	{

			motor[d2] = -speed;

			rightDone = false;

			}	else if(currentR <= (right - leeway))	{

			motor[d2] = speed;

			rightDone = false;

			}	else	{

			motor[d2] = 0;

			rightDone = true;

		}

	}

	if(leftDone && rightDone)	{

		driveDone = true;

	}

}

void resetVar()	{

	leftDone = false;
	rightDone = false;
	liftDone = false;
	clawDone = false;

}

void auton1()	{

	switch (state)	{

	case 0 :

		SensorValue[s3] = 0;
		SensorValue[s4] = 0;

		resetVar();

		state++;

		break;

	case 1 :

		claw(clawHalf);

		lift(liftBig);

		drive(100, 200, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	case 2 :

		claw(clawHalf);

		lift(liftBig);

		drive(660, 710, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	case 3 :

		lift(liftBig);

		drive (780, 780, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	case 4 :


		lift(liftBig);

		drive (1750, 1750, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	case 5 :

		drive (970, 970, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	default :

		motor[d1] = 0;
		motor[d2] = 0;
		motor[g1] = 0;
		motor[g2] = 0;
		motor[l1] = 0;
		motor[l2] = 0;
		motor[l4] = 0;
		motor[l6] = 0;

		break;

	}

}

void auton2()	{

ClearTimer(T1);

	switch(state)	{

	case 0 :

		SensorValue[s3] = 0;
		SensorValue[s4] = 0;

		resetVar();

		state++;

		break;

	case 1 :

		if(leftVal >= 400)	{

			claw(clawQuarter);

		}

		drive(815, 815, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	case 2 :

		motor[g1] = -127;
		motor[g2] = -127;

		if (((clawVal <= 350) && (clawVal < 240 || clawVal > 250)) || (time1(T1) >= 1000))	{

			resetVar();

			state++;

		}

		break;

	case 3:

		motor[g1] = -70;
		motor[g2] = -70;

		lift(liftCube);

		if (liftDone) 	{

			resetVar();

			state++;

		}

		break;

	case 4 :

		drive (1000, 750, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	case 5 :

		drive (2000, 1750, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	case 6 :

		claw(clawQuarter);

		if (clawDone)	{

			resetVar();

			state++;

		}

		break;

	case 7 :

		drive (1000, 500, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	case 8 :

		drive (600, 900, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

		case 9 :

		drive (150, 750, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	case 10 :

		lift(-SensorValue[s2]);

		if(liftDone)	{

			resetVar();

			state++;

		}

		break;

		case 11 :

		drive (850, 1150, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

			ClearTimer(T1);

		}

		break;

		case 12 :

		motor[g1] = -127;
		motor[g2] = -127;

		if ((clawVal <= 240) || (time1(T1) >= 1000))	{

			resetVar();

			state++;

		}

		break;

		case 13:

		motor[g1] = -70;
		motor[g2] = -70;

		lift(liftStars);

		if (liftDone) 	{

			resetVar();

			state++;

		}

		break;

		case 14 :

		drive (1200, 800, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

		case 15 :

		drive (2300, 2200, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

		case 16 :

		drive(2400, 2300, 127);

		claw(clawHalf);

		if (clawDone)	{

			resetVar();

			state++;

		}

		break;



	default :

		motor[d1] = 0;
		motor[d2] = 0;
		motor[g1] = 0;
		motor[g2] = 0;
		motor[l1] = 0;
		motor[l2] = 0;
		motor[l4] = 0;
		motor[l6] = 0;

		break;

	}

}

void auton3()	{


ClearTimer(T1);

	switch(state)	{

	case 0 :

		SensorValue[s3] = 0;
		SensorValue[s4] = 0;

		resetVar();

		state++;

		break;

	case 1 :

		if(leftVal >= 400)	{

			claw(clawQuarter);

		}

		drive(815, 815, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	case 2 :

		motor[g1] = -127;
		motor[g2] = -127;

		if (((clawVal <= 350) && (clawVal < 240 || clawVal > 250)) || (time1(T1) >= 1000))	{

			resetVar();

			state++;

		}

		break;

	case 3:

		motor[g1] = -70;
		motor[g2] = -70;

		lift(liftCube);

		if (liftDone) 	{

			resetVar();

			state++;

		}

		break;

	case 4 :

		drive (1000, 750, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	case 5 :

		drive (2000, 1750, 127);

		if (leftDone && rightDone)	{

			resetVar();

			state++;

		}

		break;

	case 6 :

		claw(clawQuarter);

		if (clawDone)	{

			resetVar();

			state++;

		}

		break;

	default :

		motor[d1] = 0;
		motor[d2] = 0;
		motor[g1] = 0;
		motor[g2] = 0;
		motor[l1] = 0;
		motor[l2] = 0;
		motor[l4] = 0;
		motor[l6] = 0;

		break;

	}

}

task autonomous()
{

	SensorValue[s2] = 0;
	SensorValue[s3] = 0;
	SensorValue[s4] = 0;
	state = 0;

	while(true)	{

		clawVal = SensorValue[s1];
		liftVal = SensorValue[s2];

		leftVal = SensorValue[s3];
		rightVal = -SensorValue[s4];

		if(SensorValue[selector] == 0)	{

			auton1();

			}	else if (SensorValue[onlyCube] == 0)	{

			auton2();

		}		else if (SensorValue[onlyCube] == 1)	{

			auton3();

		}

	}

	motor[d1] = 0;
	motor[d2] = 0;
	motor[g1] = 0;
	motor[g2] = 0;
	motor[l1] = 0;
	motor[l2] = 0;
	motor[l4] = 0;
	motor[l6] = 0;

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{

	SensorValue[s2] = 0;
	SensorValue[s3] = 0;
	SensorValue[s4] = 0;

	const int threshold = 15;

	while (true)	{

		clawVal = SensorValue[s1];
		liftVal = SensorValue[s2];

		leftVal = SensorValue[s3];
		rightVal = -SensorValue[s4];

		driveL = vexRT[Ch2];
		driveR = vexRT[Ch3];

		if(abs(driveR) >= threshold)	{

			motor[d1] = driveR;

			}	else {

			motor[d1] = 0;

		}
		if(abs(driveL) >= threshold)	{

			motor[d2] = driveL;

			}else	{


			motor[d2] = 0;

		}

		if(vexRT[Btn6U] == 1)	{

			motor[g1] = 127;
			motor[g2] = 127;

			lowPow = false;

			}	else if(vexRT[Btn6D] == 1)	{

			motor[g1] = -127;
			motor[g2] = -127;

			lowPow = false;

			}	else if (!(lowPow))	{

			motor[g1] = 0;
			motor[g2] = 0;

		}

		if(vexRT[Btn8D] == 1)	{

			lowPow = true;

			motor[g1]	= -50;
			motor[g2]	= -50;

		}

		if (vexRT[Btn5U] == 1)	{

			motor[l1] = 127;
			motor[l2] = 127;

			motor[l4] = 127;
			motor[l6] = 127;

			}	else if (vexRT[Btn5D] == 1)	{

			motor[l1] = -127;
			motor[l2] = -127;

			motor[l4] = -127;
			motor[l6] = -127;

			}	else	{

			motor[l1] = 0;
			motor[l2] = 0;

			motor[l4] = 0;
			motor[l6] = 0;

		}

	}
}

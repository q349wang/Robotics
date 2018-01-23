#pragma config(Sensor, in2,    s1,             sensorPotentiometer)
#pragma config(Sensor, in3,    s2,             sensorPotentiometer)
#pragma config(Sensor, dgtl1,  s3,             sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  s4,             sensorQuadEncoder)
#pragma config(Sensor, dgtl12, selector,       sensorDigitalIn)
#pragma config(Motor,  port2,           l1,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           l2,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           g1,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           d1,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           d2,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           g2,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           l4,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           l6,            tmotorVex393_MC29, openLoop, reversed)
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

const int clawStart = 494;
const int clawHalf = clawStart + 1400;
const int clawFull = clawStart + 2820;
const int clawQuarter = clawStart + 550;
bool clawDone =  false;

const int liftMin = 2240;
const int liftBig = liftMin - 1457;
const int liftSmall = liftMin - 1297;
const int liftMax = liftMin - 1776;
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

	int leeway = 100;

	clawVal = SensorValue[s1];

	if(!clawDone && (clawVal > 300))	{

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

	int leeway = 100;

	liftVal = SensorValue[s2];

	if(!liftDone && (liftVal > 300))	{

		if (liftVal <= (degree - leeway))	{

			motor[l1] = -127;
			motor[l2] = -127;

			motor[l4] = -127;
			motor[l6] = -127;

			liftDone = false;

			}	else if (liftVal >= (degree + leeway))	{

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

void drive(int left, int right)	{ // Method which automatically drives the robot

	int leeway = 5;

	int currentL = SensorValue[s3];
	int currentR = -SensorValue[s4];

	if(!leftDone)	{

		if (currentL >= (left + leeway))	{

			motor[d1] = -127;

			leftDone = false;

			}	else if(currentL <= (left - leeway))	{

			motor[d1] = 127;

			leftDone = false;

			}	else	{

			motor[d1] = 0;

			leftDone = true;

		}

	}

	if(!rightDone)	{

		if (currentR >= (right + leeway))	{

			motor[d2] = -127;

			rightDone = false;

			}	else if(currentR <= (right - leeway))	{

			motor[d2] = 127;

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

task autonomous()
{

	ClearTimer(T1);

	while(time1(T1) < 15000)	{

		clawVal = SensorValue[s1];
		liftVal = SensorValue[s2];

		leftVal = SensorValue[s3];
		rightVal = -SensorValue[s4];

		switch (state)	{

		case 0 :

			SensorValue[s3] = 0;
			SensorValue[s4] = 0;

			state++;

			break;

		case 1 :

			claw(clawHalf);

			lift(liftBig);

			drive(574, 574);

			if (leftDone && rightDone)	{

				state++;

				resetVar();

			}

			break;

		case 2 :

			claw(clawHalf);

			lift(liftBig);

			drive(574, 780);

			motor[d1] = 0;

			leftDone = true;

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		case 3 :

			claw(clawHalf);

			lift(liftBig);

			drive (990, 1274);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		case 4 :

			lift(liftBig);

			drive (1214, 1254);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		case 5 :

			lift(liftBig);

			drive (1972, 1998);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}


			break;


		case 6 :

			drive (1052, 1066);

			if (leftDone && rightDone)	{

				resetVar();

				if(SensorValue[selector] == 0)	{

					state = -1;

					}	else	{

					state++;

				}

			}

			break;


		case 7 :

			drive(1304, 389);

			lift(liftMin);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		case 8 :

			drive(2041, 1177);

			lift(liftMin);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		case 9 :

			//drive(2343, 1410);

			lift(liftMin);

			if (liftDone)	{

				resetVar();

				state++;

			}

			break;

		case 10 :

			motor[g1] = -127;
			motor[g2] = -127;

			if (clawVal < 550)	{

				state++;

			}

			break;

		case 11 :

			motor[g1] = -60;
			motor[g2] = -60;

			if(liftVal < 1750)	{

				drive(2012, 1749);

			}
			lift(liftBig);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		case 12 :

			drive(3015, 2931);
			lift(liftBig);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		case 13 :

			claw(clawQuarter);

			if (clawDone)	{

				resetVar();

				state++;

			}

			break;

		case 14 :

			drive(2634, 2686);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		case 15 :

			drive(2618, 1302);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		case 16 :

			drive(1672, 338);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		case 17 :

			claw(clawStart);

			if(clawVal < 400)	{

				lift(liftMin);

			}

			if (liftDone)	{

				resetVar();

				state++;

			}

			break;

		case 18 :

			claw(clawQuarter);

			drive(3091, 1749);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		case 19 :

			motor[g1] = -127;
			motor[g2] = -127;

			if (clawVal < 400)	{

				resetVar();

				state++;

			}

			break;

		case 20 :

			motor[g1] = -60;
			motor[g2] = -60;

			drive(2747, 2322);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		case 21 :

			lift(liftBig);

			drive(4460, 3960);

			if (leftDone && rightDone && liftDone)	{

				resetVar();

				state++;

			}

			break;

		case 22 :

			claw(clawQuarter);

			if (leftDone && rightDone)	{

				resetVar();

				state++;

			}

			break;

		default :

			motor[d1] = 0;
			motor[d2] = 0;

			break;

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

			motor[g1]	= -60;
			motor[g2]	= -60;

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

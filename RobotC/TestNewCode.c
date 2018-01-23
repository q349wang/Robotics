#pragma config(Sensor, in1,    lift,           sensorPotentiometer)
#pragma config(Sensor, in2,    grabber,        sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rightDrive,     sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftDrive,      sensorQuadEncoder)
#pragma config(Motor,  port2,           grabR,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           liftL1,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           liftL2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           driveL,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           driveR,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           liftR1,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftR2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           grabL,         tmotorVex393_MC29, openLoop)
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

const int threshold = 15; // Threshold for how much the joystick must be pushed before activating drive
int liftPos = 0; // Holds potentiometer value for the lift position
int leftPos = 0, rightPos = 0; // Holds shaft encoder value for left and right drive chains respectively

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

// Autonomous Functions - Fucntions used in the autonomous task to control robot

void drive(int left, int right)	{

	int currentL = SensorValue[leftDrive];
	int currentR = SensorValue[rightDrive];

	int leeway = 2;

	if(currentL > (left + leeway)	{

		motor[driveL] = -127;

		}	else	if(currentL < (left - leeway)	{

		motor[driveL] = 127;

		}	else	{

		motor[driveL] = 0;

	}

	if(currentR > (right + leeway)	{

		motor[driveR] = -127;

		}	else	if(currentR < (right - leeway)	{

		motor[driveR] = 127;

		}	else	{

		motor[driveR] = 0;

	}

}

void launch(int degree)	{

	int current = SensorValue[lift];



	if(current > (degree + leeway))	{

		motor[liftL1] = 127;
		motor[liftL2] = 127;
		motor[liftR1] = 127;
		motor[liftR2] = 127;

		}	else	if (current < (degree - leeway))	{

		motor[liftL1] = -127;
		motor[liftL2] = -127;
		motor[liftR1] = -127;
		motor[liftR2] = -127;

		}	else	{

		motor[liftL1] = 0;
		motor[liftL2] = 0;
		motor[liftR1] = 0;
		motor[liftR2] = 0;

	}

}

void grab(int degree)	{

	int current = SensorValue[grabber];


	if(current > (degree + leeway))	{

		motor[grabL] = 127;
		motor[grabR] = 127;

		}	else	if (current < (degree - leeway))	{

		motor[grabL] = -127;
		motor[grabR] = -127;

		}	else	{

		motor[grabL] = 0;
		motor[grabR] = 0;

	}

}

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

task autonomous()
{

AutonomousCodePlaceholderForTesting();
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

while (true)
{

	liftPos = SensorValue[lift];
	leftPos = SensorValue[leftDrive];
	rightPos = SensorValue[rightDrive];

	if(abs(vexRT[Ch3]) > threshold)	{ // Turns left drive the same amount as specified by the joystick if the joystick value is over 15

		motor[driveL] = vexRT[Ch3];

		}	else	{

		motor[driveL] = 0;

	}

	if(abs(vexRT[Ch2]) > threshold)	{ // Turns right drive the same amount as specified by the joystick if the joystick value is over 15

		motor[driveR] = vexRT[Ch2];

		}	else	{

		motor[driveR] = 0;

	}

	if(vexRT[Btn6U]==1)	{

		motor[liftL1] = 127;
		motor[liftL2] = 127;
		motor[liftR1] = 127;
		motor[liftR2] = 127;

		}	else	if (vexRT[Btn6D] ==1)	{

		motor[liftL1] = -127;
		motor[liftL2] = -127;
		motor[liftR1] = -127;
		motor[liftR2] = -127;

		}	else	{

		motor[liftL1] = 0;
		motor[liftL2] = 0;
		motor[liftR1] = 0;
		motor[liftR2] = 0;

	}

	if(vexRT[Btn5U]==1)	{

		motor[grabL] = 127;
		motor[grabR] = 127;

		}	else	if (vexRT[Btn5D] ==1)	{

		motor[grabL] = -127;
		motor[grabR] = -127;

		}	else	{

		motor[grabL] = 0;
		motor[grabR] = 0;
	}


}
}

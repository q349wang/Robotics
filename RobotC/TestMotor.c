#pragma config(Motor,  port2,           test,          tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           test2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           test3,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           test4,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           test5,         tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{

while(true)	{

	motor[test] = 127;

}

}

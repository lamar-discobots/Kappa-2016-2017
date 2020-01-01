#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           claw1,         tmotorVex393_HBridge, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port5,           rightMotor,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port6,           lift1,         tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port7,           lift2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftMotor,     tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port10,          claw2,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
void partOne(int degree, int distance)
{
	//converts distance to degrees for encoders
	int distance2 = distance*360/(4*3.1415926535);

	while(nMotorEncoder[claw2] < degree)
	{
		motor[claw1] = 127;
		motor[claw2] = 127;
	}
		motor[claw1] = 0;
		motor[claw2] = 0;

	while(nMotorEncoder[leftMotor] < distance2 && nMotorEncoder[leftMotor] < distance2)
	{
		if (nMotorEncoder[leftMotor] > nMotorEncoder[rightMotor] + 10)
		{
			motor[leftMotor] = 120;
			motor[rightMotor]= 127;
		} else if (nMotorEncoder[leftMotor] < nMotorEncoder[rightMotor] - 10)
		{
			motor[leftMotor] =127;
			motor[rightMotor]= 120;
		}	else {
			motor[leftMotor] = 127;
			motor[rightMotor]= 127;
		}
	}
		motor[rightMotor]= 0;
		motor[leftMotor]= 0;
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
void partTwo(int degree, int distance)
{
	//converts distance to degrees for encoders
	int distance2 = distance*360/(4*3.1415926535);

	while(nMotorEncoder[claw2] < degree)
	{
		motor[claw1] = 127;
		motor[claw2] = 127;
	}
		motor[claw1] = 15;
		motor[claw2] = 15;

	while(nMotorEncoder[leftMotor] > distance2 && nMotorEncoder[leftMotor] > distance2)
	{
		if (nMotorEncoder[leftMotor] > nMotorEncoder[rightMotor] + 10)
		{
			motor[leftMotor] = -127;
			motor[rightMotor]= -120;
		} else if (nMotorEncoder[leftMotor] < nMotorEncoder[rightMotor] - 10)
		{
			motor[leftMotor] = -120;
			motor[rightMotor]= -127;
		}	else {
			motor[leftMotor] = -127;
			motor[rightMotor]= -127;
		}
	}
		motor[rightMotor]= 0;
		motor[leftMotor]= 0;
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
void partThree()
{

}
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
motor[rightMotor] = motor[leftMotor] = 83;
wait1Msec(500);

motor[claw1] = motor[claw2] = 127;
wait1Msec(650);
motor[claw1] = motor[claw2] = 0;

motor[lift1] = motor[lift2] = -127;
wait1Msec(1250);
motor[lift1] = motor[lift2] = -20;

motor[rightMotor] = motor[leftMotor] = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		int leftstick = vexRT[Ch3];
		int rightstick = vexRT[Ch2];
		int liftbuttonU = vexRT[Btn6U];
		int liftbuttonD = vexRT[Btn6D];
		int clawopen = vexRT[Btn5U];
		int clawclose = vexRT[Btn5D];


		//left motor control
		if (leftstick > 10 || leftstick < -10){
			motor [leftMotor] = leftstick;
			//			motor [leftMotorB] = leftstick;
		}
		else
			motor [leftMotor] = 0;
		//			motor [leftMotorB] = 0;

		//right motor control
		if (rightstick > 10 || rightstick <-10){
			motor [rightMotor] = rightstick;
			//			motor [rightMotorB] = rightstick;
		}
		else
			motor [rightMotor] = 0;
		//			motor [rightMotorB] = 0;

		//Lift control
		if (liftbuttonU == 1){
			motor [lift1] = -127;
			motor[lift2] = -127;
		}
		else if (liftbuttonD == 1){
			motor [lift1] = 127;
			motor[lift2] = 127;
		}
		else {
			motor [lift1] = 0;
			motor[lift2] = 0;
		}
		//Claw control
		if (clawopen == 1){
			motor [claw1] = 127;
			motor [claw2] = 127;
		}
		else if (clawclose == 1){
			motor [claw1] = -127;
			motor [claw2] = -127;
		}
		else{
			motor[claw1] = 10;
			motor[claw2] = -10;}
	}

}
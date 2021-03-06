#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           claw1,         tmotorVex393_HBridge, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port4,           hang,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightMotor,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port6,           lift1,         tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port7,           lift2,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftMotor,     tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
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

void move(int dist)
{
	dist = dist*392/12.5;

	while(nMotorEncoder[rightMotor] < dist)
	{
		motor[rightMotor] = motor[leftMotor] = 127;
	}

	motor[rightMotor] = motor[leftMotor] = 0;
}

void turn(int deg)
{
	deg = degreesToRadians(deg)*10*392/12.5;

		while(nMotorEncoder[rightMotor] < abs(deg))
	{
		motor[leftMotor]  = deg/deg* 127;
		motor[rightMotor] = deg*deg*-127;
	}

	motor[rightMotor] = motor[leftMotor] = 0;
}
task autonomous()
{
resetMotorEncoder(lift1);
resetMotorEncoder(rightMotor);
resetMotorEncoder(leftMotor);

move(12.5);

turn(360);

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
		int hango = vexRT[Btn8U];
		int hangi = vexRT[Btn8D];


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
			motor [lift1] = 127;
			motor[lift2] = 127;
		}
		else if (liftbuttonD == 1){
			motor [lift1] = -127;
			motor[lift2] = -127;
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
		else
			{
			motor[claw1] = 10;
			motor[claw2] = -10;
			}

			//linear slide control
		if (hango == 1)
		{
			motor [hang] = 127;
		}
		else if (hangi == 1)
		{
			motor [hang] = -127;
		}
		else
		{
			motor[hang] = 0;
		}
	}

}

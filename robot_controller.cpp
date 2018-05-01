#include "Arduino.h"
#include "robot_controller.h"

// This function measure the distance values from the ultrasonic sensor.
float RobotControl::sensorValueCalculation(int triggerPin, int echoPin){
	// digitalWrite() is a standard arduino library function is used to give digital output to a digital pin 0 - 13
	digitalWrite(triggerPin,HIGH);
	// delayMicroseconds() is a standard arduino library function that is used to provide delay specified in microseconds
	delayMicroseconds(10);
	digitalWrite(triggerPin,LOW);
	// pulseIn() function measures the duration for which we are recieving a pulse on the digital pin
	float duration = pulseIn(echoPin, HIGH);
	float distance = duration*0.034/2;
	return distance;
}

// This function is used to take the robot in the forward direction
void RobotControl::advance(){
	digitalWrite(LEFT_HIGH,HIGH);
	digitalWrite(LEFT_LOW,LOW);
	digitalWrite(RIGHT_HIGH,HIGH);
	digitalWrite(RIGHT_LOW,LOW);
}

// This function is used to turn the robot in the right direction
void RobotControl::turnRight(){
	digitalWrite(LEFT_HIGH,HIGH);
	digitalWrite(LEFT_LOW,LOW);
	digitalWrite(RIGHT_HIGH,LOW);
	digitalWrite(RIGHT_LOW,LOW);
	Serial.println("Taking a right turn");
	delay(2250);
	stop();
}

// This function is used to turn the robot in the left direction
void RobotControl::turnLeft(){
	digitalWrite(LEFT_HIGH,LOW);
	digitalWrite(LEFT_LOW,LOW);
	digitalWrite(RIGHT_HIGH,HIGH);
	digitalWrite(RIGHT_LOW,LOW);
	Serial.println("Taking a left turn");
	delay(2250);
	stop();
}

// This function is used to stop the robot from moving forward
void RobotControl::stop(){
	digitalWrite(LEFT_HIGH,LOW);
	digitalWrite(LEFT_LOW,LOW);
	digitalWrite(RIGHT_HIGH,LOW);
	digitalWrite(RIGHT_LOW,LOW);
	Serial.println("I have stopped");
}

// This function is used to take the robot in the reverse direction
void RobotControl::fallBack(){
	digitalWrite(LEFT_HIGH,LOW);
	digitalWrite(RIGHT_HIGH,LOW);
	digitalWrite(LEFT_LOW,HIGH);
	digitalWrite(RIGHT_LOW,HIGH);
	Serial.println("Reversing");
}

void RobotControl::moveForward(){
	if(goAhead == true){
		advance();
	}
}

void RobotControl::initialTraversalRight(int fallBackOffset){
	turnRight();
	delay(3000);
	float startOfTraversalTime = millis();
	while(sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO) < (40 + fallBackOffset)){
		advance();
	}
	advance();
	delay(650);
	stop();
	float endOfTraversalTime = millis();
	initialTraversalTime = abs(startOfTraversalTime - endOfTraversalTime);
	Serial.println("Initial Traversal Time");
	Serial.println(initialTraversalTime);
}

void RobotControl::secondaryTraversalRight(bool fallBackOffset){
	turnLeft();
	advance();
	delay(650);
	stop();
	if (fallBackOffset) {
		advance();
		delay(3000);
	}
	while(sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO) < 40 || sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO) > 3000){
		advance();
	}
	advance();
	delay(650);
	stop();
}

void RobotControl::finalTraversalRight(){
	turnLeft();
	stop();
	advance();
	delay(initialTraversalTime);
	Serial.println("Object is fully traversed");
	turnRight();
	stop();
	delay(1000);
	goAhead = true;
}

void RobotControl::initialTraversalLeft(int fallBackOffset){
	turnLeft();
	delay(3000);
	float startOfTraversalTime = millis();
	while(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) < (40 + fallBackOffset)){
		advance();
	}
	advance();
	delay(650);
	stop();
	float endOfTraversalTime = millis();
	initialTraversalTime = abs(endOfTraversalTime - startOfTraversalTime);
	goAhead = false;
}

void RobotControl::secondaryTraversalLeft(bool fallBackOffset){
	turnRight();
	advance();
	delay(650);
	stop();
	if(fallBackOffset){
		advance();
		delay(3000);
	}
	while(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) < 40 || sensorValueCalculation(RIGHT_TRIGGER, RIGHT_ECHO) > 3000){
		advance();
	}
	advance();
	delay(650);
	stop();
}

void RobotControl::finalTraversalLeft(){
	turnRight();
	stop();
	advance();
	delay(initialTraversalTime);
	Serial.println("Object fully traversed");
	turnLeft();
	stop();
	delay(1000);
	goAhead = true;
}

void RobotControl::SimpleTraversal(){
	if(sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO) > 25){
		moveForward();
	}
	else{
		if(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) > 30 && sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO) > 30){
			if(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) > sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO)){
				initialTraversalRight(0);
				secondaryTraversalRight(false);
				finalTraversalRight();
			}
			else if(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) < sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO)){
				initialTraversalLeft(0);
				secondaryTraversalLeft(false);
				finalTraversalLeft();
			}
		}
		else{
			fallBack();
			delay(3000);
			if(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) > sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO)){
				initialTraversalRight(100);
				secondaryTraversalRight(true);
				finalTraversalRight();
			}
			else if(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) < sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO)){
				initialTraversalLeft(100);
				secondaryTraversalLeft(true);
				finalTraversalLeft();
			}
		}
	}
}

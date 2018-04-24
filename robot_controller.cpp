#include "Arduino.h"
#include "robot_controller.h"

float RobotControl::sensorValueCalculation(int triggerPin, int echoPin){
	digitalWrite(triggerPin,HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin,LOW);
	float duration = pulseIn(echoPin, HIGH);
	float distance = duration*0.034/2;
	return distance;
}

void RobotControl::advance(){
	digitalWrite(LEFT_HIGH,HIGH);
	digitalWrite(LEFT_LOW,LOW);
	digitalWrite(RIGHT_HIGH,HIGH);
	digitalWrite(RIGHT_LOW,LOW);
}

void RobotControl::turnRight(){
	digitalWrite(LEFT_HIGH,HIGH);
	digitalWrite(LEFT_LOW,LOW);
	digitalWrite(RIGHT_HIGH,LOW);
	digitalWrite(RIGHT_LOW,LOW);
	Serial.println("Taking a right turn");
	delay(3000);
	stop();
}

void RobotControl::turnLeft(){
	digitalWrite(LEFT_HIGH,LOW);
	digitalWrite(LEFT_LOW,LOW);
	digitalWrite(RIGHT_HIGH,HIGH);
	digitalWrite(RIGHT_LOW,LOW);
	Serial.println("Taking a left turn");
	delay(3000);
	stop();
}

void RobotControl::stop(){
	digitalWrite(LEFT_HIGH,LOW);
	digitalWrite(LEFT_LOW,LOW);
	digitalWrite(RIGHT_HIGH,LOW);
	digitalWrite(RIGHT_LOW,LOW);
	Serial.println("I have stopped");
}

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

void RobotControl::initialTraversalRight(){
	turnRight();
	float startOfTraversalRecordedDistance = sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO);
	delay(3000);
	while(sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO) < 40 || sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO) > 3000){
		advance();
	}
	float endOfTraversalRecorderDistance = sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO);
	initialTraversedDistance = startOfTraversalRecordedDistance - endOfTraversalRecorderDistance;
	Serial.println("Initially traversed distance");
	Serial.println(initialTraversedDistance);
	advance();
	delay(650);
	stop();
}

void RobotControl::secondaryTraversalRight(){
	turnLeft();
	advance();
	delay(650);
	stop();
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
	float finalTraversalStartingDistance = sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO);
	Serial.println(finalTraversalStartingDistance);
	while((finalTraversalStartingDistance - sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO)) <= abs(initialTraversedDistance)){
		Serial.println("Final distance is going coming");
		Serial.println(finalTraversalStartingDistance - sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO));
		advance();
	}
	Serial.println("Object is fully traversed");
	turnRight();
	stop();
	delay(1000);
	goAhead = true;
}

void RobotControl::initialTraversalLeft(){
	turnLeft();
	float startOfTraversalRecordedDistance = sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO);
	delay(3000);
	while(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) < 40 || sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) > 3000){
		advance();
	}
	float endOfTraversalRecorderDistance = sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO);
	initialTraversedDistance = startOfTraversalRecordedDistance - endOfTraversalRecorderDistance;
	Serial.println("Initially traversed distance");
	Serial.println(initialTraversedDistance);
	advance();
	delay(650);
	stop();
	goAhead = false;
}

void RobotControl::secondaryTraversalLeft(){
	turnRight();
	advance();
	delay(650);
	stop();
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
	float finalTraversalStartingDistance = sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO);
	Serial.println(finalTraversalStartingDistance);
	while((finalTraversalStartingDistance - sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO)) <= abs(initialTraversedDistance)){
		Serial.println("Final distance is going coming");
		Serial.println(finalTraversalStartingDistance - sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO));
		advance();
	}
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
				initialTraversalRight();
				secondaryTraversalRight();
				finalTraversalRight();
			}
			else if(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) < sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO)){
				initialTraversalLeft();
				secondaryTraversalLeft();
				finalTraversalLeft();
			}
		}
	}
}

#include "Arduino.h"
#include "arpit.h"

float RobotControl::sensorValueCalculation(int triggerPin, int echoPin){

	digitalWrite(triggerPin,HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin,LOW);
	float duration = pulseIn(echoPin, HIGH);
	float distance = duration*0.034/2;
	return distance;

}

void RobotControl::advance(){

	Serial.println(sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO));
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

void RobotControl::SimpleTraversal(){

	if(sensorValueCalculation(FRONT_TRIGGER,FRONT_ECHO) > 25){

		if(goAhead == true){
			advance();
		}

	}
	else{
		if(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) > 30 && sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO) > 30){

			if(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) > sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO)){

				turnRight();
				delay(3000);
				while(sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO) < 40 || sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO) > 3000){
					advance();
				}
				advance();
				delay(650);
				stop();
				goAhead = false;

			}

			else if(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) < sensorValueCalculation(LEFT_TRIGGER,LEFT_ECHO)){

				turnLeft();
				delay(3000);
				while(sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) < 40 || sensorValueCalculation(RIGHT_TRIGGER,RIGHT_ECHO) > 3000){
					advance();
				}
				Serial.println("Out of the loop");
				advance();
				delay(650);
				stop();
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
				goAhead = false;

			}

		}
	}


}

#include "robot_controller.h"

RobotControl robo;

void setup()
{
    pinMode(LEFT_HIGH, OUTPUT);
    pinMode(LEFT_LOW, OUTPUT);
    pinMode(RIGHT_LOW, OUTPUT);
    pinMode(RIGHT_HIGH, OUTPUT);

    pinMode(LEFT_TRIGGER,OUTPUT);
    pinMode(RIGHT_TRIGGER,OUTPUT);
    pinMode(FRONT_TRIGGER,OUTPUT);
    pinMode(REAR_TRIGGER,OUTPUT);

    pinMode(LEFT_ECHO,INPUT);
    pinMode(RIGHT_ECHO,INPUT);
    pinMode(REAR_ECHO,INPUT);
    pinMode(FRONT_ECHO,INPUT);

    Serial.begin(9600);
}

void loop()
{
  robo.SimpleTraversal();
}

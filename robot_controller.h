#define LEFT_HIGH		2
#define LEFT_LOW		3
#define RIGHT_LOW		4
#define RIGHT_HIGH	5

#define REAR_TRIGGER	6
#define RIGHT_TRIGGER	7
#define	FRONT_TRIGGER	8
#define LEFT_TRIGGER	9

#define REAR_ECHO			10
#define RIGHT_ECHO		11
#define FRONT_ECHO		12
#define LEFT_ECHO			13

class RobotControl{

public:

  bool isTraversing = false;
	float sensorValueCalculation(int,int);
	void proceed();
	void advance();
	void traverseObstacle();
	void traverseRight(float,float);
	void traverseLeft(float,float);
	void turnRight();
	void turnLeft();
	void stop();
	void fallBack();
	void SimpleTraversal();
	bool goAhead = true;

};

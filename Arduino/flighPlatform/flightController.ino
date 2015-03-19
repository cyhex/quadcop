
/**
* Flight Controller 
*
*/

#include <SoftwareSerial.h>
#include <Servo.h> 

// Constants
const int PIN_MOTOR_FRONT = 4;
const int PIN_MOTOR_BACK = 5;
const int PIN_MOTOR_LEFT = 6;
const int PIN_MOTOR_RIGHT = 7;

const int PIN_BT_RX = 3;
const int PIN_BT_TX = 2;

// user input gives 0-1024; servo input 0-180
const float SERVO_INPUT_RATIO = 0.175; 

// Begin user controlled input (Android App) definition
class inputController {

public:
	int inputBuffer[20];
	int intputBufferLen;
	int yaw;
	int pitch;
	int roll;
	int power;

	inputController();
	void read(SoftwareSerial& s);
	bool parseBuffer();
};

inputController::inputController(){
	intputBufferLen = 0;
	yaw = 0;
	pitch = 0;
	roll = 0;
	power = 0;
}

void inputController::read(SoftwareSerial& s){
	if (s.available()){
		if(intputBufferLen >= 20){
			intputBufferLen = 0;
		}
		inputBuffer[intputBufferLen] = s.read(); 
		intputBufferLen++;
	}
	
	if(intputBufferLen >= 10){
		parseBuffer();
	}
}

bool inputController::parseBuffer(){
	intputBufferLen = 0;

	int start = (inputBuffer[0] << 8) + inputBuffer[1];
	if(start != 32767){
		return false;
	}

	yaw = (inputBuffer[2] << 8) + inputBuffer[3];
	pitch = (inputBuffer[4] << 8) + inputBuffer[5];
	roll = (inputBuffer[6] << 8) + inputBuffer[7];
	power = (inputBuffer[8] << 8) + inputBuffer[9];
	return true;
}
// end inputController definition

// Begin flight controller definition

class flightController {

public:
	Servo motorFront; 
	//Servo motorBack; 
	//Servo motorLeft;
	//Servo motorRight;
	flightController();
	void setPosition(int yaw, int pitch, int roll, int power);

};

flightController::flightController(){
	motorFront.attach(PIN_MOTOR_FRONT);
	//motorBack.attach(PIN_MOTOR_BACK);
	//motorLeft.attach(PIN_MOTOR_LEFT);
	//motorRight.attach(PIN_MOTOR_RIGHT);
}

void flightController::setPosition(int yaw, int pitch, int roll, int power){
	motorFront.write(power * SERVO_INPUT_RATIO);
	//motorBack.write(power * SERVO_INPUT_RATIO);
	//motorLeft.write(power * SERVO_INPUT_RATIO);
	//motorRight.write(power * SERVO_INPUT_RATIO);
}


// End flight controller definition


// Instances definition
SoftwareSerial btSerial(PIN_BT_RX, PIN_BT_TX);
//inputController inc = inputController();
flightController flc = flightController();


long pos = 0;



void setup(){
	//btSerial.begin(9600);
	Serial.begin(9600);
  	Serial.println("Hello");
}	

void loop(){

	flc.motorFront.write(analogRead(A5)*SERVO_INPUT_RATIO);

}
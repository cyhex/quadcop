
/**
* Flight Controller 
*
*/

#include <SoftwareSerial.h>

SoftwareSerial btSerial(3,2);

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


// instances definition
inputController inc = inputController();

void setup(){
	btSerial.begin(9600);
	Serial.begin(9600);
  	Serial.println("Hello");

}

void loop(){
	inc.read(btSerial);
	
	if(!(millis() % 1000)){
		Serial.println(inc.power);
	}
}
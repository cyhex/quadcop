
/**
* Flight Controller 
*
*/

#include <SoftwareSerial.h>

SoftwareSerial btSerial(3, 2); // RX, TX
int inputBuffer[20];
int intputBufferLen = 0;

int v;

void setup(){
	Serial.begin(9600);
  	Serial.println("Hello");

	btSerial.begin(9600);
}

void parseBuffer(){
	intputBufferLen = 0;

	int start = (inputBuffer[0] << 8) + inputBuffer[1];
	if(start != 32767){
		return;
	}

	v = (inputBuffer[2] << 8) + inputBuffer[3];
	Serial.print("yaw: ");
	Serial.println(v);

	v = (inputBuffer[4] << 8) + inputBuffer[5];
	Serial.print("pitch: ");
	Serial.println(v);


	v = (inputBuffer[6] << 8) + inputBuffer[7];
	Serial.print("roll: ");
	Serial.println(v);

	v = (inputBuffer[8] << 8) + inputBuffer[9];
	Serial.print("power: ");
	Serial.println(v);

}

void loop(){
	if (btSerial.available()){
		if(intputBufferLen >= 20){
			intputBufferLen = 0;
		}
		inputBuffer[intputBufferLen] = btSerial.read(); 
		Serial.println(sizeof(inputBuffer));
		intputBufferLen++;
	}

	if(intputBufferLen >= 10){
		parseBuffer();
	}

}

/**
* Flight Controller 
*
*/

#include <SoftwareSerial.h>

SoftwareSerial btSerial(3, 2); // RX, TX
int inputBuffer[2] = {0,0};
int intputBufferLen = 0;

void setup(){
	Serial.begin(9600);
  	while (!Serial) {
    	delay(1);; // wait for serial port to connect. Needed for Leonardo only
  	}
  	Serial.println("Hello");

	btSerial.begin(9600);

}

void loop(){
	if (btSerial.available()){
		inputBuffer[intputBufferLen] = btSerial.read(); 
		intputBufferLen++;
	}

	if(intputBufferLen == 2){

		long i = (inputBuffer[0] << 8) + inputBuffer[1];
		intputBufferLen = 0;
		Serial.println(i);
	}
    
}
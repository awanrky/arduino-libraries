#ifndef _AISA_CD5PHOTOCELL_H_
#define _AISA_CD5PHOTOCELL_H_


 #include <Arduino.h>

class aisa_Cd5PhotoCell
{
public:
	int pin;
	int reading;

	aisa_Cd5PhotoCell(int analogPin);

	void takeReading();
	void toSerial();
};

#endif
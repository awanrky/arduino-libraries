#ifndef _AISA_CD5PHOTOCELL_H_
#define _AISA_CD5PHOTOCELL_H_


 #include <Arduino.h>

class aisa_Cd5PhotoCell
{
private:
	int pin;
	int reading;

public:

	aisa_Cd5PhotoCell(int analogPin);

	void takeReading();
	int getReading(bool takeReading = true);
};

#endif
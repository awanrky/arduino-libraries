
#include "aisa_Cd5PhotoCell.h"

aisa_Cd5PhotoCell::aisa_Cd5PhotoCell(int analogPin)
{
    pin = analogPin;
}

void aisa_Cd5PhotoCell::takeReading()
{
    reading = analogRead(pin);
}

int aisa_Cd5PhotoCell::getReading(bool takeReading)
{
	if (takeReading) 
	{
		this->takeReading();
	}
	return reading;
}

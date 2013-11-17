
#include "aisa_Cd5PhotoCell.h"

aisa_Cd5PhotoCell::aisa_Cd5PhotoCell(String name, int analogPin)
{
	sensorName = name;
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

String aisa_Cd5PhotoCell::getPinName()
{
    char * buffer = "axx";
    sprintf(buffer, "a%d", pin);
    return buffer;
}

String aisa_Cd5PhotoCell::getSensorName()
{
    return sensorName;
}
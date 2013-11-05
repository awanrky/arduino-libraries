
#include "aisa_Cd5Photocell.h"

aisa_Cd5PhotoCell::aisa_Cd5PhotoCell(int analogPin)
{
    pin = analogPin;
}

void aisa_Cd5PhotoCell::takeReading()
{
    reading = analogRead(pin);
}

void aisa_Cd5PhotoCell::toSerial()
{
    Serial.print("Cd5 Photo Cell--");
    Serial.println(reading);
}

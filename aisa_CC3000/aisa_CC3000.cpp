#include "aisa_CC3000.h"

aisa_CC3000::aisa_CC3000(int irqPin, int vbatPin, int csPin)
{
	spiClockDivider = SPI_CLOCK_DIVIDER;
	irq = irqPin;
	vbat = vbatPin;
	cs = csPin;
	isInitialized = false;
	cc3000 = new Adafruit_CC3000(cs, irq, vbat, spiClockDivider);
	ipStringBuffer = new char[20];
}

bool aisa_CC3000::initialize()
{
	isInitialized = cc3000->begin();
	return isInitialized;
}

bool aisa_CC3000::connectToAp(const char * networkSsid, const char * networkPassword, uint8_t networkSecurityType)
{
	bool connected = cc3000->connectToAP(networkSsid, networkPassword, networkSecurityType);

	if (connected) 
	{
		ssid = networkSsid;
		password = networkPassword;
		securityType = networkSecurityType;
	}
	return connected;
}

bool aisa_CC3000::waitForDhcpAddress()
{
	int delayMs = 100;
	int wait = 100;
	int numberOfTries = 0;

	while(!cc3000->checkDHCP())
	{
		if (numberOfTries > wait)
		{
			return false;
		}
		numberOfTries++;
		delay(delayMs);
	}
	return true;
}

bool aisa_CC3000::connectToNetwork(const char * networkSsid, const char * networkPassword, uint8_t networkSecurityType)
{
	return  this->connectToAp(networkSsid, networkPassword, networkSecurityType) &&
			this->waitForDhcpAddress();
}

void aisa_CC3000::disconnect()
{
	cc3000->disconnect();
}

bool aisa_CC3000::getAddress()
{
	return cc3000->getIPAddress(&ipAddress, &netmask, &gateway, &dhcpServer, &dnsServer);
}

String aisa_CC3000::getIpAddressString(bool refreshAddress)
{
	if (refreshAddress)
	{
		this->getAddress();
	}
	return this->getIpDotsString(ipAddress);
}

String aisa_CC3000::getNetmaskString(bool refreshAddress)
{
	if (refreshAddress)
	{
		this->getAddress();
	}
	return this->getIpDotsString(netmask);
}

String aisa_CC3000::getGatewayString(bool refreshAddress)
{
	if (refreshAddress)
	{
		this->getAddress();
	}
	return this->getIpDotsString(gateway);
}

String aisa_CC3000::getDhcpServerString(bool refreshAddress)
{
	if (refreshAddress)
	{
		this->getAddress();
	}
	return this->getIpDotsString(dhcpServer);
}

String aisa_CC3000::getDnsServerString(bool refreshAddress)
{
	if (refreshAddress)
	{
		this->getAddress();
	}
	return this->getIpDotsString(dnsServer);
}

String aisa_CC3000::getIpDotsString(uint32_t ip)
{
	sprintf(ipStringBuffer, "%d.%d.%d.%d", 
		(uint8_t)(ip >> 24),
		(uint8_t)(ip >> 16),
		(uint8_t)(ip >> 8),
		(uint8_t)(ip));

	return ipStringBuffer;
}
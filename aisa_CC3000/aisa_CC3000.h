#ifndef _AISA_CC3000_H_
#define _AISA_CC3000_H_

#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"

class aisa_CC3000
{
private:

	bool isInitialized;

	char * ipStringBuffer;

	int irq;

	int vbat;
	int cs;

	int spiClockDivider;

	String ssid;
	String password;

	int securityType;

	uint32_t ipAddress;
	uint32_t netmask;
	uint32_t gateway;
	uint32_t dhcpServer;
	uint32_t dnsServer;

	int idleTimeoutMilliseconds;

	Adafruit_CC3000 * cc3000;

public:

	aisa_CC3000(int irqPin, int vbatPin, int csPin);

	bool initialize();

	bool connectToAp(const char * networkSsid, const char * networkPassword, uint8_t networkSecurityType);

	bool waitForDhcpAddress();

	bool connectToNetwork(const char * networkSsid, const char * networkPassword, uint8_t networkSecurityType);

	bool getAddress();

	String getIpAddressString(bool refreshAddress);

	String getNetmaskString(bool refreshAddress);

	String getGatewayString(bool refreshAddress);

	String getDhcpServerString(bool refreshAddress);

	String getDnsServerString(bool refreshAddress);

	String getIpDotsString(uint32_t ip);

	void disconnect();
};

#endif
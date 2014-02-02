#ifndef _AISA_CC3000_H_
#define _AISA_CC3000_H_

#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"

#define AISA_CC3000_NO_ERROR 0;
#define AISA_CC3000_NOT_INITIALIZED 1;
#define AISA_CC3000_COULD_NOT_CONNECT_TO_AP 2;
#define AISA_CC3000_COULD_NOT_GET_DHCP_ADDRESS 3;
#define AISA_CC3000_COULD_NOT_GET_IP_ADDRESS_INFORMATION 4;
#define AISA_CC3000_COULD_NOT_RESOLVE_HOST_NAME 5;
#define AISA_CC3000_COULD_NOT_CONNECT_TO_SERVER_TCP 6;
#define AISA_CC3000_NO_RESPONSE 7;

class aisa_CC3000
{
private:

	int errorState;

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

	char * userAgentString;

public:

	aisa_CC3000(int irqPin, int vbatPin, int csPin);

	bool initialize();

	bool checkInitialized();

	bool connectToAp(const char * networkSsid, const char * networkPassword, uint8_t networkSecurityType);

	bool waitForDhcpAddress();

	bool connectToNetwork(const char * networkSsid, const char * networkPassword, uint8_t networkSecurityType);

	bool getAddress();

	int getErrorState();

	String getIpAddressString(bool refreshAddress);

	String getNetmaskString(bool refreshAddress);

	String getGatewayString(bool refreshAddress);

	String getDhcpServerString(bool refreshAddress);

	String getDnsServerString(bool refreshAddress);

	String getIpDotsString(uint32_t ip);

	bool checkConnected();

	void disconnect();

	uint32_t getHostByName(char * hostName);

	Adafruit_CC3000_Client getTcpConnection(char * hostName, uint16_t hostPort);

	Adafruit_CC3000_Client getTcpConnection(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4, uint16_t port);

	String readStatusCode(Adafruit_CC3000_Client * www);

	String tcpGet(char * hostName, char * route);

	String tcpGet(char * hostName, uint16_t hostPort, char * route);

	String tcpPost(char * hostName, char * route, char * parameters);

	String tcpPost(char * hostName, uint16_t hostPort, char * route, char * parameters);
	
	String tcpPost(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4, uint16_t port, char * route, char * parameters);

	String tcpPost(Adafruit_CC3000_Client www, char * route, char * parameters);
};
#endif
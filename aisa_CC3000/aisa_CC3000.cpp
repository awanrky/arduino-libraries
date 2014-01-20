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
	idleTimeoutMilliseconds = 10000;
	userAgentString = "User-Agent: Arduino Home";
}

bool aisa_CC3000::initialize()
{
	isInitialized = cc3000->begin();
	return this->checkInitialized();
}

bool aisa_CC3000::checkInitialized()
{
	if (!isInitialized)
	{
		errorState = AISA_CC3000_NOT_INITIALIZED;
		return false;
	}
	return true;
}

bool aisa_CC3000::connectToAp(const char * networkSsid, const char * networkPassword, uint8_t networkSecurityType)
{
	if (!this->checkInitialized())
	{
		return false;
	}

	bool connected = cc3000->connectToAP(networkSsid, networkPassword, networkSecurityType);

	if (connected) 
	{
		ssid = networkSsid;
		password = networkPassword;
		securityType = networkSecurityType;
		errorState = AISA_CC3000_NO_ERROR;
	}
	else
	{
		errorState = AISA_CC3000_COULD_NOT_CONNECT_TO_AP
	}
	return connected;
}

bool aisa_CC3000::waitForDhcpAddress()
{
	int delayMs = 100;
	int wait = 100;
	int numberOfTries = 0;

	if (!this->checkInitialized())
	{
		return false;
	}

	while(!cc3000->checkDHCP())
	{
		if (numberOfTries > wait)
		{
			errorState = AISA_CC3000_COULD_NOT_GET_DHCP_ADDRESS;
			return false;
		}
		numberOfTries++;
		delay(delayMs);
	}
	errorState = AISA_CC3000_NO_ERROR;
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

int aisa_CC3000::getErrorState()
{
	return errorState;
}

bool aisa_CC3000::getAddress()
{
	if (!this->checkInitialized())
	{
		return false;
	}

	bool fail = cc3000->getIPAddress(&ipAddress, &netmask, &gateway, &dhcpServer, &dnsServer);
	if (fail) 
	{
		errorState = AISA_CC3000_COULD_NOT_GET_IP_ADDRESS_INFORMATION;
	}
	else
	{
		errorState = AISA_CC3000_NO_ERROR;
	}
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

uint32_t aisa_CC3000::getHostByName(char * hostName)
{
	uint32_t ip = 0;
	int delayMs = 0;

	if (!this->checkInitialized())
	{
		return 0;
	}

	while (ip == 0)
	{
		if (!cc3000->getHostByName(hostName, &ip))
		{
			delayMs += 500;
			if (delayMs >= idleTimeoutMilliseconds)
			{
				errorState = AISA_CC3000_COULD_NOT_RESOLVE_HOST_NAME;
				break;
			}
		}
		else
		{
			errorState = AISA_CC3000_NO_ERROR;
			break;
		}
	}
	return ip;
}

Adafruit_CC3000_Client aisa_CC3000::getTcpConnection(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4, uint16_t port)
{
	if (!this->checkInitialized())
	{
		return NULL;
	}

	uint32_t ip = (uint32_t)octet1 << 24;
	ip += (uint32_t)octet2 << 16;
	ip += (uint32_t)octet3 << 8;
	ip += octet4;

	return cc3000->connectTCP(ip, port);
}

Adafruit_CC3000_Client aisa_CC3000::getTcpConnection(char * hostName, uint16_t hostPort)
{
	uint32_t hostIp;

	if (!this->checkInitialized())
	{
		return NULL;
	}

	hostIp = this->getHostByName(hostName);
	if (hostIp == 0)
	{
		return NULL;
	}

	return cc3000->connectTCP(hostIp, hostPort);
}

String aisa_CC3000::readStatusCode(Adafruit_CC3000_Client * www)
{
	char c;
	String readBuffer = "";
	unsigned long lastRead = millis();
	while (www->connected() && (millis() - lastRead < idleTimeoutMilliseconds))
	{
		while (www->available()) 
		{
			c = www->read();
			readBuffer = readBuffer + c;

			if (c == '\r' || c == '\n')
			{
				errorState = AISA_CC3000_NO_ERROR;
				return readBuffer.substring(9, 12);
			}
		}
	}
	errorState = AISA_CC3000_NO_RESPONSE;
	return "";
}

String aisa_CC3000::tcpGet(char * hostName, char * route)
{
	return this->tcpGet(hostName, 80, route);
}

String aisa_CC3000::tcpGet(char * hostName, uint16_t hostPort, char * route)
{
	String statusCode = "";

	Adafruit_CC3000_Client www = this->getTcpConnection(hostName, hostPort);
	if (!www.connected())
	{
		errorState = AISA_CC3000_COULD_NOT_CONNECT_TO_SERVER_TCP;
		return NULL;
	}

	www.fastrprint(F("GET "));
	www.fastrprint(route);
	www.fastrprint(F(" HTTP/1.1\r\n"));
	www.fastrprint(F("Host: "));
	www.fastrprint(hostName);
	www.fastrprint(F("\r\n"));
	www.fastrprint(F("\r\n"));
	www.println();

	statusCode = this->readStatusCode(&www);

	www.close();

	return statusCode;
}

String aisa_CC3000::tcpPost(char * hostName, char * route, char * parameters)
{
	return this->tcpPost(hostName, 80, route, parameters);
}

String aisa_CC3000::tcpPost(char * hostName, uint16_t hostPort, char * route, char * parameters)
{
	String statusCode = "";

	Adafruit_CC3000_Client www = this->getTcpConnection(hostName, hostPort);
	if (!www.connected())
	{
		errorState = AISA_CC3000_COULD_NOT_CONNECT_TO_SERVER_TCP;
		return "";
	}
	return this->tcpPost(www, route, parameters);
}

String aisa_CC3000::tcpPost(uint8_t octet1, uint8_t octet2, uint8_t octet3, uint8_t octet4, uint16_t port, char * route, char * parameters)
{

	Adafruit_CC3000_Client www = this->getTcpConnection(octet1, octet2, octet3, octet4, port);
	if (!www.connected())
	{
		errorState = AISA_CC3000_COULD_NOT_CONNECT_TO_SERVER_TCP;
		return "";
	}
	return this->tcpPost(www, route, parameters);
}

String aisa_CC3000::tcpPost(Adafruit_CC3000_Client www, char * route, char * parameters)
{
	String statusCode = "";

	www.fastrprint(F("POST "));
	www.fastrprint(route);
	www.fastrprint(F(" HTTP/1.1\r\n"));

	www.fastrprint(F("Host: "));
	www.fastrprint("blah");
	www.fastrprint(F("\r\n"));

	www.fastrprint(userAgentString);
	www.fastrprint(F("\r\n"));

	www.fastrprint(F("Content-Type: application/x-www-form-urlencoded"));
	www.fastrprint(F("\r\n"));

	www.fastrprint(F("Content-Length: "));

	char buffer[10];
	String contentLengthString = String(strlen(parameters));
	contentLengthString.toCharArray(buffer, 10);
	www.fastrprint(buffer);
	www.fastrprint(F("\r\n\r\n"));

	www.fastrprint(parameters);

	www.fastrprint(F("\r\n\r\n"));
	www.println();

	statusCode = this->readStatusCode(&www);

	www.close();

	return statusCode;
}
#ifndef __AISA_ETHERNET_H_
#define __AISA_ETHERNET_H_

#include <SPI.h>
#include <Ethernet.h>

class aisa_ethernet
{
private:
	EthernetClient ethernetClient;

	byte * macAddress;

	bool ready;

	// char * getRequest;
	char * postRequest;

	
	char request[500];

public:
	aisa_ethernet(byte * mac);

	bool initialize();

	// bool get(IPAddress server, uint16_t port, char * route, char * queryString);

	bool post(IPAddress server, uint16_t port, char * route, char * contentJson);

};
#endif
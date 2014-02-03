#include "aisa_ethernet.h"

aisa_ethernet::aisa_ethernet(byte * mac)
{
	macAddress = mac;

	postRequest = "POST %s HTTP/1.1\r\nHost: blah\r\nUser-Agent: arduino-ethernet\r\nContent-Length: %d\r\nContent-Type: application/json\r\n\r\n%s\r\n";
	getRequest = "GET %s HTTP/1.1\r\nHost: blah\r\nUser-Agent: arduino-ethernet\r\nContent-Length: %d\r\n\r\n";

	// initialize();
}

bool aisa_ethernet::initialize()
{
	if (Ethernet.begin(macAddress) != 0)
	{
		ready = true;
	}
	else
	{
		ready = false;
	}
	return ready;
}

bool aisa_ethernet::get(IPAddress server, uint16_t port, char * route, char * queryString)
{

}

bool aisa_ethernet::post(IPAddress server, uint16_t port, char * route, char * contentJson)
{
	char request[500];
	bool returnValue;

	size_t contentLength = strlen(contentJson);

	sprintf(request, postRequest, route, contentLength, contentJson);

	if(ethernetClient.connect(server, port))
	{
		ethernetClient.print(request);

		if(ethernetClient.find("HTTP/1.1") && ethernetClient.find("201 Created") ){
	       returnValue = true;
	    }

	    ethernetClient.flush();
	}
	else
	{
		returnValue = false;
	}
	ethernetClient.stop();
	return returnValue;
}
#ifndef httpgetH
#define httpgetH

#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

#include <json/json.h>

typedef struct
{
	int portno;
	char *host;
	char *getformat;

	char request[100], response[300], json[100];
}httpclient;

void jsonWriteChannel(httpclient *h, int id, int devid, unsigned char value);
unsigned char jsonChannelGetValue(httpclient *h, int id, int devid);
void jsonWriteBit(httpclient *h, int id, int devid, unsigned char value);
unsigned char jsonBitGetValue(httpclient *h, int id, int devid);
void jsonWritePulse(httpclient *h, int id, int devid, unsigned char value);
unsigned char jsonPulseGetValue(httpclient *h, int id, int devid);
unsigned char jsonReadChannel(httpclient *h, int id, int devid);
#endif

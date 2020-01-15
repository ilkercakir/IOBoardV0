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

void http_get_init(httpclient *h);
void http_get_command(httpclient *h, char *command, char *parameters);
void http_get(httpclient *h);
#endif

#include "httpget.h"

void http_get(httpclient *h, char *command, char *parameters)
{
	struct hostent *server;
	struct sockaddr_in serv_addr;
	int sockfd, bytes, sent, received, total;
	
	h->portno = 8080;
	h->host = "localhost";
	h->getformat = "GET /IOBoardV0/ControllerConsole?%s%s HTTP/1.0\r\n\r\n";

	sprintf(h->request, h->getformat, command, parameters);
//printf("Request: %s\n", h->request);

	/* create the socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		printf("ERROR opening socket\n");
		return;
	}

	/* lookup the ip address */
	server = gethostbyname(h->host);
	if (server == NULL)
	{
		printf("ERROR, no such host\n");
		return;
	}

	/* fill in the structure */
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(h->portno);
	memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

	/* connect the socket */
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("ERROR connecting\n");
		return;
	}

	/* send the request */
	total = strlen(h->request);
	sent = 0;
	do
	{
		bytes = write(sockfd, h->request+sent, total-sent);
		if (bytes < 0)
			printf("ERROR writing request to socket\n");
        if (bytes == 0)
            break;
		sent+=bytes;
	}while (sent < total);

	/* receive the response */
	memset(h->response, 0, sizeof(h->response));
	total = sizeof(h->response) - 1;
	received = 0;
	do
	{
		bytes = read(sockfd, h->response+received, total-received);
		if (bytes < 0)
			printf("ERROR reading response from socket\n");
		if (bytes == 0)
			break;
		received+=bytes;
	}while(received < total);

	if (received == total)
	{
		printf("ERROR storing complete response from socket\n");
		return;
	}

	/* close the socket */
	close(sockfd);

	/* skip headers, convert response to JSON */
	int pipes[2];
	FILE *writepipe;
	FILE *readpipe;
	pipe(pipes);

	readpipe = fdopen(pipes[0], "r");
	writepipe = fdopen(pipes[1], "w");
	fputs(h->response, writepipe);
	fclose(writepipe);

	while(fgets(h->json, sizeof(h->json), readpipe) != NULL)
    {
		if (!strcmp(h->json, "\r\n"))
			break;
	}
/*
	while (fgets(h->json, sizeof(h->json), readpipe) != NULL)
	{
		printf("--> %s\n", h->json);
	}
*/
	fgets(h->json, sizeof(h->json), readpipe);
	fclose(readpipe);
}

void jsonWriteChannel(httpclient *h, int id, int devid, unsigned char value)
{
	char params[100];

	sprintf(params, "&id=%d&devid=%d&value=%d", id, devid, value);
	http_get(h, "channel", params);
//printf("%s\n", h.json);

	struct json_object *jobj, *val;

	jobj = json_tokener_parse(h->json);

	id = (json_object_object_get_ex(jobj, "id", &val)?json_object_get_int(val):-1);
	devid = (json_object_object_get_ex(jobj, "devid", &val)?json_object_get_int(val):-1);
	value = (unsigned char)(json_object_object_get_ex(jobj, "value", &val)?json_object_get_int(val):-1);

	json_object_put(jobj);
}

unsigned char jsonChannelGetValue(httpclient *h, int id, int devid)
{
	char params[100];

	sprintf(params, "&id=%d&devid=%d", id, devid);
	http_get(h, "channel", params);
//printf("%s\n", h.json);

	struct json_object *jobj, *val;

	jobj = json_tokener_parse(h->json);

	id = (json_object_object_get_ex(jobj, "id", &val)?json_object_get_int(val):-1);
	devid = (json_object_object_get_ex(jobj, "devid", &val)?json_object_get_int(val):-1);
	unsigned char value = (unsigned char)(json_object_object_get_ex(jobj, "value", &val)?json_object_get_int(val):-1);

	json_object_put(jobj);

	return(value);
}

void jsonWriteBit(httpclient *h, int id, int devid, unsigned char value)
{
	char params[100];

	sprintf(params, "&id=%d&devid=%d&value=%d", id, devid, value);
	http_get(h, "bit", params);
//printf("%s\n", h.json);

	struct json_object *jobj, *val;

	jobj = json_tokener_parse(h->json);

	id = (json_object_object_get_ex(jobj, "id", &val)?json_object_get_int(val):-1);
	devid = (json_object_object_get_ex(jobj, "devid", &val)?json_object_get_int(val):-1);
	value = (unsigned char)(json_object_object_get_ex(jobj, "value", &val)?json_object_get_int(val):-1);

	json_object_put(jobj);
}

unsigned char jsonBitGetValue(httpclient *h, int id, int devid)
{
	char params[100];

	sprintf(params, "&id=%d&devid=%d", id, devid);
	http_get(h, "bit", params);
//printf("%s\n", h.json);

	struct json_object *jobj, *val;

	jobj = json_tokener_parse(h->json);

	id = (json_object_object_get_ex(jobj, "id", &val)?json_object_get_int(val):-1);
	devid = (json_object_object_get_ex(jobj, "devid", &val)?json_object_get_int(val):-1);
	unsigned char value = (unsigned char)(json_object_object_get_ex(jobj, "value", &val)?json_object_get_int(val):-1);

	json_object_put(jobj);

	return(value);
}

void jsonWritePulse(httpclient *h, int id, int devid, unsigned char value)
{
	char params[100];

	sprintf(params, "&id=%d&devid=%d&value=%d", id, devid, value);
	http_get(h, "pulse", params);
//printf("%s\n", h.json);

	struct json_object *jobj, *val;

	jobj = json_tokener_parse(h->json);

	id = (json_object_object_get_ex(jobj, "id", &val)?json_object_get_int(val):-1);
	devid = (json_object_object_get_ex(jobj, "devid", &val)?json_object_get_int(val):-1);
	value = (json_object_object_get_ex(jobj, "value", &val)?json_object_get_int(val):-1);

	json_object_put(jobj);
}

unsigned char jsonPulseGetValue(httpclient *h, int id, int devid)
{
	char params[100];

	sprintf(params, "&id=%d&devid=%d", id, devid);
	http_get(h, "pulse", params);
//printf("%s\n", h.json);

	struct json_object *jobj, *val;

	jobj = json_tokener_parse(h->json);

	id = (json_object_object_get_ex(jobj, "id", &val)?json_object_get_int(val):-1);
	devid = (json_object_object_get_ex(jobj, "devid", &val)?json_object_get_int(val):-1);
	unsigned char value = (unsigned char)(json_object_object_get_ex(jobj, "value", &val)?json_object_get_int(val):-1);

	json_object_put(jobj);

	return(value);
}

unsigned char jsonReadChannel(httpclient *h, int id, int devid)
{
	char params[100];

	sprintf(params, "&id=%d&devid=%d", id, devid);
	http_get(h, "readchannel", params);
//printf("%s\n", h.json);

	struct json_object *jobj, *val;

	jobj = json_tokener_parse(h->json);

	id = (json_object_object_get_ex(jobj, "id", &val)?json_object_get_int(val):-1);
	devid = (json_object_object_get_ex(jobj, "devid", &val)?json_object_get_int(val):-1);
	unsigned char value = (unsigned char)(json_object_object_get_ex(jobj, "value", &val)?json_object_get_int(val):-1);

	json_object_put(jobj);

	return(value);
}

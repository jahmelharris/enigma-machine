/*
 * Client.cpp
 *
 *  Created on: 9 Aug 2010
 *      Author: jeharris
 */

#include "Client.h"
void *recvDataCli(void *);

Client::Client(std::string address, int port, struct msg* toEncrypt, struct msg* toDecrypt) {
	/*add signal handler for SIGPIPE*/

	int sockfd;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	if((sockfd = socket(AF_INET, SOCK_STREAM,0))==-1)
	{
		perror("socket\n");
		//exit(-1);
		throw 1;
	}

	if((server = gethostbyname(&address[0]))==NULL)
	{
		std::cerr<<"No host\n";
		//exit(-1);
		throw -1;
	}

	struct threadArg tArg;
	tArg.cli=&sockfd;
	tArg.toDecrypt=toDecrypt;

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons (port);
    if((connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)))==-1)
    {
    	perror("connect\n");
    	//exit(-1);
	throw 1;
    }
    pthread_t recvThread;
	pthread_create(&recvThread, NULL, recvDataCli, (void *) &tArg);

	for(;;)
	{
		pthread_testcancel();
		std::string st;
		pthread_mutex_lock(toEncrypt->mutex);
		size_t bufSize = toEncrypt->msg.length();
		send(sockfd,&bufSize,sizeof(size_t),0);
		send(sockfd,toEncrypt->msg.c_str(),bufSize,0);
	}

}

void *recvDataCli(void *x)
{
	struct threadArg *arg = (struct threadArg *) x;
	int* fd = arg->cli;
	size_t bufSize;
	char* buf;
	for(;;)
	{
		recv(*fd, &bufSize, sizeof(size_t), 0 );
		buf = new char[bufSize+1];
		bzero(buf,bufSize+1);
		recv(*fd, buf, bufSize, 0);
		arg->toDecrypt->msg = buf;
		pthread_mutex_unlock(arg->toDecrypt->mutex);

		bufSize=0;
		delete(buf);
	}
	return NULL;
}


Client::~Client() {
	// TODO Auto-generated destructor stub
}

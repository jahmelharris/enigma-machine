/*
 * Server.cpp
 *
 *  Created on: 8 Aug 2010
 *      Author: jeharris
 */

#include "Server.h"
void *recvDataServ(void *);


Server::Server(int portNo, struct msg* toEncrypt, struct msg* toDecrypt) {
	/*add signal handler for SIGPIPE*/
	pthread_t recvThread;
	int sockfd, cli;
	unsigned int len;
	struct sockaddr_in server, client;
	if((sockfd = socket(AF_INET, SOCK_STREAM,0)) == -1)
	{
		perror("socket:\n");
		exit(-1);
	}
	bzero((char*) &server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(portNo);
	server.sin_addr.s_addr = INADDR_ANY; //all interfaces
	len = sizeof(struct sockaddr_in);
	int tr=1;
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&tr,sizeof(int)) == -1) {
	    perror("setsockopt");
	    exit(-1);
	}
	if((bind(sockfd, (struct sockaddr *) &server, len))==-1)
	{
		perror("bind\n");
		exit(-1);
	}
	if((listen(sockfd, 1)) == -1)
	{
		perror("listen\n");
		exit(-1);
	}
		if((cli=accept(sockfd, (struct sockaddr *)&client, &len)) == -1)
		{
			perror("accept\n");
			exit(EXIT_FAILURE);
		}

		struct threadArg tArg;
		tArg.cli=&cli;
		tArg.toDecrypt=toDecrypt;

		pthread_create(&recvThread, NULL, recvDataServ, (void *) &tArg);

		for(;;)
		{
			pthread_mutex_lock(toEncrypt->mutex);
			size_t bufSize = toEncrypt->msg.length();
			send(cli,&bufSize,sizeof(size_t),0);
			send(cli,toEncrypt->msg.c_str(),bufSize,0);
			toEncrypt->flag=false;
		}
}

void *recvDataServ(void* x)
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
		//arg->toDecrypt->flag=true;
		pthread_mutex_unlock(arg->toDecrypt->mutex);
		bufSize=0;
		delete(buf);
	}
	return NULL;
}


Server::~Server() {
	// TODO Auto-generated destructor stub
	std::cout<<"server deconstructor\n";
}

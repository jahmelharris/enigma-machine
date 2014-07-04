//#include <iostream>
//#include <string>
#include "sharedDT.h"
#include "Machine.h"
#include "Server.h"
#include "Client.h"


using namespace std;

string sToUpper(string);
void *createServer(void *);
void *createClient(void *);
void *msgInput(void *);
void *recvData(void *);

struct threadArgs{
	struct msg* toEncrypt;
	struct msg* toDecrypt;
	int portNo;
	string address;
};

struct msgArg{
	struct threadArgs* ta;
	Machine *machine;
};

volatile bool m_exit = false; //TODO: replace with a better way to get thread to exit process

int main(int argc, char** argv)
{
	bool server=false;
	string address="127.0.0.1";
	int port=5000;
	int c;
	while ((c = getopt(argc, argv, "sa:p:")) != EOF)
	{
		switch(c)
		{
			case 's':
				server=true;
				break;
			case 'a':
				address = optarg;
				break;
			case 'p':
				port = atoi(optarg);
				break;
			default:
				cout<<"argument not supported\n";
				cout<<"-s\t\t\tserver mode\n-a <ip address>\t\taddress of server\n-p <port>\t\tport to listen/connect\n";
				return 0;
		}
	}


	Machine machine;
	struct msg toEncrypt;
	struct msg toDecrypt;
	toEncrypt.mutex = new pthread_mutex_t;
	toDecrypt.mutex = new pthread_mutex_t;

	pthread_mutex_init(toEncrypt.mutex, NULL);
	pthread_mutex_init(toDecrypt.mutex, NULL);
	pthread_mutex_lock(toEncrypt.mutex);
	pthread_mutex_lock(toDecrypt.mutex);

	toEncrypt.flag=false;
	toDecrypt.flag=false;

	struct threadArgs arg1;
	arg1.toEncrypt = &toEncrypt;
	arg1.toDecrypt = &toDecrypt;
	arg1.portNo=port;
	arg1.address=address;
	struct msgArg mArg;
	mArg.ta=&arg1;
	mArg.machine=&machine;
	pthread_t inputThread;
	pthread_create(&inputThread, NULL, msgInput, (void*)&mArg);

	pthread_t networkThread;
	if(server)
	{
		//pthread_t serverThread;
		pthread_create(&networkThread, NULL, createServer, (void*)&arg1);

	}
	else{
		//pthread_t clientThread;
		pthread_create(&networkThread, NULL, createClient, (void*)&arg1);
	}

	/*create thread to read recieved data from shared memory then decrypt and display*/
	/*create thread to read message to send from shared memory then encrypt and send*/
	for(;;)
	{
			pthread_mutex_lock(arg1.toDecrypt->mutex);
			if(m_exit)
			{
				cout<<"exit\n";
				pthread_cancel(networkThread);
				pthread_cancel(inputThread);
				break;	//TODO:replace with something better
			}
			cout<<"Friend: "<<machine.encrypt(toDecrypt.msg)<<"\n";
			arg1.toDecrypt->flag = false;
	}
	cout<<"out of loop\n";
	int retVal;
	pthread_exit(&retVal);
	delete toEncrypt.mutex;
	delete toDecrypt.mutex;
	return 0;
}



void *createServer(void *x)
{
	struct threadArgs *arg = (struct threadArgs*) x;
	Server s(arg->portNo, arg->toEncrypt , arg->toDecrypt);
	return NULL;
}

void *createClient(void *x)
{
	struct threadArgs *arg = (struct threadArgs*) x;
	try{
	Client c(arg->address, arg->portNo, arg->toEncrypt , arg->toDecrypt);
	}
	catch(...)
	{
		m_exit = true;
		cout<<"Unlocking toDecryptMutex\n";
		pthread_mutex_unlock(arg->toDecrypt->mutex);
	}
	return NULL;
}

void *msgInput(void *x)
{

	struct msgArg *mArg = (struct msgArg*) x;
	struct threadArgs *arg = mArg->ta;
	Machine *machine = mArg->machine;

	string st;
	for(;;)
	{
		pthread_testcancel();
		cin>>st;
		//pthread_mutex_lock(arg->toDecrypt->mutex);
		arg->toEncrypt->msg = machine->encrypt(st);
		pthread_mutex_unlock(arg->toEncrypt->mutex);
	}

	return NULL;
}

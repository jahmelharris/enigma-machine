/*
 * sharedDT.h
 *
 *  Created on: 8 Aug 2010
 *      Author: jeharris
 */

#ifndef SHAREDDT_H_
#define SHAREDDT_H_
#include <string>

struct msg{
	bool flag;
	std::string msg;
	pthread_mutex_t* mutex;
};

struct threadArg{
	struct msg* toDecrypt;
	int *cli;
};
#endif /* SHAREDDT_H_ */

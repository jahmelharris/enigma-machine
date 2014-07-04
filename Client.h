/*
 * Client.h
 *
 *  Created on: 9 Aug 2010
 *      Author: jeharris
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include "sharedDT.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
/*#include <string.h>
*/
class Client {
public:
	Client(std::string, int, struct msg*, struct msg*);

	virtual ~Client();
};

#endif /* CLIENT_H_ */

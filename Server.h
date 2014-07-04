/*
 * Server.h
 *
 *  Created on: 8 Aug 2010
 *      Author: jeharris
 */

#ifndef SERVER_H_
#define SERVER_H_

/*
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
//#include <string.h>
//#include <stdlib.h>
//#include <cstdlib>
//#include <iostream>
//#include <pthread.h>
#include "sharedDT.h"
//#include <stdio.h>
*/
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

class Server {
public:
	Server(int, struct msg*, struct msg*);
	virtual ~Server();
};


#endif /* SERVER_H_ */

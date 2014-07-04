/*
 * Machine.h
 *
 *  Created on: 8 Aug 2010
 *      Author: jeharris
 */

#ifndef MACHINE_H_
#define MACHINE_H_
#include <fstream>
#include <iostream>
#include <string>
#include "Rotor.h"
#include "Plugboard.h"

class Machine{
private:
	int const NUMBEROFROTOR;// = 5;
	int const NUMBEROFREFLECTOR; //= 2;

	Rotor *r1;
	Rotor *r2;
	Rotor *r3;
	Rotor *reflector;
	Plugboard *pb;

	void setMachine(Rotor*, Rotor*, Rotor*, Rotor*, Plugboard*);

public:
	Machine();
	std::string encrypt(std::string);
	void toString();

	virtual ~Machine();
	//string decrypt(string ct){return "string";}
};
#endif /* MACHINE_H_ */

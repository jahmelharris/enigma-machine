/*
 * Rotor.h
 *
 *  Created on: 3 Aug 2010
 *      Author: jeharris
 */

#ifndef ROTOR_H_
#define ROTOR_H_
#include <string>

//using std::string;

class Rotor {
private:
	std::string wiring;
	int position;
	int notch;
public:
	Rotor();
	Rotor(std::string, int);
	void loadWiring(std::string wiring);
	void setPosition(int); //initial state 1-26
	void advance(); //advance state of rotor
	void setNotch(char);
	char getCharF(char, int);
	char getCharB(char, int);
	char getNotch();
	int getPosition();
	std::string getCurrentState();
	std::string getCurrentWiring();
	std::string getWiring();
	virtual ~Rotor();
};

#endif /* ROTOR_H_ */

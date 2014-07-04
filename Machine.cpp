/*
 * Machine.cpp
 *
 *  Created on: 8 Aug 2010
 *      Author: jeharris
 */

#include "Machine.h"
void initRotor(Rotor*, Rotor *);
std::string sToUpper(std::string);


Machine::Machine() : 
		     NUMBEROFROTOR(5),
		     NUMBEROFREFLECTOR(2),
		     reflector(NULL)
{
	Rotor *rotor = new Rotor[NUMBEROFROTOR];
	for(int i=0;i<NUMBEROFROTOR;++i)
		rotor[i] = Rotor();
	Rotor *reflector = new Rotor[NUMBEROFREFLECTOR];
	for(int i=0;i<NUMBEROFREFLECTOR;++i)
		reflector[i] = Rotor();
	Plugboard *pb = new Plugboard;
	initRotor(&rotor[0], &reflector[0]);

	setMachine(&rotor[0], &rotor[1], &rotor[2],&reflector[0], pb);
	delete[] rotor;
}

Machine::~Machine() {
	delete[] reflector;
	delete pb;
/*	if(reflector)
		for(int i=0;i<NUMBEROFREFLECTOR;++i)
			delete &reflector[i];
	//delete[] reflector;
	//delete[] pb;
	// TODO Auto-generated destructor stub
	if(r1)
		delete r1;
	if(r2)
		delete r2;
	if(r3)
		delete r3;*/
}
void Machine::toString()
{
	std::cout<<"to string\n";
	std::cout<<"wiring tostring "<<r1->getCurrentWiring()<<"\n";
	std::cout<<"notch tostring "<<r1->getNotch()<<"\n";
	std::cout<<"wiring tostring "<<r2->getCurrentWiring()<<"\n";
	std::cout<<"notch tostring "<<r2->getNotch()<<"\n";
	std::cout<<"wiring tostring "<<r3->getCurrentWiring()<<"\n";
	std::cout<<"notch tostring "<<r3->getNotch()<<"\n";
	std::cout<<"wiring tostring "<<reflector->getCurrentWiring()<<"\n";
}

std::string Machine::encrypt(std::string pt)
{

	std::string ct="";
	pt = sToUpper(pb->convert(pt));

	for(size_t i=0;i<pt.length();++i)
	{
		if(r2->getCurrentState()[0]==r2->getNotch())
		{
			r2->advance();
			r3->advance();
		}
		if(r1->getCurrentState()[0]==r1->getNotch())
		{
			r2->advance();
		}
		r1->advance();
		char currentChar = r1->getCharF(pt[i],0);
		currentChar = r2->getCharF(currentChar,r1->getPosition());
		currentChar = r3->getCharF(currentChar,r2->getPosition());
		currentChar = reflector->getCharF(currentChar,r3->getPosition());
		currentChar = r3->getCharB(currentChar,reflector->getPosition());
		currentChar = r2->getCharB(currentChar,r3->getPosition());
		currentChar = r1->getCharB(currentChar,r2->getPosition());
		ct+=currentChar;
	}
	return pb->convert(ct);
}

void initRotor(Rotor *rotor, Rotor *reflector)
{
					   //ABCDEFGHIJKLMNOPQRSTUVWXYZ
	rotor[0].loadWiring("EKMFLGDQVZNTOWYHXUSPAIBRCJ");
	rotor[1].loadWiring("AJDKSIRUXBLHWTMCQGZNPYFVOE");
	rotor[2].loadWiring("BDFHJLCPRTXVZNYEIWGAKMUSQO");
	rotor[3].loadWiring("ESOVPZJAYQUIRHXLNFTGKDCMWB");
	rotor[4].loadWiring("VZBRGITYUPSDNHLXAWMJQOFECK");
						   //ABCDEFGHIJKLMNOPQRSTUVWXYZ
	reflector[0].loadWiring("YRUHQSLDPXNGOKMIEBFZCWVJAT");
	reflector[1].loadWiring("FVPJIAOYEDRZXWGCTKUQSBNMHL");

	rotor[0].setNotch('Q');
	rotor[1].setNotch('E');
	rotor[2].setNotch('V');
	rotor[3].setNotch('J');
	rotor[4].setNotch('Z');


}

//void setMachine(Rotor *r1, Rotor *r2, Rotor *r3, Rotor *reflector, Plugboard *pb)
void Machine::setMachine(Rotor *r1, Rotor *r2, Rotor *r3, Rotor *reflector, Plugboard *pb)
{

	this->r1 = r3;
	this->r2 = r2;
	this->r3 = r1;
	this->reflector = reflector;
	this->pb = pb;
	r1->setPosition(1);
	r2->setPosition(1);
	r3->setPosition(1);
}

std::string sToUpper(std::string s)
{
	std::string r;
	for(size_t i=0;i<s.length();++i){
		r+=std::toupper(s[i]);
  	}
	return r;
}



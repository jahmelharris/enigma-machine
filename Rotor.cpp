/*
 * Rotor.cpp
 *
 *  Created on: 3 Aug 2010
 *      Author: jeharris
 */

#include "Rotor.h"
#include <iostream>

Rotor::Rotor() {
	this->position = 0;
	this->notch = 0;
	this->wiring="";
}

Rotor::Rotor(std::string wiring, int position){
	this->wiring = wiring;
	this->position = position;
}

void Rotor::loadWiring(std::string wiring){
	this->wiring = wiring;
}

void Rotor::setPosition(int position){
	this->position = --position % 26;
}

std::string Rotor::getCurrentState(){
	std::string place = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return place.substr(position,26)+place.substr(0,position);
}

std::string Rotor::getCurrentWiring(){
	return wiring.substr(position,26)+wiring.substr(0,position);
}

void Rotor::advance(){
	++position;
	position %= 26;
}

void Rotor::setNotch(char notch){
	this->notch = (int)notch - 65;
}

char Rotor::getCharF(char ch, int offset){
	ch=ch-65-offset;
	if(ch<0){
		return wiring[(26+ch+position) % 26]; //work from the end of array

	}
	return wiring[(position+ch) % 26];
}

char Rotor::getCharB(char ch, int offset){
	ch+=position;
	ch-=65;
	ch = ch % 26;
	ch+=65;
	signed int result = (wiring.find(ch,0)-position) ;
	char x;
	if(result < 0)
		x = (26+result)+65;
	else
		x =result + 65;
	return x;
}

char Rotor::getNotch(){
	return notch+65;
}
std::string Rotor::getWiring(){
	return wiring;
}

int Rotor::getPosition(){
	return position;
}

Rotor::~Rotor() {
	// TODO Auto-generated destructor stub
}

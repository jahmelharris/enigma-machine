/*
 * Plugboard.h
 *
 *  Created on: 3 Aug 2010
 *      Author: jeharris
 */

#ifndef PLUGBOARD_H_
#define PLUGBOARD_H_
#include <string>
#include <cstdlib>
#include <iostream>
class Plugboard {

private:
	std::string input;
	std::string output;
public:
	Plugboard();
	/*swap string1[i] with string2[i]*/
	void setWiring(std::string, std::string);
	/*clear plugboard*/
	void clear();
	/*swap char1 with char2*/
	void swap(char, char);
	/*unplug char*/
	void unSwap(char);
	std::string convert(std::string);
	virtual ~Plugboard();
};

#endif /* PLUGBOARD_H_ */

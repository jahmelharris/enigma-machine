/*
 * Plugboard.cpp
 *
 *  Created on: 3 Aug 2010
 *      Author: jeharris
 */

#include "Plugboard.h"

Plugboard::Plugboard() {
	input="";
	output="";
}

void Plugboard::setWiring(std::string input, std::string output){
	int check=0;
	try{
		if(input.length()!=output.length())
			throw 1;
		for(size_t i=0;i<input.length();++i)
		{
			check = output.find(input[i],0);
			if(check != -1)
				throw 2;
		}
		for(size_t i=0;i<input.length();++i)
		{
			check = input.find(input[i],i+1);
			if(check != -1)
				throw 3;
		}
		for(size_t i=0;i<output.length();++i)
		{
			check = output.find(output[i],i+1);
			if(check != -1)
				throw 4;
		}
	}
		catch(int e)
		{
			if(e == 1)
				std::cerr<<"The plugboard should contain a one to one mapping \n";
			if(e == 2)
				std::cerr<<"A plug cannot plug into itself\n";
			if( e == 3)
				std::cerr<<"Input should be unique\n";
			if( e == 4)
				std::cerr<<"Output should be unique\n";

		}

	this->input = input;
	this->output = output;

}

void Plugboard::swap(char ch, char ch2)
{
	try{
	if(ch==ch2)
		throw 1;
	else
	{
		input+=ch;
		output+=ch2;
	}
	/*add other checks*/
	}
	catch(int e)
	{
		if(e==1)
			std::cerr<<"A plug cannot plug into itself. Swap not set\n";
	}

}

void Plugboard::clear()
{
	input="";
	output="";
}

void Plugboard::unSwap(char ch)
{
	signed int place=0;
	try{
		if((place = input.find(ch,0))==-1)
			throw 1;
		input.erase(place,1);
		output.erase(place,1);

	}
	catch(int e)
	{
		if(e==1)
			std::cerr<<"Swap not found\n";
	}
}

std::string Plugboard::convert(std::string text){
	std::string outputText;
	for(size_t i=0;i<text.length();++i){
		if((signed)input.find(text[i],0)!=-1){
			outputText +=this->output[input.find(text[i],0)];
		}
		else if((signed)output.find(text[i],0)!=-1){
			outputText +=this->input[output.find(text[i],0)];

		}
		else{
			outputText += text[i];
		}

	}
	return outputText;

}

Plugboard::~Plugboard() {
	// TODO Auto-generated destructor stub
}

#ifndef RAND_CHARACTER_H_H_H
#define RAND_CHARACTER_H_H_H

#include <iostream>
#include <sstream>
#include "rand.h"

using namespace std;

class RandCharacter {
public:
	RandCharacter(unsigned long charType, int len, unsigned long randType = Rand::RAND_TYPE_PSEUDO_RANDOM);
	void generate(void);
	friend ostream &operator<<(ostream &out, const RandCharacter &c);

	static const unsigned long CHARACTER_LOWER_CASE = 0x01;
	static const unsigned long CHARACTER_UPPER_CASE = 0x02;
	static const unsigned long CHARACTER_DIGIT = 0x04;
	static const unsigned long CHARACTER_SYMBOL = 0x08;

private:
	bool charValid(unsigned char ch);
	string _validChars;
	string _randChars;
	unsigned long _charType;
	char _len;
	unsigned long _randType;
	
};

#endif

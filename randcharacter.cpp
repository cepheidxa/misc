#include <iostream>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <sstream>

#include "randcharacter.h"

using namespace std;


RandCharacter::RandCharacter(unsigned long charType, int len, unsigned long randType)
{
	_charType = charType;
	_len = len;
	_randType = randType;

	for(unsigned char ch = 0; ch < 255; ch++) {
		if(charValid(ch)) {
			_validChars += ch;
		}
	}
	generate();
}

void RandCharacter::generate(void)
{
	assert(_validChars.length() > 0);
	Rand rand(_randType);
	unsigned long value;
	for(int i = 0; i < _len; i++) {
		do {
			rand.getRand(&value, sizeof(value));
		} while(value >= ULONG_MAX - ULONG_MAX % _validChars.length());
		_randChars += _validChars[value % _validChars.length()];
	}
	value = 0;
}

bool RandCharacter::charValid(unsigned char ch)
{
	assert(ch >= 0 && ch <= 255);
	if(!isgraph(ch))
		return false;

	if(_charType & CHARACTER_LOWER_CASE && islower(ch))
			return true;
	if(_charType & CHARACTER_UPPER_CASE && isupper(ch))
			return true;
	if(_charType & CHARACTER_DIGIT && isdigit(ch))
			return true;
	if(_charType & CHARACTER_SYMBOL) { 
		string chars = "!@#$%^&*(){}[];:<>,.?";
		string t = "1";
		t[0] = ch;
		if(chars.find(t) != string::npos)
			return true;
	}
		
	return false;
}

ostream &operator<<(ostream &out, const RandCharacter &c)
{
	out<<c._randChars;
	return out;
}

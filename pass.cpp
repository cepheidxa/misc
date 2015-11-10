#include <iostream>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <sstream>

#include "randcharacter.h"
#include "pass.h"

using namespace std;

Pass::Pass(int len, int alpha, int Alpha, int number, int symbol, unsigned long randType)
{
	_len = len;
	_alpha = alpha;
	_Alpha = Alpha;
	_number = number;
	_symbol = symbol;
	_randType = randType;
	
	generate();
}

ostream& operator<<(ostream &out, const Pass &p)
{
	out<<p._pass;
	return out;
}

void Pass::generate(void)
{
	ostringstream out;
	int len = 0;
	unsigned long type = 0;
	if(_alpha >= 0) {
		len += _alpha;
		type |= RandCharacter::CHARACTER_LOWER_CASE;
		RandCharacter p(RandCharacter::CHARACTER_LOWER_CASE, _alpha);
		out<<p;
	}
	if(_Alpha >= 0) {
		len += _Alpha;
		type |= RandCharacter::CHARACTER_UPPER_CASE;
		RandCharacter p(RandCharacter::CHARACTER_UPPER_CASE, _Alpha);
		out<<p;
	}
	if(_number >= 0) {
		len += _number;
		type |= RandCharacter::CHARACTER_DIGIT;
		RandCharacter p(RandCharacter::CHARACTER_DIGIT, _number);
		out<<p;
	}
	if(_symbol >= 0) {
		len += _symbol;
		type |= RandCharacter::CHARACTER_SYMBOL;
		RandCharacter p(RandCharacter::CHARACTER_SYMBOL, _symbol);
		out<<p;
	}
	len = _len - len;
	if(len > 0) {
		RandCharacter p(type, len);
		out<<p;
	}
	
	string pass = out.str();
	assert(pass.length() == _len);
	for(int i = 0; i < _len - 1; i++) {
		unsigned char v;
		Rand rand(_randType);
		do {
			rand.getRand(&v, sizeof(v));
		} while(v >= UCHAR_MAX - UCHAR_MAX % (_len - i));
		int pos = v % (_len - i);
		char tmp = pass[i];
		pass[i] = pass[ i + pos];
		pass[i + pos] = tmp;
	}
	_pass = pass;
}

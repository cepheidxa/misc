#ifndef PASS_H_H_H
#define PASS_H_H_H

#include <iostream>
#include <string>
#include "rand.h"

using std::ostream;
using std::string;

class Pass {
public:
	Pass(int len, int alpha = 0, int Alpha = 0, int number = 0, int symbol = 0, unsigned long randType = Rand::RAND_TYPE_PSEUDO_RANDOM);
	friend ostream &operator<<(ostream &out, const Pass &p);
private:
	void generate(void);
	int _alpha;
	int _Alpha;
	int _number;
	int _symbol;
	int _len;
	unsigned long _randType;
	string _pass;
};

#endif

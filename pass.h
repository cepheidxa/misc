#ifndef PASS_H_H_H
#define PASS_H_H_H

#include <iostream>
#include <sstream>

using namespace std;

class Pass {
public:
	Pass(int len, int alpha = 0, int Alpha = 0, int number = 0, int symbol = 0);
	~Pass(void);
	void print(void);
	friend ostream &operator<<(ostream &out, const Pass &p);
private:
	unsigned long getRand(void);
	void generate(void);
	int _alpha;
	int _Alpha;
	int _number;
	int _symbol;
	int _len;
	int _fd;
	string _pass;
};

#endif

#ifndef RAND_CHARACTER_H_H_H
#define RAND_CHARACTER_H_H_H

#include <iostream>
#include <sstream>

using namespace std;

class RandCharacter {
public:
	RandCharacter(unsigned long type, int len);
	~RandCharacter(void);
	void generate(void);
	friend ostream &operator<<(ostream &out, const RandCharacter &c);

	static const unsigned long CHARACTER_LOWER_CASE = 0x01;
	static const unsigned long CHARACTER_UPPER_CASE = 0x02;
	static const unsigned long CHARACTER_DIGIT = 0x04;
	static const unsigned long CHARACTER_SYMBOL = 0x08;
private:
	bool charValid(int ch);
	unsigned long getRand(void);
	int _fd;
	char *_chs;
	int _lchs;	
	char *_p;
	char _type;
	char _len;
};

#endif

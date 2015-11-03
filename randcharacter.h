#ifndef RAND_CHARACTER_H_H_H
#define RAND_CHARACTER_H_H_H

#include <iostream>
#include <sstream>

using namespace std;

#define CHARACTER_LOWER_CASE 0x01 
#define CHARACTER_UPPER_CASE 0x02
#define CHARACTER_DIGIT 0x04
#define CHARACTER_SYMBOL 0x08

class RandCharacter {
public:
	RandCharacter(unsigned long type, int len);
	~RandCharacter(void);
	void generate(void);
	friend ostream &operator<<(ostream &out, const RandCharacter &c);
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

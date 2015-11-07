#include <iostream>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <sstream>
#ifdef __cplusplus
extern "C" {
#endif
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <error.h>
	#include <errno.h>
#ifdef __cplusplus
}
#endif

#include "randcharacter.h"

using namespace std;

#define RANDOM_FILE "/dev/urandom"


RandCharacter::RandCharacter(unsigned long type, int len)
{
	_type = type;
	_len = len;

	_fd = open(RANDOM_FILE, O_RDONLY);
	if(_fd == -1)
		error_at_line(1, errno, __FILE__, __LINE__, "%s open failed.", RANDOM_FILE);
	
	_p = new char[_len + 1];
	assert(_p != NULL);
	
	_lchs = 0;
	for(int i = 0; i <= 255; i++) {
		if(charValid(i)) {
			_lchs++;
		}
	}
	assert(_lchs < 128 && _lchs > 0);
	_chs = new char[_lchs];
	assert(_chs != NULL);
	int j = 0;
	for(int i = 0; i <= 255; i++) {
		if(charValid(i)) {
			_chs[j++] = i;
		}
	}
	generate();
}

RandCharacter::~RandCharacter(void)
{
	close(_fd);
	if(_chs)
		delete[] _chs;
	if(_p)
		delete[] _p;
}

void RandCharacter::generate(void)
{
	assert(_p != NULL);
	unsigned long value;
	for(int i = 0; i < _len; i++) {
		do {
			value = getRand();
		} while(value >= ULONG_MAX - ULONG_MAX % _lchs);
		_p[i] = _chs[value % _lchs];
	}
	_p[_len] = '\0';
	value = 0;
}

unsigned long RandCharacter::getRand(void)
{
	unsigned long value;
	int ret = read(_fd, &value, sizeof(unsigned long));
	if(ret == -1)
		error_at_line(1, errno, __FILE__, __LINE__, "%s read failed.", RANDOM_FILE);
	return value;
}

bool RandCharacter::charValid(int ch)
{
	assert(ch >= 0 && ch <= 255);
	if(!isgraph(ch))
		return false;
		
	if(((_type & CHARACTER_LOWER_CASE) == 0) && islower(ch))
		return false;
	if(((_type & CHARACTER_UPPER_CASE) == 0) && isupper(ch))
		return false;
	if(((_type & CHARACTER_DIGIT) == 0) && isdigit(ch))
		return false;
	if(((_type & CHARACTER_SYMBOL) == 0) && (!isalnum(ch)))
		return false;

	return true;
}

ostream &operator<<(ostream &out, const RandCharacter &c)
{
	out<<c._p;
	return out;
}


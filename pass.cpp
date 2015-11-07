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
#include "pass.h"

using namespace std;

#define RANDOM_FILE "/dev/urandom"

Pass::Pass(int len, int alpha, int Alpha, int number, int symbol)
{
	_fd = open(RANDOM_FILE, O_RDONLY);
	if(_fd == -1)
		error_at_line(1, errno, __FILE__, __LINE__, "%s open failed.", RANDOM_FILE);
	_len = len;
	_alpha = alpha;
	_Alpha = Alpha;
	_number = number;
	_symbol = symbol;
	
	generate();
}

Pass::~Pass(void)
{
	close(_fd);
}

void Pass::print(void)
{
	cout<<_pass<<endl;
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
	if(_alpha > 0) {
		len += _alpha;
		RandCharacter p(RandCharacter::CHARACTER_LOWER_CASE, _alpha);
		out<<p;
	}
	if(_Alpha > 0) {
		len += _Alpha;
		RandCharacter p(RandCharacter::CHARACTER_UPPER_CASE, _Alpha);
		out<<p;
	}
	if(_number > 0) {
		len += _number;
		RandCharacter p(RandCharacter::CHARACTER_DIGIT, _number);
		out<<p;
	}
	if(_symbol > 0) {
		len += _symbol;
		RandCharacter p(RandCharacter::CHARACTER_SYMBOL, _symbol);
		out<<p;
	}
	
	unsigned type = 0;
	if(_alpha >= 0)
		type |= RandCharacter::CHARACTER_LOWER_CASE;
	if(_Alpha >= 0)
		type |= RandCharacter::CHARACTER_UPPER_CASE;
	if(_number >= 0)
		type |= RandCharacter::CHARACTER_DIGIT;
	if(_symbol >= 0)
		type |= RandCharacter::CHARACTER_SYMBOL;
		
	len = _len - len;
	if(len > 0) {
		RandCharacter p(type, len);
		out<<p;
	}
	
	string pass = out.str();
	for(int i = 0; i < _len - 1; i++) {
		unsigned long v;
		do {
			v = getRand();
		} while(v >= ULONG_MAX - ULONG_MAX % (_len - i));
		int pos = v % (_len - i);
		char tmp = pass[i];
		pass[i] = pass[ i + pos];
		pass[i + pos] = tmp;
	}
	_pass = pass;
}

unsigned long Pass::getRand(void)
{
	unsigned long value;
	int ret = read(_fd, &value, sizeof(unsigned long));
	if(ret == -1)
		error_at_line(1, errno, __FILE__, __LINE__, "%s read failed.", RANDOM_FILE);
	return value;
}


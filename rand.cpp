#include <iostream>
#include <cstdlib>
#include <climits>
#include <cassert>
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
#include "rand.h"

using namespace std;

Rand::Rand(unsigned long type)
{
	if(type & RAND_TYPE_RANDOM)
		_type = RAND_TYPE_RANDOM;
	else
		_type = RAND_TYPE_PSEUDO_RANDOM;

	if(_type & RAND_TYPE_RANDOM)
		_fd = open("/dev/random", O_RDONLY);
	else
		_fd = open("/dev/urandom", O_RDONLY);
	if(_fd == -1)
		error_at_line(1, errno, __FILE__, __LINE__, "file open failed.");
}

Rand::~Rand(void)
{
	close(_fd);
}

void Rand::getRand(void *data, int len)
{
	int ret = read(_fd, data, len);
	if(ret == -1)
		error_at_line(1, errno, __FILE__, __LINE__, "file read failed.");
}

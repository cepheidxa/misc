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
#include "pass.h"
#include "config.h"

using namespace std;

#define DEFAULT_PASS_LENGTH 16

int main(int argc, char *argv[])
{
	int N = DEFAULT_PASS_LENGTH;
	int alpha = 0;
	int Alpha = 0;
	int number = 0;
	int symbol = 0;
	int use_urandom = 1; // use /dev/random or /dev/urandom
	int opt;
	while((opt = getopt(argc, argv, "a:A:n:s:N:r")) != -1) {
		switch(opt) {
		case 'a':
			alpha = atoi(optarg);
			break;
		case 'A':
			Alpha = atoi(optarg);
			break;
		case 'n':
			number = atoi(optarg);
			break;
		case 's':
			symbol = atoi(optarg);
			break;
		case 'N':
			N = atoi(optarg);
			break;
		case 'r':
			use_urandom = 0;
			break;
		default:
			cerr<<"Usage: %s [-a n] [-A n] [-n n] [-s n] [-N n] [-r]"<<endl;
			cerr<<"Please report any bugs to "<<PACKAGE_BUGREPORT<<endl;
			exit(-1);
		}
	}
	
	int randtype;
	if(use_urandom)
		randtype = Rand::RAND_TYPE_PSEUDO_RANDOM;
	else
		randtype = Rand::RAND_TYPE_RANDOM;
	Pass p(N, alpha, Alpha, number, symbol, randtype);
	cout<<p<<endl;
	
}

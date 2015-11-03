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

using namespace std;

#define DEFAULT_PASS_LENGTH 16

int main(int argc, char *argv[])
{
	int N = DEFAULT_PASS_LENGTH;
	int alpha = 0;
	int Alpha = 0;
	int number = 0;
	int symbol = 0;
	int opt;
	while((opt = getopt(argc, argv, "a:A:n:s:N:")) != -1) {
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
		default:
			cerr<<"Usage: %s [-a n] [-A n] [-n n] [-s n] [-N n]"<<endl;
			exit(-1);
		}
	}
	
	Pass p(N, alpha, Alpha, number, symbol);
	cout<<p<<endl;
	
}

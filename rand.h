#ifndef MISC_RAND_H_H_H
#define MISC_RAND_H_H_H

class Rand {
public:
	Rand(unsigned long type = 0x01);
	~Rand(void);
	void getRand(void *data, int len);
	
	static const unsigned long RAND_TYPE_PSEUDO_RANDOM = 0x01;
	static const unsigned long RAND_TYPE_RANDOM = 0x02;
private:
	unsigned long _type;
	int _fd;
};

#endif

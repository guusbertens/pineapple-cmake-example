#pragma once

#include "Rng.h"
#include "openssl/md5.h"

class Md5Rng : public Rng
{
public:
	Md5Rng();
	std::pair<double, double> get_pair();
private:
	union {
		unsigned char m_md[MD5_DIGEST_LENGTH];
		struct { unsigned long long m_x, m_y; };
	};
};

// vim: ts=4 sw=4 cin

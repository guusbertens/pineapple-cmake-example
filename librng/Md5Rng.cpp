#include "Md5Rng.h"
#include <climits>
#include <cstring>

Md5Rng::Md5Rng()
{
	memset(m_md, 0, MD5_DIGEST_LENGTH);
}

std::pair<double, double> Md5Rng::get_pair()
{
	MD5(m_md, MD5_DIGEST_LENGTH, m_md);
	double x = m_x / (double)ULLONG_MAX;
	double y = m_y / (double)ULLONG_MAX;
	return {x, y};
}

// vim: ts=4 sw=4 cin

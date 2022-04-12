#include "SimpleRng.h"
#include <stdio.h>

std::pair<double, double> SimpleRng::get_pair()
{
	m_x = (74 * m_x + 75) % 127;
	double x = (double)m_x / 126.;
	m_x = (74 * m_x + 75) % 127;
	double y = (double)m_x / 126.;
	return {x, y};
}

// vim: ts=4 sw=4 cin

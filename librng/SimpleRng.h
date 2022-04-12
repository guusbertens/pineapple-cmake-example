#pragma once

#include "Rng.h"

class SimpleRng : public Rng
{
public:
	std::pair<double, double> get_pair();
private:
	unsigned int m_x = 0;
};

// vim: ts=4 sw=4 cin

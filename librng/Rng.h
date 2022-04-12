#pragma once

#include <memory>
#include <string>
#include <utility>

class Rng {
public:
	virtual ~Rng() {};
	virtual std::pair<double, double> get_pair() = 0;
	static std::unique_ptr<Rng> get(const std::string name);
};

// vim: ts=4 sw=4 cin

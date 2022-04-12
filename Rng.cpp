#include "Rng.h"
#include "SimpleRng.h"
#include "Md5Rng.h"

std::unique_ptr<Rng> Rng::get(const std::string name)
{
	if (name == "simple")
		return std::make_unique<SimpleRng>();
	if (name == "md5")
		return std::make_unique<Md5Rng>();
	return NULL;
}

// vim: ts=4 sw=4 cin

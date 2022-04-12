#include "Rng.h"
#include "SimpleRng.h"
#ifdef ENABLE_MD5RNG
#include "Md5Rng.h"
#endif // ENABLE_MD5RNG

std::unique_ptr<Rng> Rng::get(const std::string name)
{
	if (name == "simple")
		return std::make_unique<SimpleRng>();
#ifdef ENABLE_MD5RNG
	if (name == "md5")
		return std::make_unique<Md5Rng>();
#endif // ENABLE_MD5RNG
	return NULL;
}

// vim: ts=4 sw=4 cin

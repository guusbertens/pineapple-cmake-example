#include <err.h>
#include <unistd.h>
#include <string>
#include <memory>
#include <cstring>
#include <climits>
#include <openssl/md5.h>

class Rng {
public:
	virtual ~Rng() {};
	virtual std::pair<double, double> get_pair() = 0;
	static std::unique_ptr<Rng> get(const std::string name);
};

class SimpleRng : public Rng
{
public:
	std::pair<double, double> get_pair();
private:
	unsigned int m_x = 0;
};

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

std::unique_ptr<Rng> Rng::get(const std::string name)
{
	if (name == "simple")
		return std::make_unique<SimpleRng>();
	if (name == "md5")
		return std::make_unique<Md5Rng>();
	return NULL;
}

std::pair<double, double> SimpleRng::get_pair()
{
	m_x = (74 * m_x + 75) % 127;
	double x = (double)m_x / 126.;
	m_x = (74 * m_x + 75) % 127;
	double y = (double)m_x / 126.;
	return {x, y};
}

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

void print_help()
{
	puts("pineapple [-h] [-r {rng}] -n {iterations}");
}

int main(int argc, char **argv)
{
	int opt, i;
	unsigned niter = 0, nhits = 0;
	std::string rngname("simple");

	while ((opt = getopt(argc, argv, "hr:n:")) != -1) {
		switch (opt) {
		case 'r':
			rngname = optarg;
			break;
		case 'n':
			niter = atoi(optarg);
			break;
		case 'h':
			print_help();
			exit(0);
		default:
			exit(1);
		}
	}

	if (!niter)
		errx(1, "no number of iterations given; must be >0");

	auto rng = Rng::get(rngname);
	if (!rng)
		errx(1, "unknown rng '%s'", rngname.c_str());

	printf("Doing %u iterations with the %s rng... ", niter, rngname.c_str());
	for (i=0; i<niter; i++) {
		auto [x, y] = rng->get_pair();
		if (x * x + y * y <= 1)
			nhits += 1;
	}
	printf("done.\n");

	printf("pi ~ %lf\n", 4.0 * nhits / niter);

	return 0;
}

// vim: ts=4 sw=4 cin

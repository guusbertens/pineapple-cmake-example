
#include <err.h>
#include <unistd.h>
#include <string>
#include "Rng.h"

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

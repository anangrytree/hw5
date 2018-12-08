#include <iostream>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <gsl/gsl_rng.h>

using namespace std;

int main(int args, char* argv[]) {
	int opterr = 0;
	int prob = -1;
	bool probSet = false;
	int c;
	while((c = getopt(args, argv, "p:")) != -1) {
		switch(c) {
			case 'p':
				prob = atoi(optarg);
				probSet = true;
				break;
			case '?':
				if(optopt == 'p')
					cerr << "The -p flag requires an argument with it" << "\n";
				else
					cerr << "An invalid argument was specified" << "\n";
				break;
			
		}
	}
	
	if(!probSet) {
		cerr << "Probability attribute must be set" << "\n";
		return 0;
	}

	if(prob < 0 || prob > 100) {
		cerr << "Probability must be between 0 and 100, inclusive" << "\n";
		return 0;
	}

	gsl_rng * _gsl_rng = gsl_rng_alloc(gsl_rng_mt19937);
	srand(time(NULL) ^ getpid());
	gsl_rng_set(_gsl_rng, rand());
	double random = 100 * gsl_rng_uniform(_gsl_rng);

	if(random < prob)
		cout << "Success";
	else
		cout << "Failure";

	gsl_rng_free(_gsl_rng);

	return 0;
}

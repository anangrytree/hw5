#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int args, char* argv[]) {
	int opterr = 0;
	int prob = -1;
	bool probSet = false;
	bool verbose = false;
	int trials = 0;
	int c;
	while((c = getopt(args, argv, "p:v")) != -1) {
		switch(c) {
			case 'p':
				prob = atoi(optarg);
				probSet = true;
				break;
			case 'v':
				verbose = true;
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

	if(argv[optind] == NULL) {
		cerr << "Number of trials must be set";
	} else {
		trials = atoi(argv[optind]);
	}

	for(int i = 0; i < trials; i++) {
		pid_t pid = fork();
		if(pid == 0) {
			// child
			execlp("hand", "hand", "-p" + prob, NULL);
		} else {
			// parent
			pid = wait(NULL);
			if(verbose)
				cout << " " << pid;
		}		
	}

	return 0;
}
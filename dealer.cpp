#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int args, char* argv[]) {
	int opterr = 0;
	int prob;
	char* prob_string;
	bool probSet = false;
	bool verbose = false;
	int trials = 0;
	int c;
	while((c = getopt(args, argv, "p:v")) != -1) {
		switch(c) {
			case 'p':
				prob = atoi(optarg);
				prob_string = optarg;
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

	const char* prob_opt = "-p";
	char* fstring = new char[strlen(prob_string) + 3];
	strcpy(fstring, prob_opt);
	strcat(fstring, prob_string);
	pid_t pid;
	int status;

	int success = 0;

	for(int i = 0; i < trials; i++) {
		pid = fork();
		if(pid == 0) {
			execl("hand", "hand", fstring, NULL);
			exit(0);
		}
		pid_t wpid = wait(&status);
		if(verbose) {
			cout << "PID " << wpid << " returned ";
			if(status == 0)
				cout << "success\n";
			else
				cout << "failure\n";
		}
		if(status == 0)
			success++;
	}

	double successRate = 100 * (success / (double)trials);
	cout << "Success - " << (int)successRate << "%\n";
	cout << "Failure - " << (100 - (int)successRate) << "%\n";
	
	return 0;
}

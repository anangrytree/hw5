#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <cctype>
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
	char* trials_string;
	int c;
	while((c = getopt(args, argv, ":p:v")) != -1) {
		switch(c) {
			case 'p':
				prob_string = optarg;
				probSet = true;
				break;
			case 'v':
				verbose = true;
				break;	
			case '?':
				if(optopt == 'p') {
					cerr << "The -p flag requires an argument with it" << "\n";
					return 0;
				} else {
					cerr << "An invalid argument was specified" << "\n";
					return 0;
				}
				break;
			
		}
	}

	if(argv[optind] == NULL) {
		cerr << "There are one or more issues with your input. Trials must be set as an integer at the end of the command\n";
		return 0;
	} else {
		trials_string = argv[optind];
	}

	if(!probSet) {
		cerr << "There are one or more issues with your input. Probability attribute must be set as an integer with the -p flag preceding it \n";
		return 0;
	}

	for(int i = 0; prob_string[i] != '\0'; i++) {
		if(!isdigit(prob_string[i])) {
			cerr << "There are one or more issues with your input. Probability attribute must be set as an integer with the -p flag preceding it\n";
			return 0;
		}
	}

	for(int i = 0; trials_string[i] != '\0'; i++) {
		if(!isdigit(trials_string[i])) {
			cerr << "There are one or more issues with your input. Trials must be set as an integer at the end of the command\n";
			return 0;
		}
	}

	trials = atoi(trials_string);
	prob = atoi(prob_string);

	if(trials < 0) {
		cerr << "Trials must be a positive integer\n";
		return 0;
	}

	if(prob < 0 || prob > 100) {
		cerr << "Probability must be between 0 and 100, inclusive" << "\n";
		return 0;
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

	double successRate = 10000 * (success / (double)trials);

	cout << "\nCreated " << trials << " processes\n";
	cout << "Success - " << ((int)successRate / 100.0) << "%\n";
	cout << "Failure - " << (100 - (int)successRate / 100.0) << "%\n";
	
	return 0;
}

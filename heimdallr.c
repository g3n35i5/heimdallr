#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "github.h"


void synopsys(char * cmd)
{
        printf("Usage: %s [-u username|-s username|-p port|-h|-V]\n", cmd);
}

void help(void)
{
	char* cmd = "heimdallr";
	synopsys(cmd);
	printf("  %s -u <name> to look up known usernames\n", cmd);
	printf("  %s -s <name> to search for users interactively\n", cmd);
	printf("  %s -p <port> to open a ssh server to scrape keys locally\n", cmd);
	printf("  %s -h to open this help\n", cmd);
	printf("  %s -V to show the version\n", cmd);
	exit(0);
}

int main(int argc, char *argv[]){
	int port = -1;
	if (1 == argc)
		synopsys("heimdallr");
	while ((argc > 1) && ('-' == argv[1][0])){
		switch (argv[1][1])
		{
			case 's':
				find_user(&argv[2][0]);
				break;
			case 'u':
				get_keys(&argv[2][0]);
				break;
			case 'p':
				if ((port = valid_port(&argv[2][0])) < 0) {
					printf("Error: The given port is invalid. Valid ones are between %d and %d.\n", MINPORT, MAXPORT);
					return EXIT_FAILURE;
				}
				printf("Debug: Doing stuff on port %d\n", port);
				break;
			case 'h':
				help();
                                break;
			case 'V':
				printf("Version: %s\n", VERSION);
				break;
			default:
				printf("Error: Unknown parameter.\nTake a look into 'heimdallr -h':\n");
				synopsys("heimdallr");
		}
		++argv;
		--argc;
	}
	return EXIT_SUCCESS;
}

/*
 * copt test/demo
 */

#include <stdio.h>
#include <stdlib.h>

#include "copt.h"


coptOption options[] = {
	{"this is option a", NULL, NULL, 'a', 1, 0, 0},
	{"this is option b, it belongs to mutex group 1", NULL, NULL, 'b', 0, 0, 1},
	{"this is option c, it belongs to mutex group 1", NULL, NULL, 'c', 0, 0, 1},
	{"this is option d", NULL, NULL, 'd', 0, 0, 0},
	{"this is option e, it takes an argument", "e_argument", NULL, 'e', 0, 0, 0},
	{"this is option f, it belongs to mutex group 2", NULL, NULL, 'f', 0, 0, 2},
	{"this is option g, it belongs to mutex group 2", NULL, NULL, 'g', 0, 0, 2},
	{"this is option h, it belongs to mutex group 3", NULL, NULL, 'h', 0, 0, 3}
};

coptMutexGroup mutexGroups[] = {
	{1, 1, 0},
	{2, 0, 0},
	{3, 0, 0}
};

coptEnvironment environment = {
	NULL,
	options,
	8,
	mutexGroups,
	2,
	NULL,
	0,
	1
};


int main(int ac, char **av) {
	int rc = coptParseOpts(&environment, ac, av);
	int i;
	if (rc != COPT_ERR_NONE) {
		printf("error: ");
		switch (rc) {
			case COPT_ERR_MISSING_ARGUMENT:
				printf("a required argument is missing\n");
				break;
			case COPT_ERR_ARGUMENT_OPTION_NOT_LAST:
				printf("an option requiring an argument is not the last in a list\n");
				break;
			case COPT_ERR_UNEXPECTED_CHARACTER:
				printf("unexpected character\n");
				break;
			case COPT_ERR_MUTEX_COLLISION:
				printf("more than one option in a mutually-exclusive group was given\n");
				break;
			case COPT_ERR_UNDOCUMENTED_OPTION:
				printf("unrecognized option\n");
				break;
			case COPT_ERR_MISSING_REQUIRED_OPTION:
				printf("missing a required option\n");
				break;
			case COPT_ERR_MISSING_REQUIRED_MUTEX:
				printf("missing a required option\n");
				break;
		}
		goto term;
	}
	for (i = 0; i < environment.numOptions; i++) {
		if (environment.options[i].found) {
			printf("got option %c\n", environment.options[i].option);
			if (environment.options[i].argumentValue != NULL) {
				printf("\targument: %s\n", environment.options[i].argumentValue);
			}
		}
	}
	if (environment.operands != NULL) {
		printf("got operands:\n");
		for (i = 0; i < environment.numOperands; i++) {
			printf("\t%s\n", environment.operands[i]);
		}
	}
term:
	exit(rc);
}

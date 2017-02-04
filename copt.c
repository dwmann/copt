/*
 * copt.c
 *
 * copt implementation.
 */

#include <stdlib.h>
#include <string.h>
#include <wctype.h>

#include "copt.h"


int coptParseOpts(coptEnvironment *env, int ac, char **av) {
	int i;
	env->progName = av[0];
	for (i = 1; i < ac; i++) {
		/* -- marks start of operands */
		if (av[i][0] == '-' && av[i][1] == '-') {
			if (i == ac - 1) {
				env->operands = NULL;
				env->numOperands = 0;
				return(COPT_ERR_NONE);
			}
			env->operands = (char **)(av + i + 1);
			env->numOperands = ac - i - 1;
			return(COPT_ERR_NONE);
		/* - followed by a letter or digit is an option */
		} else if (av[i][0] == '-' && iswalnum(av[i][1])) {
			char *o = av[i] + 1;
			while (*o) {
				int j;
				/* look for the option in the options array */
				for (j = 0; j < env->numOptions; j++) {
					if (env->options[j].option == *o) {
						env->options[j].found = 1;
						/* check for option in mutex group */
						if (env->options[j].mutexGroup > 0) {
							int k;
							for (k = 0; k < env->numGroups; k++) {
								if (env->mutexGroups[k].mutexGroup == env->options[j].mutexGroup) {
									if (env->mutexGroups[k].found > 0 && env->mutexGroups[k].found != env->options[j].option) {
										return(COPT_ERR_MUTEX_COLLISION);
									}
									env->mutexGroups[k].found = env->options[j].option;
									break;
								}
							}
						}
						/* if we're expecting an argument for this option, get it from the next av string */
						if (env->options[j].argumentName != NULL) {
							if (i + 1 >= ac) {
								return(COPT_ERR_MISSING_ARGUMENT);
							}
							if (strlen(o) > 1) {
								return(COPT_ERR_ARGUMENT_OPTION_NOT_LAST);
							}
							env->options[j].argumentValue = (char *)(av[i+ 1]);
							i++;
						}
						break;
					}
				}
				/* the option was not in the options array-problem */
				if (j == env->numOptions) {
					return(COPT_ERR_UNDOCUMENTED_OPTION);
				}
				o++;
			}
		/* retarded */
		} else {
			return(COPT_ERR_UNEXPECTED_CHARACTER);
		}
	}
	/* make sure all required options were given */
	for (i = 0; i < env->numOptions; i++) {
		if (env->options[i].required == 1 && env->options[i].found == 0) {
			return(COPT_ERR_MISSING_REQUIRED_OPTION);
		}
	}
	/* make sure all required mutex groups were satisfied */
	for (i = 0; i < env->numGroups; i++) {
		if (env->mutexGroups[i].required == 1 && env->mutexGroups[i].found == 0) {
			return(COPT_ERR_MISSING_REQUIRED_MUTEX);
		}
	}
	return(COPT_ERR_NONE);
}

/*
 * copt.h
 *
 * copt global declarations.
 */

#ifndef COPT_H
#define COPT_H


/*
 * DATA TYPES
 */

typedef enum coptErrors {
	/* no error */
	COPT_ERR_NONE, 
	/* an option specified as requiring an argument wasn't given one */
	COPT_ERR_MISSING_ARGUMENT, 
	/* an option accepting an argument must be last in a list: -abc */
	COPT_ERR_ARGUMENT_OPTION_NOT_LAST, 
	/* usually a non-switch character was found */
	COPT_ERR_UNEXPECTED_CHARACTER, 
	/* more than one option within a mutex group was give by the user */
	COPT_ERR_MUTEX_COLLISION, 
	/* an option with no coptOption record was given by the user */
	COPT_ERR_UNDOCUMENTED_OPTION, 
	/* a required option was not given by the user */
	COPT_ERR_MISSING_REQUIRED_OPTION, 
	/* an option in a required mutex group wasn't given by the user */
	COPT_ERR_MISSING_REQUIRED_MUTEX 
} coptErrors;

typedef struct coptOption {
	/* descriptive text for this option */
	char *description; 
	/* descriptive name for the option's argument, NULL for no argument */
	char *argumentName; 
	/* the value given for the option's argument */
	char *argumentValue; 
	/* the option character */
	char option; 
	/* 1 = the option is required, 0 = not required */
	char required; 
	/* 1 if the option is passed in, initialize to 0 */
	char found; 
	/* the mutex group number this option belongs in, 0 = none */
	int mutexGroup; 
} coptOption;

typedef struct coptMutexGroup {
	/* the mutex group number */
	int mutexGroup; 
	/* 1 = an option in this group is required, 0 = not */
	char required; 
	/* the option character from this group that was passed in, or 0 */
	char found; 
} coptMutexGroup;

typedef struct coptEnvironment {
	/* filled in by coptParseOpts with the invocation name */
	char *progName; 
	/* pointer to array of coptOption structures */
	coptOption *options; 
	/* number of options in the coptOption array */
	int numOptions; 
	/* pointer to array of coptMutexGroup structures, or NULL */
	coptMutexGroup *mutexGroups; 
	/* number of mutex groups in the coptMuteGroup array */
	int numGroups; 
	/* operands passed in by user, or NULL, initialize to NULL */
	char **operands; 
	/* number of operands parsed */
	int numOperands; 
	/* 1 = accept operands, 0 = no operands */
	char acceptOperands; 
} coptEnvironment;


/*
 * FUNCTIONS
 */

extern int coptParseOpts(coptEnvironment *env, int ac, char **av);



#endif /* COPT_H */

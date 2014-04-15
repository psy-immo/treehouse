#include "bstrlib/bstrlib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <argp.h>
#include <confuse.h>
#include <cprops/multimap.h>
#include <cprops/trie.h>
#include <assert.h>


#ifndef _TERMTREES_H
#define _TERMTREES_H
#define MAX_OP_INPUTS 0x100

/**
 * structure that stores the signature of an operation
 */

typedef struct {
	int id;
	char *out;
	int in_N;
	char *in[];
} op_signature;

/* returns the key element for op_signatures */ 
void *op_s_key(void *op);

/* compare two op_signatures */
int op_cmp(void *lp, void *rp);

/* copy an op_signature. use free(..) to release */
void* op_dup(void* ptr);


/**
 * a term struct
 */

typedef struct s_term {
	char* result;
	int param_N;
	struct s_term* params[];
} term;

/* alloc a new term struct with N param slots */
term* term_alloc(char* result_sort, int N);





/**
 * the global variable set, packed into a nice struct
 * (this enables having different "global" contexts at once)
 */

typedef struct {

	/* input data */

	cp_trie *sorts;
	int sorts_N;

	int ops_N;
	cp_multimap *ops;

	cp_vector *op_names;

	/* calculations */

	cp_multimap *terms;

	/* output */
	FILE *f;

} globals;

globals* globals_alloc();

void globals_free(globals **p);


int cli_main(int argc, char **argv);

#endif
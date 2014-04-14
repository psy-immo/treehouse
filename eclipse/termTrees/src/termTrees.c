/**
 * termTrees.c, (c) 2014, Immanuel Albrecht; Dresden University of
 * Technology, Professur für die Psychologie des Lernen und Lehrens
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <argp.h>
#include <confuse.h>
#include <cprops/multimap.h>
#include <cprops/trie.h>
#include <assert.h>

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

void *op_s_key(void *op){
	return op;
}

int op_cmp(void *lp, void *rp) {
	op_signature *l =lp;
	op_signature *r =rp;
	int x, i;

	if (l == r)
		return 0;

	if (l->out != r->out)
	{
		x = strcmp(l->out, r->out);
		assert (x); // fails if something is wrong with the sorts trie...
		return x;
	}


	if (l->in_N < r->in_N)
		return -1;

	if (l->in_N > r->in_N)
			return 1;

	for (i=0; i<l->in_N; ++i) {
		if (l->in[i] != r->in[i]) {
			x = strcmp(l->in[i], r->in[i]);
			assert (x); // fails if something is wrong with the sorts trie...
			return x;
		}
	}

	return 0;
}

void* op_dup(void* ptr) {
	op_signature *op =ptr;

	op_signature *cpy = malloc(sizeof(op_signature)+sizeof(char*)*op->in_N);
	memcpy(cpy, op, sizeof(op_signature)+sizeof(char*)*op->in_N);
	return cpy;
}

/**
 * a term struct
 */

typedef struct s_term {
	char* result;
	int param_N;
	struct s_term* params[];
} term;


term* term_alloc(char* result_sort, int N) {
	term *t = malloc(sizeof(term)+sizeof(term*)*N);
	t->result = result_sort;
	t->param_N = N;
	return t;
}


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

globals* globals_alloc() {
	globals *g = malloc(sizeof(globals));
	assert(g);

	g->sorts = cp_trie_create_trie(COLLECTION_MODE_DEEP, 0, free);
	assert(g->sorts);

	g->sorts_N = 0;

	g->ops = cp_multimap_create_by_option(COLLECTION_MODE_DEEP|COLLECTION_MODE_COPY|COLLECTION_MODE_MULTIPLE_VALUES ,
			op_s_key, op_cmp, op_dup, free);
	assert(g->ops);

	g->ops_N = 0;

	g->op_names = cp_vector_create(1); //size in multiples of sizeof(void*)
	assert(g->op_names);

	g->terms = cp_multimap_create_by_option(COLLECTION_MODE_DEEP|COLLECTION_MODE_COPY|COLLECTION_MODE_MULTIPLE_VALUES ,
			op_s_key, op_cmp, op_dup, free); /* TODO: CHANGE TO REFLECT THE TARGET SORT OF THE TERM ONLY */

	g->f = stdout;

	return g;
}

void globals_free(globals **p) {
	globals *g = *p;

	cp_trie_destroy(g->sorts);

	cp_multimap_destroy(g->terms);

	cp_multimap_destroy(g->ops);

	cp_vector_destroy_custom(g->op_names, free);

	free(*p);
	*p = 0;
}

globals *vars;

/**
 * perform computations
 * @param vars   global variables context
 */

void compute(globals *vars) {
	FILE *f = vars->f;

	fprintf(f,"Number of declared sorts: %d (%d)\nNumber of declared ops: %d (%d)\n",vars->sorts_N,
			cp_trie_count(vars->sorts),vars->ops_N,cp_multimap_count(vars->ops));

	fputs("Done.\n",f);
}

int parse_input(char* file, globals* vars) {
	cfg_opt_t operation_opts[] =
		{
		CFG_STR_LIST("in","{}", CFGF_NONE),
	CFG_STR("out", 0, CFGF_NONE),
CFG_END() };

	cfg_opt_t opts[] =
		{ CFG_STR_LIST("sorts", "{}", CFGF_NONE),
	CFG_SEC("op", operation_opts, CFGF_MULTI | CFGF_TITLE),
CFG_FUNC("include", &cfg_include), CFG_END() };

	cfg_t *cfg;

	int i, j, N, err;

	char *found, *sortname, *opname;
	op_signature *ops = malloc(sizeof(op_signature)+sizeof(char*)*MAX_OP_INPUTS);

	assert(ops);

	cfg = cfg_init(opts, CFGF_NONE);

	assert(cfg);

	if (cfg_parse(cfg, file) == CFG_PARSE_ERROR)
		return 1;

	/**
	 * add new sort names to the sorts trie
	 */

	N = cfg_size(cfg, "sorts");

	for (i = 0; i < N; i++)
	{
		sortname = cfg_getnstr(cfg, "sorts", i);
		found = cp_trie_exact_match(vars->sorts, sortname);
		if (!found)
		{
			sortname = strdup(sortname);
			cp_trie_add(vars->sorts, sortname, sortname);
			vars->sorts_N += 1;
		}
	}

	/**
	 * the the operations to the operation list
	 */

	N = cfg_size(cfg, "op");
	for (i = 0; i < N; i++)
	{

		cfg_t *op = cfg_getnsec(cfg, "op", i);
		opname = strdup(cfg_title(op));

		cp_vector_add_element(vars->op_names, opname);


		sortname = cfg_getstr(op,"out");

		assert(sortname);

		found = cp_trie_exact_match(vars->sorts,sortname);
		if (! found) {
			fputs("Operation ",stderr);
			fputs(opname,stderr);
			fputs(" uses undeclared output sort ",stderr);
			fputs(sortname,stderr);
			fputs("\n",stderr);
			/** fix it */
			sortname = strdup(sortname);
			cp_trie_add(vars->sorts, sortname, sortname);
			vars->sorts_N += 1;
			found = sortname;
		}

		ops->id = vars->ops_N;
		ops->out = found;
		ops->in_N = cfg_size(op, "in");

		assert(ops->in_N <= MAX_OP_INPUTS);

		for (j=0;j<ops->in_N; ++j) {
			sortname = cfg_getnstr(op,"in",j);
			assert(sortname);

			found = cp_trie_exact_match(vars->sorts,sortname);
			if (! found) {
				fputs("Operation ",stderr);
				fputs(opname,stderr);
				fputs(" uses undeclared input sort ",stderr);
				fputs(sortname,stderr);
				fputs("\n",stderr);
				/** fix it */
				sortname = strdup(sortname);
				cp_trie_add(vars->sorts, sortname, sortname);
				vars->sorts_N += 1;
				found = sortname;
			}
			ops->in[j] = found;
		}

		err = 0;

		cp_multimap_insert(vars->ops, ops, &err);
		if (err) {
			fputs("Operation ",stderr);
			fputs(opname,stderr);
			fputs(": cannot add to multimap ",stderr);
			fprintf(stderr,"%d",err);
			fputs("\n",stderr);
		}
		vars->ops_N += 1;

	}



	cfg_free(cfg);
	free(ops);
	return 0;
}

int parse_opt(int key, char *arg, struct argp_state *state) {
	switch (key) {
	case 'o':
		printf("Output File\n");
		break;
	case ARGP_KEY_ARG:
		/**
		 * parse input file and add contents to structures
		 */
		parse_input(arg, vars);
		break;
	case ARGP_KEY_END:
		/**
		 * do the calculations
		 */
		compute(vars);

		globals_free(&vars);
		puts("Quit.");

		break;
	}
	return 0;
}

void test();

int main(int argc, char **argv) {
	puts("Build: " __DATE__ " " __TIME__);

	test();

	vars = globals_alloc();

	struct argp_option options[] =
		{
			{ "output", 'o', "FILE", 0, "Write output to file." },
			{ 0 } };

	struct argp argp =
		{ options, parse_opt, };

	return argp_parse(&argp, argc, argv, 0, 0, 0);
}


void test () {
}

#include "termtrees.h"


static globals *vars;

#define DEFAULT_MAX_OPS 128


globals* globals_alloc() {
	globals *g = malloc(sizeof(globals));
	assert(g);

	g->sorts = cp_trie_create_trie(COLLECTION_MODE_DEEP, 0, bcstrfree);
	assert(g->sorts);

	g->sorts_N = 0;

	g->ops = cp_multimap_create_by_option(COLLECTION_MODE_DEEP|COLLECTION_MODE_COPY|COLLECTION_MODE_MULTIPLE_VALUES ,
			op_s_key, op_cmp, op_dup, free);
	assert(g->ops);

	g->ops_N = 0;

	g->op_names = cp_vector_create(1); //size in multiples of sizeof(void*)
	assert(g->op_names);

	g->max_op_count = DEFAULT_MAX_OPS;
	g->show_terms = 0;
	g->show_ops = 0;

	g->f = stdout;
	
	g->bstring_keep = cp_vector_create(1);
	assert(g->bstring_keep);

	return g;
}

void globals_free(globals **p) {
	globals *g = *p;

	cp_trie_destroy(g->sorts);

	cp_multimap_destroy(g->ops);
	
	cp_vector_destroy_custom(g->op_names,bcstrfree);

	cp_vector_destroy_custom(g->bstring_keep, bdestroy);

	free(*p);
	*p = 0;
}


static int parse_input(char* file, globals* vars) {
	cfg_opt_t operation_opts[] =
		{
		CFG_STR_LIST("in","{}", CFGF_NONE),
	CFG_STR("out", 0, CFGF_NONE),
CFG_END() };

	cfg_opt_t opts[] =
		{ CFG_INT("term-depth", DEFAULT_MAX_OPS, CFGF_NONE),
		  CFG_BOOL("show-terms", 0, CFGF_NONE),
		  CFG_BOOL("show-ops", 0, CFGF_NONE),
		CFG_STR_LIST("sorts", "{}", CFGF_NONE),
	CFG_SEC("op", operation_opts, CFGF_MULTI | CFGF_TITLE),
CFG_FUNC("include", &cfg_include), CFG_END() };

	cfg_t *cfg;

	int i, j, N, err;

	bstring bsortname, bopname;

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
			bsortname = bfromcstr(sortname);
			cp_vector_add_element(vars->bstring_keep,bsortname);
			sortname = bstr2cstr(bsortname,' ');
			
			cp_trie_add(vars->sorts, sortname, sortname);
			vars->sorts_N += 1;
		}
	}
	
	vars->max_op_count = cfg_getint(cfg,"term-depth");
	vars->show_terms = cfg_getbool(cfg,"show-terms");
	vars->show_ops = cfg_getbool(cfg,"show-ops");

	/**
	 * the the operations to the operation list
	 */

	N = cfg_size(cfg, "op");
	for (i = 0; i < N; i++)
	{

		cfg_t *op = cfg_getnsec(cfg, "op", i);
		bopname = bfromcstr(cfg_title(op));
		cp_vector_add_element(vars->bstring_keep,bopname);
		opname = bstr2cstr(bopname,' ');
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
			bsortname = bfromcstr(sortname);
			cp_vector_add_element(vars->bstring_keep,bsortname);
			sortname = bstr2cstr(bsortname,' ');
			
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
				bsortname = bfromcstr(sortname);
				cp_vector_add_element(vars->bstring_keep,bsortname);
				sortname = bstr2cstr(bsortname,' ');
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

static int parse_opt(int key, char *arg, struct argp_state *state) {
	switch (key) {
	case 'o':
		printf("Output File\n");
		break;
	case ARGP_KEY_INIT:
		vars = globals_alloc();
		assert(vars);
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

int cli_main(int argc, char **argv) {
	
	struct argp_option options[] =
		{
			{ "output", 'o', "FILE", 0, "Write output to file." },
			{ 0 } };

	struct argp argp =
		{ options, parse_opt, };

	return argp_parse(&argp, argc, argv, 0, 0, 0);
}
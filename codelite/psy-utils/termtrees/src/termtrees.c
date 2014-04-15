#include "termtrees.h"

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
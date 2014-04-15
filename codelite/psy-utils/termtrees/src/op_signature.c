#include "termtrees.h"

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

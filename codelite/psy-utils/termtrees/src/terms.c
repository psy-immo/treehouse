#include "termtrees.h"

term* term_alloc(char* result_sort, int N) {
	term *t = malloc(sizeof(term)+sizeof(term*)*N);
	t->result = result_sort;
	t->param_N = N;
	return t;
}

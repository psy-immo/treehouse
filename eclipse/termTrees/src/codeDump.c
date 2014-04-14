
/**
 * the code dump.
 */

#ifdef __NEVER_DEFINED


typedef struct {
	int const len;
	char* ps[];
} ps_array;

ps_array* ps_alloc(int len) {
	ps_array *psa = calloc(1, sizeof(ps_array) + len * sizeof(char*));
	*((int*) &(psa->len)) = len;
	return psa;
}

ps_array* ps_join(ps_array **l, ps_array **r) {
	ps_array *lr = ps_alloc((*l)->len + (*r)->len);

	memcpy(lr->ps, (*l)->ps, (*l)->len * (sizeof(char*)));
	memcpy(lr->ps + (*l)->len, (*r)->ps, (*r)->len * (sizeof(char*)));

	free(*l);
	free(*r);

	*l = lr;
	*r = 0;
	return *l;
}

void ps_freeall(ps_array *p) {
	int i;

	for (i = 0; i < p->len; ++i)
		if (p->ps[i])
			free(p->ps[i]);
	free(p);
}


#endif

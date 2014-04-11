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
#include "bstrlib/bstrlib.h"

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

typedef struct {
	ps_array *sorts;
} globals;

globals vars;

static int parse_input(char* file, globals* vars) {
	cfg_opt_t opts[] =
		{ CFG_STR_LIST("sorts", "{}", CFGF_NONE),
	CFG_FUNC("include", &cfg_include), CFG_END() };

	cfg_t *cfg;

	int i;

	cfg = cfg_init(opts, CFGF_NONE);

	if (cfg_parse(cfg, file) == CFG_PARSE_ERROR)
		return 1;

	ps_array *sorts = ps_alloc(cfg_size(cfg, "sorts"));

	for (i = 0; i < cfg_size(cfg, "sorts"); i++)
		sorts->ps[i] = strdup(cfg_getnstr(cfg, "sorts", i));

	ps_join(&vars->sorts, &sorts);

	cfg_free(cfg);
	return 0;
}

static int parse_opt(int key, char *arg, struct argp_state *state) {
	switch (key) {
	case 'o':
		printf("Output File\n");
		break;
	case ARGP_KEY_ARG:
		/**
		 * parse input file and add contents to structures
		 */
		parse_input(arg, &vars);
		break;
	case ARGP_KEY_END:
		/**
		 * do the calculations
		 */
		printf("Number of Sorts: %d\n",vars.sorts->len);
		ps_freeall(vars.sorts);
		break;
	}
	return 0;
}

int main(int argc, char **argv) {

	vars.sorts = ps_alloc(0);

	struct argp_option options[] =
		{
			{ "output", 'o', "FILE", 0, "Write output to file." },
			{ 0 } };

	struct argp argp =
		{ options, parse_opt, };

	return argp_parse(&argp, argc, argv, 0, 0, 0);

}

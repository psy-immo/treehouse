/**
 * dihy.c, (c) 2014, Immanuel Albrecht; Dresden University of
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

#include "hygra.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

dihyperedge dihy_alloc(int N_sources){
	dihyperedge e = calloc(1,sizeof(s_dihyperedge)+sizeof(node)*N_sources);
	
	assert(e);
	
	e->sources_N = N_sources;
	return e;
}

dihyperedge dihy_dup(dihyperedge e) {
	dihyperedge f = malloc(sizeof(s_dihyperedge)+sizeof(node)*e->sources_N);
	memcpy(f,e,sizeof(s_dihyperedge)+sizeof(node)*e->sources_N);
	return f;
}

int dihy_cmp(dihyperedge l, dihyperedge r) {
	int i;
	
	if (l==r)
		return 0;
	if (l->target < r->target)
		return -1;
	if (l->target > r->target)
		return 1;
	if (l->sources_N < r->sources_N)
		return -1;
	if (l->sources_N > r->sources_N)
		return 1;
		
	for (i=0;i<l->sources_N;++i)
	{
		if (l->sources[i] < r->sources[i])
			return -1;
		if (l->sources[i] > r->sources[i])
			return 1;
	}
	
	return 0;
}
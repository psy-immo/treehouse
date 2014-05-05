/**
 * bundles.c, (c) 2014, Immanuel Albrecht; Dresden University of
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

bundle bundle_alloc(int N_target_nodes) {
	bundle b = calloc(1,sizeof(s_bundle)+N_target_nodes*sizeof(s_node_count));
	b->arrows_N = N_target_nodes;
	
	return b;
}

int bundle_nf(bundle b) {
	int i,j;
	for (i=0;i<b->arrows_N;++i) {
		for (j=0;j<i;++j) {
			if (b->arrows[j].target == b->arrows[i].target)
				return 0;
		}
	}
	
	return 1;
}

void bundle_normalize(bundle b) {
	int i,j;
	
	/**
	 * first, accumulate the node multiplicities at the first
	 * occurence of each node
	 */
	
	for (i=0;i<b->arrows_N;++i) {
		for (j=0;j<i;++j) {
			if (b->arrows[j].target == b->arrows[i].target)
			{
				b->arrows[j].multiplicity += b->arrows[i].multiplicity;
				b->arrows[i].multiplicity = 0;
				break;			
			}
		}
	}
	
	/**
	 * second, clear out 0-multiplicity nodes
	 */
	 
	j = 0;
	for (i=0;i<b->arrows_N;++i) {
		if (b->arrows[i].multiplicity) {
			b->arrows[j].multiplicity = b->arrows[i].multiplicity;
			b->arrows[j].target = b->arrows[i].target;
			++j;
		}
	}
	 
	 /**
	  * third, adjust arrows_N
	  */
	b->arrows_N = j;
}

int bundle_cmp(bundle l, bundle r) {
	int i,j,N;
	int cmp;
	node target;
	
	if (l->arrows_N < r->arrows_N)
		return -1;
	if (l->arrows_N > r->arrows_N)
		return 1;
		
	N = l->arrows_N;
	
	if (N == 0)
		return 0;
		
	cmp = 0;
	target = l->arrows[0].target;
	i=0;
	
		for (j=0;j<N+1;++j)	 {
			if (j==N)
			{
				cmp = 1;			
				break;
			}
				
			if (r->arrows[j].target == l->arrows[i].target)	{
				if (r->arrows[j].multiplicity < l->arrows[i].multiplicity)
					cmp = 1;
				if (r->arrows[j].multiplicity > l->arrows[i].multiplicity)
					cmp = -1;
				break;
			}
		}
		
	for (i=1;i<N;++i) {
		if ((cmp == 0)||(l->arrows[i].target < target)) {
			for (j=0;j<N+1;++j)	 {
				if (j==N)
				{
					cmp = 1;
					target = l->arrows[i].target;
					break;
				}
					
				if (r->arrows[j].target == l->arrows[i].target)	{
					if (r->arrows[j].multiplicity < l->arrows[i].multiplicity)
					{
						cmp = 1;
						target = l->arrows[i].target;
					}
					if (r->arrows[j].multiplicity > l->arrows[i].multiplicity)
					{
						cmp = -1;
						target = l->arrows[i].target;
					}
					break;
				}
			}
		}
	}
	
	for (j=0;j<N;++j) {
		if ((cmp == 0)||(r->arrows[j].target < target)) {
			for (i=0;i<N+1;++i)	 {
				if (i==N)
				{
					cmp = -1;
					target = r->arrows[j].target;
					break;
				}
					
				if (r->arrows[j].target == l->arrows[i].target)	{
					break;
				}
			}
		}
	}
	
	return cmp;
}

bundle bundle_patf_alloc(partialtermform p) {
	int i;
	bundle b = bundle_alloc(p->input_wires_N);
	
	for (i=0;i<p->input_wires_N;++i) {
		b->arrows[i].multiplicity = 1;
		b->arrows[i].target = p->ops[p->input_wires[i].op]->signature->sources[p->input_wires[i].input];
	}
	
	bundle_normalize(b);
	
	return b;
}
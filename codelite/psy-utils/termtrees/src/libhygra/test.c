/**
 * test.c, (c) 2014, Immanuel Albrecht; Dresden University of
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
#include <assert.h>
#include "hygra.h"
#include "../bstrlib/bstrlib.h"
#include <stdlib.h>
#include <time.h>

void test_dihy() {
	puts("dihy_alloc");
	dihyperedge e = dihy_alloc(4);
	dihyperedge f = dihy_alloc(4);
	dihyperedge g = dihy_alloc(2);
	
	assert(e);
	assert(f);
	assert(g);
	
	puts("dihy_cmp");	
    assert(dihy_cmp(e,f) == 0);
	assert(dihy_cmp(g,g) == 0);
	assert(dihy_cmp(e,g) == 1);
	assert(dihy_cmp(f,g) == 1);
	assert(dihy_cmp(g,f) == -1);
	assert(dihy_cmp(g,e) == -1);
	
	f->target = (node) 1;
	assert(dihy_cmp(g,f) == -1);
	assert(dihy_cmp(f,g) == 1);
	
	e->target = (node) 1;
	f->sources[0] = (node) 1;
	assert(dihy_cmp(e,f) == -1);
	assert(dihy_cmp(f,e) == 1);
	
	puts("dihy_free");	
	dihy_free(e);
	dihy_free(f);
	dihy_free(g);
	
}

void test_patf() {
	int i,j,non_nf;
	
	static char* ids[] = {"a","b","c"};
	
	puts("patfg_alloc");
	
	generators g = patfg_alloc(3);
	assert(g);
	
	for (i=0;i<3;++i) {
		g->ops[i].identifier = ids[i];
		g->ops[i].signature = dihy_alloc(i+1);
		g->ops[i].signature->target = i;
		
		for (j=0;j<i+1;++j)
			g->ops[i].signature->sources[j] = j;
	}
	
	puts("patfb_alloc");
	patf_bucket b = patfb_alloc(g);
	
	assert(b);
	puts("sanity of bucket");
	assert(cp_vector_size(b->terms) == 3);
	assert(((partialtermform)cp_vector_element_at(b->terms,1))->input_wires_N == 2);
	assert(((partialtermform)cp_vector_element_at(b->terms,1))->input_wires[1].op == 0);
	assert(((partialtermform)cp_vector_element_at(b->terms,1))->input_wires[1].input == 1);
	
	
	puts("apply_generators_to_bucket");
	assert(apply_generators_to_bucket(b) == 3+2+1);
	assert(cp_vector_size(b->terms) == 9);
	assert(b->continue_at_index == 3);
	
	puts("apply_generators_to_bucket");
	assert(apply_generators_to_bucket(b) == 12+8+4 - 6);
	assert(b->continue_at_index == 9);
	assert(cp_vector_size(b->terms) == 27);
	
	puts("bucket contents: ");
	for (i=0;i<cp_vector_size(b->terms);++i) {
		printf(" %3d: ",i);
		fput_patf(cp_vector_element_at(b->terms,i),stdout,fputs);
		printf("\n    [= ");
		fput_patf_ordered(cp_vector_element_at(b->terms,i),stdout,fputs);
		if (patf_nf(cp_vector_element_at(b->terms,i)))
			puts("]");
		else 
			puts("] (non-n.f.)");
	}
	
	for (i=2;i<7;++i)
	{
		printf("Iteration %d\n",i+1);
		apply_generators_to_bucket(b);
		
		non_nf = 0;
		for (j=0;j<cp_vector_size(b->terms);++j) {
			if (!patf_nf(cp_vector_element_at(b->terms,j)))
				non_nf += 1;
		}
		printf("   %d/%d = %.2f%% non-n.f.\n",non_nf,cp_vector_size(b->terms),
		    (float)non_nf*100.f/(float)cp_vector_size(b->terms));
	}
	
	
	puts("patfb_free");
	patfb_free(b);
	
	puts("Normal forms only.")
	
	puts("patfb_alloc");
	b = patfb_alloc(g);
	
	
	for (i=0;i<12;++i)
	{
		printf("Iteration %d\n",i+1);
		apply_generators_to_bucket_nf(b);
		
		non_nf = 0;
		for (j=0;j<cp_vector_size(b->terms);++j) {
			if (!patf_nf(cp_vector_element_at(b->terms,j)))
				non_nf += 1;
		}
		printf("   %d/%d = %.2f%% non-n.f.\n",non_nf,cp_vector_size(b->terms),
		    (float)non_nf*100.f/(float)cp_vector_size(b->terms));
	}
	
	puts("patfb_free");
	patfb_free(b);
	
	puts("patfg_deep_free");
	patfg_deep_free(g,0);
}

int main() {
	puts("libhygra test, build: " __DATE__ " " __TIME__);
	
	srand(time(0));
	
	test_dihy();
	test_patf();
	
    return 0;
}

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

void test_math() {
    puts("number_of_m_to_n_surjections(..)");
    
        
    assert(number_of_m_to_n_surjections(2,2) == 2);
    assert(number_of_m_to_n_surjections(3,2) == 6);
    assert(number_of_m_to_n_surjections(4,2) == 14);
    assert(number_of_m_to_n_surjections(5,2) == 30);
    assert(number_of_m_to_n_surjections(6,2) == 62);
    assert(number_of_m_to_n_surjections(7,2) == 126);
    
    assert(number_of_m_to_n_surjections(3,3) == 6);
    assert(number_of_m_to_n_surjections(4,3) == 36);
    assert(number_of_m_to_n_surjections(5,3) == 150);
    assert(number_of_m_to_n_surjections(6,3) == 540);
    assert(number_of_m_to_n_surjections(7,3) == 1806);
    
    assert(number_of_m_to_n_surjections(11,4) == 3498000);
    assert(number_of_m_to_n_surjections(7,6) == 15120);
    assert(number_of_m_to_n_surjections(9,5) == 834120);
    assert(number_of_m_to_n_surjections(8,7) == 141120);
    
}

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
	clock_t begin, end;
	double time_spent;
	static char* ids[] = {"a","b","c"};
	patf_sigma s;
	
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
			
		assert(patf_eform(cp_vector_element_at(b->terms,i)));
		
		
		s = patfs_alloc(cp_vector_element_at(b->terms,i));
		printf(" sigma = [");
		for (j=0;j<s->N;++j)
		{
			if (j)
				printf(", ");
			printf("%d",s->sigma[j]);			
		}
		puts("]");
		
		free(s);
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
	
	puts("Normal forms only. (Speed-test.)");
	
	puts("patfb_alloc");
	b = patfb_alloc(g);
	patf_bucket b2 = patfb_alloc(g);
	
	
	for (i=0;i<8;++i)
	{

		printf("Iteration %d\n",i+1);
		begin = clock();
		apply_generators_to_bucket_nf2(b);
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		
		
		begin = clock();
		apply_generators_to_bucket_nf(b2);
		end = clock();
		
		printf("Time improval 2 vs 1: %f s\n",(double)(end - begin) / CLOCKS_PER_SEC - time_spent);
		printf("Method 2: %f s\n",time_spent);
		
		printf("Method 1 vs 2: %d x %d\n",cp_vector_size(b2->terms),cp_vector_size(b->terms));
		
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
	patfb_free(b2);
	
	puts("patfg_deep_free");
	patfg_deep_free(g,0);
}

void test_bundle() {
	int i;
	
	puts("bundle_alloc");
	bundle b = bundle_alloc(10);
	bundle b2 = bundle_alloc(10);
	bundle b3 = bundle_alloc(10);
	bundle b4 = bundle_alloc(10);
	bundle b5 = bundle_alloc(10);
	
	for (i=0;i<10;++i) {
		b->arrows[i].multiplicity = i+1;
		b->arrows[i].target = (node)(i%3);
		
		b4->arrows[i].multiplicity = i+1;
		b4->arrows[i].target = (node)(i%4);
		
		b2->arrows[i].multiplicity = i+1;
		b2->arrows[i].target = (node)(i%2);
		
		b5->arrows[i].multiplicity = i+1;
		b5->arrows[i].target = (node)((i+1)%2);
		
		if ((i+1)%2) {
			b3->arrows[i].multiplicity = i+2;
		} else {
			b3->arrows[i].multiplicity = i;
		}
		b3->arrows[i].target = (node)((i+1)%2);
	}
	
	assert( ! bundle_nf(b));
	
	puts("bundle_normalize");
	bundle_normalize(b);
	
	assert( bundle_nf(b));
	assert(b->arrows_N == 3);
	assert(b->arrows[0].target == (node)0);
	assert(b->arrows[0].multiplicity == 22);
	assert(b->arrows[1].target == (node)1);
	assert(b->arrows[1].multiplicity == 15);
	assert(b->arrows[2].target == (node)2);
	assert(b->arrows[2].multiplicity == 18);
	
	assert(bundle_cmp(b,b) == 0);
	
	bundle_normalize(b2);
	bundle_normalize(b3);
	bundle_normalize(b4);
    bundle_normalize(b5);
	assert( bundle_nf(b2));
	assert( bundle_nf(b3));
	assert( bundle_nf(b4));
    assert( bundle_nf(b5));
	
	assert(bundle_cmp(b2,b3) == 0);
	assert(bundle_cmp(b3,b2) == 0);
	
	assert(bundle_cmp(b,b2) == 1);
	assert(bundle_cmp(b,b3) == 1);
	
	assert(bundle_cmp(b4,b2) == 1);
	assert(bundle_cmp(b4,b3) == 1);
	
	assert(bundle_cmp(b2,b) == -1);
	assert(bundle_cmp(b3,b) == -1);
	
	assert(bundle_cmp(b2,b4) == -1);
	assert(bundle_cmp(b3,b4) == -1);
	
	assert(bundle_cmp(b,b4) == -1);
	assert(bundle_cmp(b4,b) == 1);
	
	assert(bundle_cmp(b5,b2) == 1);
	assert(bundle_cmp(b3,b5) == -1);
	
	assert(bundle_cmp(b5,b3) == 1);
	assert(bundle_cmp(b2,b5) == -1);
    
    b->arrows_N = 3;
    b2->arrows_N = 3;
    
    b->arrows[0].multiplicity = 1;
    b->arrows[1].multiplicity = 1;
    b->arrows[2].multiplicity = 1;
    
    b->arrows[0].target = 1;
    b->arrows[1].target = 2;
    b->arrows[2].target = 3;
    
    assert(bundle_plug_compatible(b,b));
    
    b2->arrows[0].multiplicity = 2;
    b2->arrows[1].multiplicity = 1;
    b2->arrows[2].multiplicity = 3;
    
    b2->arrows[0].target = 1;
    b2->arrows[1].target = 2;
    b2->arrows[2].target = 3;
    
    assert( ! bundle_plug_compatible(b,b2) );
    assert(bundle_plug_compatible(b2,b));
    
    assert( bundle_number_of_compatible_plug_variants(b2,b) == 1 );
    
    b->arrows[2].multiplicity = 2;
    
    assert( bundle_number_of_compatible_plug_variants(b2,b) == 6 );
    
    b->arrows[0].multiplicity = 2;
    
    assert( bundle_number_of_compatible_plug_variants(b2,b) == 12 );
    
    b->arrows[2].multiplicity = 3;
    
    assert( bundle_number_of_compatible_plug_variants(b2,b) == 12 );
    
	
	puts("bundle_free");
	bundle_free(b);
	bundle_free(b2);
	bundle_free(b3);
	bundle_free(b4);
	bundle_free(b5);
}

int main() {
	puts("libhygra test, build: " __DATE__ " " __TIME__);
	
	srand(time(0));

    test_math();
	
	test_bundle();
	test_dihy();
	test_patf();
	
	
    return 0;
}

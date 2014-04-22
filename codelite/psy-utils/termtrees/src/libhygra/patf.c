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
#include <limits.h>

partialtermform patf_alloc(int num_ops, int num_free_inputs) {
	char *p =  calloc(1, sizeof(s_partialtermform)
	                          +sizeof(operation)*num_ops
							  +sizeof(s_parameter_address)*(num_ops-1 + num_free_inputs));
	assert(p);
	
	partialtermform t = p;
	
	t->ops_N = num_ops;
	t->op_wires_N = num_ops-1;
	t->input_wires_N = num_free_inputs;
	
	t->ops = (p+sizeof(s_partialtermform));
	
	if (num_ops > 1)
		t->op_wires = (p+sizeof(s_partialtermform)+sizeof(operation)*num_ops);
	/* if num_ops==1 we leave it zero, so wrongful usage will segfault earlier instead of
	 * reading/writing the input_wires. */
		
	t->input_wires = (p+sizeof(s_partialtermform)+sizeof(operation)*num_ops
					   +sizeof(s_parameter_address)*(num_ops-1));
	return t;
}

generators patfg_alloc(int num) {
	generators g = calloc(1, sizeof(s_generators)+sizeof(s_operation)*num);
	
	assert(g);
	g->ops_N = num;
	
	return g;
}

/* also frees the dihyperedges of all ops[i], i=0,..,ops_N-1 */
void patfg_deep_free(generators g, cb_free free_identifiers) {
	int i;
	
	for (i=0;i<g->ops_N;++i) {
		dihy_free(g->ops[i].signature);
		if (free_identifiers) 
			free_identifiers(g->ops[i].identifier);
	}
	
	patfg_free(g);
}

patf_bucket patfb_alloc(generators g) {
	int i,j;
	
	patf_bucket b = malloc(sizeof(s_patf_bucket));
	assert(b);
	
	b->terms = cp_vector_create(1);
	b->continue_at_index = 0;
	b->gen = g;
	
	for (i=0;i<g->ops_N;++i) {
		partialtermform t = patf_alloc(1, g->ops[i].signature->sources_N);
		
		t->ops[0] = &g->ops[i];
		for (j=0;j<g->ops[i].signature->sources_N;++j)
		{
			t->input_wires[j].input = j;
			t->input_wires[j].op = 0;
		}
		
		cp_vector_add_element(b->terms,t);
	}
	
	return b;
}

void patfb_free(patf_bucket b) {
	cp_vector_destroy_custom(b->terms, patf_free);
	free(b);
}

static int apply_generators_to_bucket_nfchoice(patf_bucket b, int non_nf) {
	/**
	 * TODO: optimize this to use the correct lower bounds for the choice of the input wire
	 */
	
	int start_index,end_index,i,count,j,k,l;
	node input_sort;
	partialtermform term, g_term;
	
	start_index = b->continue_at_index;
	
	end_index = cp_vector_size(b->terms);
	count = 0;
	
	for (i=start_index;i<end_index;++i) {
		term = cp_vector_element_at(b->terms,i);
		
		for (j=0;j<term->input_wires_N;j++) {
			input_sort = term->ops[term->input_wires[j].op]->signature->sources[term->input_wires[j].input];
			
			for (k=0;k<b->gen->ops_N;++k) {
				if (b->gen->ops[k].signature->target == input_sort) {
					/**
					 * we may plug in the generator gen->ops[k] into the input_wire[j] of term
					 */
					g_term = patf_alloc(term->ops_N+1, term->input_wires_N - 1 
					                                     + b->gen->ops[k].signature->sources_N);
					
					memcpy(g_term->ops,term->ops,sizeof(operation)*term->ops_N);
					g_term->ops[term->ops_N] = &b->gen->ops[k];
					
					if (term->op_wires_N)
						memcpy(g_term->op_wires,term->op_wires,
						                          sizeof(s_parameter_address)*(term->op_wires_N));
												  
					g_term->op_wires[term->op_wires_N].op = term->input_wires[j].op;
					g_term->op_wires[term->op_wires_N].input = term->input_wires[j].input;
					
					memcpy(g_term->input_wires,term->input_wires,
					                              sizeof(s_parameter_address)*j);
					memcpy(&g_term->input_wires[j+b->gen->ops[k].signature->sources_N],
					              &term->input_wires[j+1],
				                  sizeof(s_parameter_address)*(term->input_wires_N-(j+1)));
					
					for (l=0;l<b->gen->ops[k].signature->sources_N;++l) {
						g_term->input_wires[j+l].op = term->ops_N;
						g_term->input_wires[j+l].input = l;
					}
										
					if (non_nf || (patf_nf(g_term))) {
						cp_vector_add_element(b->terms, g_term);
						count += 1;
					} else {
						patf_free(g_term);
					}
					
				}
			}
		}
	}
	
	b->continue_at_index = end_index;
	return count;
}


int apply_generators_to_bucket_nf2(patf_bucket b) {
	/**
	 * This variant is nice if you just want to generate all
	 * normal forms.
	 */
	
	int start_index,end_index,i,count,j,k,l /*,again*/;
	node input_sort;
	partialtermform term, g_term;
	int *lb_input, lb_input_N;
	
	start_index = b->continue_at_index;
	
	end_index = cp_vector_size(b->terms);
	count = 0;
	
	lb_input_N = 1;
	
	for (i=start_index;i<end_index;++i) {
		term = cp_vector_element_at(b->terms,i);
		if (term->ops_N > lb_input_N)
			lb_input_N = term->ops_N;
	}
	
	lb_input = malloc(sizeof(int)*lb_input_N);
	
	for (i=start_index;i<end_index;++i) {
		term = cp_vector_element_at(b->terms,i);
		/**
		 * ASSUMPTION: term is a normal form
		 * 
		 * in order to generate another normal form,
		 * we have to determine the lower bound of
		 * operation and input number, which the newly
		 * added operation must obey.
		 * 
		 */
		 
		memset(lb_input,0,sizeof(int)*term->ops_N);
		 
		for(j=0;j<term->op_wires_N;++j) {
			lb_input[term->op_wires[j].op] = term->op_wires[j].input+1;
		}
		
		//again = 1;
		
//		while(again) {
			//again = 0;
			for(j=0;j<term->op_wires_N;++j) {
				if (term->op_wires[j].input < lb_input[term->op_wires[j].op])
				{
					if (lb_input[j]<INT_MAX) {
						lb_input[j] = INT_MAX;
						//again = 1;
						/*
						 * we don't need to bubble, because the children that are affected
						 * by the updated value come later in n.f. terms
						 */
					}
				}
			}
		 
		//}
		
		
		for (j=0;j<term->input_wires_N;j++) {
			/**
			 * fast forward the inputs refering to op/inputs below
			 * the lower bound.
			 */
	
			 if (term->input_wires[j].input < lb_input[term->input_wires[j].op])
				 continue;
			 /**
			  * lower bound condition holds, from here on, start 
			  * generating new term forms.
			  */
			 break;
		}		
		
		for (;j<term->input_wires_N;j++) {
			
			input_sort = term->ops[term->input_wires[j].op]->signature->sources[term->input_wires[j].input];
			
			for (k=0;k<b->gen->ops_N;++k) {
				if (b->gen->ops[k].signature->target == input_sort) {
					/**
					 * we may plug in the generator gen->ops[k] into the input_wire[j] of term;
					 */					 
					 
					 
					g_term = patf_alloc(term->ops_N+1, term->input_wires_N - 1 
					                                     + b->gen->ops[k].signature->sources_N);
					
					memcpy(g_term->ops,term->ops,sizeof(operation)*term->ops_N);
					g_term->ops[term->ops_N] = &b->gen->ops[k];
					
					if (term->op_wires_N)
						memcpy(g_term->op_wires,term->op_wires,
						                          sizeof(s_parameter_address)*(term->op_wires_N));
												  
					g_term->op_wires[term->op_wires_N].op = term->input_wires[j].op;
					g_term->op_wires[term->op_wires_N].input = term->input_wires[j].input;
					
					memcpy(g_term->input_wires,term->input_wires,
					                              sizeof(s_parameter_address)*j);
					memcpy(&g_term->input_wires[j+b->gen->ops[k].signature->sources_N],
					              &term->input_wires[j+1],
				                  sizeof(s_parameter_address)*(term->input_wires_N-(j+1)));
					
					for (l=0;l<b->gen->ops[k].signature->sources_N;++l) {
						g_term->input_wires[j+l].op = term->ops_N;
						g_term->input_wires[j+l].input = l;
					}
					
				/*	if (!patf_nf(g_term)) {
						fput_patf_ordered(g_term,stdout,fputs);
						puts("Origin:");
						fput_patf_ordered(term,stdout,fputs);
						printf("Input: %d . %d\n",term->input_wires[j].op,term->input_wires[j].input);
						printf("L.B.: %d\n",lb_input[term->input_wires[j].op]);
					} */
										
					cp_vector_add_element(b->terms, g_term);
					count += 1;					
				}
			}
		}
	}
	
	b->continue_at_index = end_index;
	
	free(lb_input);
	
	return count;
}



int apply_generators_to_bucket_nf(patf_bucket b) {
	return apply_generators_to_bucket_nfchoice(b,0);
}

int apply_generators_to_bucket(patf_bucket b) {
	return apply_generators_to_bucket_nfchoice(b,1);
}

static void fput_patf_op(partialtermform t, FILE* stream, cb_fput_id fput_id, int op) {
	int i,j,free_input;
	
	fput_id(t->ops[op]->identifier, stream);
	fputs("(",stream);

	for (i=0;i<t->ops[op]->signature->sources_N;++i) {
		if (i>0)
			fputs(", ",stream);
			
		free_input = 1;
		for (j=op;j<t->op_wires_N;++j) {
			if ((t->op_wires[j].op == op) && (t->op_wires[j].input == i)) {
				fput_patf_op(t,stream,fput_id,j+1);
				free_input = 0;
				break;
			}
		}
		
		if (free_input)
			fputs(".",stream);
		
	}
	
	fputs(")",stream);
}

void fput_patf(partialtermform t, FILE* stream, cb_fput_id fput_id) {
	
	fput_patf_op(t,stream,fput_id,0);
}

static void fput_patf_op_ordered(partialtermform t, FILE* stream, cb_fput_id fput_id, int op) {
	int i,j,free_input;
	
	fput_id(t->ops[op]->identifier, stream);
	fprintf(stream,"%d",op);
	fputs("(",stream);

	for (i=0;i<t->ops[op]->signature->sources_N;++i) {
		if (i>0)
			fputs(", ",stream);
			
		free_input = 1;
		for (j=op;j<t->op_wires_N;++j) {
			if ((t->op_wires[j].op == op) && (t->op_wires[j].input == i)) {
				fput_patf_op_ordered(t,stream,fput_id,j+1);
				free_input = 0;
				break;
			}
		}
		
		if (free_input)
			fputs(".",stream);
		
	}
	
	fputs(")",stream);
}

void fput_patf_ordered(partialtermform t, FILE* stream, cb_fput_id fput_id) {
	
	fput_patf_op_ordered(t,stream,fput_id,0);
}

static int patf_nf_op(partialtermform t, int op) {
	int i,j,lower_bound,nb;
	
	/**
	 * 
	 * The main characteristic of a normal form partialtermform
	 * is that the order of appearance for the operations in
	 * t->ops is the order of appearance of the operations when
	 * read as a written term.
	 * 
	 * This implies a lower bound proprety: The highest op number
	 * that is used as part of a subterm of this operation has to
	 * be smaller than any subsequently used op number and thus
	 * is a lower bound.
	 * 
	 */
	
	lower_bound = op;
	
	for (i=0;i<t->ops[op]->signature->sources_N;++i) {
		
		for (j=op;j<t->op_wires_N;++j) {
			if ((t->op_wires[j].op == op) && (t->op_wires[j].input == i)) {
				if (j+1 < lower_bound)
					return -1;
					
				nb = patf_nf_op(t,j+1);
				if (nb < 0)
					return -1;
					
				if (nb > lower_bound)
					lower_bound = nb;
					
			}
		}		
	}
	
	return lower_bound;	
}

int patf_nf(partialtermform t) {
	return patf_nf_op(t,0) >= 0;
}
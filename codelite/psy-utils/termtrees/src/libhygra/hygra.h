/**
 * hygra.h, (c) 2014, Immanuel Albrecht; Dresden University of
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

/**
 * This library uses libcprops-0.1.12
 */

#include <cprops/heap.h>
#include <cprops/util.h>
#include <cprops/hashtable.h>
#include <cprops/vector.h>
#include <cprops/multimap.h> 
#include <stdlib.h>
#include <stdio.h>

/*
 * LIBrary for HYperGRAph related stuff :)
 */
 
#ifndef __LIBHYGRA_H
#define __LIBHYGRA_H


 
 
/**
 * DIrected HYpergraph edges
 */
 
typedef void *node;
 
typedef struct t_dihyperedge {
	node target;
	int sources_N;
	node sources[];
	
 } s_dihyperedge;
 
typedef s_dihyperedge* dihyperedge;
 
dihyperedge dihy_alloc(int N_sources);
#define dihy_free free

dihyperedge dihy_dup(dihyperedge e);
  
int dihy_cmp(dihyperedge l, dihyperedge r); 


/**
 * PArtial Term Form
 */
  
typedef struct t_operation {
	 dihyperedge signature;
	 void *identifier;
} s_operation;
 
typedef s_operation* operation;
 
typedef struct t_parameter_address {
	 int op;
	 int input;
} s_parameter_address;
 
typedef struct t_partialtermform {
	int ops_N; // >0
	int input_wires_N;
	int op_wires_N; // = ops_N-1
	/*
	 * The first operation is always considered the output,
	 * all other operations are wired as inputs of other operations
	 */
	operation *ops;
	s_parameter_address *op_wires;
	/*
	 * Keep track of where the inputs are wired to
	 */
	s_parameter_address *input_wires;
	
} s_partialtermform;

typedef s_partialtermform* partialtermform;

typedef struct t_generators {
	 int ops_N;
	 s_operation ops[];
} s_generators;

typedef s_generators *generators;

typedef struct t_patf_bucket {
	generators gen;
	/* the set of newly generated terms starts here */
	int continue_at_index;
	/*vector of partialtermform */
	cp_vector *terms;	
} s_patf_bucket;

typedef s_patf_bucket *patf_bucket;

typedef void (*cb_free)(void* p);

typedef struct t_patf_sigma {
	int N;
	int sigma[];	
} s_patf_sigma;

typedef s_patf_sigma *patf_sigma;

patf_sigma patfs_alloc(partialtermform t);
#define patfs_free free


generators patfg_alloc(int num);
#define patfg_free free

/* also frees the dihyperedges of all ops[i], i=0,..,ops_N-1, and optionally the indentifiers */
void patfg_deep_free(generators g, cb_free free_individuals);

patf_bucket patfb_alloc(generators g);
void patfb_free(patf_bucket b);

partialtermform patf_alloc(int num_ops, int num_free_inputs);
#define patf_free free

/**
 * tries to plug in every generator in every (new) partial term forms input, in order to generate
 * all possible partial terms and calculation orders
 * (you might partially evaluate the expression by first partially evaluating the last element of
 *  the ops array, then the second last, and so on. For instance, if b: X,X->X and a: X-> X,
 *  you get two partialtermforms for b(a(.), b(., .)), which may be distinguished by appending
 *  the order of partial term generation:
 *      b0(a1(.), b2(., .))   and   b0(a2(.), b1(., .))
 */
int apply_generators_to_bucket(patf_bucket b); // returns: number of new partial term forms
/**
 * same as above, but only keep normal forms
 */
int apply_generators_to_bucket_nf(patf_bucket b); // returns: number of new partial term forms
/**
 * this variant will generate only normal forms under the additional assumption that
 * the patf_bucket b only contains normal forms.
 */
int apply_generators_to_bucket_nf2(patf_bucket b); // returns: number of new partial term forms


typedef int cb_fput_node(node s, FILE *stream);
typedef int cb_fput_id(node s, FILE *stream);

void fput_patf(partialtermform t, FILE *stream, cb_fput_id fput_id);
void fput_patf_ordered(partialtermform t, FILE *stream, cb_fput_id fput_id);


/*
 * tests, whether the given partialtermform is in operation order normal form
 */
int patf_nf(partialtermform t);

/*
 * tests, whether the given partialtermform is in evaluation order form, i.e.
 * that the output of an operation may only be used as an input of an earlier
 * operation.
 * 
 * THIS SHOULD RETURN 1 FOR ALL partialtermforms USED WITH THIS LIBRARY.
 */
int patf_eform(partialtermform t);

/**
 * fills the int[t->ops_N] array sigma with the operation numbers ordered such
 * that the partialtermform where t_sigma->ops[i] = t->ops[sigma[i]] (other
 * members altered accordingly) is in normal form.
 */
void patf_get_sigma(int* sigma, partialtermform t);

/**
 * 
 * BUNDLEs -- structure that represents a multiset of nodes
 *        which may be interpreted either as a target or
 *        source of a quiver of arrows 
 */


/**
 * represents a bundle of arrows with a common target
 */
typedef struct t_node_count {
	node target;
	int multiplicity;
} s_node_count;

/**
 * represents a bunde of arrows with a common (abstract) source
 * 
 */
typedef struct t_bundle {
	int arrows_N;
	s_node_count arrows[];
} s_bundle;

typedef s_bundle *bundle;

bundle bundle_alloc(int N_target_nodes);
/**
 * allocates a new bundle that corresponds to the input nodes
 * of the partial term form p
 */
bundle bundle_patf_alloc(partialtermform p);
#define bundle_free free

/**
 * test whether a bundle is in normal form, i.e.
 * whether every arrrows[i] points has a
 * different target node
 */
int bundle_nf(bundle b);

/**
 * turns any given bundle into its normal form
 */
void bundle_normalize(bundle b);


/**
 * compare two bundles which are in normal form
 */
int bundle_cmp(bundle l, bundle g);

 
 
#endif
#include "termtrees.h"


typedef struct t_add_ops_callback_data {
	
	globals *vars;
	int nbr;
	
} s_add_ops_callback_data;

static int add_ops_callback_fn(void *entry, void *client_prm) {
	s_add_ops_callback_data *d = client_prm;
	
	cp_index_map_node *n = entry;
	cp_vector *v = n->entry;
	int N,i,j;
	op_signature *op;
	dihyperedge signature;
	
	N = cp_vector_size(v);
	
	for (i=0;i<N;++i) {
		op = cp_vector_element_at(v,i);
		signature = dihy_alloc(op->in_N);
		
		signature->target = op->out;
		for (j=0;j<op->in_N;++j) {
			signature->sources[j] = op->in[j];
		}
		
		d->vars->g->ops[d->nbr].identifier = op->id;
		d->vars->g->ops[d->nbr].signature = signature;
		
		d->nbr ++;
	}
	
	
	return 0;
}


static int fputi(int i, FILE* f) {
	fprintf(f,"µ%d",i);
}

/**
 * perform computations
 * @param vars   global variables context
 */

void compute(globals *vars) {
	s_add_ops_callback_data add_data;
	FILE *f = vars->f;
	int i,N,j;
	
	add_data.vars = vars;

	fprintf(f,"Number of declared sorts: %d (%d)\n"
	          "Number of declared ops: %d (%d)\n"
			  "Max. op count: %d\n"
			  "Number of declared tasks: %d\n",vars->sorts_N,
			          cp_trie_count(vars->sorts),
					  vars->ops_N,
					  cp_multimap_count(vars->ops),
					  vars->max_op_count,
					  cp_vector_size(vars->tasks));
		
			
	/**
	 * create intermediate structures
	 */

	 vars->g = patfg_alloc(cp_multimap_count(vars->ops));
	 
	 add_data.nbr = 0;
	 
	 cp_multimap_callback(vars->ops, add_ops_callback_fn, &add_data);
	
	 if (vars->show_ops) {
		 fprintf(f,"Declared operations\n");
		 N = cp_vector_size(vars->op_names);
		 for (i=0;i<N;++i)
		 {
			fprintf(f," µ%d ",i);
			
			fputs(cp_vector_element_at(vars->op_names,i),f);
			
			fputs("\n",f);
		 }
			 
			 
	 }
	 
	 if (vars->show_tasks) {
		 fprintf(f,"Declared tasks\n");
		 N = cp_vector_size(vars->tasks);
		 
		 for (i=0;i<N;++i) {
			
		    fprintf(f," T%d ",i);
			
			task_scheme *task = cp_vector_element_at(vars->tasks,i);
			
			fputs( task->name,f);
			fputs("\n",f);
			for (j=0;j<task->data_N;++j) {
				fputs("    '",f);
				fputs(task->data[j],f);
				fputs("'\n",f);
			}
			
			fputs("         --> ",f);
			fputs("'",f);
			fputs(task->goal,f);
			fputs("'",f);
			fputs("\n",f);
		 }
	 }
	 
	 vars->b = patfb_alloc(vars->g);
	 
	 for (i=0;i<vars->max_op_count;++i)
		 apply_generators_to_bucket_nf2(vars->b);
		 
		 
	 N = cp_vector_size(vars->b->terms);
	 fprintf(f,"Terms in n.f.: %d\n",N);
	 
	 if (vars->show_terms) {
		 fprintf(f,"Derived partial term forms\n");
		 for (i=0;i<N;++i)
		 {
			 partialtermform t = cp_vector_element_at(vars->b->terms,i);
			 
			 fprintf(f," %4d ",i);
			 fput_patf(t,f,fputi);
			 fprintf(f,"\n         : ");
			 
			 for (j=0;j<t->input_wires_N;++j) {
				 if (j!=0)
					 fputs(",\n           ",f);
				 fputs("'",f);
				 fputs(t->ops[t->input_wires[j].op]->signature->sources[t->input_wires[j].input],f);
				 fputs("'",f);
			 }
			 
			 fputs("\n         --> ",f);
			 fputs("'",f);
			 fputs(t->ops[0]->signature->target,f);
			 fputs("'",f);
			 
			 fprintf(f,"\n");
		 }
		 
	 }
	 
	 
	 /**
	  * kill intermediate structures 
	  */
	  
	  for (i=0;i<add_data.nbr;++i) {
		  patfs_free(vars->g->ops[i].signature);
	  }
	  patfb_free(vars->b);
	  patfg_free(vars->g);

	fputs("Done.\n",f);
}
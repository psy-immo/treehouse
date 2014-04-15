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

/*
 * LIBrary for HYperGRAph related stuff :)
 */
 
#ifndef __LIBHYGRA_H
#define __LIBHYGRA_H
 
 
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
 
 
#endif
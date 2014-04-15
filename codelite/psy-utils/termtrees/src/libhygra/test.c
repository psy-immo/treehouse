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

int main() {
	puts("libhygra test, build: " __DATE__ " " __TIME__);
	
	test_dihy();
	
    return 0;
}

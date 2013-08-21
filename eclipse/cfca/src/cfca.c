/**
 * cfca.c, (c) 2013, Immanuel Albrecht; Dresden University of
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
#include <stdlib.h>
#include <time.h>

#include "fca.h"
#include "fca_private.h"
#include "fca_macros.h"

/**
 * this is the main testing routine for purposes of testing the formal concept analysis
 * implementation for errors
 *
 * @return
 */

int main(void)
{
//	uint64_t test[2];
//	for (int i = 0; i < 65; ++i) {
//		test[0] = ~0ULL;
//
//		test[1] = ~0ULL;
//		MASKVECTOR(test,i+1);
//		printf("%2d: %16llx %16llx %16llx%16llx\n",BITNBR(i),BITVALUE(i),CRIMPVALUE(i),test[0]);
//	}

	/**
	 * initialize pseudo random number generator
	 */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

	srandom(time(0));

#pragma GCC diagnostic pop

	/**
	 * start tests
	 */

	FormalContext ctx;

	ctx = newFormalContextFromRandom(80, 30, 0.3f);

	writeFormalContext(ctx, "/home/immo/tmp/test.cxt");

	puts("Cloning V...");

	FormalContextV ctxV;

	ctxV = newFormalContextFromFileV("/home/immo/tmp/test.cxt");

	writeFormalContextV(ctxV, "/home/immo/tmp/testV.cxt");

	puts("Performance testing....");

	clock_t start, end;
	time_t xstart, xend;

	FormalConceptIntentBulkListV conceptsV;

	time(&xstart);
	start = clock();

	conceptsV = newConceptBulkFromContextV(ctxV);

	end = clock();
	time(&xend);

	printf("Concepts: %zu\n", countConceptsInBulkV(conceptsV));

	printf("Time version V: %f sec in %f [%d-%d]\n",
			(float) (end - start) / CLOCKS_PER_SEC,
			(float) difftime(xend, xstart), start, end);

	FormalConceptIntentBulkListV conceptsVX;

	time(&xstart);
	start = clock();

	conceptsVX = nextClosureVX(ctxV);

	end = clock();
	time(&xend);

	printf("Concepts: %zu\n", countConceptsInBulkV(conceptsV));

	printf("Time version VX: %f sec in %f [%d-%d]\n",
			(float) (end - start) / CLOCKS_PER_SEC,
			(float) difftime(xend, xstart), start, end);

	FormalConceptIntentBulkList concepts;

	time(&xstart);
	start = clock();

	concepts = newConceptBulkFromContext(ctx);

	end = clock();
	time(&xend);

	printf("Concepts: %d\n", countConceptsInBulk(concepts));

	printf("Time version 1: %f sec in %f [%d-%d]\n",
			(float) (end - start) / CLOCKS_PER_SEC,
			(float) difftime(xend, xstart), start, end);

	writeConceptsToFile(ctx, concepts, "/home/immo/tmp/test1.cxt");
	writeConceptsToFileV(ctxV, conceptsV, "/home/immo/tmp/testV.cxt");
	writeConceptsToFileV(ctxV, conceptsVX, "/home/immo/tmp/testVX.cxt");

	/*puts("=====");
	 FILE* status = fopen("/proc/self/status", "r");
	 char line[1000];
	 while (fgets(line, sizeof line, status) != NULL)
	 {
	 printf("%s", line);
	 }
	 fclose(status);
	 puts("=====");*/

	puts("Clean up...");

	deleteConceptBulkV(&conceptsVX);
	deleteConceptBulkV(&conceptsV);
	deleteConceptBulk(&concepts);
	deleteFormalContext(&ctx);
	deleteFormalContextV(&ctxV);

	return EXIT_SUCCESS;
}

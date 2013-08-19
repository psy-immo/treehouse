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

	ctx = newFormalContextFromRandom(40,40,0.3f);

	writeFormalContext(ctx,"/home/immo/tmp/test.cxt");

	puts("Cloning V...");

	FormalContextV ctxV;

	ctxV = newFormalContextFromFileV("/home/immo/tmp/test.cxt");

	writeFormalContextV(ctxV,"/home/immo/tmp/testV.cxt");

	puts("Performance testing....");

	clock_t start, end;


	start = clock();
	printf("Concepts: %d\n", countContextConceptsV(ctxV));
	end = clock();
    printf("Time version V1: %d [%d-%d]\n", end-start,start,end);


	start = clock();
	printf("Concepts: %d\n", countContextConcepts(ctx));
	end = clock();
    printf("Time version 1: %d [%d-%d]\n", end-start,start,end);



    start = clock();
   	printf("Concepts: %d\n", countContextConcepts2(ctx));
   	end = clock();
    printf("Time version 2: %d [%d-%d]\n", end-start,start,end);


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

	deleteFormalContext(&ctx);
	deleteFormalContextV(&ctxV);


	return EXIT_SUCCESS;
}

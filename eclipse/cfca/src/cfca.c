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

#include "fca.h"
#include "fca_private.h"

int main(void)
{

	FormalContext ctx;

	ctx = newFormalContextFromFile("/home/immo/tmp/test.cxt");



	puts("Internal testing....");

	FormalConceptIntentBulkList l;
	l = newConceptBulkFromContext(ctx);

	printf("Concepts: %d =? 209\n",countConceptsInBulk(l));


	puts("=====");
	FILE* status = fopen("/proc/self/status", "r");
	char line[1000];
	while (fgets(line, sizeof line, status) != NULL)
	{
		printf("%s", line);
	}
	fclose(status);
	puts("=====");

	deleteFormalContext(&ctx);

	deleteConceptBulk(&l);

	return EXIT_SUCCESS;
}

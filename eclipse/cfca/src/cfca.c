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

#include "fca/fca.h"
#include "fca/easy/private.h"
#include "fca/vector/private.h"

/**
 * this is the main testing routine for purposes of testing the formal concept analysis
 * implementation for errors
 *
 * @return
 */

int main(void)
{
	puts("Go!");
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
	ctx = newFormalContextFromRandom(15, 30, 0.3f);

	writeFormalContext(ctx, "/home/immo/tmp/test.cxt");

	EtaFunction eta;
	eta = newUniformEtaFunction(2, 30);
	eta->C[0] = 0.05; //Type I error
	eta->C[1] = 0.10; //Type II error

	LogCache logC;
	logC = newLogCache(eta->constants);
	calculateLogs(eta,logC);


	FormalContext B;
	B = newFakeMeasurement(ctx,eta,150);
	writeFormalContext(B, "/home/immo/tmp/test_B.cxt");

	ConditionMap c;
	c = newConditionMap(150);


	deleteLogCache(&logC);
	deleteEtaFunction(&eta);
	deleteFormalContext(&B);
	deleteFormalContext(&ctx);

	puts("done.");
	return EXIT_SUCCESS;
}

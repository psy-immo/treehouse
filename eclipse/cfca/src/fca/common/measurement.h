/**
 * measurement.h, (c) 2013, Immanuel Albrecht; Dresden University of
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

#ifndef FCA__MEASUREMENT_H_
#define FCA__MEASUREMENT_H_

#include <stdlib.h>

/**
 * type for probabilities
 */

typedef double Probability;

/**
 * this structure contains information on how many cases for measurements there are,
 * and what the probabilities of erroneous measurement there is for each case
 */
typedef struct sEtaFunction {
	/**
	 * the number of different probability constants
	 */
	size_t constants;

	/**
	 * the constants array.
	 */

	Probability *C;

	/**
	 * the number of error types
	 */
	size_t types;

	/**
	 * the number of different measurements
	 */

	size_t measurements;

	/**
	 * the error constants, where the rows (t) are types,
	 * and the columns (m) are measurements, i.e.
	 * the error probability for type t error and measurement m is:
	 *
	 * C[eta[t*measurements + m]]
	 */
	size_t * eta;
} *EtaFunction;

EtaFunction
newEtaFunction(size_t types, size_t measurements, size_t constants);

EtaFunction
newUniformEtaFunction(size_t types, size_t measurements);

EtaFunction
newGeneralEtaFunction(size_t types, size_t measurements);

void
deleteEtaFunction(EtaFunction* eta);


#endif /* MEASUREMENT_H_ */

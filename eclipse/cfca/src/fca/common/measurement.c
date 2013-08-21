/**
 * measurement.c, (c) 2013, Immanuel Albrecht; Dresden University of
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

#include "../common.h"

/** @file
 *  This file contains implementations regarding measurement error probabilities
 *  related structures operations
 */

/**
 * creates a new EtaFunction
 *
 * @param types  number of types, usually 2
 * @param measurements  number of different measurements,
 * @param constants  number of different error constants,
 * <= types*measurements are needed.
 * @return  a new structure
 */

EtaFunction newEtaFunction(size_t types, size_t measurements, size_t constants)
{
	RETURN_ZERO_IF_ZEROI(types);
	RETURN_ZERO_IF_ZEROI(measurements);
	RETURN_ZERO_IF_ZEROI(constants);

	EtaFunction e;
	e = malloc(sizeof(struct sEtaFunction));

	e->types = types;
	e->measurements = measurements;
	e->constants = constants;

	e->C = calloc(constants, sizeof(Probability));
	e->eta = calloc(types * measurements, sizeof(size_t));

	return e;
}

/**
 *   deletes an EtaFunction and sets the pointer to zero
 * @param eta
 */

void deleteEtaFunction(EtaFunction* eta)
{
	RETURN_IF_ZERO(eta);
	RETURN_IF_ZERO(*eta);

	free((*eta)->C);
	free((*eta)->eta);
	free(*eta);

	*eta = 0;
}

/**
 * create a new EtaFunction with the same constant for each type
 *
 * @param types
 * @param measurements
 * @return
 */
EtaFunction newUniformEtaFunction(size_t types, size_t measurements)
{
	EtaFunction e;
	e = newEtaFunction(types, measurements, types);

	for (size_t t = 0; t < types; ++t)
	{
		for (size_t m = 0; m < measurements; ++m)
		{
			e->eta[t * measurements + m] = t;
		}
	}

	return e;
}

/**
 * create a new EtaFunction with the a constant for each type and measurement on its own
 *
 * @param types
 * @param measurements
 * @return
 */
EtaFunction newGeneralEtaFunction(size_t types, size_t measurements)
{
	EtaFunction e;
	e = newEtaFunction(types, measurements, types * measurements);

	for (size_t t = 0; t < types; ++t)
	{
		for (size_t m = 0; m < measurements; ++m)
		{
			e->eta[t * measurements + m] = t * measurements + m;
		}
	}

	return e;
}

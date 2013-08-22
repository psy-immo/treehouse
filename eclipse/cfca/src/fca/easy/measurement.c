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

#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "private.h"

/**
 * calculates the likelihood function L
 * @param B   the measurement context
 * @param c   the condition map (mapping objects
 * @param I
 * @param eta
 * @param L
 */

void calculateLikelihood(const FormalContext B, const ConditionMap c,
		const FormalContext I, const EtaFunction eta, CommutativeProduct L)
{
	RETURN_IF_ZERO(B);
	RETURN_IF_ZERO(c);
	RETURN_IF_ZERO(I);
	RETURN_IF_ZERO(eta);
	RETURN_IF_ZERO(L);

	const myFormalContext* restrict b;
	b = (const myFormalContext*) B;

	const myFormalContext* restrict i;
	i = (const myFormalContext*) I;

	WARN_IF_UNEQUAL_DO(b->objects, (int )c->objects, return);
	WARN_IF_UNEQUAL_DO(b->attributes, i->attributes, return);
	WARN_IF_UNEQUAL_DO(i->attributes, (int ) eta->measurements, return);
	WARN_IF_UNEQUAL_DO(2, eta->types, return);
	WARN_IF_UNEQUAL_DO(eta->constants, L->constants,);

	memset(L->match, 0, sizeof(size_t) * L->constants);
	memset(L->mismatch, 0, sizeof(size_t) * L->constants);

	for (int g = 0; g < b->objects; ++g)
	{
		int c_g;
		c_g = (int) c->c[g];

		WARN_IF_GEQ_DO(c_g, i->objects, continue);

		for (int m = 0; m < b->attributes; ++m)
		{
			if (gIm(c_g,i,m))
			{
				if (gIm(g,b,m))
				{
					L->match[eta->eta[b->attributes + m]]++;
				}
				else
				{
					L->mismatch[eta->eta[b->attributes + m]]++;
				}
			}
			else
			{
				if (gIm(g,b,m))
				{
					L->mismatch[eta->eta[m]]++;
				}
				else
				{
					L->match[eta->eta[m]]++;
				}
			}
		}
	}
}

/**
 * generates a new formal context that comprises of a pseudo-random fake
 * measurement obtained from I with the given error probabilites and experiment count
 *
 * @param I            experimental condition context
 * @param eta          error probabilities
 * @param experiments  number of conducted experiments
 * @return  a new FormalContext object
 */
FormalContext newFakeMeasurement(const FormalContext I, const EtaFunction eta,
		int experiments)
{
	RETURN_ZERO_IF_ZERO(I);
	RETURN_ZERO_IF_ZERO(eta);

	const myFormalContext* restrict i;
	i = (const myFormalContext*) I;

	WARN_IF_UNEQUAL_DO(i->attributes, (int ) eta->measurements, return 0);

	myFormalContext *b;
	b = (myFormalContext *) newFormalContext(experiments, i->attributes);

	for (int x = 0; x < experiments; ++x)
	{
		int c_x;
		c_x =
				MIN((int) floor((double) (random()) /
								(double) RAND_MAX * (double)i->objects), i->objects-1);


		for (int m = 0; m < i->attributes; ++m)
		{
			Probability rnd;
			rnd = (Probability) random() / (Probability) RAND_MAX;

			if (gIm(c_x,i,m))
			{
				if (rnd >= eta->C[eta->eta[i->attributes + m]])
					CROSS(CELL(x,b,m));
			}
			else
			{
				if (rnd < eta->C[eta->eta[m]])
					CROSS(CELL(x,b,m));
			}
		}
		puts("\n");
	}

	return (FormalContext) b;
}


/**
 * fca_private.h, (c) 2013, Immanuel Albrecht; Dresden University of
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
 * @file
 *
 * this file contains forward declarations for fca related functions that are not
 * part of the public interface
 */

#ifndef FCA_PRIVATE_H_
#define FCA_PRIVATE_H_

#include "fca_structs.h"

myFormalConceptIntentChunk*
newConceptChunk(int attributes);

void
deleteConceptChunk(myFormalConceptIntentChunk** c);

FormalConceptIntentBulkList
newConceptBulk(int attributes);

FormalConceptIntentBulkList
newConceptBulkFromContext(FormalContext ctx);

void
writeConceptsToFile(FormalContext ctx, FormalConceptIntentBulkList root,
		const char* filename);

void
deleteConceptBulk(FormalConceptIntentBulkList* rootNode);

int
countConceptsInBulk(FormalConceptIntentBulkList root);

FormalConceptIntentBulkList
addConceptToBulk(FormalConceptIntentBulkList root, const IncidenceCell* intent);

void
closeIntent(FormalContext ctx, const IncidenceCell* input,
		IncidenceCell* output);

/**
 * this one takes about 1.92 times the time of closeIntent
 * @param ctx
 * @param input
 * @param outputIntent
 * @param outputExtent
 */
void
closeIntent2(FormalContext ctx, const IncidenceCell* input,
		IncidenceCell* outputIntent,IncidenceCell* outputExtent);

int
intentCmp(int attributes, const IncidenceCell* minus, const IncidenceCell* plus);

/**
 * and the vector versions
 */

void
closeIntentV(FormalContextV ctx, const IncidenceVector input,
		IncidenceVector output);
#endif /* FCA_PRIVATE_H_ */

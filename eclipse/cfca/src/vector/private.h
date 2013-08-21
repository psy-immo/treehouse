/**
 * vector/private.h, (c) 2013, Immanuel Albrecht; Dresden University of
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

#ifndef VECTOR_PRIVATE_H_
#define VECTOR_PRIVATE_H_

#include "structs.h"

void
closeIntentV(FormalContextV ctx, const IncidenceVector input,
		IncidenceVector output);

int
intentCmpV(size_t attributes, const IncidenceVector minus,
		const IncidenceVector plus);

myFormalConceptIntentChunkV*
newConceptChunkV(size_t attributes);

void
deleteConceptChunkV(myFormalConceptIntentChunkV** c);

FormalConceptIntentBulkListV
newConceptBulkV(size_t attributes);

FormalConceptIntentBulkListV
newConceptBulkFromContextV(FormalContextV ctx);

void
writeConceptsToFileV(FormalContextV ctx, FormalConceptIntentBulkListV root,
		const char* filename);

void
deleteConceptBulkV(FormalConceptIntentBulkListV* rootNode);

size_t
countConceptsInBulkV(FormalConceptIntentBulkListV root);

FormalConceptIntentBulkListV
addConceptToBulkV(FormalConceptIntentBulkListV root,
		const IncidenceVector intent);

/*
 * multi-threaded nextClosure
 */

FormalConceptIntentBulkListV
nextClosureVX1(FormalContextV ctx, const IncidenceVector start,
		const IncidenceVector stop);

FormalConceptIntentBulkListV
nextClosureVX(FormalContextV ctx);

#endif /* PRIVATE_H_ */

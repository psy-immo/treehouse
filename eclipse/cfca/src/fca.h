/**
 * fca.h, (c) 2013, Immanuel Albrecht; Dresden University of
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

/** @file
 *
 * this file contains the public interface to the formal context analysis code
 *
 */

#ifndef FCA_H_
#define FCA_H_

/**
 * type of the incidence relation matrix cells
 */
typedef int IncidenceCell;

/**
 * abstract formal context object type used for interface purposes
 */

struct sFormalContext;
typedef struct sFormalContext *FormalContext;

typedef struct sFormalIntent {
	int attributes;
	IncidenceCell* incidence;
} FormalIntent;

FormalContext newFormalContext(int objects, int attributes);
FormalContext newFormalContextFromFile(const char* filename);
void writeFormalContext(FormalContext ctx,const char* filename);
void deleteFormalContext(FormalContext* ctx);

#endif /* FCA_H_ */

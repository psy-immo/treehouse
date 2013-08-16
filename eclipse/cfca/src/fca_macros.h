/**
 * fca_macros.h, (c) 2013, Immanuel Albrecht; Dresden University of
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
#ifndef FCA_MACROS_H_
#define FCA_MACROS_H_

#include <stdio.h>

/**
 * checks whether x == 0, and returns
 */

#define RETURN_IF_ZERO(x) {if ((x == (void*)0)) {fprintf(stderr, "WARNING: ZERO pointer %s in %s [%s:%u]\n", #x, __FUNCTION__, __FILE__,__LINE__); return;}}

#define RETURN_ZERO_IF_ZERO(x) {if ((x == (void*)0)) {fprintf(stderr, "WARNING: ZERO pointer %s in %s [%s:%u]\n", #x, __FUNCTION__, __FILE__,__LINE__); return 0;}}

#define WARN_IF_UNEQUAL_DO(x,y,d) {if (((x) != (y))) {fprintf(stderr, "WARNING: %s NOT EQUAL TO %s in %s [%s:%u]\n", #x, #y, __FUNCTION__, __FILE__,__LINE__); d;}}


/**
 * checks whether something incides by testing the 1-bit
 */

#define INCIDES(x) (((x)&1))

/**
 * clears the mark
 */

#define CLEAR(x) { (x) = 0; }

//#define CLEAR(x) { (x) &= ~1; }

/**
 * sets the mark
 */
#define CROSS(x) { (x) = 1; }
//#define CROSS(x) { (x) |= 1; }

/**
 * results in the cell that encodes whether g incides with m
 *
 *  I may be a formal context, then g refers to the object number, or
 *  I may be a chunk of formal concepts, then g refers to the concept number.
 */

#define CELL(g,I,m) ((I)->incidence[(I)->attributes * (g) + (m)])

#define gIm(g,I,m) INCIDES(CELL( (g) , (I) , (m)))

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


#endif /* FCA_MACROS_H_ */

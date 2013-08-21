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

#ifndef NO_VECTORS

/**
 * These macros are used for uint64_t bit-stream arrays
 */

#define OFFSET(x) ((unsigned)(x)>>6)
#define BITNBR(x) (((unsigned)(x))&(63))
#define WIDTH(x) ((((unsigned)(x))&(63))?((unsigned)(x)/64)+1:((unsigned)(x)/64))

#define BITVALUE(x) ((1ULL<<(63-BITNBR(x))))

/**
 * old version
 */

#define BITVALUEX(x) ((1ULL<<BITNBR(x)))

/**
 * CRIMPVALUE(0) == 1
 * CRIMPVALUE(1) == 3
 * etc.
 */

#define CRIMPVALUE(x) ((~(0ULL))>>(63-(BITNBR(x)))<<(63-BITNBR(x)))

/**
 * old version
 */

#define CRIMPVALUEX(x) ((~(0ULL))<<(63-(BITNBR(x)))>>(63-BITNBR(x)))

/**
 * set the unused attribute bits to zero. (i.e. attributes == 100 -> width == 2, BITNBR(99) == 35
 */
#define MASKVECTOR(v,x) {if (BITNBR((x))) { *((v)+OFFSET((x)-1)) = ( (*((v)+OFFSET((x)-1))>>(63-BITNBR((x)-1))) ) << (63-BITNBR((x)-1));  }}

/**
 * old version
 */
#define MASKVECTORX(v,x) {if (BITNBR((x))) { *((v)+OFFSET((x)-1)) = ( (*((v)+OFFSET((x)-1))<<(63-BITNBR((x)-1))) ) >> (63-BITNBR((x)-1));  }}


/**
 * crosses the x-th attribute of an attribute vector
 */
#define CROSSV(v,x) { *((v)+OFFSET(x)) |= BITVALUE(x); }

/**
 * clears the x-th attribute of an attribute vector
 */
#define CLEARV(v,x) { *((v)+OFFSET(x)) &= ~ (BITVALUE(x)); }

/**
 * checks whether the x-th attribute of an attribute vector is crossed
 */
#define INCIDESV(v,x) (  ( *((v)+OFFSET(x)) >> (63-BITNBR(x)) ) & 1  )


/**
 * old version
 */
#define INCIDESVX(v,x) (  ( *((v)+OFFSET(x)) >> BITNBR(x) ) & 1  )

/**
 * gives the attribute vector for a given object
 */
#define ROW(g,I) ((I)->incidence + ((I)->width * (g)))


#endif

/**
 * These macros are used for IncidenceCell array implementations of
 * formal contexts. Such implementations are easier to debug, but
 * take up far too much memory for big scale contexts
 */

#ifndef VECTORS_ONLY

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

#endif

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


#endif /* FCA_MACROS_H_ */

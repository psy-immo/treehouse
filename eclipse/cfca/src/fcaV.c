/**
 * fca.c, (c) 2013, Immanuel Albrecht; Dresden University of
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
#include <string.h>

#include "fca.h"
#include "fca_macros.h"
#include "fca_structs.h"
#include "fca_private.h"

/** @file
 *  this file contains general formal context related operations and routines with
 *  IncidenceVector implementation
 *
 */

/**
 * create a new formal context
 *
 * @param objects       object count
 * @param attributes    attribute count
 * @return a new FormalContext object
 */

FormalContextV newFormalContextV(unsigned int objects, unsigned int attributes)
{
	myFormalContextV *ctx = malloc(sizeof(myFormalContextV));

	ctx->attributes = attributes;
	ctx->objects = objects;
	ctx->width = WIDTH(attributes);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"

	ctx->attributeNames = calloc(attributes, sizeof(char*));
	ctx->objectNames = calloc(objects, sizeof(char*));

#pragma GCC diagnostic pop

	for (unsigned int var = 0; var < attributes; ++var)
	{
		ctx->attributeNames[var] = calloc(1, sizeof(char));
	}

	for (unsigned int var = 0; var < objects; ++var)
	{
		ctx->objectNames[var] = calloc(1, sizeof(char));
	}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"

	ctx->incidence = calloc(objects * ctx->width, sizeof(uint64_t));

#pragma GCC diagnostic pop

	return (FormalContextV) ctx;
}

/**
 * deletes the formal context *ctx, and sets the pointer to zero
 *
 * @param ctx  pointer to the formal context object to be deleted
 */

void deleteFormalContextV(FormalContextV* ctx)
{
	RETURN_IF_ZERO(ctx);
	RETURN_IF_ZERO(*ctx);

	myFormalContextV *c;

	c = (myFormalContextV*) *ctx;

	*ctx = 0;

	for (unsigned int var = 0; var < c->attributes; ++var)
	{
		free(c->attributeNames[var]);
	}

	for (unsigned int var = 0; var < c->objects; ++var)
	{
		free(c->objectNames[var]);
	}

	free(c->objectNames);
	free(c->attributeNames);
	free(c->incidence);
	free(c);
}

/**
 * create a new formal context object from a .cxt file
 *
 * @param filename
 * @return  the formal context that has been read from the given file
 */

FormalContextV newFormalContextFromFileV(const char* filename)
{
	char *line;
	size_t len;

	len = (INPUTBUFFERSIZE);
	line = malloc(sizeof(char) * len);

	FILE *file;

	if (strcmp(filename, "-") == 0)
	{
		file = stdin;
	}
	else
	{
		file = fopen(filename, "r");
		RETURN_ZERO_IF_ZERO(file);
	}

	ssize_t read;

	unsigned int line_nbr;
	line_nbr = 0;

	unsigned int objects;
	unsigned int attributes;

	attributes = 0;
	objects = 0;

	myFormalContextV *ctx;
	ctx = 0;

	while ((read = getline(&line, &len, file)) != -1)
	{

		/**
		 * this should never happen, right?
		 */
		if (read == 0)
			break;
		line[read - 1] = 0;

		if (line_nbr == 0)
		{
			if (strcmp(line, "B"))
			{
				fprintf(stderr, "File '%s' is not a .cxt file\n", filename);
				goto grace;
			}
		}
		else if (line_nbr == 1)
		{
			//empty line
		}
		else if (line_nbr == 2)
		{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
			objects = atoi(line);
#pragma GCC diagnostic pop
		}
		else if (line_nbr == 3)
		{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
			attributes = atoi(line);
			ctx = (myFormalContextV *) newFormalContextV(objects, attributes);
#pragma GCC diagnostic pop
		}
		else if (line_nbr == 4)
		{
			//empty line
		}
		else if (line_nbr < objects + 5)
		{

			unsigned int i;
			i = line_nbr - 5;

			free(ctx->objectNames[i]);
			ctx->objectNames[i] = strdup(line);

		}
		else if (line_nbr < objects + attributes + 5)
		{
			unsigned int i;
			i = line_nbr - 5 - objects;

			free(ctx->attributeNames[i]);
			ctx->attributeNames[i] = strdup(line);
		}
		else if (line_nbr < objects * 2 + attributes + 5)
		{
			unsigned int i;
			i = line_nbr - 5 - objects - attributes;

			unsigned int width;
			width = MIN((unsigned int)strlen(line),attributes);

			for (unsigned int var = 0; var < width; ++var)
			{
				if ((line[var] == 'x') || (line[var] == 'X')
						|| (line[var] == '1'))
				{
					CROSSV(ROW(i, ctx), var);
				}
			}

		}
		else
		{
			/**
			 * we read all data
			 */
			break;
		}

		line_nbr++;
	}

	/**
	 * free memory and return
	 */

	grace: if (file != stdin)
	{
		fclose(file);
	}

	free(line);

	return (FormalContextV) ctx;
}

/**
 * save the context ctx at the given file location
 * @param ctx
 * @param filename
 */

void writeFormalContextV(FormalContextV ctx, const char* filename)
{
	RETURN_IF_ZERO(ctx);
	RETURN_IF_ZERO(filename);

	FILE* file;
	file = fopen(filename, "w");

	RETURN_IF_ZERO(file);

	myFormalContextV *c;
	c = (myFormalContextV*) ctx;

	fprintf(file, "B\n\n%d\n%d\n\n", c->objects, c->attributes);

	for (unsigned int var = 0; var < c->objects; ++var)
	{
		fputs(c->objectNames[var], file);
		fputs("\n", file);
	}

	for (unsigned int var = 0; var < c->attributes; ++var)
	{
		fputs(c->attributeNames[var], file);
		fputs("\n", file);
	}

	for (unsigned int g = 0; g < c->objects; ++g)
	{
		for (unsigned int m = 0; m < c->attributes; ++m)
		{
			if ( INCIDESV(ROW(g, c), m))
				fputs("X", file);
			else
				fputs(".", file);
		}
		fputs("\n", file);
	}

	fclose(file);
}

/**
 * counts the concepts in the concept lattice of ctx, using next closure algorithm
 *
 * @param ctx   formal context
 * @return   number of concepts in context
 */
int countContextConceptsV(FormalContextV ctx)
{
	RETURN_ZERO_IF_ZERO(ctx);

	myFormalContextV *c;
	c = (myFormalContextV*) ctx;

	IncidenceVector M;
	IncidenceVector Y;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"

	Y = calloc(c->width, sizeof(uint64_t));
	M = malloc(c->width * sizeof(uint64_t));


#pragma GCC diagnostic pop

	/**
	 * calculate the bottom intent of the concept lattice, i.e. {}''
	 */
	closeIntentV(ctx, Y, M);

	int count;

	count = 1;

	/**
	 * begin of nextClosure function iteration
	 */
	nextClosure:

	for (unsigned int i = c->attributes; i > 0; )
	{
		--i;

		if (!INCIDESV(M,i))
		{
			CROSSV(M,i);
			closeIntentV(ctx, M, Y);

			int good;
			good = 1;

			for (unsigned int j = 0; j < OFFSET(i); ++j)
			{
				if (Y[j] & (~(M[j])))
				{
						good = 0;
						break;
				}
			}
			if (good) {
				if (Y[OFFSET(i)]& (~M[OFFSET(i)])& CRIMPVALUE(i)) {
					good = 0;
				}
			}

			if (good)
			{
				/**
				 * we found the next intent
				 */
				count++;

				/**
				 * continue with Y for M
				 */

				IncidenceVector DELTA;
				DELTA = M;
				M = Y;
				Y = DELTA;
				/**
				 * do the nextClosure
				 */
				goto nextClosure;
			}
		}

		CLEARV(M,i);
	}

	/**
	 * free up memory
	 */

	free(M);
	free(Y);

	return count;
}

/**
 * close an attribute set, i.e. add further attributes
 *
 * @param ctx    formal context
 * @param input  the intent set that is to be closed
 * @param output  the closure intent'' wrt. ctx
 */

void closeIntentV(FormalContextV ctx, const IncidenceVector input,
		IncidenceVector output)
{

	myFormalContextV* I;
	I = (myFormalContextV*) ctx;
	for (unsigned int var = 0; var < I->width; ++var)
	{
		output[var] = ~0ULL;
	}

	MASKVECTOR(output, I->attributes);

	for (unsigned int g = 0; g < I->objects; ++g)
	{
		int good;
		good = 1;

		for (unsigned int i = 0; i < I->width; ++i) {
			if ((input[i])&(~ (ROW(g,I)[i])))
			{
				/**
				 * some attribute is not present for this object -> next object
				 */
				good = 0;
				break;
			}

		}

		if (good)
		{
			/**
			 * remove attributes that are not common among all objects that have the input
			 * attributes
			 */
			for (unsigned int i = 0; i < I->width; ++i) {
						output[i] &= ROW(g,I)[i];
			}
		}
	}
}



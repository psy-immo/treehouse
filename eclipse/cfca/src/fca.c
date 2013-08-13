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

/**
 * type of the incidence relation matrix cells
 */
typedef int IncidenceCell;

/**
 * size of a chunk of concepts
 */
#define CHUNKSIZE 64

/**
 * size of chunks per bulk
 */
#define BULKSIZE 1024

/**
 * maximal (initial) size of a line (getline will resize buffers if necessary)
 *   (including delimiter)
 */
#define INPUTBUFFERSIZE (1024)

/**
 * each formal context has a finite number of objects and attributes,
 * which may have names (though we do not require them to be unique or given),
 * and an incidence relation which is represented by an objects×attributes-IncidenceCell matrix
 */

typedef struct smyFormalContext
{
	int attributes, objects;
	char** attributeNames;
	char** objectNames;
	IncidenceCell* incidence;
} myFormalContext;

/**
 * create a new formal context
 *
 * @param objects       object count
 * @param attributes    attribute count
 * @return a new FormalContext object
 */

FormalContext newFormalContext(int objects, int attributes)
{
	myFormalContext *ctx = malloc(sizeof(myFormalContext));

	ctx->attributes = attributes;
	ctx->objects = objects;

	ctx->attributeNames = calloc(attributes, sizeof(char*));
	ctx->objectNames = calloc(objects, sizeof(char*));

	for (int var = 0; var < attributes; ++var)
	{
		ctx->attributeNames[var] = calloc(1, sizeof(char));
	}

	for (int var = 0; var < objects; ++var)
	{
		ctx->objectNames[var] = calloc(1, sizeof(char));
	}

	ctx->incidence = calloc(objects * attributes, sizeof(IncidenceCell));

	return (FormalContext) ctx;
}

/**
 * create a new formal context object from a .cxt file
 *
 * @param filename
 * @return  the formal context that has been read from the given file
 */

FormalContext newFormalContextFromFile(const char* filename)
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

	int line_nbr;
	line_nbr = 0;

	int objects;
	int attributes;

	myFormalContext *ctx;
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
			objects = atoi(line);
		}
		else if (line_nbr == 3)
		{
			attributes = atoi(line);
			ctx = (myFormalContext *) newFormalContext(objects, attributes);
		}
		else if (line_nbr == 4)
		{
			//empty line
		}
		else if (line_nbr < objects + 5)
		{

			int i;
			i = line_nbr - 5;

			free(ctx->objectNames[i]);
			ctx->objectNames[i] = strdup(line);

		}
		else if (line_nbr < objects + attributes + 5)
		{
			int i;
			i = line_nbr - 5 - objects;

			free(ctx->attributeNames[i]);
			ctx->attributeNames[i] = strdup(line);
		}
		else if (line_nbr < objects * 2 + attributes + 5)
		{
			int i;
			i = line_nbr - 5 - objects - attributes;

			int width;
			width = MIN((signed)strlen(line),attributes);

			for (int var = 0; var < width; ++var)
			{
				if ((line[var] == 'x') || (line[var] == 'X')
						|| (line[var] == '1'))
				{
					CROSS( CELL (i, ctx, var));
				}
			}

		} else {
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

	return (FormalContext) ctx;
}

/**
 * save the context ctx at the given file location
 * @param ctx
 * @param filename
 */

void writeFormalContext(FormalContext ctx, const char* filename)
{
	RETURN_IF_ZERO(ctx);
	RETURN_IF_ZERO(filename);

	FILE* file;
	file = fopen(filename, "w");

	RETURN_IF_ZERO(file);

	myFormalContext *c;
	c = (myFormalContext*) ctx;

	fputs("", file);
	fprintf(file,"B\n\n%d\n%d\n\n", c->objects, c->attributes);

	for (int var = 0; var < c->objects; ++var)
	{
		fputs(c->objectNames[var], file);
		fputs("\n", file);
	}

	for (int var = 0; var < c->attributes; ++var)
	{
		fputs(c->attributeNames[var], file);
		fputs("\n", file);
	}

	for (int g = 0; g < c->objects; ++g)
	{
		for (int m = 0; m < c->attributes; ++m)
		{
			if ( gIm(g, c, m))
				fputs("X",file);
			else
				fputs(".",file);
		}
		fputs("\n",file);
	}

	fclose(file);
}

/**
 * deletes the formal context *ctx, and sets the pointer to zero
 *
 * @param ctx  pointer to the formal context object to be deleted
 */

void deleteFormalContext(FormalContext* ctx)
{
	RETURN_IF_ZERO(ctx);
	RETURN_IF_ZERO(*ctx);

	myFormalContext *c;

	c = (myFormalContext*) *ctx;

	*ctx = 0;

	for (int var = 0; var < c->attributes; ++var)
	{
		free(c->attributeNames[var]);
	}

	for (int var = 0; var < c->objects; ++var)
	{
		free(c->objectNames[var]);
	}

	free(c->objectNames);
	free(c->attributeNames);
	free(c->incidence);
	free(c);
}

/**
 * A chunk of at most CHUNKSIZE formal concept intents
 */

typedef struct smyFormalConceptIntentChunk
{
	/**
	 * number of attributes
	 */
	int attributes;
	/**
	 * how many formal concepts are in this chunk
	 */
	int size;
	/**
	 * the intents of the concepts
	 */
	IncidenceCell* incidence;
} myFormalConceptIntentChunk;

/**
 * create a new formal concept chunk
 *
 * @param attributes  number of attributes of the hosting formal context
 * @return  a new concept chunk object
 */

myFormalConceptIntentChunk* newConceptChunk(int attributes)
{
	myFormalConceptIntentChunk *c;
	c = malloc(sizeof(myFormalConceptIntentChunk));
	c->attributes = attributes;
	c->size = 0;

	c->incidence = calloc(attributes * CHUNKSIZE, sizeof(IncidenceCell));

	return c;
}

/**
 * deletes a concept chunk object and sets its pointer to zero
 *
 * @param c   pointer to the concept chunk to be deleted
 */

void deleteConceptChunk(myFormalConceptIntentChunk** c)
{
	RETURN_IF_ZERO(c);
	RETURN_IF_ZERO(*c);

	free((*c)->incidence);

	free(*c);
	*c = 0;
}


typedef struct sFormalConceptIntentBulkNode {
	/**
	 * number of attributes of the concept intents
	 */
	int attributes;
	/**
	 * number of chunks used
	 */
	int size;
	/**
	 * array to at most BULKSIZE chunks
	 */
	myFormalConceptIntentChunk* chunks;
	/**
	 * pointer to the next BulkNode, or 0
	 */
    struct sFormalConceptIntentBulkNode* next;
} * FormalConceptIntentBulkList;

typedef FormalConceptIntentBulkNode;

FormalConceptIntentBulkList newConceptBulk(int attributes) {
	FormalConceptIntentBulkList l;
	l = malloc(sizeof(struct sFormalConceptIntentBulkNode));

	l->attributes = attributes;
	l->size = 0;
	l->chunks = calloc(BULKSIZE,sizoef(myFormalConceptIntentChunk));
	l->next = 0;
	return l;
}

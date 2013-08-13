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

#include "fca.h"

typedef int IncidenceCell;

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
	IncidenceCell* incidenceRelation;
} myFormalContext;

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

	ctx->incidenceRelation = calloc(objects * attributes,
			sizeof(IncidenceCell));

	return (FormalContext) ctx;
}

void deleteFormalContext(FormalContext* ctx)
{
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
	free(c->incidenceRelation);
	free(c);
}

/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2012 Excensus LLC.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: triangulate/ConstraintVertex.java rev. r524
 *
 **********************************************************************/

#include <geos/triangulate/ConstraintVertex.h>

#include <geos/triangulate/quadedge/Vertex.h>
#include <geos/geom/Coordinate.h>

namespace geos {
namespace triangulate { //geos.triangulate

ConstraintVertex::ConstraintVertex(const geom::Coordinate p):
	constraint(NULL), Vertex(p)
{
}

void
ConstraintVertex::setOnConstraint(const bool isOnConstraint)
{
	this->isOnConstraint = isOnConstraint;
}

bool
ConstraintVertex::isConstraint()
{
	return isOnConstraint;
}

void
ConstraintVertex::setConstraint(void* constraint)
{
	isOnConstraint = 1;
	this->constraint = constraint;
}
void*
ConstraintVertex::getConstraint()
{
	return constraint;
}

void 
ConstraintVertex::merge(const ConstraintVertex &other)
{
	if(other.isOnConstraint)
	{
		isOnConstraint = 1;
		constraint  = other.constraint;
	}
}

} //namespace geos.triangulate
} //namespace geos

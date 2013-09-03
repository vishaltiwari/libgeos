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
 * Last port: triangulate/Segment.java rev. r524
 *
 **********************************************************************/

#include <geos/triangulate/Segment.h>

#include <geos/geom/Coordinate.h>
#include <geos/geom/LineSegment.h>

namespace geos {
namespace triangulate { //geos.triangulate


Segment::Segment(const geom::Coordinate &p0,const geom::Coordinate &p1):
	ls(new geom::LineSegment(p0,p1)),
	data(NULL)
{
}

Segment::Segment(const geom::Coordinate &p0,const geom::Coordinate &p1, void* data):
	ls(new geom::LineSegment(p0,p1)),
	data(data)
{
}

Segment::~Segment()
{
	if(ls !=NULL)
		delete ls;
}

geom::LineSegment*
Segment::getLineSegment()
{
	return ls;
}

geom::Coordinate&
Segment::getStart()
{
	ls->getCoordinate(0);
}

geom::Coordinate&
Segment::getEnd()
{
	ls->getCoordinate(1);
}

double
Segment::getStartX()
{
	return (ls->getCoordinate(0)).x;
}

double
Segment::getStartY()
{
	return (ls->getCoordinate(0)).y;
}

double
Segment::getStartZ()
{
	return (ls->getCoordinate(0)).z;
}

double
Segment::getEndX()
{
	return (ls->getCoordinate(1)).x;
}

double
Segment::getEndY()
{
	return (ls->getCoordinate(1)).y;
}

double
Segment::getEndZ()
{
	return (ls->getCoordinate(1)).z;
}

void*
Segment::getData()
{
	return data;
}

void 
Segment::setData(void* data)
{
	this->data = data;
}

} //namespace geos.triangulate
} //namespace goes

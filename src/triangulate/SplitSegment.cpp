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
 * Last port: triangulate/SplitSegment.java rev. r524
 *
 **********************************************************************/

#include <geos/triangulate/SplitSegment.h>
#include <geos/geom/Coordinate.h>
#include <geos/geom/LineSegment.h>

using geos::geom::LineSegment;
using geos::geom::Coordinate;

namespace geos {
namespace triangulate { //geos.triangulate

SplitSegment::SplitSegment(const geom::LineSegment &seg):
	seg((LineSegment*)&seg),
	segLen(seg.getLength()),
	splitPt(NULL),
	minimumLen(0)
{
}

SplitSegment::~SplitSegment()
{
	if(seg != NULL)
		delete seg;
	if(splitPt !=NULL)
		delete splitPt;
}
void
SplitSegment::setMinimumLength(const double minLen)
{
	minimumLen = minLen;
}

geom::Coordinate&
SplitSegment::getSplitPoint()
{
	return *splitPt;
}

void
SplitSegment::splitAt(const double length,const geom::Coordinate &endPt)
{
	double actualLen = getConstrainedLength(length);
	double frac = actualLen / segLen;
	if(endPt.equals2D(seg->p0))
		seg->pointAlong(frac,*splitPt);
	else
		splitPt = pointAlongReverse(seg,frac);
}

void 
SplitSegment::splitAt(const geom::Coordinate &pt)
{
	double minFrac = minimumLen / segLen;
	if(pt.distance(seg->p0) < minimumLen)
	{
		seg->pointAlong(minFrac,*splitPt);
		return ;
	}
	if (pt.distance(seg->p1) < minimumLen)
	{
		splitPt = pointAlongReverse(seg,minFrac);
		return ;
	}
	*splitPt = pt;
}
double 
SplitSegment::getConstrainedLength(const double len)
{
	if(len < minimumLen)
		return minimumLen;
	return len;
}
geom::Coordinate*
SplitSegment::pointAlongReverse(const geom::LineSegment* seg,const double segmentLengthFraction)
{
	Coordinate *coord = new Coordinate(0,0);
	coord->x = seg->p1.x - segmentLengthFraction * (seg->p1.x - seg->p0.x);
	coord->y = seg->p1.y - segmentLengthFraction * (seg->p1.y - seg->p0.y);
	return coord;
}

} //namespace geos.triangulate
} //namespace geos


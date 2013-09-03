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

geom::Coordinate&
NonEncroachingSplitPointFinder findSplitPoint(const Segment &seg, const geom::Coordinate &encroachPt)
{
	geom::LineSegment* lineSeg = seg.getLineSegment();
	double segLen = lineSeg->getLength();
	double midPtLen = segLen/2;
	SplitSegment splitSeg(*lineSeg);

	geom::Coordinate projPt = projectedSplitPoint(seg,encroachPt);

	double nonEncroachDiam = projPt.distance(encroachPt) * 2 * 0.8;
	double maxSplitLen = nonEncroachDiam;
	if(maxSplitLen > midPtLen) {
		maxSplitLen = midPtLen;
	}
	splitSeg.setMinimumLength(maxSplitLen);
	splitSeg.At(projPt);
	delete lineSeg;
	return splitSeg.getSplitPoint();
}

geom::Coordinate&
NonEncroachingSplitPointFinder projectedSplitPoint(const Segment &seg, geom::Coordinate &encroachPt)
{
	geom::LineSegment* lineSeg = seg.getLineSegment();
	geom::Coordinate projPt = lineSeg->project(encroachPt);
	return projPt;
}

} //namespace geos.triangulate
} //namespace goes

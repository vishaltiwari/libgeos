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
 * Last port: triangulate/NonEncroachingSplitPointFinder.java r524
 *
 **********************************************************************/

#ifndef GEOS_TRIANGULATE_NONENCROACHINGSPLITPOINTFINDER_H
#define GEOS_TRIANGULATE_NONENCROACHINGSPLITPOINTFINDER_H

#include <list>
#include <geos/triangulate/Segment.h>

namespace geos {
namespace geom {
	class Coordinate;
	class LineSegment;
}
namespace triangulate { //geos.triangulate

class NonEncroachingSplitPointFinder : public ConstraintSplitPointFinder {
public:
	geom::Coordinate& findSplitPoint(const Segment &seg, const geom::Coordinate &encroachPt);

	static geom::Coordinate& projectedSplitPoint(const Segment &seg, geom::Coordinate &encroachPt);
};

} //namespace geos.triangulate
} //namespace geos

#endif //GEOS_TRIANGULATE_QUADEDGE_SEGMENT_H

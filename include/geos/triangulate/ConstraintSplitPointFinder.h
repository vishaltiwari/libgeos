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
 * Last port: triangulate/quadedge/ConstraintSplitPointFinder.java r524
 *
 **********************************************************************/

#ifndef GEOS_TRIANGULATE_CONSTRAINTSPLITPOINTFINDER_H
#define GEOS_TRIANGULATE_CONSTRAINTSPLITPOINTFINDER_H

#include <geos/triangulate/Segment.h>
namespace geos {
namespace geom{
	class Coordinate;
}
namespace triangulate { //geos.triangulate

/**
 * An interface for strategies for determining the location of split points on constraint segments.
 * The location of split points has a large effect on the performance and robustness of enforcing a
 * constrained Delaunay triangulation. Poorly chosen split points can cause repeated splitting,
 * especially at narrow constraint angles, since the split point will end up encroaching on the
 * segment containing the original encroaching point. With detailed knowledge of the geometry of the
 * constraints, it is sometimes possible to choose better locations for splitting.
 * 
 * @author mbdavis
 */
class ConstraintSplitPointFinder {
public:
	/** 
	 * Finds a point at which to split an encroached segment to allow the original segment to appear
	 * as edges in a constrained Delaunay triangulation.
	 * 
	 * @param seg the encroached segment
	 * @param encroachPt the encroaching point
	 * @return the point at which to split the encroached segment
	 */
	virtual geom::Coordinate findSplitPoint(Segment seg, geom::Coordinate encroachPt) = 0;
	virtual ~ConstraintSplitPointFinder() = 0 ;
} ; 
} //namespace geos.triangulate
} //namespace goes

#endif // GEOS_TRIANGULATE_CONSTRAINTSPLITPOINTFINDER_H

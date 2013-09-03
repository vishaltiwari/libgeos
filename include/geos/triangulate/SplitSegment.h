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
 * Last port: triangulate/SplitSegment.java r524
 *
 **********************************************************************/

#ifndef GEOS_TRIANGULATE_SPLITSEGMENT_H
#define GEOS_TRIANGULATE_SPLITSEGMENT_H

#include <geos/geom/LineSegment.h>

namespace geos {
namespace geom {
	class Coordinate;
	class LineSegment;
}
namespace triangulate { //geos.triangulate

class GEOS_DLL SplitSegment {
private:
	geom::LineSegment* seg;
	double segLen;
	geom::Coordinate* splitPt;
	double minimumLen;
public:
	SplitSegment(const geom::LineSegment &seg);
	~SplitSegment();

	void setMinimumLength(const double minLen);

	geom::Coordinate& getSplitPoint();

	void splitAt(const double length,const geom::Coordinate &endPt);

	void splitAt(const geom::Coordinate &pt);

private:
	double getConstrainedLength(const double len);

	static geom::Coordinate* pointAlongReverse(const geom::LineSegment* seg,const double segmentLengthFraction);
};

} //namespace geos.triangulate
} //namespace goes

#endif //GEOS_TRIANGULATE_SPLITSEGMENT_H


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
 * Last port: triangulate/Segment.java r524
 *
 **********************************************************************/

#ifndef GEOS_TRIANGULATE_SEGMENT_H
#define GEOS_TRIANGULATE_SEGMENT_H

#include <geos/geom/LineSegment.h>
namespace geos {
namespace geom {
	class Coordinate;
	class LineSegment;
}
namespace triangulate { //geos.triangulate

class GEOS_DLL Segment 
{
private:
	geom::LineSegment* ls;
	void* data;

public:
	Segment(const geom::Coordinate &p0,const geom::Coordinate &p1);

	Segment(const geom::Coordinate &p0,const geom::Coordinate &p1 ,void* data);

	~Segment();
	
	geom::LineSegment* getLineSegment();

	geom::Coordinate& getStart();
	
	geom::Coordinate& getEnd();

	double getStartX();
	double getStartY();
	double getStartZ();
	
	double getEndX();
	double getEndY();
	double getEndZ();

	void* getData();
	void setData(void* data);
};

} //namespace geos.triangulate
} //namespace goes

#endif //GEOS_TRIANGULATE_QUADEDGE_SEGMENT_H

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
 * Last port: triangulate/ConstraintVertex.java r524
 *
 **********************************************************************/

#ifndef GEOS_TRIANGULATE_CONSTRAINTVERTEX_H
#define GEOS_TRIANGULATE_CONSTRAINTVERTEX_H

#include <geos/triangulate/quadedge/Vertex.h>
namespace geos {
namespace geom{
	class Coordinate;
}
namespace triangulate { //geos.triangulate

namespace quadedge {
	class Vertex;
}

class GEOS_DLL ConstraintVertex : public geos::triangulate::quadedge::Vertex 
{
private:
	bool isOnConstraint;
	void* constraint;

public:
	ConstraintVertex(const geom::Coordinate p);

	void setOnConstraint(const bool isOnConstraint);

	bool isConstraint();

	void setConstraint(void* constraint);

	void* getConstraint();

protected:
	void merge(const ConstraintVertex &other);

};

} //namespace geos.triangulate
} //namespace goes

#endif //GEOS_TRIANGULATE_CONTRAINTVERTEX_H


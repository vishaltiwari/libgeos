/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: index/quadtree/KdNode.java rev 1.8 (JTS-1.10)
 *
 **********************************************************************/

#ifndef GEOS_IDX_KDTREE_KDTREE_H
#define GEOS_IDX_KDTREE_KDTREE_H

#include <geos/index/kdtree/KdTree.h>
#include <geos/index/kdtree/KdNode.h>

#include <geos/export.h>
#include <geos/geom/Coordinate.h> 

#include <string>
#include <memory>

namespace geos {
	namespace geom {
		class Coordinate;
	}
}

namespace geos {
namespace index { // geos::index
namespace kdtree { // geos::index::kdtree

class KdTree {

private:
	KdNode* root;
	KdNode* last;
	long int numberofNodes;
	double tolerance;

public:
	KdTree();

	KdTree(double tolerance);

	~KdTree();

};

} // namespace geos::index::kdtree
} // namespace geos::index
} // namespace geos

#endif // GEOS_IDX_KDTREE_KDTREE_H

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

#include <vector>
namespace geos {
	namespace geom {
		class Coordinate;
		class Envelope;
	}
	namespace index{
		namespace kdtree{
		class KdNode;
		}
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

	bool isEmpty();

	KdNode* insert(const geom::Coordinate &p);

	KdNode* insert(const geom::Coordinate &p, void *data);

	std::vector<void*> query(const geom::Envelope &queryEnv);

	void query(const geom::Envelope &queryEnv, std::vector<void*> &result);

private:
	void queryNode(KdNode* currentNode, const KdNode* bottomNode, 
			const geom::Envelope &queryEnv, bool odd, std::vector<void*> &result);

};

} // namespace geos::index::kdtree
} // namespace geos::index
} // namespace geos

#endif // GEOS_IDX_KDTREE_KDTREE_H

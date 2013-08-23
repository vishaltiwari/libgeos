/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
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

#include <geos/index/kdtree/KdNode.h> 
#include <geos/geom/Coordinate.h>

#include <string>
#include <sstream>
#include <cassert>

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

#if GEOS_DEBUG
#include <iostream>
#endif

using namespace std;
using namespace geos::geom;
using geos::geom::Coordinate;

namespace geos {
namespace index { // geos.index
namespace kdtree { // geos.index.kdtree

KdNode::KdNode(const double _x,const double _y , void *d):
	p(Coordinate(_x,_y)), left(NULL) , right(NULL) , count(1), data(d)
{   
}   

KdNode::KdNode(const Coordinate &point , void *d):
	p(point) , left(NULL) , right(NULL) , count(1), data(d)

{
}

KdNode::~KdNode()
{
	if(left)
		delete left;
	if(right)
		delete right;

}

double
KdNode::getX()
{
	return p.x;
}

double
KdNode::getY()
{
	return p.y;
}

geom::Coordinate
KdNode::getCoordinate()
{
	return p;
}

void*
KdNode::getData()
{
	return data;
}

KdNode*
KdNode::getLeft()
{
	return left;
}

KdNode*
KdNode::getRight()
{
	return right;
}

void
KdNode::increment()
{
	++count;
}

int
KdNode::getCount()
{
	return count;
}

bool 
KdNode::isRepeated()
{
	return count>1;
}

void 
KdNode::setLeft(const KdNode* _left)
{
	left =(KdNode*) _left;
}

void
KdNode::setRight(const KdNode* _right)
{
	right = (KdNode*)_right;
}

} // namespace geos.index.kdtree
} // namespace geos.index
} // namespace geos

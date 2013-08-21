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

namespace geos {
namespace index { // geos.index
namespace kdtree { // geos.index.quadtree

KdNode::KdNode(const double _x,const double _y , void *data)
	:   
	*p = new Coordinate(_x,_y);
	*left = NULL;
	*right = NULL;
{   


}   



} // namespace geos.index.quadtree
} // namespace geos.index
} // namespace geos

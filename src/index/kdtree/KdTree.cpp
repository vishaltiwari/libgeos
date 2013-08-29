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
 * Last port: index/quadtree/KdTree.java rev 1.8 (JTS-1.10)
 *
 **********************************************************************/

#include <geos/index/kdtree/KdTree.h> 
#include <geos/index/kdtree/KdNode.h> 
#include <geos/geom/Coordinate.h>
#include <geos/geom/Envelope.h>

#include <vector>
#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

#if GEOS_DEBUG
#include <iostream>
#endif

using namespace std;
using namespace geos::geom;
using geos::geom::Coordinate;
using geos::geom::Envelope;

namespace geos {
namespace index { // geos.index
namespace kdtree { // geos.index.kdtree

KdTree::KdTree(double tolerance):
	tolerance(tolerance), root(NULL) , last(NULL), numberofNodes(0)
{
}

KdTree::~KdTree()
{
	if(root)
		delete root;
	if(last)
		delete last;
}
bool
KdTree::isEmpty()
{
	if(root==NULL)
		return 1;
	else
		return 0;
}
KdNode*
KdTree::insert(const geom::Coordinate &p)
{
	return insert(p,NULL);
}
KdNode*
KdTree::insert(const geom::Coordinate &p, void *data)
{
	if(root == NULL)
	{
		root = new KdNode(p,data);
		return root;
	}
	KdNode* currentNode = root;
	KdNode* leafNode = root;
	bool isOddLevel = true;
	bool isLessThan = true;

	//traverse the tree
	while(currentNode != last)
	{
		if(currentNode !=NULL)
		{
			bool isInTolerance = p.distance(currentNode->getCoordinate()) <= tolerance;
			if(isInTolerance)
			{
				currentNode->increment();
				return currentNode;
			}
		}
		if(isOddLevel)
		{
			isLessThan = p.x < currentNode->getX();
		}
		else
		{
			isLessThan = p.y < currentNode->getY();
		}
		leafNode = currentNode;
		if(isLessThan)
		{
			currentNode = currentNode->getLeft();
		}
		else
		{
			currentNode = currentNode->getRight();
		}
		isOddLevel = !isOddLevel;
	}

	++numberofNodes;
	KdNode *node = new KdNode(p,data);
	node->setLeft(last);
	node->setRight(last);
	if(isLessThan)
	{
		leafNode->setLeft(node);
	}
	else
	{
		leafNode->setRight(node);
	}
	return node;
}

void
KdTree::queryNode(KdNode* currentNode, const KdNode* bottomNode, 
		        const geom::Envelope &queryEnv, bool odd, std::vector<KdNode*> &result)
{
	if(currentNode == bottomNode)
		return;

	double min;
	double max;
	double discriminant;
	if(odd)
	{
		min = queryEnv.getMinX();
		max = queryEnv.getMaxX();
		discriminant = currentNode->getX();
	}
	else
	{
		min = queryEnv.getMinY();
		max = queryEnv.getMaxY();
		discriminant = currentNode->getY();
	}
	bool searchLeft = min < discriminant;
	bool searchRight = discriminant <= max;

	if(searchLeft)
	{
		queryNode(currentNode->getLeft(),bottomNode,queryEnv,!odd,result);
	}
	if(queryEnv.contains(currentNode->getCoordinate()))
	{
		result.push_back((KdNode*)currentNode);
	}
	if(searchRight)
	{
		queryNode(currentNode->getRight(),bottomNode,queryEnv,!odd,result);
	}
}

std::vector<KdNode*>
KdTree::query(const geom::Envelope &queryEnv)
{
	std::vector<KdNode*> result;
	queryNode(root,last,queryEnv,true,result);
	return result;
}

void
KdTree::query(const geom::Envelope &queryEnv, std::vector<KdNode*> &result)
{
	queryNode(root,last,queryEnv,true,result);
}

} // namespace geos.index.kdtree
} // namespace geos.index
} // namespace geos

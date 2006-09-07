/**********************************************************************
 * $Id$
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 ***********************************************************************
 *
 * Last port: operation/overlay/OverlayResultValidator.java rev. 0
 *
 **********************************************************************/

#include <geos/operation/overlay/OverlayResultValidator.h>
#include <geos/operation/overlay/FuzzyPointLocator.h>
#include <geos/operation/overlay/OffsetPointGenerator.h>

#include <cassert>
#include <functional>
#include <vector>
#include <memory> // for auto_ptr
#include <algorithm>

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

#define COMPUTE_Z 1
#define USE_ELEVATION_MATRIX 1
#define USE_INPUT_AVGZ 0

using namespace std;
using namespace geos::geom;
using namespace geos::geomgraph;
using namespace geos::algorithm;

namespace geos {
namespace operation { // geos.operation
namespace overlay { // geos.operation.overlay

double OverlayResultValidator::_TOLERANCE = 0.000001;

namespace { // anonymous namespace

bool isArea(const Geometry& g)
{
        GeometryTypeId type = g.getGeometryTypeId();
        if ( type == GEOS_POLYGON ) return true;
        if ( type == GEOS_MULTIPOLYGON ) return true;
        return false;
}

} // anonymous namespace


/* static public */
bool
OverlayResultValidator::isValid(const Geometry& geom0, const Geometry& geom1,
		OverlayOp::OpCode opCode,
		const Geometry& result)
{
	OverlayResultValidator validator(geom0, geom1, result);
	return validator.isValid(opCode);
}

/*public*/
OverlayResultValidator::OverlayResultValidator(
		const Geometry& geom0,
		const Geometry& geom1,
		const Geometry& result)
	:
	g0(geom0),
	g1(geom1),
	gres(result),
	fpl0(g0, _TOLERANCE),
	fpl1(g1, _TOLERANCE),
	fplres(gres, _TOLERANCE),
	invalidLocation()
{
}

/*public*/
bool
OverlayResultValidator::isValid(OverlayOp::OpCode overlayOp)
{
	// The check only works for areal geoms
	if ( ! isArea(g0) ) return true;
	if ( ! isArea(g1) ) return true;
	if ( ! isArea(gres) ) return true;

	addTestPts(g0);
	addTestPts(g1);
	if (! testValid(overlayOp) )
		return false;
	return true;
}

/*private*/
void
OverlayResultValidator::addTestPts(const Geometry& g)
{
	OffsetPointGenerator ptGen(g, 5 * _TOLERANCE);
	auto_ptr< vector<geom::Coordinate> > pts = ptGen.getPoints();
	testCoords.insert(testCoords.end(), pts->begin(), pts->end());
}

/*private*/
bool
OverlayResultValidator::testValid(OverlayOp::OpCode overlayOp)
{
	for (size_t i=0, n=testCoords.size(); i<n; ++i)
	{
		Coordinate& pt = testCoords[i];
		if (! testValid(overlayOp, pt)) {
			invalidLocation = pt;
			return false;
		}
	}
	return true;
}

/*private*/
bool
OverlayResultValidator::testValid(OverlayOp::OpCode overlayOp,
		const Coordinate& pt)
{
	std::vector<geom::Location::Value> location(3);

	location[0] = fpl0.getLocation(pt);
	location[1] = fpl1.getLocation(pt);
	location[2] = fplres.getLocation(pt);

	/*
	 * If any location is on the Boundary, can't deduce anything,
	 * so just return true
	 */
	if ( find(location.begin(), location.end(), Location::BOUNDARY) != location.end() )
	{
		return true;
	}

	return isValidResult(overlayOp, location);
}

/* private */
bool
OverlayResultValidator::isValidResult(OverlayOp::OpCode overlayOp,
	std::vector<geom::Location::Value>& location)
{
	bool expectedInterior = OverlayOp::isResultOfOp(location[0],
			location[1], overlayOp);

	bool resultInInterior = (location[2] == Location::INTERIOR);

	bool isValid = ! (expectedInterior ^ resultInInterior);

	return isValid;
}



} // namespace geos.operation.overlay
} // namespace geos.operation
} // namespace geos

/**********************************************************************
 * $Log$
 **********************************************************************/

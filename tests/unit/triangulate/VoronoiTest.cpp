
// 
// Test Suite for geos::triangulate::quadedge::QuadEdge
//
// tut
#include <tut.hpp>
// geos
#include <geos/triangulate/quadedge/QuadEdge.h>
#include <geos/triangulate/quadedge/QuadEdgeSubdivision.h>
#include <geos/triangulate/IncrementalDelaunayTriangulator.h>
#include <geos/triangulate/VoronoiDiagramBuilder.h>

#include <geos/io/WKTWriter.h>
#include <geos/io/WKTReader.h>
#include <geos/geom/GeometryCollection.h>
#include <geos/geom/GeometryFactory.h>

#include <geos/geom/CoordinateArraySequence.h>
//#include <stdio.h>

using namespace geos::triangulate;
using namespace geos::triangulate::quadedge;
using namespace geos::geom;
using namespace geos::io;

namespace tut
{
	//
	// Test Group
	//

	// dummy data, not used
	struct test_voronoidiag_data
	{
		test_voronoidiag_data()
		{
		}
	};

	typedef test_group<test_voronoidiag_data> group;
	typedef group::object object;

	group test_voronoidiag_group("geos::triangulate::Voronoi");

	//helper function for funning triangulation
	void runVoronoi(const char *sitesWkt, const char *expectedWkt)
	{
		WKTReader reader;
	        WKTWriter writer;
	        geos::triangulate::VoronoiDiagramBuilder builder;
		Geometry* sites = reader.read(sitesWkt);
		Geometry* expected = reader.read(expectedWkt);
//		cout << "Here are the sites::" << sites->toString() << endl;
		std::auto_ptr<GeometryCollection> results;
		GeometryFactory geomFact;
		builder.setSites(*sites);
		results = builder.getDiagram(geomFact);

//		string out = writer.write(results.get());
//		cout << out << endl;

		results->normalize();
		expected->normalize();
			
		ensure(results->equalsExact(expected, 1e-7));
		ensure(results->getCoordinateDimension() == expected->getCoordinateDimension());

		delete sites;
		delete expected;
	}

	// Test Cases
	// Basic Tests.
	template<>
	template<>
	void object::test<1>()
	{
		using geos::geom::CoordinateSequence;
		Coordinate a(180,300);
		Coordinate b(300,290);
		Coordinate c(230,330);
		Coordinate d(244,284);

		geos::triangulate::VoronoiDiagramBuilder builder;
		std::vector<Coordinate>* v = new std::vector<Coordinate>();
		v->push_back(a);
		v->push_back(b);
		v->push_back(c);
		v->push_back(d);

		geos::geom::CoordinateArraySequence *seq = new CoordinateArraySequence(v);
		builder.setSites(*seq);

		//getting the subdiv()
		QuadEdgeSubdivision* subdiv = builder.getSubdivision();
		
//		cout << "Tolerance::" <<subdiv->getTolerance() << endl;
//		cout << "Envelope" << subdiv->getEnvelope().toString() << endl;

	}
	// 1 - Case with a single point
	template<>
	template<>
	void object::test<2>()
	{
		const char *wkt = "MULTIPOINT ((150 200))";
		const char *expected = "GEOMETRYCOLLECTION EMPTY";
		runVoronoi(wkt,expected);
	}

	template<>
	template<>
	void object::test<3>()
	{
		const char *wkt = "MULTIPOINT ((150 200), (180 270), (275 163))";

		const char *expected = "GEOMETRYCOLLECTION (POLYGON ((25 38, 25 295, 221.20588235294116 210.91176470588235, 170.024 38, 25 38)), POLYGON ((400 369.6542056074766, 400 38, 170.024 38, 221.20588235294116 210.91176470588235, 400 369.6542056074766)), POLYGON ((25 295, 25 395, 400 395, 400 369.6542056074766, 221.20588235294116 210.91176470588235, 25 295)))";

		runVoronoi(wkt,expected);
	}

	template<>
	template<>
	void object::test<4>()
	{
		const char *wkt = "MULTIPOINT ((280 300), (420 330), (380 230), (320 160))";
		
		const char *expected = "GEOMETRYCOLLECTION (POLYGON ((110 175.71428571428572, 110 500, 310.35714285714283 500, 353.515625 298.59375, 306.875 231.96428571428572, 110 175.71428571428572)), POLYGON ((590 204, 590 -10, 589.1666666666666 -10, 306.875 231.96428571428572, 353.515625 298.59375, 590 204)), POLYGON ((110 -10, 110 175.71428571428572, 306.875 231.96428571428572, 589.1666666666666 -10, 110 -10)), POLYGON ((310.35714285714283 500, 590 500, 590 204, 353.515625 298.59375, 310.35714285714283 500)))";
		runVoronoi(wkt,expected);
	}

	template<>
	template<>
	void object::test<5>()
	{
		const char *wkt = "MULTIPOINT ((320 170), (366 246), (530 230), (530 300), (455 277), (490 160))";
		
		const char *expected = "GEOMETRYCOLLECTION (POLYGON ((110 -50, 110 349.02631578947364, 405.31091180866963 170.28550074738416, 392.35294117647055 -50, 110 -50)), POLYGON ((740 63.57142857142859, 740 -50, 392.35294117647055 -50, 405.31091180866963 170.28550074738416, 429.9147677857019 205.76082797008175, 470.12061711079946 217.7882187938289, 740 63.57142857142859)), POLYGON ((110 349.02631578947364, 110 510, 323.9438202247191 510, 429.9147677857019 205.76082797008175, 405.31091180866963 170.28550074738416, 110 349.02631578947364)),  POLYGON ((323.9438202247191 510, 424.57333333333327 510, 499.70666666666665 265, 470.12061711079946 217.7882187938289, 429.9147677857019 205.76082797008175, 323.9438202247191 510)),POLYGON ((740 265, 740 63.57142857142859, 470.12061711079946 217.7882187938289, 499.70666666666665 265, 740 265)), POLYGON ((424.57333333333327 510, 740 510, 740 265, 499.70666666666665 265, 424.57333333333327 510)))";
		runVoronoi(wkt,expected);
	}
	//6. A little larger number of points
	template<>
	template<>
	void object::test<6>()
	{
		const char *wkt = "MULTIPOINT ((280 200), (406 285), (580 280), (550 190), (370 190), (360 90), (480 110), (440 160), (450 180), (480 180), (460 160), (360 210), (360 220), (370 210), (375 227))";
	
		const char *expected = "GEOMETRYCOLLECTION (POLYGON ((-20 -102.27272727272727, -20 585, 111.9484126984127 585, 293.54906542056074 315.803738317757, 318.75 215, 323.2352941176471 179.11764705882354, 319.3956043956044 144.56043956043956, -20 -102.27272727272727)), POLYGON ((365 200, 365 215, 369.40909090909093 219.4090909090909, 414.2119205298013 206.2317880794702, 411.875 200, 365 200)), POLYGON ((365 215, 365 200, 323.2352941176471 179.11764705882354, 318.75 215, 365 215)), POLYGON ((-20 -210, -20 -102.27272727272727, 319.3956043956044 144.56043956043956, 388.972602739726 137.60273972602738, 419.55882352941177 102.64705882352942, 471.66666666666674 -210, -20 -210)), POLYGON ((319.3956043956044 144.56043956043956, 323.2352941176471 179.11764705882354, 365 200, 411.875 200, 410.29411764705884 187.35294117647058, 388.972602739726 137.60273972602738, 319.3956043956044 144.56043956043956)), POLYGON ((410.29411764705884 187.35294117647058, 411.875 200, 414.2119205298013 206.2317880794702, 431.62536593766146 234.01920096435336, 465 248.0047619047619, 465 175, 450 167.5, 410.29411764705884 187.35294117647058)), POLYGON ((365 215, 318.75 215, 293.54906542056074 315.803738317757, 339.6500765696784 283.1784073506891, 369.40909090909093 219.4090909090909, 365 215)), POLYGON ((111.9484126984127 585, 501.69252873563215 585, 492.5670391061452 267.4329608938547, 465 248.0047619047619, 431.62536593766146 234.01920096435336, 339.6500765696784 283.1784073506891, 293.54906542056074 315.803738317757, 111.9484126984127 585)),  POLYGON ((369.40909090909093 219.4090909090909, 339.6500765696784 283.1784073506891, 431.62536593766146 234.01920096435336, 414.2119205298013 206.2317880794702, 369.40909090909093 219.4090909090909)), POLYGON ((388.972602739726 137.60273972602738, 410.29411764705884 187.35294117647058, 450 167.5, 450 127, 419.55882352941177 102.64705882352942, 388.972602739726 137.60273972602738)), POLYGON ((465 175, 465 248.0047619047619, 492.5670391061452 267.4329608938547, 505 255, 520.7142857142857 145, 495 145, 465 175)),POLYGON ((880 -169.375, 880 -210, 471.66666666666674 -210, 419.55882352941177 102.64705882352942, 450 127, 495 145, 520.7142857142857 145, 880 -169.375)), POLYGON ((450 167.5, 465 175, 495 145, 450 127, 450 167.5)), POLYGON ((501.69252873563215 585, 880 585, 880 130.00000000000006, 505 255, 492.5670391061452 267.4329608938547, 501.69252873563215 585)), POLYGON ((880 130.00000000000006, 880 -169.375, 520.7142857142857 145, 505 255, 880 130.00000000000006)))";

		runVoronoi(wkt,expected);
	}



} // namespace tut



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
		std::auto_ptr<GeometryCollection> results;
		Geometry *sites = reader.read(sitesWkt);
		Geometry *expected = reader.read(expectedWkt);
		VoronoiDiagramBuilder builder;
		GeometryFactory geomFact;

		builder.setSites(*sites);
		results=builder.getDiagram(geomFact);

//		std::string out = writer.write(results.get());

	//	std::cout << out << endl;
		results->normalize();
		expected->normalize();
			
		ensure(results->equalsExact(expected, 1e-7));
//		ensure(results->getCoordinateDimension() == expected->getCoordinateDimension());

		delete sites;
		delete expected;
	}

	// Test Cases
	// 1 - test
	template<>
	template<>
	void object::test<1>()
	{
		const char *wkt = "MULTIPOINT ((71,85) , (130,150) , (130,160) )";
		const char *expected = "GEOMETRYCOLLECTION (POLYGON ((2 16, 2 206.9076923076923, 97.15282392026577 120.53820598006644, 135.02898550724638 16, 2 16)), POLYGON ((2 206.9076923076923, 2 219, 209 219, 209 148.5, 97.15282392026577 120.53820598006644, 2 206.9076923076923)),POLYGON ((209 148.5, 209 16, 135.02898550724638 16, 97.15282392026577 120.53820598006644, 209 148.5)))";

		runVoronoi(wkt,expected);
		
		/*		
		//Create a subdivision centered at (0,0)
		QuadEdgeSubdivision sub(Envelope(-100, 100, -100, 100), .00001);
		//make a triagulaor to work on sub
		IncrementalDelaunayTriangulator triangulator(&sub);

		triangulator.insertSite(Vertex(0, 0));

		//extract the triangles from the subdivision
		GeometryFactory geomFact;
		std::auto_ptr<GeometryCollection> tris = sub.getTriangles(geomFact);
*/	}

} // namespace tut

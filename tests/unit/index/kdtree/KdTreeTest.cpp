// 
// Test Suite for geos::index::kdtree::KdTree class.

#include <tut.hpp>
// geos
#include <geos/index/kdtree/KdNode.h>
#include <geos/index/kdtree/KdTree.h>
#include <geos/geom/Coordinate.h>
#include <geos/geom/Envelope.h>
#include <vector>

using namespace std;
using geos::geom::Coordinate;
using geos::geom::Envelope;
using namespace geos::index::kdtree;

namespace tut
{
	// dummy data, not used
	struct test_kdtree_data {};

	typedef test_group<test_kdtree_data> group;
	typedef group::object object;

	group test_kdtree_group("geos::index::kdtree::KdTree");

	//
	// Test Cases
	//

	// 1 - Test 
	template<>
	template<>
	void object::test<1>()
	{
		//ROOT
		KdTree tree(0);

		ensure_equals(tree.isEmpty(),1);
		
		//Inserting Coordinates:
		tree.insert(Coordinate(101,10));
		tree.insert(Coordinate(210,10));
		tree.insert(Coordinate(50,50));
		tree.insert(Coordinate(70,30));
		tree.insert(Coordinate(1000,1000));

		//Querying over the tree:
		Envelope env(0,500,0,500);
		vector<KdNode*> found_Node;
		tree.query(env,found_Node);
	
		vector<Coordinate> result;
		
		for(vector<KdNode*>::iterator it=found_Node.begin() ; it!=found_Node.end() ; ++it)
		{
			cout << (*it)->getX() << " " << (*it)->getY() << endl;
			result.push_back(Coordinate( (*it)->getX(), (*it)->getY() ));
		}
		ensure_equals(result[0].equals(Coordinate(70,30)), 1);
		ensure_equals(result[1].equals(Coordinate(50,50)), 1);
		ensure_equals(result[2].equals(Coordinate(101,10)), 1);
		ensure_equals(result[3].equals(Coordinate(210,10)), 1);
	}
} // namespace tut


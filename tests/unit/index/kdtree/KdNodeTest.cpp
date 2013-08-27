// 
// Test Suite for geos::index::kdtree::KdNode class.

#include <tut.hpp>
// geos
#include <geos/index/kdtree/KdNode.h>
#include <geos/geom/Coordinate.h>

using geos::geom::Coordinate;
using namespace geos::index::kdtree;

namespace tut
{
	// dummy data, not used
	struct test_kdnode_data {};

	typedef test_group<test_kdnode_data> group;
	typedef group::object object;

	group test_kdnode_group("geos::index::kdtree::KdNode");

	//
	// Test Cases
	//

	// 1 - Test 
	template<>
	template<>
	void object::test<1>()
	{
		Coordinate c(101,10);
		int data = 10; 
		KdNode node(c,(void*)(&data));

		ensure_equals(node.getX(),101);
		ensure_equals(node.getY(),10);
//		cout << node.getX() << " " << node.getY()  << (int)node.getData()<< endl;

		KdNode *leftNode = new KdNode(1,1,(void*)(&data));

		KdNode *rightNode = new KdNode(201,15,(void*)(&data));

		node.setLeft(leftNode);
		node.setRight(rightNode);
		node.increment();
		node.increment();

		ensure_equals(node.getCount(),3);
//		cout << node.getCount() << endl;

		KdNode *left = node.getLeft();
		KdNode *right = node.getRight();

		ensure_equals(left->getX(),1);
		ensure_equals(left->getY(),1);
		
		ensure_equals(right->getX(),201);
		ensure_equals(right->getY(),15);
//		cout << left->getX() << " " << left->getY()  << endl;
//		cout << right->getX() << " " << right->getY()  << endl;
	}


} // namespace tut


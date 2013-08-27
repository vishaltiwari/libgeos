#include <geos/index/kdtree/KdNode.h>
#include <geos/index/kdtree/KdTree.h>
#include <geos/geom/Coordinate.h>
#include <iostream>

using namespace std;
using geos::geom::Coordinate;
using namespace geos::index::kdtree;
int main()
{
	//ROOT
	Coordinate c(101,10);
	int data = 10;
	KdNode node(c,(void*)(&data));
	cout << node.getX() << " " << node.getY()  << (int)node.getData()<< endl;

	KdNode *leftNode = new KdNode(1,1,(void*)(&data));
	
	KdNode *rightNode = new KdNode(201,1,(void*)(&data));
	
	node.setLeft(leftNode);
	node.setRight(rightNode);
	node.increment();
	node.increment();

	cout << node.getCount() << endl;

	KdNode *left = node.getLeft();
	KdNode *right = node.getRight();

	cout << left->getX() << " " << left->getY()  << endl;
	cout << right->getX() << " " << right->getY()  << endl;
}

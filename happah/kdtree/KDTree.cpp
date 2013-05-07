#include "KDTree.h"

KDTree::KDTree(TriangleMesh3D_ptr triangleMesh, hpuint maxTrianglesPerBox) {
	vector<hpvec3>* verticesAndNormals = triangleMesh->getVerticesAndNormals();
	vector<hpuint>* indices = triangleMesh->getIndices();

	vector<Triangle>* result = new vector<Triangle>();
	result->reserve(indices->size() / 3);
	for(size_t i = 0; i < indices->size(); i += 3){
		Triangle t = Triangle(verticesAndNormals->at(2 * indices->at(i)),
							  verticesAndNormals->at(2 * indices->at(i+1)),
							  verticesAndNormals->at(2 * indices->at(i+2)));

		result->push_back(t);
	}

	for (std::vector<Triangle>::iterator t = result->begin(); t != result->end(); t++)
	      m_bBox.addTriangle(*t);

	// Create root node
	m_root = new KDTreeInnerNode(result, m_bBox, 0, maxTrianglesPerBox);
}

KDTree::~KDTree(){
	delete m_root;
}

bool KDTree::intersectAll(Circle& intersector, std::list<CircleHitResult>* hitResults) {
  BBox intersectorBox = intersector.computeBoundingBox();
  return m_root->intersectAll(intersector, hitResults, intersectorBox, 0);
}

hpreal KDTree::intersectFirst(Ray& intersector, hpreal maxLength){
	return m_root->intersectFirst(intersector, maxLength);
}

hpuint KDTree::countTriangles() {
	return m_root->countTriangles();
}

/*
 * BasicRack.h
 *
 *  Created on: Dez 5, 2012
 *      Author: julian
 */

#include "happah/geometries/Disc.h"


// Constructor for a general gear. Gears are always centered on 0,0,0 with the z axis being the gear axis.
Disc::Disc(hpreal radius): Geometry(){
    m_radius = radius; // doppelt so groß wie ein zahn
    m_standardProfile = NULL;
    updateValues();
}

Disc::~Disc() {
    delete m_standardProfile;
}

// Create a profile of height values
void Disc::createHeightProfile() {
    m_heightProfile = std::vector<glm::vec2>();
    m_heightProfile.resize(SEGMENT_COUNT);
    hpreal x = m_length / 2.0;
    hpreal deltaX = m_length/(double)SEGMENT_COUNT;
    for( int i = 0; i < SEGMENT_COUNT; i++){
        m_heightProfile[i].x = x;
        m_heightProfile[i].y = m_standardProfile->getHeight(x) + m_module;
        x += deltaX;
    }
}

// This creates the quads for a gear. The gear axis is the model's z-axis.
std::vector<glm::vec4> Disc::createVertexData() {
    std::vector<glm::vec4> vertexData;

    float dalpha = 2 * M_PI / Z_DETAIL_LEVEL;

    // Create the height profile given the current gear settings
    createHeightProfile();


    // draw the sides (german: Mantelflaechen) of the gear
    // this is the important part where the height profile will come into play
    for (int i = 0; i < Z_DETAIL_LEVEL; i++) {
        hpreal alpha1 = i * dalpha;
        hpreal sinAlpha1 = sin(alpha1);
        hpreal cosAlpha1 = cos(alpha1);
        hpreal alpha2 = alpha1 + dalpha;
        hpreal sinAlpha2 = sin(alpha2);
        hpreal cosAlpha2 = cos(alpha2);
        for (unsigned int segmentNum = 0; segmentNum < m_heightProfile.size()-1;
                segmentNum++) {

            glm::vec4 a, b, c, d, normNext, norm;

            a.x = m_heightProfile[segmentNum+1].x;
            a.y = sinAlpha1 * m_heightProfile[segmentNum+1].y;
            a.z = cosAlpha1 * m_heightProfile[segmentNum+1].y;
            a.w = 1.0f;

            b.x = m_heightProfile[segmentNum].x;
            b.y = sinAlpha1 * m_heightProfile[segmentNum].y;
            b.z = cosAlpha1 * m_heightProfile[segmentNum].y;
            b.w = 1.0f;

            c.x = m_heightProfile[segmentNum].x;
            c.y = sinAlpha2 * m_heightProfile[segmentNum].y;
            c.z = cosAlpha2 * m_heightProfile[segmentNum].y;
            c.w = 1.0f;

            d.x = m_heightProfile[segmentNum+1].x;
            d.y = sinAlpha2 * m_heightProfile[segmentNum+1].y;
            d.z = cosAlpha2 * m_heightProfile[segmentNum+1].y;
            d.w = 1.0f;

            /*norm = glm::vec4(
                    glm::normalize(
                            glm::cross(glm::vec3(0.0f, 0.0f, c.z - b.z),
                                    glm::vec3(a.x - b.x, a.y - b.y, 0.0f))),
                    1.0f);*/
            glm::vec3 tempNorm = glm::cross( (glm::vec3)(a - b), (glm::vec3)(c - b));
            norm.x = tempNorm.x;
            norm.y = tempNorm.y;
            norm.z = tempNorm.z;
            norm.w = 1.0f;
            norm = glm::normalize(norm);




            vertexData.push_back(a);
            //dataPushback(normNext);
            vertexData.push_back(norm);
            vertexData.push_back(b);
            vertexData.push_back(norm);
            vertexData.push_back(c);
            vertexData.push_back(norm);
            vertexData.push_back(d);
            //dataPushback(normNext);
            vertexData.push_back(norm);
        }
    }
    return vertexData;
}

hpreal Disc::getRadius() {
    return m_radius;
}

void Disc::setRadius(hpreal radius){
	m_radius = radius;
	updateValues();
}

TriangleMesh* Disc::toTriangleMesh(){
	// This creates the quads for a gear. The gear axis is the model's z-axis.
	std::vector<hpvec3> *vertexData = new std::vector<hpvec3>;
	std::vector<hpuint> *indices = new std::vector<hpuint>;
	hpvec3 wildcardNormal = hpvec3(0.0f, 0.0f, 0.0f);

	float dalpha = 2 * M_PI / Z_DETAIL_LEVEL;

	// Create the height profile given the current disc settings
	createHeightProfile();

	vertexData->reserve(Z_DETAIL_LEVEL * m_heightProfile.size() *2);
	for (int i = 0; i <= Z_DETAIL_LEVEL; i++) {
		for (unsigned int j = 0; j < m_heightProfile.size();j++) {
			vertexData->push_back(hpvec3(m_heightProfile[j].x,
										sin(i * dalpha) * m_heightProfile[j].y,
										cos(i * dalpha) * m_heightProfile[j].y));
			vertexData->push_back(wildcardNormal);

			if(i != Z_DETAIL_LEVEL) {
				hpuint jNext = (j == m_heightProfile.size() - 1) ? 0 : (j + 1);

				indices->push_back(i * m_heightProfile.size() + jNext);		//0
				indices->push_back(i * m_heightProfile.size() + j);			//1
				indices->push_back((i + 1) * m_heightProfile.size() + j);	//2

				indices->push_back(i * m_heightProfile.size() + jNext);		//0
				indices->push_back((i + 1) * m_heightProfile.size() + j);	//2
				indices->push_back((i + 1) * m_heightProfile.size() + jNext);//3
			}
		}
	}

	//TODO Compute normals

	//insert correct smoothed normals:

	//6 entries per two triangles in indices
	uint indicesInRow = indices->size() / Z_DETAIL_LEVEL;
	uint trianglePairsInRow  = indicesInRow / 6;

	//array steps is necessary to walk in the vertexData array to the right places
	int steps[] = {0, 3, 4, -(indicesInRow - 3), -2, -3};

	// go one step further in width direction to reach all points
	for(uint i = 0; i < Z_DETAIL_LEVEL; ++i) {
		for (uint j = 0; j < trianglePairsInRow; ++j) {
			//calculate not normalized normals of the 6
			//surrounding triangles and sum their area
			//for every point of the gear profile
			hpvec3 normal = hpvec3(0.0f);
			int n = i * indicesInRow + j * 6;
			for (uint k = 0; k < 6; ++k) {
				int da, db; //distances in vertexData array to other two triangle points
				if(k < 2) {
					da = 2; db = 1;
				} else if (k < 4) {
					da = -1; db = 1;
				} else {
					da = -1; db = -2;
				}

				//TODO: n ist int und wird mit uint verglichen! => static_cast???
				n += steps[k];
				if (k == 2 && j == trianglePairsInRow - 1)
					n -= indicesInRow;
				//not every point has 6 surrounding triangles. Use only the ones available:
				if (n >= 0 && n < indices->size()) {
					hpvec3 a = vertexData->at(2 * indices->at(n + da)) - vertexData->at(2 * indices->at(n));
					hpvec3 b = vertexData->at(2 * indices->at(n + db)) - vertexData->at(2 * indices->at(n));
					normal = normal + (hpvec3(glm::cross(a, b)));
				}
			}
			n = i * indicesInRow + j * 6;
			for (uint k = 0; k < 6; ++k) {
				n += steps[k];
				if (k == 2 && j == trianglePairsInRow - 1)
					n -= indicesInRow;
				//not every point has 6 surrounding triangles. Use only the ones available:
				if (n >= 0 && n < indices->size())
					vertexData->at(2 * indices->at(n) + 1) = glm::normalize(normal); //insert the normal in the cell after the vertex
			}
		}
	}

	return new TriangleMesh(vertexData, indices);
}

void Disc::updateValues(){
    m_module = m_radius / 2.0;
    m_length = m_module * M_PI;
    if( m_standardProfile != NULL )
    	delete m_standardProfile;
    m_standardProfile = new StandardProfile(m_module, 30 / 180.0 * M_PI, 0, 0);
}



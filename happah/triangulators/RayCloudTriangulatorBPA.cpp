#include "RayCloudTriangulatorBPA.h"
#include <stdio.h>

const float RayCloudTriangulatorBPA::EPSILON = 0.00000001;


RayCloudTriangulatorBPA::RayCloudTriangulatorBPA(hpreal radius) : m_radius(radius), m_diameter(2 * radius) {}

RayCloudTriangulatorBPA::~RayCloudTriangulatorBPA() {}

TriangleMesh3D* RayCloudTriangulatorBPA::triangulate(const RayCloud3D& rays) {
	m_RaySize = rays.size();
	initializeGrid(rays);

	hpvec3 point1, point2, point3;

	if (searchSeedTriangle(rays, point1, point2, point3)) {
		//TODO BPA
	} else {
		return 0;
	}
	
	return 0;
}

void RayCloudTriangulatorBPA::getNearVoxels(const hpvec3 point, unsigned int voxels[]) {

		hpvec3 voxel_coordinates = (point - m_MinVec) / m_diameter;
		

		voxels[0] = (int)(voxel_coordinates.x - 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y - 0.5) * m_nZvoxels + (int)(voxel_coordinates.z - 0.5);
		voxels[1] = (int)(voxel_coordinates.x - 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y - 0.5) * m_nZvoxels + (int)voxel_coordinates.z;
		voxels[2] = (int)(voxel_coordinates.x - 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y - 0.5) * m_nZvoxels + (int)(voxel_coordinates.z + 0.5);

		voxels[3] = (int)(voxel_coordinates.x - 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)voxel_coordinates.y * m_nZvoxels + (int)(voxel_coordinates.z - 0.5);
		voxels[4] = (int)voxel_coordinates.x * m_nYvoxels * m_nZvoxels + 
				(int)voxel_coordinates.y * m_nZvoxels + (int)voxel_coordinates.z;
		voxels[5] = (int)(voxel_coordinates.x - 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)voxel_coordinates.y * m_nZvoxels + (int)(voxel_coordinates.z + 0.5);

		voxels[6] = (int)(voxel_coordinates.x - 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y + 0.5) * m_nZvoxels + (int)(voxel_coordinates.z - 0.5);
		voxels[6] = (int)(voxel_coordinates.x - 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y + 0.5) * m_nZvoxels + (int)voxel_coordinates.z;
		voxels[8] = (int)(voxel_coordinates.x - 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y + 0.5) * m_nZvoxels + (int)(voxel_coordinates.z + 0.5);

		voxels[9] = (int)voxel_coordinates.x * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y - 0.5) * m_nZvoxels + (int)(voxel_coordinates.z - 0.5);
		voxels[10] = (int)voxel_coordinates.x * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y - 0.5) * m_nZvoxels + (int)voxel_coordinates.z;
		voxels[11] = (int)voxel_coordinates.x * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y - 0.5) * m_nZvoxels + (int)(voxel_coordinates.z + 0.5);

		voxels[12] = (int)voxel_coordinates.x * m_nYvoxels * m_nZvoxels + 
				(int)voxel_coordinates.y * m_nZvoxels + (int)(voxel_coordinates.z - 0.5);
		voxels[13] = (int)voxel_coordinates.x * m_nYvoxels * m_nZvoxels + 
				(int)voxel_coordinates.y * m_nZvoxels + (int)voxel_coordinates.z;
		voxels[14] = (int)voxel_coordinates.x * m_nYvoxels * m_nZvoxels + 
				(int)voxel_coordinates.y * m_nZvoxels + (int)(voxel_coordinates.z + 0.5);

		voxels[15] = (int)voxel_coordinates.x * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y + 0.5) * m_nZvoxels + (int)(voxel_coordinates.z - 0.5);
		voxels[16] = (int)voxel_coordinates.x * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y + 0.5) * m_nZvoxels + (int)voxel_coordinates.z;
		voxels[17] = (int)voxel_coordinates.x * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y + 0.5) * m_nZvoxels + (int)(voxel_coordinates.z + 0.5);

		voxels[18] = (int)(voxel_coordinates.x + 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y - 0.5) * m_nZvoxels + (int)(voxel_coordinates.z - 0.5);
		voxels[19] = (int)(voxel_coordinates.x + 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y - 0.5) * m_nZvoxels + (int)voxel_coordinates.z;
		voxels[20] = (int)(voxel_coordinates.x + 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y - 0.5) * m_nZvoxels + (int)(voxel_coordinates.z + 0.5);
	
		voxels[21] = (int)(voxel_coordinates.x + 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)voxel_coordinates.y * m_nZvoxels + (int)(voxel_coordinates.z - 0.5);
		voxels[22] = (int)(voxel_coordinates.x + 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)voxel_coordinates.y * m_nZvoxels + (int)voxel_coordinates.z;
		voxels[23] = (int)(voxel_coordinates.x + 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)voxel_coordinates.y * m_nZvoxels + (int)(voxel_coordinates.z + 0.5);

		voxels[24] = (int)(voxel_coordinates.x + 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y + 0.5) * m_nZvoxels + (int)(voxel_coordinates.z - 0.5);
		voxels[25] = (int)(voxel_coordinates.x + 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y + 0.5) * m_nZvoxels + (int)voxel_coordinates.z;
		voxels[26] = (int)(voxel_coordinates.x + 0.5) * m_nYvoxels * m_nZvoxels + 
				(int)(voxel_coordinates.y + 0.5) * m_nZvoxels + (int)(voxel_coordinates.z + 0.5);
}

bool RayCloudTriangulatorBPA::searchSeedTriangle(const RayCloud3D& rays, hpvec3& point1, hpvec3& point2, hpvec3& point3) {	
	
	for (unsigned int i = 0; i < m_RaySize; i += 2) {
		//TODO prüfe ob bereits verwendet
		int results[3];
		results[0] = i;
		bool stop = false;
		unsigned int results_index = 1;
		
		unsigned int nearVoxels[27];
		getNearVoxels(rays[i], nearVoxels);

		for (unsigned int h = 0; h < 27; ++h) {
			printf("%d\n", nearVoxels[h]);
		}
				
		for (unsigned int n = 0; !stop && n < 27 && nearVoxels[n] < m_GridSize; ++n) {

			//printf("Block: %d\n", nearVoxels[n]);	

			if (grid[nearVoxels[n]] != -1) {
				//printf("Punkt x:%f y:%f z:%f\n", rays[grid[n]].x, rays[grid[n]].y, rays[grid[n]].z);
				
				hpvec3 diff = rays[i] - rays[grid[nearVoxels[n]]];
				if (glm::length(diff) <= m_radius && grid[nearVoxels[n]] != i) {
					results[results_index] = grid[nearVoxels[n]];
					if (++results_index == 3) {
						stop = true;
					}
				}
			
				int c = grid[nearVoxels[n]] >> 1;
				while (!stop && nexts[c] != -1) {
					//printf("Punkt x:%f y:%f z:%f\n", rays[nexts[c]].x, rays[nexts[c]].y, rays[nexts[c]].z);
					diff = rays[i] - rays[nexts[c]];

					if (glm::length(diff) <= m_radius && nexts[c] != i) {
						results[results_index] = nexts[c];
						if (++results_index == 3) {
							stop = true;
						}
					}

					c = nexts[c] >> 1;
				}

				//printf("res_index:%d\n", results_index);
			}
			//printf("\n");
		}

		if (stop) {
		
			printf("Point1 x:%f y:%f z:%f\n", rays[results[0]].x, rays[results[0]].y, rays[results[0]].z);
			printf("Point2 x:%f y:%f z:%f\n", rays[results[1]].x, rays[results[1]].y, rays[results[1]].z);
			printf("Point3 x:%f y:%f z:%f\n", rays[results[2]].x, rays[results[2]].y, rays[results[2]].z);
			
			continue;
			
			bool valid = true;
			hpvec3 center1, center2;

			//hpvec3 outerCenter = tRay<T>::isInHalfspace(res1) ? center1 : center2;
			hpvec3 outerCenter;

			unsigned int nearVoxelsToCenter[27];
			getNearVoxels(outerCenter, nearVoxelsToCenter);

			for (unsigned int j = 0; valid && j < 27 && j < m_GridSize; ++j) {
				
				if (grid[nearVoxelsToCenter[j]] != -1) {
					hpvec3 diffCenter = rays[i] - rays[grid[nearVoxelsToCenter[j]]];
					if (glm::length(diffCenter) <= m_radius && grid[nearVoxelsToCenter[j]] != 	results[0] && grid[nearVoxelsToCenter[j]] != results[1] && grid[nearVoxelsToCenter[j]] != results[2]) {
						valid = false;
					}
				

					int k = grid[nearVoxelsToCenter[j]] >> 1;
					while (valid && nexts[k] != -1) {
						diffCenter = rays[i] - rays[nexts[k]];
					
						if (glm::length(diffCenter) <= m_radius && nexts[k] != results[0] 	&& nexts[k] != results[0] && nexts[k] != results[0]) {
							valid = false;
						}			

					}
				}
			}
			
			if (valid) {
				point1 = rays[results[0]];
				point2 = rays[results[1]];
				point3 = rays[results[2]];
				
				return true;
			}
		}
	}

	return false;
}

void RayCloudTriangulatorBPA::testSeedTriangle(const hpvec3& point1, const hpvec3& point2, const hpvec3& point3) {
	printf("Punkt 1 x:%f y:%f z:%f\n", point1.x, point1.y, point1.z);
	printf("Punkt 2 x:%f y:%f z:%f\n", point2.x, point2.y, point2.z);
	printf("Punkt 3 x:%f y:%f z:%f\n\n", point3.x, point3.y, point3.z);

	hpvec3 diff2 = point1 - point2;
	printf("Abstand 1 zu 2: %f\n", (float) glm::length(diff2));
	hpvec3 diff3 = point1 - point3;
	printf("Abstand 1 zu 3: %f\n", (float) glm::length(diff3));
	hpvec3 diff4 = point2 - point3;
	printf("Abstand 2 zu 3: %f\n\n", (float) glm::length(diff4));
	
}

void RayCloudTriangulatorBPA::initializeGrid(const RayCloud3D& rays) {
	m_XMax = numeric_limits<float>::min();
	m_YMax = m_XMax;
	m_ZMax = m_XMax;
	m_XMin = numeric_limits<float>::max();
	m_YMin = m_XMin;
	m_ZMin = m_XMin;
	
	for (unsigned int i = 0; i < m_RaySize; i += 2) {
		m_XMin = min(m_XMin, rays[i].x);
		m_YMin = min(m_YMin, rays[i].y);
		m_ZMin = min(m_ZMin, rays[i].z);
		m_XMax = max(m_XMax, rays[i].x);
		m_YMax = max(m_YMax, rays[i].y);
		m_ZMax = max(m_ZMax, rays[i].z);
	}

	m_MinVec = hpvec3(m_XMin, m_YMin, m_ZMin);

	float xDistance = m_XMax - m_XMin;
	float yDistance = m_YMax - m_YMin;
	float zDistance = m_ZMax - m_ZMin;

	m_nXvoxels = (int) ceil((xDistance / m_diameter) + EPSILON);
	m_nYvoxels = (int) ceil((yDistance / m_diameter) + EPSILON);
	m_nZvoxels = (int) ceil((zDistance / m_diameter) + EPSILON);

	m_GridSize = m_nXvoxels * m_nYvoxels * m_nZvoxels;
	nexts = vector<int>(m_RaySize >> 1, -1);	
	grid = vector<int>(m_GridSize, -1);
	
	unsigned int index;
	for (unsigned int j = 0; j < m_RaySize; j += 2) {
		index = getIndex(rays[j]);		

		if (grid[index] >= 0) {
			nexts[j >> 1] = grid[index];
		}
		grid[index] = j;
	}

	//testGrid(rays);	
}

void RayCloudTriangulatorBPA::testGrid(const RayCloud3D& rays) {

	printf("m_XMin: %f\n", m_XMin);
	printf("m_YMin: %f\n", m_YMin);
	printf("m_ZMin: %f\n\n", m_ZMin);

	printf("m_nXvoxels: %d\n", m_nXvoxels);
	printf("m_nYvoxels: %d\n", m_nYvoxels);
	printf("m_nZvoxels: %d\n\n", m_nZvoxels);


	for (unsigned int k = 0; k < m_GridSize; ++k) {
		unsigned int l = k;
		int x = l / (m_nYvoxels * m_nZvoxels);
		l %= (m_nYvoxels * m_nZvoxels);
		int y = l / m_nZvoxels;
		l %= m_nZvoxels;
		int z = l;	
		
		printf("Voxel x:%d y:%d z:%d\n", x, y, z);

		if (grid[k] == -1) {
			printf("n.a.\n");
		} else {
			printf("Punkt x:%f y:%f z:%f\n", rays[grid[k]].x, rays[grid[k]].y,
			 	rays[grid[k]].z);
			
			int c = grid[k] / 2;
			while (nexts[c] != -1) {
				printf("Punkt x:%f y:%f z:%f\n", rays[nexts[c]].x,
					rays[nexts[c]].y, rays[nexts[c]].z);
				c = nexts[c] / 2;
			}
		}
		printf("\n");
	}
}


unsigned int RayCloudTriangulatorBPA::getIndex(const hpvec3& point) {
	hpvec3 voxel_coordinates = (point - m_MinVec) / m_diameter;

	return (int) voxel_coordinates.x * m_nYvoxels * m_nZvoxels + (int) voxel_coordinates.y * m_nZvoxels + 
		(int) voxel_coordinates.z;
}

TriangleMesh2D* RayCloudTriangulatorBPA::triangulate(const PointCloud2D& pofints, const hpvec3& origin, const hpvec3& normal) {
	//TODO
	return 0;
}

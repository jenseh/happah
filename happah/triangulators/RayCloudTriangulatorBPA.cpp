#include "RayCloudTriangulatorBPA.h"
#include <stdio.h>


RayCloudTriangulatorBPA::RayCloudTriangulatorBPA(hpreal radius) : m_radius(radius) {}

RayCloudTriangulatorBPA::~RayCloudTriangulatorBPA() {}

TriangleMesh3D* RayCloudTriangulatorBPA::triangulate(const RayCloud3D& rays) {
	m_RaySize = rays.size();
	m_diameter = 2 * m_radius;
	initializeGrid(rays);

	hpvec3 point1, point2, point3;

	if (searchSeedTriangle(rays, point1, point2, point3)) {
		//TODO BPA
	} else {
		return 0;
	}
	
	return 0;
}

bool RayCloudTriangulatorBPA::searchSeedTriangle(const RayCloud3D& rays, hpvec3& point1, hpvec3& point2, hpvec3& point3) {

	hpvec3 voxel_coordinates;
	hpvec3 minvec = hpvec3(m_Xmin, m_Ymin, m_Zmin);		
	
	for (unsigned int i = 0; i < m_RaySize; i += 2) {
		//TODO prüfe ob bereits verwendet
		int results[3];
		results[0] = i;
		bool stop = false;
		unsigned int results_index = 1;
		voxel_coordinates = (rays[i] - minvec) / (2 * m_radius);
		hpvec3 old_coordinates(voxel_coordinates);

		

		int possible_index[27];
		int* ptr = possible_index;
		for (int j = -1; j < 2; j++) {
			voxel_coordinates.x += j * 0.5;
			for (int k = -1; k < 2; k++) {
				voxel_coordinates.y += k * 0.5;
				for (int l = -1; l < 2; l++) {
					voxel_coordinates.z += l * 0.5;
					
					*ptr++ = (int)voxel_coordinates.x * m_nYvoxels * m_nZvoxels + 
						(int)voxel_coordinates.y * m_nZvoxels + (int)voxel_coordinates.z;
					
					voxel_coordinates.z = old_coordinates.z;
				}
				voxel_coordinates.y = old_coordinates.y;
			}
			voxel_coordinates.x = old_coordinates.x;
		}
		//printf("Punkt x:%f y:%f z:%f\n", rays[i].x, rays[i].y, rays[i].z);	
				
		for (unsigned int n = 0; !stop && n < 27 && n < grid.size(); n++) {

			//printf("Block: %d\n", n);	

			if (grid[n] != -1) {
				//printf("Punkt x:%f y:%f z:%f\n", rays[grid[n]].x, rays[grid[n]].y,
			 	//rays[grid[n]].z);
				hpvec3 diff = rays[i] - rays[grid[n]];
				if (glm::length(diff) <= m_radius && grid[n] != i) {
					results[results_index] = grid[n];
					if (++results_index == 3) {
						stop = true;
					}
				}
			
				int c = grid[n] / 2;
				while (!stop && nexts[c] != -1) {
					//printf("Punkt x:%f y:%f z:%f\n", rays[nexts[c]].x,
					//srays[nexts[c]].y, rays[nexts[c]].z);
					diff = rays[i] - rays[nexts[c]];

					if (glm::length(diff) <= m_radius && nexts[c] != i) {
						results[results_index] = nexts[c];
						if (++results_index == 3) {
							stop = true;
						}
					}

					c = nexts[c] / 2;
				}
			}
			//printf("\n");
		}

		if (stop) {
		
			hpvec3 normal1 = rays[results[0] + 1];
			hpvec3 normal2 = rays[results[1] + 1];
			hpvec3 normal3 = rays[results[2] + 1];
			hpvec3 triangle_normal = glm::cross(rays[results[1]] - rays[results[0]], rays[results[2]] - rays[results[0]]);

			testSeedTriangle(rays[results[0]], rays[results[1]], rays[results[2]]);

			if (glm::dot(triangle_normal, normal1) > 0 && glm::dot(triangle_normal, normal2) > 0 && glm::dot(triangle_normal, normal3) > 0) {
			
				//TODO 

			}
		}
	}

	return true;
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
	m_Xmax = numeric_limits<float>::max();
	m_Ymax = m_Xmax;
	m_Zmax = m_Xmax;
	m_Xmin = numeric_limits<float>::min();
	m_Ymin = m_Xmin;
	m_Zmin = m_Xmin;
	
	for (unsigned int i = 0; i < m_RaySize; i += 2) {
		m_Xmin = min(m_Xmin, rays[i].x);
		m_Ymin = min(m_Ymin, rays[i].y);
		m_Zmin = min(m_Zmin, rays[i].z);
		m_Xmax = max(m_Xmax, rays[i].x);
		m_Ymax = max(m_Ymax, rays[i].y);
		m_Zmax = max(m_Zmax, rays[i].z);
	}

	float x_distance = m_Xmax - m_Xmin;
	float y_distance = m_Ymax - m_Ymin;
	float z_distance = m_Zmax - m_Zmin;

	m_nXvoxels = (int) ceil(x_distance / m_diameter);
	m_nYvoxels = (int) ceil(y_distance / m_diameter);
	m_nZvoxels = (int) ceil(z_distance / m_diameter);

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

	printf("m_Xmin: %f\n", m_Xmin);
	printf("m_Ymin: %f\n", m_Ymin);
	printf("m_Zmin: %f\n\n", m_Zmin);

	printf("m_nXvoxels: %d\n", m_nXvoxels);
	printf("m_nYvoxels: %d\n", m_nYvoxels);
	printf("m_nZvoxels: %d\n\n", m_nZvoxels);


	for (unsigned int k = 0; k < grid.size(); k++) {
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
	hpvec3 voxel_coordinates = (point - hpvec3(m_Xmin, m_Ymin, m_Zmin)) / m_diameter;

	return (int) voxel_coordinates.x * m_nYvoxels * m_nZvoxels + (int) voxel_coordinates.y * m_nZvoxels + 
		(int) voxel_coordinates.z;
}

TriangleMesh2D* RayCloudTriangulatorBPA::triangulate(const PointCloud2D& pofints, const hpvec3& origin, const hpvec3& normal) {
	//TODO
	return 0;
}

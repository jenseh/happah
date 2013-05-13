#include "RayCloudTriangulatorBPA.h"
#include <stdio.h>


RayCloudTriangulatorBPA::RayCloudTriangulatorBPA(hpreal radius) : m_radius(radius), 
	FLOAT_MIN(numeric_limits<float>::min()), FLOAT_MAX(numeric_limits<float>::max()) {}

RayCloudTriangulatorBPA::~RayCloudTriangulatorBPA() {}

TriangleMesh* RayCloudTriangulatorBPA::triangulate(const RayCloud3D& rays) {
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

	using namespace glm; {

	hpvec3 voxel_coordinates;
	unsigned int rays_size = rays.size();
	hpvec3 minvec = hpvec3(x_min, y_min, z_min);	
	
	
	for (unsigned int i = 0; i < rays_size; i += 2) {
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
					
					*ptr++ = (int)voxel_coordinates.x * y_voxels * z_voxels + 
						(int)voxel_coordinates.y * z_voxels + (int)voxel_coordinates.z;
					
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
				if (length(diff) <= m_radius && grid[n] != i) {
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

					if (length(diff) <= m_radius && nexts[c] != i) {
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
			hpvec3 triangle_normal = cross(rays[results[1]] - rays[results[0]], rays[results[2]] - rays[results[0]]);

			testSeedTriangle(rays[results[0]], rays[results[1]], rays[results[2]]);

			if (dot(triangle_normal, normal1) > 0 && dot(triangle_normal, normal2) > 0 && dot(triangle_normal, normal3) > 0) {
			
				//TODO 

			}
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

	hpvec3 sa = 0.5 * sqrt(2.0 * ((point3 - point1) * (point3 - point1) + (point2 - point1) * (point2 - point1)) - 
		(point2 - point3) * (point2 - point3)));


	/*
	hpvec3 mitte12 = (point2 - point1);
	hpvec3 mitte13 = (point3 - point1);
	hpvec3 average = (mitte12 + mitte13) / (float) 2.0;
	
	printf("Mitte 1 - 2 x:%f y:%f z:%f\n", mitte12.x, mitte12.y, mitte12.z);
	printf("Mitte 1 - 3 x:%f y:%f z:%f\n", mitte13.x, mitte13.y, mitte13.z);
	printf("Average x:%f y:%f z:%f\n\n", average.x, average.y, average.z);


	hpvec3 mitte23 = (point3 - point2);
	hpvec3 mitte21 = (point1 - point2);
	hpvec3 average2 = (mitte23 + mitte21) / (float) 2.0;

	printf("Mitte 2 - 3 x:%f y:%f z:%f\n", mitte23.x, mitte23.y, mitte23.z);
	printf("Mitte 2 - 1 x:%f y:%f z:%f\n", mitte21.x, mitte21.y, mitte21.z);
	printf("Average 2 x:%f y:%f z:%f\n\n", average2.x, average2.y, average2.z);

	float divisor = ((average2.x * average.y) - (average2.y * average.x));
	float c, k;
	
	if (divisor == 0.0) {
		printf("TODO Divisor 0.");
	} else {
		c = (((point2.x - point1.x) * -1 * average.y) + (average.x * 
			(point2.y - point1.y))) / divisor;
		if (average.x != 0.0) {
			k = ((point2.x - point1.x) + (c * average2.x)) / average.x;
		} else if (average.y != 0.0) {
			k = ((point2.y - point1.y) + (c * average2.y)) / average.y;
		} else {
			printf("TODO average.x und average.y sind 0.");
		}
	}

	printf("c: %f k: %f test: %f\n", c, k, divisor);

	printf("Check x: %f == %f\n", point1.x + k * average.x, point2.x + c * average2.x);
	printf("Check y: %f == %f\n", point1.y + k * average.y, point2.y + c * average2.y);
	printf("Check z: %f == %f\n", point1.z + k * average.z, point2.z + c * average2.z);

	printf("Test2\n\n");	

	hpvec3 mitte31 = (point1 - point3);
	hpvec3 mitte32 = (point2 - point3);
	hpvec3 average3 = (mitte31 + mitte32) / (float) 2.0;

	printf("Mitte 3 - 1 x:%f y:%f z:%f\n", mitte31.x, mitte31.y, mitte31.z);
	printf("Mitte 3 - 2 x:%f y:%f z:%f\n", mitte32.x, mitte32.y, mitte32.z);
	printf("Average 3 x:%f y:%f z:%f\n\n", average3.x, average3.y, average3.z);

	divisor = ((average3.x * average.y) - (average3.y * average.x));
	
	if (divisor == 0.0) {
		printf("TODO Divisor 0.");
	} else {
		c = (((point3.x - point1.x) * -1 * average.y) + (average.x * 
			(point3.y - point1.y))) / divisor;
		if (average.x != 0.0) {
			k = ((point3.x - point1.x) + (c * average3.x)) / average.x;
		} else if (average.y != 0.0) {
			k = ((point3.y - point1.y) + (c * average3.y)) / average.y;
		} else {
			printf("TODO average.x und average.y sind 0.");
		}
	}

	printf("c: %f k: %f test: %f\n", c, k, divisor);
	
	float blah = point3.x + (c * average3.x);
	
	printf("x3: %f c: %f a3.x: %f res = %f\n", point3.x, c, average3.x, blah);

	printf("Check x: %f == %f\n", point1.x + k * average.x, point3.x + c * average3.x);
	printf("Check y: %f == %f\n", point1.y + k * average.y, point3.y + c * average3.y);
	printf("Check z: %f == %f\n\n", point1.z + k * average.z, point3.z + c * average3.z);
	

	hpvec3 triangle_normal = glm::cross(point2 - point1, point3 - point1);

	printf("Normale x: %f y: %f z: %f\n\n", triangle_normal.x, triangle_normal.y, triangle_normal.z);
	*/


	
}

void RayCloudTriangulatorBPA::initializeGrid(const RayCloud3D& rays) {
	x_max = FLOAT_MIN;
	y_max = FLOAT_MIN;
	z_max = FLOAT_MIN;
	x_min = FLOAT_MAX;
	y_min = FLOAT_MAX;
	z_min = FLOAT_MAX;

	unsigned int rays_size = rays.size();
	for (unsigned int i = 0; i < rays_size; i += 2) {
		x_min = min(x_min, rays[i].x);
		y_min = min(y_min, rays[i].y);
		z_min = min(z_min, rays[i].z);
		x_max = max(x_max, rays[i].x);
		y_max = max(y_max, rays[i].y);
		z_max = max(z_max, rays[i].z);
	}

	float x_distance = x_max - x_min;
	float y_distance = y_max - y_min;
	float z_distance = z_max - z_min;

	x_voxels = (int) ceil(x_distance / (2 * m_radius));
	y_voxels = (int) ceil(y_distance / (2 * m_radius));
	z_voxels = (int) ceil(z_distance / (2 * m_radius));

	int grid_size = x_voxels * y_voxels * z_voxels;
	nexts = vector<int>(rays_size / 2, -1);	
	grid = vector<int>(grid_size, -1);
	
	int index;
	for (unsigned int j = 0; j < rays_size; j += 2) {
		index = getIndex(rays[j]);

		if (grid[index] >= 0) {
			nexts[j / 2] = grid[index];
		}
		grid[index] = j;
	}

	//testGrid(rays);	
}

void RayCloudTriangulatorBPA::testGrid(const RayCloud3D& rays) {

	printf("x_min: %f\n", x_min);
	printf("y_min: %f\n", y_min);
	printf("z_min: %f\n\n", z_min);

	printf("x_voxels: %d\n", x_voxels);
	printf("y_voxels: %d\n", y_voxels);
	printf("z_voxels: %d\n\n", z_voxels);


	for (unsigned int k = 0; k < grid.size(); k++) {
		unsigned int l = k;
		int x = l / (y_voxels * z_voxels);
		l %= (y_voxels * z_voxels);
		int y = l / z_voxels;
		l %= z_voxels;
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


int RayCloudTriangulatorBPA::getIndex(const hpvec3& point) {
	hpvec3 voxel_coordinates = (point - hpvec3(x_min, y_min, z_min)) / (2 * m_radius);

	return (int) voxel_coordinates.x * y_voxels * z_voxels + (int) voxel_coordinates.y * z_voxels + 
		(int) voxel_coordinates.z;
}

TriangleMesh* RayCloudTriangulatorBPA::triangulate(const PointCloud2D& pofints, const hpvec3& origin, const hpvec3& normal) {
	//TODO
	return 0;
}

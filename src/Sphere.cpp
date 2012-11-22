#include <math.h>

#include "Sphere.h"

using namespace std;

Sphere::Sphere(float _radius, QMatrix4x4 *_projectionMatrix,
		QMatrix4x4 *_viewMatrix, QVector3D* _camPos) :
		GeometryObject(_projectionMatrix, _viewMatrix, _camPos) {
	radius = _radius;
}

Sphere::~Sphere() {
}

bool Sphere::hit(glm::vec3 rayPos, glm::vec3 rayDir) {
	float A, B, C;
	A = rayDir.x * rayDir.x + rayDir.y * rayDir.y + rayDir.z * rayDir.z;
	B = 2 * (rayDir.x * rayPos.x + rayDir.y * rayPos.y + rayDir.z * rayPos.z);
	C = rayPos.x * rayPos.x + rayPos.y * rayPos.y + rayPos.z * rayPos.z
			- radius * radius;

	float t0, t1;
	if (!quad(A, B, C, &t0, &t1))
		return false;
	float tmin = glm::min(t0, t1);
	hitpoint = rayPos + tmin * rayDir;

	return true;
}

bool Sphere::quad(float A, float B, float C, float *t0, float *t1) {
	float q;
	float discrim = B * B - 4.0f * A * C;

	if (discrim < 0)
		return false;
	float root = std::sqrt(discrim);
	if (B < 0)
		q = -0.5f * (B - root);
	else
		q = -0.5f * (B + root);
	*t0 = q / A;
	*t1 = C / q;

	if (*t0 > *t1) {
		float temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}
	return true;

}

float Sphere::getRadius() {
	return radius;
}

glm::vec3 Sphere::getHitpoint() {
	return hitpoint;
}

void Sphere::createVertexData() {
	int dtheta = 5;
	int dphi = 5;
	const float toRad = M_PI / 180.0f;
	for (int theta = -90; theta <= 90 - dtheta; theta = theta + dtheta) {
		for (int phi = 0; phi <= 360 - dphi; phi = phi + dphi) {
			glm::vec4 a, b, c, d, normA, normB, normC, normD;
			a.x = cos(theta * toRad) * cos(phi * toRad);
			a.y = cos(theta * toRad) * sin(phi * toRad);
			a.z = sin(theta * toRad);
			a.w = 1.0f;
			normA = glm::normalize(a);

			b.x = cos((theta + dtheta) * toRad) * cos(phi * toRad);
			b.y = cos((theta + dtheta) * toRad) * sin(phi * toRad);
			b.z = sin((theta + dtheta) * toRad);
			b.w = 1.0f;
			normB = glm::normalize(b);

			c.x = cos((theta + dtheta) * toRad) * cos((phi + dphi) * toRad);
			c.y = cos((theta + dtheta) * toRad) * sin((phi + dphi) * toRad);
			c.z = sin((theta + dtheta) * toRad);
			c.w = 1.0f;
			normC = glm::normalize(c);

			d.x = cos(theta * toRad) * cos((phi + dphi) * toRad);
			d.y = cos(theta * toRad) * sin((phi + dphi) * toRad);
			d.z = sin(theta * toRad);
			d.w = 1.0f;
			normD = glm::normalize(d);

			dataPushback(a);
			dataPushback(normA);
			dataPushback(b);
			dataPushback(normB);
			dataPushback(c);
			dataPushback(normC);
			dataPushback(d);
			dataPushback(normD);
		}
	}
}


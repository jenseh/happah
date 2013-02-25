#include "Box.h"



Box::Box()
{
    min 	= bvec(0,0,0);
    max 	= bvec(0,0,0);
    center 	= bvec(0,0,0);
}


Box::Box (const bvec &_min, const bvec &_max)
{
    min = _min;
    max = _max;
}

Box & Box::operator= (const Box &other)
{
    if (this != &other)
    {
        min 	= other.min;
        max 	= other.max;
        center 	= other.center;
    }

    return *this;
}

/**
  * Get the area of the box.
  */
double Box::getArea (void) const
{
    double width  = (max[0] - min[0]);
    double length = (max[1] - min[1]);
    double height = (max[2] - min[2]);
    return 2.0 * (length * width   +
                     length * height +
                     width * height);
}


bool Box::testTriangle (const Triangle& triangle) const
{
    double tri_verts[3][3];
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            tri_verts[i][j] = triangle.vertices[i][j];
        }
    }
    double centerVec[3] = {center.x, center.y, center.z};
    double half_sizeVec[3] = {half_size.x, half_size.y, half_size.z};
    return tribox::triBoxOverlap<double> (centerVec, half_sizeVec, tri_verts);
}


bool Box::testPoint (const bvec &point) const
{
    for (int i = 0; i < 3; ++i)
    {
        if (point[i] > max[i] || point[i] < min[i])
        {
            return false;
        }
    }

    return true;
}


bool Box::testRay (const Ray &ray, double &time) const
{
    double min_time = 0.0, max_time = HUGE_VAL;
    double epsilon = 0.0001;

    // Close-in on the box in each dimension seperately.
    for (size_t d = 0; d < 3; ++d)
    {
        if (ray.direction[d] == 0.0)
        {
            if (ray.origin[d] > max[d] || ray.origin[d] < min[d])
            {
                return false;
            }
        }
        else
        {
            double time1 = (min[d] - epsilon - ray.origin[d]) * ray.inverse_direction[d];
            double time2 = (max[d] + epsilon - ray.origin[d]) * ray.inverse_direction[d];

            if (time1 > time2)
            {
                std::swap (time1, time2);
            }

            min_time = std::max (time1, min_time);
            max_time = std::min (time2, max_time);

            if ((time2 < min_time) || (time1 > max_time))
            {
                return false;
            }
        }
    }

    time = min_time;
    return true;
}


void Box::calcDimensions (void)
{
    for (size_t i = 0; i < 3; ++i)
    {
        center[i] = min[i] + (max[i] - min[i]) * 0.5;
        half_size[i] = fabs (max[i] - min[i]) * 0.5;
    }
}


double Box::calcDistance (bvec& point) const
{
    bvec projected_point = min;
    for (size_t i = 0; i < 3; ++i)
    {
        if (point[i] > max[i])
        {
            projected_point[i] = max[i];
        }

        if (point[i] > min[i] && point[i] < max[i])
        {
            projected_point[i] = point[i];
        }
    }

    return glm::distance (projected_point, point);
}




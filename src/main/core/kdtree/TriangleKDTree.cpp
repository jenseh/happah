#include "TriangleKDTree.h"


TriangleKDTree::TriangleKDTree()
{
    m_root = NULL;
}


TriangleKDTree::~TriangleKDTree()
{
    clear ();
}


void TriangleKDTree::build (TriangleMesh &mesh)
{
    kvec min (HUGE_VAL, HUGE_VAL, HUGE_VAL);
    kvec max (-HUGE_VAL, -HUGE_VAL, -HUGE_VAL);
    m_root = new TriangleKDTreeNode;

    mesh.fillTriangles();

    for (size_t i = 0; i < mesh.getTriangles().size(); ++i)
    {
        for (int j = 0; j < 3; ++j)// Loop over triangle vertices
        {
            for (int k = 0; k < 3; ++k)// Loop over vertex indices.
            {
                max[k] = std::max (max[k], mesh.getTriangles().at(i)->vertices[j][k]);
                min[k] = std::min (min[k], mesh.getTriangles().at(i)->vertices[j][k]);
            }
        }

        //piece->triangles[i].initializeIntersection ();
        m_root->triangles.push_back(mesh.getTriangles().at(i));
    }

    m_root->box = Box (min, max);
    m_root->box.calcDimensions ();
    buildR (m_root, 0);
}


void TriangleKDTree::clear (void)
{
    clearR (m_root);
    m_root = NULL;
}



bool TriangleKDTree::intersect (Ray &ray, IntersectInfo &info, const double tmin)
{
    ray.inverse_direction[0] = 1.0 / ray.direction[0];
    ray.inverse_direction[1] = 1.0 / ray.direction[1];
    ray.inverse_direction[2] = 1.0 / ray.direction[2];
    return intersectR (m_root, ray, tmin, info);
}



void TriangleKDTree::buildR (TriangleKDTreeNode *&node, int current_depth)
{
    if (node == NULL)
    {
        return;
    }

    if (split (node, current_depth))
    {
        buildR (node->left, current_depth + 1);
        buildR (node->right, current_depth + 1);
    }
}


bool TriangleKDTree::sahSplit (TriangleKDTreeNode *&node, int current_depth)
{
    int split_axis = current_depth % 3;
    double best_split_plane = 0.0;
    double traversal_cost = 0.3;
    double intersect_cost = 1.0;
    double best_cost = HUGE_VAL;
    TriangleKDTreeNode *left = new TriangleKDTreeNode;
    TriangleKDTreeNode *right = new TriangleKDTreeNode;
    std::set<double> split_planes; // Set of split planes already tried.
    std::pair <typename std::set <double>::iterator, bool> return_value;
    double parent_area = 1.0 / node->getArea ();

    // Determine the best split plane to use.
    // Loop over the triangles in this node, the split planes are selected as the
    // current split axis of each primitive.
    for (size_t i = 0; i < node->triangles.size (); ++i)
    {
        double split_plane = HUGE_VAL;
        // Find the smallest of the vertices of this triangle.
        for (int j = 0; j < 3; ++j)
        {
            if (node->triangles[i]->vertices[j][split_axis] < split_plane)
            {
                // Make sure that this split plane lies inside of the node.  Because triangles can
                // span multiple nodes, this check is necessary.
                if (node->triangles[i]->vertices[j][split_axis] < node->box.max[split_axis] &&
                    node->triangles[i]->vertices[j][split_axis] > node->box.min[split_axis])
                {
                    split_plane = node->triangles[i]->vertices[j][split_axis];
                }
            }
        }

        if (split_plane != HUGE_VAL)
        {
            return_value = split_planes.insert (split_plane);
            if (return_value.second)
            {
                // We have not yet evaluated this split plane.
                // Make two new nodes that would be children of this node using the current split plane.
                left->box.min = node->box.min;
                left->box.max = node->box.max;
                left->box.max[split_axis] = split_plane;

                right->box.min = node->box.min;
                right->box.max = node->box.max;
                right->box.min[split_axis] = split_plane;

                left->box.calcDimensions ();
                right->box.calcDimensions ();

                int left_count  = left->intersectCount (node->triangles);
                int right_count = right->intersectCount (node->triangles);
                double left_prob = left->getArea () * parent_area;
                double right_prob = right->getArea () * parent_area;

                double cost = traversal_cost + intersect_cost * (left_prob * left_count + right_prob * right_count);
                if (cost < best_cost)
                {
                    best_cost = cost;
                    best_split_plane = split_plane;
                }
            }
        }
    }

    // Now that the best split plane has been found, determine if this cost is less than simply raytracing the node itself.
    if (best_cost < (intersect_cost * node->triangles.size ()))
    {
        left->box.min = node->box.min;
        left->box.max = node->box.max;
        left->box.max[split_axis] = best_split_plane;

        right->box.min = node->box.min;
        right->box.max = node->box.max;
        right->box.min[split_axis] = best_split_plane;

        left->box.calcDimensions ();
        right->box.calcDimensions ();

        // Insert the triangles into the left and right nodes.
        for (size_t i = 0; i < node->triangles.size (); ++i)
        {
            left->insertTriangle (node->triangles[i]);
            right->insertTriangle (node->triangles[i]);
        }

        // Clear the parent node, link it with the children, and finish.
        node->triangles.clear ();
        node->left = left;
        node->right = right;
        return true;
    }

    delete left;
    delete right;
    return false;
}


bool TriangleKDTree::medianSplit (TriangleKDTreeNode *&node, int depth)
{
    // Find the longest axis, this will be the splitting axis.
    double length = 0.0;
    int axis = 0;
    for (int i = 0; i < 3; ++i)
    {
        float tmp = node->box.max[i] - node->box.min[i];
        if (tmp > length)
        {
            length = tmp;
            axis = i;
        }
    }

    float split_plane = (node->box.max[axis] + node->box.min[axis]) * 0.5;
    TriangleKDTreeNode *left = new TriangleKDTreeNode;
    TriangleKDTreeNode *right = new TriangleKDTreeNode;

    left->box.min = node->box.min;
    left->box.max = node->box.max;
    left->box.max[axis] = split_plane;

    right->box.min = node->box.min;
    right->box.max = node->box.max;
    right->box.min[axis] = split_plane;

    left->box.calcDimensions ();
    right->box.calcDimensions ();

    // Add the triangles to the new child nodes.
    for (size_t i = 0; i < node->triangles.size (); ++i)
    {
        bool insert_left = false;
        bool insert_right = false;
        insert_left = left->insertTriangle (node->triangles[i]);
        insert_right = right->insertTriangle (node->triangles[i]);
        /*if (!insert_left && !insert_right)
        {
            std::cout << "triangle missed: " << node->triangles[i]->m_vertices[0] << " " <<
                         node->triangles[i]->m_vertices[1] << " " <<
                         node->triangles[i]->m_vertices[2] << std::endl;
            std::cout << "\tleft, right center = " << left->center << ", " << right->center << std::endl;
            std::cout << "\tleft, right half size = " << left->half_size << ", " << right->half_size << std::endl;
        }*/
    }

    // Check to make sure that the split actually did something.
    if (node->triangles.size () == left->triangles.size () &&
        node->triangles.size () == right->triangles.size ())
    {
        delete left;
        delete right;
        return false;
    }

    if (left->triangles.size () == 0)
    {
        delete left;
        left = NULL;
    }

    if (right->triangles.size () == 0)
    {
        delete right;
        right = NULL;
    }

    node->triangles.clear ();
    node->left = left;
    node->right = right;
    return true;

}


void TriangleKDTree::clearR (TriangleKDTreeNode *&node)
{
    if (node == NULL)
    {
        return;
    }

    clearR (node->left);
    clearR (node->right);
    delete node;
    node = NULL;
}


bool TriangleKDTree::split (TriangleKDTreeNode *&node, int depth)
{
    if (node->triangles.size () > 64)
    {
        return medianSplit (node, depth);
    }

    else if (node->triangles.size () > 32)
    {
        return sahSplit (node, depth);
    }

    return false;
}


bool TriangleKDTree::intersectR (const TriangleKDTreeNode *node, Ray &ray, const double &tmin, IntersectInfo &info)
    {
        if (node == NULL)
        {
            return false;
        }

        double time = 0.0;
        if (node->checkRay (ray, time))
        {
            if (time > info.time)
            {
                // This box is farther away than the previously hit triangle, so we don't care about it.
                return false;
            }

            bool hit = false;
            if (node->isLeaf ())
            {
                time = 0.0;
                // Test the triangles in this node for an intersection.
                for (size_t i = 0; i < node->triangles.size (); ++i)
                {
                    if (node->triangles[i]->checkRayIntersection (ray.origin, ray.direction, time))
                    {
                        if (time >= tmin)
                        {
                            // Ensure that the hitpoint is actually within the bounds of this node.
                            // The triangle could get hit outside of this node since triangles
                            // can span multiple nodes.
                            kvec hit_point = ray.origin + ray.direction * (float)time;
                            //if (node->checkPoint (hit_point))
                            {
                                hit = true;
                                if (time < info.time)
                                {
                                    info.time		= time;
                                    info.hit_point 	= hit_point;
                                    info.triangle	= node->triangles[i];
                                }
                            }
                        }
                    }
                }

                return hit;
            }
        }
        else
        {
            return false;
        }

        bool left = false, right = false;
        left = intersectR (node->left, ray, tmin, info);
        right = intersectR (node->right, ray, tmin, info);
        return left || right;
    }



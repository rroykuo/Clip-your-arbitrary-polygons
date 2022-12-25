#ifndef CLIP_YOUR_ARBITRARY_POLYGONS_POLYGON_H
#define CLIP_YOUR_ARBITRARY_POLYGONS_POLYGON_H

#pragma once
#include "PolygonUtils.h"

namespace PolyClip{

    class Polygon{
        Vertex * start_;
        Vertex * end_;
    public:
        typedef PolygonVertexIter iterator;
        int vertexNum_{};

        explicit Polygon(std::vector<Point2d> vertices);
        ~Polygon();

        // some property should be copied via polygon clipping operation
        // if using this function to copy
        // REMEMBER do polygon clipping operation from scratch

        Polygon(Polygon &poly);
        Polygon& operator=(Polygon& poly);

        // insert vertex to polygon on specific position
        void Insert(Vertex* new_v, Vertex *pos);
        void Insert(const Point2d& vertex, Vertex *pos);
        void Insert(double x, double y, Vertex* pos);

        // delete vertex on specific position
        void Remove(Vertex* pos);

        // create iterator
        iterator begin(){
            return {start_, 0};
        }

        // create end iterator for visiting all of vertices
        iterator end(){
            return {end_, vertexNum_};
        }

        // create end iterator, but let iterator visit one more vertices
        // to use start point as end point

        iterator endEdge(){
            return {end_, vertexNum_ + 1};
        }

    protected:
        friend class PolygonVertexIter;
    };

}

#endif //CLIP_YOUR_ARBITRARY_POLYGONS_POLYGON_H

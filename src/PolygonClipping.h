#ifndef CLIP_YOUR_ARBITRARY_POLYGONS_POLYGONCLIPPING_H
#define CLIP_YOUR_ARBITRARY_POLYGONS_POLYGONCLIPPING_H

#pragma once

#include "Polygon.h"
#include <iostream>

namespace PolyClip{
    enum {MarkIntersection, MarkUnion, MarkDifferentiate};
    class PolygonOperation{
    public:
        // Phase 1
        static void DetectIntersection(Polygon& clip_poly, Polygon& sub_poly);
        // Phase 2 and Phase 3
        // Mark vertices for intersection
        // true: normally intersection
        // false: no intersection or one polygon is inside the other
        static bool Mark(Polygon& clip_poly, Polygon& sub_poly,
                         std::vector<std::vector<Point2d> >& possible_result,
                         int markType);

        // Store the result
        static std::vector<std::vector<Point2d> > IntersectionResults(Polygon& clip_poly);
        static std::vector<std::vector<Point2d> > UnionResults(Polygon& clip_poly);
        static std::vector<std::vector<Point2d> > DifferentiateResults(Polygon& clip_poly);

        static void print(Polygon& polygon){
            for(auto & iter : polygon){
                std::cout << iter.x_ << " " << iter.y_ << "\n";
            }
        }

    private:
        static bool LineSegmentIntersection(Point2d& p1, Point2d& p2,
                                            Point2d& q1, Point2d& q2,
                                            float& alphaP, float& alphaQ);
        static Vertex CreateVertex(const Point2d& p1, const Point2d& p2, float alpha);
        // Determine the point is inside the polygon or not
        static bool Pnpoly(const Point2d& p, Polygon& polygon);
    };

}

#endif //CLIP_YOUR_ARBITRARY_POLYGONS_POLYGONCLIPPING_H

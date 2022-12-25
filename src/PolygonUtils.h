#ifndef CLIP_YOUR_ARBITRARY_POLYGONS_POLYGONUTILS_H
#define CLIP_YOUR_ARBITRARY_POLYGONS_POLYGONUTILS_H

#pragma  once
#include <vector>
#include <cstdlib>

namespace PolyClip{
    struct Point2d{
        double x_, y_;
        Point2d():x_(0.0), y_(0.0){}
        Point2d(double x, double y):x_(x), y_(y){}
    };

    struct Vertex{
        double x_, y_;
        Vertex * next_;
        Vertex * prev_;
        bool intersect_;
        bool entryExit_;
        Vertex * neighbor_;
        double alpha_;
        bool processed;

        Vertex()
            :x_(0.0), y_(0.0), alpha_(0.0),
            next_(nullptr), prev_(nullptr),
            neighbor_(nullptr), intersect_(false),
            entryExit_(false), processed(false){}
        explicit Vertex(const Point2d& p)
            :x_(p.x_), y_(p.y_), alpha_(0.0),
            next_(nullptr), prev_(nullptr),
            neighbor_(nullptr), intersect_(false),
            entryExit_(false), processed(false){}
        Vertex(double x, double y)
            :x_(x), y_(y), alpha_(0.0),
            next_(nullptr), prev_(nullptr),
            neighbor_(nullptr), intersect_(false),
            entryExit_(false), processed(false){}
    };
    // This object is used for sort intersection vertices so that we can insert these at correct order
    struct VertexPtrDistance{
        Vertex * ptr;
        double distance;
        VertexPtrDistance(Vertex* vPtr, double dis):ptr(vPtr),distance(dis){}
    };
    struct SortVertexPtrDistance{
        bool operator()(const VertexPtrDistance& v1, const VertexPtrDistance& v2){
            return v1.distance < v2.distance;
        }
    };

    class PolygonVertexIter{
    public:
        PolygonVertexIter(Vertex *cv, int visitedCount)
            :currentVertex_(cv), visitedCount_(visitedCount){};

        PolygonVertexIter operator++(){
            visitedCount_++;
            currentVertex_ = currentVertex_->next_;
            return *this;
        }
        PolygonVertexIter operator--(){
            visitedCount_--;
            currentVertex_ = currentVertex_->prev_;
            return *this;
        }
        Vertex& operator*(){
            return *currentVertex_; // similar to pointer
                                    // return exactly this vertex
        }
        bool operator!=(const PolygonVertexIter& p) const{
            return abs(visitedCount_) != abs(p.visitedCount_);
        }
        Vertex* eval(){return currentVertex_;}
        PolygonVertexIter next(){
            PolygonVertexIter nextIter = *this;
            return  ++nextIter;
        }

    private:
        Vertex * currentVertex_;
        int visitedCount_;
    };

    class Utils{
    public:
        // Shoelace formula
        //this formula only could calculate non-self-intersecting polygon
        //so the instance only could be convex or concave
        static double CalculatePolygonArea(const std::vector<Point2d>& polygon){
            double a = 0.0, b = 0.0;
            for(int i=0; i<polygon.size(); i++){
                if (i == polygon.size() - 1){
                    a += polygon[i].x_ * polygon[0].y_;
                    b += polygon[0].x_ * polygon[i].y_;
                }
                else{
                    a += polygon[i].x_ * polygon[i+1].y_;
                    b += polygon[i+1].x_ * polygon[i].y_;
                }
            }
            return abs((a-b) / 2);
        }
    };

}






#endif //CLIP_YOUR_ARBITRARY_POLYGONS_POLYGONUTILS_H

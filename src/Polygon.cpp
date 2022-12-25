#include "Polygon.h"

PolyClip::Polygon::Polygon(std::vector<Point2d> vertices){
    vertexNum_ = 0;
    for (int i=0; i<vertices.size(); i++){
        if (i != 0){
            Insert(vertices[i], end_);
            end_ = end_ -> next_;
        }
        else{
            auto* new_v = new Vertex(vertices[0]);
            new_v -> next_ = new_v;
            new_v -> prev_ = new_v;

            start_ = new_v;
            end_ = new_v;
            vertexNum_++;
        }
    }
}

PolyClip::Polygon::Polygon(Polygon &poly) {
    int i = 0;
    for (auto iter = poly.begin(); iter != poly.end(); ++iter, ++i){
        // let intersection points be added by clipping polygon operation
        if((*iter).intersect_){
            continue;
        }
        if(i != 0){
            auto* new_v = new Vertex(Point2d((*iter).x_, (*iter).y_));
            Insert(new_v, end_);
            end_ = end_->next_;
        }
        else{
            auto* new_v = new Vertex(Point2d((*iter).x_, (*iter).y_));

            new_v->next_ = new_v;
            new_v->prev_ = new_v;

            start_ = new_v;
            end_ = new_v;
            vertexNum_++;
        }
    }
}
PolyClip::Polygon& PolyClip::Polygon::operator=(Polygon &poly) {
    if (this == &poly){
        return *this;
    }
    while (start_){
        Remove(start_);
    }
    auto* copy_poly = new Polygon(poly);

    vertexNum_ = copy_poly->vertexNum_;
    start_ = copy_poly->start_;
    end_ = copy_poly->end_;

    return *this;
}

PolyClip::Polygon::~Polygon() {
    while (start_){
        Remove(start_);
    }
}
void PolyClip::Polygon::Insert(Vertex *new_v, Vertex *pos) {
    auto next_v = pos->next_;

    new_v->next_ = next_v;
    new_v->prev_ = pos;

    pos->next_ = new_v;

    next_v->prev_ = new_v;
    vertexNum_++;
}

void PolyClip::Polygon::Insert(double x, double y, Vertex *pos) {
    auto * new_v = new Vertex(x, y);
    auto next_v = pos->next_;

    new_v->next_ = next_v;
    new_v->prev_ = pos;

    pos->next_ = new_v;

    next_v->prev_ = new_v;

    vertexNum_++;
}

void PolyClip::Polygon::Insert(const Point2d &vertex, Vertex *pos) {
    auto * new_v = new Vertex(vertex);
    auto next_v = pos->next_;

    new_v->next_ = next_v;
    new_v->prev_ = pos;

    pos->next_ = new_v;

    next_v->prev_ = new_v;

    vertexNum_++;
}


void PolyClip::Polygon::Remove(Vertex *pos) {
    if(vertexNum_ == 1){
        start_ = nullptr;
        end_ = nullptr;
        auto neighbor_v = pos->neighbor_;
        if(neighbor_v){
            neighbor_v->neighbor_ = nullptr;
        }
        delete pos;
    }
    else{
        auto pre_v = pos->prev_;
        auto next_v = pos->next_;
        auto neighbor_v = pos->neighbor_;

        if(pre_v){
            pre_v->next_ = next_v;
        }
        if(next_v){
            next_v->prev_ = pre_v;
        }
        if(neighbor_v){
            neighbor_v->neighbor_ = nullptr;
        }
        if(pos == start_){
            start_ = next_v;
        }
        if(pos == end_){
            end_ = pre_v;
        }
        delete pos;
    }
    vertexNum_--;
}












#ifndef CLIP_YOUR_ARBITRARY_POLYGONS_PROCESSPOLYGON_H
#define CLIP_YOUR_ARBITRARY_POLYGONS_PROCESSPOLYGON_H


#pragma once
#include "PolygonUtils.h"
#include "PolygonClipping.h"
#include <iostream>

std::vector<std::vector<PolyClip::Point2d> > results;
std::vector<PolyClip::Point2d> vertices1;
std::vector<PolyClip::Point2d> vertices2;
extern bool process_flag;
extern bool RenderResultFlag;

void Process(int ClippingType){



    PolyClip::Polygon polygon1(vertices1);
    PolyClip::Polygon polygon2(vertices2);

    std::cout << "<-------------------- Phase1: Intersection -------------------->\n";
    PolyClip::PolygonOperation::DetectIntersection(polygon1, polygon2);

    std::cout << "<-------------------- Phase2: Chalk cart mark ------------------>\n";
    std::vector<std::vector<PolyClip::Point2d> > possible_result;
    std::cout << "<-------------------- Phase3: Extract desire results ----------->\n\n";



    if(ClippingType == 0){
        if (PolyClip::PolygonOperation::Mark(polygon1, polygon2,
                                             possible_result, PolyClip::MarkIntersection)){
            results = PolyClip::PolygonOperation::IntersectionResults(polygon1);
            for (auto & result : results){
                for (auto p : result)
                    std::cout << "(" << p.x_ << ", " << p.y_ << ")" << "---";
                std::cout << "\n";
            }
        }
        else {
            if (possible_result.empty())
                std::cout << "No intersection\n";
            else {
                for (auto & i : possible_result) {
                    for (auto p: i)
                        std::cout << "(" << p.x_ << ", " << p.y_ << ")" << "---";
                    std::cout << "\n";
                }
            }
        }
    }
    else if (ClippingType == 1){
        if (PolyClip::PolygonOperation::Mark(polygon1, polygon2,
                                             possible_result, PolyClip::MarkUnion)){
            results = PolyClip::PolygonOperation::UnionResults(polygon1);
            for (auto & result : results){
                for (auto p : result)
                    std::cout << "(" << p.x_ << ", " << p.y_ << ")" << "---";
                std::cout << "\n";
            }
        }
        else{
            if (possible_result.empty())
                std::cout << "No intersection\n";
            else
            {
                for (auto & i : possible_result){
                    for (auto p : i)
                        std::cout << "(" << p.x_ << ", " << p.y_ << ")" << "---";
                    std::cout << "\n";
                }
            }
        }
    }
    else{
        if (PolyClip::PolygonOperation::Mark(polygon1, polygon2,
                                             possible_result, PolyClip::MarkDifferentiate))
        {
            results = PolyClip::PolygonOperation::DifferentiateResults(polygon1);
            for (auto & result : results){
                for (auto p : result)
                    std::cout << "(" << p.x_ << ", " << p.y_ << ")" << "---";
                std::cout << "\n";
            }
        }
        else{
            if (possible_result.empty())
                std::cout << "No intersection\n";
            else{
                for (auto & i : possible_result){
                    for (auto p : i)
                        std::cout << "(" << p.x_ << ", " << p.y_ << ")" << "---";
                    std::cout << "\n";
                }
            }
        }

    }
    process_flag = false;
    RenderResultFlag = true;
}

#endif //CLIP_YOUR_ARBITRARY_POLYGONS_PROCESSPOLYGON_H

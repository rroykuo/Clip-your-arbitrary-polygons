#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "PolygonUtils.h"
#include "PolygonClipping.h"

void Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    {
        glColor3f(1.0,0.0,0.0);
        glVertex2f(0, .5);
        glColor3f(0.0,1.0,0.0);
        glVertex2f(-.5,-.5);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(.5, -.5);
    }
    glEnd();
}

int main(int argc, const char * argv[]) {
//    GLFWwindow* win;
//    if(!glfwInit()) {
//        return -1;
//    }
//    win = glfwCreateWindow(480, 320, "Triangle", NULL, NULL);
//    if(!win) {
//        glfwTerminate();
//        exit(EXIT_FAILURE);
//    }
//    if(!glewInit()) {
//        return -1;
//    }
//    glfwMakeContextCurrent(win);
//    while(!glfwWindowShouldClose(win)){
//        Render();
//        glfwSwapBuffers(win);
//        glfwPollEvents();
//    }
//    glfwTerminate();
//    exit(EXIT_SUCCESS);
    std::vector<PolyClip::Point2d> vertices1;
    vertices1.emplace_back(10.0, 10.0);
    vertices1.emplace_back(10.0, 100.0);
    vertices1.emplace_back(100.0, 100.0);
    vertices1.emplace_back(100.0, 10.0);
    PolyClip::Polygon polygon1(vertices1);

    std::vector<PolyClip::Point2d> vertices2;
    vertices2.emplace_back(10, 100);
    vertices2.emplace_back(10, 150);
    vertices2.emplace_back(100, 150);
    vertices2.emplace_back(100, 100);
    PolyClip::Polygon polygon2(vertices2);

    std::cout << "<-------------------- Phase1: Intersection -------------------->\n";
    PolyClip::PolygonOperation::DetectIntersection(polygon1, polygon2);

    std::cout << "<-------------------- Phase2: Chalk cart mark -------------------->\n";
    std::vector<std::vector<PolyClip::Point2d> > possible_result;
    std::cout << "<-------------------- Phase3: Extract desire results -------------------->\n";
    if (PolyClip::PolygonOperation::Mark(polygon1, polygon2,
                                         possible_result,PolyClip::MarkIntersection)){
        std::vector<std::vector<PolyClip::Point2d> > results =
                PolyClip::PolygonOperation::IntersectionResults(polygon1);
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

    return 0;
}
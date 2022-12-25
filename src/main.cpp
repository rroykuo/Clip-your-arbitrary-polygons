#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ProcessPolygon.h"


extern std::vector<std::vector<PolyClip::Point2d> > results;
extern std::vector<PolyClip::Point2d> vertices1;
extern std::vector<PolyClip::Point2d> vertices2;


void Render(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);{
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

    printf("\n<---------Input the Clipping type--------->\n\n"
           "Intersection: 0\n"
           "Union: 1\n"
           "Differentiate: 2\n\n"
           "Enter the number: ");

    std::string ClipType;
    std::cin >> ClipType;



    const char* ClipTitle;
    if(std::stoi(ClipType) == 0){
        ClipTitle = "Intersection";
    }
    else if (std::stoi(ClipType) == 1){
        ClipTitle = "Union";
    }
    else{
        ClipTitle = "Differentiate";
    }

    if(!glfwInit()) {
        return -1;
    }

    // Process the polygon
    Process(std::stoi(ClipType));

    GLFWwindow* win = glfwCreateWindow(960, 780, ClipTitle, nullptr, nullptr);
    if(!win) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    if(!glewInit()) {
        return -1;
    }
    int width, height;
    glfwGetFramebufferSize(win, &width, &height);

    glViewport(0, 0, width, height);
    glfwMakeContextCurrent(win);
    while(!glfwWindowShouldClose(win)){
        glfwPollEvents();
        Render();
        glfwSwapBuffers(win);
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);

    return 0;
}
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ProcessPolygon.h"


extern std::vector<std::vector<PolyClip::Point2d> > results;
extern std::vector<PolyClip::Point2d> vertices1;
extern std::vector<PolyClip::Point2d> vertices2;

int VerticesNumOfPoly1, VerticesNumOfPoly2;
int VerticesCnt1 = 0, VerticesCnt2 = 0;
bool process_flag = false;
bool RenderPoly1Flag = false;
bool RenderPoly2Flag = false;
bool RenderResultFlag = false;

//static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
////    std::cout << "Position: (" << xpos << "," << ypos << ")" <<" \n";
//}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        if(VerticesCnt2 < VerticesNumOfPoly2){
            double xpos, ypos;
            //getting cursor position
            glfwGetCursorPos(window, &xpos, &ypos);
            xpos = xpos/480 -1;
            ypos = -ypos/390 + 1;
            std::cout << "Subject polygon's " << VerticesCnt2+1 << " th position at ("
            << xpos << " , " << ypos << ")" << " \n";
            vertices2.emplace_back(xpos, ypos);
            VerticesCnt2++;
            if(VerticesCnt2 == VerticesNumOfPoly2){
                printf("\n");
                RenderPoly2Flag = true;
            }
        }
        else if(VerticesCnt1 < VerticesNumOfPoly1){
            double xpos, ypos;
            //getting cursor position
            glfwGetCursorPos(window, &xpos, &ypos);
            xpos = xpos/480 -1;
            ypos = -ypos/390 + 1;
            std::cout << "Clipping polygon's " << VerticesCnt1+1 << " th position at ("
            << xpos << " , " << ypos << ")" << " \n";
            vertices1.emplace_back(xpos, ypos);
            VerticesCnt1++;
            if(VerticesCnt1 == VerticesNumOfPoly1){
                RenderPoly1Flag = true;
                printf("\n");
                printf("Click Right Button Of Mouse To Process\n");
//                process_flag = true;
            }
        }
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        if(VerticesCnt2 == VerticesNumOfPoly2 && VerticesCnt1 == VerticesNumOfPoly1){
//            RenderPoly1Flag = false;
//            RenderPoly2Flag = false;
            process_flag = true;

        }
    }
}


void RenderPolygon2(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if(RenderPoly2Flag){
        glColor4f(1.0,0.0,0.0, 0.1);
        glBegin(GL_TRIANGLE_FAN);
        for (int i=0; i<VerticesNumOfPoly2; i++){
            glVertex3f(vertices2[i].x_, vertices2[i].y_, 0);
        }
        glEnd();
        if(RenderPoly1Flag){
            glBegin(GL_TRIANGLE_FAN);
            glColor4f(0.0,0.0,1.0, 0.1);
            for (int i=0; i<VerticesNumOfPoly1; i++){
                glVertex3f(vertices1[i].x_, vertices1[i].y_, 0.5);
            }
            glEnd();
        }
    }
    if (RenderResultFlag){
        for (auto & result : results){
            glBegin(GL_TRIANGLE_FAN);
            glColor4f(0.0,1.0,0.0, 0.1);
            for (auto p : result)
                glVertex3f(p.x_, p.y_, 1);
            glEnd();
        }

    }
}


int main(int argc, const char * argv[]) {

    printf("\n<---------Input the Clipping type--------->\n\n"
           "Intersection: 0\n"
           "Union: 1\n"
           "Differentiate: 2\n\n"
           "Enter the number: ");

    int ClipType;
    std::cin >> ClipType;

    const char* ClipTitle;
    if(ClipType == 0){
        ClipTitle = "Intersection";
    }
    else if (ClipType == 1){
        ClipTitle = "Union";
    }
    else{
        ClipTitle = "Differentiate";
    }

    if(!glfwInit()) {
        return -1;
    }


    printf("\nEnter the Vertex number of subject polygon: ");
    std::cin>>VerticesNumOfPoly2;
    printf("\n\nEnter the Vertex number of clipping polygon: ");
    std::cin>>VerticesNumOfPoly1;
    printf("\n");


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
    glfwSetMouseButtonCallback(win, mouse_button_callback);
    while(!glfwWindowShouldClose(win)){
        glfwPollEvents();
        if(process_flag){
            // Process the polygon
            Process(ClipType);
        }
        if(RenderPoly2Flag){
            RenderPolygon2();
        }
        glfwSwapBuffers(win);
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);

    return 0;
}
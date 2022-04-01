
#include "variables.hpp"
#include "update.hpp"

const GLdouble pi = 3.1415926535897932384626433832795;
const double fpsLimit = 1.0 / 120.0;
double updateTime = 0;
float angle = 0;

void drawCube(float deltaTime, double radius) {
    GLfloat vertices[] = {
        -1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
        1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
        -1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
        -1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
    };
    GLfloat colors[] = {
        0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
        1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
        0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
        0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
    };
    glRotatef(angle, 0, 1, 0);
    glTranslated(radius, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    angle += deltaTime * 60;
}

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
    GLdouble fW, fH;
    fH = tan(fovY / 360 * pi) * zNear;
    fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void update() {
    
    if(window == NULL || resourcesFolderPath.length() == 0) {
        return;
    }
    
    while(!glfwWindowShouldClose(window)) {
        double now = glfwGetTime();
        double deltaTime = now - updateTime;
        double fps = 1.0 / deltaTime;
        printf("FPS: %f\n", fps);
        glfwPollEvents();
        if (deltaTime >= fpsLimit) {
            GLint dims[4] = {0};
            glGetIntegerv(GL_VIEWPORT, dims);
            GLint windowWidth = dims[2];
            GLint windowHeight = dims[3];
            glViewport(0, 0, windowWidth, windowHeight);
            glClearColor(0.0, 0.8, 0.3, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION_MATRIX);
            glLoadIdentity();
            perspectiveGL(60, (double)windowWidth / (double)windowHeight, 0.1, 100);
            glMatrixMode(GL_MODELVIEW_MATRIX);
            glTranslatef(0, 0, -5);
            drawCube((float)(now - updateTime), 0);
            glfwSwapInterval(1);
            glfwSwapBuffers(window);
            updateTime = now;
        }
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

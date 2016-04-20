#include "widgetopengl.h"
#include <iostream>

WidgetOpenGL::WidgetOpenGL(QWidget* parent) : QOpenGLWidget(parent), QOpenGLFunctions()
{
    //makeCurrent();

}

void WidgetOpenGL::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);


    glEnable(GL_DEPTH_TEST);

}

void WidgetOpenGL::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float vertices[] = {-0.5, -0.5,   0.0, 0.5,   0.5, -0.5};


    f->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    f->glEnableVertexAttribArray(0);


    // On affiche le triangle

    f->glDrawArrays(GL_TRIANGLES, 0, 3);


    // On désactive le tableau Vertex Attrib puisque l'on en a plus besoin

    f->glDisableVertexAttribArray(0);


}

void WidgetOpenGL::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    std::cout << width << '-' << height << std::endl;

}

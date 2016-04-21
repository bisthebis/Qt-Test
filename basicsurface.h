#ifndef BASICSURFACE_H
#define BASICSURFACE_H

#include "widgetopengl.h"

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QtOpenGL>
#include <QtGui>
#include <QtWidgets>

class BasicSurface : public WidgetOpenGL
{
    Q_OBJECT
    public:
        BasicSurface(QWidget* parent = nullptr);
        virtual ~BasicSurface();
        void init();

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);


    signals:

    public slots:
        void setRed(int v) {red = v;}
        void setGreen(int v) {green = v;}
        void setBlue(int v) {blue = v;}
        void updateShader();

    private:
        QOpenGLShaderProgram program;
        QOpenGLVertexArrayObject VAO;
        QOpenGLBuffer VBO;
        unsigned char red, green, blue;
};

#endif // BASICSURFACE_H

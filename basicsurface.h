#ifndef BASICSURFACE_H
#define BASICSURFACE_H



#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QtOpenGL>
#include <QtGui>
#include <QtWidgets>
#include <QtMath>

#include "camera.h"

class BasicSurface : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
    public:
        BasicSurface(QWidget* parent = nullptr);
        virtual ~BasicSurface();

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);


    signals:


    public slots:
        void setRed(int v) {red = v;}
        void setGreen(int v) {green = v;}
        void setBlue(int v) {blue = v;}
        void setFrustrumSize(int v) {frustrumSize = double(v)/10.0f; recomputeProjection(); window()->findChild<QCheckBox*>("isOrthographic")->setChecked(true);}
        void setFieldOfView(int v) {FoV = double(v); recomputeProjection(); window()->findChild<QCheckBox*>("isOrthographic")->setChecked(false);}
        void updateShader();
        void reloadShader();

    private slots:
        void recomputeProjection();


    private:
        QOpenGLShaderProgram program;
        QOpenGLVertexArrayObject VAO;
        QOpenGLBuffer VBO;
        QMatrix4x4 projection;

            float frustrumSize = 2.0f;
            float FoV = 60.0f;


        unsigned char red, green, blue;

        Camera camera;
};

#endif // BASICSURFACE_H

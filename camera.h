#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QMatrix4x4>
#include <QVector3D>

class Camera : public QObject
{
    Q_OBJECT
    public:
        explicit Camera(QObject *parent = 0);
        const QMatrix4x4& get(){return view;}

    signals:
        void valueChanged();
    public slots:
        void setEye(const QVector3D& v) {eye.setX(v.x()); eye.setY(v.y()); eye.setZ(v.z()); update();}
        void setTarget(const QVector3D& v) {target.setX(v.x()); target.setY(v.y()); target.setZ(v.z());  update();}
        void setAxis(const QVector3D& v) {axis.setX(v.x()); axis.setY(v.y()); axis.setZ(v.z());  update();}

    private:
        void update();
        QMatrix4x4 view;
        QVector3D eye;
        QVector3D target;
        QVector3D axis;
};

#endif // CAMERA_H

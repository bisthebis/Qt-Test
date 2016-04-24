#include "camera.h"


Camera::Camera(QObject *parent) : QObject(parent), eye(3,3,3), target(0,0,0), axis(0,1,0)
{
    view.setToIdentity();
}
void Camera::update()
{
    view.setToIdentity();
    view.lookAt(eye, target, axis);
    emit valueChanged();

}

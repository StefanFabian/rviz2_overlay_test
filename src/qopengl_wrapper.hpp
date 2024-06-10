//
// Created by stefan on 10.06.24.
//

#ifndef QOPENGL_WRAPPER_HPP
#define QOPENGL_WRAPPER_HPP
#include <memory>

class QPainter;
class QOpenGLFramebufferObject;
class QOpenGLPaintDevice;
class QOffscreenSurface;
class QOpenGLContext;

class QOpenGLWrapper {
public:
    QOpenGLWrapper(int width, int height, unsigned int texture_id);

void draw();

    void init();
private:
    QOpenGLContext *context_ = nullptr;
    QOffscreenSurface *surface_ = nullptr;
    QOpenGLFramebufferObject *fbo_ = nullptr;
    QOpenGLPaintDevice *paint_device_ = nullptr;
    QPainter *painter_;
    int width_, height_;
    unsigned int texture_id_;
};

#endif //QOPENGL_WRAPPER_HPP

//
// Created by stefan on 10.06.24.
//

#include "qopengl_wrapper.hpp"
#include "timer.hpp"

#include <QPainter>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLPaintDevice>
#include <QOffscreenSurface>

#include <GL/glx.h>


QOpenGLWrapper::QOpenGLWrapper(int width, int height, unsigned int texture_id) : width_(width), height_(height), texture_id_(texture_id) {
}

void QOpenGLWrapper::draw() {
    init();
    static hector_timeit::Timer timer("render", hector_timeit::Timer::Default, false, true);
    hector_timeit::TimeBlock block(timer);
    GLXContext native_context = glXGetCurrentContext();
    GLXDrawable native_drawable = glXGetCurrentDrawable();
    ::Display *display = glXGetCurrentDisplay();
    context_->makeCurrent(surface_);
    if (paint_device_ == nullptr) {
        paint_device_ = new QOpenGLPaintDevice(width_, height_);
        fbo_ = new QOpenGLFramebufferObject(width_, height_);
    painter_ = new QPainter(paint_device_);
    }
    fbo_->bind();
    painter_->fillRect( width_ / 4, height_ / 4, width_ / 2, height_ / 2, Qt::blue );
    fbo_->release();
    QOpenGLFramebufferObject::bindDefault();
    QImage img = fbo_->toImage();
    context_->doneCurrent();
    glXMakeCurrent(display, native_drawable, native_context);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
}

void QOpenGLWrapper::init() {
    if (context_ != nullptr) return;

    context_ =new QOpenGLContext;
    QSurfaceFormat format;
    format.setDepthBufferSize(16);
    format.setStencilBufferSize(8);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    context_->setFormat(format);
    if (!context_->create()) {
        exit(1);
    }
    surface_ = new QOffscreenSurface();
    surface_->setFormat(format);
    surface_->create();
}

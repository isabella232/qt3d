/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

#ifndef QT3DRENDER_QCLEARBUFFERS_H
#define QT3DRENDER_QCLEARBUFFERS_H

#include <Qt3DRender/qframegraphnode.h>
#include <Qt3DRender/qrendertargetoutput.h>
#include <QtGui/QColor>
#include <QtCore/QFlags>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

class QClearBuffersPrivate;

class Q_3DRENDERSHARED_EXPORT QClearBuffers : public QFrameGraphNode
{
    Q_OBJECT
    Q_PROPERTY(BufferType buffers READ buffers WRITE setBuffers NOTIFY buffersChanged)
    Q_PROPERTY(QColor clearColor READ clearColor WRITE setClearColor NOTIFY clearColorChanged)
    Q_PROPERTY(float clearDepthValue READ clearDepthValue WRITE setClearDepthValue NOTIFY clearDepthValueChanged)
    Q_PROPERTY(int clearStencilValue READ clearStencilValue WRITE setClearStencilValue NOTIFY clearStencilValueChanged)
    Q_PROPERTY(Qt3DRender::QRenderTargetOutput* colorBuffer READ colorBuffer WRITE setColorBuffer NOTIFY colorBufferChanged)

public:
    explicit QClearBuffers(Qt3DCore::QNode *parent = nullptr);
    ~QClearBuffers();

    enum BufferType {
        None = 0,
        ColorBuffer = (1 << 0),
        DepthBuffer = (1 << 1),
        StencilBuffer = (1 << 2),
        DepthStencilBuffer = DepthBuffer | StencilBuffer,
        ColorDepthBuffer = ColorBuffer | DepthBuffer,
        ColorDepthStencilBuffer = ColorBuffer | DepthStencilBuffer,
        AllBuffers = 0xFFFFFFFF
    };
    Q_ENUM(BufferType) // LCOV_EXCL_LINE
    Q_DECLARE_FLAGS(BufferTypeFlags, BufferType)

    BufferType buffers() const;
    QColor clearColor() const;
    float clearDepthValue() const;
    int clearStencilValue() const;
    QRenderTargetOutput *colorBuffer() const;

public Q_SLOTS:
    void setBuffers(BufferType buffers);
    void setClearColor(const QColor& color);
    void setClearDepthValue(float clearDepthValue);
    void setClearStencilValue(int clearStencilValue);
    void setColorBuffer(QRenderTargetOutput *buffer);

Q_SIGNALS:
    void buffersChanged(BufferType buffers);
    void clearColorChanged(const QColor& color);
    void clearDepthValueChanged(float clearDepthValue);
    void clearStencilValueChanged(int clearStencilValue);
    void colorBufferChanged(QRenderTargetOutput *buffer);

protected:
    explicit QClearBuffers(QClearBuffersPrivate &dd, Qt3DCore::QNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QClearBuffers)
    Qt3DCore::QNodeCreatedChangeBasePtr createNodeCreationChange() const override;
};

} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_QCLEARBUFFERS_H

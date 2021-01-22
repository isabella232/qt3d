/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
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

#ifndef QT3DRENDER_QGEOMETRYRENDERER_H
#define QT3DRENDER_QGEOMETRYRENDERER_H

#include <Qt3DCore/qcomponent.h>
#include <Qt3DRender/qgeometry.h>
#include <Qt3DRender/qt3drender_global.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

class QGeometryRendererPrivate;
class QGeometryFactory;

typedef QSharedPointer<QGeometryFactory> QGeometryFactoryPtr;

class Q_3DRENDERSHARED_EXPORT QGeometryRenderer : public Qt3DCore::QComponent
{
    Q_OBJECT
    Q_PROPERTY(int instanceCount READ instanceCount WRITE setInstanceCount NOTIFY instanceCountChanged)
    Q_PROPERTY(int vertexCount READ vertexCount WRITE setVertexCount NOTIFY vertexCountChanged)
    Q_PROPERTY(int indexOffset READ indexOffset WRITE setIndexOffset NOTIFY indexOffsetChanged)
    Q_PROPERTY(int firstInstance READ firstInstance WRITE setFirstInstance NOTIFY firstInstanceChanged)
    Q_PROPERTY(int firstVertex READ firstVertex WRITE setFirstVertex NOTIFY firstVertexChanged)
    Q_PROPERTY(int indexBufferByteOffset READ indexBufferByteOffset WRITE setIndexBufferByteOffset NOTIFY indexBufferByteOffsetChanged)
    Q_PROPERTY(int restartIndexValue READ restartIndexValue WRITE setRestartIndexValue NOTIFY restartIndexValueChanged)
    Q_PROPERTY(int verticesPerPatch READ verticesPerPatch WRITE setVerticesPerPatch NOTIFY verticesPerPatchChanged)
    Q_PROPERTY(bool primitiveRestartEnabled READ primitiveRestartEnabled WRITE setPrimitiveRestartEnabled NOTIFY primitiveRestartEnabledChanged)
    Q_PROPERTY(Qt3DRender::QGeometry* geometry READ geometry WRITE setGeometry NOTIFY geometryChanged)
    Q_PROPERTY(PrimitiveType primitiveType READ primitiveType WRITE setPrimitiveType NOTIFY primitiveTypeChanged)

public:
    explicit QGeometryRenderer(Qt3DCore::QNode *parent = nullptr);
    ~QGeometryRenderer();

    enum PrimitiveType {
        Points = 0x0000,
        Lines = 0x0001,
        LineLoop = 0x0002,
        LineStrip = 0x0003,
        Triangles = 0x0004,
        TriangleStrip = 0x0005,
        TriangleFan = 0x0006,
        LinesAdjacency = 0x000A,
        TrianglesAdjacency = 0x000C,
        LineStripAdjacency = 0x000B,
        TriangleStripAdjacency = 0x000D,
        Patches = 0x000E
    };
    Q_ENUM(PrimitiveType) // LCOV_EXCL_LINE

    // how to figure out index count and all the fancy stuff that QMeshData provides for us?
    // also how to figure out which attribute(s?) hold the indices?

    int instanceCount() const;
    int vertexCount() const;
    int indexOffset() const;
    int firstInstance() const;
    int firstVertex() const;
    int indexBufferByteOffset() const;
    int restartIndexValue() const;
    int verticesPerPatch() const;
    bool primitiveRestartEnabled() const;
    QGeometry *geometry() const;
    PrimitiveType primitiveType() const;

    Q3D_DECL_DEPRECATED QGeometryFactoryPtr geometryFactory() const;
    Q3D_DECL_DEPRECATED void setGeometryFactory(const QGeometryFactoryPtr &factory);

public Q_SLOTS:
    void setInstanceCount(int instanceCount);
    void setVertexCount(int vertexCount);
    void setIndexOffset(int indexOffset);
    void setFirstInstance(int firstInstance);
    void setFirstVertex(int firstVertex);
    void setIndexBufferByteOffset(int offset);
    void setRestartIndexValue(int index);
    void setVerticesPerPatch(int verticesPerPatch);
    void setPrimitiveRestartEnabled(bool enabled);
    void setGeometry(QGeometry *geometry);
    void setPrimitiveType(PrimitiveType primitiveType);

Q_SIGNALS:
    void instanceCountChanged(int instanceCount);
    void vertexCountChanged(int vertexCount);
    void indexOffsetChanged(int indexOffset);
    void firstInstanceChanged(int firstInstance);
    void firstVertexChanged(int firstVertex);
    void indexBufferByteOffsetChanged(int offset);
    void restartIndexValueChanged(int restartIndexValue);
    void verticesPerPatchChanged(int verticesPerPatch);
    void primitiveRestartEnabledChanged(bool primitiveRestartEnabled);
    void geometryChanged(QGeometry *geometry);
    void primitiveTypeChanged(PrimitiveType primitiveType);

protected:
    explicit QGeometryRenderer(QGeometryRendererPrivate &dd, Qt3DCore::QNode *parent = nullptr);
    // TODO Unused remove in Qt6
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &change) override;

private:
    Q_DECLARE_PRIVATE(QGeometryRenderer)
    Qt3DCore::QNodeCreatedChangeBasePtr createNodeCreationChange() const override;
};

} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_QGEOMETRYRENDERER_H

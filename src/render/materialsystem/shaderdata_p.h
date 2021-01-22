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

#ifndef QT3DRENDER_RENDER_SHADERDATA_P_H
#define QT3DRENDER_RENDER_SHADERDATA_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <Qt3DRender/private/backendnode_p.h>
#include <Qt3DRender/qshaderdata.h>
#include <QMutex>
#include <Qt3DCore/private/matrix4x4_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

namespace Render {

class GraphicsContext;
class GLBuffer;
class NodeManagers;

class Q_3DRENDERSHARED_PRIVATE_EXPORT ShaderData : public BackendNode
{
public:
    enum TransformType {
        NoTransform = -1,
        ModelToEye = 0,
        ModelToWorld,
        ModelToWorldDirection
    };
    struct PropertyValue {
        QVariant value;
        bool isNested;
        bool isTransformed;
    };

    ShaderData();
    ~ShaderData();

    QHash<QString, PropertyValue> properties() const { return m_originalProperties; }

    // Called by FramePreparationJob
    void updateWorldTransform(const Matrix4x4 &worldMatrix);

    QVariant getTransformedProperty(const QString &name, const Matrix4x4 &viewMatrix) const noexcept;

    // Unit tests purposes only
    TransformType propertyTransformType(const QString &name) const;

    void setManagers(NodeManagers *managers);

    void syncFromFrontEnd(const Qt3DCore::QNode *frontEnd, bool firstTime) override;

#ifdef Q_OS_WIN
    // To get MSVC to compile even though we don't need any cleanup
    void cleanup() {}
#endif

protected:
    PropertyReaderInterfacePtr m_propertyReader;


    // 1 to 1 match with frontend properties
    QHash<QString, PropertyValue> m_originalProperties;

    Matrix4x4 m_worldMatrix;
    NodeManagers *m_managers;

    static ShaderData *lookupResource(NodeManagers *managers, Qt3DCore::QNodeId id);
    ShaderData *lookupResource(Qt3DCore::QNodeId id);

    friend class RenderShaderDataFunctor;
};

class RenderShaderDataFunctor : public Qt3DCore::QBackendNodeMapper
{
public:
    explicit RenderShaderDataFunctor(AbstractRenderer *renderer, NodeManagers *managers);

    Qt3DCore::QBackendNode *create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const final;
    Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const final;
    void destroy(Qt3DCore::QNodeId id) const final;

private:
    NodeManagers *m_managers;
    AbstractRenderer *m_renderer;
};

} // namespace Render

} // namespace Qt3DRender

QT_END_NAMESPACE

Q_DECLARE_METATYPE(Qt3DRender::Render::ShaderData*) // LCOV_EXCL_LINE

#endif // QT3DRENDER_RENDER_SHADERDATA_P_H

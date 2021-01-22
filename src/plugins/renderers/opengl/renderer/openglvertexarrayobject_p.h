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

#ifndef QT3DRENDER_RENDER_OPENGL_OPENGLVERTEXARRAYOBJECT_H
#define QT3DRENDER_RENDER_OPENGL_OPENGLVERTEXARRAYOBJECT_H

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

#include <QtGui/qopenglvertexarrayobject.h>
#include <submissioncontext_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {
namespace Render {

class GeometryManager;

typedef QPair<HGeometry, Qt3DCore::QNodeId> VAOIdentifier;

namespace OpenGL {

class GLShaderManager;

class Q_AUTOTEST_EXPORT OpenGLVertexArrayObject
{
public:
    OpenGLVertexArrayObject();

    void bind();
    void release();

    void create(SubmissionContext *ctx, const VAOIdentifier &key);
    VAOIdentifier key() const;
    void destroy();
    void cleanup();

    bool isAbandoned(GeometryManager *geomMgr, GLShaderManager *shaderMgr);

    QOpenGLVertexArrayObject *vao() { return m_vao.data(); }
    const QOpenGLVertexArrayObject *vao() const { return m_vao.data(); }

    void setSpecified(bool b) { m_specified = b; }
    bool isSpecified() const { return m_specified; }


private:
    QMutex m_mutex;
    SubmissionContext *m_ctx;
    QScopedPointer<QOpenGLVertexArrayObject> m_vao;
    bool m_specified;
    bool m_supportsVao;
    VAOIdentifier m_owners;

    friend class SubmissionContext;

    void saveVertexAttribute(const SubmissionContext::VAOVertexAttribute &attr);
    inline void saveIndexAttribute(HGLBuffer glBufferHandle) { m_indexAttribute = glBufferHandle; }

    QVector<SubmissionContext::VAOVertexAttribute> m_vertexAttributes;
    SubmissionContext::VAOIndexAttribute m_indexAttribute;
};

} // namespace OpenGL
} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_OPENGL_OPENGLVERTEXARRAYOBJECT_H

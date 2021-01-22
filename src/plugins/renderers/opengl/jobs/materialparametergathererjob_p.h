/****************************************************************************
**
** Copyright (C) 2016 Paul Lemire
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

#ifndef QT3DRENDER_RENDER_OPENGL_MATERIALPARAMETERGATHERERJOB_P_H
#define QT3DRENDER_RENDER_OPENGL_MATERIALPARAMETERGATHERERJOB_P_H

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

#include <Qt3DCore/qaspectjob.h>
#include <Qt3DCore/qnodeid.h>
#include <Qt3DRender/private/handle_types_p.h>
#include <Qt3DRender/private/qt3drender_global_p.h>
#include <renderviewjobutils_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

namespace Render {

class NodeManagers;
class TechniqueFilter;
class RenderPassFilter;

namespace OpenGL {
class Renderer;

// TO be executed for each FrameGraph branch with a given RenderPassFilter/TechniqueFilter
class MaterialParameterGathererJobPrivate;

class Q_AUTOTEST_EXPORT MaterialParameterGathererJob : public Qt3DCore::QAspectJob
{
public:
    MaterialParameterGathererJob();

    inline void setNodeManagers(NodeManagers *manager) Q_DECL_NOTHROW { m_manager = manager; }
    inline void setTechniqueFilter(TechniqueFilter *techniqueFilter) Q_DECL_NOTHROW { m_techniqueFilter = techniqueFilter; }
    inline void setRenderPassFilter(RenderPassFilter *renderPassFilter) Q_DECL_NOTHROW { m_renderPassFilter = renderPassFilter; }
    inline const MaterialParameterGathererData &materialToPassAndParameter() Q_DECL_NOTHROW { return m_parameters; }
    inline void setHandles(std::vector<HMaterial> &&handles) Q_DECL_NOTHROW { m_handles = std::move(handles); }
    inline void setHandles(const std::vector<HMaterial> &handles) Q_DECL_NOTHROW { m_handles = handles; }

    inline TechniqueFilter *techniqueFilter() const Q_DECL_NOTHROW { return m_techniqueFilter; }
    inline RenderPassFilter *renderPassFilter() const Q_DECL_NOTHROW { return m_renderPassFilter; }

    void run() final;

private:
    NodeManagers *m_manager;
    TechniqueFilter *m_techniqueFilter;
    RenderPassFilter *m_renderPassFilter;

    // Material id to array of RenderPasse with parameters
    MaterialParameterGathererData m_parameters;
    std::vector<HMaterial> m_handles;

    Q_DECLARE_PRIVATE(MaterialParameterGathererJob)
};

typedef QSharedPointer<MaterialParameterGathererJob> MaterialParameterGathererJobPtr;

} // OpenGL

} // Render

} // Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_OPENGL_MATERIALPARAMETERGATHERERJOB_P_H

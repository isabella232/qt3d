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

#include "rendertargetselectornode_p.h"
#include <Qt3DCore/private/qchangearbiter_p.h>
#include <Qt3DRender/qrendertargetselector.h>
#include <Qt3DRender/private/qrendertargetselector_p.h>
#include <Qt3DRender/qrendertarget.h>
#include <Qt3DRender/private/renderlogging_p.h>
#include <Qt3DRender/qrendertargetoutput.h>

QT_BEGIN_NAMESPACE

using namespace Qt3DCore;

namespace Qt3DRender {
namespace Render {

RenderTargetSelector::RenderTargetSelector() :
    FrameGraphNode(FrameGraphNode::RenderTarget)
{
}

void RenderTargetSelector::syncFromFrontEnd(const QNode *frontEnd, bool firstTime)
{
    const QRenderTargetSelector *node = qobject_cast<const QRenderTargetSelector *>(frontEnd);
    if (!node)
        return;

    FrameGraphNode::syncFromFrontEnd(frontEnd, firstTime);

    const QNodeId renderTargetId = qIdForNode(node->target());
    if (renderTargetId != m_renderTargetUuid) {
        m_renderTargetUuid = renderTargetId;
        markDirty(AbstractRenderer::FrameGraphDirty);
    }

    if (node->outputs() != m_outputs) {
        m_outputs = node->outputs();
        markDirty(AbstractRenderer::FrameGraphDirty);
    }
}

} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE

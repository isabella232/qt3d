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

#include <Qt3DRender/private/rendertargetoutput_p.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/private/qrendertargetoutput_p.h>
#include <QVariant>

QT_BEGIN_NAMESPACE

using namespace Qt3DCore;

namespace Qt3DRender {
namespace Render {

RenderTargetOutput::RenderTargetOutput()
    : BackendNode()
{
}

void RenderTargetOutput::syncFromFrontEnd(const Qt3DCore::QNode *frontEnd, bool firstTime)
{
    const QRenderTargetOutput *node = qobject_cast<const QRenderTargetOutput *>(frontEnd);
    if (!node)
        return;

    const bool oldEnabled = isEnabled();
    BackendNode::syncFromFrontEnd(frontEnd, firstTime);

    if (node->attachmentPoint() != m_attachmentData.m_point) {
        m_attachmentData.m_point = node->attachmentPoint();
        markDirty(AbstractRenderer::AllDirty);
    }
    if (node->mipLevel() != m_attachmentData.m_mipLevel) {
        m_attachmentData.m_mipLevel = node->mipLevel();
        markDirty(AbstractRenderer::AllDirty);
    }
    if (node->layer() != m_attachmentData.m_layer) {
        m_attachmentData.m_layer = node->layer();
        markDirty(AbstractRenderer::AllDirty);
    }
    if (node->face() != m_attachmentData.m_face) {
        m_attachmentData.m_face = node->face();
        markDirty(AbstractRenderer::AllDirty);
    }
    const auto textureId = Qt3DCore::qIdForNode(node->texture());
    if (textureId != m_attachmentData.m_textureUuid) {
        m_attachmentData.m_textureUuid = textureId;
        markDirty(AbstractRenderer::AllDirty);
    }

    if (oldEnabled != isEnabled())
        markDirty(AbstractRenderer::AllDirty);
}

Qt3DCore::QNodeId RenderTargetOutput::textureUuid() const
{
    return m_attachmentData.m_textureUuid;
}

int RenderTargetOutput::mipLevel() const
{
    return m_attachmentData.m_mipLevel;
}

int RenderTargetOutput::layer() const
{
    return m_attachmentData.m_layer;
}

QString RenderTargetOutput::name() const
{
    return m_attachmentData.m_name;
}

QAbstractTexture::CubeMapFace RenderTargetOutput::face() const
{
    return m_attachmentData.m_face;
}

QRenderTargetOutput::AttachmentPoint RenderTargetOutput::point() const
{
    return m_attachmentData.m_point;
}

Qt3DRender::Render::Attachment *RenderTargetOutput::attachment()
{
    return &m_attachmentData;
}

const Attachment *RenderTargetOutput::attachment() const
{
    return &m_attachmentData;
}

} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE

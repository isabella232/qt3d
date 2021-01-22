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

#include "mousehandler_p.h"

#include <Qt3DInput/qmousehandler.h>
#include <Qt3DInput/qmousedevice.h>

#include <Qt3DInput/private/inputmanagers_p.h>
#include <Qt3DInput/private/inputhandler_p.h>
#include <Qt3DInput/private/mousedevice_p.h>
#include <Qt3DInput/private/qmousehandler_p.h>

QT_BEGIN_NAMESPACE

using namespace Qt3DCore;

namespace Qt3DInput {
namespace Input {

MouseHandler::MouseHandler()
    : BackendNode(ReadWrite)
    , m_inputHandler(nullptr)
{
}

MouseHandler::~MouseHandler()
{
}

Qt3DCore::QNodeId MouseHandler::mouseDevice() const
{
    return m_mouseDevice;
}

void MouseHandler::setInputHandler(InputHandler *handler)
{
    m_inputHandler = handler;
}

void MouseHandler::syncFromFrontEnd(const Qt3DCore::QNode *frontEnd, bool firstTime)
{
    BackendNode::syncFromFrontEnd(frontEnd, firstTime);
    const Qt3DInput::QMouseHandler *node = qobject_cast<const Qt3DInput::QMouseHandler *>(frontEnd);
    if (!node)
        return;

    const auto newId = Qt3DCore::qIdForNode(node->sourceDevice());
    if (m_mouseDevice != newId)
        setDevice(newId);
}

void MouseHandler::setDevice(Qt3DCore::QNodeId device)
{
    m_mouseDevice = device;
}

MouseHandlerFunctor::MouseHandlerFunctor(InputHandler *handler)
    : m_handler(handler)
{
}

Qt3DCore::QBackendNode *MouseHandlerFunctor::create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const
{
    MouseHandler *input = m_handler->mouseInputManager()->getOrCreateResource(change->subjectId());
    input->setInputHandler(m_handler);
    return input;
}

Qt3DCore::QBackendNode *MouseHandlerFunctor::get(Qt3DCore::QNodeId id) const
{
    return m_handler->mouseInputManager()->lookupResource(id);
}

void MouseHandlerFunctor::destroy(Qt3DCore::QNodeId id) const
{
    m_handler->mouseInputManager()->releaseResource(id);
}

} // namespace Input
} // namespace Qt3DInput

QT_END_NAMESPACE

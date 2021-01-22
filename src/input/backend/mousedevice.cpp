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

#include "mousedevice_p.h"

#include <Qt3DInput/qmousedevice.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qnode.h>

#include <Qt3DInput/private/inputmanagers_p.h>
#include <Qt3DInput/private/inputhandler_p.h>
#include <Qt3DInput/private/qmousedevice_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DInput {
namespace Input {

MouseDevice::MouseDevice()
    : QAbstractPhysicalDeviceBackendNode(ReadOnly)
    , m_inputHandler(nullptr)
    , m_wasPressed(false)
    , m_sensitivity(0.1f)
    , m_updateAxesContinuously(false)
{
}

MouseDevice::~MouseDevice()
{
}

void MouseDevice::setInputHandler(InputHandler *handler)
{
    m_inputHandler = handler;
}

InputHandler *MouseDevice::inputHandler() const
{
    return m_inputHandler;
}

float MouseDevice::axisValue(int axisIdentifier) const
{
    switch (axisIdentifier) {
    case QMouseDevice::X:
        return m_mouseState.xAxis;
    case QMouseDevice::Y:
        return m_mouseState.yAxis;
    case QMouseDevice::WheelX:
        return m_mouseState.wXAxis;
    case QMouseDevice::WheelY:
        return m_mouseState.wYAxis;
    default:
        break;
    }
    return 0.0f;
}

bool MouseDevice::isButtonPressed(int buttonIdentifier) const
{
    switch (buttonIdentifier) {
    case QMouseEvent::LeftButton:
        return m_mouseState.leftPressed;
    case QMouseEvent::MiddleButton:
        return m_mouseState.centerPressed;
    case QMouseEvent::RightButton:
        return m_mouseState.rightPressed;
    default:
        break;
    }
    return false;
}

MouseDevice::MouseState MouseDevice::mouseState() const
{
    return m_mouseState;
}

QPointF MouseDevice::previousPos() const
{
    return m_previousPos;
}

bool MouseDevice::wasPressed() const
{
    return m_wasPressed;
}

float MouseDevice::sensitivity() const
{
    return m_sensitivity;
}

bool MouseDevice::updateAxesContinuously() const
{
    return m_updateAxesContinuously;
}

#if QT_CONFIG(wheelevent)
void MouseDevice::updateWheelEvents(const QList<QT_PREPEND_NAMESPACE (QWheelEvent)> &events)
{
    // Reset axis values before we accumulate new values for this frame
    m_mouseState.wXAxis = 0.0f;
    m_mouseState.wYAxis = 0.0f;
    if (!events.isEmpty()) {
        for (const QT_PREPEND_NAMESPACE(QWheelEvent) &e : events) {
            m_mouseState.wXAxis += m_sensitivity * e.angleDelta().x();
            m_mouseState.wYAxis += m_sensitivity * e.angleDelta().y();
        }
    }
}
#endif

// Main Thread
void MouseDevice::updateMouseEvents(const QList<QT_PREPEND_NAMESPACE(QMouseEvent)> &events)
{
    // Reset axis values before we accumulate new values for this frame
    m_mouseState.xAxis = 0.0f;
    m_mouseState.yAxis = 0.0f;

    if (!events.isEmpty()) {
        for (const QT_PREPEND_NAMESPACE(QMouseEvent) &e : events) {
            m_mouseState.leftPressed = e.buttons() & (Qt::LeftButton);
            m_mouseState.centerPressed = e.buttons() & (Qt::MiddleButton);
            m_mouseState.rightPressed = e.buttons() & (Qt::RightButton);
            const bool pressed = m_mouseState.leftPressed || m_mouseState.centerPressed || m_mouseState.rightPressed;
            if (m_updateAxesContinuously || (m_wasPressed && pressed)) {
                m_mouseState.xAxis += m_sensitivity * (e.screenPos().x() - m_previousPos.x());
                m_mouseState.yAxis += m_sensitivity * (m_previousPos.y() - e.screenPos().y());
            }
            m_wasPressed = pressed;
            m_previousPos = e.screenPos();
        }
    }
}

void MouseDevice::syncFromFrontEnd(const Qt3DCore::QNode *frontEnd, bool firstTime)
{
    QAbstractPhysicalDeviceBackendNode::syncFromFrontEnd(frontEnd, firstTime);
    const Qt3DInput::QMouseDevice *node = qobject_cast<const Qt3DInput::QMouseDevice *>(frontEnd);
    if (!node)
        return;

    m_sensitivity = node->sensitivity();
    m_updateAxesContinuously = node->updateAxesContinuously();
}

MouseDeviceFunctor::MouseDeviceFunctor(QInputAspect *inputAspect, InputHandler *handler)
    : m_inputAspect(inputAspect)
    , m_handler(handler)
{
}

Qt3DCore::QBackendNode *MouseDeviceFunctor::create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const
{
    MouseDevice *controller = m_handler->mouseDeviceManager()->getOrCreateResource(change->subjectId());
    controller->setInputAspect(m_inputAspect);
    controller->setInputHandler(m_handler);
    m_handler->appendMouseDevice(m_handler->mouseDeviceManager()->lookupHandle(change->subjectId()));
    return controller;
}

Qt3DCore::QBackendNode *MouseDeviceFunctor::get(Qt3DCore::QNodeId id) const
{
    return m_handler->mouseDeviceManager()->lookupResource(id);
}

void MouseDeviceFunctor::destroy(Qt3DCore::QNodeId id) const
{
    m_handler->removeMouseDevice(m_handler->mouseDeviceManager()->lookupHandle(id));
    m_handler->mouseDeviceManager()->releaseResource(id);
}

} // namespace Input
} // namespace Qt3DInput

QT_END_NAMESPACE

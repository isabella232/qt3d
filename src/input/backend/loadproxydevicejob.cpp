/****************************************************************************
**
** Copyright (C) 2016 Klaralvdalens Datakonsult AB (KDAB).
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

#include "loadproxydevicejob_p.h"
#include <Qt3DCore/private/qaspectmanager_p.h>
#include <Qt3DInput/private/qabstractphysicaldeviceproxy_p.h>
#include <Qt3DInput/private/qabstractphysicaldeviceproxy_p_p.h>
#include <Qt3DInput/private/inputhandler_p.h>
#include <Qt3DInput/private/inputmanagers_p.h>
#include <Qt3DInput/private/job_common_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DInput {
namespace Input {

class LoadProxyDeviceJobPrivate : public Qt3DCore::QAspectJobPrivate
{
public:
    LoadProxyDeviceJobPrivate() { }
    ~LoadProxyDeviceJobPrivate() override { }

    void postFrame(Qt3DCore::QAspectManager *manager) override;

    QVector<QPair<Qt3DCore::QNodeId, QAbstractPhysicalDevice *>> updates;
};

LoadProxyDeviceJob::LoadProxyDeviceJob()
    : Qt3DCore::QAspectJob(*new LoadProxyDeviceJobPrivate)
    , m_inputHandler(nullptr)
{
    SET_JOB_RUN_STAT_TYPE(this, JobTypes::DeviceProxyLoading, 0)
}

LoadProxyDeviceJob::~LoadProxyDeviceJob()
{
}

void LoadProxyDeviceJob::setProxiesToLoad(const QVector<Qt3DCore::QNodeId> &wrappers)
{
    m_proxies = wrappers;
}

void LoadProxyDeviceJob::setInputHandler(InputHandler *handler)
{
    m_inputHandler = handler;
}

InputHandler *LoadProxyDeviceJob::inputHandler() const
{
    return m_inputHandler;
}

QVector<Qt3DCore::QNodeId> LoadProxyDeviceJob::proxies() const
{
    return m_proxies;
}

void LoadProxyDeviceJob::run()
{
    Q_D(LoadProxyDeviceJob);
    d->updates.reserve(m_proxies.size());

    Q_ASSERT(m_inputHandler);
    for (const Qt3DCore::QNodeId id : qAsConst(m_proxies)) {
        PhysicalDeviceProxy *proxy = m_inputHandler->physicalDeviceProxyManager()->lookupResource(id);
        QAbstractPhysicalDevice *device = m_inputHandler->createPhysicalDevice(proxy->deviceName());
        if (device != nullptr)
            proxy->setDevice(device);
    }
}

void LoadProxyDeviceJobPrivate::postFrame(Qt3DCore::QAspectManager *manager)
{
    for (const auto &res : qAsConst(updates)) {
        QAbstractPhysicalDeviceProxy *node = qobject_cast<QAbstractPhysicalDeviceProxy *>(manager->lookupNode(res.first));
        if (!node)
            continue;

        auto *device = res.second;
        QAbstractPhysicalDeviceProxyPrivate *dnode = static_cast<QAbstractPhysicalDeviceProxyPrivate *>(QAbstractPhysicalDeviceProxyPrivate::get(node));
        QAbstractPhysicalDevice *oldDevice = dnode->m_device;
        dnode->setDevice(device);
        // Delete the old device if it existed
        delete oldDevice;
    }

    updates.clear();
}


} // namespace Input
} // namespace Qt3DInput

QT_END_NAMESPACE

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

#ifndef QT3DINPUT_INPUT_PHYSICALDEVICEPROXY_P_H
#define QT3DINPUT_INPUT_PHYSICALDEVICEPROXY_P_H

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

#include <Qt3DInput/private/backendnode_p.h>
#include <Qt3DCore/qnodeid.h>

QT_BEGIN_NAMESPACE

namespace Qt3DInput {

class QAbstractPhysicalDevice;

namespace Input {

class PhysicalDeviceProxyManager;

class Q_AUTOTEST_EXPORT PhysicalDeviceProxy : public BackendNode
{
public:
    PhysicalDeviceProxy();
    void cleanup();

    QString deviceName() const;

    void setManager(PhysicalDeviceProxyManager *manager);
    PhysicalDeviceProxyManager *manager() const;

    // Called from a job to update the frontend
    void setDevice(QAbstractPhysicalDevice *device);
    Qt3DCore::QNodeId physicalDeviceId() const;

    void syncFromFrontEnd(const Qt3DCore::QNode *frontEnd, bool firstTime) override;

private:
    QString m_deviceName;
    PhysicalDeviceProxyManager *m_manager;
    Qt3DCore::QNodeId m_physicalDeviceId;
};

class PhysicalDeviceProxyNodeFunctor: public Qt3DCore::QBackendNodeMapper
{
public:
    explicit PhysicalDeviceProxyNodeFunctor(PhysicalDeviceProxyManager *manager);

    Qt3DCore::QBackendNode *create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const final;
    Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const final;
    void destroy(Qt3DCore::QNodeId id) const final;

private:
    PhysicalDeviceProxyManager *m_manager;
};

} // namespace Input

} // namespace Qt3DInput

QT_END_NAMESPACE

#endif // QT3DINPUT_INPUT_PHYSICALDEVICEPROXY_P_H

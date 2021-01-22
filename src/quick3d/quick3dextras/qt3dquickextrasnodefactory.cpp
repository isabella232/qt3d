/****************************************************************************
**
** Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB).
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

#include "qt3dquickextrasnodefactory_p.h"

QT_BEGIN_NAMESPACE

namespace Qt3DExtras {

Q_GLOBAL_STATIC(QuickExtrasNodeFactory, quick_extras_node_factory)

QuickExtrasNodeFactory *QuickExtrasNodeFactory::instance()
{
    return quick_extras_node_factory();
}

void QuickExtrasNodeFactory::registerType(const char *className, const char *quickName, int major, int minor)
{
    m_types.insert(className, Type(quickName, major, minor));
}

Qt3DCore::QNode *QuickExtrasNodeFactory::createNode(const char *type)
{
    if (!m_types.contains(type))
        return nullptr;

    Type &typeInfo(m_types[type]);

    if (!typeInfo.resolved) {
        typeInfo.resolved = true;
        typeInfo.t = QQmlMetaType::qmlType(QString::fromLatin1(typeInfo.quickName), typeInfo.version.first, typeInfo.version.second);
    }

    return typeInfo.t.isValid() ? qobject_cast<Qt3DCore::QNode *>(typeInfo.t.create()) : nullptr;
}

} // namespace Qt3DExtras

QT_END_NAMESPACE

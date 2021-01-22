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

#ifndef QT3DQUICKEXTRAS_GLOBAL_P_H
#define QT3DQUICKEXTRAS_GLOBAL_P_H

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

#include <Qt3DQuickExtras/qt3dquickextras_global.h>
#include <QtQml/qqml.h>

#define Q_3DQUICKEXTRASSHARED_PRIVATE_EXPORT Q_3DQUICKEXTRASSHARED_EXPORT

QT_BEGIN_NAMESPACE

namespace Qt3DExtras {
namespace Quick {

Q_3DQUICKEXTRASSHARED_PRIVATE_EXPORT void Quick3DExtras_initialize();
Q_3DQUICKEXTRASSHARED_PRIVATE_EXPORT void Quick3DExtras_registerType(const char *className, const char *quickName, int major, int minor);

template<class T, class E> void registerExtendedType(const char *className, const char *quickName,
                                                     const char *uri, int major, int minor, const char *name)
{
    qmlRegisterExtendedType<T, E>(uri, major, minor, name);
    Quick3DExtras_registerType(className, quickName, major, minor);
}

} // Quick
} // Qt3DExtras

QT_END_NAMESPACE

#endif // QT3DQUICKEXTRAS_GLOBAL_P_H

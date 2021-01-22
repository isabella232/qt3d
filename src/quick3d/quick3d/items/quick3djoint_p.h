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

#ifndef QT3DCORE_QUICK_QUICK3DJOINT_P_H
#define QT3DCORE_QUICK_QUICK3DJOINT_P_H

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

#include <QObject>
#include <Qt3DCore/qjoint.h>
#include <QtQml/QQmlListProperty>

#include <Qt3DQuick/private/qt3dquick_global_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {
namespace Quick {

class Q_3DQUICKSHARED_PRIVATE_EXPORT Quick3DJoint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Qt3DCore::QJoint> childJoints READ childJoints)
public:
    explicit Quick3DJoint(QObject *parent = nullptr);

    QQmlListProperty<Qt3DCore::QJoint> childJoints();

    inline QJoint *parentJoint() const { return qobject_cast<QJoint*>(parent()); }

private:
    static void appendJoint(QQmlListProperty<Qt3DCore::QJoint> *list, Qt3DCore::QJoint *obj);
    static QJoint *jointAt(QQmlListProperty<Qt3DCore::QJoint> *list, int index);
    static int jointCount(QQmlListProperty<Qt3DCore::QJoint> *list);
    static void clearJoints(QQmlListProperty<Qt3DCore::QJoint> *list);
};

} // namespace Quick
} // namespace Qt3DCore

QT_END_NAMESPACE

#endif // QT3DCORE_QUICK_QUICK3DJOINT_P_H

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

#ifndef QT3DINPUT_INPUT_QUICK_QUICK3DINPUTSEQUENCE_H
#define QT3DINPUT_INPUT_QUICK_QUICK3DINPUTSEQUENCE_H

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

#include <Qt3DInput/qinputsequence.h>
#include <QtQml/QQmlListProperty>

#include <Qt3DQuickInput/private/qt3dquickinput_global_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DInput {
namespace Input {
namespace Quick {

class Q_3DQUICKINPUTSHARED_PRIVATE_EXPORT Quick3DInputSequence : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Qt3DInput::QAbstractActionInput> sequences READ qmlActionInputs CONSTANT)
public:
    explicit Quick3DInputSequence(QObject *parent = nullptr);

    inline QInputSequence *parentSequence() const { return qobject_cast<QInputSequence *>(parent()); }
    QQmlListProperty<QAbstractActionInput> qmlActionInputs();

private:
    static void appendActionInput(QQmlListProperty<QAbstractActionInput> *list, QAbstractActionInput *input);
    static QAbstractActionInput *actionInputAt(QQmlListProperty<QAbstractActionInput> *list, int index);
    static int actionInputCount(QQmlListProperty<QAbstractActionInput> *list);
    static void clearActionInputs(QQmlListProperty<QAbstractActionInput> *list);
};

} // namespace Quick
} // namespace Input
} // namespace Qt3DInput

QT_END_NAMESPACE


#endif // QT3DINPUT_INPUT_QUICK_QUICK3DINPUTSEQUENCE_H

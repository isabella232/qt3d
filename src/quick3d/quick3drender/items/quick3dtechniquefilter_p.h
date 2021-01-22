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

#ifndef QT3DRENDER_RENDER_QUICK_QUICK3DTECHNIQUEFILTER_P_H
#define QT3DRENDER_RENDER_QUICK_QUICK3DTECHNIQUEFILTER_P_H

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

#include <Qt3DRender/qfilterkey.h>
#include <Qt3DRender/qtechniquefilter.h>
#include <QtQml/QQmlListProperty>

#include <Qt3DQuick/private/quick3dnode_p.h>
#include <Qt3DQuickRender/private/qt3dquickrender_global_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {
namespace Render {
namespace Quick {

class Q_3DQUICKRENDERSHARED_PRIVATE_EXPORT Quick3DTechniqueFilter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Qt3DRender::QFilterKey> matchAll READ matchList)
    Q_PROPERTY(QQmlListProperty<Qt3DRender::QParameter> parameters READ parameterList)

public:
    explicit Quick3DTechniqueFilter(QObject *parent = 0);

    QQmlListProperty<QFilterKey> matchList();
    QQmlListProperty<QParameter> parameterList();

    inline QTechniqueFilter *parentTechniqueFilter() const { return qobject_cast<QTechniqueFilter*>(parent()); }

private:
    static void appendRequire(QQmlListProperty<QFilterKey> *list, QFilterKey *criterion);
    static QFilterKey *requireAt(QQmlListProperty<QFilterKey> *list, int index);
    static int requiresCount(QQmlListProperty<QFilterKey> *list);
    static void clearRequires(QQmlListProperty<QFilterKey> *list);

    static void appendParameter(QQmlListProperty<QParameter> *list, QParameter *param);
    static QParameter *parameterAt(QQmlListProperty<QParameter> *list, int index);
    static int parametersCount(QQmlListProperty<QParameter> *list);
    static void clearParameterList(QQmlListProperty<QParameter> *list);
};

} // namespace Quick
} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_QUICK_QUICK3DTECHNIQUEFILTER_P_H

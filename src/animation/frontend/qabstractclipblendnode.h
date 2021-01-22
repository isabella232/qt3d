/****************************************************************************
**
** Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
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
****************************************************************************/

#ifndef QT3DANIMATION_QABSTRACTCLIPBLENDNODE_H
#define QT3DANIMATION_QABSTRACTCLIPBLENDNODE_H

#include <Qt3DAnimation/qt3danimation_global.h>
#include <Qt3DCore/qnode.h>

QT_BEGIN_NAMESPACE

namespace Qt3DAnimation {

class QAbstractAnimationClip;
class QAbstractClipBlendNodePrivate;

class Q_3DANIMATIONSHARED_EXPORT QAbstractClipBlendNode : public Qt3DCore::QNode
{
    Q_OBJECT
public:
    ~QAbstractClipBlendNode();

protected:
    explicit QAbstractClipBlendNode(Qt3DCore::QNode *parent = nullptr);
    explicit QAbstractClipBlendNode(QAbstractClipBlendNodePrivate &dd, Qt3DCore::QNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QAbstractClipBlendNode)
};


} // Qt3DAnimation

QT_END_NAMESPACE


#endif // QT3DANIMATION_QABSTRACTCLIPBLENDNODE_H

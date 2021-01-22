/****************************************************************************
**
** Copyright (C) 2018 Klaralvdalens Datakonsult AB (KDAB).
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

#ifndef QT3DRENDER_QSETFENCE_P_H
#define QT3DRENDER_QSETFENCE_P_H

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

#include <Qt3DRender/private/qframegraphnode_p.h>
#include <Qt3DRender/qsetfence.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

class QSetFencePrivate : public QFrameGraphNodePrivate
{
public:
    QSetFencePrivate();
    void setHandleType(QSetFence::HandleType type);
    void setHandle(QVariant handle);

    QSetFence::HandleType m_handleType;
    QVariant m_handle;

    Q_DECLARE_PUBLIC(QSetFence)
};

struct QSetFenceData
{
};

} // Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_QSETFENCE_P_H

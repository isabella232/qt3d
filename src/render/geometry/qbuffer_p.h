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

#ifndef QT3DRENDER_QBUFFER_P_H
#define QT3DRENDER_QBUFFER_P_H

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

#include <Qt3DCore/private/qnode_p.h>
#include <Qt3DRender/qbuffer.h>
#include <Qt3DRender/qbufferdatagenerator.h>
#include <Qt3DRender/qt3drender_global.h>
#include <private/qnode_p.h>
#include <QByteArray>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

class Q_3DRENDERSHARED_EXPORT QBufferPrivate : public Qt3DCore::QNodePrivate
{
public:
    Q_DECLARE_PUBLIC(QBuffer)

    QBufferPrivate();

    QByteArray m_data;
    QBuffer::BufferType m_type;
    QBuffer::UsageType m_usage;
    QBufferDataGeneratorPtr m_functor;
    bool m_syncData;
    QBuffer::AccessType m_access;

    void setData(const QByteArray &data);

    static const char *UpdateDataPropertyName;
};

struct QBufferData
{
    QByteArray data;
    QBuffer::UsageType usage;
    QBufferDataGeneratorPtr functor;
    bool syncData;
    QBuffer::AccessType access;
};

struct QBufferUpdate
{
    int offset;
    QByteArray data;
};

} // namespace Qt3DRender

QT_END_NAMESPACE
Q_DECLARE_METATYPE(Qt3DRender::QBufferUpdate) // LCOV_EXCL_LINE

#endif // QT3DRENDER_QBUFFER_P_H

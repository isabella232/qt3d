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

#ifndef QT3DCORE_QBACKENDNODE_H
#define QT3DCORE_QBACKENDNODE_H

#include <Qt3DCore/qnodecreatedchange.h>
#include <Qt3DCore/qnodeid.h>
#include <Qt3DCore/qnodecommand.h>
#include <Qt3DCore/qscenechange.h>
#include <Qt3DCore/qt3dcore_global.h>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {

class QBackendNodePrivate;
class QBackendNode;
class QAspectEngine;

#if defined(QT_BUILD_INTERNAL)
class QBackendNodeTester;
#endif

class Q_3DCORESHARED_EXPORT QBackendNodeMapper
{
public:
    virtual ~QBackendNodeMapper();
    virtual QBackendNode *create(const QNodeCreatedChangeBasePtr &change) const = 0;        // TODO QT6 change to only take a NodeId
    virtual QBackendNode *get(QNodeId id) const = 0;
    virtual void destroy(QNodeId id) const = 0;
};

typedef QSharedPointer<QBackendNodeMapper> QBackendNodeMapperPtr;

class Q_3DCORESHARED_EXPORT QBackendNode
{
public:
    enum Mode {
        ReadOnly = 0,
        ReadWrite
    };

    explicit QBackendNode(Mode mode = ReadOnly);
    virtual ~QBackendNode();

    QNodeId peerId() const Q_DECL_NOEXCEPT;

    void setEnabled(bool enabled) Q_DECL_NOEXCEPT;
    bool isEnabled() const Q_DECL_NOEXCEPT;

    Mode mode() const Q_DECL_NOEXCEPT;

protected:
    Q_DECLARE_PRIVATE(QBackendNode)
    explicit QBackendNode(QBackendNodePrivate &dd);
    Q3D_DECL_DEPRECATED void notifyObservers(const QSceneChangePtr &e);
    Q3D_DECL_DEPRECATED QNodeCommand::CommandId sendCommand(const QString &name, const QVariant &data,
                                                          QNodeCommand::CommandId replyTo = QNodeCommand::CommandId());
    Q3D_DECL_DEPRECATED void sendReply(const QNodeCommandPtr &command);
    Q3D_DECL_DEPRECATED virtual void sceneChangeEvent(const QSceneChangePtr &e);

    QBackendNodePrivate *d_ptr;

private:
    Q_DISABLE_COPY(QBackendNode)
    void setPeerId(QNodeId id) Q_DECL_NOEXCEPT;
    Q3D_DECL_DEPRECATED virtual void initializeFromPeer(const QNodeCreatedChangeBasePtr &change);

    friend class QBackendNodePropertyChange;
    friend class QAbstractAspectPrivate;
#if defined(QT_BUILD_INTERNAL)
    friend class QBackendNodeTester;
#endif
};

} // namespace Qt3DCore

QT_END_NAMESPACE

#endif // QT3DCORE_QBACKENDNODE_H

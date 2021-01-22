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

#include "qpropertynodeaddedchange.h"
#include "qpropertynodeaddedchange_p.h"

#include <Qt3DCore/private/qnode_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {

QPropertyNodeAddedChangePrivate::QPropertyNodeAddedChangePrivate()
    : QStaticPropertyValueAddedChangeBasePrivate()
    , m_addedNodeIdTypePair()
{
}

/*!
 * \class Qt3DCore::QPropertyNodeAddedChange
 * \inheaderfile Qt3DCore/QPropertyNodeAddedChange
 * \inherits Qt3DCore::QStaticPropertyValueAddedChangeBase
 * \inmodule Qt3DCore
 * \brief Used to notify when a node is added to a property.
 *
 */

/*!
 * \typedef Qt3DCore::QPropertyNodeAddedChangePtr
 * \relates Qt3DCore::QPropertyNodeAddedChange
 *
 * A shared pointer for QPropertyNodeAddedChange.
 */

/*!
 * Constructs a new QPropertyNodeAddedChange with \a subjectId, \a node.
 */
QPropertyNodeAddedChange::QPropertyNodeAddedChange(QNodeId subjectId, QNode *node)
    : QStaticPropertyValueAddedChangeBase(*new QPropertyNodeAddedChangePrivate, subjectId)
{
    Q_D(QPropertyNodeAddedChange);
    Q_ASSERT(node);
    d->m_addedNodeIdTypePair = QNodeIdTypePair(node->id(), QNodePrivate::findStaticMetaObject(node->metaObject()));

    // Ensure the node has issued a node creation change. We can end
    // up here if a newly created node with a parent is immediately set
    // as a property on another node. In this case the deferred call to
    // _q_postConstructorInit() will not have happened yet as the event
    // loop will still be blocked. So force it here and we catch this
    // eventuality in the _q_postConstructorInit() function so that we
    // do not repeat the creation and new child scene change events.
    QNodePrivate::get(node)->_q_ensureBackendNodeCreated();
}

/*! \internal */
QPropertyNodeAddedChange::~QPropertyNodeAddedChange()
{
}

/*!
 * \return the id of the node added to the property.
 */
QNodeId QPropertyNodeAddedChange::addedNodeId() const
{
    Q_D(const QPropertyNodeAddedChange);
    return d->m_addedNodeIdTypePair.id;
}

/*!
 * \return the meta object of the node added to the property.
 */
const QMetaObject *QPropertyNodeAddedChange::metaObject() const
{
    Q_D(const QPropertyNodeAddedChange);
    return d->m_addedNodeIdTypePair.type;
}

} // namespace Qt3DCore

QT_END_NAMESPACE

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

#include "qscenechange.h"

#include "qscenechange_p.h"

QT_BEGIN_NAMESPACE

namespace Qt3DCore {

/*!
 * \enum Qt3DCore::ChangeFlag
 * \relates Qt3DCore::QSceneChange
 * \obsolete
 *
 * The types of change that can be sent and received by Qt3D's change notification system.
 *
 * \value NodeCreated A new instance of a QNode subclass has been created.
 * \value NodeDeleted A QNode has been deleted.
 * \value PropertyUpdated A QNode property has been updated.
 * \value PropertyValueAdded A QNode has been added to the scene.
 * \value PropertyValueRemoved A QNode has been removed from the scene.
 * \value CommandRequested A QNodeCommand has been sent between a node and its backend.
 * \value ComponentAdded A QComponent has been added to a QEntity.
 * \value ComponentRemoved A QComponent has been removed from a QEntity.
 * \value CallbackTriggered A QNode triggered a callback.
 * \value AllChanges Allows an observer to monitor for any of the above changes.
 */

QSceneChangePrivate::QSceneChangePrivate()
    : q_ptr(nullptr)
    , m_subjectId()
    , m_deliveryFlags(QSceneChange::BackendNodes)
    , m_type(AllChanges)
{
}

QSceneChangePrivate::~QSceneChangePrivate()
{
}

/*!
 * \class Qt3DCore::QSceneChange
 * \inheaderfile Qt3DCore/QSceneChange
 * \inmodule Qt3DCore
 * \brief The base class for changes that can be sent and received by Qt3D's change notification system.
 */

/*!
 * \typedef Qt3DCore::QSceneChangePtr
 * \relates Qt3DCore::QSceneChange
 *
 * A shared pointer for QSceneChange.
 */

/*!
 * \enum QSceneChange::DeliveryFlag
 *
 * The types of change that can be sent and received by Qt3D's change notification system.
 *
 * \value BackendNodes
 * \value Nodes
 * \value DeliverToAll
 */

/*!
 * Constructs a new QSceneChange with \a type and \a subjectId.
 */
QSceneChange::QSceneChange(ChangeFlag type, QNodeId subjectId)
    : d_ptr(new QSceneChangePrivate)
{
    d_ptr->q_ptr = this;
    Q_D(QSceneChange);
    d->m_type = type;
    d->m_subjectId = subjectId;
}

/*! \internal */
QSceneChange::QSceneChange(QSceneChangePrivate &dd,
                           ChangeFlag type, QNodeId subjectId)
    : d_ptr(&dd)
{
    d_ptr->q_ptr = this;
    Q_D(QSceneChange);
    d->m_type = type;
    d->m_subjectId = subjectId;
}

QSceneChange::~QSceneChange()
{
    delete d_ptr;
}

/*!
 * Returns the scene change type.
 */
ChangeFlag QSceneChange::type() const Q_DECL_NOTHROW
{
    Q_D(const QSceneChange);
    return d->m_type;
}

/*!
  Sets the delivery flags of the change to \a flags.
  */
void QSceneChange::setDeliveryFlags(DeliveryFlags flags) Q_DECL_NOTHROW
{
    Q_D(QSceneChange);
    d->m_deliveryFlags = flags;
}

/*!
 Returns the set delivery flags.
 */
QSceneChange::DeliveryFlags QSceneChange::deliveryFlags() const Q_DECL_NOTHROW
{
    Q_D(const QSceneChange);
    return d->m_deliveryFlags;
}

/*!
 * \return scene change subject id.
 */
QNodeId QSceneChange::subjectId() const Q_DECL_NOTHROW
{
    Q_D(const QSceneChange);
    return d->m_subjectId;
}

} // Qt3D

QT_END_NAMESPACE

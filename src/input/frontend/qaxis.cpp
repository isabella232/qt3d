/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
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
****************************************************************************/

#include "qaxis.h"
#include "qaxis_p.h"

#include <Qt3DInput/qabstractaxisinput.h>
#include <Qt3DCore/qnodecreatedchange.h>

QT_BEGIN_NAMESPACE

namespace Qt3DInput {

/*!
    Constructs a new QAxis instance with \a parent.
    \class Qt3DInput::QAxis
    \inmodule Qt3DInput
    \inherits Qt3DCore::QNode
    \brief QAxis stores QAbstractAxisInputs used to trigger an input event.
    \since 5.7
*/

/*!
    \qmltype Axis
    \inqmlmodule Qt3D.Input
    \instantiates Qt3DInput::QAxis
    \brief QML frontend for the Qt3DInput::QAxis C++ class.

    Links a set of AbstractAxisInputs that trigger the same event.
    \since 5.7
*/

/*!
    \qmlproperty int QAxis::value
    \readonly

    Holds the value of the axis.

    Note this property is not updated when the axis is disabled.
*/

/*!
    Constructs a new QAxis instance with parent \a parent.
 */
QAxis::QAxis(Qt3DCore::QNode *parent)
    : Qt3DCore::QNode(*new QAxisPrivate(), parent)
{
    Q_D(QAxis);
    connect(this, &QAxis::enabledChanged, [d]() {
        d->setValue(0.);
    });
}

/*! \internal */
QAxis::~QAxis()
{
}

/*!
  \qmlproperty list<AbstractAxisInput>  Qt3D.Input::Axis::inputs

  the list of AbstractAxisInput that can trigger this Axis.
*/

/*!
    QAxis::addInput
    Adds an \a input for the axis.

    \sa Qt3DInput::QAbstractAxisInput
 */
void QAxis::addInput(QAbstractAxisInput *input)
{
    Q_D(QAxis);
    if (!d->m_inputs.contains(input)) {
        d->m_inputs.push_back(input);

        if (!input->parent())
            input->setParent(this);

        // Ensures proper bookkeeping
        d->registerDestructionHelper(input, &QAxis::removeInput, d->m_inputs);
        d->updateNode(input, "input", Qt3DCore::PropertyValueAdded);
    }
}

/*!
    \qmlproperty QVariantList Qt3D.Input::Axis::buttons

    The Buttons that can trigger this Action
*/

/*!
    QAxis::removeInput

    Removes an \a input from the axis.

    \sa Qt3DInput::QAbstractAxisInput
 */
void QAxis::removeInput(QAbstractAxisInput *input)
{
    Q_D(QAxis);
    if (d->m_inputs.contains(input)) {

        d->updateNode(input, "input", Qt3DCore::PropertyValueRemoved);

        d->m_inputs.removeOne(input);

        // Remove bookkeeping connection
        d->unregisterDestructionHelper(input);
    }
}

/*!
    QAxis::inputs

    \return vector of all inputs added to the axis.
 */
QVector<QAbstractAxisInput *> QAxis::inputs() const
{
    Q_D(const QAxis);
    return d->m_inputs;
}

/*!
  \property QAxis::value

  The value of the axis.
 */
float QAxis::value() const
{
    Q_D(const QAxis);
    return d->m_value;
}

// TODO Unused remove in Qt6
void QAxis::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &)
{
}

Qt3DCore::QNodeCreatedChangeBasePtr QAxis::createNodeCreationChange() const
{
    auto creationChange = Qt3DCore::QNodeCreatedChangePtr<QAxisData>::create(this);
    auto &data = creationChange->data;
    data.inputIds = qIdsForNodes(inputs());
    return creationChange;
}

} // Qt3DInput

QT_END_NAMESPACE

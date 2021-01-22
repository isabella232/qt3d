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

#ifndef QT3DINPUT_INPUT_KEYEVENTDISPATCHERJOB_P_H
#define QT3DINPUT_INPUT_KEYEVENTDISPATCHERJOB_P_H

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

#include <Qt3DInput/QKeyEvent>
#include <Qt3DCore/qaspectjob.h>
#include <Qt3DCore/qnodeid.h>

QT_BEGIN_NAMESPACE

namespace Qt3DInput {
namespace Input {

class InputHandler;
class KeyEventDispatcherJobPrivate;

class KeyEventDispatcherJob : public Qt3DCore::QAspectJob
{
public:
    explicit KeyEventDispatcherJob(Qt3DCore::QNodeId input, const QList<QT_PREPEND_NAMESPACE(QKeyEvent)> &events);
    void setInputHandler(InputHandler *handler);
    void run() override;

private:
    Q_DECLARE_PRIVATE(KeyEventDispatcherJob)

    InputHandler *m_inputHandler;
};

} // namespace Input
} // namespace Qt3DInput

QT_END_NAMESPACE

#endif // QT3DINPUT_INPUT_KEYEVENTDISPATCHERJOB_P_H

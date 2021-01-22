/****************************************************************************
**
** Copyright (C) 2020 Klaralvdalens Datakonsult AB (KDAB).
** Copyright (C) 2016 Paul Lemire <paul.lemire350@gmail.com>
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

#ifndef QT3DRENDER_DEBUG_COMMANDEXECUTER_H
#define QT3DRENDER_DEBUG_COMMANDEXECUTER_H

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

#include <QVector>
#include <QVariant>
#include <QMutex>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {

namespace Debug {
class AsynchronousCommandReply;
} // Debug

} // Qt3DCore

namespace Qt3DRender {

namespace Render {
namespace Rhi {
class Renderer;
class RenderView;
} // Rhi
} // Render

namespace Debug {

class CommandExecuter
{
public:
    explicit CommandExecuter(Render::Rhi::Renderer *renderer);

    void performAsynchronousCommandExecution(const QVector<Render::Rhi::RenderView *> &views);

    QVariant executeCommand(const QStringList &args);

private:
    Render::Rhi::Renderer *m_renderer;
    QVector<Qt3DCore::Debug::AsynchronousCommandReply *> m_pendingCommands;
    QMutex m_pendingCommandsMutex;
};

} // Debug

} // Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_DEBUG_COMMANDEXECUTER_H

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

#include "corelogging_p.h"

QT_BEGIN_NAMESPACE

namespace Qt3DCore {

Q_LOGGING_CATEGORY(Nodes, "Qt3D.Core.Nodes", QtWarningMsg);
Q_LOGGING_CATEGORY(Aspects, "Qt3D.Core.Aspects", QtWarningMsg);
Q_LOGGING_CATEGORY(Resources, "Qt3D.Core.Resources", QtWarningMsg);
Q_LOGGING_CATEGORY(ChangeArbiter, "Qt3D.Core.ChangeArbiter", QtWarningMsg);

} // Qt3D

QT_END_NAMESPACE

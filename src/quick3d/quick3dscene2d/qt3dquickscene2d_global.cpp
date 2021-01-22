/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

#include "qt3dquickscene2d_global_p.h"
#include "qt3dquickscene2dnodefactory_p.h"

QT_BEGIN_NAMESPACE

namespace Qt3DRender {
namespace Quick {

void Quick3DScene2D_initialize()
{
    Qt3DCore::QAbstractNodeFactory::registerNodeFactory(QuickScene2DNodeFactory::instance());
}

void Quick3DScene2D_registerType(const char *className, const char *quickName, int major, int minor)
{
    QuickScene2DNodeFactory::instance()->registerType(className, quickName, major, minor);
}

} // namespace Quick
} // namespace Qt3DRender

QT_END_NAMESPACE

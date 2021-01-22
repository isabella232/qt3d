/****************************************************************************
**
** Copyright (C) 2016 Paul Lemire
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

#include "lightgatherer_p.h"
#include <Qt3DRender/private/job_common_p.h>
#include <Qt3DRender/private/managers_p.h>
#include <Qt3DRender/private/entity_p.h>
#include <Qt3DRender/private/qt3drender_global_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

namespace Render {

LightGatherer::LightGatherer()
    : Qt3DCore::QAspectJob()
    , m_manager(nullptr)
    , m_environmentLight(nullptr)
{
    SET_JOB_RUN_STAT_TYPE(this, JobTypes::LightGathering, 0)
}

void LightGatherer::run()
{
    m_lights.clear();
    m_environmentLight = nullptr;

    const std::vector<HEntity> &handles = m_manager->activeHandles();
    int envLightCount = 0;

    for (const HEntity &handle : handles) {
        Entity *node = m_manager->data(handle);
        const QVector<Light *> lights = node->renderComponents<Light>();
        if (!lights.isEmpty())
            m_lights.push_back(LightSource(node, lights));
        const QVector<EnvironmentLight *> envLights = node->renderComponents<EnvironmentLight>();
        envLightCount += envLights.size();
        if (!envLights.isEmpty() && !m_environmentLight)
            m_environmentLight = envLights.first();
    }

    if (envLightCount > 1)
        qWarning() << "More than one environment light found, extra instances are ignored";
}

} // Render

} // Qt3DRender

QT_END_NAMESPACE

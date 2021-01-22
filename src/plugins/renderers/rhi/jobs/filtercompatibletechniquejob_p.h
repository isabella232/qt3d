/****************************************************************************
**
** Copyright (C) 2020 Klaralvdalens Datakonsult AB (KDAB).
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

#ifndef QT3DRENDER_RENDER_RHI_FILTERCOMPATIBLETECHNIQUEJOB_H
#define QT3DRENDER_RENDER_RHI_FILTERCOMPATIBLETECHNIQUEJOB_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <Qt3DCore/qaspectjob.h>
#include <Qt3DRender/private/qt3drender_global_p.h>

#include <QSharedPointer>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {
namespace Render {

class TechniqueManager;

namespace Rhi {

class Renderer;

class Q_AUTOTEST_EXPORT FilterCompatibleTechniqueJob : public Qt3DCore::QAspectJob
{
public:
    FilterCompatibleTechniqueJob();

    void setManager(TechniqueManager *managers);
    TechniqueManager *manager() const;

    void setRenderer(Renderer *renderer);
    Renderer *renderer() const;

    void run() override;

private:
    TechniqueManager *m_manager;
    Renderer *m_renderer;
};

typedef QSharedPointer<FilterCompatibleTechniqueJob> FilterCompatibleTechniqueJobPtr;

} // namespace Rhi
} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_RHI_FILTERCOMPATIBLETECHNIQUEJOB_H

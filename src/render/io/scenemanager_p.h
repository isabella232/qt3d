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

#ifndef QT3DRENDER_RENDER_SCENEMANAGER_P_H
#define QT3DRENDER_RENDER_SCENEMANAGER_P_H

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

#include <Qt3DCore/private/qresourcemanager_p.h>
#include <Qt3DCore/private/qdownloadhelperservice_p.h>
#include <Qt3DRender/private/scene_p.h>
#include <Qt3DCore/qnodeid.h>
#include <Qt3DRender/private/loadscenejob_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {
class QEntity;
}

namespace Qt3DRender {
namespace Render {

class SceneManager;

class SceneDownloader : public Qt3DCore::QDownloadRequest {
public:
    SceneDownloader(const QUrl &source, Qt3DCore::QNodeId sceneComponent, SceneManager* manager);

    void onCompleted() override;

private:
    Qt3DCore::QNodeId m_sceneComponent;
    SceneManager* m_manager;
};

typedef QSharedPointer<SceneDownloader> SceneDownloaderPtr;


class Q_3DRENDERSHARED_PRIVATE_EXPORT SceneManager : public Qt3DCore::QResourceManager<
        Scene,
        Qt3DCore::QNodeId,
        Qt3DCore::ObjectLevelLockingPolicy>
{
public:
    SceneManager();
    ~SceneManager();

    void setDownloadService(Qt3DCore::QDownloadHelperService *service);

    void addSceneData(const QUrl &source, Qt3DCore::QNodeId sceneUuid,
                      const QByteArray &data = QByteArray());
    QVector<LoadSceneJobPtr> takePendingSceneLoaderJobs();

    void startSceneDownload(const QUrl &source, Qt3DCore::QNodeId sceneUuid);
    void clearSceneDownload(SceneDownloader *downloader);

private:
    Qt3DCore::QDownloadHelperService *m_service;
    QVector<LoadSceneJobPtr> m_pendingJobs;
    QVector<SceneDownloaderPtr> m_pendingDownloads;
};

} // namespace Render
} // namespace Qt3DRender

Q_DECLARE_RESOURCE_INFO(Qt3DRender::Render::Scene, Q_REQUIRES_CLEANUP)

QT_END_NAMESPACE

#endif // SCENEMANAGER_P_H

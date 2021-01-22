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

#ifndef QT3D_ASSIMPIMPORTER_H
#define QT3D_ASSIMPIMPORTER_H

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

// ASSIMP LIBRARY INCLUDE
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/DefaultLogger.hpp>

#include <QtCore/QDir>
#include <QtCore/QLoggingCategory>
#include <QtCore/QVector>

#include "assimphelpers.h"

#include <Qt3DRender/private/qsceneimporter_p.h>

QT_BEGIN_NAMESPACE

class QFile;

namespace Qt3DCore {
class QCamera;
}

namespace Qt3DAnimation {
class QKeyframeAnimation;
class QMorphingAnimation;
}

namespace Qt3DRender {

class QMaterial;
class QAbstractTexture;
class QAbstractLight;
class QGeometryRenderer;

Q_DECLARE_LOGGING_CATEGORY(AssimpImporterLog)

class AssimpImporter : public QSceneImporter
{
    Q_OBJECT

public:
    AssimpImporter();
    ~AssimpImporter();

    // SceneParserInterface interface
    void setSource(const QUrl& source) override;
    void setData(const QByteArray& data, const QString &basePath) override;
    bool areFileTypesSupported(const QStringList &extensions) const override;
    Qt3DCore::QEntity *scene(const QString &id = QString()) override;
    Qt3DCore::QEntity *node(const QString &id) override;

private:
    static bool areAssimpExtensions(const QStringList &extensions);
    static QStringList assimpSupportedFormats();

    Qt3DCore::QEntity *node(aiNode *node);

    void readSceneFile(const QString &file);
    void readSceneData(const QByteArray& data, const QString &basePath);

    void cleanup();
    void parse();

    QMaterial *loadMaterial(uint materialIndex);
    QGeometryRenderer *loadMesh(uint meshIndex);
    QAbstractTexture *loadEmbeddedTexture(uint textureIndex);
    QAbstractLight *loadLight(uint lightIndex);
    Qt3DCore::QEntity *loadCamera(aiNode *node);
    void loadAnimation(uint animationIndex);

    void copyMaterialName(QMaterial *material, aiMaterial *assimpMaterial);
    void copyMaterialColorProperties(QMaterial *material, aiMaterial *assimpMaterial);
    void copyMaterialFloatProperties(QMaterial *material, aiMaterial *assimpMaterial);
    void copyMaterialBoolProperties(QMaterial *material, aiMaterial *assimpMaterial);
    void copyMaterialShadingModel(QMaterial *material, aiMaterial *assimpMaterial);
    void copyMaterialBlendingFunction(QMaterial *material, aiMaterial *assimpMaterial);
    void copyMaterialTextures(QMaterial *material, aiMaterial *assimpMaterial);

    class SceneImporter {
    public :

        SceneImporter();
        ~SceneImporter();

        Assimp::Importer *m_importer;
        mutable const aiScene *m_aiScene;

        QHash<aiTextureType, QString> m_textureToParameterName;
        QVector<Qt3DAnimation::QKeyframeAnimation *> m_animations;
        QVector<Qt3DAnimation::QMorphingAnimation *> m_morphAnimations;
    };

    QDir     m_sceneDir;
    bool     m_sceneParsed;
    AssimpImporter::SceneImporter *m_scene;
    static QStringList assimpSupportedFormatsList;
};

} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3D_ASSIMPIMPORTER_H

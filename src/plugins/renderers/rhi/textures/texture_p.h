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

#ifndef QT3DRENDER_RENDER_RHI_GLTEXTURE_H
#define QT3DRENDER_RENDER_RHI_GLTEXTURE_H

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

#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qtextureimagedata.h>
#include <Qt3DRender/qtexturegenerator.h>
#include <Qt3DRender/private/backendnode_p.h>
#include <Qt3DRender/private/handle_types_p.h>
#include <Qt3DRender/private/texture_p.h>
#include <QFlags>
#include <QMutex>
#include <QSize>

QT_BEGIN_NAMESPACE

class QRhiTexture;
class QRhiSampler;

namespace Qt3DRender {
namespace Render {

template<class APITexture, class APITextureImage>
class APITextureManager;

class TextureImageManager;
class TextureDataManager;
class TextureImageDataManager;

namespace Rhi {
class RenderBuffer;
class SubmissionContext;

/**
 * @brief
 *   Actual implementation of the OpenGL texture object. Makes sure the
 *   QOpenGLTexture is up-to-date with the generators, properties and parameters
 *   that were set for this RHITexture.
 *
 *   Can be shared among multiple QTexture backend nodes through the
 *   RHITextureManager, which will make sure that there are no two GLTextures
 *   sharing the same texture data.
 *
 *   A RHITexture can be unique though. In that case, it will not be shared
 *   between QTextures, but private to one QTexture only.
 *
 *   A RHITexture can also represent an OpenGL renderbuffer object. This is used
 *   only in certain special cases, mainly to provide a packed depth-stencil
 *   renderbuffer suitable as an FBO attachment with OpenGL ES 3.1 and earlier.
 *   Such a RHITexture will have no texture object under the hood, and therefore
 *   the only valid operation is getOrCreateRenderBuffer().
 */
class Q_AUTOTEST_EXPORT RHITexture
{
public:
    RHITexture();
    ~RHITexture();

    enum DirtyFlag {
        None = 0,
        TextureData = (1 << 0), // texture data needs uploading to GPU
        Properties = (1 << 1), // texture needs to be (re-)created
        Parameters = (1 << 2), // texture parameters need to be (re-)set
        SharedTextureId = (1 << 3), // texture id from shared context
        TextureImageData = (1 << 4) // texture image data needs uploading
    };

    /**
     * Helper class to hold the defining properties of TextureImages
     */
    struct Image
    {
        QTextureImageDataGeneratorPtr generator;
        int layer;
        int mipLevel;
        QAbstractTexture::CubeMapFace face;

        inline bool operator==(const Image &o) const
        {
            bool sameGenerators = (generator == o.generator)
                    || (!generator.isNull() && !o.generator.isNull() && *generator == *o.generator);
            return sameGenerators && layer == o.layer && mipLevel == o.mipLevel && face == o.face;
        }
        inline bool operator!=(const Image &o) const { return !(*this == o); }
    };

    inline TextureProperties properties() const { return m_properties; }
    inline TextureParameters parameters() const { return m_parameters; }
    inline QTextureGeneratorPtr textureGenerator() const { return m_dataFunctor; }
    inline int sharedTextureId() const { return m_sharedTextureId; }
    inline QVector<Image> images() const { return m_images; }

    inline QSize size() const { return QSize(m_properties.width, m_properties.height); }
    inline QRhiTexture *getRhiTexture() const { return m_rhi; }
    inline QRhiSampler *getRhiSampler() const { return m_rhiSampler; }

    /**
     * @brief
     *   Returns the QOpenGLTexture for this RHITexture. If necessary,
     *   the GL texture will be created from the TextureImageDatas associated
     *   with the texture and image functors. If no functors are provided,
     *   the texture will be created without images.
     *
     *   If the texture properties or parameters have changed, these changes
     *   will be applied to the resulting OpenGL texture.
     */
    struct TextureUpdateInfo
    {
        QRhiTexture *texture = nullptr;
        bool wasUpdated = false;
        TextureProperties properties;
    };

    TextureUpdateInfo createOrUpdateRhiTexture(SubmissionContext *ctx);

    /**
     * @brief
     *   Returns the RenderBuffer for this RHITexture. If this is the first
     *   call, the OpenGL renderbuffer object will be created.
     */
    RenderBuffer *getOrCreateRenderBuffer();

    void destroy();

    void cleanup();

    bool isDirty() const { return m_dirtyFlags != None; }

    bool hasTextureData() const { return !m_textureData.isNull(); }
    bool hasImagesData() const { return !m_imageData.isEmpty(); }

    QFlags<DirtyFlag> dirtyFlags() const { return m_dirtyFlags; }

    QMutex *externalRenderingLock() { return &m_externalRenderingMutex; }

    void setExternalRenderingEnabled(bool enable) { m_externalRendering = enable; }

    bool isExternalRenderingEnabled() const { return m_externalRendering; }

    // Purely for unit testing purposes
    bool wasTextureRecreated() const { return m_wasTextureRecreated; }

    void setParameters(const TextureParameters &params);
    void setProperties(const TextureProperties &props);
    void setImages(const QVector<Image> &images);
    void setGenerator(const QTextureGeneratorPtr &generator);
    void setSharedTextureId(int textureId);
    void addTextureDataUpdates(const QVector<QTextureDataUpdate> &updates);

    QVector<QTextureDataUpdate> textureDataUpdates() const { return m_pendingTextureDataUpdates; }
    QTextureGeneratorPtr dataGenerator() const { return m_dataFunctor; }

private:
    void requestImageUpload() { m_dirtyFlags |= TextureImageData; }

    void requestUpload() { m_dirtyFlags |= TextureData; }

    bool testDirtyFlag(DirtyFlag flag) { return m_dirtyFlags.testFlag(flag); }

    void setDirtyFlag(DirtyFlag flag, bool value = true) { m_dirtyFlags.setFlag(flag, value); }

    QRhiTexture *buildRhiTexture(SubmissionContext *ctx);
    bool loadTextureDataFromGenerator();
    void loadTextureDataFromImages();
    void uploadRhiTextureData(SubmissionContext *ctx);
    void updateRhiTextureParameters(SubmissionContext *ctx);
    void introspectPropertiesFromSharedTextureId();
    void destroyResources();

    QFlags<DirtyFlag> m_dirtyFlags;
    QMutex m_externalRenderingMutex;
    QRhiTexture *m_rhi;
    QRhiSampler *m_rhiSampler;
    RenderBuffer *m_renderBuffer;

    // target which is actually used for GL texture
    TextureProperties m_properties;
    TextureParameters m_parameters;

    QTextureGeneratorPtr m_dataFunctor;
    QTextureGenerator *m_pendingDataFunctor;
    QVector<Image> m_images;

    // cache actual image data generated by the functors
    QTextureDataPtr m_textureData;
    QVector<QTextureImageDataPtr> m_imageData;
    QVector<QTextureDataUpdate> m_pendingTextureDataUpdates;

    int m_sharedTextureId;
    bool m_externalRendering;
    bool m_wasTextureRecreated;
};

} // namespace Rhi
} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_RHI_GLTEXTURE_H

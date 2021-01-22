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

#ifndef QT3DRENDER_RENDER_RHI_GLSHADER_P_H
#define QT3DRENDER_RENDER_RHI_GLSHADER_P_H

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

#include <shadervariables_p.h>
#include <shaderparameterpack_p.h>
#include <Qt3DRender/qshaderprogram.h>
#include <QMutex>
#include <QtGui/private/qshader_p.h>
#include <QtGui/private/qrhi_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

namespace Render {

namespace Rhi {

class Q_AUTOTEST_EXPORT RHIShader
{
public:
    struct UBO_Member
    {
        ShaderUniformBlock block;
        QVector<QShaderDescription::BlockVariable> members;
    };

    RHIShader();

    bool isLoaded() const { return m_isLoaded; }
    void setLoaded(bool loaded) { m_isLoaded = loaded; }

    void prepareUniforms(ShaderParameterPack &pack);

    void setFragOutputs(const QHash<QString, int> &fragOutputs);
    const QHash<QString, int> fragOutputs() const;

    inline QVector<int> uniformsNamesIds() const { return m_uniformsNamesIds; }
    inline QVector<int> standardUniformNameIds() const { return m_standardUniformNamesIds; }
    inline QVector<int> uniformBlockNamesIds() const { return m_uniformBlockNamesIds; }
    inline QVector<int> storageBlockNamesIds() const { return m_shaderStorageBlockNamesIds; }
    inline QVector<int> attributeNamesIds() const { return m_attributeNamesIds; }

    QVector<QString> uniformsNames() const;
    QVector<QString> attributesNames() const;
    QVector<QString> uniformBlockNames() const;
    QVector<QString> storageBlockNames() const;
    QVector<QString> samplerNames() const;
    QVector<QString> imagesNames() const;

    inline QVector<ShaderUniform> uniforms() const { return m_uniforms; }
    inline QVector<ShaderAttribute> attributes() const { return m_attributes; }
    inline QVector<ShaderUniformBlock> uniformBlocks() const { return m_uniformBlocks; }
    inline QVector<ShaderStorageBlock> storageBlocks() const { return m_shaderStorageBlocks; }
    inline QVector<ShaderAttribute> samplers() const { return m_samplers; }
    inline QVector<ShaderAttribute> images() const { return m_images; }

    QHash<QString, ShaderUniform> activeUniformsForUniformBlock(int blockIndex) const;

    ShaderUniformBlock uniformBlockForBlockIndex(int blockNameId) const noexcept;
    ShaderUniformBlock uniformBlockForBlockNameId(int blockIndex) const noexcept;
    ShaderUniformBlock uniformBlockForBlockName(const QString &blockName) const noexcept;

    ShaderStorageBlock storageBlockForBlockIndex(int blockIndex) const noexcept;
    ShaderStorageBlock storageBlockForBlockNameId(int blockNameId) const noexcept;
    ShaderStorageBlock storageBlockForBlockName(const QString &blockName) const noexcept;

    enum ParameterKind { Uniform, UBO, SSBO, Struct };
    ParameterKind categorizeVariable(int nameId) const noexcept;

    bool hasUniform(int nameId) const noexcept;
    bool hasActiveVariables() const noexcept;

    void setShaderCode(const QVector<QByteArray> shaderCode) { m_shaderCode = shaderCode; }
    QVector<QByteArray> shaderCode() const;

    const QShader &shaderStage(QShader::Stage stage) const noexcept { return m_stages[stage]; }
    QVector<UBO_Member> uboMembers() const { return m_uboMembers; }

    const QSet<QString> &unqualifiedUniformNames() const noexcept
    {
        return m_unqualifiedUniformNames;
    }

    void introspect();

private:
    bool m_isLoaded;
    QShader m_stages[6];

    QVector<QString> m_uniformsNames;
    QVector<int> m_uniformsNamesIds;
    QVector<int> m_standardUniformNamesIds;
    QVector<ShaderUniform> m_uniforms;

    QVector<QString> m_attributesNames;
    QVector<int> m_attributeNamesIds;
    QVector<ShaderAttribute> m_attributes;

    QVector<QString> m_uniformBlockNames;
    QVector<int> m_uniformBlockNamesIds;
    QVector<ShaderUniformBlock> m_uniformBlocks;
    QHash<int, QHash<QString, ShaderUniform>> m_uniformBlockIndexToShaderUniforms;
    QSet<QString> m_unqualifiedUniformNames;

    QVector<QString> m_shaderStorageBlockNames;
    QVector<int> m_shaderStorageBlockNamesIds;
    QVector<ShaderStorageBlock> m_shaderStorageBlocks;

    QVector<QString> m_samplerNames;
    QVector<int> m_samplerIds;
    QVector<ShaderAttribute> m_samplers;

    QVector<QString> m_imageNames;
    QVector<int> m_imageIds;
    QVector<ShaderAttribute> m_images;

    QVector<QString> m_structNames;
    QVector<int> m_structNamesIds;

    QHash<QString, int> m_fragOutputs;
    QVector<QByteArray> m_shaderCode;

    // Private so that only SubmissionContext can call it
    friend class SubmissionContext;
    void initializeAttributes(const QVector<ShaderAttribute> &attributesDescription);
    void initializeUniformBlocks(const QVector<ShaderUniformBlock> &uniformBlockDescription);
    void
    initializeShaderStorageBlocks(const QVector<ShaderStorageBlock> &shaderStorageBlockDescription);
    void initializeSamplers(const QVector<ShaderAttribute> &samplerDescription);
    void initializeImages(const QVector<ShaderAttribute> &imageDescription);
    void recordAllUniforms(const QShaderDescription::BlockVariable &ubo, QString parentName);

    QVector<UBO_Member> m_uboMembers;

    mutable QMutex m_mutex;
    QMetaObject::Connection m_contextConnection;
};

} // Rhi

} // Render

} // Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_RHI_GLSHADER_P_H

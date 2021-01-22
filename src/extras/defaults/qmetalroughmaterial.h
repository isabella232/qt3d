/****************************************************************************
**
** Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB).
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

#ifndef QT3DEXTRAS_QMETALROUGHMATERIAL_H
#define QT3DEXTRAS_QMETALROUGHMATERIAL_H

#include <Qt3DExtras/qt3dextras_global.h>
#include <Qt3DRender/qmaterial.h>
#include <QtGui/qcolor.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {
class QAbstractTexture;
}

namespace Qt3DExtras {

class QMetalRoughMaterialPrivate;

class Q_3DEXTRASSHARED_EXPORT QMetalRoughMaterial : public Qt3DRender::QMaterial
{
    Q_OBJECT
    Q_PROPERTY(QVariant baseColor READ baseColor WRITE setBaseColor NOTIFY baseColorChanged)
    Q_PROPERTY(QVariant metalness READ metalness WRITE setMetalness NOTIFY metalnessChanged)
    Q_PROPERTY(QVariant roughness READ roughness WRITE setRoughness NOTIFY roughnessChanged)
    Q_PROPERTY(QVariant ambientOcclusion READ ambientOcclusion WRITE setAmbientOcclusion NOTIFY ambientOcclusionChanged REVISION 10)
    Q_PROPERTY(QVariant normal READ normal WRITE setNormal NOTIFY normalChanged REVISION 10)
    Q_PROPERTY(float textureScale READ textureScale WRITE setTextureScale NOTIFY textureScaleChanged REVISION 10)

public:
    explicit QMetalRoughMaterial(Qt3DCore::QNode *parent = nullptr);
    ~QMetalRoughMaterial();

    QVariant baseColor() const;
    QVariant metalness() const;
    QVariant roughness() const;
    QVariant ambientOcclusion() const;
    QVariant normal() const;
    float textureScale() const;

public Q_SLOTS:
    void setBaseColor(const QVariant &baseColor);
    void setMetalness(const QVariant &metalness);
    void setRoughness(const QVariant &roughness);
    void setAmbientOcclusion(const QVariant &ambientOcclusion);
    void setNormal(const QVariant &normal);
    void setTextureScale(float textureScale);

Q_SIGNALS:
    void baseColorChanged(const QVariant &baseColor);
    void metalnessChanged(const QVariant &metalness);
    void roughnessChanged(const QVariant &roughness);
    void ambientOcclusionChanged(const QVariant &ambientOcclusion);
    void normalChanged(const QVariant &normal);
    void textureScaleChanged(float textureScale);

protected:
    explicit QMetalRoughMaterial(QMetalRoughMaterialPrivate &dd, Qt3DCore::QNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QMetalRoughMaterial)
};

} // namespace Qt3DExtras

QT_END_NAMESPACE

#endif // QT3DEXTRAS_QMETALROUGHMATERIAL_H

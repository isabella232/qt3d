/****************************************************************************
**
** Copyright (C) 2019 Klaralvdalens Datakonsult AB (KDAB).
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

#ifndef QT3DRENDER_QTEXTUREDATAUPDATE_H
#define QT3DRENDER_QTEXTUREDATAUPDATE_H

#include <Qt3DRender/qt3drender_global.h>
#include <Qt3DRender/qabstracttexture.h>

#include <QtCore/qshareddata.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender
{

class QTextureDataUpdate;
class QTextureDataUpdatePrivate;

Q_3DRENDERSHARED_EXPORT bool operator==(const QTextureDataUpdate &lhs, const QTextureDataUpdate &rhs) noexcept;

class Q_3DRENDERSHARED_EXPORT QTextureDataUpdate
{
public:
    QTextureDataUpdate();
    QTextureDataUpdate(const QTextureDataUpdate &other);
    QTextureDataUpdate &operator=(const QTextureDataUpdate &other);
    QTextureDataUpdate &operator=(QTextureDataUpdate &&other) noexcept
    { swap(other); return *this; }
    ~QTextureDataUpdate();

    void swap(QTextureDataUpdate &other) noexcept { qSwap(d_ptr, other.d_ptr); }

    int x() const;
    int y() const;
    int z() const;
    int layer() const;
    int mipLevel() const;
    QAbstractTexture::CubeMapFace face() const;
    QTextureImageDataPtr data() const;

    void setX(int x);
    void setY(int y);
    void setZ(int z);
    void setLayer(int layer);
    void setMipLevel(int mipLevel);
    void setFace(QAbstractTexture::CubeMapFace face);
    void setData(const QTextureImageDataPtr &data);

private:
    friend Q_3DRENDERSHARED_EXPORT bool operator==(const QTextureDataUpdate &lhs, const QTextureDataUpdate &rhs) noexcept;
    Q_DECLARE_PRIVATE(QTextureDataUpdate)
    QExplicitlySharedDataPointer<QTextureDataUpdatePrivate> d_ptr;
};
QT3D_DECLARE_TYPEINFO(Qt3DRender, QTextureDataUpdate, Q_MOVABLE_TYPE)

inline bool operator!=(const QTextureDataUpdate &lhs, const QTextureDataUpdate &rhs) noexcept
{ return !operator==(lhs, rhs); }

inline void swap(QTextureDataUpdate &lhs, QTextureDataUpdate &rhs) noexcept { return lhs.swap(rhs); }

} // Qt3DRender

QT_END_NAMESPACE

Q_DECLARE_METATYPE(Qt3DRender::QTextureDataUpdate)


#endif // QT3DRENDER_QTEXTUREDATAUPDATE_H

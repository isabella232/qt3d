/****************************************************************************
**
** Copyright (C) 2015 Paul Lemire
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

#include "buffermanager_p.h"

QT_BEGIN_NAMESPACE

namespace Qt3DRender {
namespace Render {

BufferManager::BufferManager()
{
}

BufferManager::~BufferManager()
{
}

void BufferManager::addDirtyBuffer(Qt3DCore::QNodeId bufferId)
{
    if (!m_dirtyBuffers.contains(bufferId))
        m_dirtyBuffers.push_back(bufferId);
}

QVector<Qt3DCore::QNodeId> BufferManager::takeDirtyBuffers()
{
    return qMove(m_dirtyBuffers);
}

// Called in QAspectThread::syncChanges
void BufferManager::removeBufferReference(Qt3DCore::QNodeId bufferId)
{
    QMutexLocker lock(&m_mutex);
    Q_ASSERT(m_bufferReferences.contains(bufferId) && m_bufferReferences[bufferId] > 0);
    m_bufferReferences[bufferId]--;
}

// Called in QAspectThread
void BufferManager::addBufferReference(Qt3DCore::QNodeId bufferId)
{
    QMutexLocker lock(&m_mutex);
    m_bufferReferences[bufferId]++;
}

// Called in Render thread
QVector<Qt3DCore::QNodeId> BufferManager::takeBuffersToRelease()
{
    QMutexLocker lock(&m_mutex);
    QVector<Qt3DCore::QNodeId> buffersToRelease;
    for (auto it = m_bufferReferences.begin(), end = m_bufferReferences.end(); it != end; /*erasing*/) {
        if (it.value() == 0) {
            buffersToRelease.append(it.key());
            it = m_bufferReferences.erase(it);
        } else {
            ++it;
        }
    }
    return buffersToRelease;
}

} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE

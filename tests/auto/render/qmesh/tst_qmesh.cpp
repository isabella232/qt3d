/****************************************************************************
**
** Copyright (C) 2016 Paul Lemire <paul.lemire350@gmail.com>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

// TODO Remove in Qt6
#include <QtCore/qcompilerdetection.h>
QT_WARNING_DISABLE_DEPRECATED

#include <QtTest/QTest>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/private/qmesh_p.h>
#include <QObject>
#include <QSignalSpy>
#include <Qt3DCore/private/qscene_p.h>
#include "testarbiter.h"

class MyQMesh : public Qt3DRender::QMesh
{
    Q_OBJECT
public:
    explicit MyQMesh(Qt3DCore::QNode *parent = nullptr)
        : Qt3DRender::QMesh(parent)
    {}
};

class tst_QMesh : public QObject
{
    Q_OBJECT

private Q_SLOTS:

    void checkDefaultConstruction()
    {
        // GIVEN
        Qt3DRender::QMesh mesh;

        // THEN
        QCOMPARE(mesh.source(), QUrl());
        QCOMPARE(mesh.meshName(), QString());
        QCOMPARE(mesh.status(), Qt3DRender::QMesh::None);
    }

    void checkPropertyChanges()
    {
        // GIVEN
        Qt3DRender::QMesh mesh;

        {
            // WHEN
            QSignalSpy spy(&mesh, SIGNAL(sourceChanged(QUrl)));
            const QUrl newValue(QStringLiteral("qrc:/mesh.obj"));
            mesh.setSource(newValue);

            // THEN
            QVERIFY(spy.isValid());
            QCOMPARE(mesh.source(), newValue);
            QCOMPARE(spy.count(), 1);

            // WHEN
            spy.clear();
            mesh.setSource(newValue);

            // THEN
            QCOMPARE(mesh.source(), newValue);
            QCOMPARE(spy.count(), 0);
        }
        {
            // WHEN
            QSignalSpy spy(&mesh, SIGNAL(meshNameChanged(QString)));
            const QString newValue = QStringLiteral("MainBody");
            mesh.setMeshName(newValue);

            // THEN
            QVERIFY(spy.isValid());
            QCOMPARE(mesh.meshName(), newValue);
            QCOMPARE(spy.count(), 1);

            // WHEN
            spy.clear();
            mesh.setMeshName(newValue);

            // THEN
            QCOMPARE(mesh.meshName(), newValue);
            QCOMPARE(spy.count(), 0);
        }
    }

    void checkSourceUpdate()
    {
        // GIVEN
        TestArbiter arbiter;
        Qt3DRender::QMesh mesh;
        arbiter.setArbiterOnNode(&mesh);

        Qt3DCore::QAspectEngine *engine = reinterpret_cast<Qt3DCore::QAspectEngine*>(0xdeadbeefL);
        Qt3DCore::QScene *scene = new Qt3DCore::QScene(engine);
        Qt3DCore::QNodePrivate *meshd = Qt3DCore::QNodePrivate::get(&mesh);
        meshd->setScene(scene);
        QCoreApplication::processEvents();
        arbiter.clear();

        {
            // WHEN
            mesh.setSource(QUrl(QStringLiteral("qrc:/toyplane.obj")));
            QCoreApplication::processEvents();

            // THEN
            QCOMPARE(arbiter.dirtyNodes().size(), 1);
            QCOMPARE(arbiter.dirtyNodes().front(), &mesh);

            arbiter.clear();
        }

        {
            // WHEN
            mesh.setSource(QStringLiteral("qrc:/toyplane.obj"));
            QCoreApplication::processEvents();

            // THEN
            QCOMPARE(arbiter.dirtyNodes().size(), 0);
        }

    }

    void checkMeshNameUpdate()
    {
        // GIVEN
        TestArbiter arbiter;
        Qt3DRender::QMesh mesh;
        arbiter.setArbiterOnNode(&mesh);

        Qt3DCore::QAspectEngine *engine = reinterpret_cast<Qt3DCore::QAspectEngine*>(0xdeadbeefL);
        Qt3DCore::QScene *scene = new Qt3DCore::QScene(engine);
        Qt3DCore::QNodePrivate *meshd = Qt3DCore::QNodePrivate::get(&mesh);
        meshd->setScene(scene);
        QCoreApplication::processEvents();
        arbiter.clear();

        {
            // WHEN
            mesh.setMeshName(QStringLiteral("Phil"));
            QCoreApplication::processEvents();

            // THEN
            QCOMPARE(arbiter.dirtyNodes().size(), 1);
            QCOMPARE(arbiter.dirtyNodes().front(), &mesh);

            arbiter.clear();
        }

        {
            // WHEN
            mesh.setMeshName(QStringLiteral("Phil"));
            QCoreApplication::processEvents();

            // THEN
            QCOMPARE(arbiter.dirtyNodes().size(), 0);
        }

    }

    void checkGeometryFactoryIsAccessibleEvenWithNoScene() // QTBUG-65506
    {
        // GIVEN
        Qt3DRender::QMesh mesh;

        // WHEN
        mesh.setSource(QUrl(QStringLiteral("some_path")));

        // THEN
        QVERIFY(!Qt3DRender::QMeshPrivate::get(&mesh)->m_geometryFactory.isNull());
    }
};

QTEST_MAIN(tst_QMesh)

#include "tst_qmesh.moc"

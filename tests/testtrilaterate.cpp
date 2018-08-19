/***************************************************************************
** Polarize Positioning                                                   **
**                                                                        **
** Copyright (C) 2018                                             **
**                                                                        **
** This program is free software; you can redistribute it and/or modify   **
** it under the terms of the GNU General Public License as published by   **
** the Free Software Foundation; either version 3 of the License, or      **
** (at your option) any later version.                                    **
** This program is distributed in the hope that it will be useful,        **
** but WITHOUT ANY WARRANTY; without even the implied warranty of         **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          **
** GNU General Public License for more details.                           **
** You should have received a copy of the GNU General Public License      **
** along with this program; if not, write to the Free Software Foundation,**
** Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA      **
***************************************************************************/
#include <trivector.h>
#include "trilaterate.h"
#include <QtTest/QtTest>
class TestTrilaterate : public QObject
{
    Q_OBJECT
private slots:
    void testTrilaterateTwoResults();
    void testTrilaterateNoResults();
    void testWeirdFloatingPoint();
};

void TestTrilaterate::testTrilaterateTwoResults()
{
    TriVector p1(0,0,0,100);
    TriVector p2(100,0,0,100);
    TriVector p3(0,100,0,100);

    TriLaterate t(p1,p2,p3);
    QList<QVector3D> results = t.trilaterate();
    QVector3D firstExpect(50,50,70.71067811865476);
    QVector3D secondExpect(50,50,-70.71067811865476);
    QList<QVector3D> expectations;
    expectations <<  firstExpect << secondExpect;
    QCOMPARE(expectations, results);

    p1 = TriVector(0,0,0,100);
    p2 = TriVector(100,0,0,100);
    p3 = TriVector(0,100,50,100);

    TriLaterate t2(p1,p2,p3);
    QList<QVector3D> results2 = t2.trilaterate();
    firstExpect = QVector3D(50,20.419601084501917,84.16079783099616);
    secondExpect = QVector3D(50,79.58039891549808,-34.16079783099617);
    expectations.clear();
    expectations <<  firstExpect << secondExpect;
    QCOMPARE(expectations, results2);
}

void TestTrilaterate::testTrilaterateNoResults()
{
    TriVector p1(0,0,0,10);
    TriVector p2(100,0,0,10);
    TriVector p3(0,100,0,10);

    TriLaterate t(p1,p2,p3);
    QList<QVector3D> results = t.trilaterate();
    QVERIFY(results.isEmpty());
}

void TestTrilaterate::testWeirdFloatingPoint()
{
    TriVector p1(69,0,69,0);
    TriVector p2(0,50,50,0);
    TriVector p3(0,80,80,0);

    TriLaterate t(p1,p2,p3);
    QList<QVector3D> results = t.trilaterate();
    QVector3D firstExpect(-1.5631940186722204e-13,-1.4210854715202004e-13,0);
    QList<QVector3D> expectations;
    expectations <<  firstExpect;
    QCOMPARE(expectations, results);

}


    QTEST_MAIN(TestTrilaterate)

    #include "testtrilaterate.moc"

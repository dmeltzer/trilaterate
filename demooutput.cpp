/***************************************************************************
** trilaterate Positioning                                                   **
**                                                                        **
** Copyright (C) 2016-2017  Daniel Meltzer <dmeltzer.devel@gmail.com>     **
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

#include "demooutput.h"
#include "trivector.h"
#include "trilaterate.h"
#include <QHostAddress>
DemoOutput::DemoOutput(QObject *parent)
    : QObject(parent)
    , m_ipAddress(QString("127.0.0.1"))
    , m_oscEnabled(false)
    , m_manager(nullptr)
{
//    m_manager = new OSCNetworkManager;
//    m_manager->setIpAddress(QHostAddress(m_ipAddress));
//    m_manager->setUseTcp(true)`;
//    m_manager->setEnabled(true);

//    connect(m_manager, SIGNAL(messageReceived(OSCMessage)), this, SLOT(onMessageRecieved(OSCMessage)));
}

void
DemoOutput::output(const QStringList &point1, const QStringList &point2, const QStringList &point3)
{
//    if(!m_oscEnabled) {
//        qDebug() << "Output not enabled, aborting";
//        return;
//    }


//    QVector3D firstPoint(point1[0].toFloat(), point1[1].toFloat(), point1[2].toFloat());
    TriVector firstPoint(point1);
    TriVector secondPoint(point2);
    TriVector thirdPoint(point3);
    TriLaterate t(firstPoint, secondPoint, thirdPoint);
    QVector3D solution = t.trilaterate().first();
    qDebug() << "Solution: " << solution;
//    qDebug() << "Original Coordinates: " << firstPoint << secondPoint << thirdPoint;
    // Based on https://stackoverflow.com/questions/16176656/trilateration-and-locating-the-point-x-y-z
    // First, translate so that firstPoint is at the origin.
//    firstPoint += translationVector;
//    secondPoint += translationVector;
//    thirdPoint += translationVector;
//    qDebug() << "Translated Coordinates: " << firstPoint << secondPoint << thirdPoint;

//    // Next, we need to ensure that P2 is on the x-axis after translation.
//    if(!qFuzzyCompare(secondPoint.y(), 0))
//    {
//        // We're not on the x-axis, we need to rotate the view to become so.
//        // Calculate the angle between P2' and [1,0]
//        // theta = acos(P2'x / ||P2'||
//        // ||A|| = sqrt(Ax+Ay+Az)
//        qreal p2Magnitude = qSqrt(secondPoint.x() + secondPoint.y() + secondPoint.z());
//        float theta = qRadiansToDegrees(acos(secondPoint.x() / p2Magnitude));
//        qDebug() << "Magnitude: " << p2Magnitude << " rotation angle: " << theta;

//        // Now, lets rotate the vectors.
//        // rotation matrix
//        // [cos(theta) -sin(theta)]
//        // [sin(theta  cos(theta  ]
//        // If P2y is positive, we rotate negative.
//        // If P2y is negative, we rotate positive.
//        if(secondPoint.y() > 0)
//            theta = -theta;
//        // The first point is currently at the origin, no need to rotate
//        QVector3D firstPointRot = firstPoint;
//        float values[] = {
//            cos(theta), -sin(theta),
//            sin(theta), cos(theta)
//        };
////        QMatrix2x2 translationMatrix(values);
//        QMatrix4x4 m;
////        m.rotate(Qt3DCore::QTransform::fromAxisAndAngle(QVector3D(5,0,0), theta));
//        m.rotate(theta, , 0);
//        QVector3D secondPointRot = m * secondPoint;
////        secondPointRot.setX(secondPoint.x() * cos(theta) - secondPoint.y() * sin(theta));
////        secondPointRot.setY(secondPoint.y() * sin(theta) + secondPoint.y() * cos(theta));
//        qDebug() << "Rotated Second Point: " << secondPointRot << " theta: " << theta;

//        QVector3D thirdPointRot;
//        thirdPointRot.setX(thirdPoint.x() * cos(theta) - thirdPoint.y() * sin(theta));
//        thirdPointRot.setY(thirdPoint.y() * sin(theta) + thirdPoint.y() * cos(theta));
//        qDebug() << "Rotated third Point: " << thirdPointRot;



//    }
//    // Solving for X
//    // x = (r1^2 - (r2^2 + d^2) / 2d  (d,0) are coords of translated point2
//    float x = (square(firstRadius) - square(secondRadius) + square(secondPoint.x())) / 2* secondPoint.x();

//    //y = (r1^2 - r3^2 + i^2 + j^2) / 2j - (i/j)x //(i,j) are coords of P3'
//    float y = (square(firstRadius) - square(thirdRadius) + square(thirdPoint.x()) + square(thirdPoint.y()))
//            / (2*thirdPoint.y() - (thirdPoint.x() / thirdPoint.y())*x);

//    // translate Back to origin.
//    QVector3D result = QVector3D(x,y,0) + translationVector;
//    qDebug() << "X: " << x << " Y: " << y << "Result Point: " << result;


}

void
DemoOutput::setIpAddress(QString ipAddress)
{
    if(m_ipAddress!=ipAddress) {
        qDebug() << "IP Changed: " << ipAddress;
        m_ipAddress = ipAddress;
        m_manager->setIpAddress(QHostAddress(ipAddress));
    }
    emit ipChanged();
}

void
DemoOutput::onMessageRecieved(OSCMessage message)
{

}

QVector3D DemoOutput::vectorize(const QStringList &qmlPoint)
{
    return QVector3D (qmlPoint[0].toFloat(), qmlPoint[1].toFloat(), qmlPoint[2].toFloat());
}

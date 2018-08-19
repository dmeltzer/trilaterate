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
    , m_firstPoint()
    , m_secondPoint()
    , m_thirdPoint()
{
//    m_manager = new OSCNetworkManager;
//    m_manager->setIpAddress(QHostAddress(m_ipAddress));
//    m_manager->setUseTcp(true)`;
//    m_manager->setEnabled(true);
    m_oldMessage = QVector<QVariant>();
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
    m_firstPoint = TriVector(point1);
    m_secondPoint = TriVector(point2);
    m_thirdPoint = TriVector(point3);

    QVector3D solution = TriLaterate::trilaterate(m_firstPoint, m_secondPoint, m_thirdPoint).first();
    qDebug() << "Solution: " << solution;
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
    if(message.pathStartsWith("/pfs/listener/updateAxes"))
    {
        // This message has six arguements:
        // Pan min, Pan max, tilt min, tilt max, current pan, current tilt.
        // For now, we need to assume that the channel we're dealing with is active.
        qDebug() << "MESSAGE RECIEVED: ";
        QVector<QVariant> arguments = message.arguments();
        qDebug() << arguments;
        // These come across as PLC#,Timestamp, axis,position,load,status,error#
        // Let's chunk into more meaningful bits.
        // First remove metadata
        QVector<QVariant> metadata;
        metadata << arguments.takeFirst() << arguments.takeFirst();

        // Now that timestamp is stripped, compare this to the old arguement list.
        // TODO: Probably need to cache/key by PLC# if we try to use this in theater.
        if( m_oldMessage == arguments ) {
            return;
        }
        qDebug() << "Metadata is: " << metadata;
        QHash<int,int> axisMap;
        // Now, loop over remaining and build axis data for each.
        while (!arguments.empty()) {
            axisMap.insert(arguments.takeFirst().toInt(), arguments.takeFirst().toInt());
            arguments.remove(0,3); // For now, we don't care about the load, status, or error
        }

        m_firstPoint.setWinchDistance(axisMap.value(m_firstPoint.axis()));
        m_secondPoint.setWinchDistance(axisMap.value(m_secondPoint.axis()));
        m_thirdPoint.setWinchDistance(axisMap.value(m_thirdPoint.axis()));
        QVector3D updatedSolution = TriLaterate::trilaterate(m_firstPoint, m_secondPoint, m_thirdPoint).first();
        qDebug() << "Updated Solution: " << updatedSolution;
        m_oldMessage = arguments;
    }
}

QVector3D DemoOutput::vectorize(const QStringList &qmlPoint)
{
    return QVector3D (qmlPoint[0].toFloat(), qmlPoint[1].toFloat(), qmlPoint[2].toFloat());
}

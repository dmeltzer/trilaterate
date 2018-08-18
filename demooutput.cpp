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

#include <QHostAddress>
DemoOutput::DemoOutput(QObject *parent)
    : QObject(parent)
    , m_ipAddress(QString("127.0.0.1"))
    , m_oscEnabled(false)
    , m_manager(0)
    , m_currentLocation(0,0,0)
{
    m_manager = new OSCNetworkManager;
    m_manager->setIpAddress(QHostAddress(m_ipAddress));
    m_manager->setUseTcp(true);
    m_manager->setEnabled(true);

    connect(m_manager, SIGNAL(messageReceived(OSCMessage)), this, SLOT(onMessageRecieved(OSCMessage)));
}

void
DemoOutput::output(const QStringList &source, const QStringList &target)
{
    if(!m_oscEnabled) {
        qDebug() << "Output not enabled, aborting";
        return;
    }

    // Okay, so lets take this step by step.
    // Three points:
    // Point of The light source itself.  This will be shifted to 0,0,0
    // Calibration point.  This is where the light currently is.
    // Target we are pointing at.

    QVector3D sourcePoint(source[0].toFloat(), source[1].toFloat(), source[2].toFloat());
    QVector3D targetPoint(target[0].toFloat(), target[1].toFloat(), target[2].toFloat());

    if(sourcePoint == targetPoint) {
        qDebug() << "No Change in values, ignoring";
        return;
    }
    qDebug() << "Source: " << sourcePoint << " Target: " << targetPoint;

    // We need to shift the source to 0.  This means we should subtract the source from each vector.
    // Or maybe we don't need to do the translation?
    QVector3D translatedSource = sourcePoint - sourcePoint;
    QVector3D translatedTarget = targetPoint - sourcePoint;
//    QVector3D translatedSource = sourcePoint;
//    QVector3D translatedTarget = targetPoint;

    qDebug() << "Translated: ";
    qDebug() << "Source: " << translatedSource << " Target: " << translatedTarget;


    // Now lets calculate pan/tilt to the calibartion point -- And calculate the pan/tilt to it.  This should be current pan/tilt if things are working.
//    PolarPoint p_current = PolarPoint(sourcePoint).toPoint(m_currentLocation);
    PolarPoint p_source(translatedSource, m_currentLocation.minPan(), m_currentLocation.maxPan());
    qDebug() << "SOURCE: " << p_source;
    PolarPoint p_current = p_source.toPoint(m_currentLocation);
    qDebug() << "ORIGIN: Pan: " << p_current.pan() << "Tilt: " << p_current.tilt();


    // trilaterate the target point and calculate source between the two.
    PolarPoint p_target(translatedTarget);

    // Now Calculate to new point
    PolarPoint translatedVector = p_source.toPoint(p_target);
    qDebug() << "TRANSLATION: Pan: " << translatedVector.pan() << "Tilt: " << translatedVector.tilt();
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

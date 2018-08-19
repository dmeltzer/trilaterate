/***************************************************************************
** Polarize Positioning                                                   **
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

#include "polarpoint.h"
#include <QtMath>
#include <QDebug>
PolarPoint::PolarPoint(qreal r, qreal theta, qreal phi, qreal minPan, qreal maxPan)
{
    m_r = r;
    m_theta = theta;
    m_phi = phi;
    setMaxPan(maxPan);
    setMinPan(minPan);
}

PolarPoint::PolarPoint(const QVector3D &source, qreal minPan, qreal maxPan)
{
    m_r = qSqrt(
                     (source.x()*source.x())
                    +(source.y()*source.y())
                    +(source.z()*source.z())
                );
    m_theta = qAcos(source.z()/m_r);
    m_phi = qAtan2(source.y(),source.x());
    setMaxPan(maxPan);
    setMinPan(minPan);
}

//Theta is Tilt
qreal
PolarPoint::pan()
{
    return qRadiansToDegrees(m_theta);
}

void
PolarPoint::setPan(const qreal degrees)
{
    m_theta = qDegreesToRadians(degrees);
}

// Phi is Pan.
qreal
PolarPoint::tilt()
{
    return qRadiansToDegrees(m_phi);
}

void
PolarPoint::setTilt(const qreal degrees)
{
    m_phi = qDegreesToRadians(degrees);
}

PolarPoint
PolarPoint::toPoint(PolarPoint point)
{

    // We need to do a few things here to calculate the most optimal solution.
    // First of all, The initial solution should be between -PI and PI. We can use that
    // to transform to find cleanest solution.
    // Theta = pan, phi = tilt
    // Pan will be phi_cal - phi_trans
    qDebug() << "CALCULATRING:";
    qDebug() << "This point pan: " << pan() << " Other point pan: " << point.pan();
    qreal newPan = phi() - point.phi();
    //TODO: Do we need to worry about pan boundries?
//    qDebug() << "New Tilt: "
//    if(newTilt > maxTilt()|| newTilt < minTilt())
//    {
//        newTilt -= M_PI;
//    }

    // Tilt will be theta_cal - theta_trans
    qreal newTilt = theta() - point.theta();
//    qDebug() << "Original pan calc: " << newPan << " max pan " << m_maxPan << " min pan " << m_minPan;
    // Need to use the members to get radians.  THe accessors convert to degrees.
    // TODO: Rethink this to suck less
    if( (newPan > m_maxPan) || (newPan < m_minPan))
    {
        newPan = fmod(newPan,M_PI);
        qDebug() << "Outside bounds, new pan is: " << newPan;
    }

    // R will be r_cal - r_trans
    qreal newR = R() - point.R();
    return PolarPoint(newR, newTilt, newPan, minPan(), maxPan());
}

qreal
PolarPoint::minTilt() const
{
    return qRadiansToDegrees(m_minTilt);
}

void
PolarPoint::setMinTilt(const qreal &value)
{
    m_minTilt = qDegreesToRadians(value);
}

qreal
PolarPoint::maxTilt() const
{
    return qRadiansToDegrees(m_maxTilt);
}

void
PolarPoint::setMaxTilt(const qreal &value)
{
    m_maxTilt = qDegreesToRadians(value);
}

qreal
PolarPoint::minPan() const
{
    return qRadiansToDegrees(m_minPan);
}

void
PolarPoint::setMinPan(const qreal &value)
{
    m_minPan = qDegreesToRadians(value);
}

qreal
PolarPoint::maxPan() const
{
    return qRadiansToDegrees(m_maxPan);
}

void
PolarPoint::setMaxPan(const qreal &value)
{
    m_maxPan = qDegreesToRadians(value);
}




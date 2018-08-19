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

#ifndef POLARPOINT_H
#define POLARPOINT_H
#include <QVector3D>
#include <QString>
#include <QtMath>

class PolarPoint
{
public:
    PolarPoint();
    PolarPoint(qreal r, qreal theta, qreal phi, qreal minPan = -M_PI, qreal maxPan=M_PI);
    PolarPoint(const QVector3D &, qreal minPan =-M_PI, qreal maxPan = M_PI);

    void setR(qreal r) { m_r = r; }
    void setTheta(qreal theta) { m_theta = theta; }
    void setPhi( qreal phi ) { m_phi = phi; }

    qreal R() const { return m_r; }
    qreal theta() const { return m_theta; }
    qreal phi() const { return m_phi; }

    void setPan(const qreal degrees);
    qreal pan();
    qreal tilt();
    void setTilt(const qreal degrees);

    PolarPoint toPoint(PolarPoint point);

    qreal minTilt() const;
    void setMinTilt(const qreal &value);

    qreal minPan() const;
    void setMinPan(const qreal &value);

    qreal maxPan() const;
    void setMaxPan(const qreal &value);

    qreal maxTilt() const;
    void setMaxTilt(const qreal &value);

    operator QString() const { return QString("R: %1 Theta: %2 Phi: %3").arg(m_r).arg(m_theta).arg(m_phi); }

private:
    qreal m_r; // Radius, distance from point to point in a straight line
    qreal m_theta; // Azumith coordinate.  Represents Pan.
    qreal m_phi; // Inclination Coordinate.  Represents tilt

    // Boundries
    qreal m_minPan;
    qreal m_maxPan;
    qreal m_minTilt;
    qreal m_maxTilt;
};

#endif // POLARPOINT_H

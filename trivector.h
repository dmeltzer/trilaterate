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
#ifndef TRIVECTOR_H
#define TRIVECTOR_H

#include <QVector3D>
#include <QStringList>
#include <QtMath>

class TriVector
{
public:
    TriVector(QVector3D v, qreal radius);
    TriVector(qreal x, qreal y, qreal z, qreal radius);
    TriVector(QStringList values);

    void setDistance(qreal radius) { m_distance = radius; }
    qreal distance() const { return m_distance; }

    void setVector (const QVector3D &v)  { m_vector = v; }
    QVector3D vector() const { return m_vector; }
//    static float norm(const TriVector &v);

private:
    QVector3D m_vector;
    qreal m_distance;
};
#endif // TRIVECTOR_H




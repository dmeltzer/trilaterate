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
#include "trivector.h"
TriVector::TriVector(QVector3D v, qreal cableToZero)
{
    m_vector = v;
    m_cableOffset = v.z() - cableToZero;
}

TriVector::TriVector(qreal x, qreal y, qreal z, qreal cableToZero)
{
    m_vector = QVector3D(x,y,z);
    m_cableOffset = z - cableToZero;
}


TriVector::TriVector(QStringList values)
{
    m_vector = QVector3D(values[0].toFloat(), values[1].toFloat(), values[2].toFloat());
    m_cableOffset = m_vector.z() -  values[3].toDouble();
}

void TriVector::setWinchDistance(qreal cableLength)
{
    // This is going to come in as a arbitray number.
    // For our purposes, when this number is 0 the distance is z() - cableOffset.
    // If the number is negative, it's further away.
    // If the number is positive, it's closer to the divert point.
    qreal startingLength = m_vector.z() - m_cableOffset;
    m_distance = startingLength + cableLength;
}

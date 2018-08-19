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
#include "trilaterate.h"
#include "trivector.h"

#include <qdebug.h>
TriLaterate::TriLaterate(const TriVector &v1, const TriVector &v2, const TriVector &v3) :
    m_v1(v1),
    m_v2(v2),
    m_v3(v3)
{
}

QList<QVector3D> TriLaterate::trilaterate()
{
    QVector3D firstVector = m_v1.vector();
    QVector3D secondVector = m_v2.vector();
    QVector3D thirdVector = m_v3.vector();

    // Attempt based on trilaterate.js
    QVector3D ex = (secondVector - firstVector) / norm((secondVector - firstVector));
    float i = QVector3D::dotProduct(ex, (thirdVector - firstVector));
    QVector3D a = (thirdVector - firstVector) - (ex * i);
    QVector3D ey = a / norm(a);
    QVector3D ez = QVector3D::crossProduct(ex, ey);
    float d = norm(secondVector - firstVector);
    float j = QVector3D::dotProduct(ey, (thirdVector - firstVector));
    float x = (square(m_v1.distance()) - square(m_v2.distance()) + square(d)) / (2*d);
    float y = (square(m_v1.distance()) - square(m_v3.distance()) + square(i) + square(j)) / (2*j)-(i/j) * x;
    float b = square(m_v1.distance()) - square(x) - square(y);

    if(qAbs(b) < 0.0000000001) {
        b = 0;
    }
    float z = qSqrt(b);
    if(isnan(z))
    {
        qDebug() << "No Solution Found!!";
        return QList<QVector3D>();
    }
//	a = vector_add(p1, vector_add(vector_multiply(ex, x), vector_multiply(ey, y)))
    a = (firstVector + (ex*x + (ey*y)));
    QVector3D firstSolutionPoint = a+(ez*z);
    QVector3D secondSolutionPoint = (a-(ez*z));
    if(qFuzzyCompare(z,0))
    {
        qDebug() << "Solution is: " << firstSolutionPoint;
        return QList<QVector3D>() << firstSolutionPoint;
    }
    qDebug() << "Solution is either: " << firstSolutionPoint << " Or: " << secondSolutionPoint;
    return QList<QVector3D>() << firstSolutionPoint << secondSolutionPoint;
}

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
class TriVector : public QVector3D
{
public:
    TriVector(qreal xpos, qreal ypos, qreal zpos, qreal radius);
    TriVector(QStringList values);
    ~TriVector();

protected:
    float square(float value) { return value*value; }
    float norm();
private:
    qreal m_radius;
};

#endif // TRIVECTOR_H

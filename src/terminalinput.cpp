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

#include "terminalinput.h"

#include <QTextStream>
#include <QStringList>
#include <QDebug>
TerminalInput::TerminalInput()
{

}

QVector3D
TerminalInput::inputValues(const QString &name)
{
    QTextStream stream(stdin);
    QString input;
    qDebug() << QString("Enter %1 Values as x,y,z").arg(name);
    while(stream.readLineInto(&input))
    {
        const QStringList values = input.split(',');
        if(values.count() != 3) {
            qDebug() << "Invalid Format, Please try again";
            continue;
        }
        return QVector3D(values[0].toFloat(),values[1].toFloat(),values[2].toFloat());
    }
    return QVector3D();
}

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

#ifndef POLARIZE_INPUTINTERFACE_H
#define POLARIZE_INPUTINTERFACE_H
#include <QVector3D>
#include <QtPlugin>
class PolarizeInputInterface
{
public:
    virtual ~PolarizeInputInterface() {}
    virtual QVector3D inputValues(const QString &name) = 0;
};

#define POLAR_INPUTINTERFACE_iid "org.dmeltzer.polarize.TerminalInput"
Q_DECLARE_INTERFACE(PolarizeInputInterface, POLAR_INPUTINTERFACE_iid)
#endif // POLARIZE_INPUTINTERFACE_H

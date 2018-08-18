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

#ifndef DEMOOUTPUT_H
#define DEMOOUTPUT_H

#include <QObject>
#include <QDebug>
#include <QJSValue>
#include "polarpoint.h"
#include "etc-osc/OSCMessage.h"
#include "etc-osc/OSCNetworkManager.h"
class DemoOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ipAddress READ ipAddress WRITE setIpAddress NOTIFY ipChanged)
    Q_PROPERTY(bool oscEnabled READ oscEnabled WRITE setOscEnabled NOTIFY oscEnabledChanged)


public:
    explicit DemoOutput(QObject *parent = 0);
    Q_INVOKABLE void output(const QStringList &source, const QStringList &target);

    QString ipAddress() { return m_ipAddress; }
    Q_INVOKABLE void setIpAddress(QString ipAddress);

    bool oscEnabled() { return m_oscEnabled; }
    void setOscEnabled(bool oscEnabled) {
        if(m_oscEnabled !=oscEnabled)
            m_oscEnabled = oscEnabled;
        emit oscEnabledChanged(); }

signals:
    void ipChanged();
    void oscEnabledChanged();


public slots:
    void onMessageRecieved(OSCMessage message);
private:
    QString m_ipAddress;
    bool m_oscEnabled;
    OSCNetworkManager *m_manager;

    PolarPoint m_currentLocation;
};

#endif // DEMOOUTPUT_H
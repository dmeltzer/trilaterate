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

#include <QApplication>
#include <QDebug>
#include <QVector3D>
#include <QDir>
#include <QQmlApplicationEngine>
#include "src/polarpoint.h"
#include <QSettings>
#include <QRect>
#include <QQuickWindow>
#include <QQmlContext>
#include "demooutput.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QQmlApplicationEngine *engine = new QQmlApplicationEngine();
    QCoreApplication::setOrganizationName("EMPAC");
    QCoreApplication::setOrganizationDomain("empac.rpi.edu");
    QCoreApplication::setApplicationName("eChamThingy");
    DemoOutput *d = new DemoOutput;
    engine->rootContext()->setContextProperty("_demo", d);
    // actually load QML file:
    engine->load(QUrl(QStringLiteral("qrc:/mainwindow.qml")));
    QSettings independentSettings;

    QRect windowGeometry = independentSettings.value("windowGeometry").toRect();
    bool maximized = independentSettings.value("maximized").toBool();
    QQuickWindow* window = qobject_cast<QQuickWindow*>(engine->rootObjects()[0]);
    if (!window)
        return 0;
    if (!windowGeometry.isNull())
        window->setGeometry(windowGeometry);
    if (maximized)
        window->showMaximized();
    return a.exec();
}




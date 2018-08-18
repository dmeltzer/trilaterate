#include "mainapp.h"
#include <QDir>
#include <QPluginLoader>
#include <QApplication>
MainApp::MainApp(QWidget *parent)
    : QMainWindow(parent)
    , m_input(0)
{


}

bool
MainApp::loadPlugins()
{
//    QDir pluginsDir(qApp->applicationDirPath());
//    #if defined(Q_OS_WIN)
//        if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
//            pluginsDir.cdUp();
//    #elif defined(Q_OS_MAC)
//        if (pluginsDir.dirName() == "MacOS") {
//            pluginsDir.cdUp();
//            pluginsDir.cdUp();
//            pluginsDir.cdUp();
//        }
//    #endif
//        pluginsDir.cd("plugins");
//        foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
//            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
//            QObject *plugin = pluginLoader.instance();
//            if (plugin) {
//                m_input = qobject_cast<PolarizeInputInterface *>(plugin);
//                if (m_input)
//                    return true;
//            }
//        }

        return false;
}

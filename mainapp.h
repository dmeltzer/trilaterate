#ifndef MAINAPP_H
#define MAINAPP_H

#include <QMainWindow>
#include "src/inputinterface.h"
class MainApp : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainApp(QWidget *parent = 0);

signals:

public slots:

private:
    bool loadPlugins();
    PolarizeInputInterface *m_input;
};

#endif // MAINAPP_H

// #include<iostream>
#include <QApplication>
#include <QWebEngineUrlScheme>
#include "mainwindow.h"
#include "myschemehandler.h"
int main(int argc, char* argv[])
{

    // 需要自定义三个scheme
    QStringList myScheme = {"bres", "sound", "img", "entry"};

    for (auto schemeName : myScheme ) {
        QWebEngineUrlScheme scheme(schemeName.toLatin1());
        // 只需要host
        scheme.setSyntax(QWebEngineUrlScheme::Syntax::Host);
        // 是本地资源 允许访问本地资源 允许访问其他链接
        scheme.setFlags(QWebEngineUrlScheme::Flag::LocalScheme |
                        QWebEngineUrlScheme::Flag::LocalAccessAllowed |
                        QWebEngineUrlScheme::Flag::CorsEnabled);
        // 注册scheme
        QWebEngineUrlScheme::registerScheme(scheme);
    }

    QApplication app(argc, argv);
    MainWindow mainwindow;
    mainwindow.show();
    return app.exec();
}

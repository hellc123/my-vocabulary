// #include<iostream>
#include <QApplication>
#include <QWebEngineUrlScheme>
#include "mainwindow.h"
#include "myschemehandler.h"
#include <QObject>
int main(int argc, char* argv[])
{
    QStringList myScheme = {"bres", "sound", "img", "entry"};

    for (const auto &schemeName : myScheme ) {
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
    QFont f = QApplication::font();
    f.setStyleStrategy( QFont::PreferAntialias );
    QApplication::setFont( f );
    MainWindow mainwindow;
    mainwindow.show();

    return app.exec();
}

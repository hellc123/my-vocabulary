#ifndef MYSCHEMEHANDLER_H
#define MYSCHEMEHANDLER_H

#include <QWebEngineUrlSchemeHandler>

class MySchemeHandler : public QWebEngineUrlSchemeHandler
{
    Q_OBJECT
public:
    explicit MySchemeHandler(QObject *parent = nullptr);
    void requestStarted(QWebEngineUrlRequestJob *job);
};

#endif // MYSCHEMEHANDLER_H

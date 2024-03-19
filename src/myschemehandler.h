#ifndef MYSCHEMEHANDLER_H
#define MYSCHEMEHANDLER_H

#include <QWebEngineUrlSchemeHandler>
#include "articlemaker.h"
class MySchemeHandler : public QWebEngineUrlSchemeHandler
{
    Q_OBJECT
public:
    explicit MySchemeHandler(QObject *parent, ArticleMaker& articleMaker);
    void requestStarted(QWebEngineUrlRequestJob *job);
    // 文章生产器
    ArticleMaker& articleMaker;
};

#endif // MYSCHEMEHANDLER_H

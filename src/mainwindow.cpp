#include "mainwindow.h"
#include "webview.h"
#include <QString>
#include <QFile>
#include <QWidget>
#include "myschemehandler.h"
#include <QCloseEvent>
#include "databasemanager.h"
#include <QVector>
#include "word.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
      dbAddress(R"(E:\BaiduNetdiskWorkspace\project\my-vocabulary\dict\mdxDictionary.db)"),
      dictDatabase(dbAddress),
      articleMaker(dictDatabase)
{
    // 安装 scheme handler
    MySchemeHandler *handler = new MySchemeHandler(this, articleMaker);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("bres", handler);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("sound", handler);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("img", handler);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("entry", handler);

    view = new WebView();

    inspector = new QWebEngineView();
    connect(view->pageAction(QWebEnginePage::WebAction::ViewSource),&QAction::triggered,this,&MainWindow::showInpector);
    view->load(QUrl(R"(entry://AC)"));
    setCentralWidget(view);
    resize(800,400);
}

MainWindow::~MainWindow()
{
    delete inspector;
}

void MainWindow::showInpector(bool)
{
    inspector->page()->setInspectedPage( view->page() );
    inspector->show();
}

void MainWindow::appQuit()
{
    // 如果insepct打开了，就关闭它
    if(inspector && inspector->isVisible()){
        inspector->close();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    appQuit();

}

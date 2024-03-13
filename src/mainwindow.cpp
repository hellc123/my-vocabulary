#include "mainwindow.h"
#include "webview.h"
#include <QString>
#include <QFile>
#include <QWidget>
#include "myschemehandler.h"
#include <QCloseEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    // 安装 scheme handler
    MySchemeHandler *handler = new MySchemeHandler(this);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("bres", handler);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("sound", handler);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("img", handler);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("entry", handler);


    view = new WebView();
    inspector = new QWebEngineView();


    connect(view->pageAction(QWebEnginePage::WebAction::ViewSource),&QAction::triggered,this,&MainWindow::showInpector);
    view->load(QUrl(R"(entry://animal)"));

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

#include "mainwindow.h"
#include "webview.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    WebView *view = new WebView(parent);
    QUrl local(QUrl::fromLocalFile("E:\\BaiduNetdiskWorkspace\\project\\my-vocabulary\\dict\\abolish.html"));
    view->load(local);
    qDebug() << local.toString();

    setCentralWidget(view);
    resize(800,400);

}

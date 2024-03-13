#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webview.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWebEngineView *inspector;
    WebView *view;
    void showInpector(bool);

private:
    // 定义窗口退出时的动作
    void appQuit();

// 对事件的重写
private:
    virtual void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webview.h"
#include "databasemanager.h"
#include "articlemaker.h"
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

    // 一定要注意这三个变量声明的顺序
    // 数据库路径
    const QString dbAddress;
    // 词典数据库
    DatabaseManager dictDatabase;
    // 文章生产器
    ArticleMaker articleMaker;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webview.h"
#include "databasemanager.h"
#include "articlemaker.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include "articlepad.h"
#include "vocabularytest.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // 网页检查器
    QWebEngineView *inspector;

    // 中央widget
    QWidget *centralArea;
    // 中心的横向布局
    QHBoxLayout * centralAreaLayout;

    // 文本编辑框和单词列表
    ArticlePad * articlePad;

    // 一个 书写栏，和一个webview，
    QWidget *translateArea;
    WebView *view;
    QLineEdit *translateLine;
    QVBoxLayout * translateAreaLayout;


    void showInpector(bool);
    void loadWord(const QString & word);

private:
    // 定义窗口退出时的动作
    void appQuit();

// 对事件的重写
private:
    virtual void closeEvent(QCloseEvent *event);

    // 一定要注意这三个变量声明的顺序
    // 数据库路径
    const QString dbAddress;
    // 词库数据库路径
    const QString vocabularyAddress;
    // 词典数据库
    DatabaseManager dictDatabase;
    // CET4，6 考研词库
    VocabularyDatabase vocabularyDatabase;
    // 文章生产器
    ArticleMaker articleMaker;
};

#endif // MAINWINDOW_H

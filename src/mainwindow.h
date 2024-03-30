#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databasemanager.h"
#include "articlemaker.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include "articlepad.h"
#include "learningmodel.h"
#include "wordprocess.h"
#include "translatearea.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // 中央widget
    QWidget *centralArea;
    // 中心的横向布局
    QHBoxLayout * centralAreaLayout;

    // 文本编辑框和单词列表
    ArticlePad * articlePad;
    // 搜索栏和单词显示
    TranslateArea *translateArea;



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
    // stop word 路径
    const QString stopWordsAddress;
    // 用户学习记录路径
    const QString userVocabularyAddress;
    // 词典数据库
    DatabaseManager dictDatabase;
    // CET4，6 考研词库
    VocabularyDatabase vocabularyDatabase;
    // 文章生产器
    ArticleMaker articleMaker;
    // 语言处理，分词
    WordProcess wordProcess;
    // 学习模型，用于管理用户学习记录
    LearningModel learningModel;


};

#endif // MAINWINDOW_H

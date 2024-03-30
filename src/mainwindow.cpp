#include "mainwindow.h"
#include <QString>
#include <QFile>
#include <QWidget>
#include "myschemehandler.h"
#include <QCloseEvent>
#include "databasemanager.h"
#include <QVector>
#include <QOpenGLContext>
#include "translatearea.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
//      dbAddress(R"(E:\BaiduNetdiskWorkspace\project\my-vocabulary\dict\mdxDictionary.db)"),
//      vocabularyAddress(R"(E:\BaiduNetdiskWorkspace\project\my-vocabulary\dict\vocabulary.db)"),
//      stopWordsAddress(R"(E:\BaiduNetdiskWorkspace\project\my-vocabulary\profile\stopWords.txt)"),
//      userVocabularyAddress(R"(E:\BaiduNetdiskWorkspace\project\my-vocabulary\profile\myVocabulary.xml)"),
      dbAddress(R"(.\dict\mdxDictionary.db)"),
      vocabularyAddress(R"(.\dict\vocabulary.db)"),
      stopWordsAddress(R"(.\profile\stopWords.txt)"),
      userVocabularyAddress(R"(.\profile\myVocabulary.xml)"),
      dictDatabase(dbAddress),
      vocabularyDatabase(vocabularyAddress),
      articleMaker(dictDatabase, vocabularyDatabase),
      wordProcess(dictDatabase, stopWordsAddress),
      learningModel(userVocabularyAddress)
{
    // 安装 scheme handler
    MySchemeHandler *handler = new MySchemeHandler(this, articleMaker);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("bres", handler);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("sound", handler);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("img", handler);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("entry", handler);

    // 取消边界
    setContentsMargins(0,0,0,0);

    // 中央widget
    centralArea = new QWidget(this);
    centralArea->setContentsMargins(0,0,0,0);
    setCentralWidget(centralArea);
    centralAreaLayout = new QHBoxLayout();
    centralArea->setLayout(centralAreaLayout);
    centralAreaLayout->setContentsMargins(5,5,0,5);
    centralAreaLayout->setSpacing(5);



//    centralWidget()->layout()->setContentsMargins(0,0,0,0);
//    this->layout()->setContentsMargins(0,0,0,0);

    // 文本编辑器和单词列表部分
    articlePad = new ArticlePad(dictDatabase, wordProcess,learningModel, this);
    articlePad->setContentsMargins(0,0,0,0);
    centralAreaLayout->addWidget(articlePad, 12);


    // 搜索栏和单词释义显示
    translateArea = new TranslateArea(learningModel, this);
    centralAreaLayout->addWidget(translateArea, 10);

    // 点击 word list 里的单词，查询这个单词
    connect(articlePad, &ArticlePad::articlePadSearchWord, translateArea, &TranslateArea::loadWord);

    // 当按下unfamiliar按钮后，更新articlePad
    connect(translateArea, &TranslateArea::unfamiliarClick, articlePad, &ArticlePad::updateListView);

    // 词汇测试程序
    // 遍历所有 vocaublary.xml 中的单词
    //VocabularyTest *test = new VocabularyTest();
    //test ->show();

    //qDebug() << dictDatabase.findOriginalWord(Word("doers")).toXMLString();

    // 初始查询单词
    translateArea->loadWord("welcome");
    resize(1000,600);

}

MainWindow::~MainWindow()
{
    //delete inspector;
}

void MainWindow::appQuit()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    appQuit();
}

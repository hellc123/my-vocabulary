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
#include <QOpenGLContext>
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

    // 中央widget
    centralArea = new QWidget(this);
    centralArea->setContentsMargins(0,0,0,0);
    setCentralWidget(centralArea);
    centralAreaLayout = new QHBoxLayout();
    centralArea->setLayout(centralAreaLayout);
    centralAreaLayout->setContentsMargins(0,0,0,0);
    centralAreaLayout->setSpacing(1);

    // 文本编辑器和单词列表部分
    articlePad = new ArticlePad();
    centralAreaLayout->addWidget(articlePad, 9);

    // 查词和显示释义部分
    translateArea = new QWidget(this);
    translateLine = new QLineEdit();
    view = new WebView();

    translateAreaLayout = new QVBoxLayout();
    translateArea->setLayout(translateAreaLayout);
    translateAreaLayout->addWidget(translateLine);
    translateAreaLayout->addWidget(view);

    centralAreaLayout->addWidget(translateArea, 10);
    // 按下Enter键和Return键之后，进行搜索
    connect(translateLine, &QLineEdit::returnPressed, this,
               [=](){view->load(QUrl(QString(R"(entry://)")+translateLine->text().trimmed()));});

    // 点击 word list 里的单词，查询这个单词
    connect(articlePad, &ArticlePad::articlePadSearchWord, this, &MainWindow::loadWord);
    // 检测网页
    inspector = new QWebEngineView();
    connect(view->pageAction(QWebEnginePage::WebAction::ViewSource),&QAction::triggered,this,&MainWindow::showInpector);

    // 初始查询单词
    loadWord("welcome");

    VocabularyTest *test = new VocabularyTest();
    test ->show();

    resize(1000,600);
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

void MainWindow::loadWord(const QString &word)
{
    view->load(QUrl(QString(R"(entry://)")+word.trimmed()));
    translateLine->setText(word.trimmed());
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

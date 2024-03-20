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

    // 查词和显示释义部分
    translateArea = new QWidget(this);
    translateLine = new QLineEdit();
    view = new WebView();

    translateAreaLayout = new QVBoxLayout();
    translateArea->setLayout(translateAreaLayout);
    translateAreaLayout->addWidget(translateLine);
    translateAreaLayout->addWidget(view);

    centralAreaLayout->addWidget(translateArea);
    // 按下Enter键和Return键之后，进行搜索
    connect(translateLine, &QLineEdit::returnPressed, this,
               [=](){view->load(QUrl(QString(R"(entry://)")+translateLine->text().trimmed()));});


    // 检测网页
    inspector = new QWebEngineView();
    connect(view->pageAction(QWebEnginePage::WebAction::ViewSource),&QAction::triggered,this,&MainWindow::showInpector);

    // 初始查询单词
    view->load(QUrl(R"(entry://done)"));

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

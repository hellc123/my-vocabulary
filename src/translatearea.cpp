#include "translatearea.h"

//TranslateArea::TranslateArea(QWidget *parent)
//    : QWidget{parent}
//{

//}

TranslateArea::TranslateArea(LearningModel &lm, QWidget *parent)
    : QWidget{parent},
      learningModel(lm)
{
    //UI部分

    // 总布局
    setContentsMargins(0,0,0,0);
    translateAreaLayout = new QVBoxLayout(this);
    translateAreaLayout->setContentsMargins(0,0,0,0);
    translateAreaLayout->setSpacing(5);
    setLayout(translateAreaLayout);
    // 搜索栏
    translateLineArea = new QWidget();
    translateLineArea->setContentsMargins(0,0,5,0);
    translateLineLayout = new QHBoxLayout(translateLineArea);
    translateLineArea->setLayout(translateLineLayout);
    translateLineLayout->setContentsMargins(0,0,0,0);
    translateLine = new QLineEdit();
    searchButton = new QPushButton("Search");
    unfamiliarButton = new QPushButton("Unfamiliar -10");
    translateLineLayout->addWidget(translateLine);
    translateLineLayout->addWidget(searchButton);
    translateLineLayout->addWidget(unfamiliarButton);
    // 文章显示
    view = new WebView();
    translateAreaLayout->addWidget(translateLineArea);
    translateAreaLayout->addWidget(view,10);

    // 检测网页窗口
    inspector = new QWebEngineView(this);
    inspector->setWindowFlag(Qt::Window);
    // 按下右键菜单中的ViewSource，弹出inspector
    connect(view->pageAction(QWebEnginePage::WebAction::ViewSource),&QAction::triggered,this,&TranslateArea::showInpector);


    // 按下Enter键和Return键之后，进行搜索
    connect(translateLine, &QLineEdit::returnPressed, this, &TranslateArea::toSearch);
    // 按下搜索按钮，进行搜索
    connect(searchButton, &QPushButton::clicked, this, &TranslateArea::toSearch);

    // 按钮unfamiliar按钮，对应单词减去10分，
    connect(unfamiliarButton, &QPushButton::clicked, this, &TranslateArea::unfamiliarClicked);


}

void TranslateArea::showInpector(bool)
{
    // 显示，并成为焦点
    inspector->page()->setInspectedPage( view->page() );
    inspector->resize(800,400);
    inspector->show();
    inspector->setFocus();
    qDebug() << "inspector";
}

void TranslateArea::loadWord(const QString &word)
{
    view->load(QUrl(QString(R"(entry://mydictionary/)")+word.trimmed()));
    translateLine->setText(word.trimmed());
}

void TranslateArea::loadWordFormEdit()
{
    loadWord(translateLine->text().trimmed());
}

void TranslateArea::unfamiliarClicked(bool)
{
    // 单词减10分
    int rt = QMessageBox::question(this,"Unfamiliar","Do you think this word is unfamiliar?",QMessageBox::Yes | QMessageBox::No);
    if(rt==QMessageBox::Yes) {
        learningModel.unfamiliar(translateLine->text().trimmed());
        disableUnfamiliarButton();
        emit unfamiliarClick();
    }
}

void TranslateArea::disableUnfamiliarButton()
{
    unfamiliarButton->setEnabled(false);
}

void TranslateArea::enableUnfamiliarButton()
{
    unfamiliarButton->setEnabled(true);
}

void TranslateArea::toSearch()
{
    loadWordFormEdit();
    enableUnfamiliarButton();
}

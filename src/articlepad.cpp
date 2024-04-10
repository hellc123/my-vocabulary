#include "articlepad.h"
#include "wordprocess.h"
#include <QSizePolicy>
ArticlePad::ArticlePad(const DatabaseManager &db, WordProcess & wp,LearningModel &lm, QWidget *parent)
    : QWidget{parent},
      db(db),
      wp(wp),
      lm(lm)
{
    articlePadLayout = new QHBoxLayout();

    articlePadLayout->setContentsMargins(0,0,0,0);
    articlePadLayout->setSpacing(5);
    //articlePadLayout->setContentsMargins(5,10,0,10);
    setLayout(articlePadLayout);

    // 文章编辑框
    //articleEdit = new QTextEdit();
    articleEdit = new QPlainTextEdit();
    articleEdit->setContentsMargins(0,0,0,0);
    articlePadLayout->addWidget(articleEdit, 9);

    // 单词显示与学习区域
    wordViewArea = new QWidget();
    wordViewArea->setContentsMargins(0,0,0,0);
    wordViewArea->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    wordViewArea->setMaximumWidth(150);
    wordViewAreaLayout = new QVBoxLayout(wordViewArea);
    wordViewAreaLayout->setContentsMargins(0,0,0,0);
    wordViewArea->setLayout(wordViewAreaLayout);
    articlePadLayout->addWidget(wordViewArea, 4);
    // 单词显示
    wordListView = new QListView();
    wordListView->setModel(&wordListModel);
    wordListView->setContentsMargins(0,0,0,0);
    wordViewAreaLayout->addWidget(wordListView);
    // 学习按钮
    easyButton = new QPushButton("Easy\t+20");
    goodButton = new QPushButton("Good\t+10");
    hardButton = new QPushButton("Hard\t+5");
    ignoreButton = new QPushButton("Ignore");
    wordViewAreaLayout->addWidget(ignoreButton);
    wordViewAreaLayout->addWidget(easyButton);
    wordViewAreaLayout->addWidget(goodButton);
    wordViewAreaLayout->addWidget(hardButton);




    // 当文字更新后，生成分词后的结果并显示
    connect(articleEdit, &QPlainTextEdit::textChanged, this, [=](){tokenizer(articleEdit->toPlainText());});
    // 文字更新后，关闭按钮
    connect(articleEdit, &QPlainTextEdit::textChanged, this, &ArticlePad::disableButton);
    // 点击单词后
    connect(wordListView, &QListView::clicked, this, &ArticlePad::clickWord);
    // index 移动也会更新 防止按住鼠标移动
    connect(wordListView, &QListView::entered, this, &ArticlePad::clickWord);
    // 点击单词和，开启按钮
    connect(wordListView, &QListView::clicked, this, &ArticlePad::enableButton);

    // 绑定按钮
    connect(easyButton, &QPushButton::clicked, this, &ArticlePad::easy);
    connect(goodButton, &QPushButton::clicked, this, &ArticlePad::good);
    connect(hardButton, &QPushButton::clicked, this, &ArticlePad::hard);
    connect(ignoreButton, &QPushButton::clicked, this, &ArticlePad::ignore);
    // 默认关闭按钮
    disableButton();
}

void ArticlePad::loadAndSort(QSet<QString> &wordSet)
{
    //auto pointer = &ArticlePad::wordLessThan;
    wordListModel.copyFormSet(wordSet);
//    std::sort(wordListModel.begin(),wordListModel.end(),&ArticlePad::wordLessThan);
    std::sort(wordListModel.begin(),wordListModel.end(),[=](const QString& s1,const QString &s2){return wordLessThan(s1,s2);});
    return;
}

bool ArticlePad::wordLessThan(const QString &s1, const QString &s2)
{
    if (lm.getScore(s1) == lm.getScore(s2))
        return s1 < s2;
    return lm.getScore(s1) < lm.getScore(s2);
}

/// To-DO:
/// 1. 一个输入 article 返回 QSet<QString> 的文字处理类 WordProcess
/// 2. 一个输入 QSet<QString>, 返回值得学习的QSet<QString> 语言学习模型类 LearningModel
/// 3. 完成学习界面的UI设计
bool ArticlePad::tokenizer(QString article)
{
    if(article.isEmpty()) {
        article = " ";
    }

    //qDebug() << article;

    QSet<QString> uniqueWords;
    // 语言处理
    // 分词，查找单词原型，去除stop word，去重
    wp.setArticle(article);
    wp.getWordsSet(uniqueWords);

    // 判断一个单词是否应该被学习
    lm.getLearningSet(uniqueWords);
    qDebug() << uniqueWords.count();


    // 显示结果
    // 让 wordsList 首先按分数升序排列，然后按字母顺序升序排列

    loadAndSort(uniqueWords);

    //wordListModel.copyFormSet(uniqueWords);

    return true;
}

void ArticlePad::clickWord(const QModelIndex &index)
{
    emit articlePadSearchWord(wordListModel.data(index).toString());
}

void ArticlePad::easy()
{
    //qDebug() << "1";
    const QModelIndex index = wordListView->currentIndex();
    // 非法情况
    if(!index.isValid()) {
        return;
    }
    QString currentWord = wordListModel.data(index).toString();
    lm.easy(currentWord);

    // 更新wordListView
    updateListView();
}

void ArticlePad::good()
{
    const QModelIndex index = wordListView->currentIndex();
    // 非法情况
    if(!index.isValid()) {
        return;
    }
    QString currentWord = wordListModel.data(index).toString();
    lm.good(currentWord);
    // 更新wordListView
    updateListView();
}

void ArticlePad::hard()
{
    const QModelIndex index = wordListView->currentIndex();
    // 非法情况
    if(!index.isValid()) {
        return;
    }
    QString currentWord = wordListModel.data(index).toString();
    lm.hard(currentWord);
    // 更新wordListView
    updateListView();
}

void ArticlePad::ignore()
{
    // 用一个提示框询问是否要ignore
    int ret = QMessageBox::question(this, "ignore word", "Are you sure to ignore this word?",
                                   QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::No)
        return;
    const QModelIndex index = wordListView->currentIndex();
    // 非法情况
    if(!index.isValid()) {
        return;
    }
    QString currentWord = wordListModel.data(index).toString();
    // 这里使用word process
    wp.ignore(currentWord);
    // 更新wordListView
    updateListView();
}

void ArticlePad::disableButton()
{
    isEnableButton = false;
    easyButton->setEnabled(isEnableButton);
    goodButton->setEnabled(isEnableButton);
    hardButton->setEnabled(isEnableButton);
    ignoreButton->setEnabled(isEnableButton);
}

void ArticlePad::enableButton()
{
    isEnableButton = true;
    easyButton->setEnabled(isEnableButton);
    goodButton->setEnabled(isEnableButton);
    hardButton->setEnabled(isEnableButton);
    ignoreButton->setEnabled(isEnableButton);
}

void ArticlePad::updateListView()
{
    // 为了提供学习反馈，当按下学习键之后，不管一个单词需不需要再次学习，都跳到下一个单词
    // 获取当前 QModelIndex
    const QModelIndex index = wordListView->currentIndex();
    // 获得当前单词
    const QString currentWord = wordListModel.data(index).toString();

    // 刷新 ListView
    tokenizer(articleEdit->toPlainText());

    // 判断index是否合法
    int count = wordListModel.rowCount();

    // 如果已经不存在单词了
    if(count == 0) {
        // 关闭按钮
        disableButton();
        return;
    }

    // 学习前该单词是最后一个单词
    // 如果该单词在学习之后不在学习list中，则 index.row() >= count
    // 代表学习完成
    if(index.row() >= count) {
        // 关闭按钮
        disableButton();
        return;
    }
    // 当单词还是原来那个单词就跳到下一个单词
    if(currentWord==wordListModel.data(index).toString()) {
//        qDebug() <<"@@@@@@@@@@@@@";
//        qDebug() << currentWord;
//        qDebug() << wordListModel.data(index).toString();
//        qDebug() <<"@@@@@@@@@@@@@";
        const QModelIndex nextIndex = wordListModel.index(index.row()+1);
        // 如果没有下一个单词
        if (!nextIndex.isValid()) {
            // 关闭按钮
            disableButton();
            return;
        } else {
            wordListView->scrollTo(nextIndex);
            wordListView->setCurrentIndex(nextIndex);
            emit wordListView->entered(nextIndex);
        }
    } else {
        // 单词已经不在学习队列，那么当前index的单词就是下一个单词
        wordListView->scrollTo(index);
        wordListView->setCurrentIndex(index);
        emit wordListView->entered(index);
    }
}

WordListModel::WordListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}



int WordListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return wordsList.size();
}

QVariant WordListModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() || index.row() >= wordsList.size() ) {
        return QVariant();
    }

    if ( role == Qt::DisplayRole || role == Qt::ToolTipRole ) {
        return wordsList.at(index.row());

    }
    else {
        return QVariant();
    }
}

void WordListModel::copyFormSet(const QSet<QString> &wordSet)
{
    wordsList = wordSet.values();
    //wordsList.sort();
    dataChanged();
}

WordListModel &WordListModel::push_word(const QString &word)
{
    if(!word.isEmpty()) {
        wordsList.push_back(word);
        dataChanged();
    }
    return *this;
}

void WordListModel::remove_word(unsigned int i)
{
    wordsList.remove(i);
    dataChanged();
}

void WordListModel::clear()
{
    wordsList.clear();
    dataChanged();
}

QList<QString>::iterator WordListModel::begin()
{
    return wordsList.begin();
}

QList<QString>::iterator WordListModel::end()
{
    return wordsList.end();
}

void WordListModel::dataChanged()
{
    beginResetModel();
    endResetModel();
}



#include "articlepad.h"

ArticlePad::ArticlePad(QWidget *parent)
    : QWidget{parent}
{
    articlePadLayout = new QHBoxLayout();
    articlePadLayout->setContentsMargins(5,10,0,10);
    setLayout(articlePadLayout);
    articleEdit = new QTextEdit();
    articleEdit->setContentsMargins(0,0,0,0);
    wordListView = new QListView();
    wordListView->setContentsMargins(0,0,0,0);
    articlePadLayout->addWidget(articleEdit, 9);
    articlePadLayout->addWidget(wordListView, 4);
    wordListView->setModel(&wordListModel);

    // 当文字跟新后，生成分词后的结果并显示
    connect(articleEdit, &QTextEdit::textChanged, this, [=](){tokenizer(articleEdit->toPlainText());});
    // 点击单词后
    connect(wordListView, &QListView::clicked, this, &ArticlePad::clickWord);
}

bool ArticlePad::tokenizer(QString article)
{
    if(article.isEmpty()) {
        article = " ";
    }
    // 字母和连字符
//    QRegularExpression re(R"(^$)");
    //QRegularExpression re(R"( [A-Za-z][A-Za-z-]*[A-Za-z] )");
    QRegularExpression re(R"((?<=[^-'A-Za-z]|^)[A-Za-z]+(?=[^-'A-Za-z]|$))");
    QSet<QString> uniqueWords;
    for (const QRegularExpressionMatch &match : re.globalMatch(article)) {
        QString word = match.captured(0);
    // 这里要接语言处理
        // 首先根据规则去除 stop word
        // 然后提取该单词的原型
    // 然后进行词库匹配
        // 与已经掌握的单词进行匹配，判断单词是否已经掌握
        uniqueWords.insert(word);
    }
//    QRegularExpressionMatchIterator i = re.globalMatch(article);
//
//    wordListModel.clear();
//    while (i.hasNext()) {
//        QRegularExpressionMatch match = i.next();
//        qDebug() << match.captured(0);
//        uniqueWords.insert(match.captured(0));
//    }
    wordListModel.copyFormSet(uniqueWords);
    return true;
}

void ArticlePad::clickWord(const QModelIndex &index)
{
    emit articlePadSearchWord(wordListModel.data(index).toString());
}

WordListModel::WordListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}



int WordListModel::rowCount(const QModelIndex &parent) const
{
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
    wordsList.sort();
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

void WordListModel::dataChanged()
{
    beginResetModel();
    endResetModel();
}

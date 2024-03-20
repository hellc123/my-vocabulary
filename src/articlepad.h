#ifndef ARTICLEPAD_H
#define ARTICLEPAD_H

#include <QObject>
#include <QWidget>
#include <QListView>
#include <QAbstractItemView>
#include <QList>
#include <QListView>
#include <QTextEdit>
#include <QCursor>
#include <QHBoxLayout>
#include <QRegularExpression>
#include <QSet>
// model
// 1、一个纯文本写字栏
// 2、对这个写字栏中的文本进行分词
// 3、提取所有分词结果的词干


// view
// 1、一个候选单词栏
// 2、将分出的词干显示在这里
// 3、点击单词，显示释义

// 用来存放单词数据
class WordListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WordListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void copyFormSet(const QSet<QString> & wordSet);
    WordListModel& push_word(const QString & word);
    void remove_word(unsigned int i);
    void clear();
private slots:
    // 使用这个方法来更新view的数据
    void dataChanged();

private:
    // 存放一个个单词
    QList<QString> wordsList;
};


// 分词和显示单词
// 用 QTextEditor 来书写章
// 用 QTextCursor 来高亮文本
class ArticlePad : public QWidget
{
    Q_OBJECT
public:
    explicit ArticlePad(QWidget *parent = nullptr);
private:
    // 横向布局
    QHBoxLayout * articlePadLayout;
    // 写字板
    QTextEdit *articleEdit;
    // 用来显示单词列表
    QListView *wordListView;
    // 用来存储单词数据
    WordListModel wordListModel;

    // 分词
    bool tokenizer(QString article);
    void clickWord(const QModelIndex &index);
signals:
    void articlePadSearchWord(QString word);

};


#endif // ARTICLEPAD_H

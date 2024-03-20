#ifndef ARTICLEPAD_H
#define ARTICLEPAD_H

#include <QObject>
#include <QWidget>
#include <QListView>
#include <QAbstractItemView>
#include <QList>
#include <QListView>
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
private slots:
    void historyChanged();

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
    QListView wordListView;
    WordListModel wordListModel;
signals:

};


#endif // ARTICLEPAD_H

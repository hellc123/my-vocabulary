#ifndef ARTICLEPAD_H
#define ARTICLEPAD_H

#include "databasemanager.h"
#include <QObject>
#include <QWidget>
#include <QListView>
#include <QAbstractItemView>
#include <QList>
#include <QStringList>
#include <QListView>
#include <QTextEdit>
#include <QCursor>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QSet>
#include "learningmodel.h"
#include <QPushButton>
#include "wordprocess.h"
#include <QMessageBox>
#include <QPlainTextEdit>
#include <algorithm>
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
    QList<QString>::iterator begin();
    QList<QString>::iterator end();
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
    explicit ArticlePad(const DatabaseManager &db,WordProcess & wp, LearningModel &lm, QWidget *parent = nullptr);
private:
    // 横向布局
    QHBoxLayout * articlePadLayout;
    // 写字板
    QPlainTextEdit * articleEdit;
    //QTextEdit *articleEdit;

    // 单词显示和学习区域
    QWidget *wordViewArea;
    QVBoxLayout *wordViewAreaLayout;
    // 用来显示单词列表
    QListView *wordListView;
    // 用来存储单词数据
    WordListModel wordListModel;
    // wordsList 从QSet<QString>读取数据，并按照单词得分和首字母排序
    void loadAndSort(QSet<QString> &wordSet);
    bool wordLessThan(const QString &s1, const QString &s2);

    // 学习区域
    QPushButton *easyButton;
    QPushButton *goodButton;
    QPushButton *hardButton;
    QPushButton *ignoreButton;

    // 分词
    bool tokenizer(QString article);
    void clickWord(const QModelIndex &index);
    // 词典数据库
    const DatabaseManager &db;
    // 语言处理类
    WordProcess & wp;
    // 学习模型
    LearningModel &lm;
    // 按钮是否 开启
    bool isEnableButton;
public:
signals:
    void articlePadSearchWord(QString word);

private slots:
    // 作用与当前 QListView 的 QModelIndex 对应word
    void easy();
    void good();
    void hard();
    void ignore();
    // 关闭按钮
    void disableButton();
    // 开启按钮
    void enableButton();
public:
    // 当按下学习按钮之后，要更新wordListView
    void updateListView();

};


#endif // ARTICLEPAD_H

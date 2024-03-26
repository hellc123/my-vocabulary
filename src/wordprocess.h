#ifndef WORDPROCESS_H
#define WORDPROCESS_H

#include <QObject>
#include "word.h"
#include "databasemanager.h"
#include <QVector>
#include <QSet>
#include <QFile>
#include <QSaveFile>
/// 一个输入 article 返回 QSet<QString> 的文字处理类 WordProcess
/// 1、分词功能
/// 2、判断首字母大写的单词能否搜索，或者这个任务能否交给 DatabaseManager 来做
///     -事实证明可以
/// 3、单词字面意义上的去重和单词在词形方面的去重，比如 apples 和 apple 是一个单词，只保留一个
class WordProcess
{
public:
    WordProcess(const DatabaseManager &db, const QString &stopWordsPath);
    WordProcess(const QString& article, const DatabaseManager &db, const QString &stopWordsPath);
    // 最终结果的 word 个数
    // 返回结果
    void getWordsSet(QSet<QString> &wordsSet);
    void setArticle(const QString &article);
    void ignore(const QString &word);
private:
    unsigned int count;
    // 不需要排序，只需要去重
    QSet<QString> words;
    // 词典数据库 用于词形去重
    const DatabaseManager &db;

    // 通过正则表达式分词
    bool tokenizer(const QString &article);
    // 太慢了
    // 原型去重
    bool deduplicate();

    // 去除 stop word
    void removeStopWord();
    void loadStopWord();
    // 不需要的单词
    QSet<QString> stopWords;
    const QString stopWordsFilePath;
    void saveStopWords();
};

#endif // WORDPROCESS_H

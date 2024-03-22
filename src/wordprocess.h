#ifndef WORDPROCESS_H
#define WORDPROCESS_H

#include <QObject>
#include "word.h"
#include <QVector>
/// 一个输入 article 返回 QSet<QString> 的文字处理类 WordProcess
/// 1、分词功能
/// 2、判断首字母大写的单词能否搜索，或者这个任务能否交给 DatabaseManager 来做
///     -事实证明可以
/// 3、单词字面意义上的去重和单词在词形方面的去重，比如 apples 和 apple 是一个单词，只保留一个
class WordProcess
{
public:
    WordProcess(const QString& path);
    // 大html中所以的word
    unsigned int count;
    QVector<Word> words;
};

#endif // WORDPROCESS_H

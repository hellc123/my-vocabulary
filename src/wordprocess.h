#ifndef WORDPROCESS_H
#define WORDPROCESS_H

#include <QObject>
#include "word.h"
#include <QVector>
// 输入一个 txt文件，返回word的集合
class WordProcess
{
public:
    WordProcess(const QString& path);
    // 大html中所以的word
    unsigned int count;
    QVector<Word> words;
};

#endif // WORDPROCESS_H

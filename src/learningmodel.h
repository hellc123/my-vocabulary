#ifndef LEARNINGMODEL_H
#define LEARNINGMODEL_H

#include <QObject>
#include <QDomDocument>
#include <QSet>
#include "word.h"
#include <qfile.h>
#include <QSaveFile>
///
/// The LearningModel class
/// 最终目标是找到目前不会的东西
/// 1、管理已有的学习记录
/// 2、通过已有的学习记录，判断目前不会的单词
///
class LearningModel
{
public:
    // 学习记录的路径
    LearningModel(const QString &path);
    // 根据wordSet中的单词（已经经过WordPress处理的原型单词）
    // 返回需要学习的单词，覆盖wordSet
    void getLearningSet(QSet<QString> &wordSet) const;

    // 单词学习部分
    // 加20分
    void easy(const QString &word);
    // 加10分
    void good(const QString &word);
    // 加5分
    void hard(const QString &word);
    // 减10分
    void unfamiliar(const QString &word);
private:
    WordList words;
    const QString wordsFilePath;
    // 保存到path
    void save() const;
    // 给某个单词加分
    void addScore(const QString &word, int score);
    // 都某个单词减分
    void subtractScore(const QString &word, int score);
};

#endif // LEARNINGMODEL_H

#include "learningmodel.h"

LearningModel::LearningModel(const QString &path) :
    wordsFilePath(path)
{
    QFile  xmlFile(path);
    qDebug() << xmlFile.exists();
    if(xmlFile.open(QFile::ReadOnly | QFile::Text)) {
        QString data = xmlFile.readAll();
        //qDebug() << data;
        words.fromXMLString(data);
        xmlFile.close();
    } else {
        qDebug() << "LearningModel can not open file: " << path;
        qDebug() << xmlFile.errorString();
    }
}

void LearningModel::getLearningSet(QSet<QString> &wordSet) const
{
    double averageScore = words.getAverageScore();
    QSet<QString> newWordSet;
    for (const QString& word : wordSet) {
        // 在用户学习记录里面搜索
        Word newWord = words.getWord(word);
        //qDebug() << newWord.getScore();
        // 不管有没有找到
        if (newWord.getScore() <= averageScore)
            newWordSet.insert(word);
        //qDebug() << word;
    }
    wordSet = newWordSet;
}

void LearningModel::easy(const QString &word)
{
    addScore(word, 20);
}

void LearningModel::good(const QString &word)
{
    addScore(word, 10);
}

void LearningModel::hard(const QString &word)
{
    addScore(word, 5);
}

void LearningModel::save() const
{
    // 使用QSaveFile
    QSaveFile wordsProfile(wordsFilePath);
    if(!wordsProfile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Can not open file" + wordsFilePath+".tem";
        return;
    }
    wordsProfile.write(words.toXMLString().toUtf8());
    // 提交到原来文件
    wordsProfile.commit();
    //
}

void LearningModel::addScore(const QString &word, unsigned int score)
{
    if(word.isEmpty())
        return;
    // 加分
    words.addWordScore(word,score);
    // 保存
    save();
}

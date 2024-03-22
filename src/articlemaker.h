#ifndef ARTICLEMAKER_H
#define ARTICLEMAKER_H

#include <QObject>
#include <QString>
#include "databasemanager.h"
// 输入一个 word
// 在数据库中找到所有匹配的html，然后组合成一个最终html

class ArticleMaker
{
public:
    ArticleMaker(const DatabaseManager& db, const VocabularyDatabase& vdb);
    ArticleMaker(const QString & word, const DatabaseManager& db, const VocabularyDatabase& vdb);
    bool searchWord(const QString & word);
    bool searchResorce(const QString & fileName, QByteArray & data);
    QString getHtml();
    QString getWord();
private:
    QString _word;

    // 词典库
    const DatabaseManager& _db;
    // 四六级考研词库
    const VocabularyDatabase& _vdb;
    QString _html;
};

#endif // ARTICLEMAKER_H

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
    ArticleMaker(const DatabaseManager& db);
    ArticleMaker(const QString & word, const DatabaseManager& db);
    bool searchWord(const QString & word);
    bool searchResorce(const QString & fileName, QByteArray & data);
    QString getHtml();
    QString getWord();
private:
    QString _word;
    const DatabaseManager& _db;
    QString _html;
};

#endif // ARTICLEMAKER_H

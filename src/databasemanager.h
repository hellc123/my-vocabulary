#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QVector>
#include "word.h"
class DatabaseManager
{
public:
    DatabaseManager(const QString &path);
    ~DatabaseManager();
    bool isOpen() const;
    bool searchWord(const Word & searchWord,QVector<Word> & Words);
private:
    QSqlDatabase db;
    // 创建词典数据库
    bool createTable();
    bool insertWord(Word & word);
    bool hasTable(const QString &tableName);
public:
    // 初始化数据库
    bool initDictionary(const QString &dictPath);
};

#endif // DATABASEMANAGER_H

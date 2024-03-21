#include "databasemanager.h"
#include "wordProcess.h"

DatabaseManager::DatabaseManager(const QString &path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if(db.open()) {
        qDebug() << "database is open";
    } else {
        qDebug() << "database error!";
    }
    createTable();
}

DatabaseManager::~DatabaseManager()
{
    if(isOpen()) {
        db.close();
    }
}

bool DatabaseManager::isOpen() const
{
    return db.isOpen();
}

bool DatabaseManager::searchWord(const Word & searchWord,QVector<Word> & Words) const
{
    // 执行查询
    QSqlQuery query;
    if(!searchWord.getWord().isEmpty()) {
        QString sqlQuery("SELECT html FROM dictionaryTable WHERE word=%1");
        sqlQuery = sqlQuery.arg("\"" + searchWord.getWord() + "\"");
        query.prepare(sqlQuery);
        qDebug() << sqlQuery;
    }
    if (!query.exec()) {
        qDebug() << "Error: Failed to execute query.";
        return false;
    }

    Word tem;
    tem.setWord(searchWord.getWord());
    // 处理查询结果
    while (query.next()) {
        // 获取查询结果中的字段值
        tem.setHtml(query.value(0).toString().trimmed());
        Words.push_back(tem);
    }
    return true;
}

bool DatabaseManager::createTable()
{
    bool success = true;
    QSqlQuery query;
    // 建立词典表
    // id 每个单词的主键
    // word 单词
    // html 单词对应的html
    QString dictionaryTable(R"(CREATE TABLE dictionaryTable(
                  id INTEGER PRIMARY KEY AUTOINCREMENT,
                  word TEXT,
                  html TEXT);)");
    query.prepare(dictionaryTable);
    // 检测是否执行成功
    if (!query.exec())
    {
        qDebug() << "dictionary table already created ";
        success = false;
    } else {
        qDebug() << "dictionary table is created firstly";
    }
    return success;
}

bool DatabaseManager::insertWord(Word &word)
{
    bool success = false;
    if (!word.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO dictionaryTable(word,html) VALUES (:word,:html)");
        queryAdd.bindValue(":word", word.getWord());
        qDebug() << word.getWord();
        queryAdd.bindValue(":html", word.getHtml());
        if(queryAdd.exec()) {
            success = true;
        }
        else
            qDebug() << "record could not add: " << queryAdd.lastError();
    }
    else
        qDebug() << "Data is required to insert.";
    return success;
}

bool DatabaseManager::hasTable(const QString &tableName)
{
    QString createTable(QString("SELECT name FROM sqlite_master WHERE type='table' AND name='%1'").arg(tableName));
    QSqlQuery query;
    query.prepare(createTable);
    return !query.exec();
}

bool DatabaseManager::initDictionary(const QString &dictPath)
{
    //dictPath 是字典的大html位置
    WordProcess parser(dictPath);
    for(Word& w : parser.words) {
        insertWord(w);
    }
    // 暂时不做错误处理
    return true;
}

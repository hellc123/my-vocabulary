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
#include <QFile>
#include <QByteArray>
#include <QDir>
#include <QFileInfo>
#include "word.h"



/*
// 数据库结构
CREATE TABLE dictionaryTable(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    word TEXT,
    html TEXT);
CREATE TABLE sound(
    file TEXT PRIMARY KEY,
    data BLOB);
CREATE TABLE image(
    file TEXT PRIMARY KEY,
    data BLOB);
CREATE TABLE css(
    file TEXT PRIMARY KEY,
    data BLOB);
CREATE TABLE js(
    file TEXT PRIMARY KEY,
    data BLOB);
CREATE TABLE font(
    file TEXT PRIMARY KEY,
    data BLOB);
CREATE TABLE svg(
    file TEXT PRIMARY KEY,
    data BLOB);
*/

// 由解析出来的mdx资源文件夹，建立数据库
class DatabaseManager
{
public:
    DatabaseManager(const QString &path);
    ~DatabaseManager();
    bool isOpen() const;
    // 搜索 searchWord 将结果保存在Words中
    bool searchWord(const Word & searchedWord,QVector<Word> & Words) const;
    // 搜索 fileName的资源，然后保存在data里面
    bool searchResorce(const QString & fileName, QByteArray & data) const;
    // 通过词典，判断一个词的原型
    Word findOriginalWord(const Word & searchedWord) const;
private:
    QSqlDatabase db;
    // 创建词典 html 数据库
    bool createTable();
    // 创建音频表 mp3
    bool createSoundTable();
    // 创建图片表 png
    bool createImageTable();
    // 创建 svg 表
    bool createSVGTable();
    // 创建 css 表
    bool createCSSTable();
    // 创建 js 表
    bool createJSTable();
    // 创建字体表 tff 格式
    bool createFontTable();

    bool insertWord(Word & word);
    bool insertBLOB(const QString &tableName,const QString &filePath);
    bool hasTable(const QString &tableName) const;

    // 从表中获得数据
    bool getResource(const QString &tableName, const QString &resouceName, QByteArray &data) const;
public:
    // 初始化数据库
    bool initDictionary(const QString &dictPath);
    // 初始化音频数据
    bool initSoundData(const QString &soundPath);
    // 初始化图片 png 数据
    bool initImageData(const QString &imagePath);
    // 初始化 css 数据
    bool initCSSData(const QString &path);
    // 初始化 js 数据
    bool initJSData(const QString &path);
    // 初始化 tff 数据
    bool initFontData(const QString &path);
    // 初始化svg 数据
    bool initSVGDate(const QString &path);

};


// 四六级词库数据
// 数据库结构
/*
CREATE TABLE vocabulary (
    word TEXT PRIMARY KEY,
    CET4 TEXT,
    CET6 TEXT,
    NEEP TEXT,
    rank TEXT
);
*/
class VocabularyDatabase {
public:
    VocabularyDatabase(const QString &path);
    Word searchWord(const Word &word) const;
private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H

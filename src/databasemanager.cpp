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
    createSoundTable();
    createImageTable();
    createCSSTable();
    createJSTable();
    createFontTable();
    createSVGTable();
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
    QSqlQuery query(db);
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
    return !Words.isEmpty();
}

bool DatabaseManager::searchResorce(const QString &fileName, QByteArray &data) const
{
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
    if (fileName.isEmpty())
        return false;
    QString fileType = fileName.split(".").last();
    if(fileType==fileName) {
        qDebug() << "File type error!";
        return false;
    }
    if(fileType=="mp3"){
        getResource("sound", fileName, data);
    } else if(fileType=="png"){
        getResource("image", fileName, data);
    } else if(fileType=="css"){
        getResource("css", fileName, data);
    } else if(fileType=="js"){
        getResource("js", fileName, data);
    } else if(fileType=="tff"){
        getResource("font", fileName, data);
    } else if(fileType=="svg"){
        getResource("svg", fileName, data);
    }
    return true;
}

bool DatabaseManager::createTable()
{
    bool success = true;
    QSqlQuery query(db);
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

bool DatabaseManager::createSoundTable()
{
    bool success = true;
    QSqlQuery query(db);
    // 建立词典表
    // file mp3 文件名
    // data BLOB
    QString soundTable(R"(CREATE TABLE sound(
                  file TEXT PRIMARY KEY,
                  data BLOB);)");
    query.prepare(soundTable);
    // 检测是否执行成功
    if (!query.exec())
    {
        qDebug() << "sound table already created ";
        success = false;
    } else {
        qDebug() << "sound table is created firstly";
    }
    return success;
}

bool DatabaseManager::createImageTable()
{
    bool success = true;
    QSqlQuery query(db);
    // 建立词典表
    // file png 文件名
    // data BLOB
    QString imageTable(R"(CREATE TABLE image(
                  file TEXT PRIMARY KEY,
                  data BLOB);)");
    query.prepare(imageTable);
    // 检测是否执行成功
    if (!query.exec())
    {
        qDebug() << "image table already created ";
        success = false;
    } else {
        qDebug() << "image table is created firstly";
    }
    return success;
}

bool DatabaseManager::createCSSTable()
{
    bool success = true;
    QSqlQuery query(db);
    // 建立词典表
    // file 文件名
    // data BLOB
    QString imageTable(R"(CREATE TABLE css(
                  file TEXT PRIMARY KEY,
                  data BLOB);)");
    query.prepare(imageTable);
    // 检测是否执行成功
    if (!query.exec())
    {
        qDebug() << "CSS table already created";
        success = false;
    } else {
        qDebug() << "CSS table is created firstly";
    }
    return success;
}

bool DatabaseManager::createJSTable()
{
    bool success = true;
    QSqlQuery query(db);
    // 建立词典表
    // file 文件名
    // data BLOB
    QString JSTable(R"(CREATE TABLE js(
                  file TEXT PRIMARY KEY,
                  data BLOB);)");
    query.prepare(JSTable);
    // 检测是否执行成功
    if (!query.exec())
    {
        qDebug() << "JS table already created";
        success = false;
    } else {
        qDebug() << "JS table is created firstly";
    }
    return success;
}

bool DatabaseManager::createFontTable()
{
    bool success = true;
    QSqlQuery query(db);
    // 建立词典表
    // file 文件名
    // data BLOB
    QString fontTable(R"(CREATE TABLE font(
                  file TEXT PRIMARY KEY,
                  data BLOB);)");
    query.prepare(fontTable);
    // 检测是否执行成功
    if (!query.exec())
    {
        qDebug() << "Font table already created";
        success = false;
    } else {
        qDebug() << "Font table is created firstly";
    }
    return success;
}

bool DatabaseManager::createSVGTable()
{
    bool success = true;
    QSqlQuery query(db);
    // 建立词典表
    // file 文件名
    // data BLOB
    QString fontTable(R"(CREATE TABLE svg(
                  file TEXT PRIMARY KEY,
                  data BLOB);)");
    query.prepare(fontTable);
    // 检测是否执行成功
    if (!query.exec())
    {
        qDebug() << "SVG table already created";
        success = false;
    } else {
        qDebug() << "SVG table is created firstly";
    }
    return success;
}

bool DatabaseManager::insertWord(Word &word)
{
    bool success = false;
    if (!word.isEmpty())
    {
        QSqlQuery queryAdd(db);
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

bool DatabaseManager::insertBLOB(const QString &tableName, const QString &filePath)
{
    QFile blobFile(filePath);
    QFileInfo blobFileInfo(filePath);
    QByteArray blobData;
    if (!blobFile.open(QFile::ReadOnly)) {
        qDebug() << filePath << " can not open!";
        return false;
    } else {
        blobData = blobFile.readAll();
    }
    if (!tableName.isEmpty() && !filePath.isEmpty())
    {
        QSqlQuery queryAdd(db);
        queryAdd.prepare(QString("INSERT INTO %1(file,data) VALUES (:file,:data)").arg(tableName));
        queryAdd.bindValue(":file", blobFileInfo.fileName());
        queryAdd.bindValue(":data", blobData);
        if(!queryAdd.exec()) {
            qDebug() << "record could not add: " << queryAdd.lastError();
            return false;
        }
    }
    else
        qDebug() << "Data is required to insert.";
    return true;
}


bool DatabaseManager::hasTable(const QString &tableName) const
{
    QString createTable(QString("SELECT name FROM sqlite_master WHERE type='table' AND name='%1'").arg(tableName));
    QSqlQuery query(db);
    query.prepare(createTable);
    return !query.exec();
}

bool DatabaseManager::getResource(const QString &tableName, const QString &resouceName, QByteArray &data) const
{
    // 执行查询
    QSqlQuery query(db);
    if(!tableName.isEmpty() && !resouceName.isEmpty()) {
        QString sqlQuery("SELECT data FROM %1 WHERE file=%2");
        sqlQuery = sqlQuery.arg(tableName, "\"" + resouceName + "\"");
        query.prepare(sqlQuery);
        qDebug() << sqlQuery;
    }
    if (!query.exec()) {
        qDebug() << "Error: Failed to get resouce:" << tableName << ":" << resouceName;
        return false;
    }

    // 处理查询结果
    if (query.next()) {
        // 获取查询结果中的字段值
        data.append(query.value(0).toByteArray());
    }
    return true;
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

bool DatabaseManager::initSoundData(const QString &soundPath)
{
    //获取soundPath
    QDir soundDir(soundPath);
    if(!soundDir.exists()) {
        qDebug() << soundPath <<" is not existed!";
        return false;
    } else {
        qsizetype fileNumber = soundDir.count();
        auto fileList = soundDir.entryInfoList(QDir::Files);
        qsizetype i = 0;
        for(auto &soundfile : fileList) {
            insertBLOB("sound", soundfile.absoluteFilePath());
            qDebug() << double(++i) / fileNumber * 100 << "%";
        }
    }

    // 暂时不做错误处理
    return true;
}

bool DatabaseManager::initImageData(const QString &imagePath)
{
    //获取imagePath
    QDir soundDir(imagePath);
    if(!soundDir.exists()) {
        qDebug() << imagePath <<" is not existed!";
        return false;
    } else {
        qsizetype fileNumber = soundDir.count();
        auto fileList = soundDir.entryInfoList(QDir::Files);
        qsizetype i = 0;
        for(auto &soundfile : fileList) {
            insertBLOB("image", soundfile.absoluteFilePath());
            qDebug() << double(++i) / fileNumber * 100 << "%";
        }
    }
    // 暂时不做错误处理
    return true;
}

bool DatabaseManager::initCSSData(const QString &path)
{
    //获取path
    QDir fileDir(path);
    if(!fileDir.exists()) {
        qDebug() << path <<" is not existed!";
        return false;
    } else {
        qsizetype fileNumber = fileDir.count();
        auto fileList = fileDir.entryInfoList(QDir::Files);
        qsizetype i = 0;
        for(auto &soundfile : fileList) {
            insertBLOB("css", soundfile.absoluteFilePath());
            qDebug() << double(++i) / fileNumber * 100 << "%";
        }
    }
    // 暂时不做错误处理
    return true;
}

bool DatabaseManager::initJSData(const QString &path)
{
    //获取path
    QDir fileDir(path);
    if(!fileDir.exists()) {
        qDebug() << path <<" is not existed!";
        return false;
    } else {
        qsizetype fileNumber = fileDir.count();
        auto fileList = fileDir.entryInfoList(QDir::Files);
        qsizetype i = 0;
        for(auto &soundfile : fileList) {
            insertBLOB("js", soundfile.absoluteFilePath());
            qDebug() << double(++i) / fileNumber * 100 << "%";
        }
    }
    // 暂时不做错误处理
    return true;
}

bool DatabaseManager::initFontData(const QString &path)
{
    //获取path
    QDir fileDir(path);
    if(!fileDir.exists()) {
        qDebug() << path <<" is not existed!";
        return false;
    } else {
        qsizetype fileNumber = fileDir.count();
        auto fileList = fileDir.entryInfoList(QDir::Files);
        qsizetype i = 0;
        for(auto &soundfile : fileList) {
            insertBLOB("font", soundfile.absoluteFilePath());
            qDebug() << double(++i) / fileNumber * 100 << "%";
        }
    }
    // 暂时不做错误处理
    return true;
}

bool DatabaseManager::initSVGDate(const QString &path)
{
    //获取path
    QDir fileDir(path);
    if(!fileDir.exists()) {
        qDebug() << path <<" is not existed!";
        return false;
    } else {
        qsizetype fileNumber = fileDir.count();
        auto fileList = fileDir.entryInfoList(QDir::Files);
        qsizetype i = 0;
        for(auto &soundfile : fileList) {
            insertBLOB("svg", soundfile.absoluteFilePath());
            qDebug() << double(++i) / fileNumber * 100 << "%";
        }
    }
    // 暂时不做错误处理
    return true;
}

VocabularyDatabase::VocabularyDatabase(const QString &path)
{
    db = QSqlDatabase::addDatabase("QSQLITE", "secondary");
    db.setDatabaseName(path);
    if(db.open()) {
        qDebug() << "Vocabulary database is open";
    } else {
        qDebug() << "Vocabulary database error!";
        qDebug() << db.lastError().text();
    }
}

Word VocabularyDatabase::searchWord(const QString &word) const
{
    // 执行查询
    QSqlQuery query(db);
    Word result;
    result.setWord(word);
    if(!word.isEmpty()) {

        QString sqlQuery("SELECT CET4,CET6,NEEP,rank FROM vocabulary WHERE word=\"%1\"");
        sqlQuery = sqlQuery.arg(word);
        query.prepare(sqlQuery);
        qDebug() << sqlQuery;
    }
    if (!query.exec()) {
        qDebug() << "Error: Failed to search word in vocabulary.";
        qDebug() << query.lastError();
    }

    // 处理查询结果
    if (query.next()) {
        // 获取查询结果中的字段值
        result.setCET4(query.value(0).toString()=="CET4");
        result.setCET6(query.value(1).toString()=="CET4");
        result.setNEEP(query.value(2).toString()=="NEEP");
        result.setRank(query.value(3).toString());
    }
    return result;
}

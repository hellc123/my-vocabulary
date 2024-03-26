#include "wordprocess.h"
#include "qregularexpression.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
WordProcess::WordProcess(const DatabaseManager &db, const QString &stopWordsPath) :
    db(db),
    stopWordsFilePath(stopWordsPath)
{

}

WordProcess::WordProcess(const QString& article, const DatabaseManager &db, const QString &stopWordsPath) :
    db(db),
    stopWordsFilePath(stopWordsPath)
{
    // 分词
    tokenizer(article);
    // 去除stop word
    removeStopWord();
    // 查找词典，找到原型，然后去重
    deduplicate();
    // 去两边，防止非原型命中stop word，但是其他形式没有
    removeStopWord();
}

void WordProcess::getWordsSet(QSet<QString> &wordsSet)
{
    for (const QString & word : words) {
        wordsSet.insert(word);
    }
}

void WordProcess::setArticle(const QString &article)
{
    // "Drive" bug

    // 分词
    tokenizer(article);
    // Drive
    // 去除stop word
    removeStopWord();
    // 除不了 因为 stop word 是 dirve
    // 查找词典，找到原型，然后去重
    deduplicate();
    // 去两边，防止非原型命中stop word，但是其他形式没有
    removeStopWord();
}

void WordProcess::ignore(const QString &word)
{
    // 已经有了
    if(stopWords.contains(word)) {
        return;
    }
    // 判断word是否合法 目前先不判断
    stopWords.insert(word);
    saveStopWords();
    qDebug() << "Ignore word: " << word;
}

bool WordProcess::tokenizer(const QString &article)
{
    if(article.isEmpty()) {
        return false;
    }
    if(!words.isEmpty()) {
        words.clear();
    }
    // 字母和连字符
    // clang 建议使用static类型的正则表达式
    static QRegularExpression re(R"((?<=[^-'A-Za-z]|^)[A-Za-z]+(?=[^-'A-Za-z]|$))");
    for (const QRegularExpressionMatch &match : re.globalMatch(article)) {
        words.insert(match.captured(0));
    }
    return true;
}

bool WordProcess::deduplicate()
{
    QSet<QString> deduplicatedWords;
    for (const QString & word : words) {
        // 找到原型
        Word temWord = db.findOriginalWord(Word(word));
        // 词典里面搜不到的就说明是错别词，舍弃
        if (!temWord.getWord().isEmpty()) {
            deduplicatedWords.insert(temWord.getWord());
        }
    }
    count = deduplicatedWords.count();
    words = deduplicatedWords;
    return true;
}

void WordProcess::removeStopWord()
{
    // 加载 stop word
    loadStopWord();
    // 去除 stop word
    // 不能这么写
//    for (const QString & word : words) {
//        if(stopWords.contains(word)) {
//            words.remove(word);
//            qDebug() << word;
//        }
//    }
    QSet<QString> toBeRemoved;
    // 一定不要在一遍循环，一遍修改循环
    // 这样会造成特别奇怪的随机错误
    for (const QString & word : words) {
        if(stopWords.contains(word)) {
            toBeRemoved.insert(word);
        }
    }
    words = words - toBeRemoved;
}

void WordProcess::loadStopWord()
{
    // stop word 是以回车分隔的文本文件
    QFile stopWordsFile(stopWordsFilePath);
    if (!stopWordsFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Can not open stop words file " << stopWordsFilePath;
        return;
    }
    QString stopWordsString = stopWordsFile.readAll();
    QStringList stopWordsStringList = stopWordsString.split('\n',Qt::SkipEmptyParts);
    for (const QString & word : stopWordsStringList) {
        stopWords.insert(word);
    }
    stopWordsFile.close();
}

void WordProcess::saveStopWords()
{
    QSaveFile stopWordsFile(stopWordsFilePath);
    if(!stopWordsFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Can not open stop words file" << stopWordsFilePath;
    }
    QString stopWordString;
    for (auto begin = stopWords.begin(), end = stopWords.end(); begin != end; begin++) {
        stopWordString += *begin;
        stopWordString += '\n';
    }
    stopWordsFile.write(stopWordString.toUtf8());
    stopWordsFile.commit();
}

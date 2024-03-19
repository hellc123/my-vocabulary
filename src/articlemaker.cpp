#include "articlemaker.h"
#include "word.h"
#include <QVector>
ArticleMaker::ArticleMaker(const DatabaseManager &db):
    _db(db)
{

}

ArticleMaker::ArticleMaker(const QString &word, const DatabaseManager &db) :
    _word(word),
    _db(db)
{
}
QString ArticleMaker::getHtml()
{
    return _html;
}

QString ArticleMaker::getWord()
{
    return _word;
}

bool ArticleMaker::searchWord(const QString &word)
{
    _word = word;
    if(_word.isEmpty())
        return false;
    Word searchWord(_word);
    QVector<Word> searchWords;
    // 在词典数据库里面搜索
    _db.searchWord(searchWord,searchWords);

    QString body;
    // 遍历所有html
    for (auto begin = searchWords.begin(),end = searchWords.end();
         begin != end;) {
        if(begin->html.first(8)=="@@@LINK=") {
            //继续搜索LINK后对应的单词
            Word newWord(begin->html.mid(8));
            // 搜索新的单词，并将其放到begin的后面
            // 由于QVector本质上就是QList，所有随机插入开销不大
            QVector<Word> newSearchWords;
            _db.searchWord(newWord,newSearchWords);
            // 把原来的删除
            searchWords.erase(begin);
            for (const auto & newSearchWord : newSearchWords) {
                searchWords.prepend(newSearchWord);
            }
            begin = searchWords.begin();
        } else {
            // 这是一个完成的单词html
            body += (begin->html + "\n");
            searchWords.erase(begin++);
        }
    }
    // 加上头部
    QString head(R"(<!DOCTYPE html>
<meta charset="utf-8">
<html>
<title>animal</title>
<head>
    <script src="myJavascript.js" charset="utf-8" type="text/javascript" language="javascript"></script>
</head>
<audio id="audioPlayer" controls style="display: none;">
    Your browser does not support the audio element.
</audio>)");
    // 加上尾部
    QString tailor(R"(</html>)");
    _html = head + body + tailor;
    return !_html.isEmpty();
}

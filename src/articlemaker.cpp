#include "articlemaker.h"
#include "word.h"
#include <QVector>
#include <QSet>
ArticleMaker::ArticleMaker(const DatabaseManager &db, const VocabularyDatabase& vdb):
    _db(db),
    _vdb(vdb)
{

}

ArticleMaker::ArticleMaker(const QString &word, const DatabaseManager &db, const VocabularyDatabase& vdb) :
    _word(word),
    _db(db),
    _vdb(vdb)
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
    if (!_db.searchWord(searchWord,searchWords)) {
        // 没有找到结果
        QString NotFonudHtml = R"(<!DOCTYPE html><html><head></head><body><div class="gdnotfound"><p>No definition for <b>%1</b> was found in dictionary.</p></div></body></html>)";
        _html = NotFonudHtml.arg(_word);
        return false;
    }



    // 在四六级考研词库里面搜索
    searchWord = _vdb.searchWord(Word(_word));

    QString body;
    // 遍历所有html
    // 把 _word 和 @@@LINK=LINKWORD 都放到一个set里面，从而避免循环连接
    QSet<QString> searchedWords;
    searchedWords.insert(_word);
    for (auto begin = searchWords.begin(),end = searchWords.end();
         begin != end;) {
        // 为了便于debug，打印QVector<Word> searchWords的所有元素
//        qDebug() << "begin";
//        for (const auto & w :searchWords) {
//            qDebug() << w.word;
//        }
        if(begin->getHtml().first(8)=="@@@LINK=") {
            //继续搜索LINK后对应的单词
            Word newWord(begin->getHtml().mid(8));
            // 判断是否已经被搜索过了
            if (!searchedWords.contains(newWord.getWord())) {
                // 搜索新的单词，并将其放到begin的后面
                // 由于QVector本质上就是QList，所有随机插入开销不大
                QVector<Word> newSearchWords;
                _db.searchWord(newWord,newSearchWords);

                // 把原来的删除
                searchWords.erase(begin);
                // 将新的结果，保留其顺序，放到前面
                searchWords = newSearchWords + searchWords;
                //for (const auto & newSearchWord : newSearchWords) {
                //    searchWords.insert(begin, newSearchWord);
                //}

                begin = searchWords.begin();
                end = searchWords.end();
                searchedWords.insert(newWord.getWord());
            } else {
                // 如果已经被搜索过了，那就跳过
                searchWords.erase(begin);
                begin=searchWords.begin();
                end = searchWords.end();
            }

        } else {
            // 这是一个完成的单词html
            body += (begin->getHtml() + "\n");
            //searchWords.erase(begin++);
            searchWords.erase(begin);
            begin=searchWords.begin();
            end = searchWords.end();
        }
    }

    // 加上头部
    QString head(R"(<!DOCTYPE html>
<meta charset="utf-8">
<html>
<title>animal</title>
<head>
    <link rel="stylesheet" type="text/css" href="qrc:/rsc/articleStyle.css" />
    <script src="qrc:/rsc/articleJS.js" charset="utf-8" type="text/javascript" language="javascript"></script>
</head>
<audio id="audioPlayer" controls style="display: none;">
    Your browser does not support the audio element.
</audio>)");



    // 显示四六级标签
    QString tagHtml;
    QString tagTemplate = R"(<div class="rounded">%1</div>)";
    if(searchWord.IsCET4())
        tagHtml += tagTemplate.arg("CET4") + " ";

    if(searchWord.IsCET6())
        tagHtml += tagTemplate.arg("CET6") + " ";

    if(searchWord.IsNEEP())
        tagHtml += tagTemplate.arg("NEEP") + " ";

    if(!searchWord.getRank().isEmpty())
        tagHtml += tagTemplate.arg(searchWord.getRank()) + " ";

    // 显示语言切换按钮

    QString languageButton = R"(<button class="rounded language-button" onclick=languageSwitch()>Enlish</button>)";

    // 加上尾部
    QString tailor(R"(</html>)");
    _html = head + tagHtml + languageButton + body + tailor;
    return !_html.isEmpty();
}

bool ArticleMaker::searchResorce(const QString &fileName, QByteArray &data)
{
    return _db.searchResorce(fileName, data);
}

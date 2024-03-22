#include "word.h"
Word::Word(const QString &w, const QString &h) :
    word(w),
    html(h),
    originalWord(w)
{
    score = 0;
    CET4 = false;
    CET6 = false;
    NEEP = false;
}

void Word::setWordInformation(const QString &w, bool cet4, bool cet6, bool neep, unsigned int sc, const QString & rk)
{
    word = w;
    CET4 = cet4;
    CET6 = cet6;
    NEEP = neep;
    score = sc;
    rank = rk;
}

void Word::addScore(unsigned int sc)
{
    // 获取当前时间
    QDateTime newTime = QDateTime::currentDateTime();
    QPair<QDateTime,unsigned int> record(newTime,sc);
    qDebug() << "Word:" << word << "Original:" << originalWord << "Record:" << newTime.toString() << sc;
    records.push_back(record);
    score += sc;
}

bool Word::isEmpty()
{
    // 只要word和html中的一个没有，就返回空
    return word.isEmpty() || html.isEmpty();
}

QString Word::getOriginalWord() const
{
    return originalWord;
}

unsigned int Word::getScore() const
{
    return score;
}

void Word::setScore(unsigned int newScore)
{
    score = newScore;
}

bool Word::IsCET4() const
{
    return CET4;
}

void Word::setCET4(bool newIsCET4)
{
    CET4 = newIsCET4;
}

bool Word::IsCET6() const
{
    return CET6;
}

void Word::setCET6(bool newIsCET6)
{
    CET6 = newIsCET6;
}

bool Word::IsNEEP() const
{
    return NEEP;
}

void Word::setNEEP(bool newIsNEEP)
{
    NEEP = newIsNEEP;
}

QString Word::getRank() const
{
    return rank;
}

void Word::setRank(const QString & newRank)
{
    rank = newRank;
}

QString Word::getHtml() const
{
    return html;
}

void Word::setHtml(const QString &newHtml)
{
    html = newHtml;
}

void Word::setWord(const QString &newWord)
{
    word = newWord;
}

QString Word::getWord() const
{
    return word;
}

QString Word::toXMLString() const
{
    //<word>
        //<name>word</name>
        //<original>originalWord</original>
        //<score>score</score>
        //<CET4>isCET4</CET4>
        //<CET6>isCET6</CET6>
        //<NEEP>isNEEP</NEEP>
        //<rank>rank<rank>
        //<records>
            //<addScore time="yyyy/MM/dd-HH/mm/ss">10</addScore>
        //</records>
    //</word>
    QString xmlString;
    // 完成基本信息
    xmlString = QString("<word><name>%1</name><original>%2</original>"
                        "<score>%3</score><CET4>%4</CET4>"
                        "<CET6>%5</CET6><NEEP>%6</NEEP><rank>%7</rank>")
            .arg(word)
            .arg(originalWord)
            .arg(score)
            .arg(CET4?"CET4":"")
            .arg(CET6?"CET6":"")
            .arg(NEEP?"NEEP":"")
            .arg(rank);
    // 完成记录的书写
    xmlString += "<records>";
    for(const auto & record : records) {
        //<addScore time="yyyy/MM/dd-HH/mm/ss">10</addScore>
        xmlString += QString("<addScore time=\"%1\">%2</addScore>")
                .arg(record.first.toString("yyyy/MM/dd-HH/mm/ss"))
                .arg(record.second);
    }
    xmlString += "</records></word>";
    qDebug() << xmlString;
    return xmlString;
}

void Word::formXMLString(const QString &xmlData)
{
    QDomDocument xml(xmlData);
    //<word>
        //<name>word</name>
        //<original>originalWord</original>
        //<score>score</score>
        //<CET4>isCET4</CET4>
        //<CET6>isCET6</CET6>
        //<NEEP>isNEEP</NEEP>
        //<rank>rank<rank>
        //<records>
            //<addScore time="yyyy/MM/dd-HH/mm/ss">10</addScore>
        //</records>
    //</word>
    QDomNodeList nameElement = xml.elementsByTagName("name");
    QDomNodeList originalElement = xml.elementsByTagName("name");
    QDomNodeList scoreElement = xml.elementsByTagName("name");
    QDomNodeList CET4Element = xml.elementsByTagName("name");
    QDomNodeList CET6Element = xml.elementsByTagName("name");
    QDomNodeList NEEPElement = xml.elementsByTagName("name");
    QDomNodeList rankElement = xml.elementsByTagName("name");
    QDomNodeList recordsElement = xml.elementsByTagName("name");
}


QString WordList::toXMLString() const
{
    // 格式
    //<lexicon>
        //<word>
            //<name>word</name>
            //<original>originalWord</original>
            //<score>score</score>
            //<CET4>isCET4</CET4>
            //<CET6>isCET6</CET6>
            //<NEEP>isNEEP</NEEP>
            //<rank>rank<rank>
            //<records>
                //<addScore time="yyyy/MM/dd-HH/mm/ss">10</addScore>
            //</records>
        //</word>
    //</lexicon>
    QString xmlString;
    xmlString +="<lexicon>";
    for (const Word& word : *this) {
        xmlString += word.toXMLString();
    }
    xmlString +="</lexicon>";
    return xmlString;
}

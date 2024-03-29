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

bool Word::isEmpty() const
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
    //qDebug() << xmlString;
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
    // 根element 是word
    formQDomElement(xml.toElement());

}

void Word::formQDomElement(const QDomElement &node)
{
    // 这个 node 是<word>
    QDomNodeList elements = node.childNodes();
    if(elements.count() != 8) {
        qDebug() << "XML error !";
        return;
    }
    // name
    word = elements.at(0).toElement().text();
    originalWord = elements.at(1).toElement().text();
    score = elements.at(2).toElement().text().toUInt();
    CET4 = elements.at(3).toElement().text() == "CET4";
    CET6 = elements.at(4).toElement().text() == "CET6";
    NEEP = elements.at(5).toElement().text() == "NEEP";
    rank = elements.at(6).toElement().text();
    QDomNodeList recordsNodes = elements.at(7).childNodes();
    for (int i = 0; i < recordsNodes.count(); i++) {
        //<addScore time="2024/03/21-21/16/31">50</addScore>
        QString dateAndTime;
        dateAndTime = recordsNodes.at(i).toElement().attribute("time");
        //qDebug() << dateAndTime;
        QDateTime recordTime;
        recordTime = QDateTime::fromString(dateAndTime,"yyyy/MM/dd-HH/mm/ss");
        unsigned int recordScore =recordsNodes.at(i).toElement().text().toUInt();
        records.push_back(QPair<QDateTime, unsigned int>(recordTime, recordScore));
    }
    //toXMLString();
}

bool Word::less(const Word &left, const Word &right)
{
    return left.getWord() < right.getWord();
}

bool Word::greater(const Word &left, const Word &right)
{
    return left.getWord() > right.getWord();
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
    for (const auto& word : words) {
        xmlString += word.toXMLString();
    }
    xmlString +="</lexicon>";
    return xmlString;
}

void WordList::fromXMLString(const QString &xmlString)
{
    QDomDocument xml;
    xml.setContent(xmlString);
    //<lexicon> element 里面有很多word
    auto wordDomList= xml.elementsByTagName("word");
    qDebug() << wordDomList.count();
    for (int i = 0; i < wordDomList.count(); i++) {
        Word newWord;
        newWord.formQDomElement(wordDomList.at(i).toElement());
        insert(newWord);
    }
}

void WordList::addWordScore(qsizetype index, unsigned int score)
{
    if (index >= words.count()) {
        qDebug() << "index out of range!";
        return;
    }
    words[words.keys()[index]].addScore(score);
    totalScore+=score;
}

void WordList::addWordScore(const Word &word, unsigned int score)
{   qDebug() << words.count();
    // 单词存在的时候，加分
    if(words.contains(word.getWord())){
        words[word.getWord()].addScore(score);
        totalScore+=score;
    } else {
        // 不存在这个单词
        // 添加这个单词并加分
        words.insert(word.getWord(), word);
        words[word.getWord()].addScore(score);
        wordNumber++;
        totalScore+=word.getScore();
    }
    qDebug() << words.count();
    qDebug() << "Word:" << word.getWord() << " adds " << score << ". Its current score is " << words[word.getWord()].getScore();
}

void WordList::insert(const Word &word)
{
    // 不存在才添加
    if(!words.contains(word.getWord())){
        words.insert(word.getWord(), word);
        // 更新统计数据
        wordNumber++;
        totalScore += word.getScore();
    }
}

double WordList::getAverageScore()
{
    qDebug() << "Current average score is: " << double(totalScore) / wordNumber;
    averageScore = double(totalScore) / wordNumber;
    return averageScore;
}

double WordList::getAverageScore() const
{
    qDebug() << "Current average score is: " << double(totalScore) / wordNumber;
    return double(totalScore) / wordNumber;
}

const Word WordList::operator[](qsizetype index) const
{
    return words.values()[index];
}

const Word WordList::getWord(const QString &word) const
{
    return words[word];
}

const Word WordList::getWord(const Word &word) const
{
    return words[word.getWord()];
}


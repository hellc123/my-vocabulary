#ifndef WORD_H
#define WORD_H
#include <QList>
#include <QDateTime>
#include <QString>
#include <QPair>
#include <QDomDocument>
class Word
{
public:
    Word(const QString & w = QString(),
         const QString & h = QString());

    // 设置单词
    void setWordInformation(const QString& w, bool cet4, bool cet6,
                 bool neep, unsigned int sc, const QString & rk);

    //只要word和html中的一个没有，就返回空
    bool isEmpty();


    void setOriginalWord(const QString& w);
    QString getOriginalWord() const;
    unsigned int getScore() const;
    void setScore(unsigned int newScore);
    bool IsCET4() const;
    void setCET4(bool newIsCET4);
    bool IsCET6() const;
    void setCET6(bool newIsCET6);
    bool IsNEEP() const;
    void setNEEP(bool newIsNEEP);
    QString getRank() const;
    void setRank(const QString & newRank);
    QString getHtml() const;
    void setHtml(const QString &newHtml);
    void setWord(const QString &newWord);
    QString getWord() const;

    // 增加分数，并保存学习记录
    void addScore(unsigned int score);
    // toXMLString 转化为XML格式
    QString toXMLString() const;
    // 从xml中读取单词信息
    void formXMLString(const QString& xmlDate);

private:
    QString word;
    QString html;
    // 单词的初始形态
    QString originalWord;
    // 分数 分数表示熟练程度
    unsigned int score = 0;
    // CET4单词
    bool CET4 = false;
    // CET6单词
    bool CET6 = false;
    // 考研单词
    bool NEEP = false;
    // 考研词频
    QString rank = 0;
    // 学习记录 加分记录
    QList<QPair<QDateTime,unsigned int>> records;
};

//using WordList = QList<Word>;
// 一个存有单词和单词学习记录的列表
class WordList : public QList<Word> {
public:
    // 转换为XML格式字符串
    QString toXMLString() const;
    // 从XML文件中读取
    void fromXMLString(const QString & xmlString);
};

#endif // WORD_H

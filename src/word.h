#ifndef WORD_H
#define WORD_H
#include <QList>
#include <QDateTime>
#include <QString>
#include <QPair>
#include <QDomDocument>
#include <algorithm>
#include <QHash>
#include <QMap>

// Word 是一个可以被hash的量
// 通过 word 判断是否是同一个量

class Word
{
public:
    // 默认构造函数
    explicit Word();
    explicit Word(const QString w);
    explicit Word(const QString w, const QString h);

    // 设置单词
    void setWordInformation(const QString& w, bool cet4, bool cet6,
                 bool neep, int sc, const QString & rk);

    //只要word和html中的一个没有，就返回空
    bool isEmpty() const;
    void setOriginalWord(const QString& w);
    QString getOriginalWord() const;
    int getScore() const;
    void setScore(int newScore);
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
    void addScore(int score);
    // 减少分数，并保存学习记录
    void subtractScore(int score);
    // toXMLString 转化为XML格式
    QString toXMLString() const;
    // 从xml中读取单词信息
    void formXMLString(const QString& xmlDate);
    // 从 QDomElement 获得单词信息
    void formQDomElement(const QDomElement &node);

    // 比较函数
    static bool less(const Word& left, const Word& right);
    static bool greater(const Word& left, const Word& right);
    bool operator==(const Word &other) const {
        return word == other.word;
    }
    bool operator<(const Word& other) const {
        return word < other.word;
    }
    bool operator>(const Word& other) const {
        return word > other.word;
    }
//    // Hash 函数，用于散列 Student 对象
//    inline uint qHash(const Word &key, uint seed = 0) {
//        return qHash(key.word,seed);
//    }
private:
    QString word;
    QString html;
    // 单词的初始形态
    QString originalWord;
    // 分数 分数表示熟练程度
    // 分数改为int类型，允许负数
    int score = 0;
    // CET4单词
    bool CET4 = false;
    // CET6单词
    bool CET6 = false;
    // 考研单词
    bool NEEP = false;
    // 考研词频
    QString rank = 0;
    // 学习记录 加分记录
    QList<QPair<QDateTime, int>> records;
};

//using WordList = QList<Word>;

// 一个存有单词和单词学习记录的列表
// 单词存在 QMap<QString,Word> 里面
class WordList{
public:
    // 转换为XML格式字符串
    QString toXMLString() const;
    // 从XML文件中读取
    void fromXMLString(const QString & xmlString);

private:
    // 总单词数量
    int wordNumber;
    // 所有单词的总分
    int totalScore;
    // 所有单词的平均分
    double averageScore;
public:
    // 重载QList 的操作
    void addWordScore(qsizetype index, int score);
    // 寻找单词word，如果存在则为这个单词加分score，不存在则先添加这个单词word，然后再加分
    void addWordScore(const Word& word, int score);
    // 寻找单词word，如果存在则为这个单词减去score，不存在就不做任何事情
    void subtractScore(const Word& word, int score);

    // 重写push_back 使之能够统计单词数量和总分
    //void push_back(const Word& word);
    void insert(const Word& word);
    qsizetype size() const noexcept { return wordNumber; }
    qsizetype count() const noexcept { return size(); }
    qsizetype length() const noexcept { return size(); }

    double getAverageScore();
    double getAverageScore() const;

    // 应该定义为const，因为会导致直接就不能修改protexted成员，导致总分无法统计
    const Word operator[](qsizetype index) const;

    // 获得Word
    const Word getWord(const QString &word) const;
    const Word getWord(const Word &word) const;

private:
    // 保存words
    QMap<QString, Word> words;
};

#endif // WORD_H

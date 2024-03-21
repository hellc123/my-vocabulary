#ifndef VACABULARYTEST_H
#define VACABULARYTEST_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QEvent>
#include <QFile>
#include <QSharedPointer>
#include <QDOMDocument>
#include "word.h"
// 学习记录的路径
#define _MY_VOCAVULARY_XML_ "E:\\BaiduNetdiskWorkspace\\project\\my-vocabulary\\profile\\myVocabulary.xml"

// 这是一个用于测试自己会那些单词的小组件

// 读取 四六级和考研词库数据
// 数据在 qrc:/../res/vocabulary.xml

// 将自己学习记录保存在
// E:\BaiduNetdiskWorkspace\project\my-vocabulary\profile\myVocabulary.xml 中
// 学习记录 保存在 <vocabulary> 标签下
    //<word>
        //<name>单词</name>
        //<score>当前这个单词的得分</score>
        //<records>
            //<addScore time="系统时间UTC8 yyyy/mm/dd/hh/mm/ss 24小时制">10</addScore>
        //</records>
    //</word>

class VocabularyTest : public QWidget
{
    Q_OBJECT
public:
    explicit VocabularyTest(QWidget *parent = nullptr);
    ~VocabularyTest();
private:
    QString word;
    // 一个显示单词的标签
    // 三个表示熟悉程度的按钮
    QLabel *wordLabel;
    // 单词的标签
    QLabel *wordTag;
    // 加50分
    QPushButton *familiarButton;
    // 加10分
    QPushButton *vagueButton;
    // 0分
    QPushButton *unknowButton;
    // 布局
    // 上下布局
    QGridLayout* vocabularyAreaLayout;

    // 写入xml学习记录文件
    QString vocabularyRecord=_MY_VOCAVULARY_XML_;

    void familiarButtonPushed(bool clicked = true);
    void vagueButtonPushed(bool clicked = true);
    void unknowButtonPushed(bool clicked = true);

    // 读取词库,将所有单词保存为wordList
    void loadWords();


    // 单词列表
    WordList wordList;
    // 当前的单词位置
    unsigned int wordIndex;
    // 显示下一个单词 如果index是0，则显示第一个单词，然后index++
    void nextWord();
    void showWord(unsigned int index);

    // 开始写入学习记录
    void beginWrite();
    // 写入当前单词
    void wordWrite();
    // 结束时，写入 </lexicon>
    void finishWrite();


signals:

protected:
    void keyPressEvent(QKeyEvent *event) override;
    // 鼠标向下滚动代表familiar 向上滚动代表unknow
    void wheelEvent(QWheelEvent *event) override;


};

#endif // VACABULARYTEST_H

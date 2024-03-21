#include "vocabularytest.h"
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMessageBox>
#include <QApplication>

VocabularyTest::VocabularyTest(QWidget *parent)
    : QWidget{parent}
{
    // ui 部分
    vocabularyAreaLayout = new QGridLayout();
    setLayout(vocabularyAreaLayout);
    wordLabel = new QLabel();
    wordLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    QFont biggerFont;
    biggerFont.setPointSize(20);
    wordTag = new QLabel();
    wordTag->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    wordLabel->setFont(biggerFont);
    familiarButton = new QPushButton("Familair\t+50");
    vagueButton = new QPushButton("Vague\t+10");
    unknowButton = new QPushButton("Unknow\t+0");
    vocabularyAreaLayout->addWidget(wordTag,0,1,1,1);
    vocabularyAreaLayout->addWidget(wordLabel,1,1,1,1);
    vocabularyAreaLayout->addWidget(familiarButton,3,1,1,1);
    vocabularyAreaLayout->addWidget(vagueButton,4,1,1,1);
    vocabularyAreaLayout->addWidget(unknowButton,5,1,1,1);
    resize(250,350);

    // 逻辑部分
    connect(familiarButton, &QPushButton::clicked, this, &VocabularyTest::familiarButtonPushed);
    connect(vagueButton, &QPushButton::clicked, this, &VocabularyTest::vagueButtonPushed);
    connect(unknowButton, &QPushButton::clicked, this, &VocabularyTest::unknowButtonPushed);

    // 读取词库的单词
    loadWords();

    // 显示第一个单词
    wordIndex = 0;
    showWord(wordIndex);

    // 开始记录
    beginWrite();
}

VocabularyTest::~VocabularyTest()
{
}

void VocabularyTest::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_J) {
        familiarButtonPushed();
    } else if(event->key() == Qt::Key_K) {
        vagueButtonPushed();
    } else if(event->key() == Qt::Key_L) {
        unknowButtonPushed();
    } else
        QWidget::keyPressEvent(event);
}

void VocabularyTest::wheelEvent(QWheelEvent *event)
{

//    qDebug() << event->angleDelta().x();
//    qDebug() << event->angleDelta().y();
    //滚轮上正 下负
    if(event->angleDelta().y() > 0) {
        unknowButtonPushed();
    } else if(event->angleDelta().y() < 0) {
        familiarButtonPushed();
    } else
        QWidget::wheelEvent(event);
}

void VocabularyTest::familiarButtonPushed(bool)
{
    qDebug() << "familiar";
    wordList[wordIndex].addScore(50);
    //qDebug() << wordList[wordIndex].toXMLString();
    wordWrite();
    nextWord();
}

void VocabularyTest::vagueButtonPushed(bool)
{
    qDebug() << "vague";
    wordList[wordIndex].addScore(10);
    //qDebug() << wordList[wordIndex].toXMLString();
    wordWrite();
    nextWord();
}

void VocabularyTest::unknowButtonPushed(bool)
{
    qDebug() << "unknow";
    wordList[wordIndex].addScore(0);
    //qDebug() << wordList[wordIndex].toXMLString();
    wordWrite();
    nextWord();
}

void VocabularyTest::loadWords()
{
/*
//      当完成一个单词信息的读取时，i == 5
//    unsigned i = 0;
//    QString tag;
//    while (!xmlRead->atEnd() && !xmlRead->hasError()) {
//        QXmlStreamReader::TokenType token = xmlRead->readNext();
//        if (token == QXmlStreamReader::StartDocument)
//            continue;
//        if (token == QXmlStreamReader::StartElement) {
//            if(xmlRead->name().toString()=="name") {
//                xmlRead->readNext();
//                word = xmlRead->text().toString();
//                i++;
//            }
//            if(xmlRead->name().toString()=="CET4") {
//                xmlRead->readNext();
//                tag = tag + xmlRead->text().toString()+" ";
//                i++;
//            }
//            if(xmlRead->name().toString()=="CET6") {
//                xmlRead->readNext();
//                tag = tag + xmlRead->text().toString()+" ";
//                i++;
//            }
//            if(xmlRead->name().toString()=="NEEP") {
//                xmlRead->readNext();
//                tag = tag + xmlRead->text().toString()+" ";
//                i++;
//            }
//            if(xmlRead->name().toString()=="rank") {
//                xmlRead->readNext();
//                tag = tag + xmlRead->text().toString()+" ";
//                i++;
//            }
//            if(i == 5)
//                break;
//        }
//    }
*/
    // 读取所有词库，并转换为wordLists
    QFile vocabularyFile(":/rsc/vocabulary.xml");
    if (!vocabularyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open XML file." << vocabularyFile.errorString();
        //qt_assert("Failed to open XML file.","vocaularytest.cpp",129);
        return;
    }
    // 设置文件内容到 QDomDocument
    QDomDocument xmlDocument;
    if (!xmlDocument.setContent(&vocabularyFile)) {
        vocabularyFile.close();
        qDebug() << "Failed to set content of XML document.";
        return;
    }
    vocabularyFile.close();

    // <lexicon><word><name>a</name><CET4>CET4</CET4><CET6></CET6><NEEP>NEEP</NEEP><rank>3</rank></word></lexicon>

    // 获取 XML 根元素
    QDomElement root = xmlDocument.documentElement();
    // 打印根元素名称
    qDebug() << "Root element:" << root.tagName();
    // 遍历子元素
    QDomNodeList children = root.childNodes();
    for (int i = 0; i < children.count(); ++i) {
        QDomNode node = children.at(i);
        // 获取 word 里面的值
        QDomNodeList wordNode = node.childNodes();
        Word newWord;
        // name
        newWord.setWord(wordNode.at(0).toElement().text());
        // CET4
        newWord.setCET4(wordNode.at(1).toElement().text() == "CET4");
        // CET6
        newWord.setCET6(wordNode.at(2).toElement().text() == "CET6");
        // NEEP
        newWord.setNEEP(wordNode.at(3).toElement().text()=="NEEP");
        // rank
        newWord.setRank(wordNode.at(4).toElement().text());
        wordList.push_back(newWord);
    }
}

void VocabularyTest::nextWord()
{
    wordIndex++;
    if(wordIndex < wordList.count()) {
        showWord(wordIndex);
    } else
    {
        qDebug() << "finish test!";
        finishWrite();
        this->close();
    }

}

void VocabularyTest::showWord(unsigned int index)
{
    wordLabel->setText(wordList[index].getWord());
    QString tag;
    tag += wordList[index].IsCET4()?"CET4 ":" ";
    tag += wordList[index].IsCET6()?"CET6 ":" ";
    tag += wordList[index].IsNEEP()?"NEEP ":" ";
    tag += wordList[index].getRank();
    wordTag->setText(tag.simplified());
}

void VocabularyTest::beginWrite()
{
    QFile recordsFile(vocabularyRecord);
    if(recordsFile.exists()) {
        int returnCode = QMessageBox::information(this, "File existed!", "The file "+vocabularyRecord+" is existed, do you want to delete it?", QMessageBox::Yes, QMessageBox::No);
        if(returnCode == QMessageBox::No) {
            qDebug() << "Now quit!";
            close();
            setDisabled(true);
        }
    }
    if(!recordsFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Can not open file:" << vocabularyRecord;
    } else {
        recordsFile.write("<lexicon>");
        recordsFile.close();
    }
}

void VocabularyTest::wordWrite()
{
    QFile recordsFile(vocabularyRecord);
    if(!recordsFile.open(QFile::WriteOnly | QFile::Append |QFile::Text)) {
        qDebug() << "Can not open file:" << vocabularyRecord;
    } else {
        recordsFile.write(wordList[wordIndex].toXMLString().toUtf8());
        recordsFile.close();
    }
}

void VocabularyTest::finishWrite()
{
    QFile recordsFile(vocabularyRecord);
    if(!recordsFile.open(QFile::WriteOnly | QFile::Append |QFile::Text)) {
        qDebug() << "Can not open file:" << vocabularyRecord;
    } else {
        recordsFile.write("</lexicon>");
        recordsFile.close();
        close();
    }
}

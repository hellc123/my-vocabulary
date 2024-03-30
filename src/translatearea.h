#ifndef TRANSLATEAREA_H
#define TRANSLATEAREA_H

// 搜索栏和webview

#include <QWidget>
#include "webview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include "learningmodel.h"
#include <QMessageBox>
class TranslateArea : public QWidget
{
    Q_OBJECT
public:
    //explicit TranslateArea(QWidget *parent = nullptr);
    explicit TranslateArea(LearningModel &lm, QWidget *parent = nullptr);
    // 搜索单词word，并显示文章
    void loadWord(const QString & word);
private:
    // 学习模型
    LearningModel &learningModel;
    // 一个搜索栏和一个webview，
    QVBoxLayout * translateAreaLayout;
    // 搜索栏和 一个搜索按钮，一个Unfamiliar 按钮
    QWidget *translateLineArea;
    QLineEdit *translateLine;
    QPushButton * searchButton;
    QPushButton * unfamiliarButton;
    QHBoxLayout * translateLineLayout;
    // 文章显示区域
    WebView *view;
    // 网页检查器
    QWebEngineView *inspector;
    // 显示网页检查器
    void showInpector(bool);
    // 从translateLine获得内容并搜索
    void loadWordFormEdit();
    // 按下unfamiliar按钮
    void unfamiliarClicked(bool);

    // 关闭unfamiliar按钮
    void disableUnfamiliarButton();
    void enableUnfamiliarButton();

    // 当要进行搜索的时候，运行的函数
    void toSearch();
signals:
    void unfamiliarClick();
};

#endif // TRANSLATEAREA_H

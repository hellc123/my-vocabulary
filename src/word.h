#ifndef WORD_H
#define WORD_H

#include <QString>
class Word
{
public:
    Word(const QString & w = QString(),
         const QString & h = QString());
    QString word;
    QString html;
    bool isEmpty();
};

#endif // WORD_H

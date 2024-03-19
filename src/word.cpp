#include "word.h"
Word::Word(const QString &w, const QString &h) :
    word(w),
    html(h)
{

}

bool Word::isEmpty()
{
    // 只要word和html中的一个没有，就返回空
    return word.isEmpty() || html.isEmpty();
}

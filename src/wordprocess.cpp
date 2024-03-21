#include "wordprocess.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
WordProcess::WordProcess(const QString& path)
{
    QFile dict(path);
    if(dict.open(QFile::ReadOnly | QFile::Text)) {
        qDebug()<< "open" + path;
        QTextStream in(&dict);
        Word tem;
        QString line;
        while(!in.atEnd()){
            line = in.readLine();
            tem.setWord(line.trimmed());
            // html
            line = in.readLine();
            tem.setHtml(line.trimmed());
            // </> 舍弃
            line = in.readLine();
            words.push_back(tem);
            //qDebug() << tem.word;
        }
    } else {
        qDebug()<< "Can not open" + path;
    }
}

#include "myschemehandler.h"
#include <QByteArray>
#include <QWebEngineUrlRequestJob>
#include <QUrl>
#include <QFile>
#include <QDebug>
#include <QNetworkReply>
#include <QBuffer>

MySchemeHandler::MySchemeHandler(QObject *parent, ArticleMaker& articleMaker)
    : QWebEngineUrlSchemeHandler{parent},
      articleMaker(articleMaker)
{

}

void MySchemeHandler::requestStarted(QWebEngineUrlRequestJob *job)
{
    // 获取请求的url
    const QUrl url = job->requestUrl();
    qDebug() << url.toDisplayString();

    // path 会带一个 '/'
    // 要获得原始的url
    QString host = url.host(QUrl::DecodeReserved);
    QString fileType;
    QString filename = url.path();
    if(filename != "/") {
        filename = filename.mid(filename.lastIndexOf('/'));
        fileType = filename.split('.')[1];
    }

    QString fileAddressPrefix = R"(E:\BaiduNetdiskWorkspace\project\my-vocabulary\dict\)";
    //qDebug() << filename;
    // 打开文件之后，文件何时关闭呢？

    QByteArray *ba = new QByteArray;
    QBuffer *buffer = new QBuffer(ba);
    connect( job, &QObject::destroyed, buffer, [ = ]() {
      buffer->close();
      ba->clear();
      delete ba;
      buffer->deleteLater();
      //qDebug() << "ba 已经删除";
    } );

    if(url.scheme() == "entry") {
        if(fileType.isEmpty()) {
            qDebug() << host;
            articleMaker.searchWord(host);
            //qDebug()<< articleMaker.getHtml();
            ba->append(articleMaker.getHtml().toUtf8());
            buffer->open(QBuffer::ReadOnly);
            buffer->seek(0);
            job->reply(QByteArrayLiteral("text/html"), buffer);
            // 从数据库中获得html
        }
        qDebug() << filename;
        if(fileType == "css") {
            QFile *file = new QFile(fileAddressPrefix+filename);
            file->open(QFile::ReadOnly);
            ba->append(file->readAll());
            file->close();
            buffer->open(QBuffer::ReadOnly);
            buffer->seek(0);
            job->reply(QByteArrayLiteral("text/css"), buffer);
            delete file;
        }
        if(fileType == "js") {
            QFile *file = new QFile(fileAddressPrefix+filename);
            file->open(QFile::ReadOnly);
            ba->append(file->readAll());
            file->close();
            buffer->open(QBuffer::ReadOnly);
            buffer->seek(0);
            job->reply(QByteArrayLiteral("text/javascript"), buffer);
            delete file;
        }
        if (fileType == "svg"){
            QFile *file = new QFile(fileAddressPrefix+filename);
            file->open(QFile::ReadOnly);
            ba->append(file->readAll());
            file->close();
            buffer->open(QBuffer::ReadOnly);
            buffer->seek(0);
            job->reply(QByteArrayLiteral("image/svg+xml"), buffer);
            delete file;
        }
        if (fileType == "ttf"){
            qDebug() << filename;
            QFile *file = new QFile(fileAddressPrefix+"font/"+filename);
            qDebug() << fileAddressPrefix+filename;
            file->open(QFile::ReadOnly);
            ba->append(file->readAll());
            file->close();
            buffer->open(QBuffer::ReadOnly);
            buffer->seek(0);
            job->reply(QByteArrayLiteral("font/ttf"), buffer);
            delete file;
        }
        if (fileType == "png"){
            //qDebug() << "png";
            QFile *file = new QFile(fileAddressPrefix+"am\\"+filename);
            file->open(QFile::ReadOnly);
            ba->append(file->readAll());
            file->close();
            buffer->open(QBuffer::ReadOnly);
            buffer->seek(0);
            job->reply(QByteArrayLiteral("image/png"), buffer);
            delete file;
        }
        return;
    }
    if (url.scheme() == "sound"){
        //qDebug() << "mp3";
        QFile *file = new QFile(fileAddressPrefix+"sound\\"+host);
        qDebug() << fileAddressPrefix+"sound\\"+host;
        file->open(QFile::ReadOnly);
        ba->append(file->readAll());
        file->close();
        buffer->open(QBuffer::ReadOnly);
        buffer->seek(0);
        job->reply(QByteArrayLiteral("audio/mpeg"), buffer);
    }
}

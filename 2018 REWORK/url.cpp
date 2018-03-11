#include "url.hpp"

URL::URL(QObject *parent) : QObject(parent)
{

}

QString URL::get_request(QString i_strURL)
{

    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(i_strURL)));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString strHtml = response->readAll();
    delete response;
    return strHtml;
}

//QByteArray postData;
//postData.append("param1=string&");
//postData.append("param2=string");

QString URL::post_request(QString i_strURL,QByteArray i_baPostData )
{
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.post(QNetworkRequest(QUrl(i_strURL)),i_baPostData);
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString strHtml = response->readAll();
    delete response;
    return strHtml;
}

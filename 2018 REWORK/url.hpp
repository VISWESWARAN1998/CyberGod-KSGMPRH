#ifndef URL_H
#define URL_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>

class URL : public QObject
{
    Q_OBJECT
public:

    explicit URL(QObject *parent = nullptr);
    QString get_request(QString i_strURL);
    QString post_request(QString i_strURL,QByteArray i_baPostData);

signals:

public slots:
};

#endif // URL_H

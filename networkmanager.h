#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QVariant>
#include <QUrlQuery>
#include <QObject>
#include <QDebug>
#include <QUrl>

namespace NetMan {

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    QNetworkAccessManager *manager;
    void makeRequest(const QUrl &url);


public slots:
    void onFinished(QNetworkReply* reply);

signals:
    void responseReceived(const QByteArray& response);
    void errorOccurred(const QString& errorString);

private:
    QUrl url;
    QUrlQuery query;
    QNetworkRequest request;
    QNetworkReply *reply;

};

}

#endif //NETWORKMANAGER_H

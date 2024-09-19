#include "networkmanager.h"
#include <QObject>
#include <QDebug>

NetMan::NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished, this, &NetMan::NetworkManager::onFinished);
}

NetMan::NetworkManager::~NetworkManager() {

}

void NetMan::NetworkManager::makeRequest(const QUrl &url) {
    request.setUrl(url);
    manager->get(request);
}

void NetMan::NetworkManager::onFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

        if (statusCode.isValid() && statusCode.toInt() == 200) {
            QByteArray response = reply->readAll();
            emit responseReceived(response);
        } else {
            QString msg = "Error: StatusCode: " + QString::number(statusCode.toInt());
            qWarning() << msg;
            emit errorOccurred(msg);
        }
    } else {
        QString errorMsg = "Error: " + reply->errorString();
        qWarning() << errorMsg;
        emit errorOccurred(errorMsg);
    }
    reply->deleteLater();
}

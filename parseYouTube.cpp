#include "mainwindow.h"

void MainWindow::parseYouTube(const QJsonObject& jsonObj) {
    QJsonObject itemsObj, idObj, snippetObj, thumbObj;

    // define thumbnail parsing nested object (default, high, medium)
    auto parseThumbnails = [](const QJsonObject& thumbObj) {
        for (auto it = thumbObj.begin(); it != thumbObj.end(); ++it) {
            QString thumbKey = it.key();
            QJsonValue thumbValue = it.value();
            if (thumbKey == "default" && thumbValue.isObject()) {
                qDebug() << "=> Default: " << thumbValue.toObject().keys();
            } else if (thumbKey == "medium" && thumbValue.isObject()) {
                qDebug() << "=> Medium: " << thumbValue.toObject().keys();
            } else if (thumbKey == "high" && thumbValue.isObject()) {
                qDebug() << "=> High: " << thumbValue.toObject().keys();
            }
        }
    };
    // define lambda for parsing Object
    auto parseObject = [&](const QJsonObject& obj) {
        for (auto it = obj.begin(); it != obj.end(); ++it) {
            QString key = it.key();
            QJsonValue value = it.value();
            QString type;
            switch (value.type()) {
                case QJsonValue::Null:    type = "Null"; break;
                case QJsonValue::Bool:    type = "Bool"; break;
                case QJsonValue::Double:  type = "Double"; break;
                case QJsonValue::String:  type = "String"; break;
                case QJsonValue::Array:   type = "Array"; break;
                case QJsonValue::Object:  type = "Object"; break;
                case QJsonValue::Undefined: type = "Undefined"; break;
                default: type = "Unknown"; break;
            }
            if (key == "thumbnails" && value.isObject()) {
                thumbObj = value.toObject();
                parseThumbnails(thumbObj);
            }

            QString outText = QString("Key: %1 => %2 => Type: (%3)").arg(key).arg(value.toString()).arg(type);
            qDebug() << outText;
        }
    };
    auto parseItems = [&](const QJsonObject& obj) {
    for (auto it = obj.begin(); it != obj.end(); ++it) {
            QString key = it.key();
            QJsonValue value = it.value();
            if (key == "id" && value.isObject()) {
                idObj = value.toObject();
                parseObject(idObj);

            } else if (key == "snippet" && value.isObject()) {
                snippetObj = value.toObject();
                parseObject(snippetObj);
            }
        }
    };

    // Define lambda for parsing Array
    auto parseArray = [&](const QJsonArray& arr) {
        for (const QJsonValue &arrValue : arr) {
            if (arrValue.isObject()) {
                QJsonObject itemsObj = arrValue.toObject();
                qDebug() << "=> Parsing items Object <=";
                parseItems(itemsObj);
                BuildOutput(idObj, snippetObj, thumbObj);
            }
        }
    };


    // Begin code
    qDebug() << "=> Parsing jsonObj";
    parseObject(jsonObj);

    qDebug() << "=> Parsing items Array";
    if (jsonObj.contains("items")) {
        QJsonArray itemsArr = jsonObj.value("items").toArray();
        parseArray(itemsArr);
    } else {
        qDebug() << "items doesn't exist.";
    }


}

void MainWindow::BuildOutput(const QJsonObject& idObj, const QJsonObject& snippet, const QJsonObject& thumbObj) {
    QString channelId, channelTitle, description, videoTitle, videoId, videoLink, videoUrl, prettyDate;
    QDateTime published;

    channelId = snippet["channelId"].toString();
    channelTitle = snippet["channelTitle"].toString();
    description = snippet["description"].toString();
    videoTitle = snippet["title"].toString();
    published = QDateTime::fromString( snippet["publishedAt"].toString() , Qt::ISODate);
    prettyDate = published.toString("ddd MMM , dd yyyy hh:mm:ss ap");
    videoId = idObj["videoId"].toString();
    videoLink = QString("https://www.youtube.com/watch?v=%1").arg(videoId);
    msg = QString("Channel: %1 [%2]\nDescription: %3\nVideo Title: %4 [%5]\nPublished: %6\n")
            .arg(channelTitle).arg(channelId).arg(description).arg(videoTitle).arg(videoId).arg(prettyDate).arg(videoLink);

    UpdateOutput(msg);
    videoUrl = QString("Video Link: <a href=\"%7\">%7</a><br>").arg(videoLink);
    InsertLink(videoUrl);

}

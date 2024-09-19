#include "mainwindow.h"

void MainWindow::parseYouTube(const QJsonObject& jsonObj) {
    QString details;

    // define lambda for parsing Object
    auto parseObject = [](const QJsonObject& obj) {
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
            QString outText = QString("Key: %1 => %2 => Type: (%3)").arg(key).arg(value.toString()).arg(type);
            qDebug() << outText;
        }
    };

    // Define lambda for parsing Array
    auto parseArray = [&](const QJsonArray& arr) {
        for (const QJsonValue &arrValue : arr) {
            if (arrValue.isObject()) {
                QJsonObject itemsObj = arrValue.toObject();
                qDebug() << "=> Parsing items Object <=";
                parseObject(itemsObj);
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
/*
void MainWindow::parseArray(const QJsonArray& jsonArray) {
    QVector<Videos> videoArray;
    QJsonObject idObj, snippet, etag;

    for (const QJsonValue &arrValue : jsonArray) {

        if (arrValue.isObject()) {
            QJsonObject obj = arrValue.toObject();
            //QJsonDocument doc(obj);
            //qDebug() << "obj: " << doc.toJson(QJsonDocument::Indented);

            for (auto it = obj.begin(); it != obj.end(); ++it) {
                QString key = it.key();
                QJsonValue value = it.value();

                if (value.isObject()) {
                    msg = QString("Key: %1 => Object").arg(key);
                    qDebug() << msg;
                    if (key == "id") {
                        idObj = obj["id"].toObject();
                    } else if (key =="snippet") {
                        snippet = obj["snippet"].toObject();
                    } else if (key =="etag") {
                        etag = obj["etag"].toObject();
                    } else {
                        qDebug() << "Unknown Key in Object";
                    }
                }
            }
            ParseItems(snippet, idObj, videoArray);
        } else {
            qDebug() << "Array element is not an object.";
        }
    }

    msg = QString("Video Vector Size (%1)").arg(videoArray.size());
    UpdateOutput(msg);
}


void MainWindow::ParseItems(const QJsonObject& snippet, const QJsonObject& idObj, QVector<Videos>& videoArray) {
    QString Id, Title, desc, VideoTitle, videoId, videoLink, videoUrl, prettyDate;
    QDateTime published;

    Id = snippet["channelId"].toString();
    Title = snippet["channelTitle"].toString();
    desc = snippet["description"].toString();
    VideoTitle = snippet["title"].toString();
    published = QDateTime::fromString( snippet["publishedAt"].toString() , Qt::ISODate);
    prettyDate = published.toString("ddd MMM , dd yyyy hh:mm:ss ap");
    videoId = idObj["videoId"].toString();
    videoLink = QString("https://www.youtube.com/watch?v=%1").arg(videoId);
    msg = QString("Channel: %1 [%2]\nDescription: %3\nVideo Title: %4 [%5]\nPublished: %6\n")
            .arg(Title).arg(Id).arg(desc).arg(VideoTitle).arg(videoId).arg(prettyDate).arg(videoLink);

    UpdateOutput(msg);
    videoUrl = QString("Video Link: <a href=\"%7\">%7</a><br>").arg(videoLink);
    InsertLink(videoUrl);

    //save data to vector
    Videos v1;
    v1.channelId = Id;
    v1.channelTitle = Title;
    v1.Description = desc;
    v1.VideoId = videoId;
    v1.VideoTitle = VideoTitle;
    v1.Published = prettyDate;
    videoArray.append(v1);
}*/

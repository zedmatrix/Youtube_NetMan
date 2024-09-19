#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QObject>
#include "parseYouTube.cpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networkmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    netman(new NetMan::NetworkManager(this))
{
    //
    ui->setupUi(this);
    ui->urlOutput->setAcceptRichText(true);

    //
    connect(ui->quit, &QPushButton::clicked, this, &MainWindow::Quit);
    connect(netman, &NetMan::NetworkManager::responseReceived, this, &MainWindow::handleResponse);
    connect(netman, &NetMan::NetworkManager::errorOccurred, this, &MainWindow::handleError);
    connect(ui->urlInput, &QLineEdit::returnPressed, this, &MainWindow::handleURL);

    //

    QJsonDocument apiDoc = readAPIFile();
    if (!apiDoc.isNull()) {
        if (apiDoc.isObject()) {
            QJsonObject jsonObj = apiDoc.object();
            apiKey = jsonObj["apikey"].toString();
            apiUrl = QUrl(jsonObj["apiurl"].toString());
            msg = QString("url: %1 \nkey: %2").arg(apiUrl.toString()).arg(apiKey);
            UpdateStatus("API File Successful.");
        } else {
            UpdateStatus("Object Not Found.");
        }
    } else {
        UpdateStatus("Document is invalid.");
    }


}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::Quit() {
    qDebug() << "Quitting";
    qApp->quit();
}
void MainWindow::UpdateOutput(const QString &msg) {
    ui->urlOutput->append(msg);

}
void MainWindow::InsertLink(const QString &videoLink) {
    QTextCursor cursor(ui->urlOutput->document());
    cursor.movePosition(QTextCursor::End);
    cursor.insertHtml(videoLink);

    // QTextCharFormat linkFormat;
    // linkFormat.setAnchor(true);
    // linkFormat.setAnchorHref(videoLink);
    // linkFormat.setForeground(QBrush(Qt::blue));
    // linkFormat.setFontUnderline(true);

    //ui->urlOutput->setOpenExternalLinks(true); //not valid in qt6
}

void MainWindow::UpdateStatus(const QString &statusMsg) {
    // posssible to use currentMessage() ??
    ui->statusbar->showMessage(statusMsg);
}

QJsonDocument MainWindow::readAPIFile() {
    qDebug() << "apiFile: " << apiFile;
    QFile file(MainWindow::apiFile);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        UpdateStatus("Cannot Open API File.");
        return {};
    }

    QTextStream textStream(&file);
    QString fileContent = textStream.readAll();

    QByteArray jsonData = fileContent.toUtf8();
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        statusMsg = "JSON parse error:" + parseError.errorString();
        UpdateStatus(statusMsg);
        return {};
    }
    file.close();
    return jsonDoc;
}

void MainWindow::handleURL() {
    QString searchTerm = ui->urlInput->text().trimmed();

    QUrl url(apiUrl);
    QUrlQuery query;
    query.addQueryItem("part", "snippet");
    query.addQueryItem("q", searchTerm);
    query.addQueryItem("type", "channelId");
    query.addQueryItem("publishedAfter", "2024-09-17T00:00:00Z");
    query.addQueryItem("maxResults", "15");
    query.addQueryItem("key", apiKey);

    url.setQuery(query);

    if (url.isValid() && !url.host().isEmpty()) {
        statusMsg = "Valid URL:" + url.toString();
        UpdateStatus(statusMsg);
        netman->makeRequest(url);

    } else {
        UpdateStatus("Invalid URL");
    }
}
/*
    Network Manager block which could be moved to a separate cpp

*/
void MainWindow::handleResponse(const QByteArray& response) {
    QString responseText = QString::fromUtf8(response);

    QRegularExpression htmlTagPattern("<[^>]*>");
    responseText.remove(htmlTagPattern);

    responseText = responseText.trimmed();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseText.toUtf8());

    if (!jsonResponse.isNull() && jsonResponse.isObject()) {
        QJsonObject jsonObject = jsonResponse.object();
        QStringList keys = jsonObject.keys();
        QString keysString = keys.join(", ");
        UpdateOutput(keysString);
        parseYouTube(jsonObject);

    } else {
        UpdateOutput("No valid JSON object found.");
    }

    //qDebug() << "Response:" << responseText;

    UpdateStatus("Data received successfully!");
}

void MainWindow::handleError(const QString& errorString) {
        qWarning() << "Error:" << errorString;

        UpdateStatus(errorString);
}

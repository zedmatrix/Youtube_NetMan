#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QDateTime>
#include <QFile>
#include <QStatusBar>
#include <QTextEdit>
#include <QTextCursor>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
namespace NetMan { class NetworkManager; }
QT_END_NAMESPACE

// Create New Snippet to write out
struct Videos {
    QString channelId;
    QString channelTitle;
    QString Description;
    QString VideoId;
    QString VideoTitle;
    QString Published;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QString apiFile;

private slots:
    QJsonDocument readAPIFile();
    void parseYouTube(const QJsonObject& jsonObj);
    //void parseArray(const QJsonArray& jsonArray);
    //void ParseItems(const QJsonObject& snippet, const QJsonObject& idObj, QVector<Videos>& videoArray);
    void InsertLink(const QString &videoLink);
    void handleResponse(const QByteArray& response);
    void handleError(const QString& errorString);
    void handleURL();
    void UpdateStatus(const QString &statusMsg);
    void UpdateOutput(const QString &msg);
    void Quit();


private:
    Ui::MainWindow *ui;
    NetMan::NetworkManager *netman;
    QString apiKey, statusMsg, msg;
    QUrl apiUrl;


};




#endif // MAINWINDOW_H

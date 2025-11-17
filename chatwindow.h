#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ChatWindow(const QString &username, QWidget *parent = nullptr);
    ~ChatWindow();

private slots:
    void on_addFriendButton_clicked();
    void on_sendMessageButton_clicked();

private:
    Ui::ChatWindow *ui;
    QString username;
    QVector<QString> friends;
    QNetworkAccessManager *networkManager;
};

#endif // CHATWINDOW_H

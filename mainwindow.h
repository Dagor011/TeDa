#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "user.h"
#include <QTcpSocket> // QSslSocket

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    static bool checkIfUserExistsInDB(const QString &username);

private slots:
    void on_registerButton_clicked();
    void on_loginButton_clicked();
    void on_logoutButton_clicked();


    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    User currentUser;
    QPushButton *registerButton;
    QPushButton *loginButton;
    QPushButton *logoutButton;
    QVBoxLayout *buttonLayout;


    QTcpSocket *socket;
};

#endif // MAINWINDOW_H

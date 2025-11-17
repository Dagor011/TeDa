#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QTcpSocket>
#include "inputdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    buttonLayout = ui->buttonLayout;


    registerButton = new QPushButton("Register", this);
    loginButton = new QPushButton("Login", this);
    logoutButton = new QPushButton("Logout", this);


    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(logoutButton);


    connect(registerButton, &QPushButton::clicked, this, &MainWindow::on_registerButton_clicked);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
    connect(logoutButton, &QPushButton::clicked, this, &MainWindow::on_logoutButton_clicked);

    // Подключение к базе данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/DataBases/TeDa.db");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
        qDebug() << db.lastError().text();
    } else {
        qDebug() << "Database: connection ok";
    }

    // socket
    socket = new QTcpSocket(this);


    connect(socket, &QTcpSocket::connected, this, &MainWindow::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
    delete socket;
}

void MainWindow::on_registerButton_clicked()
{
    InputDialog dialog("Registration", this);
    if (dialog.exec() == QDialog::Accepted) {
        QString username = dialog.getUsername();
        QString password = dialog.getPassword();
        QString email = dialog.getEmail();


        User newUser(username.toStdString(), password.toStdString(), email.toStdString());

        QSqlQuery query;
        query.prepare("INSERT INTO users (username, password, email) VALUES (:username, :password, :email)");
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        query.bindValue(":email", email);

        if (!query.exec()) {
            qDebug() << "Error: " << query.lastError().text();
        } else {
            qDebug() << "User registered successfully";
        }
    }
}

void MainWindow::on_loginButton_clicked()
{
    InputDialog dialog("Login", this);
    if (dialog.exec() == QDialog::Accepted) {
        QString username = dialog.getUsername();
        QString password = dialog.getPassword();

        qDebug() << "Username:" << username;
        qDebug() << "Password:" << password;


        socket->connectToHost("localhost", 12345);

        // Отправляем команду LOGIN
        QString loginMessage = "LOGIN|" + username + "|" + password;
        socket->write(loginMessage.toUtf8());


        if (socket->waitForReadyRead()) {
            QByteArray data = socket->readAll();
            QString response = QString::fromUtf8(data);

            if (response == "OK") {
                qDebug() << "Login successful";


                while (buttonLayout->count() > 0) {
                    auto item = buttonLayout->takeAt(0);
                    delete item->widget();
                    delete item;
                }

                // Обновление времени последнего входа
                currentUser.setLastLogin(std::chrono::system_clock::now());
            } else {
                qDebug() << "Login failed";
            }
        } else {
            qDebug() << "Failed to connect to server";
        }
    }
}

void MainWindow::on_logoutButton_clicked()
{
    //
}

//check usert
bool MainWindow::checkIfUserExistsInDB(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Error checking user existence in DB:" << query.lastError().text();
        return false;
    }

    if (query.first()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

// Обработчики сигналов QTcpSocket
void MainWindow::onConnected()
{
    qInfo() << "Connected to server";
}

void MainWindow::onDisconnected()
{
    qInfo() << "Disconnected from server";
}

void MainWindow::onReadyRead()
{
    QByteArray data = socket->readAll();
    QString msg = QString::fromUtf8(data);

    // Обработка полученных сообщений
    if (msg.startsWith("MESSAGE")) {
        QStringList parts = msg.split("|");
        if (parts.size() >= 2) {
            QString message = parts.at(1);
            qInfo() << "Received message: " << message;
        }
    }
}

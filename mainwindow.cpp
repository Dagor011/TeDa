#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Получение макета из ui файла
    buttonLayout = ui->buttonLayout;

    // Создание кнопок
    registerButton = new QPushButton("Register", this);
    loginButton = new QPushButton("Login", this);
    logoutButton = new QPushButton("Logout", this);

    // Добавление кнопок в макет
    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(logoutButton);

    // Подключение сигналов к слотам
    connect(registerButton, &QPushButton::clicked, this, &MainWindow::on_registerButton_clicked);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
    connect(logoutButton, &QPushButton::clicked, this, &MainWindow::on_logoutButton_clicked);

    //База данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/DataBases/TeDa.db");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
        qDebug() << db.lastError().text();
    } else {
        qDebug() << "Database: connection ok";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::on_registerButton_clicked()
{
    InputDialog dialog("Registration", this);
    if (dialog.exec() == QDialog::Accepted) {
        QString username = dialog.getUsername();
        QString password = dialog.getPassword();
        QString email = dialog.getEmail();

        // Создание нового пользователя
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
//верификация
void MainWindow::on_loginButton_clicked()
{
    InputDialog dialog("Login", this);
    if (dialog.exec() == QDialog::Accepted) {
        QString username = dialog.getUsername();
        QString password = dialog.getPassword();

        QSqlQuery query;
        query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if (!query.exec()) {
            qDebug() << "Error: " << query.lastError().text();
        } else {
            if (query.next()) {
                qDebug() << "Login successful";
                // Обновление времени последнего входа
                currentUser.setLastLogin(std::chrono::system_clock::now());
            } else {
                qDebug() << "Login failed";
            }
        }
    }
}

void MainWindow::on_logoutButton_clicked()
{

}

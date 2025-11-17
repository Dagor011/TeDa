#include "inputdialog.h"

InputDialog::InputDialog(const QString& title, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(title);

    // интерфейс
    labelUsername = new QLabel("Username:", this);
    labelPassword = new QLabel("Password:", this);
    labelEmail = new QLabel("Email:", this);
    lineEditUsername = new QLineEdit(this);
    lineEditPassword = new QLineEdit(this);
    lineEditPassword->setEchoMode(QLineEdit::Password);
    lineEditEmail = new QLineEdit(this);
    buttonSubmit = new QPushButton("Submit", this);

    // Создание макетов
    QHBoxLayout* layoutUsername = new QHBoxLayout();
    layoutUsername->addWidget(labelUsername);
    layoutUsername->addWidget(lineEditUsername);

    QHBoxLayout* layoutPassword = new QHBoxLayout();
    layoutPassword->addWidget(labelPassword);
    layoutPassword->addWidget(lineEditPassword);

    QHBoxLayout* layoutEmail = new QHBoxLayout();
    layoutEmail->addWidget(labelEmail);
    layoutEmail->addWidget(lineEditEmail);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(layoutUsername);
    mainLayout->addLayout(layoutPassword);
    mainLayout->addLayout(layoutEmail);
    mainLayout->addWidget(buttonSubmit);


    connect(buttonSubmit, &QPushButton::clicked, this, &InputDialog::accept);
}

QString InputDialog::getUsername() const {
    return lineEditUsername->text();
}

QString InputDialog::getPassword() const {
    return lineEditPassword->text();
}

QString InputDialog::getEmail() const {
    return lineEditEmail->text();
}

void InputDialog::accept() {

    if (lineEditUsername->text().isEmpty() || lineEditPassword->text().isEmpty() || lineEditEmail->text().isEmpty()) {
        //QMessageBox::warning(this, "Error", "Username, password, and email cannot be empty");
        return;
    }


    QDialog::accept();
}

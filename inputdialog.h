#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class InputDialog : public QDialog {
    Q_OBJECT

public:
    explicit InputDialog(const QString& title, QWidget* parent = nullptr);
    QString getUsername() const;
    QString getPassword() const;
    QString getEmail() const;

private:
    QLabel* labelUsername;
    QLabel* labelPassword;
    QLabel* labelEmail;
    QLineEdit* lineEditUsername;
    QLineEdit* lineEditPassword;
    QLineEdit* lineEditEmail;
    QPushButton* buttonSubmit;

private slots:
    void accept(); // Явно объявляем реализацию слота accept
};

#endif

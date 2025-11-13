#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>

class RegistrationButton : public QPushButton {
    Q_OBJECT

public:
    RegistrationButton(QWidget *parent = nullptr);
};

class LoginButton : public QPushButton {
    Q_OBJECT

public:
    LoginButton(QWidget *parent = nullptr);
};



#endif // BUTTONS_H

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    void handleLogin();

private:
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *loginBtn;
};

#endif

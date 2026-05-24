#include "loginwindow.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *title = new QLabel("EcoRide");
    title->setStyleSheet("font-size: 28px; font-weight: bold; color: #2e7d32;");
    layout->addWidget(title, 0, Qt::AlignCenter);

    QLabel *userLabel = new QLabel("Username:");
    userLabel->setStyleSheet("color: #1b5e20; font-weight: bold;");
    usernameInput = new QLineEdit;
    usernameInput->setStyleSheet("background-color: white; border: 1px solid #2e7d32; color: black;");

    QLabel *passLabel = new QLabel("Password:");
    passLabel->setStyleSheet("color: #1b5e20; font-weight: bold;");
    passwordInput = new QLineEdit;
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setStyleSheet("background-color: white; border: 1px solid #2e7d32; color: black;");

    loginBtn = new QPushButton("Login");
    loginBtn->setStyleSheet("background-color: #2e7d32; color: white; font-weight: bold; padding: 6px;");

    layout->addWidget(userLabel);
    layout->addWidget(usernameInput);
    layout->addWidget(passLabel);
    layout->addWidget(passwordInput);
    layout->addWidget(loginBtn);

    setLayout(layout);
    resize(300, 200);

    setStyleSheet("background-color: #e8f5e9; font-family: Arial;");

    connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::handleLogin);
}

void LoginWindow::handleLogin()
{
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registered");
        msgBox.setText("New account created. Please login again.");
        msgBox.setStyleSheet("QLabel{ color: black; }");  // text color fix
        msgBox.exec();

        return;
    }

    bool found = false;

    QFile file("users.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 2) {
                if (parts[0] == username && parts[1] == password) {
                    found = true;
                    break;
                }
            }
        }
        file.close();
    }

    if (found) {
        MainWindow *mw = new MainWindow(username, false);
        mw->show();
        this->close();
    } else {

        QFile fileOut("users.txt");
        if (fileOut.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&fileOut);
            out << username << "," << password << "\n";
            fileOut.close();
        }
        QMessageBox msgBox;
        msgBox.setWindowTitle("Registered");
        msgBox.setText("New account created. Please login again.");
        msgBox.setIcon(QMessageBox::Information);

        msgBox.setStyleSheet(
            "QMessageBox { background-color: white; } "
            "QLabel { color: black; } "
            "QPushButton { background-color: white; color: black; font-weight: bold; }"
            );

        msgBox.exec();

    }
}

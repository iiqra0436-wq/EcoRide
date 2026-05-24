#include "mainwindow.h"
#include "driverdashboard.h"
#include "riderdashboard.h"
#include "loginwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QToolButton>

MainWindow::MainWindow(QString username, bool isDriver, QWidget *parent)
    : QWidget(parent), username(username), isDriver(isDriver)
{
    QVBoxLayout *layout = new QVBoxLayout;


    QToolButton *backArrow = new QToolButton;
    backArrow->setArrowType(Qt::LeftArrow);
    backArrow->setStyleSheet("color: #2e7d32; font-weight: bold;");
    layout->addWidget(backArrow, 0, Qt::AlignLeft);

    QLabel *label = new QLabel("Welcome " + username + "! Choose your mode:");
    label->setStyleSheet("font-size: 20px; font-weight: bold; color: #2e7d32;");
    layout->addWidget(label, 0, Qt::AlignCenter);

    QPushButton *driverBtn = new QPushButton("Driver Mode");
    driverBtn->setStyleSheet("background-color: #2e7d32; color: white; font-weight: bold; padding: 8px;");

    QPushButton *riderBtn = new QPushButton("Rider Mode");
    riderBtn->setStyleSheet("background-color: #2e7d32; color: white; font-weight: bold; padding: 8px;");

    layout->addWidget(driverBtn);
    layout->addWidget(riderBtn);

    setLayout(layout);
    resize(400, 300);


    setStyleSheet("background-color: #e8f5e9; font-family: Arial;");

    connect(driverBtn, &QPushButton::clicked, this, [=]() {
        DriverDashboard *dd = new DriverDashboard(username);
        dd->show();
        this->close();
    });

    connect(riderBtn, &QPushButton::clicked, this, [=]() {
        RiderDashboard *rd = new RiderDashboard(username);
        rd->show();
        this->close();
    });


    connect(backArrow, &QToolButton::clicked, this, [=]() {
        LoginWindow *login = new LoginWindow;
        login->show();
        this->close();
    });
}

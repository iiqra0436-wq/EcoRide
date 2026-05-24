#include "riderdashboard.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QToolButton>
#include <QLineEdit>
#include <QDebug>

RiderDashboard::RiderDashboard(QString username, QWidget *parent)
    : QWidget(parent), username(username)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(6);
    layout->setContentsMargins(15, 10, 15, 10);

    QLabel *label = new QLabel("Rider Dashboard - Welcome " + username);
    label->setStyleSheet("font-size: 16px; font-weight: bold; color: #2e7d32;");

    QToolButton *backArrow = new QToolButton;
    backArrow->setArrowType(Qt::LeftArrow);
    backArrow->setStyleSheet("color: #2e7d32;");
    layout->addWidget(backArrow, 0, Qt::AlignLeft);

    rideList = new QListWidget;
    rideList->setStyleSheet("background-color: white; border: 1px solid #2e7d32; color: black;");
    layout->addWidget(rideList);

    QPushButton *acceptBtn = new QPushButton("Accept Ride");
    acceptBtn->setStyleSheet("background-color: #2e7d32; color: white; padding: 6px; font-size: 14px;");

    counterFareInput = new QLineEdit;
    counterFareInput->setPlaceholderText("Propose your fare");
    counterFareInput->setStyleSheet("background-color: white; border: 1px solid #2e7d32; padding: 4px; font-size: 13px;");

    QPushButton *proposeBtn = new QPushButton("Propose Fare");
    proposeBtn->setStyleSheet("background-color: #2e7d32; color: white; padding: 6px; font-size: 14px;");

    QPushButton *viewMyAcceptedBtn = new QPushButton("View My Accepted Rides");
    viewMyAcceptedBtn->setStyleSheet("background-color: #2e7d32; color: white; padding: 6px; font-size: 14px;");

    QPushButton *cancelBtn = new QPushButton("Cancel Ride");
    cancelBtn->setStyleSheet("background-color: #c62828; color: white; padding: 6px; font-size: 14px;");

    layout->addWidget(acceptBtn);
    layout->addWidget(counterFareInput);
    layout->addWidget(proposeBtn);
    layout->addWidget(viewMyAcceptedBtn);
    layout->addWidget(cancelBtn);

    setLayout(layout);
    resize(500, 450);
    setStyleSheet("background-color: #e8f5e9; font-family: Arial;");

    loadRides();

    connect(acceptBtn, &QPushButton::clicked, this, [=]() {
        QListWidgetItem *item = rideList->currentItem();
        if (!item) {
            QMessageBox::warning(this, "No Selection", "Please select a ride first.");
            return;
        }
        QString selectedRide = item->text();
        QString driverName = selectedRide.section('|', 0, 0).remove("Driver: ").trimmed();
        QFile file("rides.txt");
        QStringList lines;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(",");
                if (parts.size() >= 5 && parts[0] == driverName && parts[4] == "Pending") {
                    parts[4] = "Accepted";
                    if (parts.size() == 5) {
                        parts << username;
                    } else {
                        parts[5] = username;
                    }
                    line = parts.join(",");
                }
                lines << line;
            }
            file.close();
        }
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (const QString &line : lines)
                out << line << "\n";
            file.close();
        }
        QMessageBox::information(this, "Ride Accepted", "Driver is coming!\n" + item->text());
        rideList->clear();
        loadRides();
    });

    connect(proposeBtn, &QPushButton::clicked, this, [=]() {
        QListWidgetItem *item = rideList->currentItem();
        if (!item) {
            QMessageBox::warning(this, "No Selection", "Please select a ride first.");
            return;
        }
        QString counterFare = counterFareInput->text();
        if (counterFare.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter a counter fare.");
            return;
        }
        QFile file("proposals.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << username << "," << counterFare << "," << item->text() << "\n";
            file.close();
        }
        QMessageBox::information(this, "Proposal Sent", "Your fare proposal has been sent to the driver.");
        counterFareInput->clear();
    });

    connect(viewMyAcceptedBtn, &QPushButton::clicked, this, [=]() {
        QFile file("rides.txt");
        QStringList accepted;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(",");
                if (parts.size() >= 6 && parts[4] == "Accepted" && parts[5] == username) {
                    accepted << "Driver: " + parts[0] + " | From: " + parts[1] + " → " + parts[2] + " | Fare: " + parts[3];
                }
            }
            file.close();
        }
        QMessageBox::information(this, "My Accepted Rides", accepted.isEmpty() ? "You have not accepted any rides yet." : accepted.join("\n"));
    });

    connect(cancelBtn, &QPushButton::clicked, this, [=]() {
        QFile file("rides.txt");
        QStringList lines;
        bool cancelled = false;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(",");
                if (parts.size() >= 6 && parts[4] == "Accepted" && parts[5] == username) {
                    parts[4] = "Cancelled";
                    line = parts.join(",");
                    cancelled = true;
                }
                lines << line;
            }
            file.close();
        }
        if (cancelled) {
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                for (const QString &line : lines)
                    out << line << "\n";
                file.close();
            }
            QMessageBox::information(this, "Ride Cancelled", "Your ride has been cancelled.");
        } else {
            QMessageBox::information(this, "No Ride", "You have no accepted rides to cancel.");
        }
        rideList->clear();
        loadRides();
    });

    connect(backArrow, &QToolButton::clicked, this, [=]() {
        MainWindow *mw = new MainWindow(username, false);
        mw->show();
        this->close();
    });
}

void RiderDashboard::loadRides()
{
    rideList->clear();
    QFile file("rides.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() >= 4) {
                QString driver = parts[0];
                QString origin = parts[1];
                QString destination = parts[2];
                QString fare = parts[3];
                QString status = (parts.size() >= 5 ? parts[4] : "Pending");
                if (status == "Pending") {
                    rideList->addItem("Driver: " + driver + " | From: " + origin + " → " + destination + " | Fare: " + fare);
                }
            }
        }
        file.close();
    }
}

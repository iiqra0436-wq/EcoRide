#include "driverdashboard.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QToolButton>
#include <QInputDialog>
#include <QDebug>

DriverDashboard::DriverDashboard(QString username, QWidget *parent)
    : QWidget(parent), username(username)
{
    QVBoxLayout *layout = new QVBoxLayout;

    QHBoxLayout *headerLayout = new QHBoxLayout;
    QToolButton *backArrow = new QToolButton;
    backArrow->setArrowType(Qt::LeftArrow);
    backArrow->setStyleSheet("color: #2e7d32;");

    QLabel *label = new QLabel("Driver Dashboard - Welcome " + username);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 18px; font-weight: bold; color: #2e7d32;");

    headerLayout->addWidget(backArrow, 0, Qt::AlignLeft);
    headerLayout->addWidget(label, 1);

    layout->addLayout(headerLayout);

    originInput = new QLineEdit;
    originInput->setPlaceholderText("Enter origin");
    originInput->setStyleSheet("background-color: white; border: 1px solid #2e7d32; padding: 6px;");

    destinationInput = new QLineEdit;
    destinationInput->setPlaceholderText("Enter destination");
    destinationInput->setStyleSheet("background-color: white; border: 1px solid #2e7d32; padding: 6px;");

    fareInput = new QLineEdit;
    fareInput->setPlaceholderText("Enter fare");
    fareInput->setStyleSheet("background-color: white; border: 1px solid #2e7d32; padding: 6px;");

    QPushButton *postBtn = new QPushButton("Post Ride");
    postBtn->setStyleSheet("background-color: #2e7d32; color: white; padding: 8px; font-size: 14px;");

    QPushButton *viewAcceptedBtn = new QPushButton("View Accepted Rides");
    viewAcceptedBtn->setStyleSheet("background-color: #2e7d32; color: white; padding: 8px; font-size: 14px;");

    QPushButton *viewProposalsBtn = new QPushButton("View Fare Proposals");
    viewProposalsBtn->setStyleSheet("background-color: #2e7d32; color: white; padding: 8px; font-size: 14px;");

    QPushButton *cancelBtn = new QPushButton("Cancel Ride");
    cancelBtn->setStyleSheet("background-color: #c62828; color: white; padding: 8px; font-size: 14px;");

    layout->addWidget(originInput);
    layout->addWidget(destinationInput);
    layout->addWidget(fareInput);
    layout->addWidget(postBtn);
    layout->addWidget(viewAcceptedBtn);
    layout->addWidget(viewProposalsBtn);
    layout->addWidget(cancelBtn);

    setLayout(layout);
    resize(500, 450);
    setStyleSheet("background-color: #e8f5e9; font-family: Arial;");

    connect(postBtn, &QPushButton::clicked, this, [=]() {
        if (originInput->text().isEmpty() || destinationInput->text().isEmpty() || fareInput->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill in all fields.");
            return;
        }
        QFile file("rides.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << username << "," << originInput->text() << "," << destinationInput->text() << "," << fareInput->text() << ",Pending\n";
            file.close();
        }
        QMessageBox::information(this, "Ride Posted", "Your ride has been posted successfully!");
        originInput->clear();
        destinationInput->clear();
        fareInput->clear();
    });

    connect(viewAcceptedBtn, &QPushButton::clicked, this, [=]() {
        QFile file("rides.txt");
        QStringList accepted;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(",");
                if (parts.size() >= 6 && parts[0] == username && parts[4] == "Accepted") {
                    accepted << "From: " + parts[1] + " → " + parts[2] + " | Fare: " + parts[3] + " | Rider: " + parts[5];
                }
            }
            file.close();
        }
        QMessageBox::information(this, "Accepted Rides", accepted.isEmpty() ? "No rides accepted yet." : accepted.join("\n"));
    });

    connect(viewProposalsBtn, &QPushButton::clicked, this, [=]() {
        QFile file("proposals.txt");
        QStringList proposals;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(",");
                if (parts.size() >= 3 && line.contains("Driver: " + username)) {
                    proposals << line;
                }
            }
            file.close();
        }
        if (proposals.isEmpty()) {
            QMessageBox::information(this, "Fare Proposals", "No proposals yet for your rides.");
            return;
        }
        bool ok;
        QString chosen = QInputDialog::getItem(this, "Fare Proposals", "Select a proposal to accept:", proposals, 0, false, &ok);
        if (ok && !chosen.isEmpty()) {
            QStringList chosenParts = chosen.split(",");
            QString riderName = chosenParts[0];
            QString counterFare = chosenParts[1];
            QFile ridesFile("rides.txt");
            QStringList lines;
            if (ridesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&ridesFile);
                while (!in.atEnd()) {
                    QString line = in.readLine();
                    QStringList parts = line.split(",");
                    if (parts.size() >= 5 && parts[0] == username && parts[4] == "Pending") {
                        parts[4] = "Accepted";
                        if (parts.size() == 5) {
                            parts << riderName;
                        } else {
                            parts[5] = riderName;
                        }
                        line = parts.join(",");
                    }
                    lines << line;
                }
                ridesFile.close();
            }
            if (ridesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&ridesFile);
                for (const QString &line : lines)
                    out << line << "\n";
                ridesFile.close();
            }
            QMessageBox::information(this, "Proposal Accepted", "You accepted " + riderName + "'s proposal of " + counterFare + ". Ride marked as Accepted.");
        }
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
                if (parts.size() >= 5 && parts[0] == username && parts[4] == "Pending") {
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
            QMessageBox::information(this, "No Ride", "You have no pending rides to cancel.");
        }
    });

    connect(backArrow, &QToolButton::clicked, this, [=]() {
        MainWindow *mw = new MainWindow(username, true);
        mw->show();
        this->close();
    });
}

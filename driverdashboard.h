#ifndef DRIVERDASHBOARD_H
#define DRIVERDASHBOARD_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class DriverDashboard : public QWidget
{
    Q_OBJECT
public:
    explicit DriverDashboard(QString username, QWidget *parent = nullptr);

private:
    QString username;
    QLineEdit *originInput;
    QLineEdit *destinationInput;
    QLineEdit *fareInput;
    QPushButton *postRideBtn;

    void postRide();
};

#endif

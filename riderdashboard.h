#ifndef RIDERDASHBOARD_H
#define RIDERDASHBOARD_H

#include <QWidget>
#include <QListWidget>

class RiderDashboard : public QWidget
{
    Q_OBJECT
public:
    explicit RiderDashboard(QString username, QWidget *parent = nullptr);

private:
    QString username;
    QLineEdit *counterFareInput;
    QListWidget *rideList;

    void loadRides();
};

#endif // RIDERDASHBOARD_H

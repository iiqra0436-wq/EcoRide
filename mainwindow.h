#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QString username, bool isDriver, QWidget *parent = nullptr);

private:
    QString username;
    bool isDriver;
};

#endif

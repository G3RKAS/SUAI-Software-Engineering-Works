#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr, QString FIO="", QString Position="");
    static QString FIOnPosToRegCode(QString, QString);

    void SetOrder(int);

    QString GetRegCode();
    QString GetFIO();
    QString GetPosition();
    bool IsBusy();
    QString GetOrderStatus();

private:
    QString RegCode;
    QString FIO;
    QString Position;
    bool MasterBusy;
    int OrderNumber;
};

#endif // WORKER_H

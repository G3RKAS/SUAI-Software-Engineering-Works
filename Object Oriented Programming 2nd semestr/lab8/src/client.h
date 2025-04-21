#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr, QString FIO = "", QString Adress="", QString PhoneNumber="");
    static int PhoneNumberToRegNumber(QString);

    int GetRegNumber();
    QString GetFIO();
    QString GetAdress();
    QString GetPhoneNumber();

private:
    int RegNumber;
    QString FIO;
    QString Adress;
    QString PhoneNumber;

signals:
};

#endif // CLIENT_H

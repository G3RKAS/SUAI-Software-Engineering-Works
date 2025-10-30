#include "client.h"


Client::Client(QObject *parent, QString FIO, QString Adress, QString PhoneNumber)
    : QObject{parent}
{
    this->FIO = FIO;
    this->Adress = Adress;
    this->PhoneNumber = PhoneNumber;

    this->RegNumber = Client::PhoneNumberToRegNumber(PhoneNumber);
}

QString Client::GetFIO()
{
    return this->FIO;
}

QString Client::GetAdress()
{
    return this->Adress;
}

QString Client::GetPhoneNumber()
{
    return this->PhoneNumber;
}

int Client::GetRegNumber()
{
    return this->RegNumber;
}

int Client::PhoneNumberToRegNumber(QString PhoneNumber)
{
    QString NumberToSum = PhoneNumber.replace( " ", "" ).remove('+');
    int OutSum = 0;
    for (auto number : std::as_const(NumberToSum) )
    {
        OutSum += pow(number.digitValue(), 2);
    }
    return OutSum;
}

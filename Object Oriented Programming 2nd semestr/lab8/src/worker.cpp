#include "worker.h"
#include "qdebug.h"

Worker::Worker(QObject *parent, QString FIO, QString Position)
    : QObject{parent}
{
    this->FIO = FIO;
    this->Position = Position;
    this->MasterBusy = false;
    this->OrderNumber = -1;

    this->RegCode = Worker::FIOnPosToRegCode(FIO, Position);
}

void Worker::SetOrder(int OrderNumber)
{
    this->OrderNumber = OrderNumber;
    if (OrderNumber == -1)
    {
        this->MasterBusy = false;
    }
    else
    {
        this->MasterBusy = true;
    }
}

QString Worker::GetRegCode()
{
    return this->RegCode;
}

QString Worker::GetFIO()
{
    return this->FIO;
}

QString Worker::GetPosition()
{
    return this->Position;
}

bool Worker::IsBusy()
{
    return this->MasterBusy;
}

QString Worker::GetOrderStatus()
{
    if ((this->OrderNumber == -1) && not(this->MasterBusy))
    {
        return "Нет";
    }
    return "Есть";
}

QString Worker::FIOnPosToRegCode(QString FIO, QString Position)
{
    QString RegCode = "";
    if (Position == "Intern")
    {
        RegCode += "IN-";
    }
    else if (Position == "Junior")
    {
        RegCode += "JN-";
    }
    else if (Position == "Middle")
    {
        RegCode += "ML-";
    }
    else if (Position == "Senior")
    {
        RegCode += "SN-";
    }
    else
    {
        RegCode += "OT-";
    }

    int tempCode = 0;
    FIO = FIO.toUpper();
    foreach (auto str, FIO.split(" ")){
        if (str.isEmpty())
        {
            continue;
        }
        tempCode += int(str[0].unicode());
    }
    return RegCode + QString::number(tempCode);
}

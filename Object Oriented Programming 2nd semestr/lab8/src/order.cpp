#include "order.h"

Order::Order(QObject *parent, int ClientRegNumber,
             QString MasterRegCode, QString ThingToRepair)
    : QObject{parent}
{
    this->ClientRegNumber = ClientRegNumber;
    this->MasterRegCode = MasterRegCode;
    this->ThingToRepair = ThingToRepair;
    this->StatusOfRepair = RepairStatus::InProcess;
    this->OrderNumber = -1;
}

void Order::SetOrderNumber(int OrderNum)
{
    this->OrderNumber = OrderNum;
}

void Order::SetRepairStatus(RepairStatus Status)
{
    this->StatusOfRepair = Status;
}

int Order::GetClientRegNumber()
{
    return this->ClientRegNumber;
}

QString Order::GetMasterRegCode()
{
    return this->MasterRegCode;
}

QString Order::GetThingToRepair()
{
    return this->ThingToRepair;
}

QString Order::GetStatusOfRepair()
{
    switch (this->StatusOfRepair)
    {
    case RepairStatus::InProcess:
        return "В процессе";
        break;
    case RepairStatus::Completed:
        return "Выполнен";
        break;
    }
    return "";
}

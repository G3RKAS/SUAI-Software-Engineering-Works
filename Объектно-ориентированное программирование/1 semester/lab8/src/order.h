#ifndef ORDER_H
#define ORDER_H

#include <QObject>

class Order : public QObject
{
    Q_OBJECT
public:
    enum class RepairStatus
    {
        InProcess,
        Completed
    };

    explicit Order(QObject *parent = nullptr, int ClientRegNumber = 0,
                   QString MasterRegCode = "", QString ThingToRepair = "");
    void SetOrderNumber(int);
    void SetRepairStatus(RepairStatus);

    int GetClientRegNumber();
    QString GetMasterRegCode();
    QString GetThingToRepair();
    QString GetStatusOfRepair();

private:
    int ClientRegNumber;
    QString MasterRegCode;
    QString ThingToRepair;
    RepairStatus StatusOfRepair;
    int OrderNumber;
};

#endif // ORDER_H
